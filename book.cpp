#include "book.h"
#include "util.h"
#include <set>
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;


Book::Book(const string category, const string name, double price, int qty,
    const string isbn, const string author) :
    Product(category, name, price, qty),isbn_(isbn), author_(author)
{

} 

set<string> Book::keywords() const
{
    set<string> output;

    set<string> namekw = parseStringToWords(name_);
    set<string> authorkw = parseStringToWords(author_);

    output = setUnion(namekw, authorkw);
    output.insert(isbn_);

    return output;

}


string Book::displayString() const
{
    stringstream ss;
    ss << fixed << setprecision(2);
    
    ss << name_ << "\n"
    << "Author: " << author_ << " " << "ISBN: " << isbn_ << "\n"
    << price_ << " " << qty_ << " left.";

    return ss.str();
  
}

void Book::dump(ostream& os) const
{
    os << "book" << endl;
    os << name_ << endl;
    os << price_ << endl;
    os << qty_ << endl;
    os << isbn_ << endl;
    os << author_ << endl;
}

