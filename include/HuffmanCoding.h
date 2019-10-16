#ifndef ARCHIVER_HUFFMANCODING_H
#define ARCHIVER_HUFFMANCODING_H

#include "Symbol.h"

#include <vector>

class HuffmanCoding {
private:
    class Tree {
    private:
        class Node {
        public:
            bool isLeaf;
            Symbol symb;
            Node *left, *right;
            Node();
        };

        Node *root;
        Tree();
    };

    Tree buildTree(std::vector <Symbol> &data);
public:
    void enocde(std::vector <Symbol> &data);
    void decode(std::vector <Symbol> &data);
};


#endif //ARCHIVER_HUFFMANCODING_H
