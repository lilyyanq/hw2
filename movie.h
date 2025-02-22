#ifndef MOVIE_H /*BOOK_H*/
#define MOVIE_H

#include "product.h"
#include <set>
#include <string>

using namespace std;

class Movie : public Product {
public:
    // Constructor
    Movie(const string& name, double price, int qty, const string& genre, const string& rating);

    // Override Product's pure virtual functions
    set<string> keywords() const override;
    string displayString() const override;
    void dump(std::ostream& os) const override;

private:
    string genre_;   // genre of the movie
    string rating_; // rating of the movie
};

#endif

#pragma once
#pragma once