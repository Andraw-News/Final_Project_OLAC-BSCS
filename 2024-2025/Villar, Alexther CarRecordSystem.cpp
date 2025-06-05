#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <cctype>
#include <fstream>
using namespace std;

vector<vector<string>> data;

bool isLettersOnly(const string& str) {
    for (char ch : str) {
        if (!isalpha(ch) && ch != ' ') return false;
    }
    return !str.empty();
}

bool isNumbersOnly(const string& str) {
    for (char ch : str) {
        if (!isdigit(ch)) return false;
    }
    return !str.empty();
}

string toLowerCase(const string& str) {
    string result;
    for (char ch : str) result += tolower(ch);
    return result;
}

bool modelExists(const string& model) {
    for (const auto& row : data) {
        if (toLowerCase(row[0]) == toLowerCase(model)) return true;
    }
    return false;
}

void saveToFile() {
    ofstream file("car_records.txt");
    for (const auto& row : data) {
        file << row[0] << "," << row[1] << "," << row[2] << "\n";
    }
    file.close();
}

void loadFromFile() {
    ifstream file("car_records.txt");
    string line;
    while (getline(file, line)) {
        size_t pos1 = line.find(",");
        size_t pos2 = line.find(",", pos1 + 1);
        if (pos1 != string::npos && pos2 != string::npos) {
            string model = line.substr(0, pos1);
            string year = line.substr(pos1 + 1, pos2 - pos1 - 1);
            string color = line.substr(pos2 + 1);
            data.push_back({model, year, color});
        }
    }
    file.close();
}

void addCar() {
    string model, year, color;
    cin.ignore();

    do {
        cout << "Enter Car Model (letters only): ";
        getline(cin, model);
        if (!isLettersOnly(model)) {
            cout << "❌ Invalid model. Please try again.\n";
        } else if (modelExists(model)) {
            cout << "⚠ Car model already exists. Use a different one.\n";
            model.clear();
        }
    } while (model.empty());

    do {
        cout << "Enter Year (numbers only): ";
        cin >> year;
        if (!isNumbersOnly(year)) cout << "❌ Invalid year. Please try again.\n";
    } while (!isNumbersOnly(year));

    do {
        cout << "Enter Color (letters only): ";
        cin >> color;
        if (!isLettersOnly(color)) cout << "❌ Invalid color. Please try again.\n";
    } while (!isLettersOnly(color));

    data.push_back({model, year, color});
    cout << "✔ Car record added successfully.\n";
    saveToFile();
}

void displayCars() {
    if (data.empty()) {
        cout << "⚠ No car records to display.\n";
        return;
    }
    cout << left << setw(20) << "Model" << setw(10) << "Year" << setw(10) << "Color" << "\n";
    cout << string(40, '-') << "\n";
    for (const auto& row : data) {
        cout << setw(20) << row[0] << setw(10) << row[1] << setw(10) << row[2] << "\n";
    }
    cout << "\nTotal car records: " << data.size() << "\n";
}

void bubbleSort(int field) {
    for (size_t i = 0; i < data.size() - 1; i++) {
        for (size_t j = 0; j < data.size() - i - 1; j++) {
            string a = data[j][field], b = data[j + 1][field];
            if (field == 1) { // Year: pad with zeros
                a = string(4 - a.length(), '0') + a;
                b = string(4 - b.length(), '0') + b;
            }
            if (a > b) swap(data[j], data[j + 1]);
        }
    }
    cout << "✔ Car records sorted using Bubble Sort.\n";
    saveToFile();
}

void sortCars() {
    int field;
    cout << "Sort by:\n1. Model\n2. Year\n3. Color\nChoose (1-3): ";
    cin >> field;
    field--;

    if (field >= 0 && field <= 2) {
        bubbleSort(field);
    } else {
        cout << "❌ Invalid choice. Sort cancelled.\n";
    }
}

void editCar() {
    cin.ignore();
    string model;
    cout << "Enter the car model to edit: ";
    getline(cin, model);

    bool found = false;
    for (auto& row : data) {
        if (toLowerCase(row[0]) == toLowerCase(model)) {
            string year, color;
do {
                cout << "Enter new Year: ";
                cin >> year;
                if (!isNumbersOnly(year)) cout << "❌ Invalid. Please try again.\n";
            } while (!isNumbersOnly(year));

            do {
                cout << "Enter new Color: ";
                cin >> color;
                if (!isLettersOnly(color)) cout << "❌ Invalid. Please try again.\n";
            } while (!isLettersOnly(color));

            row[1] = year;
            row[2] = color;
            cout << "✔ Car record updated successfully.\n";
            found = true;
            saveToFile();
            break;
        }
    }
    if (!found) {
        cout << "⚠ Car model not found.\n";
    }
}

void searchCar() {
    cin.ignore();
    string model;
    cout << "Enter the car model to search: ";
    getline(cin, model);

    bool found = false;
    for (const auto& row : data) {
        if (toLowerCase(row[0]) == toLowerCase(model)) {
            cout << "\n✔ Car found:\n";
            cout << "Model: " << row[0] << "\nYear: " << row[1] << "\nColor: " << row[2] << "\n";
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "⚠ No matching car found.\n";
    }
}

void deleteCar() {
    cin.ignore();
    string model;
    cout << "Enter the car model to delete: ";
    getline(cin, model);

    bool found = false;
    for (auto it = data.begin(); it != data.end(); ++it) {
        if (toLowerCase((*it)[0]) == toLowerCase(model)) {
            char confirm;
            cout << "Are you sure you want to delete " << (*it)[0] << "? (y/n): ";
            cin >> confirm;

            if (tolower(confirm) == 'y') {
                data.erase(it);
                saveToFile();
                cout << "✔ Car deleted successfully.\n";
            } else {
                cout << "✖ Deletion cancelled.\n";
            }
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "⚠ Car model not found.\n";
    }
}

void showMenu() {
    cout << "\n===== CAR RECORD SYSTEM =====\n";
    cout << "1. Add Car Record\n";
    cout << "2. Display All Cars\n";
    cout << "3. Sort Cars\n";
    cout << "4. Edit Car Record\n";
    cout << "5. Search Car\n";
    cout << "6. Delete Car Record\n";
    cout << "7. Exit\n";
    cout << "Choose an option: ";
}

int main() {
    loadFromFile();
    int choice;

    do {
        showMenu();
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: addCar(); break;
            case 2: displayCars(); break;
            case 3: sortCars(); break;
            case 4: editCar(); break;
            case 5: searchCar(); break;
            case 6: deleteCar(); break;
            case 7: cout << "👋 Exiting Car Record System. Goodbye!\n"; break;
            default: cout << "❌ Invalid option. Please try again.\n";
        }

    } while (choice != 7);

    return 0;
}
