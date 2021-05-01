#include <iostream>

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


int main() {
    Word *head = nullptr;


    return 0;
}

void printDictionary(Word *&head) {
    Word *current = head;
    Word *currentSyn;
    cout << " --------------- " << endl;
    while (current != nullptr) {
        cout << current->word << " : ";
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
    if (head == nullptr || head->word >= temp->word) {
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
        temp->next = current->next;
        current->next = temp;
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
    if (current->synonym == nullptr || current->synonym->word >= temp->word) {
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
        temp->next = currentSyn->next;
        currentSyn->next = temp;
    }
}
