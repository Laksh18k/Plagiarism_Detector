#include "PlagiarismDetector.h"
#include "FileManager.h"
#include <iostream>

using namespace std;

int main(){
    vector<Document> docs;

    // load documents from files
    vector<string> filePaths={"doc1.txt","doc2.txt","doc3.txt"};
    for(const string &path:filePaths){
        try{
            string text=FileManager::read(path);
            docs.push_back(Document(text));
            cout << "Loaded: "<<path<<"\n";
        }catch(const runtime_error &e){
            cout << "Error loading "<<path<<": "<<e.what()<<"\n";
        }
    }

    if(docs.size()<2){
        cout << "Need at least 2 documents to check.\n";
        return 1;
    }

    PlagiarismDetector detector(0.5); // 50% similarity threshold

    int choice;
    cout << "\n1. Direct Check (Document 1 vs Document 2)\n";
    cout << "2. Check All\n";
    cout << "Enter choice: ";
    cin >> choice;

    switch(choice){
        case 1:
            cout << "\n--- Direct Check: Document 1 vs Document 2 ---\n";
            if(detector.isPlagiarised(docs[0],docs[1])){
                cout << "Plagiarism detected between Document 1 and Document 2.\n";
            }else{
                cout << "No plagiarism detected between Document 1 and Document 2.\n";
            }
            break;
        case 2:
            cout << "\n--- Check All ---\n";
            detector.checkAll(docs);
            break;
        default:
            cout << "Invalid choice.\n";
            return 1;
    }

    return 0;
}