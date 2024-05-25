#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Handbook {
private:
    string filename = "spravochnik.txt";

public:
    void addRecord(string companyName, string owner, string telephone, string address, string occupation) {
        ofstream file(filename, ios_base::app);
        file << companyName << ", " << owner << ", " << telephone << ", " << address << ", " << occupation << endl << endl;
        file.close();
        cout << "Entry added successfully" << endl;
    }

    void searchByName(string companyName) {
        ifstream file(filename);
        string line;
        while (getline(file, line)) {
            size_t pos = line.find(companyName);
            if (pos != string::npos) {
                cout <<"Company found: " << endl << line << endl;
            }

        }
        file.close();
    }

    void searchByOwner(string owner) {
        ifstream file(filename);
        string line;
        while (getline(file, line)) {
            size_t pos = line.find(owner);
            if (pos != string::npos) {
                cout <<"Name found: " << endl << line << endl;
            }
      
        }
        file.close();
    }

    void searchByPhoneNumber(string telephone) {
        ifstream file(filename);
        string line;
        while (std::getline(file, line)) {
            size_t pos = line.find(telephone);
            if (pos != string::npos) {
                cout << "Telephone found: " << endl << line << endl;
            }
    
        }
        file.close();
    }

    void searchByActivity(string occupation) {
        ifstream file(filename);
        string line;
        while (getline(file, line)) {
            size_t pos = line.find(occupation);
            if (pos != string::npos) {
                cout << "Occupation found: " << endl << line << endl;
            }
            
        }
        file.close();
    }

    void showAllRecords() {
        ifstream file(filename);
        string line;
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    }
};

int main() {

    setlocale(LC_ALL, "Russian");
    string comp, name, number, address, occupation;

    Handbook sprav;
    /*sprav.addRecord("Massivesoft", "Alishque", "555-54-81", "Redmond, Washington 98052-6399", "Co-founder");
    sprav.addRecord("Ashot's Kebab House", "Ashot", "777-84-90", "Krasnodarskiy kray, Sochi", "CEO");*/
    
    while (true) {
        cout << "It's time to choose: " << endl;
        cout << "1.Search by company name" << endl;
        cout << "2.Search by owner name" << endl;
        cout << "3.Search by telephone number" << endl;
        cout << "4.Search by occupation in company" << endl;
        cout << "5.Show all records" << endl;
        cout << "6.Add new entry" << endl;
        

        int choice;
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "Input company name:" << endl;
            cin >> comp;
            sprav.searchByName(comp);
            continue;
        case 2:
            cout << "Input owner name:" << endl;
            cin >> name;
            sprav.searchByOwner(name);
            continue;
        case 3:
            cout << "Input phone number:" << endl;
            cin >> number;
            sprav.searchByPhoneNumber(number);
            continue;
        case 4:
            cout << "Input occupation: " << endl;
            cin >> occupation;
            sprav.searchByActivity(occupation);
            continue;
        case 5:
            cout << "Showing all records:" << endl;
            sprav.showAllRecords();
            continue;
        case 6:
          cout << "Input company name:";
        getline(cin.ignore(), comp);
        
        cout << "Input owner name:";
        getline(cin, name);
      
        cout << "Input number:";
        getline(cin, number);
     
        cout << "Input address:";
        getline(cin, address);
       
        cout << "Input occupation:";
        getline(cin, occupation);
        
        sprav.addRecord(comp, name, number, address, occupation);
            continue;
        default:
            cout << "entrada incorrecta, try again" << endl;
            continue;
        }
        return 0;
   }
  
}

