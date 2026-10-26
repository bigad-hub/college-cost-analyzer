// This program shall analyze the cost and acceptance rate of top Computer Science colleges across California.
#include "library.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

/*
    load_csv
    Reads california.csv and stores the colleges into an array.
    Returns the number of colleges read.
*/
static unsigned load_csv(const string &filename, College a[], unsigned cap)
{
    ifstream fin(filename); // open the CSV file

    // if file cannot be opened
    if (!fin)
    {
        cout << "Error: could not open " << filename << endl;
        return 0;
    }

    unsigned n = 0; // number of colleges stored
    string line;    // one line from the file

    /*
        Read the file line by line.
        Example line in CSV:
        University of California Irvine,11633,29
    */
    while (getline(fin, line) && n < cap)
    {
        if (line.empty())
            continue; // skip empty lines

        string name, costStr, rateStr;

        // stringstream lets us split the line using commas
        stringstream ss(line);

        // read the 3 parts of the CSV
        if (!getline(ss, name, ','))
            continue;
        if (!getline(ss, costStr, ','))
            continue;
        if (!getline(ss, rateStr))
            continue;

        // store the data into the array
        a[n].name = name;
        a[n].cost = stoi(costStr); // convert string -> integer
        a[n].rate = stoi(rateStr);

        n++; // move to next array position
    }

    return n; // return how many colleges were loaded
}

/*
    copy_array
    Copies one array into another.
    We use this b/s sorting changes the array order,
    but we want to keep the original order.
*/
static void copy_array(const College src[], College dst[], unsigned n)
{
    for (unsigned i = 0; i < n; i++)
        dst[i] = src[i];
}

int main()
{
    const unsigned CAP = 10; // maximum number of colleges allowed

    College list[CAP]; // array that stores the colleges from the CSV

    // load the CSV file into the array
    unsigned n = load_csv("california.csv", list, CAP);

    // if nothing was loaded, stop the program
    if (n == 0)
        return 0;

    // ========================= DISPLAY ORIGINAL DATA =========================
    cout << "=== DISPLAY (Original Data) ===" << endl;

    // call display function from library.cpp
    display(list, n);

    // ========================= SEARCH TESTING =========================
    cout << "\n=== SEARCH TESTING ===\n"
         << endl;

    // search example: first element
    cout << "1) Beginning (rate): University of California Los Angeles" << endl;
    cout << "Result: "
         << search(list, n, "University of California Los Angeles", "rate")
         << endl;

    // search example: middle element
    cout << "\n2) Middle (cost): University of California Irvine" << endl;
    cout << "Result: "
         << search(list, n, "University of California Irvine", "cost")
         << endl;

    // search example: last element
    cout << "\n3) End (rate): University of California San Diego" << endl;
    cout << "Result: "
         << search(list, n, "University of California San Diego", "rate")
         << endl;

    // search example: college not found
    cout << "\n4) Not found (rate): Stanford University" << endl;
    cout << "Result: "
         << search(list, n, "Stanford University", "rate")
         << " (should be negative)" << endl;

    // test both cost and rate categories
    cout << "\n5) Different valid categories (UCLA)" << endl;
    cout << "cost: "
         << search(list, n, "University of California Los Angeles", "cost")
         << endl;

    cout << "rate: " << search(list, n, "University of California Los Angeles", "rate") << endl;

    // invalid category example
    cout << "\n6) Valid college name but invalid category" << endl;
    cout << "Result: " << search(list, n, "University of California Irvine", "tuition") << " (should be negative)" << endl;

    // ========================= SORTING TESTS =========================
    cout << "\n=== SORTING TESTS ===\n"
         << endl;

    College tmp[CAP]; // temporary array used for sorting

    // ----- SORT BY NAME -----
    copy_array(list, tmp, n); // copy original data

    cout << "--- Before sort_by_name ---" << endl;
    display(tmp, n);

    sort_by_name(tmp, n); // insertion sort

    cout << "\n--- After sort_by_name ---" << endl;
    display(tmp, n);

    // ----- SORT BY COST -----
    copy_array(list, tmp, n);

    cout << "\n--- Before sort_by_cost ---" << endl;
    display(tmp, n);

    sort_by_cost(tmp, n); // selection sort

    cout << "\n--- After sort_by_cost ---" << endl;
    display(tmp, n);

    // ----- SORT BY ACCEPTANCE RATE -----
    copy_array(list, tmp, n);

    cout << "\n--- Before sort_by_acceptance ---" << endl;
    display(tmp, n);

    sort_by_acceptance(tmp, n); // bubble sort

    cout << "\n--- After sort_by_acceptance ---" << endl;
    display(tmp, n);

    return 0; // program finished successfully
}
