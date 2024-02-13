#include <iostream>
#include <queue>
#include <map>
using namespace std;


struct HuffmanNode {
    char data;
    int freq;
    HuffmanNode *left, *right;
    HuffmanNode(char data, int freq) : data(data), freq(freq), left(nullptr), right(nullptr) {}
};


struct Compare {
    bool operator()(HuffmanNode* a, HuffmanNode* b) {
        return a->freq > b->freq;
    }
};


void generateCodes(HuffmanNode* root, string code, map<char, string>& codes) {
    if (!root)
        return;

    if (root->data != '\0') {
        codes[root->data] = code;
    }

    generateCodes(root->left, code + "0", codes);
    generateCodes(root->right, code + "1", codes);
}


void buildHuffmanTree(string S, int f[]) {
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> pq;

    // Create leaf nodes for each character
    for (int i = 0; i < S.length(); ++i) {
        pq.push(new HuffmanNode(S[i], f[i]));
    }


    while (pq.size() > 1) {
        HuffmanNode* left = pq.top();
        pq.pop();
        HuffmanNode* right = pq.top();
        pq.pop();

        HuffmanNode* newNode = new HuffmanNode('\0', left->freq + right->freq);
        newNode->left = left;
        newNode->right = right;
        pq.push(newNode);
    }

    HuffmanNode* root = pq.top();

    map<char, string> codes;
    generateCodes(root, "", codes);

    cout << "Huffman codes will be:" << endl;
    for (auto& pair : codes) {
        cout << "  " << pair.first << " : " << pair.second << endl;
    }
}

int main() {
    string S;
    cout << "Enter the string S: ";
    cin >> S;

    int n = S.length();
    int f[n];
    cout << "Enter the frequencies of characters in order: ";
    for (int i = 0; i < n; ++i) {
        cin >> f[i];
    }

    buildHuffmanTree(S, f);

    return 0;
}
