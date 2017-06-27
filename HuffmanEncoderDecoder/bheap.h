/*
 * bheap.h
 *
 *  Created on: Mar 27, 2017
 *      Author: arawat
 */

#ifndef BHEAP_H_
#define BHEAP_H_

#include "hnode.h"
#include <vector>

class bheap{

	std::vector<hnode const*> 			_heap;

	void 								percolateup(int i);
	void 								percolatedown(int i);
	int 								lchild(int i);
	int 								rchild(int i);
	int 								parent(int i);

public:
									
										bheap();
										~bheap();
										bheap(std::vector<hnode const *> &numbers);
	void 								insert(hnode const* ele);
	hnode const* 						getmin();
	void 								deletemin();
	//void								heapify(vector<int> &a);
	int 								size();
	void								displayheap();

};

#endif /* BHEAP_H_ */
