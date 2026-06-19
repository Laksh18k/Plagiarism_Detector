#pragma once

#include <string>
#include <unordered_set>

using namespace std;

class Document {
    private:
        string rawText;
        string cleanText;
        unordered_set<long long> hashes;

        // static data members same for all instances
        static const int Window_Size = 10;          // size of sliding window
        static const long long Modulus = 1e9 + 7;  // modulus to keep hash in check
        static const long long Base = 31;           // base for hash function

        void getHash();

    public:
        Document(const string& text);

        string getRawText() const;
        string getCleanText() const;
        unordered_set<long long> getHashes() const;
};
