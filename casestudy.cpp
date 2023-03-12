#include <iostream>
#include <string>
#include <fstream> //Reading and Writing  ifstream
#include <cstdio>
#include <cstdlib>
//CRUD   Create, Read, Update, Delete
using namespace std;
int mainScreen(); //Prototype Function
void dispRec();
void dispAll();
void newEmployee();
string replaceto(string text, char frm, char to);

int main() { mainScreen(); } //Function Driver

string replaceto(string text, char frm, char to) {
    for (int i = 0; i < text.length(); i++) {
        string newtext;
        if (text[i] == frm) {
            text[i] = to;
        }
    }
    return text;
}

string padTo(string str, const size_t num, const char paddingChar = ' ') {
    int str_size = str.size();
    for (int i = str_size; i <= num; i++) {
        str = str + paddingChar;
    }
    return str;
}

void dispRec() {
    ifstream showPersons("persons.txt");
    string fname, mname, lname;
    int age, recno, totalrec = 0;
    system("CLS");
    cout << "Entire database: " << endl;
    cout << "   _________________________________________________________________________________" << endl;
    cout << "   | No. |First Name           |Middle Name          |Last Name            |Age    |" << " " << endl;
    cout << "   ---------------------------------------------------------------------------------" << endl;
    while (showPersons >> recno >> fname >> mname >> lname >> age) {
        fname = replaceto(fname, '_', ' ');
        mname = replaceto(mname, '_', ' ');
        lname = replaceto(lname, '_', ' ');
        cout << "   |" << padTo(to_string(recno), 3) << " " << padTo("|" + fname, 20) << " " << padTo("|" + mname, 20) << " "
            << padTo("|" + lname, 20) << " " << padTo("|" + to_string(age), 3) << "    |" << endl;
        cout << "   ---------------------------------------------------------------------------------" << endl;
        totalrec++;
    }
    cout << "\ntotal rec: " << totalrec << endl;
}

void dispAll() {
    dispRec();
    system("pause");
    cin.get();
    mainScreen();
}

void newEmployee() {
    ofstream newrec("persons.txt", ios::app); //person.txt  text file or flat file, DATABASE
    ifstream recread("persons.txt");
    string newfname, newlname, newmname;
    string fname, lname, mname;
    int recno = 0, age, newage, totalrec = 1, newrecno;
    while (recread >> recno >> fname >> mname >> lname >> age) {
        totalrec++;
    }
    recread.close();

    system("cls");
    cout << "\tEnter first name: ";
    cin.sync();
    getline(cin, newfname);
    cout << "\tEnter middle name: ";
    getline(cin, newmname);
    cout << "\tEnter last name: ";
    getline(cin, newlname);
    cout << "\tEnter age: ";
    cin >> newage;
    system("cls");
    //replace
    newfname = replaceto(newfname, ' ', '_');
    newmname = replaceto(newmname, ' ', '_');
    newlname = replaceto(newlname, ' ', '_');
    newrecno = totalrec++;
    newrec << "\n" << newrecno << ' ' << newfname << ' ' << newmname << ' ' << newlname << ' ' << newage;
    newrec.close();
    system("pause");
    mainScreen();
}

void editfile() {
    int recno, input, age, newage;
    string editfname;
    string editlname, editmname;
    string newfname, newlname, newmname;

    ifstream editperson("persons.txt", ios::in);
    ofstream writetemp("temPersons.txt");
    dispRec();
    cout << "\n\tEnter no of record to update:";
    cin >> input;
    cout << "\tEnter New First Name: ";
    
    getline(cin, newfname);
    cout << "\tEnter new Middle Name: ";
    getline(cin, newmname);
    cout << "\tEnter new Last nName: ";
    getline(cin, newlname);
    cout << "\tEnter Age: ";
    cin >> newage;
    newfname = replaceto(newfname, ' ', '_');
    newmname = replaceto(newmname, ' ', '_');
    newlname = replaceto(newlname, ' ', '_');
    while (!editperson.eof()) {
        editperson >> recno >> editfname >> editmname >> editlname >> age;
        if (recno == input) {

            writetemp << "\n" << recno << " " << newfname << " " << newmname << " " << newlname << " " << newage;
        }
        else {
            writetemp << "\n" << recno << " " << editfname << " " << editmname << " " << editlname << " " << age;
        }
    }
    editperson.close();
    writetemp.close();
    ifstream editperson2("temPersons.txt", ios::in);
    ofstream writetemp2("persons.txt");
    while (!editperson2.eof()) {
        editperson2 >> recno >> editfname >> editmname >> editlname >> age;
        writetemp2 << "\n" << recno << " " << editfname << " " << editmname << " " << editlname << " " << age;
    }
    editperson2.close();
    writetemp2.close();
    mainScreen();
}

void deleteitem() {
    dispRec();
    ifstream delperson("persons.txt");
    ofstream writetemp("temPersons.txt");
    string delfname, dellname, delmname;
    int input, age, recno, recnew = 1;
    if (delperson.good()) {
        cout << "Enter no to delete:";
        cin >> input;
        while (delperson >> recno >> delfname >> delmname >> dellname >> age) {
            if (input != recno) {
                int rc = recnew++;
                writetemp << "\n" << rc << " " << delfname << " " << delmname << " " << dellname << " " << age;
            }
        }
    }
    else {
        cout << "item not found" << endl;
    }
    delperson.close();
    writetemp.close();
    ifstream delperson2("temPersons.txt", ios::in);
    ofstream writetemp2("persons.txt");
    while (!delperson2.eof()) {
        delperson2 >> recno >> delfname >> delmname >> dellname >> age;
        writetemp2 << "\n" << recno << " " << delfname << " " << delmname << " " << dellname << " " << age;
    }
    delperson2.close();
    writetemp2.close();
    dispAll();
}
int mainScreen() {
    string nem, lnem;
    system("cls");
    int choice;
    cout << "\t\t==================================================\n";
    cout << "\t\t\t      Medicine Management System \n";
    cout << "\t\t==================================================\n\n";
    cout << "\t\t--------------------------------------------------\n";
    cout << "\t\t||\t1. Available Medicine \t\t\t||\n";
    cout << "\t\t||\t2. Add new Medicine \t\t\t||\n";
    cout << "\t\t||\t3. Edit  \t\t\t\t||\n";
    cout << "\t\t||\t4. Delete  \t\t\t\t||\n";
    cout << "\t\t||\t5. Exit \t\t\t\t||\n";
    cout << "\t\t--------------------------------------------------\n";
    cout << "Enter choice: ";
    cin >> choice;
    switch (choice) {
    case 1: newEmployee(); break;
    case 2: dispAll(); break;
    case 3: editfile(); break;
    case 4: deleteitem(); break;
    }
    return 0;
}
