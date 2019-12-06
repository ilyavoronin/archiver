#include "HuffmanCoding.h"

#include "HuffmanTree.h"

void HuffmanCoding::encode(String<Symbol> &data, DataInfo &data_info) {
    HuffmanTree huffman_tree(data);
    std::map <Symbol, String<bool> > codes_map = huffman_tree.getCodes();

    std::vector <String<bool> > codes(kAlphabetSize);
    for (auto elem : codes_map) {
        codes[(elem.first).get()] = elem.second;    //index is the symbol number
    }
    String <bool> res;
    for (int i = 0; i < data.size(); i++) {
        res += codes[data[i].get()];
    }

    huffman_tree.writeTree(data_info);
    data_info.write((int)res.size());
    data = res.toSymb();
}


void HuffmanCoding::decode(String<Symbol> &data, DataInfo &data_info) {
    HuffmanTree huffman_tree;
    huffman_tree.readTree(data_info);

    String <bool> bin_data = data.toBool();
    int bin_data_size;
    data_info.read(bin_data_size);
    int pos = 0;
    data.clear();
    while (pos < bin_data_size) {
        data.add(huffman_tree.getNextSymbol(bin_data, pos));
    }
}