#ifndef DATASTORE_H
#define DATASTORE_H
#include <string>
#include <set>
#include <vector>
#include "product.h"
#include "user.h"

/**
 * DataStore Interface needed for parsing and instantiating products and users
 *
 * A derived version of the DataStore can provide other services as well but
 * must support those below
 *
 * DO NOT EDIT
 */

class DataStore {
public:
    virtual ~DataStore() { }
    virtual void addProduct(Product* p) = 0;
    virtual void addUser(User* u) = 0;
    virtual std::vector<Product*> search(std::vector<std::string>& terms, int type) = 0;
    virtual void dump(std::ostream& ofile) = 0;
};

#endif
