#include "clothing.h"
#include <sstream>
#include <iostream>
#include <iomanip>
#include "util.h"

using namespace std;

// Constructor: Calls Product constructor and initializes isbn_ and author_
Clothing::Clothing(const string& name, double price, int qty, const string& size, const string& brand)
    : Product("clothing", name, price, qty), brand_(brand), size_(size) {
}

// Generate keywords
set<string> Clothing::keywords() const {
    set<string> keys;
    set<string> partkeys;
    // get key words from clothing name
    partkeys = parseStringToWords(name_);
    keys.insert(partkeys.begin(), partkeys.end());

    // get key words from clothing brand
    partkeys = parseStringToWords(brand_);
    keys.insert(partkeys.begin(), partkeys.end());


    return keys;
}

// Return a formatted string with clothing details, called by displayProducts in the amazon.cpp
string Clothing::displayString() const {
    ostringstream os;
    os << name_ << "\n"
        << "Size: " << size_ << " Brand: " << brand_ << "\n"
        << price_ << " " << qty_ << " left.";
    return os.str();
}

// Dump clothing data in a structured format
void Clothing::dump(ostream& os) const {
    // Call Product's dump() to print name_, price_, and qty_
    Product::dump(os);

    // Print only the additional fields specific to Clothing
    os << size_ << "\n" << brand_ << endl;
}
