#ifndef DECNODE_H_
#define DECNODE_H_

#include<cstddef>

struct decnode {

    decnode *left;
    decnode *right;
    int value;
    bool isLeaf;
    decnode():
    	left(NULL),
		right(NULL),
		isLeaf(false),
    	value(-1)
    {
    }
};



#endif /* DECNODE_H_ */
