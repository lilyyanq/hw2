#ifndef CLOTHING_H
#define CLOTHING_H

#include "product.h"
#include <set>
#include <string>

using namespace std;

class Clothing : public Product {
public:
    // Constructor
    Clothing(const string& name, double price, int qty, const string& brand, const string& size);

    // Override Product's pure virtual functions
    set<string> keywords() const override;
    string displayString() const override;
    void dump(std::ostream& os) const override;

private:
    string brand_;   // brand of the clothing
    string size_; // size of the clothing
};

#endif

#pragma once