#include "movie.h"
#include "util.h"
#include <set>
#include <sstream>

using namespace std;

Movie::Movie(const std::string category, const std::string name, double price, int qty, std::string genre, std::string rating)
: Product(category, name, price, qty), genre_(genre), rating_(rating)
{

}

void Movie::dump(std::ostream& os) const {
    Product::dump(os);
    os << genre_ << "\n" << rating_ << endl;
}

std::set<std::string> Movie::keywords() const {
    set<string> result = parseStringToWords(convToLower(name_));

    result.insert(convToLower(genre_));
    return result;
}

std::string Movie::displayString() const {
    stringstream priceStream;
    priceStream << price_;

    string result = "";
    result += name_ + "\n";
    result += "Genre: " + genre_ + " Rating: " + rating_ + "\n";
    result += priceStream.str() + " " + to_string(qty_) + " left.";
    return result;
}