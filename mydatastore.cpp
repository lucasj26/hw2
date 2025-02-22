#include "datastore.h"
#include "product.h"
#include "user.h"
#include "util.h"
#include "mydatastore.h"
#include <map>
#include <set>
#include <string>
#include <iostream>

using namespace std;

MyDataStore::~MyDataStore() 
{
    for (Product* p : products_) {
        delete p;
    }
    for (User* u : users_) {
        delete u;
    }
    
}

void MyDataStore::addProduct(Product* p)
{
    products_.insert(p);

    set<string> kw = p->keywords();

    set<string>::iterator it;

    for(it=kw.begin();it!= kw.end();it++){
        keywords_[*it].insert(p);
    }

}

void MyDataStore::addUser(User* u)
{
    users_.insert(u);
}

vector<Product*> MyDataStore::search(vector<string>& terms, int type)
{
    set<Product*> output;

    if (terms.empty()) {
        return vector<Product*>(); 
    }
    
    if (type == 0) {  
        if (keywords_.find(terms[0]) != keywords_.end()) {
            output = keywords_[terms[0]]; 
        }

        for (size_t i = 1; i < terms.size(); i++) {
            std::string lowerTerm = convToLower(terms[i]);
            if (keywords_.find(lowerTerm) != keywords_.end()) {
                set<Product*> curr = keywords_[terms[i]];
                output = setIntersection(output, curr); 
            } else {
                return vector<Product*>();
            }
        }
    }
    else if (type==1){
         for (size_t i = 0; i < terms.size(); i++){
            std::string lowerTerm = convToLower(terms[i]);
            if (keywords_.find(lowerTerm) != keywords_.end()){
                set<Product*> curr = keywords_[terms[i]];
                output = setUnion(output, curr);
            }
         }
    }


    vector<Product*> resultVector(output.begin(), output.end());
    return resultVector;
    
}      

void MyDataStore::dump(ostream& ofile)
{
    ofile << "<products>" << endl;
    for(Product* p: products_){
        p->dump(ofile);
    }
    ofile << "</products>" << endl;

    ofile << "<users>" << endl;
    for(User* u: users_){
        u->dump(ofile);
    }
    ofile << "</users>";

}

void MyDataStore::addCart(const std::string& username, int index,  std::vector<Product*> hits)
{
    User* temp = nullptr;
    for(User* u: users_){
        if(convToLower(u->getName()) == convToLower(username)){
            temp = u;
            break;
        }
    }

    if(temp==nullptr){
        cout << "Invalid request" << endl;
        return;
    }

    int hitsSize = hits.size();
    if(index > 0 && index <= hitsSize){
        cart_[username].push(hits[index-1]);
        return;
    }
    else{
        cout << "Invalid request" << endl;
        return;
    }

    

}

void MyDataStore::viewCart(const std::string& username)
{
    User* temp = nullptr;
    for(User* u: users_){
        if(convToLower(u->getName()) == convToLower(username)){
            temp = u;
            break;
        }
    }

    if(temp==nullptr){
        cout << "Invalid username" << endl;
        return;
    }

    queue<Product*> currCart = cart_[username];


    int index = 1;
    while(!currCart.empty()){
        Product* p = currCart.front();
        cout << "Item " << index << endl;
        cout << p->displayString() << endl;

        index++;
        currCart.pop();
        
    }

    return;


}

void MyDataStore::buyCart(const std::string& username)
{
    User* temp = nullptr;
    for(User* u: users_){
        if(convToLower(u->getName()) == convToLower(username)){
            temp = u;
            break;
        }
    }

    if(temp==nullptr){
        cout << "Invalid username" << endl;
        return;
    }

    queue<Product*>& currCart = cart_[username];
    queue<Product*> newCart;

    while(!currCart.empty()){
        Product* p = currCart.front();
        currCart.pop();

        double price = p->getPrice();

        if(p->getQty() >0 && temp->getBalance() >= price){
            p->subtractQty(1);
            temp->deductAmount(price);
        }
        else{ // if purchase doesn't happen for any reason
            newCart.push(p); // keep track of item so it remains in cart
        }
    }

    cart_[username] = newCart;

}
