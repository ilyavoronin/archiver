#ifndef ARCHIVER_HUFFMANTREE_H
#define ARCHIVER_HUFFMANTREE_H

#include <map>

#include "AString.h"
#include "Symbol.h"
#include "DataInfo.h"

class HuffmanTree {
  public:
    explicit HuffmanTree(const String <Symbol> &data);
    HuffmanTree();

    ~HuffmanTree();

    void writeTree(DataInfo &data_info);
    void readTree(DataInfo &data_info);
    std::map <Symbol, String<bool> > getCodes();
    Symbol getNextSymbol(String <bool> &data, int &pos);

  private:
    struct Node {
        inline static int curNum = 0;

        Node(Symbol symb_ = 0, Node* left_ = nullptr, Node* right_ = nullptr);

        bool is_leaf;
        Symbol symb;
        Node *left, *right;
        Node* pr; //previous vertex
    };

    Node* buildTree(const String <Symbol> &data);
    void getCodesDfs(Node *cur_vert, String<bool> cur_str, std::map <Symbol, String<bool> > &res);
    void getEulerDfs(Node *cur_vert, String <Symbol> &symb, String <bool> &euler);
    void deleteTree(Node *vert);

    Node *root_;
};


#endif //ARCHIVER_HUFFMANTREE_H
