#ifndef BOOK_H
#define BOOK_H

#include "product.h"
#include <set>
#include <string>

using namespace std;

class Book : public Product {
public:
    // Constructor
    Book(const string& name, double price, int qty, const string& isbn, const string& author);

    // Override Product's pure virtual functions
    set<string> keywords() const override;
    string displayString() const override;
    void dump(std::ostream& os) const override;

private:
    string isbn_;   // ISBN of the book
    string author_; // Author of the book
};

#endif
