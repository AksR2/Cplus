# Huffman Encoder and Decoder in C++

This project demonstrates my love for C++. I've implemented this project as part of my advance data structures course work.

* The code has an encoder.cpp and a decoder.cpp which are the two main files for this project.
* The encoder (using huffman encoding scheme) encodes a list of numbers to achieve comperessions.
* The decoder then uses the encoder table and the encoded.bin file to decompress to restore the original contents.

## TODO
* Make decoder efficient
* Create a common interface for the create tree code. This way different trees can implement the common functions based on their functionality. Thus decluttering the code I had intially written.
