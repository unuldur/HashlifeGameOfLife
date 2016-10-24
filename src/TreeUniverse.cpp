//
// Created by PAYS on 16/10/2016.
//

#include "TreeUniverse.h"



void TreeUniverse::runStep() {
    while (root->getLevel() < 3 ||
           root->getNw()->getPopulation() != root->getNw()->getSe()->getSe()->getPopulation() ||
           root->getNe()->getPopulation() != root->getNe()->getSw()->getSw()->getPopulation() ||
           root->getSw()->getPopulation() != root->getSw()->getNe()->getNe()->getPopulation() ||
           root->getSe()->getPopulation() != root->getSe()->getNw()->getNw()->getPopulation())
    {
        root = root->expandUniverse();
    }
    root =  root->nextGeneration();
}

void TreeUniverse::setByte(const int x,const int y) {
    while (true) {
        int maxCoordinate = 1 << (root->getLevel() - 1) ;
        if (-maxCoordinate <= x && x <= maxCoordinate-1 && -maxCoordinate <= y && y <= maxCoordinate-1)
            break ;
        root = root->expandUniverse() ;
    }
    root =  root->setByte(x, y) ;
}

int TreeUniverse::getByte(const int x,const int y) const{
    return root->getByte(x,y);
}

TreeUniverse::TreeUniverse() {
    root = TreeNode::create();
}

TreeUniverse::~TreeUniverse() {
    delete root;
}

int TreeUniverse::getLevel() const {
    return root->getLevel();
}

TreeNode *TreeUniverse::getRoot() const {
    return root;
}

