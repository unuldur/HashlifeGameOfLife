
#include <iostream>
#include "src/TreeUniverse.h"

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
    universe->setByte(-1,-1,true);
    universe->setByte(0,0,true);
    universe->setByte(1,0,true);
    universe->setByte(-1,1,true);
    universe->setByte(0,1,true);
    TreeNode* root = universe->getRoot();
    afficheRoot(universe->getRoot());

    //cout << root->getThis() << endl;
    universe->runStep();
    afficheRoot(universe->getRoot());
    cout << universe->getRoot()->getDifference(root,0,0);


    return 0;
}



