#include "HuffmanCoding.h"

#include <set>

HuffmanCoding::Node::Node(Symbol symb_, Node *left_, Node *right_) {
    isLeaf = false;
    left = left_;
    right = right_;
    symb = symb_;
    num = 0;
    pr = nullptr;
}

HuffmanCoding::Node* HuffmanCoding::buildTree(const String <Symbol> &data) {
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

void HuffmanCoding::getCodesDfs(HuffmanCoding::Node *curVert, String<bool> curStr,
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

void HuffmanCoding::getEulerDfs(Node *curVert, String <Symbol> &chars, String <bool> &euler) {
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

void HuffmanCoding::writeTree(Node *root, DataInfo &dataInfo) {
    String <Symbol> chars;
    String <bool> euler;
    getEulerDfs(root, chars, euler);
    dataInfo.write(euler);
    dataInfo.write(chars);
}

std::map<Symbol, String<bool> > HuffmanCoding::getCodes(HuffmanCoding::Node *root) {
    std::map <Symbol, String<bool> > res;
    getCodesDfs(root, String<bool>(), res);
    return res;
}

HuffmanCoding::Node* HuffmanCoding::readTree(DataInfo &dataInfo) {
    String <Symbol> chars;
    String <bool> euler;
    dataInfo.read(euler);
    dataInfo.read(chars);
    Node *root = new Node;
    Node *cur = root;
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
    return root;
}

void HuffmanCoding::deleteTree(Node *vert) {
    if (vert == nullptr) {
        return;
    }
    deleteTree(vert->left);
    deleteTree(vert->right);
    delete vert;
}

void HuffmanCoding::encode(String<Symbol> &data, DataInfo &dataInfo) {
    Node *root = buildTree(data);
    std::map <Symbol, String<bool> > codesMap = getCodes(root);

    std::vector <String<bool> > codes(ALPH_SIZE);
    for (auto elem : codesMap) {
        codes[(elem.first).get()] = elem.second;    //index is the symbol number
    }
    String <bool> res;
    for (int i = 0; i < data.size(); i++) {
        res += codes[data[i].get()];
    }
    writeTree(root, dataInfo);
    dataInfo.write((int)res.size());
    data = res.toSymb();
    deleteTree(root);
}


void HuffmanCoding::decode(String<Symbol> &data, DataInfo &dataInfo) {
    Node *root = readTree(dataInfo);

    std::map <Symbol, String<bool> > codesMap = getCodes(root);

    std::vector <String<bool> > codes(ALPH_SIZE);
    for (auto elem : codesMap) {
        codes[(elem.first).get()] = elem.second;    //index is the symbol number
    }
    String <bool> binData = data.toBool();
    int dataSize;
    dataInfo.read(dataSize);
    int pos = 0;
    data.clear();
    Node *cur = root;
    while (pos < dataSize) {
        if (cur->isLeaf) {
            data.add(cur->symb);
            cur = root;
        }
        else {
            if (binData[pos] == 0) {
                cur = cur->left;
            }
            else {
                cur = cur->right;
            }
            pos++;
        }
    }
    if (cur->isLeaf) {
        data.add(cur->symb);
    }
    deleteTree(root);
}