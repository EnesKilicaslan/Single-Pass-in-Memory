# Single-Pass-in-Memory


Usage
	
	In the files, There is run.sh which contains running Tokenization and Compile and run process. 
	If you call 	./run.sh from your terminal, Tokenization part will start and you will be prompted to enter path of collection.
  After tokenization  part completed, indexer will start. And at the end you will be able to answer Boolean queries. 

Requirements

Python 2.7
	This is because of tokenization part, I am using htmllib standard [1] library 	
    from Python 2.7 to tokenize the collection and turning it into a stream of tokens file 	
    named “token_list.txt” and file name and doc-id pair in the file named 	“file_number.txt”.
	
	The reason why I am using this library is it is easy to implement and it is a standard 	library, 
  so no need installing something else except from Python 2.7 . There were 	some libraries in C++ but they
  requires external libraries and installing.


C++ Compiler
	Because Spimi and Boolean retrieval parts are implemented in C++, compiler is needed. I currently tested with
    GNU C++ compiler G++ with default options on Ubuntu operating system and did not have any problem to run. 
