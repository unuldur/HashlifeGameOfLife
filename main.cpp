#include <iostream>
#include "src/TreeUniverse.h"

using namespace std;

void afficheRoot(TreeUniverse* tree)
{
    int nbCase = 1;
    for (int j = 0; j < tree->getLevel(); ++j) {
        nbCase *= 2;
    }

    for (int i =  0 - nbCase/2; i < nbCase/2; ++i) {
        for (int j = 0 - nbCase/2; j < nbCase/2; ++j) {
            cout << tree->getByte(i,j) << " ";
        }
        cout << endl;
    }
    cout << endl;
}


int main() {
    TreeUniverse* universe = new TreeUniverse;
    universe->setByte(-1,-1);
    universe->setByte(0,0);
    universe->setByte(1,0);
    universe->setByte(-1,1);
    universe->setByte(0,1);
    afficheRoot(universe);
    universe->runStep();
    afficheRoot(universe);
    universe->runStep();
    afficheRoot(universe);
    return 0;
}



