//
// Created by julie on 22/12/2016.
//

#include "HashLifeTreeNode.h"


HashLifeTreeNode::HashLifeTreeNode(bool living) : CanonicalTreeNode(living) {}

HashLifeTreeNode::HashLifeTreeNode(TreeNode *nw, TreeNode *ne, TreeNode *sw, TreeNode *se) : CanonicalTreeNode(nw, ne,
                                                                                                               sw,
                                                                                                               se) {}

HashLifeTreeNode::HashLifeTreeNode(int level) : CanonicalTreeNode(level) {}

TreeNode *HashLifeTreeNode::create(bool living) {
    return (new HashLifeTreeNode(living))->intern();
}

TreeNode *HashLifeTreeNode::create(TreeNode *nw, TreeNode *ne, TreeNode *sw, TreeNode *se) {
    if(nw == nullptr && ne == nullptr && sw == nullptr && se == nullptr){
        return nullptr;
    }
    HashLifeTreeNode* tree = new HashLifeTreeNode(nw,ne,sw,se);
    if(tree->getPopulation() == 0)
    {
        return nullptr;
    }
    return tree->intern();
}

TreeNode *HashLifeTreeNode::create(int level) {
    return (new HashLifeTreeNode(level));
}

TreeNode *HashLifeTreeNode::nextGeneration() {
    if(result == nullptr){
        result = TreeNode::nextGeneration();
    }
    return result;
}

TreeNode *HashLifeTreeNode::create() {
    return new HashLifeTreeNode(3);
}
