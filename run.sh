#compile cpp files  // -W -Wall -Werror -pedantic 
g++ Dictionary.cpp main.cpp PostingList.cpp Spimi.cpp Token.cpp -o exec

#/media/psf/Home/Desktop/au/IR/project/en/
python parser.py #run the parser
./exec #run spimi
