//
// Created by PAYS on 13/10/2016.
//

#include <sstream>

#include "TreeNode.h"

TreeNode::TreeNode(bool living) : living(living),nw(nullptr),ne(nullptr),sw(nullptr),se(nullptr) {
    level = 0;
    population = living ? 1 : 0;
}

TreeNode::TreeNode(TreeNode *nw, TreeNode *ne, TreeNode *sw, TreeNode *se) :  sw(sw), ne(ne), nw(nw), se(se){
    population = 0;
    if(nw != nullptr)
    {
        population += nw->getPopulation();
        level = nw->level + 1;
    }
    if(ne != nullptr)
    {
        population += ne->getPopulation();
        level = ne->level + 1;
    }
    if(sw != nullptr)
    {
        population += sw->getPopulation();
        level = sw->level + 1;
    }
    if(se != nullptr)
    {
        population += se->getPopulation();
        level = se->level + 1;
    }
    living = population != 0;

}

TreeNode::~TreeNode() {
    delete nw;
    delete ne;
    delete sw;
    delete se;
}

TreeNode* TreeNode::oneGen(int bitmask){
    if(bitmask == 0)
    {
        return nullptr;
    }
    int self = (bitmask >> 5) & 1;
    bitmask &= 0x757;
    int nbNeighbours = 0;
    while (bitmask != 0)
    {
        nbNeighbours++;
        bitmask &= (bitmask - 1);
    }
    if(nbNeighbours == 3 || (nbNeighbours == 2 && self != 0))
    {
        return create(true);
    }
    return nullptr;
}

TreeNode* TreeNode::slowSimulation(){
    int allbits = 0 ;
    for (int y=-2; y<2; y++)
        for (int x=-2; x<2; x++)
            allbits = (allbits << 1) + getByte(x, y) ;

    return create(oneGen(allbits>>5), oneGen(allbits>>4),
                  oneGen(allbits>>1), oneGen(allbits)) ;
}

TreeNode* TreeNode::centeredSubnode(){
    TreeNode* n00 = create(level-2);
    if(nw != nullptr)
    {
        n00 = nw->se;
    }
    TreeNode* n01 = create(level-2);
    if(ne != nullptr)
    {
        n01 = ne->sw;
    }
    TreeNode* n10 = create(level-2);
    if(sw != nullptr)
    {
        n10 = sw->ne;
    }
    TreeNode* n11 = create(level-2);
    if(se != nullptr)
    {
        n11 = se->nw;
    }
    return create(n00,n01,n10,n11);
}

TreeNode* TreeNode::centeredVertical(TreeNode* n,TreeNode* s)
{
    TreeNode* n00 = create(level-3);
    if(n != nullptr && n->sw != nullptr)
    {
        n00 = n->sw->se;
    }
    TreeNode* n01 = create(level-3);
    if(n != nullptr && n->se != nullptr)
    {
        n01 = n->se->sw;
    }
    TreeNode* n10 = create(level-3);
    if(s != nullptr && s->nw != nullptr)
    {
        n10 = s->nw->ne;
    }
    TreeNode* n11 = create(level-3);
    if(s != nullptr && s->ne != nullptr)
    {
        n11 = s->ne->nw;
    }
    return create(n00,n01,n10,n11);
}

TreeNode *TreeNode::centeredHorizontal(TreeNode *w, TreeNode *e){
    TreeNode* n00 = create(level-3);
    if(w != nullptr && w->ne != nullptr)
    {
        n00 = w->ne->se;
    }
    TreeNode* n01 = create(level-3);
    if(e != nullptr && e->nw != nullptr)
    {
        n01 = e->nw->sw;
    }
    TreeNode* n10 = create(level-3);
    if(w != nullptr && w->se != nullptr)
    {
        n10 = w->se->ne;
    }
    TreeNode* n11 = create(level-3);
    if(e != nullptr && e->sw != nullptr)
    {
        n11 = e->sw->nw;
    }
    return create(n00,n01,n10,n11);
}

TreeNode *TreeNode::centeredSubSubnode(){
    TreeNode* n00 = create(level-3);
    if(nw != nullptr && nw->se != nullptr)
    {
        n00 = nw->se->se;
    }
    TreeNode* n01 = create(level-3);
    if(ne != nullptr && ne->sw != nullptr)
    {
        n01 = ne->sw->sw;
    }
    TreeNode* n10 = create(level-3);
    if(sw != nullptr && sw->ne != nullptr)
    {
        n10 = sw->ne->ne;
    }
    TreeNode* n11 = create(level-3);
    if(se != nullptr && se->nw != nullptr)
    {
        n11 = se->nw->nw;
    }
    return create(n00,n01,n10,n11);
}

TreeNode* TreeNode::nextGeneration(){
    if(population == 0)
    {
        return create(level - 1);
    }
    if(level == 2)
    {
        return slowSimulation();
    }
    TreeNode* n00 = nullptr;
    if(nw != nullptr) {
        n00 = nw->centeredSubnode();
    }
    TreeNode* n01 = centeredHorizontal(nw, ne);
    TreeNode* n02 = nullptr;
    if(ne != nullptr) {
        n02 = ne->centeredSubnode();
    }
    TreeNode* n10 = centeredVertical(nw, sw);
    TreeNode* n11 = centeredSubSubnode();
    TreeNode* n12 = centeredVertical(ne, se);
    TreeNode* n20 = nullptr;
    if(sw != nullptr) {
        n20 = sw->centeredSubnode();
    }
    TreeNode* n21 = centeredHorizontal(sw, se);
    TreeNode* n22 = nullptr;
    if(se != nullptr)
    {
        n22 = se->centeredSubnode() ;
    }
    TreeNode* nn00 = create(n00, n01, n10, n11);
    TreeNode* nn01 = create(n01, n02, n11, n12);
    TreeNode* nn10 = create(n10, n11, n20, n21);
    TreeNode* nn11 = create(n11, n12, n21, n22);
    if(nn00 != nullptr)
    {
        nn00 = nn00->nextGeneration();
    }
    if(nn01 != nullptr)
    {
        nn01 = nn01->nextGeneration();
    }
    if(nn10 != nullptr)
    {
        nn10 = nn10->nextGeneration();
    }
    if(nn11 != nullptr)
    {
        nn11 = nn11->nextGeneration();
    }
    return create(nn00,nn01,nn10,nn11);

}


TreeNode *TreeNode::expandUniverse(){
    if(nw == nullptr && ne == nullptr && sw == nullptr && se == nullptr){
        return create(level + 1);
    }
    TreeNode* n00 = nullptr;
    if(nw != nullptr)
    {
        n00 = create(nullptr, nullptr, nullptr, nw);
    }
    TreeNode* n01 = nullptr;
    if(ne != nullptr)
    {
        n01 = create(nullptr, nullptr, ne, nullptr);
    }
    TreeNode* n10 = nullptr;
    if(sw != nullptr)
    {
        n10 = create(nullptr, sw, nullptr, nullptr);
    }
    TreeNode* n11 = nullptr;
    if(se != nullptr)
    {
        n11 = create(se, nullptr, nullptr, nullptr);
    }
    return create(n00,n01,n10,n11);
}



int TreeNode::getByte(const int x, const int y) const{
    if(level == 0)
    {
        return living ? 1 : 0;
    }
    int offset = 1 << (level -2);
    if (x < 0) {
        if (y < 0) {
            if(nw == nullptr)
            {
                return 0;
            }
            return nw->getByte(x + offset, y + offset);
        } else {
            if(sw == nullptr)
            {
                return 0;
            }
            return sw->getByte(x + offset, y - offset);
        }
    } else {
        if (y < 0) {
            if(ne == nullptr)
            {
                return 0;
            }
            return ne->getByte(x - offset, y + offset);
        } else {
            if(se == nullptr)
            {
                return 0;
            }
            return se->getByte(x - offset, y - offset);
        }
    }
}

TreeNode * TreeNode::setByte(const int x, const int y, bool living) {
    if(level == 0)
    {
        if(living) {
            return create(true);
        }
        return nullptr;
    }
    int offset = 1 << (level -2);
    if (x < 0) {
        if (y < 0) {
            if(nw == nullptr)
            {
                nw = create(level - 1);
            }
            return create(nw->setByte(x + offset, y + offset,living),ne,sw,se);
        } else {
            if(sw == nullptr)
            {
                sw = create(level - 1);
            }
            return create(nw,ne,sw->setByte(x + offset, y - offset,living),se);
        }
    } else {
        if (y < 0) {
            if(ne == nullptr)
            {
                ne = create(level - 1);
            }
            return create(nw,ne->setByte(x - offset, y + offset,living),sw,se);
        } else {
            if(se == nullptr)
            {
                se = create(level - 1);
            }
            return create(nw,ne,sw,se->setByte(x - offset, y - offset,living));
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

bool TreeNode::isLiving() const {
    return living;
}

double TreeNode::getPopulation() const {
    return population;
}

TreeNode *TreeNode::create() {
    return new TreeNode(3);
}

TreeNode *TreeNode::create(bool living){
    return new TreeNode(living);
}

TreeNode *TreeNode::create(TreeNode *nw, TreeNode *ne, TreeNode *sw, TreeNode *se){
    if(nw == nullptr && ne == nullptr && sw == nullptr && se == nullptr){
        return nullptr;
    }
    TreeNode* tree = new TreeNode(nw,ne,sw,se);
    if(tree->getPopulation() == 0)
    {
        return nullptr;
    }
    return tree;
}

string TreeNode::getLivingCell(const int& x, const int& y) const
{
    stringstream ss;
    int x2, y2;
    if(level == 0)
    {
        ss << "x=" << x << ",y="<<y << " ";
        return ss.str();
    }
    int offset = 1 << (level -2);
    if(level == 1)
    {
        offset = 0;
    }
    if(nw != nullptr)
    {
        x2 = x;
        y2 = y;
        if(level == 1)
        {
            x2--;
            y2--;
        }
        ss << nw->getLivingCell(x2 - offset, y2 - offset);
    }
    if(sw != nullptr)
    {
        x2 = x;
        if(level == 1)
        {
            x2--;
        }
        ss << sw->getLivingCell(x2 - offset, y + offset);
    }
    if(ne != nullptr)
    {
        y2 = y;
        if(level == 1)
        {
            y2--;
        }
        ss << ne->getLivingCell(x + offset, y2 - offset);
    }
    if(se != nullptr)
    {
        ss << se->getLivingCell(x + offset, y + offset);
    }
    return ss.str();
}

string TreeNode::getDifference(const TreeNode* t, const int& x, const int& y) const {
    stringstream ss;
    int x2, y2;
    if(t == nullptr)
    {
        return getLivingCell(x,y);
    }
    if(level == 0)
    {
        if(living != t->isLiving()) {
            ss << "x=" << x << ",y=" << y << " ";
        }
        return ss.str();
    }

    int offset = 1 << (level -2);
    if(level == 1)
    {
        offset = 0;
    }
    x2 = x;
    y2 = y;
    if(level == 1)
    {
        x2--;
        y2--;
    }
    if(nw == nullptr)
    {
        if(t->nw != nullptr) {
            ss << t->nw->getLivingCell(x2 - offset, y2 - offset);
        }
    }else{
        ss << nw->getDifference(t->nw,x2 - offset, y2 - offset);
    }


    y2 = y;
    if(level == 1)
    {
        y2--;
    }
    if(ne == nullptr)
    {
        if(t->ne != nullptr) {
            ss << t->ne->getLivingCell(x + offset, y2 - offset);
        }
    }else {
        ss << ne->getDifference(t->ne, x + offset, y2 - offset);
    }


    if(se == nullptr)
    {
        if(t->se != nullptr) {
            ss << t->se->getLivingCell(x + offset, y + offset);
        }
    }else {
        ss << se->getDifference(t->se, x + offset, y + offset);
    }


    x2 = x;
    if(level == 1)
    {
        x2--;
    }
    if(sw == nullptr)
    {
        if(t->sw != nullptr) {
            ss << t->sw->getLivingCell(x2 - offset, y + offset);
        }
    }else {
        ss << sw->getDifference(t->sw, x2 - offset, y + offset);
    }
    return ss.str();
}

TreeNode::TreeNode(const int &level): living(false),nw(nullptr),ne(nullptr),sw(nullptr),se(nullptr),level(level),population(0) {
}

TreeNode *TreeNode::create(int level) {
    return new TreeNode(level);
}




