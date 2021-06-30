/*
This is a simple console program created for pure beginner experimenting on [C++ References] and [File I/O].
This program allows the user to enter string data into an array and can check the #of elements, and data in the array.
[data type don't neccessarily need to be array]
*/


#include <iostream>
#include <unistd.h>
#include <conio.h>
#include <fstream>

using namespace std;

const int MAX_NAMES = 10; // Max names which can be contained in the namelist. (array)
const string FILE_NAME = "STORE.txt"; // Elements of the array are stored in this text file row-wise.

// Finds and updates the count of the non-null elements in an string array.
int find_update_num_of_elements(string namelist[], int& num_of_people) {

    num_of_people = 0;

    for (int i=0; i<MAX_NAMES; i++) {
        if (namelist[i] != "") {
            num_of_people++;
        }
    }
    return num_of_people;
}

// Append an element to the string array.
void add_element(string namelist[], int& num_of_people) {

    if (num_of_people == MAX_NAMES) {
            cout << "\nCannot enter more names [capacity reached]\nIf you wish to enter more names please format " << FILE_NAME << " and restart app." << endl; 
            cout << "Or just delete " << FILE_NAME << endl;
            return;
        }

    cin.ignore();
    string input_name;
    cout << "\nEnter name to be appended to the name list: ";
    getline(cin, input_name);

    if (input_name != "") {

        for (int i = -1; i<num_of_people; i++) {
            
            if (i+1 == num_of_people) {
                namelist[num_of_people] = input_name; // Added the element to the last availabe index in array namelist.
                cout << "Element '" << input_name << "' added to namelist successfully.\n" << endl;
            }
        }

        num_of_people++;

        // Storing data to file so that it can be used to read and load data from previous sessions. (making the RAM effect a ROM effect)
        ofstream writer;
        writer.open(FILE_NAME, ios::app);
        
        for (int i=0; i < num_of_people; i++) {

            if (i+1 == num_of_people) {

                writer << namelist[i] << endl;
            }
        }
        writer.close();
    } else {
        cout << "\n------Value entered CANNOT BE 'NULL'!------\n" << endl;
    }
    return ;
}

// Displays the elements of a string array.
void display_elements(string namelist[], int& num_of_people) {

    cout << "Elements:" << endl;
    for (int i=0; i < num_of_people; i++) {
        cout << "\t\t " <<namelist[i] << endl;
    }
    cout << "\n";
}

void read_data(string namelist[], int& num_of_people) {

    ifstream reader;
    reader.open(FILE_NAME);
    
    if (reader.fail()) {
        cout << "ERROR! FILE WAS NOT CREATED" << endl;
    } else {
        int i = 0;
        string test;
        while (!(reader.eof()) && i < MAX_NAMES) {
            getline(reader, test);
            if (test != "") {
                namelist[i] = test;
                i++;
            }
        }
        num_of_people = i;
    }
    reader.close();

}


int main() {

    string namelist[MAX_NAMES];
    int num_of_people;
    
    read_data(namelist, num_of_people);

    if (num_of_people == MAX_NAMES) {
        
        cout << "\n------------------------------------------------------------------\nCannot enter more names [capacity reached]\nIf you wish to enter more names please delete " << FILE_NAME << " and restart app." << endl; 
        cout << "\nPress ANY CHAR to EXIT app :";
        getch();
        system("cls");
        cout << "\n\n\n\n\n--------     Application Closed.    ---------------" << endl;
        sleep(1);

        return 0;
    }

    int choice = 10;

    while (choice != 0) {
        
        cout << "\nEnter # - ?\n" << endl;
        cout << "      1 - ADD ELEMENT                                      "<< MAX_NAMES - num_of_people  << " free slots."<< endl;
        cout << "      2 - DISPLAY ALL ELEMENT" << endl;
        cout << "      3 - DISPLAY CURRENT #OF ELEMENTS" << endl;
        cout << "      0 - EXIT APP" << endl;
        cout << "\nEnter choice: ";
        cin >> choice;
        cout << "\n\n";
        
        switch (choice) {
            
            case 1:
                add_element(namelist, num_of_people);
                break;
            case 2:
                display_elements(namelist, num_of_people);
                break;
            case 3:
                cout << "Current #of elements in array: " << find_update_num_of_elements(namelist, num_of_people) << endl;
                break;
            case 0:
                cout << "Application Closed." << endl;
                sleep(1);
                exit(0);
                // EXITS APP.
                break;
            default:
                cout << "Enter Valid Input Please." << endl;
                break;
        }

        cout << "\nPlease enter any character to carry on: ";
        getch();
        system("cls");    
    }

    cout << "Application Closed." << endl;
    sleep(1);


    return 0;
}