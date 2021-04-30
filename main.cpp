#include <iostream>

using namespace std;
struct Word {
    string word;
    Word *next;
    Word *synonym;
};

// print link list
void printLinkedList(Word *head);

// creat word prototype
Word *creatWord(const string &word);

// add created word in a linked list
void addWord(Word *&head, Word *temp);


int main() {
    return 0;
}

void printLinkedList(Word *head) {
    while (head != nullptr) {
        cout << head->word << endl;
        head = head->next;
    }
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