//
// Created by Enes Kılıçaslan on 06/12/16.
//

#ifndef SPIMI1_TOKEN_H
#define SPIMI1_TOKEN_H

#include <iostream>
#include <string>

using namespace std;

// This class  does not need copy constructer, destructer  or overloading assignment operator implicitly
class Token
{
public:
    Token(const string term, const long int doc_id);// constructer with term and doc_id
    
    //setter for term and doc_id
    void setTerm(const string theTerm);
    void setDoc_id(const long int theDoc_id);

    //getter for term and doc_id
    string getTerm() const { return this->term;}
    long int getDoc_id() const { return this->doc_id;}

private:
    string term;
    long int doc_id;

};

#endif //SPIMI1_TOKEN_H
