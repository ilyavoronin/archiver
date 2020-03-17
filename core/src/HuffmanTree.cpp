#include "HuffmanTree.h"

#include <set>

HuffmanTree::HuffmanTree(const String<mchar> &data) {
    root_ = buildTree(data);
}

HuffmanTree::HuffmanTree() {
    root_ = nullptr;
}

void HuffmanTree::deleteTree(Node *vert) {
    if (vert == nullptr) {
        return;
    }
    deleteTree(vert->left);
    deleteTree(vert->right);
    delete vert;
}

HuffmanTree::~HuffmanTree() {
    deleteTree(root_);
}

void HuffmanTree::writeTree(DataInfo &data_info) {
    String <mchar> chars;
    String <bool> euler;
    getEulerDfs(root_, chars, euler);
    data_info.write(euler);
    data_info.write(chars);
}

void HuffmanTree::readTree(DataInfo &data_info) {
    String <mchar> chars;
    String <bool> euler;

    //correspond to values that `getEulerDfs` returns
    data_info.read(euler);
    data_info.read(chars);

    Node *new_root = new Node;
    Node *cur = new_root;
    int curSymb = 0;
    int pos = 0;
    while (pos < euler.size() && cur != nullptr) {
        if (pos == 0 || (euler[pos] == 1 && euler[pos - 1] == 1)) {
            Node *new_node = new Node;
            new_node->pr = cur;
            cur->left = new_node;
            cur = new_node;
            pos++;
            continue;
        }
        if (euler[pos] == 1 && euler[pos - 1] == 0) {
            Node *new_node = new Node;
            new_node->pr = cur;
            cur->right = new_node;
            cur = new_node;
        }
        if (euler[pos] == 0) {
            if (euler[pos - 1] == 1) {
                cur->symb = chars[curSymb++];
                cur->is_leaf = true;
            }
            cur = cur->pr;
        }
        pos++;
    }
    this->root_ = new_root;
}

std::map<mchar, String<bool> > HuffmanTree::getCodes() {
    std::map <mchar, String<bool> > res;
    getCodesDfs(root_, String<bool>(), res);
    return res;
}

mchar HuffmanTree::getNextmchar(String<bool> &data, int &pos) {
    Node *cur = root_;
    while (true) {
        if (cur->is_leaf) {
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

HuffmanTree::Node::Node(mchar symb_, Node *left_, Node *right_) {
    is_leaf = false;
    left = left_;
    right = right_;
    symb = symb_;
    pr = nullptr;
}

HuffmanTree::Node* HuffmanTree::buildTree(const String <mchar> &data) {
    std::map <mchar, int> freqs;
    for (int i = 0; i < (int)data.size(); i++) {
        freqs[data[i]]++;
    }
    if (freqs.size() == 1) {
        //if data consists of only one symbol
        Node *root = new Node;
        Node *one_leaf = new Node(data[0]);
        Node *empty_leaf = new Node(0);
        one_leaf->is_leaf = true;
        empty_leaf->is_leaf = true;
        one_leaf->pr = root;
        empty_leaf->pr = root;
        root->left = one_leaf;
        root->right = empty_leaf;
        return root;
    }
    std::set <std::pair <int, Node*> > sorted_freqs;
    for (auto elem : freqs) {
        Node *new_node = new Node(elem.first);
        new_node->is_leaf = true;
        sorted_freqs.insert({elem.second, new_node});
    }
    while (sorted_freqs.size() > 1) {
        auto freq1 = *(sorted_freqs.begin());
        sorted_freqs.erase(sorted_freqs.begin());
        auto freq2 = *(sorted_freqs.begin());
        sorted_freqs.erase(sorted_freqs.begin());
        sorted_freqs.insert({freq1.first + freq2.first, new Node(0, freq1.second, freq2.second)});
    }
    return (*(sorted_freqs.begin())).second;
}

void HuffmanTree::getCodesDfs(HuffmanTree::Node *cur_vert, String<bool> cur_str,
                              std::map<mchar, String<bool> > &res) {
    if (cur_vert->is_leaf) {
        res[cur_vert->symb] = cur_str;
        return;
    }
    if (cur_vert->left != nullptr) {
        getCodesDfs(cur_vert->left, cur_str + bool(0), res);
    }
    if (cur_vert->right != nullptr) {
        getCodesDfs(cur_vert->right, cur_str + bool(1), res);
    }
}

void HuffmanTree::getEulerDfs(HuffmanTree::Node *cur_vert, String <mchar> &chars, String <bool> &euler) {
    if (cur_vert->is_leaf) {
        chars.add(cur_vert->symb);
    }
    else {
        euler.add(1);
        getEulerDfs(cur_vert->left, chars, euler);
        euler.add(1);
        getEulerDfs(cur_vert->right, chars, euler);
    }
    euler.add(0);
}