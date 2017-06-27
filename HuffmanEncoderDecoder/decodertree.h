#include <iostream>
#include <string>
#include "decnode.h"
using namespace std;

class DecoderTree {
private:
    decnode* root;
public:
    decnode* getRoot();
    void addLeafAtPath(int value, string binarypath);
    int getValueAtPath(string binarypath);

    DecoderTree() {
        root = new decnode();
    }
};



