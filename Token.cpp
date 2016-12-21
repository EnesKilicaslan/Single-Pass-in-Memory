//
// Created by Enes Kılıçaslan on 06/12/16.
//

#include "Token.h"

Token :: Token(const string term, long int doc_id)
{
    this->setTerm(term);
    this->setDoc_id(doc_id);
}

void Token ::setTerm(const string theTerm)
{
    this->term = theTerm;
}

void Token ::setDoc_id(const long int theDoc_id)
{
    this->doc_id = theDoc_id;
}

