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

    static TreeNode* create(bool living);

    static TreeNode* create(const int& level);

    static TreeNode* create(TreeNode* nw, TreeNode* ne, TreeNode* sw, TreeNode* se);

    TreeNode* nextGeneration() const;

    virtual ~TreeNode();

    int getByte(const int x,const int y) const;

    TreeNode * setByte(const int x, const int y, bool living);


    TreeNode *expandUniverse() const;

    int getLevel() const;

    TreeNode *getNw() const;

    TreeNode *getNe() const;

    TreeNode *getSw() const;

    TreeNode *getSe() const;

    double getPopulation() const;

    string getThis() const;

private:
    TreeNode* nw;
    TreeNode* ne;
    TreeNode* sw;
    TreeNode* se;
    bool living;
    double population;
    int level;

    TreeNode* oneGen(int bitmask) const;

    TreeNode* slowSimulation() const;

    TreeNode *centeredSubnode()const;

    TreeNode *centeredVertical(TreeNode *n, TreeNode *s) const;

    TreeNode *centeredHorizontal(TreeNode *pNode, TreeNode *pTreeNode)const;

    TreeNode *centeredSubSubnode()const;

    vector<string> getLignesTreeNode() const;




};


#endif //GAMEOFLIFE_TREENODE_H
