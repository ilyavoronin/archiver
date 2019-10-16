#include "HuffmanCoding.h"

HuffmanCoding::Tree::Node::Node() {
    isLeaf = false;
    left = nullptr;
    right = nullptr;
}

HuffmanCoding::Tree::Tree() {
    root = new Node;
}

HuffmanCoding::Tree HuffmanCoding::buildTree(std::vector<Symbol> &data) {

}

void HuffmanCoding::enocde(std::vector<Symbol> &data) {

}