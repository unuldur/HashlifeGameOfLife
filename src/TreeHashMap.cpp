//
// Created by julie on 20/12/2016.
//


#include "TreeHashMap.h"

map<int,TreeNode*> TreeHashMap::hash;

void TreeHashMap::add(int key, TreeNode* value) {
    hash[key] = value;
}

TreeNode* TreeHashMap::get(int key) {
    std::map<int,TreeNode*>::iterator it = hash.find(key);
    if(it == hash.end()){
        return nullptr;
    }
    return it->second;
}