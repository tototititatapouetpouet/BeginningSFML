#include "Tree.h"

int main()
{
    CompositeNode cNode;

    auto* grosNode1 = new CompositeNode(&cNode);
    auto* node1 = new LeafNode{ grosNode1 };
    auto* node2 = new LeafNode{ grosNode1 };

    auto* grosNode2 = new CompositeNode(&cNode);
    auto* node12 = new LeafNode{ grosNode2 };
    auto* node22 = new LeafNode{ grosNode2 };

    cNode.display();

    CompositeNode someRoot;
    grosNode2->setParent(&someRoot);

    std::cout << "dssdfufsd";
}


