//
// Created by Enes Kılıçaslan on 06/12/16.
//

#include "Dictionary.h"

Dictionary::Dictionary()
{
    this->dictionary = map<string, PostingList>();
}

Dictionary::Dictionary(Token token, PostingList& posting_list)
{
    this->dictionary[token.getTerm()] = posting_list;
}

Dictionary::Dictionary(const map<string, PostingList> &thedictionary)
{
    this->dictionary= thedictionary;
}

void Dictionary::addToPostingList(Token token)
{
    map<string,PostingList> :: iterator it;

    it = this->dictionary.find(token.getTerm());

    if (it == this->dictionary.end()) //no term in the dictionary
    {
        PostingList temp = PostingList();
        this->dictionary[token.getTerm()] = temp; // create a new Posting list
        this->dictionary[token.getTerm()].addDoc_id(token.getDoc_id()); // add the current token to the posting list

    } else //term in dictionary
    {
        this->dictionary[token.getTerm()].addDoc_id(token.getDoc_id()); // add the current token to the posting list
    }
}

void Dictionary::writeToFile(string filename) 
{
	ofstream outfile;
	outfile.open (filename.c_str(), ios::out | ios::trunc); 

	if (outfile.is_open())
	{	
		//first is string and second is posting list
		for (map<string, PostingList>::iterator it=this->dictionary.begin(); it!=this->dictionary.end(); ++it) 
        	outfile << it->first << "," << it->second.toString() << endl;
        
	    outfile.close();

	}else 
		cout << "Unable to open file " << filename << endl; 
    
}