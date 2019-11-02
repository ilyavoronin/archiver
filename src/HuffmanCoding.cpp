#include "HuffmanCoding.h"

#include <set>

HuffmanCoding::Node::Node(Symbol symb_, Node *left_, Node *right_) {
    isLeaf = false;
    left = left_;
    right = right_;
    symb = symb_;
    num = 0;
    pr = 0;
}

HuffmanCoding::Node* HuffmanCoding::buildTree(String <Symbol> &data) {
    std::map <Symbol, int> freqs;
    for (int i = 0; i < (int)data.size(); i++) {
        freqs[data[i]]++;
    }
    std::set <std::pair <int, Node*> > sortedFreqs;
    for (auto elem : freqs) {
        Node *newNode = new Node(elem.first);
        newNode->isLeaf = true;
        sortedFreqs.insert({-elem.second, newNode});    //sorting in descending order
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

void HuffmanCoding::getByteString(String<bool> &bstr, String<Symbol> &res) {
    for (int i = 0; i < bstr.size(); i += 8) {
        uint8_t c = 0;
        while (bstr.size() % 8 != 0) {
            bstr.add(0);
        }
        for (int j = 0; j < 8; j++) {
            if (bstr[j] == 1) {
                c |= (1 << j);
            }
        }
        res += Symbol(c);
    }
}

void HuffmanCoding::getNodesDfs(Node *curVert, std::vector<Node *> &nodes, Node *pr) {
    if (curVert == nullptr) {
        return;
    }
    curVert->pr = pr;
    nodes.push_back(curVert);
    getNodesDfs(curVert->left, nodes, curVert);
    getNodesDfs(curVert->right, nodes, curVert);
}

void HuffmanCoding::writeTree(Node *root, DataInfo &dataInfo) {
    std::vector <Node* > nodes;   //List of nodes
    getNodesDfs(root, nodes, 0);
    std::vector <Node* > leafNodes;
    std::vector <Node* > addNodes;
    for (auto node : nodes) {
        if (node->isLeaf) {
            leafNodes.push_back(node);
        }
        else {
            addNodes.push_back(node);
        }
    }
    for (auto node : addNodes) {
        node->num = Node::curNum++;
    }
    for (auto node : leafNodes) {
        node->num = Node::curNum++;
    }
    dataInfo.write(int(leafNodes.size()));
    for (auto node : addNodes) {
        if (node->pr != nullptr) {
            dataInfo.write(short(node->pr->num));
        }
        else {
            dataInfo.write(short(0));
        }
    }
    for (auto node : leafNodes) {
        dataInfo.write(short(node->pr->num));
        dataInfo.write(node->symb);
    }
}

std::map<Symbol, String<bool> > HuffmanCoding::getCodes(HuffmanCoding::Node *root) {
    std::map <Symbol, String<bool> > res;
    getCodesDfs(root, String<bool>(), res);
    return res;
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
    data.clear();
    getByteString(res, data);
    writeTree(root, dataInfo);
}

void HuffmanCoding::decode(String<Symbol> &data, DataInfo &dataInfo) {

}