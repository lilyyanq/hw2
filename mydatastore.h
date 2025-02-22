#pragma once
#ifndef AMAZONDATASTORE_H
#define AMAZONDATASTORE_H

#include "datastore.h"
//#include <set>  -- they are inlcuded in the datastore.h file already
//#include <vector>
#include <map>
#include <deque>
using namespace std;

class AmazonDataStore : public DataStore {
public:
    AmazonDataStore();
    ~AmazonDataStore();

    void addProduct(Product* p) override;
    void addUser(User* u) override;
    vector<Product*> search(vector<string>& terms, int type) override;
    void dump(ostream& ofile) override;
    void addToCart(const string& username, Product* product);

    void viewCart(const std::string& username);

    void buyCart(const string& username);
    bool userExists(const string& username);

    User* getUser(const string& username);

private:
    vector<Product*> products_;   // Store all products, vector has fast push back 
    vector<User*> users_;         // Store all users
    map<string, set<Product*>> keywordMap_; // Map keywords to products

    map<string, deque<Product*>> carts_; // FIFO Cart


};

#endif