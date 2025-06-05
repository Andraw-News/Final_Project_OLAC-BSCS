#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <chrono>

using namespace std;
using namespace std::chrono;

vector<vector<string>> library;

// Display records
void displayRecords() {
    if (library.empty()) {
        cout << "No records to display.\n";
        return;
    }

    cout << left << setw(20) << "Title" << setw(20) << "Author"
         << setw(6) << "Year" << setw(15) << "Publisher"
         << setw(15) << "ISBN" << setw(15) << "Genre"
         << setw(10) << "Status" << endl;
    cout << string(101, '-') << endl;

    for (auto& rec : library) {
        for (int i = 0; i < 7; ++i)
            cout << setw(i == 2 ? 6 : (i >= 5 ? 15 : 20)) << rec[i];
        cout << endl;
    }
}

// Add record
void addRecord() {
    vector<string> book(7);
    cout << "Enter Title: ";
    getline(cin >> ws, book[0]);

    if (book[0].empty()) {
        cout << "Error: Title cannot be empty.\n";
        return;
    }

    for (auto& rec : library)
        if (rec[0] == book[0]) {
            cout << "Error: Duplicate title.\n";
            return;
        }

    cout << "Enter Author: "; getline(cin, book[1]);
    cout << "Enter Year: "; getline(cin, book[2]);
    cout << "Enter Publisher: "; getline(cin, book[3]);
    cout << "Enter ISBN: "; getline(cin, book[4]);
    cout << "Enter Genre: "; getline(cin, book[5]);
    cout << "Enter Status (Available/Borrowed): "; getline(cin, book[6]);

    library.push_back(book);
    cout << "Book added.\n";
}

// Edit record
void editRecord() {
    displayRecords();
    if (library.empty()) return;

    int i;
    cout << "Enter record number to edit: ";
    cin >> i;

    if (i < 1 || i > library.size()) {
        cout << "Invalid index.\n";
        return;
    }

    vector<string>& book = library[i - 1];
    cout << "Editing Record #" << i << endl;

    cout << "New Title (current: " << book[0] << "): ";
    getline(cin >> ws, book[0]);
    cout << "New Author: "; getline(cin, book[1]);
    cout << "New Year: "; getline(cin, book[2]);
    cout << "New Publisher: "; getline(cin, book[3]);
    cout << "New ISBN: "; getline(cin, book[4]);
    cout << "New Genre: "; getline(cin, book[5]);
    cout << "New Status: "; getline(cin, book[6]);

    cout << "Record updated.\n";
}

// Delete record
void deleteRecord() {
    displayRecords();
    if (library.empty()) return;

    int i;
    cout << "Enter record number to delete: ";
    cin >> i;

    if (i < 1 || i > library.size()) {
        cout << "Invalid index.\n";
        return;
    }

    library.erase(library.begin() + (i - 1));
    cout << "Record deleted.\n";
}

// Search record by title
void searchRecord() {
    cout << "Enter title to search: ";
    string title;
    getline(cin >> ws, title);
    bool found = false;

    for (auto& rec : library) {
        if (rec[0] == title) {
            cout << "Found:\n";
            for (auto& field : rec) cout << field << " | ";
            cout << endl;
            found = true;
        }
    }

    if (!found) cout << "No book found with that title.\n";
}

// Bubble sort
void bubbleSort(int field) {
    int n = library.size();
    for (int i = 0; i < n-1; i++)
        for (int j = 0; j < n-i-1; j++)
            if (library[j][field] > library[j+1][field])
                swap(library[j], library[j+1]);
}

// Selection sort
void selectionSort(int field) {
    int n = library.size();
    for (int i = 0; i < n-1; i++) {
        int minIdx = i;
        for (int j = i+1; j < n; j++)
            if (library[j][field] < library[minIdx][field])
                minIdx = j;
        swap(library[i], library[minIdx]);
    }
}

// Insertion sort
void insertionSort(int field) {
    for (int i = 1; i < library.size(); i++) {
        vector<string> key = library[i];
        int j = i - 1;
        while (j >= 0 && library[j][field] > key[field]) {
            library[j+1] = library[j];
            j--;
        }
        library[j+1] = key;
    }
}

// Quick Sort helpers
int partition(int low, int high, int field) {
    string pivot = library[high][field];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (library[j][field] <= pivot) {
            i++;
            swap(library[i], library[j]);
        }
    }
    swap(library[i+1], library[high]);
    return i+1;
}

void quickSort(int low, int high, int field) {
    if (low < high) {
        int pi = partition(low, high, field);
        quickSort(low, pi-1, field);
        quickSort(pi+1, high, field);
    }
}

// Merge Sort helpers
void merge(int l, int m, int r, int field) {
    int n1 = m - l + 1, n2 = r - m;
    vector<vector<string>> L(n1), R(n2);
    for (int i = 0; i < n1; i++) L[i] = library[l + i];
    for (int i = 0; i < n2; i++) R[i] = library[m + 1 + i];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2)
        library[k++] = (L[i][field] <= R[j][field]) ? L[i++] : R[j++];
    while (i < n1) library[k++] = L[i++];
    while (j < n2) library[k++] = R[j++];
}

void m
