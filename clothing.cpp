#include "clothing.h"
#include "util.h"
#include <set>
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;


Clothing::Clothing(const string category, const string name, double price, int qty,
    const string size, const string brand) :
    Product(category, name, price, qty), size_(size), brand_(brand)
{

} 

set<string> Clothing::keywords() const
{
    set<string> output;

    set<string> namekw = parseStringToWords(name_);
    set<string> brandkw = parseStringToWords(brand_);

    output = setUnion(namekw, brandkw);

    return output;

}


std::string Clothing::displayString() const
{
    stringstream ss;
    ss << fixed << setprecision(2);
    
    ss << name_ << "\n"
    << "Size: " << size_ << " " << "Brand: " << brand_ << "\n"
    << price_ << " " << qty_ << " left.";

    return ss.str();
}

void Clothing::dump(ostream& os) const
{
    os << "clothing" << endl;
    os << name_ << endl;
    os << price_ << endl;
    os << qty_ << endl;
    os << size_ << endl;
    os << brand_ << endl;
}

