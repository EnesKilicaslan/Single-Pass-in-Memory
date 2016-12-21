//
// Created by Enes Kılıçaslan on 10/12/16.
// Ref: http://stackoverflow.com/questions/1894886/parsing-a-comma-delimited-stdstring
//
#include "Spimi.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <stack>
#include <stdlib.h>     /* exit, EXIT_FAILURE */
#include <cstdio>
#include <ctime>
#include <algorithm>


namespace eneskilicaslan_au_spimi{

Spimi::Spimi(const string &token_stream_path) : min_memory(60000) {
    this->token_stream_path = "/home/parallels/Desktop/_SPIMI_/token_list.txt"; //token_stream_path;
    output_file_name = "out0.txt"; //it can be out0.txt or out1.txt !! demo
}

long int Spimi:: getMin_memory() const {
    return this->min_memory;
}

void Spimi::run()
{
	clock_t start;
	double duration_indexer, duration_loading_file_names;

	start = clock(); //start timer
	//run spimi algorithm
	cout << "****Single Pass in Memory Indexer started**********" << endl;
	//spimi();
	duration_indexer = ( std::clock() - start ) / (double) CLOCKS_PER_SEC; //finish timer indexing
	cout << "Indexing is Done in " << number_to_string(duration_indexer) << " seconds.." << endl;

	start = clock(); //timer for loading file names

	load_file_names();
	load_words();

	duration_loading_file_names = ( std::clock() - start ) / (double) CLOCKS_PER_SEC; //finish timer loading words an file names
	cout << "Loading file names and words Done in " << number_to_string(duration_loading_file_names) << " seconds.." << endl;
	cout << "Everthing is Done in " << number_to_string(duration_indexer + duration_loading_file_names) << " seconds.." << endl;


	cout << "**********Ready to Answer Boolean Queries***********" << endl;

	while(true)
	{
		string  temp = "";
		string first = "",  second = "";
		double duration_answer;
		//variables for query results
		stack<string> oper;
		stack<string> search;

		vector<int> v1, v2, result; //for first and second

		cout << "Enter your Query: ";

		char input[100];
		cin.getline(input,sizeof(input));
		string user_input(input);
		start = clock(); //start timer

		vector<string> query;
		stringstream qss(user_input);

		while(qss >> temp)
			query.push_back(temp);

		if(!check_query(query)){
			cout << "Wrong query, try again.." << endl;
			continue;
		}

		//starts from here !!!!! Forget about not for now!!!!
		for( unsigned int i=0; i< query.size(); i++)
			if(query[i] == "or" || query[i] == "and" || query[i] == "not")
				oper.push(query[i]);
			else
				search.push(query[i]);

		first = search.top();
		search.pop();

		result = words[first];
		
		while(!oper.empty())
		{
			bool is_not = false;
			string op = "";

			op = oper.top();
			oper.pop();
			
			if(op == "not"){
				is_not = true;
				op = oper.top();
				oper.pop();
			}
			
			second = search.top();
			search.pop();
			v2 = words[second];

			if(is_not)
				v2 = not_operation(v2);
			
			if(op == "or"){
				result = or_operation(result, v2);
			}
			else if(op == "and"){
				
				result = and_operation(result, v2);
			}
			
		}

		
		for(unsigned int i=0; i< result.size(); ++i)
			cout << i+1 << "-)   " << get_doc_name( result[i]) << endl;

		cout << endl;
		
		duration_answer = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
		cout << "\t\t\t\t( " << number_to_string(duration_answer) << " seconds)" << endl; 

	}

}

void Spimi::spimi()
{
    string line;
    string input_var; //this will be deleted
    int num_of_blocks = 1;

    ifstream infile;
    infile.open(this->getToken_stream_path().c_str());

    //check if the token stream file is really exist
    if(infile.is_open())
    {	
    	 
    	//while the token stream is not consumed totally
        while(!infile.eof()) 
        {
            string dict_file_name;
            dict_file_name = number_to_string(num_of_blocks);
	    	dict_file_name += "block.txt";

	   		Dictionary *mydict = new Dictionary();

            //read the whole token stream, till it is totally consumed
            while (is_there_enough_memory()) {

            	getline(infile, line);
                string token_term;
                long int token_docid;

                istringstream iss(line);

                //assigning term and docid
                if (!(iss >> token_term >> token_docid))
                    break;
                
                /**
                 * in spimi algorithm,
                 *  1-  if token not in Dictionary:
                 *          addToDictionary(token)
                 *  2-  else:
                 *          posting_list = getPostingsList()
                 *      if postin_list.isFull()
                 *          posting_list.doubleSize()
                 *
                 *  3-  add_to_posting_list(token.doc_id)
                 *
                 *  part 1 is done in the Dictionary class automatically, i.e if the token is already in the dictionary it does not
                 *      add to dictionary just adds the doc_id, or if the token does not exist in the dictionary the class adds the
                 *      term and doc_id itself.
                 *
                 *  part 2 is done in PostingList class automatically, the class always checks if the capacity is enough or not before
                 *      adding a doc_id to the list. if the capacity is not enough it makes its size double.
                 *
                 *  part 3 is done in Dictionary class, when we add a token to the dictionary it add's its term and doc_id together
                 */
                Token temp(token_term, token_docid);
                
                mydict->addToPostingList(temp);
            }

            //this is for demo and to keep track of memory with htop
            //cout  << "for the next block or finishing press any keyboard button and enter, " << dict_file_name<<endl;
            //cin  >> input_var;
            ++num_of_blocks;

            //we don't need to sort here, because in C++ map keys are always sorted
            mydict->writeToFile(dict_file_name);
            delete mydict;

            this->dictionary_file_names.push_back(dict_file_name);
        }

        --num_of_blocks; //decrece by one because, in the last iteration there is one extra increasing
        cout << "merging files, " << number_to_string(num_of_blocks) << endl;
        this->output_file_name = merge_files(num_of_blocks);
        cout << "merging is done!" << endl;
        cout << "output_file_name = " << this->output_file_name << endl;


    }
    else{
        cout << this->getToken_stream_path() << " could not open!!";
        exit (EXIT_FAILURE);
        
    }
}


bool check_query(vector<string> v)
{
	//variables for v results
	stack<string> oper;
	stack<string> search;
	unsigned int oper_len, search_len;
	string prev;
	unsigned int i;

	//starts from here !!!!! Forget about not for now!!!!
	for( i=0; i< v.size(); i++)
	{	

		if(i > 0){
			prev = v[i - 1];
		}

		if(v[i] == "or" || v[i] == "and"){
			oper.push(v[i]);
		}
		else if (v[i] == "not"){
			
			if((prev != "or" && prev != "and") && i > 0){
				
				return false;
			}
		}
		else{
			search.push(v[i]);
		}

	}

	oper_len = oper.size();
	search_len = search.size();
	
	if(oper_len != search_len -1)
		return false;

	return true;
}


void Spimi::load_words()
{
	string line = "";

	ifstream infile;
    infile.open(get_output_file_name().c_str());

    if (!infile.is_open())
    {
        cerr << get_output_file_name() << " could not open" << endl;
    }

    //file_number.txt
    while(getline(infile, line))
    {
        string word;
        string docids;
       	
        istringstream iss(line);

        getline(iss, word, ',');
        getline(iss, docids, ',');

        std::stringstream ss(docids);

        int i;

        while(ss >> i)
        	words[word].push_back(i);
    }

}

string Spimi::get_output_file_name() const
{
	return output_file_name;
}
string Spimi::get_doc_name(int doc_id)
{
	return this->filename_docid[doc_id];
}


void Spimi::load_file_names()
{
	string line = "";
	this->total_num_of_files = 1;
    ifstream infile;
    infile.open("./file_number.txt");

    if (!infile.is_open())
    {
        cerr << "./file_number.txt could not open";
    }


    //file_number.txt
    while(getline(infile, line))
    {
        string file_name;
        int docid;
        istringstream iss(line);

        //assigning term and docid
        if (!(iss >> file_name >> docid))
        {
            cout << "Something wrong with token stream file, no good format like(i.e 'term do_idc')";
            break;
        }

        this->filename_docid[docid] = file_name;
        ++this->total_num_of_files;

    }
}


const string Spimi::getToken_stream_path() const {
    return token_stream_path;
}

void Spimi::setToken_stream_path(const string &token_stream_path) {
    Spimi::token_stream_path = token_stream_path;
}


bool Spimi::is_there_enough_memory() const
{
    if(get_free_memory_available() > this->getMin_memory())
        return true;
    else
        return false;
}

/*the below methods  don't  belong to Spimi class but they are in the same namespace*/
//this method works only on linux machines
long int get_free_memory_available() 
{
    string line, str1, str2;
    long int value;
    ifstream infile;

    infile.open("/proc/meminfo", ifstream::in);
    getline(infile, line); // skip first line
    getline(infile, line);

    istringstream iss(line);

    //split the value in long int format
    if (!(iss >> str1 >> value >> str2))
        cout << "proc file is not in expected format";

    return value;
}

template <typename T>
string number_to_string(T pNumber)
{
 ostringstream oOStrStream;
 oOStrStream << pNumber;
 return oOStrStream.str();
}

/**
 * merge files
 * @param n number of files that need to be merged
 * @return name of the output file
 */
string merge_files(int n)
{
    string out[]= {"out0.txt","out1.txt"};
    string output;

    if(n < 1)
    {
        cout << "merge is not possible, there is no file";

    }
    else if(n == 1){
        return "1block.txt"; //return the input file
    }

    else if(n == 2){
        merge_two_files("1block.txt", "2block.txt", "out1.txt");
        return "out1.txt";
    }
    else {
        merge_two_files("1block.txt", "2block.txt", "out1.txt");
        output = out[1];
   
        for (int i = 3; i <= n; ++i) {
            merge_two_files(out[i%2], (number_to_string(i)+"block.txt").c_str(), out[(i%2 + 1)%2]);
            output = out[(i%2 + 1)%2];
        }
    }

    //clean block files
    for(int i=0; i<=n; ++i)
    	remove((number_to_string(i)+ "block.txt").c_str() );

    (output == out[0])? remove(out[1].c_str()) : remove(out[0].c_str()); //remove temproray output file
    return output;
}

//the files must contain more one line
void merge_two_files(string in_file_name1, string in_file_name2, string out_file_name)
{
    string line1="" , line2= "";
    string term1="", term2= "", doc1="", doc2="";

    ifstream indata1;
    ifstream indata2;
    ofstream outdata;

    indata1.open(in_file_name1.c_str());
    indata2.open(in_file_name2.c_str());
    outdata.open(out_file_name.c_str());

    bool need_new_first  = true;
    bool need_new_second = true;
    bool first_is_valid  = true;
    bool second_is_valid = true;

    while(first_is_valid || second_is_valid)
    {         

        if (need_new_first)
        {
            if (getline(indata1, line1))
                first_is_valid = true;
            else
                first_is_valid = false;

            need_new_first = false;
        }

        if (need_new_second)
        {
            if (getline(indata2, line2))
                second_is_valid = true;
            else
                second_is_valid = false;

            need_new_second = false;
        }

        if (first_is_valid && second_is_valid)
        {
            //seperate tokens
            istringstream ss1(line1);
            istringstream ss2(line2);

            getline(ss1, term1, ',');
            getline(ss1, doc1,  ',');

            getline(ss2, term2, ',');
            getline(ss2, doc2,  ',');   

            if (term1 < term2)
            {
                outdata << line1 << "\n";
                need_new_first = true;
            }
            else if (term2 < term1)
            {
                outdata << line2 << "\n";
                need_new_second = true;
            }
            else //both of them are equal
            {   
                outdata << term1 + "," + doc1 + " " + doc2 + "\n";
                need_new_first = true;
                need_new_second = true;
            }
        } 
        else if (first_is_valid)
        {
            outdata << line1 << "\n";
            need_new_first = true;
        }
        else if (second_is_valid)
        {
            outdata << line2 << "\n";
            need_new_second = true;
        }
        
    }
}


vector<int> and_operation(vector<int> vec1, vector<int> vec2){

	unsigned int i=0, j=0;
	vector<int> result;

	while(i< vec1.size() && j < vec2.size()){

		if(vec1[i] == vec2[j]){
			result.push_back(vec1[i]);
			++i;
			++j;
		}
		else if(vec1[i] < vec2[j])
			++i;
		else
			++j;
	}

	return result;
}

vector<int> or_operation(vector<int> vec1, vector<int> vec2){

	unsigned int i=0, j=0;
	vector<int> result;

	//proccess until at least one of the vectors are consumed
	while(i< vec1.size() && j < vec2.size()){

		if(vec1[i] == vec2[j]){
			result.push_back(vec1[i]);
			++i;
			++j;
		}
		else if(vec1[i] < vec2[j]){
			result.push_back(vec1[i]);
			++i;
		}
		else{
			result.push_back(vec2[j]);
			++j;
		}
	}

	//if first vector is not consumed totally
	if ( i < vec1.size())
		while(i != vec1.size()){
			result.push_back(vec1[i]);
			++i;
		}
	//if second vector is not consumed totally
	else if (j < vec2.size())
		while(j != vec2.size()){
			result.push_back(vec2[j]);
			++j;
		}

	return result;
}


vector<int> Spimi::not_operation(vector<int> vec)
{
	vector<int> result;

	for(int i=1; i<this->total_num_of_files; ++i)
	{
		if(find(vec.begin(), vec.end(), i) != vec.end())
			continue;

		result.push_back(i);
	}

	return result;

}


}//end of namespace
