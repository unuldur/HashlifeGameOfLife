
#include <iostream>
#include "src/TreeUniverse.h"
#include "src/TreeHashMap.h"

using namespace std;


void afficheRoot(TreeNode* tree)
{
    int nbCase = 1;
    for (int j = 0; j < tree->getLevel(); ++j) {
        nbCase *= 2;
    }
    for (int i =  0 - nbCase/2; i < nbCase/2; ++i) {
        for (int j = 0 - nbCase/2; j < nbCase/2; ++j) {
            cout << tree->getByte(i,j);
        }
        cout << endl;
    }
    cout << endl;
}


int main() {
    TreeUniverse* universe = new TreeUniverse;
    universe->setByte(1,1,true);
    universe->setByte(2,1,true);
    universe->setByte(3,1,true);
    universe->setByte(1,2,true);
    universe->setByte(2,3,true);
    TreeNode* root = universe->getRoot();
    afficheRoot(universe->getRoot());
    universe->runStep();
    afficheRoot(universe->getRoot());
    cout << root->getDifference(universe->getRoot(),0,0) <<endl;



    return 0;
}



