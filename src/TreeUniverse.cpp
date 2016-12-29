//
// Created by PAYS on 16/10/2016.
//

#include "TreeUniverse.h"
#include "CanonicalTreeNode.h"
#include "HashLifeTreeNode.h"


void TreeUniverse::runStep() {
    if(root == nullptr)
    {
        return;
    }
    double populationNw = 0, populationNe = 0, populationSw = 0, populationSe = 0;
    double populationNwSeSe = 0, populationNeSwSw = 0, populationSwNeNe = 0, populationSeNwNw = 0;
    while(true){
        if(root->getNw() != nullptr)
        {
            populationNw = root->getNw()->getPopulation();
            if(root->getNw()->getSe() != nullptr && root->getNw()->getSe()->getSe() != nullptr){
                populationNwSeSe = root->getNw()->getSe()->getSe()->getPopulation();
            }
        }
        if(root->getNe() != nullptr)
        {
            populationNe = root->getNe()->getPopulation();
            if(root->getNe()->getSw() != nullptr && root->getNe()->getSw()->getSw() != nullptr){
                populationNeSwSw = root->getNe()->getSw()->getSw()->getPopulation();
            }
        }
        if(root->getSw() != nullptr)
        {
            populationSw = root->getSw()->getPopulation();
            if(root->getSw()->getNe() != nullptr && root->getSw()->getNe()->getNe() != nullptr){
                populationSwNeNe = root->getSw()->getNe()->getNe()->getPopulation();
            }
        }
        if(root->getSe() != nullptr)
        {
            populationSe = root->getSe()->getPopulation();
            if(root->getSe()->getNw() != nullptr && root->getSe()->getNw()->getNw() != nullptr){
                populationSeNwNw = root->getSe()->getNw()->getNw()->getPopulation();
            }
        }
        if (root->getLevel() >= 3 &&
               populationNw == populationNwSeSe &&
               populationNe == populationNeSwSw &&
               populationSw == populationSwNeNe &&
               populationSe == populationSeNwNw) {
            break;
        }
        root = root->expandUniverse();
    }
    root =  root->nextGeneration();
}

void TreeUniverse::setByte(const int x,const int y, bool living) {
    if(root == nullptr)
    {
        root = TreeNode::create();
    }
    while (true) {
        int maxCoordinate = 1 << (root->getLevel() - 1) ;
        if (-maxCoordinate <= x && x <= maxCoordinate-1 && -maxCoordinate <= y && y <= maxCoordinate-1)
            break ;
        root = root->expandUniverse() ;
    }

    root =  root->setByte(x, y, living) ;
}

int TreeUniverse::getByte(const int x,const int y) const{
    if(root == nullptr){
        return 0;
    }
    return root->getByte(x,y);
}

TreeUniverse::TreeUniverse() {
    root = nullptr;
}

TreeUniverse::~TreeUniverse() {
    delete root;
}

int TreeUniverse::getLevel() const {
    if(root == nullptr)
    {
        return 0;
    }
    return root->getLevel();
}

TreeNode *TreeUniverse::getRoot() const {
    return root;
}

