#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <string>
#include <vector>
#include <set>
#include "product.h"
#include "datastore.h"
#include <map>

class MyDataStore : public DataStore {
	public:
		MyDataStore();
    virtual ~MyDataStore();
    virtual void addProduct(Product* p);
    virtual void addUser(User* u);
    virtual std::vector<Product*> search(std::vector<std::string>& terms, int type);
    virtual void dump(std::ostream& ofile);
		
		std::set<Product*> products_;
		std::set<User*> users_;
		std::vector<User*> cartUsers;
		std::vector<std::vector<Product*>> cartProducts;
};

#endif