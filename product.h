#ifndef PRODUCT_H
#define PRODUCT_H
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>

class Product {
public:
    Product(const std::string category, const std::string name, double price, int qty);
    virtual ~Product();
    virtual std::set<std::string> keywords() const = 0;
    virtual bool isMatch(std::vector<std::string>& searchTerms) const;
    virtual std::string displayString() const = 0;
    virtual void dump(std::ostream& os) const;
    double getPrice() const;
    std::string getName() const;
    int getQty() const;
    void subtractQty(int num);
protected:
    std::string name_;
    double price_;
    int qty_;
    std::string category_;
};
#endif
