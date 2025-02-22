#include "mydatastore.h"
#include <iostream>
#include "util.h"
using namespace std;

AmazonDataStore::AmazonDataStore() {}
AmazonDataStore::~AmazonDataStore() {
    // Loop through products_ using an index
    for (size_t i = 0; i < products_.size(); ++i) {
        delete products_[i];
    }

    // Loop through users_ using an index
    for (size_t i = 0; i < users_.size(); ++i) {
        delete users_[i];
    }
}



void AmazonDataStore::addProduct(Product* p) {
    if (p) {
        products_.push_back(p); // fast O(1)

        // Add product to keyword map
        set<string> keys = p->keywords();
        for (const string& key : keys) {
            keywordMap_[key].insert(p);
        }
    }
}

void AmazonDataStore::addUser(User* u) {
    if (u) {
        users_.push_back(u); // fast O(1)
    }
}

vector<Product*> AmazonDataStore::search(vector<string>& terms, int type) {
    set<Product*> results;
    if (terms.empty()) return {}; // No search terms

    bool first = true;
    for (const string& term : terms) {  
        map<string, set<Product*>>::iterator it = keywordMap_.find(term);
        if (it != keywordMap_.end()) {  
            set<Product*>& products = it->second;  // store the search result

            if (first) {
                results = products;  // First matching term 
                first = false;
            }
            else {
                if (type == 0) { // AND search (intersection)
                    results = setIntersection(results, products);
                }
                else { // OR search (union)
                    results = setUnion(results, products);
                }
            }
        }
        else // no product found for THIS term
        { 
            if (type == 0) { // AND search (intersection), then should return empty
				for (Product* p : results) {
					delete p; // Free memory for each Product
				}
				
                results.clear(); //optional: clear() removes all elements from the set,make sure the set is empty.
				return vector<Product*>();// return empty vector
            }
            //else - OR search (union), then continue to search next term.               
            
        }
    }

    return vector<Product*>(results.begin(), results.end());
}


// write products and users to the file linked by ofile
void AmazonDataStore::dump(ostream& ofile) {
    ofile << "<products>\n";

    // Iterate through products_ 
    for (size_t i = 0; i < products_.size(); ++i) {
        products_[i]->dump(ofile);
    }

    ofile << "</products>\n";

    ofile << "<users>\n";

    // Iterate through users_ 
    for (size_t i = 0; i < users_.size(); ++i) {
        users_[i]->dump(ofile);
    }

    ofile << "</users>\n";
}

void AmazonDataStore::addToCart(const std::string& username, Product* product) {
    // Convert username to lowercase for consistency
    std::string lowerUsername = convToLower(username);

    // amazon.cpp has checked if the user exists or not already
    // Add the product to the user's cart (FIFO order)
    carts_[lowerUsername].push_back(product);
}

void AmazonDataStore::viewCart(const std::string& username) {
    std::string lowerUsername = convToLower(username);

    // Check if the user exists
    if (!userExists(lowerUsername)) {
        std::cout << "Invalid username" << std::endl;
        return;
    }

    // Get user's cart
    if (carts_.find(lowerUsername) == carts_.end() || carts_[lowerUsername].empty()) {
        std::cout << "Cart is empty." << std::endl;
        return;
    }

    // Print cart products in FIFO order
    std::deque<Product*>& cart = carts_[lowerUsername];
    int index = 1;
    for (Product* product : cart) {
        std::cout << "Item " << index++ << ":" << std::endl;
        std::cout << product->displayString() << std::endl;
        std::cout << std::endl;
    }
}

void AmazonDataStore::buyCart(const std::string& username) {
    std::string lowerUsername = convToLower(username);

    // Get the user object
    User* user = getUser(lowerUsername);
    if (!user) {
        std::cout << "Invalid username" << std::endl;
        return;
    }
    // Get reference to user's cart
    std::deque<Product*>& cart = carts_[lowerUsername];
    if (cart.empty()) {
        std::cout << "Cart is empty." << std::endl;
        return;
    }

    // Process each product in FIFO order
    for (std::deque<Product*>::iterator it = cart.begin(); it != cart.end();) 
	{
		Product* product = *it;

        // Check if the product is in stock and the user has enough credit
        if (product->getQty() > 0 && user->getBalance() >= product->getPrice()) 
        {
            user->deductAmount(product->getPrice());  // Deduct price
            product->subtractQty(1);  // Reduce stock
            it = cart.erase(it);  // Remove item from cart
            std::cout << "Item " << product->getName() << " is purchased." << std::endl;

        }
        else {
            ++it;  // Move to next item
        }
    }
}


User* AmazonDataStore::getUser(const std::string& username) {
    std::string lowerUsername = convToLower(username);

    for (size_t i = 0; i < users_.size(); ++i) {
        if (convToLower(users_[i]->getName()) == lowerUsername) {
            return users_[i];  // Return pointer to the input user
        }
    }

    return nullptr;  // user not found
}


bool AmazonDataStore::userExists(const std::string& username) {
    std::string lowerUsername = convToLower(username);

    // go through users_ vector to find the user
    for (size_t i = 0; i < users_.size(); ++i) {
        if (convToLower(users_[i]->getName()) == lowerUsername) {
            return true;
        }
    }

    return false;
}