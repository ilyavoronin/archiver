#ifndef ARCHIVER_HUFFMANTREE_H
#define ARCHIVER_HUFFMANTREE_H

#include "AString.h"
#include "Symbol.h"
#include "DataInfo.h"

#include <map>


class HuffmanTree {
private:
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

    Node *root;

    Node* buildTree(const String <Symbol> &data);
    void getCodesDfs(Node *curVert, String<bool> curStr, std::map <Symbol, String<bool> > &res);
    void getEulerDfs(Node *curVert, String <Symbol> &symb, String <bool> &euler);
    void deleteTree(Node *vert);
public:
    explicit HuffmanTree(const String <Symbol> &data);
    HuffmanTree();
    ~HuffmanTree();
    std::map <Symbol, String<bool> > getCodes();
    void writeTree(DataInfo &dataInfo);
    void readTree(DataInfo &dataInfo);
    Symbol getNextSymbol(String <bool> &data, int &pos);
};


#endif //ARCHIVER_HUFFMANTREE_H
