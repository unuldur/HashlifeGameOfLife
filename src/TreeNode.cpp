//
// Created by PAYS on 13/10/2016.
//

#include <sstream>

#include <list>
#include "TreeNode.h"

TreeNode::TreeNode(bool living) : living(living),nw(nullptr),ne(nullptr),sw(nullptr),se(nullptr) {
    level = 0;
    population = living ? 1 : 0;
}

TreeNode::TreeNode(TreeNode *nw, TreeNode *ne, TreeNode *sw, TreeNode *se) :  sw(sw), ne(ne), nw(nw), se(se){
    population = nw->population + ne->population + sw->population + se->population;
    living = population != 0;
    level = nw->level + 1;
}

TreeNode::~TreeNode() {
    delete nw;
    delete ne;
    delete sw;
    delete se;
}

TreeNode* TreeNode::oneGen(int bitmask) const{
    if(bitmask == 0)
    {
        return create(false);
    }
    int self = (bitmask >> 5) & 1;
    bitmask &= 0x757;
    int nbNeighbours = 0;
    while (bitmask != 0)
    {
        nbNeighbours++;
        bitmask &= (bitmask - 1);
    }
    return create(nbNeighbours == 3 || (nbNeighbours == 2 && self != 0));
}

TreeNode* TreeNode::slowSimulation() const{
    int allbits = 0 ;
    for (int y=-2; y<2; y++)
        for (int x=-2; x<2; x++)
            allbits = (allbits << 1) + getByte(x, y) ;
    return create(oneGen(allbits>>5), oneGen(allbits>>4),
                  oneGen(allbits>>1), oneGen(allbits)) ;
}

TreeNode* TreeNode::centeredSubnode() const{
    return create(nw->se, ne->sw, sw->ne, se->nw) ;
}

TreeNode* TreeNode::centeredVertical(TreeNode* n,TreeNode* s) const
{
    return create(n->sw->se, n->se->sw, s->nw->ne, s->ne->nw) ;
}

TreeNode *TreeNode::centeredHorizontal(TreeNode *w, TreeNode *e) const{
    return create(w->ne->se, e->nw->sw, w->se->ne, e->sw->nw) ;
}

TreeNode *TreeNode::centeredSubSubnode() const{
    return create(nw->se->se, ne->sw->sw, sw->ne->ne, se->nw->nw) ;

}

TreeNode* TreeNode::nextGeneration() const{
    if(population == 0)
    {
        return nw;
    }
    if(level == 2)
    {
        return slowSimulation();
    }
    TreeNode* n00 = nw->centeredSubnode();
    TreeNode* n01 = centeredHorizontal(nw, ne);
    TreeNode* n02 = ne->centeredSubnode();
    TreeNode* n10 = centeredVertical(nw, sw);
    TreeNode* n11 = centeredSubSubnode();
    TreeNode* n12 = centeredVertical(ne, se);
    TreeNode* n20 = sw->centeredSubnode();
    TreeNode* n21 = centeredHorizontal(sw, se);
    TreeNode* n22 = se->centeredSubnode() ;
    return create((create(n00, n01, n10, n11))->nextGeneration(),
                        (create(n01, n02, n11, n12))->nextGeneration(),
                        (create(n10, n11, n20, n21))->nextGeneration(),
                        (create(n11, n12, n21, n22))->nextGeneration()) ;

}


TreeNode *TreeNode::expandUniverse() const{
    TreeNode* border = emptyTree(level-1) ;
    return create(create(border, border, border, nw),
                            create(border, border, ne, border),
                            create(border, sw, border, border),
                            create(se, border, border, border)) ;
}

TreeNode *TreeNode::emptyTree(const int lev) const{
    if (lev == 0)
        return create(false) ;
    TreeNode* n = emptyTree(lev-1) ;
    return create(n, n, n, n) ;
}

int TreeNode::getByte(const int x, const int y) const{
    if(level == 0)
    {
        return living ? 1 : 0;
    }
    int offset = 1 << (level -2);
    if (x < 0) {
        if (y < 0) {
            return nw->getByte(x + offset, y + offset);
        } else {
            return sw->getByte(x + offset, y - offset);
        }
    } else {
        if (y < 0) {
            return ne->getByte(x - offset, y + offset);
        } else {
            return se->getByte(x - offset, y - offset);
        }
    }
}

TreeNode *TreeNode::setByte(const int x,const int y) const{
    if(level == 0)
    {
        return create(true);
    }
    int offset = 1 << (level -2);
    if (x < 0) {
        if (y < 0) {
            return create(nw->setByte(x + offset, y + offset),ne,sw,se);
        } else {
            return create(nw,ne,sw->setByte(x + offset, y - offset),se);
        }
    } else {
        if (y < 0) {
            return create(nw,ne->setByte(x - offset, y + offset),sw,se);
        } else {
            return create(nw,ne,sw,se->setByte(x - offset, y - offset));
        }
    }
}

int TreeNode::getLevel() const {
    return level;
}

TreeNode *TreeNode::getNw() const {
    return nw;
}

TreeNode *TreeNode::getNe() const {
    return ne;
}

TreeNode *TreeNode::getSw() const {
    return sw;
}

TreeNode *TreeNode::getSe() const {
    return se;
}

double TreeNode::getPopulation() const {
    return population;
}

TreeNode *TreeNode::create() {
    return (new TreeNode(false))->emptyTree(3);
}

TreeNode *TreeNode::create(bool living){
    return new TreeNode(living);
}

TreeNode *TreeNode::create(TreeNode *nw, TreeNode *ne, TreeNode *sw, TreeNode *se){
    return new TreeNode(nw,ne,sw,se);
}



vector<string> TreeNode::getLignesTreeNode() const
{
    vector<string> my;
    if(level == 0)
    {
        living?my.push_back("1"):my.push_back("0");
        return my;
    }
    vector<string> snw = nw->getLignesTreeNode();
    vector<string> sne = ne->getLignesTreeNode();
    vector<string> ssw = sw->getLignesTreeNode();
    vector<string> sse = se->getLignesTreeNode();

    int nb = snw.size();
    for (int i = 0; i < nb; ++i) {
        my.push_back(snw[i]+sne[i]);
    }
    for (int i = 0; i < nb; ++i) {
        my.push_back(ssw[i]+sse[i]);
    }
    return my;

}

string TreeNode::getThis() const {
    vector<string> myVec = getLignesTreeNode();
    string my ="";
    int taille = myVec.size();
    for (int i = 0; i < taille; ++i) {
        my += myVec[i]+"\n";
    }
    return my;
}



