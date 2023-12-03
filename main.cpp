#include <iostream>
#include <queue>
#include <map>

using namespace std;

struct node {
    char symbol;
    int frequency;
    node *left;
    node *right;

    bool operator<(const node &other) const {
        return frequency < other.frequency;
    }
};

void printHuffmanCodes(const map<char, string> &huffmanCodes) {
    for (const pair<char, string> &entry : huffmanCodes) {
        cout << entry.first << ": " << entry.second << endl;
    }
}

void generateHuffmanCodes(const map<char, int> &charFreqMap) {
    priority_queue<node> pq;

    for (const pair<char, int> &entry : charFreqMap) {
        node *n = new node;
        n->symbol = entry.first;
        n->frequency = entry.second;
        n->left = nullptr;
        n->right = nullptr;

        pq.push(*n);
    }

    while (pq.size() > 1) {
        node *left = new node;
        *left = pq.top();
        pq.pop();

        node *right = new node;
        *right = pq.top();
        pq.pop();

        node *parent = new node;
        parent->frequency = left->frequency + right->frequency;
        parent->left = left;
        parent->right = right;

        pq.push(*parent);
    }

    map<char, string> huffmanCodes;

    void traverse(node *node, string code) {
        if (!node) return;

        if (!node->left && !node->right) {
            huffmanCodes[node->symbol] = code;
            return;
        }

        if (node->left) traverse(node->left, code + "0");

        if (node->right) traverse(node->right, code + "1");
    }

    traverse(pq.top(), "");

    printHuffmanCodes(huffmanCodes);
}

int main() {
    map<char, int> charFreqMap = {{'a', 5}, {'b', 9}, {'c', 12}, {'d', 13}, {'e', 16}, {'f', 45}};

    generateHuffmanCodes(charFreqMap);
    return 0;
}
