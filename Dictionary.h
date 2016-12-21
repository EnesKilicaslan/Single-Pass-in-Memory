//
// Created by Enes Kılıçaslan on 06/12/16.
//

#ifndef SPIMI1_DICTIONARY_H
#define SPIMI1_DICTIONARY_H

#include <iostream>
#include <fstream>
#include <string>
#include <map>

#include "PostingList.h"
#include "Token.h"

using namespace std;

class Dictionary {

public:
    Dictionary();
    Dictionary(Token token, PostingList& posting_list);
    Dictionary(const map<string, PostingList> &dictionary);

    void addToPostingList(Token token);
    // this is now just print
    void writeToFile(string filename) ;

private:
    //term , list of doc_ids
    map<string, PostingList> dictionary;

};


#endif //SPIMI1_DICTIONARY_H
