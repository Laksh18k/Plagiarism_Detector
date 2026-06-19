#include "Document.h"
#include "TextNormalization.h"

void Document::getHash(){
    long long string_size=cleanText.size();
    if(string_size < Window_Size) return;
    long long base_power=1;
    for(int i=0;i<Window_Size;i++){         // precomputing the maximum base power
        base_power=(base_power*Base)%Modulus;
    }
    long long current_hash=0;
    for(int i=0;i<Window_Size;i++){
        current_hash=(current_hash*Base+cleanText[i])%Modulus;
    }
    hashes.insert(current_hash);
    for(long long i=Window_Size;i<string_size;i++){
        char oldChar=cleanText[i-Window_Size];
        char newChar=cleanText[i];
        long long newHash=((current_hash-oldChar*base_power%Modulus+Modulus)*Base+newChar)%Modulus;
        hashes.insert(newHash);
        current_hash=newHash;               // slide the window forward
    }
}

Document::Document(const string &text){
    rawText=text;
    cleanText=TextNormalization::clean(rawText);
    getHash();
}

string Document::getRawText() const { return rawText; }
string Document::getCleanText() const { return cleanText; }
unordered_set<long long> Document::getHashes() const { return hashes; }