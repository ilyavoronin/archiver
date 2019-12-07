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

    //This method is for decoding
    //We have binary data and want to decode it with tree
    //`pos` -- is the position from which code for the next symbol begins
    //At the and of the function `pos` will point to the beginning of the next symbol code
    Symbol getNextSymbol(String <bool> &data, int &pos);

  private:
    struct Node {
        Node(Symbol symb_ = 0, Node* left_ = nullptr, Node* right_ = nullptr);

        bool is_leaf;
        Symbol symb;
        Node *left, *right;
        Node* pr; //previous vertex
    };

    Node* buildTree(const String <Symbol> &data);

    //`cur_str` is a bit string from root of the tree to the `cur_vert`
    //res[s] = bit string that corresponds to s in the tree
    void getCodesDfs(Node *cur_vert, String<bool> cur_str, std::map <Symbol, String<bool> > &res);

    //This method is building an euler path of the tree:
    //every time it goes down it writes 1 to the `euler`
    //and 0 when goes up
    //`symb` is the list of symbols in the leaves in the order of euler bypass
    void getEulerDfs(Node *cur_vert, String <Symbol> &symb, String <bool> &euler);

    //This method is called from the destructor
    //Recursively deletes tree nodes in the subtree of `vert`
    void deleteTree(Node *vert);

    Node *root_;
};


#endif //ARCHIVER_HUFFMANTREE_H
