#include "datastore.h"
#include "product.h"
#include "user.h"
#include <map>

class MyDataStore : public DataStore {

public:
    void addProduct(Product* p);
    void addUser(User* u);
    std::vector<Product*> search(std::vector<std::string>& terms, int type);
    void dump(std::ostream& ofile);

    bool userExists(std::string username);

    std::vector<Product*> getCart(std::string username);
    void addToCart(size_t hit_index, std::string username);
    void buyCart(std::string username);

    bool validHitIndex(size_t index);

private:
    std::map<std::string, std::set<Product*>> products;
    std::map<std::string, User*> users;
    std::map<std::string, std::vector<Product*>> carts;
    std::vector<Product*> prevSearch;
};