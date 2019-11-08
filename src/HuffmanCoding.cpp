#include "HuffmanCoding.h"
#include "HuffmanTree.h"
void HuffmanCoding::encode(String<Symbol> &data, DataInfo &dataInfo) {
    HuffmanTree huffmanTree(data);
    std::map <Symbol, String<bool> > codesMap = huffmanTree.getCodes();

    std::vector <String<bool> > codes(ALPH_SIZE);
    for (auto elem : codesMap) {
        codes[(elem.first).get()] = elem.second;    //index is the symbol number
    }
    String <bool> res;
    for (int i = 0; i < data.size(); i++) {
        res += codes[data[i].get()];
    }
    huffmanTree.writeTree(dataInfo);
    dataInfo.write((int)res.size());
    data = res.toSymb();
}


void HuffmanCoding::decode(String<Symbol> &data, DataInfo &dataInfo) {
    HuffmanTree huffmanTree;
    huffmanTree.readTree(dataInfo);

    std::map <Symbol, String<bool> > codesMap = huffmanTree.getCodes();

    String <bool> binData = data.toBool();
    int dataSize;
    dataInfo.read(dataSize);
    int pos = 0;
    data.clear();
    while (pos < dataSize) {
        data.add(huffmanTree.getNextSymbol(binData, pos));
    }
}