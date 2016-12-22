//
// Created by julie on 20/12/2016.
//

#include "CanonicalTreeNode.h"

CanonicalTreeNode::CanonicalTreeNode(bool living) : TreeNode(living) {

}

CanonicalTreeNode::CanonicalTreeNode(TreeNode *nw, TreeNode *ne, TreeNode *sw, TreeNode *se) : TreeNode(nw, ne, sw,
                                                                                                        se) {

}

CanonicalTreeNode::CanonicalTreeNode(int level) : TreeNode(level) {

}

TreeNode *CanonicalTreeNode::create(bool living) {
    return (new CanonicalTreeNode(living))->intern();
}

TreeNode *CanonicalTreeNode::create(TreeNode *nw, TreeNode *ne, TreeNode *sw, TreeNode *se) {
    if(nw == nullptr && ne == nullptr && sw == nullptr && se == nullptr){
        return nullptr;
    }
    CanonicalTreeNode* tree = new CanonicalTreeNode(nw,ne,sw,se);
    if(tree->getPopulation() == 0)
    {
        return nullptr;
    }
    return tree->intern();
}

TreeNode *CanonicalTreeNode::create() {
    return (new CanonicalTreeNode(3));
}

TreeNode* CanonicalTreeNode::create(int level) {
    return (new CanonicalTreeNode(level));
}

TreeNode* CanonicalTreeNode::intern() {
    auto hash = std::hash<TreeNode*>{}(this);
    TreeNode* canon = TreeHashMap::get(hash);
    if(canon != nullptr){
        return canon;
    }
    TreeHashMap::add(hash,this);
    return this;
}