#include "datastore.h"
#include "product.h"
#include "user.h"
#include "util.h"
#include <map>
#include <set>
#include <string>
#include <iostream>
#include <queue>


class MyDataStore : public DataStore{

public:
    ~MyDataStore() override;
    void addProduct(Product* p) override;
    void addUser(User* u) override;
    std::vector<Product*> search(std::vector<std::string>& terms, int type) override;
    void dump(std::ostream& ofile) override;

    void addCart(const std::string& username, int index, std::vector<Product*> hits);
    void viewCart(const std::string& username);
    void buyCart(const std::string& username);



private:
    std::set<Product*> products_;
    std::set<User*> users_;
    std::map<std::string, std::set<Product*>> keywords_;
    std::map<std::string, std::queue<Product*>> cart_;
    

    

};