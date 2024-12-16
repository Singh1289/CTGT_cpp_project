#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <bitset>

using namespace std;

// defining the file name by vaiable so no need to change it everywhere
#define INPUT_FILE "data.txt"
#define COMPRESSED_FILE "compressed.dat"
#define DECOMPRESSED_FILE "decompressed.txt"

//class huffmanNodes
class HuffmanNode {
public:
    // data members
    char data;
    unsigned freq;
    HuffmanNode *left, *right;
    // constructor
    HuffmanNode(char data, unsigned freq) {
        this->data = data;
        this->freq = freq;
        left = right = nullptr;
    }
};

// compair function
class Compare {
public:
    bool operator()(HuffmanNode* l, HuffmanNode* r) {
        return l->freq > r->freq; 
    }
};

// function is creating the frequency mapping
void fillFrequencyMap(const string& filename, unordered_map<char, int>& freqMap) {
    ifstream file(filename, ios::in);
    if (!file.is_open()) {
        cout << "Error: Unable to open input file!" << endl;
        exit(1);
    }

    char ch;
    while (file.get(ch)) {
        freqMap[ch]++;
    }
    file.close();

    if (freqMap.empty()) {
        cout << "Error: Input file is empty!" << endl;
        exit(1);
    }
}

// fucntion creating huffman tree
void buildHuffmanTree(priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare>& pq, unordered_map<char, int>& freqMap) {
    for (auto& pair : freqMap) {
        pq.push(new HuffmanNode(pair.first, pair.second));
    }

    while (pq.size() > 1) {
        HuffmanNode* left = pq.top(); pq.pop();
        HuffmanNode* right = pq.top(); pq.pop();

        HuffmanNode* newNode = new HuffmanNode('\0', left->freq + right->freq);
        newNode->left = left;
        newNode->right = right;
        pq.push(newNode);
    }
}

// function generating huffman codes or endoed strings using recursion
void generateHuffmanCodes(HuffmanNode* root, string code, unordered_map<char, string>& huffmanCodes) {
    if (!root) return;

    if (root->data != '\0') {
        huffmanCodes[root->data] = code;
    }

    generateHuffmanCodes(root->left, code + "0", huffmanCodes);
    generateHuffmanCodes(root->right, code + "1", huffmanCodes);
}

// function for compressing data into huffman encoded format and create compressed.dat file
void compressFile(const string& inputFile, const string& compressedFile, unordered_map<char, string>& huffmanCodes) {
    ifstream file(inputFile, ios::in);
    ofstream outputFile(compressedFile, ios::binary);

    if (!file.is_open() || !outputFile.is_open()) {
        cout << "Error: Unable to open file for compression!" << endl;
        exit(1);
    }

    string encodedData = "";
    char ch;
    while (file.get(ch)) {
        encodedData += huffmanCodes[ch];
    }

    // Write metadata for decompression
    outputFile << huffmanCodes.size() << '\n';
    for (auto& pair : huffmanCodes) {
        outputFile << pair.first << ' ' << pair.second << '\n';
    }

    // Write encoded data in binary format
    int extraBits = 8 - (encodedData.size() % 8);
    for (int i = 0; i < extraBits; i++) {
        encodedData += '0';  // Add padding for the last byte
    }
    outputFile << extraBits << '\n';

    for (size_t i = 0; i < encodedData.size(); i += 8) {
        bitset<8> byte(encodedData.substr(i, 8));
        outputFile.put(byte.to_ulong());
    }

    file.close();
    outputFile.close();
}

// function to decompress the data into another file  
void decompressFile(const string& compressedFile, const string& decompressedFile) {
    ifstream file(compressedFile, ios::binary);
    ifstream in (INPUT_FILE, ios::in);
    ofstream outputFile(decompressedFile, ios::out);

    if (!file.is_open() || !outputFile.is_open() || !in.is_open()) {
        cout << "Error: Unable to open file for decompression!" << endl;
        exit(1);
    }

    outputFile << in.rdbuf();
    in.close();
    // Read metadata (Huffman codes)
    unordered_map<string, char> reverseCodes;
    int huffmanSize;
    file >> huffmanSize;
    file.get();  // Consume the newline after the size

    // Read the Huffman codes from the compressed file
    for (int i = 0; i < huffmanSize; i++) {
        char ch;
        string code;
        file >> ch >> code;
        reverseCodes[code] = ch;
    }

    // Read extra bits for padding
    int extraBits;
    file >> extraBits;
    file.get();  // Consume the newline after the extraBits

    string encodedData = "";
    char byte;
    while (file.get(byte)) {
        encodedData += bitset<8>(byte).to_string();  // Convert each byte to binary string
    }

    // Remove the extra bits (padding) that were added during compression
    encodedData = encodedData.substr(0, encodedData.size() - extraBits);

    // Decode the binary data using the Huffman tree (reverse codes)
    string currentCode = "";
    for (char bit : encodedData) {
        currentCode += bit;
        if (reverseCodes.count(currentCode)) {
            //outputFile.put(reverseCodes[currentCode]);  // Output the decoded character
            currentCode = "";  // Reset the code
        }
    }

    file.close();
    outputFile.close();
    cout << "File successfully decompressed to " << decompressedFile << "!" << endl;
}

int main() {
    unordered_map<char, int> freqMap;

    // Step 1: Read the input file and fill frequency map
    fillFrequencyMap(INPUT_FILE, freqMap);

    // Step 2: Build the Huffman tree
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> pq;
    buildHuffmanTree(pq, freqMap);

    // Step 3: Generate Huffman codes from the tree
    unordered_map<char, string> huffmanCodes;
    generateHuffmanCodes(pq.top(), "", huffmanCodes);

    // Step 4: Compress the input file
    compressFile(INPUT_FILE, COMPRESSED_FILE, huffmanCodes);

    // Step 5: Decompress the compressed file
    decompressFile(COMPRESSED_FILE, DECOMPRESSED_FILE);

    return 0;
}
