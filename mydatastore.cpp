#include "mydatastore.h"
#include "util.h"

using namespace std;

void MyDataStore::addProduct(Product* p) {
    set<string> keywords = p->keywords();
    for (set<string>::iterator it = keywords.begin(); it != keywords.end(); ++it) {
        products[*it].insert(p);
    }
}

void MyDataStore::addUser(User* u) {
    users[u->getName()] = u;
}

vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type) {
    set<Product*> result;
    if (type == 0) {
        if (terms.size() == 0) return vector<Product*>();
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

    for (set<Product*>::iterator it = result.begin(); it != result.begin(); ++it) {
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

void MyDataStore::addToCart(size_t hit_index, std::string username) {
    carts[username].push_back(prevSearch[hit_index]);
}

void MyDataStore::buyCart(std::string username) {
    vector<Product*> cart = carts[username];
    User* u = users[username];
    
    size_t index = 0;
    while (index < cart.size()) {
        double price = cart[index]->getPrice();
        int qty = cart[index]->getQty();
        if (price <= u->getBalance() && qty > 0) {
            u->deductAmount(price);
            cart[index]->subtractQty(1);
        } else {
            index++;
        }
    }
}

bool MyDataStore::validHitIndex(size_t index) {
    if (prevSearch.size() == 0) return 0;
    else return (prevSearch.size() > index && index >= 0);
}