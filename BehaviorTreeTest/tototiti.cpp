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

    rootNode.getRootNode();

    BT::Sequence behavior(&rootNode);

    auto* nTimes = new BT::DoUntilFailure(&behavior);

    auto* findEnemy = new BT::FindEnemy(nTimes);
    auto* killAnEnemy = new BT::Retry(nTimes);

    auto* victoryDance = new BT::VictoryDance(&behavior);

    auto* ifGunEmpty = new BT::IfGunEmpty(killAnEnemy);
    new BT::ReloadGun(ifGunEmpty);
    new BT::Fire(killAnEnemy);
    new BT::IsEnemyDead(killAnEnemy);

    testBourrin(&behavior);
}


