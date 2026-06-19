# pragma once
#include <vector>
#include "Document.h"
using namespace std;

class PlagiarismDetector{
    private:
        double threshold;
        double getSimilarity(const Document &a, const Document &b);

    public:
        PlagiarismDetector(double threshold=0.5);
        bool isPlagiarised(const Document &a, const Document &b);
        void checkAll(vector<Document>& docs);
};