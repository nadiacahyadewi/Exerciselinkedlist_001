#include <iostream>
#include <string>
using namespace std;

class Node { 
public:
    int rollNumber;
    string name;
    Node* next;
};

class CircularLinkedList {
private:
    Node* LAST;

public:
    CircularLinkedList() {
        LAST = NULL;
    }

    void addNode(); //menambah node
    bool search(int rollno, Node** Nadia, Node** Cahya); //mencari node 
    bool listEmpty(); //mengecek linked list kosong
    bool delNode(); //menghapus node
    void traverse(); //menampilkan semua linked list
};

void CircularLinkedList::addNode() {
    Node* newNode = new Node();
    cout << "\nEnter roll number: ";
    cin >> newNode->rollNumber;
    cout << "Enter name: ";
    cin >> newNode->name;

    if (listEmpty()) { //jika linked list kosong
        newNode->next = newNode;
        LAST = newNode;
    }
    else { //linked list tidak kosong
        Node* nadia = LAST->next;
        Node* cahya = NULL;

        do { 
            cahya = nadia;
            nadia = nadia->next;
        } while (nadia != LAST->next && nadia->rollNumber < newNode->rollNumber);

        cahya->next = newNode;
        newNode->next = nadia;

        if (nadia == LAST->next) {  //memasukan awal
            LAST->next = newNode;
        }
        if (nadia == LAST) { //memasukan akhir
            LAST = newNode;
        }
    }

    cout << "Node added successfully!" << endl;
}

bool CircularLinkedList::search(int rollno, Node** cahya, Node** nadia) {
    *cahya = LAST->next;
    *nadia = LAST->next;

    while (*nadia != LAST) {
        if (rollno == (*nadia)->rollNumber) {
            return true;
        }
        *cahya = *nadia;
        *nadia = (*nadia)->next;
    }

    if (rollno == LAST->rollNumber) {
        return true;
    }
    else {
        return false;
    }
}

bool CircularLinkedList::listEmpty() {
    return LAST == NULL;
}

bool CircularLinkedList::delNode() {
    if (listEmpty()) {
        cout << "\nList is empty. Deletion failed!" << endl;
        return false;
    }

    int rollno;
    cout << "\nEnter roll number to delete: ";
    cin >> rollno;

    Node* cahya = NULL;
    Node* nadia = NULL;

    if (!search(rollno, &cahya, &nadia)) { //jika mencari node
        cout << "Node not found. Deletion failed!" << endl; //hasil pencarian gagal
        return false;
    }

    if (cahya == nadia) { //jika hanya satu node di linkedlist
        LAST = NULL;
        delete nadia; //menghapus salh satu node
        cout << "Node deleted successfully!" << endl; //menghapus node berhasil
        return true;
    }

    if (nadia == LAST) { 
        LAST = cahya;
    }

    cahya->next = nadia->next;
    delete nadia;

    cout << "Node deleted successfully!" << endl;
    return true;
}

void CircularLinkedList::traverse() { 
    if (listEmpty()) { //memeriksa list 
        cout << "\nList is empty\n"; 
    }
    else { 
        cout << "\nRecords in the list are:\n"; //merekam semua list
        Node* nadiaNode = LAST->next;

        while (nadiaNode != LAST) {
            cout << nadiaNode->rollNumber << " " << nadiaNode->name << endl;
            nadiaNode = nadiaNode->next;
        }

        cout << LAST->rollNumber << " " << LAST->name << endl;
    }
}

int main() {
    CircularLinkedList obj;

    while (true) {
        try {
            cout << "\nMenu" << endl;
            cout << "1. Add a record to the list" << endl;
            cout << "2. Delete a record from the list" << endl;
            cout << "3. View all the records in the list" << endl;
            cout << "4. Exit" << endl;
            cout << "\nEnter your choice (1-5): ";
            char ch;
            cin >> ch;

            switch (ch) {
            case '1': {
                obj.addNode();
                break;
            }
            case '2': {
                obj.delNode();
                break;
            }
            case '3': {
                obj.traverse();
                break;
            }
            case '4': {
                return 0;
            }
            default: {
                cout << "Invalid option" << endl;
                break;
            }
            }
        }
        catch (exception& e) {
            cout << e.what() << endl;
        }
    }

    return 0;
}