#compile cpp files  // -W -Wall -Werror -pedantic 
g++ Dictionary.cpp main.cpp PostingList.cpp Spimi.cpp Token.cpp -o exec

python parser.py #run the parser
./exec #run spimi
