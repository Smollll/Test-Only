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
void exit();
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
    ifstream showPersons("medicine.txt");
    string dtype, dname, bname, dprice, dadd, edate;
    int qua, recno , totalrec = 0;
    system("CLS");
    cout << "Entire database: " << endl;
    cout << "_____________________________________________________________________________________________________________________________________________________________" << endl;
    cout << "  | Drug ID |  Drug Type        | Drug Name       |  Brand Name        |    Available Stock     |     Drug Price      | Date Added |     Expiration Date   |  " << " " << endl;
    cout << "-------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    while (showPersons >> recno >> dtype >> dname >> bname >> qua >> dprice >> dadd >> edate) {
        dtype = replaceto(dtype, '_', ' ');
        dname = replaceto(dname, '_', ' ');
        bname = replaceto(bname, '_', ' ');
        cout << "   |" << padTo(to_string(recno), 3) << " " << padTo("|" + dtype , 20) << " " << padTo("|" + dname, 20) << " "
            << padTo("|" + bname, 20) << " " << padTo("|" + to_string(qua), 10) << " " << padTo("|" + dprice, 10 )<< " " << padTo("|" + dadd, 10) << " " << padTo("|" + edate, 10) << endl;
        cout << "---------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
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
    ofstream newrec("medicine.txt", ios::app); //medicine.txt  text file or flat file, DATABASE
    ifstream recread("medicine.txt");
    string newdtype, newdname, newbname, newdprice, newdadd, newedate;
    string dtype, lname, dname, bname, dprice, dadd, edate;
    int recno = 0, qua, newqua, totalrec = 1, newrecno;
    while (recread >> recno >> dtype >> dname >> bname >> qua >> dprice >> dadd >> edate) {
        totalrec++;
    }
    recread.close();

    system("cls");
    cout << "\tEnter Medicine Type: ";
    cin.sync();
    getline(cin, newdtype);
    cout << "\tEnter Medicine Name: ";
    getline(cin, newdname);
    cout << "\tEnter Brand Name: ";
    getline(cin, newbname);
    cout << "\tHow many Would you like to put: ";
    cin >> newqua;
    cout << "\tEnter Price: ";
    getline(cin, newdprice);
    cout << "\tEnter Date Added: ";
    getline(cin, newdadd);
    cout << "\tEnter Expiration Date: ";
    getline(cin, newedate);
    system("cls");
    //replace
    newdtype = replaceto(newdtype, '_', ' ');
    newdname = replaceto(newdname, '_', ' ');
    newbname = replaceto(newbname, '_', ' ');
    newrecno = totalrec++;
    newrec << "\n" << newrecno << ' ' << newdtype << ' ' << newdname << ' ' << newbname<< ' ' << newqua << ' ' << newdprice << ' ' << newdadd  << ' ' << newedate;
    newrec.close();
    system("pause");
    mainScreen();
}

void editfile() {
    int recno, input, qua, newqua;
    string editdadd, dadd;
    string editdprice, dprice;
    string editedate, edate;
    string editdtype;
    string editdname, editbname;
    string newdtype, newdname, newbname, newdprice, newdadd, newedate;

    ifstream editperson("medicine.txt", ios::in);
    ofstream writetemp("temMedicine.txt");
    dispRec();
    cout << "\n\tEnter no of record to update:";
    cin >> input;
    cout << "\tEnter New Medicine Type: ";
    cin.sync();
    getline(cin, newdtype);
    cout << "\tEnter New Medicine Name: ";
    getline(cin, newdname);
    cout << "\tEnter New Brand Name: ";
    getline(cin, newbname);
    cout << "\tEdit how many would you like to put: ";
    cin >> newqua;
    cout << "\tEnter Price ";
    getline(cin, newdprice);
    cout << "\tEnter New Date Added: ";
    getline(cin,newdadd);
    cout << "\tEnter New Expiration Date: ";
    getline(cin,newedate);
    newdtype = replaceto(newdtype, '_', ' ');
    newdname = replaceto(newdname, '_', ' ');
    newbname = replaceto(newbname, '_', ' ');
    while (!editperson.eof()) {
        editperson >> recno >> editdtype >> editdname >> editbname >> qua >> editdprice >> editdadd >> newedate;
        if (recno == input) {

            writetemp << "\n" << recno << " " << newdtype << " " << newdname << " " << newbname << " " << newqua << " " << newdprice << " " << newdadd << " " << newedate;
        }
        else {
            writetemp << "\n" << recno << " " << editdtype << " " << editdname << " " << editbname << " " << qua<< " " << editdprice << " " << editdadd << " " << editedate;
        }
    }
    editperson.close();
    writetemp.close();
    ifstream editperson2("temMedicine.txt", ios::in);
    ofstream writetemp2("medicine.txt");
    while (!editperson2.eof()) {
        editperson2 >> recno >>  editdtype >> editdname >> editbname >> qua >> editdprice >> editdadd >> editedate;
        writetemp2 << "\n" << recno << " " << editdtype << " " << editdname << " " << editbname << " " << qua<< " " << editdprice << " " << editdadd << " " << editedate;
    }
    editperson2.close();
    writetemp2.close();
    mainScreen();
}

void deleteitem() {
    dispRec();
    ifstream delperson("medicine.txt");
    ofstream writetemp("temMedicine.txt");
    string deldtype, deldname, delbname, deldprice, deldadd, deledate;
    int input, qua, recno, recnew = 1;
    if (delperson.good()) {
        cout << "Enter no. to delete:";
        cin >> input;
        while (delperson >> recno >>  deldtype >> deldname >> delbname >> qua >> deldprice >> deldadd >> deledate) {
            if (input != recno) {
                int rc = recnew++;
                writetemp << "\n" << rc << " " <<  deldtype << " " << deldname << " " << delbname << " " << qua << " " << deldprice << " " << deldadd << " " << deledate;
            }
        }
    }
    else {
        cout << "item not found" << endl;
    }
    delperson.close();
    writetemp.close();
    ifstream delperson2("temMedicine.txt", ios::in);
    ofstream writetemp2("medicine.txt");
    while (!delperson2.eof()) {
        delperson2 >> recno >> deldtype >> deldname >> delbname >> qua >> deldprice >> deldadd >> deledate;
        writetemp2 << "\n" << recno << " " << deldtype << " " << deldname << " " << delbname << " " << qua<< " " << deldprice << " " << deldadd << " " << deledate;
    }
    delperson2.close();
    writetemp2.close();
    dispAll();
}

void exit ()
{
	cout << "\nThank You!\n" << endl;
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
    case 1: dispAll(); break;
    case 2: newEmployee(); break;
    case 3: editfile(); break;
    case 4: deleteitem(); break;
    case 5: exit(); break;
    }
	return 0;
}
