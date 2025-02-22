#include "book.h"
#include <sstream>
#include <iostream>
#include <iomanip>
#include "util.h"

using namespace std;

// Constructor: Calls Product constructor and initializes isbn_ and author_
Book::Book(const string& name, double price, int qty, const string& isbn, const string& author)
    : Product("book", name, price, qty), isbn_(isbn), author_(author) {
}

// Generate keywords
set<string> Book::keywords() const {
    set<string> keys;
    set<string> partkeys;
    // get key words from book name
    partkeys = parseStringToWords(name_);   
    keys.insert(partkeys.begin(), partkeys.end());

    // get key words from author name
    partkeys = parseStringToWords(author_);
    keys.insert(partkeys.begin(), partkeys.end());

    // Add ISBN as a keyword
    keys.insert(isbn_);

    return keys;
}

// Return a formatted string with book details, called by displayProducts in the amazon.cpp and printed to console using cout
string Book::displayString() const {
    ostringstream os;
    os << name_ << "\n"
        << "Author: " << author_ << " ISBN: " << isbn_ << "\n"
        << price_ << " " << qty_ << " left.";
    return os.str();
}

// Dump book data in a structured format
void Book::dump(ostream& os) const {
    // Call Product's dump() to print name_, price_, and qty_
    Product::dump(os);

    // Print only the additional fields specific to Book
    os << isbn_ << "\n" << author_ << endl;
}
