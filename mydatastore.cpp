#include "mydatastore.h"
#include "util.h"

using namespace std;

MyDataStore::~MyDataStore() {
    // set<Product*> allProducts;
    // for (map<string, set<Product*>>::iterator it = products.begin(); it != products.end(); ++it) {
    //     allProducts = setUnion(allProducts, (*it).second);
    // }

    for (set<Product*>::iterator it = deleteList.begin(); it != deleteList.end(); ++it) {
        delete *it;
    }

    for (map<string, User*>::iterator it = users.begin(); it != users.end(); ++it) {
        delete (*it).second;
    }
}

void MyDataStore::addProduct(Product* p) {
    set<string> keywords = p->keywords();
    for (set<string>::iterator it = keywords.begin(); it != keywords.end(); ++it) {
        products[*it].insert(p);
        deleteList.insert(p);
    }
}

void MyDataStore::addUser(User* u) {
    users[u->getName()] = u;
}

vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type) {
    set<Product*> result;
    if (type == 0) {
        if (terms.size() == 0) {
            prevSearch = vector<Product*>();
            return vector<Product*>();
        }
        
        result = products[terms[0]];
        for (size_t i = 1; i < terms.size(); i++) {
            result = setIntersection(result, products[terms[i]]);
        }
    } else if (type == 1) {
        if (terms.size() == 0) {
            throw "No keywords";
        }
        for (size_t i = 0; i < terms.size(); i++) {
            result = setUnion(result, products[terms[i]]);
        }
    } else {
        throw "invalid search type";
    }

    vector<Product*> resultVec;

    for (set<Product*>::iterator it = result.begin(); it != result.end(); ++it) {
        resultVec.push_back(*it);

    }

    prevSearch = resultVec;
    return resultVec;
}

std::vector<Product*> MyDataStore::getCart(std::string username) {
    return carts[username];
}

bool MyDataStore::userExists(string username) {
    return users.find(username) != users.end();
}

void MyDataStore::addToCart(Product* p, std::string username) {
    carts[username].push_back(p);
    
}

void MyDataStore::buyCart(std::string username) {
    vector<Product*>& cart = carts[username];
    User* u = users[username];
    vector<Product*> newCart;
    
    size_t index = 0;
    while (index < cart.size()) {
        double price = cart[index]->getPrice();
        int qty = cart[index]->getQty();
        if (price <= u->getBalance() && qty > 0) {
            u->deductAmount(price);
            cart[index]->subtractQty(1);
        } else {
            newCart.push_back(cart[index]);
        }
        index++;
    }
    carts[username] = newCart;
}

bool MyDataStore::validHitIndex(size_t index) {
    if (prevSearch.size() == 0) return false;
    else return (prevSearch.size() > index && index >= 0);
}

void MyDataStore::dump(std::ostream& ofile) {
    ofile << "<products>\n";
    // set<Product*> allProducts;
    // for (std::map<std::string, std::set<Product*>>::iterator it = products.begin(); it != products.end(); ++it) {
    //     allProducts = setUnion(allProducts, it->second);
    // }

    for (set<Product*>::iterator it = deleteList.begin(); it != deleteList.end(); ++it) {
        (*it)->dump(ofile);
    }

    ofile << "</products>\n";
    ofile << "<users>\n";

    for (std::map<std::string, User*>::iterator it = users.begin(); it != users.end(); ++it) {
        (*it).second->dump(ofile);
    }
    ofile << "</users>" << endl;
}