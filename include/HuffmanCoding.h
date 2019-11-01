#ifndef ARCHIVER_HUFFMANCODING_H
#define ARCHIVER_HUFFMANCODING_H

#include "Symbol.h"
#include "String.h"
#include "DataInfo.h"

#include <vector>
#include <map>

class HuffmanCoding {
private:
    const int ALPH_SIZE = 256;
    class Node {
    public:
        inline static int curNum = 0;
        bool isLeaf;
        Symbol symb;
        int num;
        Node *left, *right;
        Node* pr; //previous vertex
        Node(Symbol symb_ = 0, Node* left = nullptr, Node* right = nullptr);
    };
    Node* buildTree(String <Symbol> &data);
    std::map <Symbol, String<bool> > getCodes(Node *root);
    void getCodesDfs(Node *curVert, String<bool> curStr, std::map <Symbol, String<bool> > &res);
    void getByteString(String <bool> &bstr, String <Symbol> &res);
    void getNodesDfs(Node *curVert, std::vector<Node *> &nodes, Node *pr);  //get nodes vector and find prevs
    void writeTree(Node *root, DataInfo &dataInfo);
public:
    void encode(String <Symbol> &data, DataInfo &dataInfo);   //overwriting data
    void decode(String <Symbol> &data);   //overwriting data
};


#endif //ARCHIVER_HUFFMANCODING_H
