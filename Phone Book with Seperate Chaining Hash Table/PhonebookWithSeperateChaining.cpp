#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Node
{
    string number;
    string name;
    Node* next;

    Node(string number, string name, Node* next = nullptr){
        this->number = number;
        this->name = name;
        this->next = next;
    }

    void print(){
        cout << "Phone number: " << number << endl;
        cout << "Contact name: " << name << endl;
    }
};

class SLL
{
private:
    Node* head;
    Node* tail;
    int size;

public:
    SLL(){
        head = tail = nullptr;
        size = 0;
    }

    void insertNode(string number, string name){
        if (size == 0)
        {
            head = tail = new Node(number, name);
            size++;
        }else{
            tail->next = new Node(number, name);
            tail = tail->next;
            size++;
        }
    }

    Node* searchNode(string number){
        Node* temp = head;
        while (temp)
        {
            if(temp->number == number){
                return temp;
            }else{
                temp = temp->next;
            }
        }
        return nullptr;
    }

    void deleteNode(string number){
        if (head == nullptr)
        {
            throw runtime_error("Number not found (Empty list)");
        }
        Node* prev = nullptr;
        Node* temp = head;
        while (temp != nullptr)
        {   
            if(temp->number == number){
                string name = temp->name;
                if (temp == head)
                {
                    delete temp;
                    head = temp->next;
                }else if (temp == tail)
                {
                    delete temp;
                    tail = prev;
                }else{
                    prev->next = temp->next;
                    delete temp;
                }
                cout << "You have successfully deleted " << number << ", " << name << endl;
                return;
            }
            prev = temp;
            temp = temp->next;
        }
        cout << "NUmber not found" << endl;
    }

    void printSLL(){
        if (size == 0)
        {   
            cout << "Empty" << endl;
        }else{
            Node* temp = head;
            while (temp)
            {
                temp->print();
                temp = temp->next;
                cout << endl;
            }
        }       
    }

    bool isEmpty(){
        if(size == 0){
            return true;
        }else{
            return false;
        }
    }
};

void insertContact(const vector<SLL*> &phoneBook, string number, string name){
    try{
        int size = phoneBook.size();
        long long num = stoll(number);
        phoneBook[num%size]->insertNode(number, name);
        cout << "You have successfully inserted " << number << ", " << name << endl;
    }catch(...){
        cout << "Invalid Input" << endl;
    }
}

void deletionContact(const vector<SLL*> &phoneBook, string number){
    try{
        int size = phoneBook.size();
        long long num = stoll(number);
        phoneBook[num%size]->deleteNode(number);
    }catch(...){
        cout << "Invalid Input" << endl;
    }
}

void searchContact(const vector<SLL*> &phoneBook, string number){
    try{
        int size = phoneBook.size();
        long long num = stoll(number);
        Node* temp = phoneBook[num%size]->searchNode(number);
        if (temp == nullptr)
        {
            cout << "Number not found" << endl;
        }else{
            temp->print();
        }
    }catch(...){
        cout << "Invalid Input" << endl;
    }
}

void printAllContacts(const vector<SLL*> &phoneBook){
    for (int i = 0; i < 11; i++)
    {
        cout << "Slot " << i << ":" << endl;
        phoneBook[i]->printSLL();
        cout << "\n";
    }
}

int main(){
    vector<SLL*> phoneBook(11);

    for (int i = 0; i < phoneBook.size(); i++)
    {
        SLL* newList = new SLL();
        phoneBook[i] = newList;
    }
    
    int decision = 0;
    while (decision != 5)
    {
        cout << "Insert contact(1) ; Delete contact(2) ; Search contact(3) ; Print all contacts(4) ; Exit(5)" << endl;
        cout << "Enter your decision: ";
        cin >> decision;

        string number;
        string name;
        switch (decision)
        {
        case 1:
            cout << "Enter the phone number: ";
            cin >> number;
            cout << "Enter the contact name: ";
            cin >> name;
            insertContact(phoneBook, number, name);
            break;
        case 2:
            cout << "Enter your number: ";
            cin >> number;
            deletionContact(phoneBook, number);
            break;
        case 3:
            cout << "Enter your number: ";
            cin >> number;
            searchContact(phoneBook, number);
            break;
        case 4:
            printAllContacts(phoneBook);
            break;
        case 5:
            cout << "Program terminated" << endl;
            break;
        default:
            cout << "Invalid Input!" << endl;
            break;
        }
    }
    return 0;
}