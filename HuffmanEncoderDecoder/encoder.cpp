/*
 * encoder.cpp
 *
 *  Created on: Mar 27, 2017
 *      Author: akshay
 */

#include "bheap.h"
#include "fheap.h"
#include "pheap.h"
#include "hnode.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <cstddef>
#include <ctime>
#include <stack>
#include <string>

void FillFreqMapFromFile(
	std::ifstream &infile,
	std::unordered_map<int,unsigned int> &freq_map){

	int number;
	while(infile >> number){
		auto it_f=freq_map.find(number);
		if(it_f!=freq_map.end()){
			it_f->second++;	
		} else {
			freq_map[number]=1;
		}
	}
}

void CreateHnodeVecFromFreqMap(	
	std::unordered_map<int,unsigned int> const &freq_map,
	std::vector<hnode const*> &hnode_vec){
	
	for(auto it:freq_map){
		hnode* huff_node=new hnode(it.first,it.second,NULL,NULL);
		hnode_vec.push_back(huff_node);	
	}
}

hnode const* BuildTreeFheap(
		std::unordered_map<int,unsigned int> const &freq_map){

	std::vector<hnode const*> hnode_vec;
	CreateHnodeVecFromFreqMap(freq_map,hnode_vec);

	fheap fheap_obj(hnode_vec);

	unsigned int freq;
	//std::cout<<"The 4-way heap"<<std::endl;
	//fheap_obj.displayheap();
	while (fheap_obj.size() > 4)
	{
		//std::cout<<"iteration:"<<std::endl;
		hnode const *left =fheap_obj.getmin();
		fheap_obj.deletemin();
		//fheap_obj.displayheap();

		hnode const *right = fheap_obj.getmin();
		fheap_obj.deletemin();
		//fheap_obj.displayheap();

		freq=left->freq + right->freq;
		//std::cout<<"Result Freq:"<<freq<<std::endl;
		//data to be -1 since it is an internal node...
		hnode const* parent = new hnode(-1,freq, left, right );
		fheap_obj.insert(parent);
		//fheap_obj.displayheap();
	}
	return fheap_obj.getmin();
}

hnode const* BuildTreeBheap(
		std::unordered_map<int,unsigned int> const &freq_map){

	std::vector<hnode const*> hnode_vec;
	CreateHnodeVecFromFreqMap(freq_map,hnode_vec);

	bheap bheap_obj(hnode_vec);

	//bheap_obj.displayheap();
	unsigned int freq;

	int count=0;
	while ((bheap_obj.size() > 1))
	{	count++;
		//std::cout<<"iteration:"<<std::endl;
		hnode const *left =bheap_obj.getmin();
		bheap_obj.deletemin();
		//bheap_obj.displayheap();
		
		hnode const *right = bheap_obj.getmin();
		bheap_obj.deletemin();
		//bheap_obj.displayheap();
		
		freq=left->freq + right->freq;
		//std::cout<<"Result Freq:"<<freq<<std::endl;
		//data to be -1 since it is an internal node...
		hnode const* parent = new hnode(-1,freq, left, right );
		bheap_obj.insert(parent);
		//bheap_obj.displayheap();
	}
	return bheap_obj.getmin();
}


hnode const* BuildTreePheap(
		std::unordered_map<int,unsigned int> const &freq_map){

	std::vector<hnode const*> hnode_vec;
	CreateHnodeVecFromFreqMap(freq_map,hnode_vec);

	pheap pheap_obj(hnode_vec);

	unsigned int freq;

	while ((pheap_obj.size() > 1))
	{
		hnode const *left =pheap_obj.findMin();
		pheap_obj.deleteMin();
		hnode const *right = pheap_obj.findMin();
		pheap_obj.deleteMin();

		freq=left->freq + right->freq;
		//std::cout<<"Result Freq:"<<freq<<std::endl;
		//data to be -1 since it is an internal node...
		hnode const* parent = new hnode(-1,freq, left, right );
		pheap_obj.Insert(parent);
	}
	return pheap_obj.findMin();
}

// Prints huffman codes from the root of Huffman Tree.
void printCodes(
		hnode const *root,
		std::string str,
		std::unordered_map<int,std::string> &code_table_map
		)
{

    if (!root)
        return;

    if (root->data != -1){
    	code_table_map[root->data]=str;
    }

    printCodes(root->left, str + "0",code_table_map);
    printCodes(root->right, str + "1",code_table_map);
}


char setBit(char num, int i){
	return num|(1<<i);
}

void compress(std::string &value,std::vector<char> &result){

	char res=0;
	char str;
	for(long i=0;i<value.size();){
		res=0;
		for(int j=7;j>=0;j--){
			if(value[i]=='1')
				res=setBit(res,j);
			i++;
		}
		result.push_back(res);
	}
}

void binfilecreate(
		std::unordered_map<int,std::string> &code_table_map,
		char *filename,
		char const *out
		){

	std::ifstream infile (filename);
	std::ofstream onfile (out,std::ios::out | std::ios::binary);

	int number;
	std::string value;
	while(infile >> number){
		auto it_f=code_table_map.find(number);
		if(it_f!=code_table_map.end()){
			value+=it_f->second;

		} else {
			std::cout<<"-----------This cannot happen : "<<(it_f->first)<<std::endl;
		}
	}
	std::vector<char> result;
	compress(value,result);
	char *res=&result[0];
	onfile.write(res,result.size());
	onfile.close();
	infile.close();

}


int main(int argc, char *argv[]){


	//TODO: will Create interface for the heap so that the underlying heap is abstracted away.
	// It also will reduce code replication. eliminate the three different build tree functions into one.

	if ( argc != 2 ){
		std::cout<<"Usage: "<<argv[0]<<" <input_file_name>\n";
		return 0;
	}

	std::ifstream infile (argv[1]);
	if ( !infile.is_open() ){
	  std::cout<<"Could not open file\n";
	  return 0;
	}
	//create the frequency map used by the program...

	std::unordered_map<int,unsigned int> freq_map;

	
	FillFreqMapFromFile(infile,freq_map);

	infile.close();
	clock_t start_time;

//	std::cout<<"Huffman binary heap:"<<std::endl;
//	start_time=clock();
//	for(int i=0;i<10;i++)
//		hnode const* rootb=BuildTreeBheap(freq_map);
//
//	std::unordered_map<int,std::string> code_table_map1;
//	printCodes(rootb,"",code_table_map1);
//	std::cout << "Time using binary heap (microsecond):  " << (clock() - start_time)/10 << std::endl;

	std::string of;
	std::cout<<"Huffman 4way heap:"<<std::endl;
	start_time=clock();
	//for(int i=0;i<10;i++)
		hnode const* rootf=BuildTreeFheap(freq_map);

	std::unordered_map<int,std::string> code_table_map2;
	printCodes(rootf,"",code_table_map2);
	of="encoded.bin";
	char const *o2=of.c_str();
	binfilecreate(code_table_map2,argv[1],o2);
	std::string code_table_file_name="code_table.txt";
	std::ofstream onfile (code_table_file_name,std::ios::out);
	for(auto it:code_table_map2){
		onfile<<it.first<<" "<<it.second<<"\n";
	}
	std::cout << "Time using 4-way heap (microsecond):  " << (clock() - start_time)/10 << std::endl;


//	std::cout<<"Encode table:"<<std::endl;
//	std::string code_table_file_name="code_table.txt";
//	std::ofstream onfile (code_table_file_name,std::ios::out);
//	for(auto it:code_table_map2){
//		onfile<<it.first<<" "<<it.second<<"\n";
//	}
//
//	onfile.close();

//	std::cout<<"Huffman pairing heap:"<<std::endl;
//	start_time=clock();
//	for(int i=0;i<10;i++)
//		hnode const* rootp=BuildTreePheap(freq_map);
//
//	std::unordered_map<int,std::string> code_table_map3;
//	printCodes(rootp,"",code_table_map3);
//	std::cout << "Time using pairing heap (microsecond):  " << (clock() - start_time)/10 << std::endl;
//
//	std::cout<<"Encode table:"<<std::endl;
//	std::string code_table_file_name="code_table.txt";
//	std::ofstream onfile (code_table_file_name,std::ios::out);
//	for(auto it:code_table_map3){
//		onfile<<it.first<<" "<<it.second<<"\n";
//	}
//	onfile.close();

	return 0;
}

