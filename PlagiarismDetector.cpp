#include "PlagiarismDetector.h"
#include <iostream>
 
PlagiarismDetector::PlagiarismDetector(double threshold){
    this->threshold=threshold;
}

double PlagiarismDetector::getSimilarity(const Document& a,const Document &b){
    unordered_set<long long> hash_a= a.getHashes();
    unordered_set<long long> hash_b= b.getHashes();
    int common=0;
    for(long long hashval:hash_b){
        if(hash_a.count(hashval)) common++;
    }
    // containment: common/smaller set
    // more accurate than jaccard when documents differ in length
    int smaller=min(hash_a.size(),hash_b.size());
    if(smaller==0) return 0.0;
    return (double)common/smaller;
}

bool PlagiarismDetector::isPlagiarised(const Document& a,const Document &b){
    return getSimilarity(a,b)>=threshold;
}

void PlagiarismDetector::checkAll(vector<Document>& docs){
    int n=docs.size();
    bool found=false;
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            double score=getSimilarity(docs[i],docs[j]);
            if(score>=threshold){
                cout << "Plagiarism detected between Document "<<i+1<<" and Document "<<j+1;
                cout << " (similarity: "<<score*100<<"%) \n";
                found=true;
            }
        }
    }
    if(!found) cout << "No plagiarism detected.\n";
}
