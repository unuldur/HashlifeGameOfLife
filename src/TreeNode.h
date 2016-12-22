//
// Created by PAYS on 13/10/2016.
//

#ifndef GAMEOFLIFE_TREENODE_H
#define GAMEOFLIFE_TREENODE_H

#include <string.h>
#include <iostream>
#include <vector>

using namespace std;
class TreeNode{
public:

    TreeNode(TreeNode *nw, TreeNode *ne, TreeNode *sw, TreeNode *se);

    TreeNode(bool living);

    TreeNode(const int & level);

    static TreeNode* create();

    virtual TreeNode* create(bool living);

    virtual TreeNode* create(int level);

    virtual TreeNode* create(TreeNode* nw, TreeNode* ne, TreeNode* sw, TreeNode* se);

    virtual TreeNode* nextGeneration();

    virtual ~TreeNode();

    int getByte(const int x,const int y) const;

    TreeNode * setByte(const int x, const int y, bool living);


    TreeNode *expandUniverse();

    int getLevel() const;

    bool isLiving() const;

    TreeNode *getNw() const;

    TreeNode *getNe() const;

    TreeNode *getSw() const;

    TreeNode *getSe() const;

    double getPopulation() const;

    string getDifference(const TreeNode* t, const int& x,const int& y) const;


protected:
    TreeNode* nw;
    TreeNode* ne;
    TreeNode* sw;
    TreeNode* se;
    bool living;
    double population;
    int level;

    TreeNode* oneGen(int bitmask);

    TreeNode* slowSimulation();

    TreeNode *centeredSubnode();

    TreeNode *centeredVertical(TreeNode *n, TreeNode *s);

    TreeNode *centeredHorizontal(TreeNode *pNode, TreeNode *pTreeNode);

    TreeNode *centeredSubSubnode();

    string getLivingCell(const int& x,const int& y) const;


};


#endif //GAMEOFLIFE_TREENODE_H
