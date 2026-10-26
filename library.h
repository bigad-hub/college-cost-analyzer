#ifndef LIBRARY_H
#define LIBRARY_H

#include <string>
using std::string;

// One college record from california.csv 

struct College
{
    string name; // college name 
    int cost;    // average cost after aid 
    int rate;    // acceptance rate (%) 
};

// Prints table of first n colleges + summary (min/max/avg cost) 
void display(const College a[], unsigned n);

/*
    Search by college name + category:
    category = "cost" or "rate"
    returns value, or -1 if not found / invalid category
*/
int search(const College a[], unsigned n, string name, string category);

// Sort first n colleges (must be 3 different algorithms) 

void sort_by_name(College a[], unsigned n);        // insertion sort (A->Z) 
void sort_by_cost(College a[], unsigned n);        // selection sort (high->low) 
void sort_by_acceptance(College a[], unsigned n);  // bubble sort (low->high) 

#endif