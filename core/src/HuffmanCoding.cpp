#include "HuffmanCoding.h"

#include "HuffmanTree.h"

void HuffmanCoding::encode(String<mchar> &data, DataInfo &data_info) {
    data_info.write((int)data.size());
    if (data.size() == 0) {
        return;
    }
    HuffmanTree huffman_tree(data);
    std::map <mchar, String<bool> > codes_map = huffman_tree.getCodes();

    //map is replaces with vector in order to get string for symbol faster
    //codes[i] -- string that corresponds to mchar(i)
    std::vector <String<bool> > codes(kAlphabetSize);
    for (auto elem : codes_map) {
        codes[(elem.first)] = elem.second;    //index is the symbol number
    }
    String <bool> res;
    for (int i = 0; i < data.size(); i++) {
        res += codes[data[i]];
    }

    huffman_tree.writeTree(data_info);
    data_info.write((int)res.size());
    data = res.toSymb();
}


void HuffmanCoding::decode(String<mchar> &data, DataInfo &data_info) {
    int data_size;
    data_info.read(data_size);
    if (data_size == 0) {
        return;
    }
    HuffmanTree huffman_tree;
    huffman_tree.readTree(data_info);

    String <bool> bin_data = data.toBool();
    int bin_data_size;
    data_info.read(bin_data_size);
    int pos = 0;
    data.clear();
    while (pos < bin_data_size) {
        data.add(huffman_tree.getNextmchar(bin_data, pos));
    }
}