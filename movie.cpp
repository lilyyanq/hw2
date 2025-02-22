#include "movie.h"
#include <sstream>
#include <iostream>
#include <iomanip>
#include "util.h"

using namespace std;

// Constructor: Calls Product constructor and initializes isbn_ and author_
Movie::Movie(const string& name, double price, int qty, const string& genre, const string& rating)
    : Product("movie", name, price, qty), genre_(genre), rating_(rating) {
}

// Generate keywords
set<string> Movie::keywords() const {
    set<string> keys;
    set<string> partkeys;
    // get key words from movie name
    partkeys = parseStringToWords(name_);
    keys.insert(partkeys.begin(), partkeys.end());

    // get key words from movie genre
    partkeys = parseStringToWords(genre_);
    keys.insert(partkeys.begin(), partkeys.end());

    
    return keys;
}

// Return a formatted string with movie details, called by displayProducts in the amazon.cpp
string Movie::displayString() const {
    ostringstream os;
    os << name_ << "\n"
        << "Genre: " << genre_ << " Rating: " << rating_ << "\n"
        << price_ << " " << qty_ << " left.";
    return os.str();
}

// Dump movie data in a structured format
void Movie::dump(ostream& os) const {
    // Call Product's dump() to print name_, price_, and qty_
    Product::dump(os);

    // Print only the additional fields specific to Movie
    os << genre_ << "\n" << rating_ << endl;
}
