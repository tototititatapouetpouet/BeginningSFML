#include "Tree.h"

#include <conio.h>

void testBourrin(BT::CompositeNode* node)
{
    BT::Status status = BT::Running;
    while (status == BT::Running)
    {
        status = node->tick();
        ::_getch();
    }
}

int main()
{
    Game game;

    BT::RootNode rootNode(&game.npc);

    BT::Sequence behavior(&rootNode);

    auto* nTimes = new BT::DoUntilFailure(&behavior);

    auto* findEnemy = new BT::FindEnemy(nTimes, &game.npc);
    auto* killAnEnemy = new BT::Retry(nTimes);

    auto* victoryDance = new BT::VictoryDance(&behavior);

    auto* ifGunEmpty = new BT::IfGunEmpty(killAnEnemy);
    new BT::ReloadGun(ifGunEmpty, &game.npc);
    new BT::Fire(killAnEnemy, &game.npc);
    new BT::IsEnemyDead(killAnEnemy, &game.npc);

    testBourrin(&behavior);
}


