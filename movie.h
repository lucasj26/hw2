#include "product.h"
#include <string>
#include <iostream>
#include <set>

class Movie : public Product {
public:
    Movie(const std::string category, const std::string name, double price, int qty,
    const std::string genre, const std::string rating);

    std::set<std::string> keywords() const override;
    std::string displayString() const override;
    void dump(std::ostream& os) const override;
    
private:
    std::string genre_;
    std::string rating_;
};