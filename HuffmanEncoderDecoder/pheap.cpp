/*
 * pairheap.cpp
 *
 *  Created on: Mar 28, 2017
 *      Author: akshay
 */

#include "hnode.h"
#include "pheap.h"
#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;


pheap::pheap()
{
	_heapsize=0;
    root = NULL;
}

pheap::pheap(vector<hnode const*> &numbers){
	root=NULL;
	_heapsize=0;
	for(auto ele:numbers){
		Insert(ele);
	}
}


pheap::~pheap()
{
}

pnode *pheap::Insert(hnode const* x)
{
   pnode *newNode = new pnode(x);
    if (root == NULL){
        root = newNode;
    }else{
        meldhelper(root, newNode);
    }
    ++_heapsize;
    return newNode;
}

hnode const* pheap::findMin()
{
    return root->huff_node;
}

void pheap::deleteMin()
{
    pnode *oldRoot = root;
    if (root->leftChild == NULL)
        root = NULL;
    else
        root = meldSib(root->leftChild);
    --_heapsize;
    delete oldRoot;
}

void pheap::meldhelper(pnode * &first, pnode *second)
{
    if (second == NULL)
    {
    	return;
    }
    if (*(second->huff_node) < *(first->huff_node))
    {
        second->prev = first->prev;
        first->prev = second;
        first->nextSibling = second->leftChild;
        if (first->nextSibling != NULL)
            first->nextSibling->prev = first;
        second->leftChild = first;
        first = second;
    }
    else
    {
        second->prev = first;
        first->nextSibling = second->nextSibling;
        if (first->nextSibling != NULL)
            first->nextSibling->prev = first;
        second->nextSibling = first->leftChild;
        if (second->nextSibling != NULL)
            second->nextSibling->prev = second;
        first->leftChild = second;
    }
}

pnode *pheap::meldSib(pnode *firstSibling)
{
    if (firstSibling->nextSibling == NULL)
        return firstSibling;
    static vector<pnode *> treeArray(5);
    int numSiblings = 0;
    for (; firstSibling != NULL; numSiblings++){
        if (numSiblings == treeArray.size())
            treeArray.resize(numSiblings * 2);
        treeArray[numSiblings] = firstSibling;
        firstSibling->prev->nextSibling = NULL;
        firstSibling = firstSibling->nextSibling;
    }
    if (numSiblings == treeArray.size())
        treeArray.resize(numSiblings + 1);
    treeArray[numSiblings] = NULL;
    int i = 0;
    for (; i + 1 < numSiblings; i += 2)
        meldhelper(treeArray[i], treeArray[i + 1]);
    int j = i - 2;
    if (j == numSiblings - 3)
        meldhelper (treeArray[j], treeArray[j + 2]);
    for (; j >= 2; j -= 2)
        meldhelper(treeArray[j - 2], treeArray[j] );
    return treeArray[0];
}


long pheap::size(){
	return _heapsize;
}

