#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;
#define RESET   "\033[0m"
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
struct Person {
    char gender;
    string orientation;
};
bool milgya;
int counter = -1;
long long int factorial = 0;
bool Safe(vector<vector<Person>>& matrix, Person person, int i, int j) {
    try {
        if (counter <= factorial) {
            if (i < 0 || i >= matrix.size() || j < 0 || j >= matrix[0].size() || matrix[i][j].gender != ' ') {
                return false;
            }
            char currentGender = person.gender;
            string currentOrientation = person.orientation;
            if (i > 0 && (matrix[i - 1][j].gender == currentGender || matrix[i - 1][j].orientation == currentOrientation)) {
                return false;
            }
            if (i < matrix.size() - 1 && (matrix[i + 1][j].gender == currentGender || matrix[i + 1][j].orientation == currentOrientation)) {
                return false;
            }
            if (j > 0 && (matrix[i][j - 1].gender == currentGender || matrix[i][j - 1].orientation == currentOrientation)) {
                return false;
            }
            if (j < matrix[0].size() - 1 && (matrix[i][j + 1].gender == currentGender || matrix[i][j + 1].orientation == currentOrientation)) {
                return false;
            }
            else {
                throw exception();
            }
            return true;
            /* if (matrix[i][j].gender != ' ') {
                  return false;
              }
              char currentGender = person.gender;
              string currentOrientation = person.orientation;
              if (i > 0 && matrix[i - 1][j].gender == currentGender && matrix[i - 1][j].orientation == currentOrientation) {
                  return false;
              }
              if (i < matrix.size() - 1 && matrix[i + 1][j].gender == currentGender && matrix[i + 1][j].orientation == currentOrientation) {
                  return false;
              }
              if (j > 0 && matrix[i][j - 1].gender == currentGender && matrix[i][j - 1].orientation == currentOrientation) {
                  return false;
              }
              if (j < matrix[0].size() - 1 && matrix[i][j + 1].gender == currentGender && matrix[i][j + 1].orientation == currentOrientation) {
                  return false;
              }
              return true;*/
        }
    }
    catch (exception e) {
        cout << RED << "No arrangement found " << RESET << endl;
        exit(0);
    }
}

bool arrangementOfPeople(vector<vector<Person>>& matrix, vector<Person>& people, int index) {
    if (index == people.size())
        return true;
    Person currentPerson = people[index];
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[0].size(); j++) {
            try {
                counter++;
                if (matrix[i][j].gender == ' ' && Safe(matrix, currentPerson, i, j)) {
                    matrix[i][j] = currentPerson;
                    if (arrangementOfPeople(matrix, people, index + 1))
                        return true;
                    milgya = true;
                    matrix[i][j] = { ' ', " " };
                }
            }
            catch (const exception e) {
                cout << "Error occured " << endl;;
                return false;
            }
        }
    }
    milgya = false;
    return false;
}
long long fact(int num) {
    long long product = 1;
    for (int i = 1; i <= num; i++) {
        product = product * i;
    }
    return product;
}
int main() {
    ifstream rdr("people.txt");
    string str;
    vector<Person> people;
    while (getline(rdr, str)) {
        stringstream ss(str);
        string t;
        bool isGender = true;
        Person p;
        while (getline(ss, t, ',')) {
            if (isGender) {
                p.gender = t[0];
                isGender = false;
            }
            else {
                p.orientation = t;
                people.push_back(p);
                isGender = true;
            }
        }
    }
    factorial = fact(people.size());
    //cout<<fact(people.size())<<endl;
    cout << YELLOW << "Size is " << people.size() << endl << RESET;
    int numRows = 2;
    int numCols = 3;
    cout << CYAN << "Enter Rows " << RESET;
    cin >> numRows;
    while (numRows <= 0) {
        cout << RED << "Enter correct rows " << RESET;
        cin >> numRows;
    }
    cout << CYAN << "Enter cols " << RESET;
    cin >> numCols;
    while (numRows <= 0) {
        cout << RED << "Enter correct cols " << RESET;
        cin >> numCols;
    }
    while (numRows * numCols != people.size()) {
        cout << RED << "Rows x Cols dont match the size" << endl << RESET << CYAN << "Enter Rows " << RESET;
        cin >> numRows;
        cout << CYAN << "Enter cols " << RESET;
        cin >> numCols;
        while (numRows <= 0) {
            cout << RED << "Enter correct rows " << RESET;
            cin >> numRows;
        }
        while (numRows <= 0) {
            cout << RED << "Enter correct cols " << RESET;
            cin >> numCols;
        }
    }
    vector<vector<Person>> matrix(numRows, vector<Person>(numCols, { ' ', " " }));
    bool result = arrangementOfPeople(matrix, people, 0);
    if (result) {
        cout << GREEN << "Arrangement successful!" << RESET << endl;
        for (int i = 0; i < numRows; i++) {
            for (int j = 0; j < numCols; j++) {
                cout << YELLOW << "(" << CYAN << matrix[i][j].gender << RESET "," << CYAN << matrix[i][j].orientation << YELLOW << ") " << RESET;
            }
            cout << endl;
        }
    }
    else {
        cout << RED << "No valid arrangement found." << RESET << endl;
    }
}