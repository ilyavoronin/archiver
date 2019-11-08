#include "HuffmanTree.h"

#include <set>

HuffmanTree::Node::Node(Symbol symb_, Node *left_, Node *right_) {
    isLeaf = false;
    left = left_;
    right = right_;
    symb = symb_;
    num = 0;
    pr = nullptr;
}

HuffmanTree::HuffmanTree(const String<Symbol> &data) {
    root = buildTree(data);
}

HuffmanTree::HuffmanTree() {
    root = nullptr;
}

HuffmanTree::~HuffmanTree() {
    deleteTree(root);
}

HuffmanTree::Node* HuffmanTree::buildTree(const String <Symbol> &data) {
    std::map <Symbol, int> freqs;
    for (int i = 0; i < (int)data.size(); i++) {
        freqs[data[i]]++;
    }
    std::set <std::pair <int, Node*> > sortedFreqs;
    for (auto elem : freqs) {
        Node *newNode = new Node(elem.first);
        newNode->isLeaf = true;
        sortedFreqs.insert({elem.second, newNode});
    }
    while (sortedFreqs.size() > 1) {
        auto freq1 = *(sortedFreqs.begin());
        sortedFreqs.erase(sortedFreqs.begin());
        auto freq2 = *(sortedFreqs.begin());
        sortedFreqs.erase(sortedFreqs.begin());
        Node *newNode = new Node();
        sortedFreqs.insert({freq1.first + freq2.first, new Node(0, freq1.second, freq2.second)});
    }
    return (*(sortedFreqs.begin())).second;
}

void HuffmanTree::getCodesDfs(HuffmanTree::Node *curVert, String<bool> curStr,
                                std::map<Symbol, String<bool> > &res) {
    if (curVert->isLeaf) {
        res[curVert->symb] = curStr;
        return;
    }
    if (curVert->left != nullptr) {
        getCodesDfs(curVert->left, curStr + bool(0), res);
    }
    if (curVert->right != nullptr) {
        getCodesDfs(curVert->right, curStr + bool(1), res);
    }
}

void HuffmanTree::getEulerDfs(HuffmanTree::Node *curVert, String <Symbol> &chars, String <bool> &euler) {
    if (curVert->isLeaf) {
        chars.add(curVert->symb);
    }
    else {
        euler.add(1);
        getEulerDfs(curVert->left, chars, euler);
        euler.add(1);
        getEulerDfs(curVert->right, chars, euler);
    }
    euler.add(0);
}

void HuffmanTree::writeTree(DataInfo &dataInfo) {
    String <Symbol> chars;
    String <bool> euler;
    getEulerDfs(root, chars, euler);
    dataInfo.write(euler);
    dataInfo.write(chars);
}

std::map<Symbol, String<bool> > HuffmanTree::getCodes() {
    std::map <Symbol, String<bool> > res;
    getCodesDfs(root, String<bool>(), res);
    return res;
}

void HuffmanTree::readTree(DataInfo &dataInfo) {
    String <Symbol> chars;
    String <bool> euler;
    dataInfo.read(euler);
    dataInfo.read(chars);
    Node *newRoot = new Node;
    Node *cur = newRoot;
    int curSymb = 0;
    int pos = 0;
    while (pos < euler.size() && cur != nullptr) {
        if (pos == 0 || euler[pos] == 1 && euler[pos - 1] == 1) {
            Node *newNode = new Node;
            newNode->pr = cur;
            cur->left = newNode;
            cur = newNode;
            pos++;
            continue;
        }
        if (euler[pos] == 1 && euler[pos - 1] == 0) {
            Node *newNode = new Node;
            newNode->pr = cur;
            cur->right = newNode;
            cur = newNode;
        }
        if (euler[pos] == 0) {
            if (euler[pos - 1] == 1) {
                cur->symb = chars[curSymb++];
                cur->isLeaf = true;
            }
            cur = cur->pr;
        }
        pos++;
    }
    this->root = newRoot;
}

void HuffmanTree::deleteTree(Node *vert) {
    if (vert == nullptr) {
        return;
    }
    deleteTree(vert->left);
    deleteTree(vert->right);
    delete vert;
}

Symbol HuffmanTree::getNextSymbol(String<bool> &data, int &pos) {
    Node *cur = root;
    while (true) {
        if (cur->isLeaf) {
            return cur->symb;
        }
        else {
            if (data[pos] == 0) {
                cur = cur->left;
            }
            else {
                cur = cur->right;
            }
            pos++;
        }
    }
}