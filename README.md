# College Cost Analyzer

A C++ program that reads cost and acceptance-rate data for California colleges from a CSV file, then displays, searches, and sorts it. It's built to help high school students compare schools at a glance.

## What it does

- **Displays** every college in an aligned table, then prints the most expensive college, the least expensive college, and the average cost (to 2 decimal places).
- **Searches** by college name and category (`cost` or `rate`). It returns -1 if the college isn't found or the category is invalid.
- **Sorts** the data three ways, each with a different algorithm:

| Function | Sorts by | Algorithm |
|---|---|---|
| `sort_by_name` | Name, A to Z | Insertion sort |
| `sort_by_cost` | Cost, high to low | Selection sort |
| `sort_by_acceptance` | Acceptance rate, low to high | Bubble sort |

Adding a new college is as simple as adding a line to `california.csv`. The program loads up to 10 colleges, so no code changes are needed.

## Built with

- C++ (structs, arrays, functions, file I/O with `ifstream` and `stringstream`)
- Formatted output with `<iomanip>` (`setw`, `fixed`, `setprecision`)

## Project structure

```
college-cost-analyzer/
├── main.cpp         # loads the CSV and runs the display, search, and sort tests
├── library.h        # College struct and function declarations
├── library.cpp      # display, search, and the three sorting functions
└── california.csv   # data: name, cost after aid, acceptance rate (%)
```

## How to run

You need a C++ compiler such as `g++`. From this folder:

```bash
g++ -std=c++17 main.cpp library.cpp -o analyzer
./analyzer
```

Run it from the folder that contains `california.csv`, since the program opens the file by name.

## Sample output

```
=== DISPLAY (Original Data) ===
College                                         Cost   Acceptance rate
======================================================================
University of California Los Angeles     $     13393               11%
University of California Berkeley        $     17652               14%
University of California Irvine          $     11633               29%
California State University San Marcos   $     10500               96%
San Diego State University               $     21879               34%
University of California San Diego       $     13293               25%
======================================================================
The most expensive university is: San Diego State University

The least expensive university is: California State University San Marcos
The average cost in California is: $14725.00
```

## Testing

`main.cpp` tests the search with a college at the beginning, middle, and end of the array, a college that isn't in the data, both valid categories, and a valid college with an invalid category. Each sort is shown before and after on the same data.

## What I learned

- Organizing related data with a `struct` and an array of structs
- Reading and parsing a CSV file line by line
- Writing and comparing three different sorting algorithms
- Handling edge cases, like missing colleges and invalid input, without crashing

*Built for my Computer Science II course at California State University San Marcos.*
