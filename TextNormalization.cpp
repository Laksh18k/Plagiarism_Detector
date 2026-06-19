#include "TextNormalization.h"

string TextNormalization::clean(const string &input){
    string output;
    output.reserve(input.size());
    for(char ch:input){
        if(isalnum(ch)) output+=tolower(ch);
    }
    return output;
}