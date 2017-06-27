/*
 * FourHeap.h
 *
 *  Created on: Mar 27, 2017
 *      Author: arawat
 */

#ifndef FHEAP_H
#define FHEAP_H_

#include "hnode.h"
#include <vector>

class fheap{

	std::vector<hnode const*> 			_heap;

	void 								percolateup(int i);
	void 								percolatedown(int i);
	int 								smallestChild(int i);
	int 								kthChild(int i, int k);
	int 								parent(int i);

public:

										fheap();
										~fheap();
										fheap(std::vector<hnode const *> &numbers);
	void 								insert(hnode const* ele);
	hnode const* 						getmin();
	void 								deletemin();
	//void								heapify(vector<int> &a);
	size_t 								size();
	void								displayheap();
		
};
#endif /*FHEAP_H_*/