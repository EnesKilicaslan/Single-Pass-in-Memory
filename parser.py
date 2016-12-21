"""
PARSING html files into toke_list.txt file

@Author Enes KILICASLAN


@Ref
    https://docs.python.org/2/library/htmlparser.html
    http://stackoverflow.com/questions/3411771/multiple-character-replace-with-python
    http://stackoverflow.com/questions/2212643/python-recursive-folder-read
    http://stackoverflow.com/questions/19859282/check-if-a-string-contains-a-number

"""

from HTMLParser import HTMLParser
import re
import os

result = open("token_list.txt", 'w', 0)
file_numner = open("file_number.txt", 'w', 0)

#by meaningfull I mean a word must include at least three different letters in it
def is_word_meaningful(str):
    line = ''.join(set(str))
    if len(line) > 2:
        return True
    else:
        return False

def only_letters(string):
    return all(letter.isalpha() for letter in string)

def more_than_three_same_letter(string):
    for ch in string:
        if string.count(ch) > 2:
            return True

    return False


class MyHTMLParser(HTMLParser):
    def __init__(self):
        HTMLParser.__init__(self)
        self.data = []

    def handle_data(self, data):
        data = data.replace('\n', '')
        data = data.replace('\t', '')

        if data.find('@import') != -1:
            return
        data = re.sub(r'[^\w\s]', '', data)

        #string does not contain letter
        if not re.search('[a-zA-Z]+', data) :
            return

        #this pass all non-useless words like a, as, in , to
        if len(data) > 2:
            current_words = data.split()
            for one_word in current_words:
                if len(one_word) > 2 and not one_word in self.data and not hasNumbers(one_word.lower()):
                    one_word = one_word.lower()
                    if is_word_meaningful(one_word) and only_letters(one_word) and not more_than_three_same_letter(one_word):
                        self.data.append(one_word)

def hasNumbers(inputString):
    return bool(re.search(r'\d', inputString))

def pars_html(path, num ):
    parser = MyHTMLParser()
    parser.feed(open(path).read())

    for one_word in parser.data:
        result.write(one_word + " " + str(num) + "\n")

    parser.close()

walk_dir = raw_input("please enter collection directory to index: ")
counter = 1
print "Tokenizing...\n"

for root, subdirs, files in os.walk(walk_dir):
    for file in files:
        if file.find(".html") != -1:
            name = ""
            name += root
            if root[len(root) - 1 ] != '/':
                name +=  "/"
            name += file
            try:
                file_numner.write(name + " " + str(counter) + "\n") #keep the name of the files
                pars_html(name, counter) # write tokens to the file
                counter += 1
            except:
                continue

print "total: ", counter , "number of files are processed"
