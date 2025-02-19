#include "clothing.h"
#include "util.h"
#include <set>

using namespace std;

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, std::string size, std::string brand)
: Product(category, name, price, qty), size_(size), brand_(brand)
{

}

void Clothing::dump(std::ostream& os) const {
    Product::dump(os);
    os << size_ << "\n" << brand_;
}

std::set<std::string> Clothing::keywords() const {
    set<string> nameKeywords = parseStringToWords(convToLower(name_));
    set<string> brandKeywords = parseStringToWords(convToLower(brand_));

    set<string> result = setUnion(nameKeywords, brandKeywords);
    return result;
}

std::string Clothing::displayString() const {
    string result = "";
    result += name_ + "\n";
    result += "Size: " + size_ + " Brand: " + brand_ + "\n";
    result += to_string(price_) + " " + to_string(qty_) + " left";
    return result;
}