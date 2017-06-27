#include <iostream>
#include <string>
#include "decodertree.h"

using namespace std;

void DecoderTree::addLeafAtPath(int value, string binarypath) {
    decnode *current;
    current = root;
    for (int i = 0; i < binarypath.length(); i++) {
        if (binarypath.at(i) == '0') {
            if (current->left == NULL) {
                decnode* newNode = new decnode();
                current->left = newNode;
            }
            current = current->left;
        }
        else if (binarypath.at(i) == '1') {
            if (current->right == NULL) {
                decnode* newNode = new decnode();
                current->right = newNode;
            }
            current = current->right;
        }
    }
    current->value = value;
    current->isLeaf = true;
}

int DecoderTree::getValueAtPath(string binarypath) {
    decnode *curr;
    curr = root;

    for (int i = 0; i < binarypath.length(); i++) {
		if (curr == NULL) {
			return -1;
		}
		else if (binarypath.at(i) == '0') {
			curr = curr->left;
		}
		else if (binarypath.at(i) == '1') {
			curr = curr->right;
		}
    }

    if (curr->isLeaf == true) {
        return curr->value;
    }
    else {
        return -1;
    }
}

decnode* DecoderTree::getRoot() {
    return root;
}



