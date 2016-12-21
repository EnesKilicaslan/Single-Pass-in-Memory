//
// Created by Enes Kılıçaslan on 10/12/16.
//

#ifndef SPIMI1_SPIMI_H
#define SPIMI1_SPIMI_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "Token.h"
#include "PostingList.h"
#include "Dictionary.h"

using namespace std;

namespace eneskilicaslan_au_spimi {

class Spimi {
public:
    Spimi(const string &token_stream_path);

    void run();

    string get_doc_name(int doc_id);
    long getMin_memory() const ;

    const string getToken_stream_path() const;

    void setToken_stream_path(const string &token_stream_path);
    void spimi(); //this will be private
    string get_output_file_name() const;

    map<string, vector<int> > words;

private:
    string token_stream_path;
    vector< string > dictionary_file_names;
    const long int min_memory; // this is in KB
    string output_file_name;

    map<int , string> filename_docid;

    bool is_there_enough_memory() const; // only used by spimi method
    void load_file_names(); // keep file_name docid pair in memory
    void load_words();
    vector<int> not_operation(vector<int> vec);
    int total_num_of_files; 
   
};

long int get_free_memory_available(); // **Warning! -- this works only on Linux machines
template <typename T>
string number_to_string(T pNumber);


/**
 *
 * @param n number of files that need to be merged
 * @return name of the output file
 */
string merge_files(int n);
void merge_two_files(string in_file_name1, string in_file_name2, string out_file_name);
bool check_query(vector<string> v);
vector<int> and_operation(vector<int> vec1, vector<int> vec2);
vector<int> or_operation(vector<int> vec1, vector<int> vec2);


}//end of namespace eneskilicaslan_au_spimi




#endif //SPIMI1_SPIMI_H
