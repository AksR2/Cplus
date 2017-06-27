#include <iostream>
#include <string>
#include <fstream>
#include "decodertree.h"

using namespace std;

int main(int argc, char const *argv[]) {

   if ( argc != 3 ){
	cout<<"Usage: "<<argv[0]<<" encoded.bin code_table.txt"<<endl;
	return 0;
    }

    std::ifstream encodedbinf (argv[1],ios::binary | ios::in);
    if ( !encodedbinf.is_open() ){
	  std::cout<<"Could not open file\n";
	  return 0;
    }

    ifstream codetablef(argv[2], ios::in);
    if ( !codetablef.is_open() ){
	  std::cout<<"Could not open file\n";
	  return 0;
    }

    DecoderTree decodertree = DecoderTree();
    int key;
    string val;
    cout << "Building Decode Tree" << endl;
    while (codetablef >> key >> val) {
        decodertree.addLeafAtPath(key, val);
    }

    cout << "Decoding binary file" << endl;
    ofstream onfile ("decoded.txt",std::ios::out);

    char c;
    string resultChunk;
    int value;
    int d;
	
	//TODO: make it more effecient by not re-traversing the decoder tree when a mismatch occurs.
	//This is the reason why my decoder is running slow for now. I'll be making it faster and more efficient.
    while (encodedbinf.get(c)) {
        for (int i = 7; i >= 0; i--) {
            d = (c >> i) & 1;
            resultChunk.append(to_string(d));
            value=decodertree.getValueAtPath(resultChunk);
            if (value != -1) {
                onfile << value << endl;
                resultChunk = "";
            }
        }

    }

    cout<<"Done file name is decoded.txt"<<endl;
    onfile.close();
    encodedbinf.close();
    codetablef.close();
    return 0;
}



