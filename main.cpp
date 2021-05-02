#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;
struct Word {
    string word;
    Word *next;
    Word *synonym;
};

// print link list
void printDictionary(Word *&head);

// creat word prototype
Word *creatWord(const string &word);

// add created word in a linked list
void addWord(Word *&head, Word *temp);

// add created synonym for added word in a linked list
void addSynonym(Word *&head, const string &word, Word *temp);

//delete main word and all synonyms
int deleteWord(Word *&head, const string &word);

int deleteSynonym(Word *&head, const string &word, const string &syn);

void searchWord(Word *&head, const string &word);

void changeMisspelling(Word *&head, const string &currentWord, const string &newWord);

void writeOnFile(Word *&head, const string &path);

void readFromFile(Word *&head, const string &path);

int main() {
    Word *head = nullptr;
    int inputChoice, countOfSynonyms;
    string word, synonym, changeWord, path;
    do {
        cout << "1.Add word and synonyms\n";
        cout << "2.Delete word\n";
        cout << "3.Delete synonym of a word\n";
        cout << "4.Search word\n";
        cout << "5.Print dictionary\n";
        cout << "6.Change misspelling of words\n";
        cout << "7.Save on a file\n";
        cout << "8.Import from file\n";
        cout << "9.Exit\n";

        cin >> inputChoice;
        switch (inputChoice) {

            case 1:
                cout << "Enter your new word: \n";
                cin >> word;
                addWord(head, creatWord(word));
                cout << "Enter count of synonyms you wanna add: \n";
                cin >> countOfSynonyms;

                //if there is no synonym delete the word
                if (countOfSynonyms == 0)deleteWord(head, word);
                for (int i = 0; i < countOfSynonyms; ++i) {
                    cout << "Enter" << i + 1 << "th synonyms you wanna add: \n";
                    cin >> synonym;
                    addSynonym(head, word, creatWord(synonym));
                }
                break;
            case 2:
                cout << "Enter word you wanna delete: \n";
                cin >> word;
                deleteWord(head, word);
                break;
            case 3:
                cout << "Enter the word you want to delete the synonym for: \n";
                cin >> word;
                cout << "Enter the synonym you wanna delete \n";
                cin >> synonym;
                deleteSynonym(head, word, synonym);
                break;
            case 4:
                cout << "Enter word: \n";
                cin >> word;
                searchWord(head, word);
                break;
            case 5:
                printDictionary(head);
                break;
            case 6:
                cout << "Enter the word you wanna change \n";
                cin >> changeWord;
                cout << "Enter the new word\n";
                cin >> word;
                changeMisspelling(head, changeWord, word);
                break;
            case 7:
                cout << "Enter path you wanna save file:\n";
                cin >> path;
                writeOnFile(head, path);
                break;
            case 8:
                cout << "Enter path you wanna import file:\n";
                cin >> path;
                readFromFile(head, path);
                break;
            case 9:
                cout << "Do you want to save file?\n1.Yes 2.No\n";
                cin >> inputChoice;
                switch (inputChoice) {

                    case 1:
                        cout << "Enter path you wanna save file:\n";
                        cin >> path;
                        writeOnFile(head, path);
                        inputChoice = 9;
                        break;
                    case 2:
                        cout << "File not saved!\n";
                        inputChoice = 9;
                        break;
                    default:
                        cout << "Wrong number!\n\n";
                        inputChoice = 0;
                        break;
                }
                break;
            default:
                cout << "Something was wrong!\n------------\n";
                break;
        }
    } while (inputChoice != 9);
    return 0;
}

void printDictionary(Word *&head) {
    Word *current = head;
    Word *currentSyn;
    if (current == nullptr) {

        return;
    }
    cout << " --------------- " << endl;
    while (current != nullptr) {
        cout << "Word : " << current->word << "   Synonyms : ";
        currentSyn = current->synonym;
        while (currentSyn != nullptr) {
            cout << currentSyn->word << " ";
            currentSyn = currentSyn->next;
        }
        cout << endl;
        current = current->next;
    }
    cout << " --------------- " << endl;
}

Word *creatWord(const string &word) {
    Word *temp = new Word;
    temp->word = word;
    temp->next = nullptr;
    temp->synonym = nullptr;
    return temp;
}

void addWord(Word *&head, Word *temp) {
    Word *current;

    // check if linked list is empty   or   new word is smaller than first word
    if (head == nullptr || head->word > temp->word) {
        // add new node to the first
        temp->next = head;
        head = temp;
    } else {
        current = head;
        // Navigation in linked list till new word smaller than next one
        // or arrive to the end
        while (current->next != nullptr && current->next->word < temp->word) {
            current = current->next;
        }
        //add new node
        if (current->word != temp->word) {
            temp->next = current->next;
            current->next = temp;
        }
    }
}

void addSynonym(Word *&head, const string &word, Word *temp) {
    Word *current = head;
    Word *currentSyn;

    // Navigation in synonyms till arrive to purpose word
    while (current->word != word) {
        current = current->next;
    }

    // if synonyms is empty or new synonym is smaller than all synonyms
    if (current->synonym == nullptr || current->synonym->word > temp->word) {
        temp->next = current->synonym;
        current->synonym = temp;
    } else {
        currentSyn = current->synonym;
        // Navigation in synonyms till new word smaller than next one
        // or arrive to the end
        while (currentSyn->next != nullptr && currentSyn->next->word < temp->word) {
            currentSyn = currentSyn->next;
        }
        //add new synonyms
        if (temp->word != currentSyn->word) {
            temp->next = currentSyn->next;
            currentSyn->next = temp;
        }

    }
}

int deleteWord(Word *&head, const string &word) {
    Word *perv = nullptr;
    Word *current = head;
    //if list is empty
    if (head == nullptr) {
        cout << "The word not found!\n\n";
        return 0;
    } else {
        while (current != nullptr) {
            if (current->word == word) { // arrive to purpose word
                if (current == head && head->next == nullptr) { //if dictionary has 1 word
                    head = nullptr;
                } else if (current == head) { // if word is the first and there is more than 1 word in dictionary
                    head = head->next;
                } else if (current->next == nullptr) { // if word is the last word in dictionary
                    perv->next = nullptr;
                } else { // if word is between the first and the last word
                    perv->next = current->next;
                }
                delete current; //delete word and free memory on heap
                cout << "the word and synonyms deleted successfully\n\n";
                return 1;
            }
            perv = current;
            current = current->next;
        }
    }
    cout << "the word not found!\n\n";
    return 0;
}


int deleteSynonym(Word *&head, const string &word, const string &syn) {
    Word *pervSyn = nullptr;
    Word *current = head;

    //if list is empty
    if (current == nullptr) {
        cout << "the synonym not found!\n\n";
        return 0;
    } else {
        while (current->word != word) {
            current = current->next;
        }
        Word *currentSyn = current->synonym;
        while (currentSyn != nullptr) {
            if (currentSyn->word == syn) { // arrive to purpose synonym
                if (currentSyn == current->synonym && currentSyn->next == nullptr) { //if word has 1 synonym
                    current->synonym = nullptr;
                } else if (currentSyn ==
                           current->synonym) { // if synonym is the first and there is more than 1 synonym in dictionary
                    current->synonym = currentSyn->next;
                } else if (currentSyn->next == nullptr) { // if synonym is the last synonym in dictionary
                    pervSyn->next = nullptr;
                } else { // if synonym is between the first and the last synonym
                    pervSyn->next = currentSyn->next;
                }
                delete currentSyn; //delete synonym and free memory on heap
                if (current->synonym == nullptr) { // delete word if there is not any synonym for the word
                    deleteWord(head, word);
                }
                cout << "the synonym deleted successfully\n\n";
                return 1;
            }
            pervSyn = currentSyn;
            currentSyn = currentSyn->next;
        }
    }
    cout << "the synonym not found!\n\n";
    return 0;
}

void searchWord(Word *&head, const string &word) {
    Word *current = head;
    Word *currentSyn;
    while (current->word != word) {
        current = current->next;
        if (current == nullptr) {
            cout << "This word is not in the dictionary!\n\n";
            return;
        }
    }
    // print word and synonyms
    cout << " --------------- " << endl;
    cout << "Word : " << current->word << "   Synonyms : ";
    currentSyn = current->synonym;
    while (currentSyn != nullptr) {
        cout << currentSyn->word << " ";
        currentSyn = currentSyn->next;
    }
    cout << "\n --------------- " << endl;
}

void changeMisspelling(Word *&head, const string &currentWord, const string &newWord) {
    Word *current = head, *current2 = head;
    while (current->word != currentWord) {
        current = current->next;
        if (current == nullptr) {
            cout << currentWord << " is not in the dictionary!\n";
            return;
        }
    }
    //create new word sorted by name
    addWord(head, creatWord(newWord));
    while (current2) {
        if (current2->word == newWord)break;
        current2 = current2->next;
    }
    //link old synonyms to new sorted word
    current2->synonym = current->synonym;
    
    //delete old word
    deleteWord(head, current->word);
}

void writeOnFile(Word *&head, const string &path) {
    ofstream write(path);
    Word *current = head;
    Word *currentSyn;
    if (current == nullptr) {
        return;
    }
    while (current != nullptr) {
        write << current->word << " ";
        currentSyn = current->synonym;
        while (currentSyn != nullptr) {
            write << currentSyn->word << " ";
            currentSyn = currentSyn->next;
        }
        write << endl;
        current = current->next;
    }
    write.close();
}

void readFromFile(Word *&head, const string &path) {
    ifstream read(path);
    string line;
    string word, synonym;
    int length;
    while (!getline(read, line).eof()) {
        if (line == "") continue;
        length = line.length();
        if (line[length - 1] != ' ')line += " "; // add a space at the end of line
        length = line.length();
        int pos = line.find_first_of(' ');


        word = line.substr(0, pos); //specify the first word as main word in dictionary
        pos++;
        int pos2 = pos; // pos2 specify the beginning of each synonym index in string
        addWord(head, creatWord(word)); //add to list

        for (int i = pos; i < length; ++i) {
            //check for space to split words and add synonyms one by one
            if (line[i] == ' ') {
                synonym = line.substr(pos2, i - pos2);
                addSynonym(head, word, creatWord(synonym));
                pos2 = i + 1;
            }
        }
    }
}