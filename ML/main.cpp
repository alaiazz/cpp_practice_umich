//Project UID db1f506d06d84ab787baf250c265e24e
# include <iostream>
# include <string>
# include <cmath>
# include <map>
# include <set>
# include "csvstream.h"

using namespace std;

// EFFECTS: Return a set of unique whitespace delimited words.x (provided)
    set<string> unique_words(const string &str) {
        istringstream source(str);
        set<string> words;
        string word;
        while (source >> word) {
            words.insert(word);
        }
        return words;
    }

class Classifier{
public:
    double training (const map<string, string>& rawrow, int argc){
        string label, content;
        postnum++;
        for(auto& col:rawrow){
            if(col.first=="tag"){
                label=col.second;
            }
        }
        for(auto& col:rawrow){
            if(col.first=="tag"){
                labels[col.second]++;
            }
            if(col.first=="content"){
                content = col.second;
                set<string> uniqwords = unique_words(col.second);
                for (auto& singleword:uniqwords){
                    if(words.find(singleword)==words.end()){
                        uniqwordcount++;
                    }
                    words[singleword]++;
                    labelwords[{label,singleword}]++;
                }
            }
        }
        if(argc==4){cout<<"  label = "<<label<<", content = "<<content<<endl;}
        return uniqwordcount;
    }

    void printing (){
        cout<<"classes:"<<endl;
        for(auto& col:labels){
            double a=log(col.second/postnum);
            cout<<"  "<<col.first<<", "<<col.second<<" examples, log-prior = "
            <<a<<endl;
        }
        cout<<"classifier parameters:"<<endl;
        for(auto& outter:labelwords){
            string label=outter.first.first;
            double b=log(labelwords[outter.first]/double(labels[label]));
                cout<<"  "<<label<<":"<<outter.first.second<<", count = "
                <<labelwords[outter.first]<<", log-likelihood = "<<b<<endl;
        }
        cout<<endl;
    }

    int readtraining(string train_filename, Classifier & machine, int argc){
        try {
            csvstream csvin(train_filename);
            map <string,string> row;
            int example=0, vocab=0;
            if(argc==4){cout<<"training data:"<<endl;}
            while (csvin >> row){
                example++;
                vocab = machine.training(row,argc);
            }
            cout<< "trained on " << example << " examples" <<endl;
            if(argc==4){cout<<"vocabulary size = "<<vocab<<endl;}
            cout<<endl;
            if(argc==4){machine.printing();}
            return 0;
        }
        catch (const csvstream_exception& e) {
            cout << "Error opening file: " <<train_filename<< endl;
            return 3;
        }
    }

    bool predicting (const map<string, string>& rawtestrow){
        string correctlabel, content, predicted;
        set<string> uniqwords;
        double maxscore = 0-INFINITY;
        for(auto& col:rawtestrow){
            if(col.first=="tag"){
                correctlabel= col.second;
            }
            if(col.first=="content"){
                content = col.second;
                uniqwords = unique_words(col.second);
            }
        }
        for(auto& test:labels){
            double score=log(labels[test.first]/postnum);
            for(auto& sinw:uniqwords){
                if(words.find(sinw)==words.end()){
                    score= score+ log(1/postnum);
                }
                else if(labelwords.find({test.first,sinw})==labelwords.end()){
                    score= score+ log(words[sinw]/postnum);
                }
                else{
                    double a= labelwords[{test.first,sinw}];
                    score= score+ log(a/labels[test.first]);
                }
            }
            if(score>maxscore){
                predicted=test.first;
                maxscore=score;
            }
        }
        cout<<"  correct = "<<correctlabel<<", predicted = "<<predicted
        <<", log-probability score = "<<maxscore<<endl
        <<"  content = "<<content<<endl<<endl;
        if(predicted==correctlabel){return true;}
        else{return false;}
    }

private:
    map<string , int> labels;
    map<string , int> words;
    map<pair<string, string>,int> labelwords;
    double postnum=0;
    double uniqwordcount=0;
};

int main(int argc, char **argv) {
    cout.precision(3);
    if(argc!=3 && argc!=4){
        cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
        return 1;}
    if(argc==4){
        string a=argv[3];
        if(a!="--debug"){
        cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
        return 2;}}
    string train_filename= argv[1], test_filename= argv[2];
    Classifier machine;
    if(machine.readtraining(train_filename, machine, argc)!=0){
        return 3;
    }
    try {
        csvstream csvtest(test_filename);
        map <string,string> row;
        int y=0, all=0;
        cout<<"test data:"<<endl;
        while (csvtest >> row){ all++;
            if(machine.predicting(row)==true){y++;}}
    cout<<"performance: "<<y<<" / "<<all<<" posts predicted correctly"<<endl;}
    catch (const csvstream_exception& e) {
        cout << "Error opening file: " <<test_filename<< endl;
        return 4;}
    return 0;
}