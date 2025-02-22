#include "movie.h"
#include "util.h"
#include <set>
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

Movie::Movie(const string category, const string name, double price, int qty,
    const string genre, const string rating) :
    Product(category, name, price, qty), genre_(genre), rating_(rating)
{

} 

set<string> Movie::keywords() const
{
    set<string> output = parseStringToWords(name_);

    output.insert(convToLower(genre_));

    return output;

}


string Movie::displayString() const
{
    stringstream ss;
    ss << fixed << setprecision(2);
    
    ss << name_ << "\n"
    << "Genre: " << genre_ << " " << "Rating: " << rating_ << "\n"
    << price_ << " " << qty_ << " left.";

    return ss.str();
}

void Movie::dump(ostream& os) const
{
    os << "movie" << endl;
    os << name_ << endl;
    os << price_ << endl;
    os << qty_ << endl;
    os << genre_ << endl;
    os << rating_ << endl;

}

