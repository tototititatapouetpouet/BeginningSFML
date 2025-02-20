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

    BT::Sequence behavior;

    auto* nTimes = new BT::DoNTime(&behavior, 3);

    auto* findEnemy = new BT::FindEnemy(nTimes, &game.npc);
    auto* killAnEnemy = new BT::Retry(nTimes);

    auto* victoryDance = new BT::VictoryDance(&behavior);

    new BT::ReloadGunIfEmpty(killAnEnemy);
    new BT::Fire(killAnEnemy, &game.npc);
    new BT::IsEnemyDead(killAnEnemy, &game.npc);

    testBourrin(&behavior);
}


