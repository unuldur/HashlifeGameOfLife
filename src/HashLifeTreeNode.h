//
// Created by julie on 22/12/2016.
//

#ifndef GAMEOFLIFE_HASHLIFETREENODE_H
#define GAMEOFLIFE_HASHLIFETREENODE_H


#include "CanonicalTreeNode.h"

class HashLifeTreeNode : public CanonicalTreeNode {
public:
    HashLifeTreeNode(bool living);
    HashLifeTreeNode(TreeNode *nw, TreeNode *ne, TreeNode *sw, TreeNode *se);
    HashLifeTreeNode(int level);

    static TreeNode *create();
private:
    TreeNode *create(bool living) override;

    TreeNode *create(TreeNode *nw, TreeNode *ne, TreeNode *sw, TreeNode *se) override;

    TreeNode *create(int level) override;

    TreeNode *nextGeneration() override;

    TreeNode* result;
};


#endif //GAMEOFLIFE_HASHLIFETREENODE_H
