/**
 * @project
 *
 *  **** Information Retrieval, SPIMI-Project, University Of Antwerpen ****
 *
 * @author
 *  @name
 *      Enes KILICASLAN
 *  @education
 *      Computer Science MSc at UA and BSc at Gebze Technical University
 *  @contact
 *      eeneskilicaslan@gmail.com
 *
 * @requirements
 *  Python 2.7
 *      -This is because of tokenization part, I am using htmllib standar library from Python 2.7 to tokenize the collection
 *      and turning it into a stream of tokens file named 'token_list.txt'
 *
 *  C++ Compiler
 *      -I am using gcc GNU compiler with the default options on Linux(Ubuntu).  Actually This program is operating system dependent
 *
 *
 * @referances
 *
 *  read
 *      -http://stackoverflow.com/questions/7868936/read-file-line-by-line
 *
 *  free memory available
 *      -http://stackoverflow.com/questions/669438/how-to-get-memory-usage-at-run-time-in-c
 *      -http://stackoverflow.com/questions/2513505/how-to-get-available-memory-c-g
 *
 *
 *  easy assignment from string to variable
 *      -http://stackoverflow.com/questions/7868936/read-file-line-by-line
 *	
 * 	convert int to string
 *		-http://stackoverflow.com/questions/5590381/easiest-way-to-convert-int-to-string-in-c
 *
 */

#include "Spimi.h"

 using namespace  eneskilicaslan_au_spimi;

int main() {

    Spimi obj("asdsad"); //takes the name of token stream file
    obj.run();

    return 0;
}
