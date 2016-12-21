//
// Created by julie on 20/12/2016.
//

#ifndef GAMEOFLIFE_TREEHASHMAP_H
#define GAMEOFLIFE_TREEHASHMAP_H

#include "TreeNode.h"
#include <iostream>
#include <map>

using namespace std;
class TreeHashMap {
public:
    static void add(int key, TreeNode* value);
    static TreeNode* get(int key);
private:
    static  map<int,TreeNode*> hash;
};


#endif //GAMEOFLIFE_TREEHASHMAP_H
