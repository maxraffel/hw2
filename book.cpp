#include "book.h"
#include "util.h"
#include <set>

using namespace std;

Book::Book(const std::string category, const std::string name, double price, int qty, std::string isbn, std::string author)
: Product(category, name, price, qty), isbn_(isbn), author_(author)
{

}

void Book::dump(std::ostream& os) const {
    Product::dump(os);
    os << "\n" << isbn_ << "\n" << author_;
}

std::set<std::string> Book::keywords() const {
    set<string> nameKeywords = parseStringToWords(convToLower(name_));
    set<string> authorKeywords = parseStringToWords(convToLower(author_));

    set<string> result = setUnion(nameKeywords, authorKeywords);
    result.insert(convToLower(isbn_));
    return result;
}

std::string Book::displayString() const {
    string result = "";
    result += name_ + "\n";
    result += "Author: " + author_ + " ISBN: " + isbn_ + "\n";
    result += to_string(price_) + " " + to_string(qty_) + " left";
    return result;
}