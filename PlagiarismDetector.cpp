#include "PlagiarismDetector.h"
#include "Document.h"
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
    // containment  similarity
    int smaller=min(hash_a.size(),hash_b.size());
    if(smaller==0) return 0.0;
    return (double)common/smaller;
}

bool PlagiarismDetector::isPlagiarised(const Document &a, const Document &b){
    double hashScore=getSimilarity(a,b);
    double lcsScore=getLCSSimilarity(a,b);
    double combined=(hashScore+lcsScore)/2; 
 
    cout << "  Hash similarity: "<<hashScore*100<<"%\n";
    cout << "  LCS similarity:  "<<lcsScore*100<<"%\n";
    cout << "  Combined score:  "<<combined*100<<"%\n";
 
    return combined>=threshold;
}

void PlagiarismDetector::checkAll(vector<Document> &docs){
    int n=docs.size();
    bool found=false;
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            double hashScore=getSimilarity(docs[i],docs[j]);
            double lcsScore=getLCSSimilarity(docs[i],docs[j]);
            double combined=(hashScore+lcsScore)/2;
            if(combined>=threshold){
                cout << "Plagiarism detected between Document "<<i+1<<" and Document "<<j+1<<"\n";
                cout << "  Hash similarity: "<<hashScore*100<<"%\n";
                cout << "  LCS similarity:  "<<lcsScore*100<<"%\n";
                cout << "  Combined score:  "<<combined*100<<"%\n";
                found=true;
            }
        }
    }
    if(!found) cout << "No plagiarism detected.\n";
}

double PlagiarismDetector::getLCSSimilarity(const Document &a, const Document &b){
    const string& text_a=a.getCleanText();
    const string& text_b=b.getCleanText();
    long long size_a=text_a.size();
    long long size_b=text_b.size();
    if(size_a==0||size_b==0) return 0.0;
    vector<long long> prev(size_b+1,0);
    vector<long long> curr(size_b+1,0);
    for(int i=1;i<=size_a;i++){
        for(int j=1;j<=size_b;j++){
            if(text_a[i-1]==text_b[j-1]) curr[j]=1+prev[j-1];
            else curr[j]=max(curr[j-1],prev[j]);
        }
        prev=curr;
    }
    long long length=prev[size_b];
    return (double)length/min(size_a,size_b);
}