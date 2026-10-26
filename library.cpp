// Add your function definitions here
#include "library.h"
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

/*
    Helper function: swap two College objects.
    We use this in sorting.
*/
static void swap_college(College &x, College &y)
{
    College temp = x;
    x = y;
    y = temp;
}

void display(const College a[], unsigned n)
{
    // If there is no data, nothing to show
    if (n == 0)
    {
        cout << "No data to display." << endl;
        return;
    }

    /*
        These widths control the table format.
        Adjust these if we want tighter/wider spacing.
        IMPORTANT: No tabs; use setw() formatting.
    */
    const int NAME_W = 40;
    const int COST_W = 12;
    const int RATE_W = 18;

    // Print header row
    cout << left << setw(NAME_W) << "College"
         << right << setw(COST_W) << "Cost"
         << right << setw(RATE_W) << "Acceptance rate" << endl;

    // Print a separator line
    cout << string(NAME_W + COST_W + RATE_W, '=') << endl;

    /*
        We calculate summary stats while we print the rows:
        - minCost/minName: least expensive
        - maxCost/maxName: most expensive
        -- sum: used for average
    */
    int minCost = a[0].cost, maxCost = a[0].cost;
    string minName = a[0].name, maxName = a[0].name;
    long long sum = 0;

    /* Print each college row */
    for (unsigned i = 0; i < n; i++)
    {
        /*
            - name is left aligned
            - cost has $ aligned (we print " $" then the number)
            - rate has % aligned
        */
        cout << left << setw(NAME_W) << a[i].name
             << right << " $" << setw(COST_W - 2) << a[i].cost
             << right << setw(RATE_W - 1) << a[i].rate << "%" << endl;

        // Add to sum for average calculation
        sum += a[i].cost;

        // Check for new minimum cost
        if (a[i].cost < minCost)
        {
            minCost = a[i].cost;
            minName = a[i].name;
        }

        // Check for new maximum cost
        if (a[i].cost > maxCost)
        {
            maxCost = a[i].cost;
            maxName = a[i].name;
        }
    }

    // Print bottom separator line
    cout << string(NAME_W + COST_W + RATE_W, '=') << endl;

    // Average cost = sum / n (convert to double to keep decimals)
    double avg = static_cast<double>(sum) / n;

    // Print summary results
    cout << "The most expensive university is: " << maxName << "\n\n";
    cout << "The least expensive university is: " << minName << endl;

    /*
        fixed + setprecision(2):
        - fixed forces decimals
        - setprecision(2) prints exactly 2 digits after decimal point
    */
    cout << fixed << setprecision(2);
    cout << "The average cost in California is: $" << avg << "\n\n";
}

int search(const College a[], unsigned n, string name, string category)
{
    /*
        Only two valid categories based on project instructions:
        "cost" -> return a[i].cost
        "rate" -> return a[i].rate

        If category is invalid, return -1.
    */
    if (category != "cost" && category != "rate")
    {
        return -1;
    }

    /*
        Linear search:
        Walk through the array from 0 to n-1 and compare names.
    */
    for (unsigned i = 0; i < n; i++)
    {
        if (a[i].name == name)
        {
            if (category == "cost")
                return a[i].cost;
            return a[i].rate; // category == rate
        }
    }

    // Not found
    return -1;
}

/*
    sort_by_name uses: INSERTION SORT
    - Builds a sorted left part of the array
    - Inserts each new element into the correct position
    Sorting: alphabetical A - Z
*/
void sort_by_name(College a[], unsigned n)
{
    for (unsigned i = 1; i < n; i++)
    {
        College key = a[i];              // the item we want to insert
        int j = static_cast<int>(i) - 1; // compare with left side

        // Move bigger names one step right
        while (j >= 0 && a[j].name > key.name)
        {
            a[j + 1] = a[j];
            j--;
        }

        // Place key into correct position
        a[j + 1] = key;
    }
}

/*
    sort_by_cost uses: SELECTION SORT
    - For each position i, find the best element in the rest of the array
    Sorting: cost DESCENDING (highest -> lowest)
*/
void sort_by_cost(College a[], unsigned n)
{
    for (unsigned i = 0; i + 1 < n; i++)
    {
        unsigned best = i;

        // Find index of largest cost from i..n-1
        for (unsigned j = i + 1; j < n; j++)
        {
            if (a[j].cost > a[best].cost)
            {
                best = j;
            }
        }

        // Swap it into position i
        if (best != i)
            swap_college(a[i], a[best]);
    }
}

/*
    sort_by_acceptance uses: BUBBLe SORT
    - Repeatedly swaps neighbors if they are out of order
    Sorting: acceptance rate ASCENDING (lowest ->> highest)
*/
void sort_by_acceptance(College a[], unsigned n)
{
    if (n < 2)
        return;

    for (unsigned pass = 0; pass < n - 1; pass++)
    {
        bool swapped = false;

        // Bubble up the largest rate toward the end
        for (unsigned i = 0; i < n - 1 - pass; i++)
        {
            if (a[i].rate > a[i + 1].rate)
            {
                swap_college(a[i], a[i + 1]);
                swapped = true;
            }
        }

        // If no swaps happened, array is already sorted
        if (!swapped)
            break;
    }
}