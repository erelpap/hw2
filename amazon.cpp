#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include "product.h"
#include "db_parser.h"
#include "product_parser.h"
#include "util.h"
#include "mydatastore.h"
#include "mydatastore.cpp"
#include "datastore.h"

using namespace std;
struct ProdNameSorter {
    bool operator()(Product* p1, Product* p2) {
        return (p1->getName() < p2->getName());
    }
};
void displayProducts(vector<Product*>& hits);


// creating a reverse vector function to reversing the vector in the buycart option
// this is needed since a vector is used in there and when the products are bought
// we need to pop_front but since vector does not have a pop_front functionality
// the vector is reversed once pop_back is done and reversed again.

void reverseVector(vector<Product*>& vectorke);

void reverseVector(vector<Product*>& vectorke){
    for(unsigned int i = 0; i < vectorke.size()/2; i++){
        Product* temp = vectorke[vectorke.size() - 1 - i];
        vectorke[vectorke.size() - 1 - i] = vectorke[i];
        vectorke[i] = temp;
    }
}


int main(int argc, char* argv[])
{
    if(argc < 2) {
        cerr << "Please specify a database file" << endl;
        return 1;
    }

    /****************
     * Declare your derived DataStore object here replacing
     *  DataStore type to your derived type
     ****************/
    MyDataStore ds;



    // Instantiate the individual section and product parsers we want
    ProductSectionParser* productSectionParser = new ProductSectionParser;
    productSectionParser->addProductParser(new ProductBookParser);
    productSectionParser->addProductParser(new ProductClothingParser);
    productSectionParser->addProductParser(new ProductMovieParser);
    UserSectionParser* userSectionParser = new UserSectionParser;

    // Instantiate the parser
    DBParser parser;
    parser.addSectionParser("products", productSectionParser);
    parser.addSectionParser("users", userSectionParser);

    // Now parse the database to populate the DataStore
    if( parser.parse(argv[1], ds) ) {
        cerr << "Error parsing!" << endl;
        return 1;
    }

    cout << "=====================================" << endl;
    cout << "Menu: " << endl;
    cout << "  AND term term ...                  " << endl;
    cout << "  OR term term ...                   " << endl;
    cout << "  ADD username search_hit_number     " << endl;
    cout << "  VIEWCART username                  " << endl;
    cout << "  BUYCART username                   " << endl;
    cout << "  QUIT new_db_filename               " << endl;
    cout << "====================================" << endl;

    vector<Product*> hits;
    bool done = false;
    while(!done) {
        cout << "\nEnter command: " << endl;
        string line;
        getline(cin,line);
        stringstream ss(line);
        string cmd;
        if((ss >> cmd)) {
            if( cmd == "AND") {
                string term;
                vector<string> terms;
                while(ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = ds.search(terms, 0);
                displayProducts(hits);
            }
            else if ( cmd == "OR" ) {
                string term;
                vector<string> terms;
                while(ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = ds.search(terms, 1);
                displayProducts(hits);
            }
            else if ( cmd == "QUIT") {
                string filename;
                if(ss >> filename) {
                    ofstream ofile(filename.c_str());
                    ds.dump(ofile);
                    ofile.close();
                }
                done = true;
            }
            else if(cmd == "ADD"){
                int hitIndex; 
                bool cartExists = false;
                bool userExists = false;
                string username;
                int indexSearched;

                ss >> username;
                ss >> hitIndex;
                
                set<User*>::iterator it;
                User* newUser;
                // checked if the user exists
                for(it = ds.users_.begin(); it != ds.users_.end(); ++it){
                    if((*it)->getName() == username){
                        userExists = true;
                        newUser = *it; 
                        break;
                    }
                }
                // checked if the user have an existing cart
                for(unsigned int i = 0; i < ds.cartUsers.size(); i++){
                    if(ds.cartUsers[i]->getName() == username){
                        cartExists = true;
                        indexSearched = i;
                        break;
                    }
                }
                if(!userExists){
                    cout << "Invalid user!" << endl;
                }
                // if cart does not exist a new cart is created below
                else if(!cartExists){
                    std::vector<Product*> newCart;
                    ds.cartProducts.push_back(newCart);
                    ds.cartUsers.push_back(newUser);
                    ds.cartProducts[ds.cartProducts.size() - 1].push_back(hits[hitIndex - 1]);
                }
                // if the cart does exist only the product is put into the cart
                else{
                    ds.cartProducts[indexSearched].push_back(hits[hitIndex - 1]);
                }
            }
        
            else if(cmd == "VIEWCART"){
                string username;
                ss >> username;
                int searched;
                // the index of the user is saved to find the corresponding
                // cart in the cartProducts vector 
                for(unsigned int i = 0; i < ds.cartUsers.size(); i++){
                    if(ds.cartUsers[i]->getName() == username){
                        searched = i;
                    }
                }
                // In the corresponding element all the products are printed out
                for(unsigned int i = 0; i < ds.cartProducts[searched].size(); i++){
                    cout << ds.cartProducts[searched][i]->displayString() << endl;
                }
            }
            else if ( cmd == "BUYCART"){
                string username;
                ss >> username;
                int index;
                int counter = 0;
                bool cartExists = false;
                // checked if the given user have a cart or not
                while(!cartExists && counter < ds.cartUsers.size()){
                    if(ds.cartUsers[counter]->getName() == username){
                        cartExists = true;
                        index = counter;
                    }
                    counter = counter + 1;
                }
                if(cartExists){
                    int counter = 0;
                    for(unsigned int i = 0; i < ds.cartProducts[index].size(); i++){
                        double price = ds.cartProducts[index][i]->getPrice();
                        // if the user has money and if the product still exists the product is bought
                        if(ds.cartUsers[index]->getBalance() > price &&  ds.cartProducts[index][i]->getQty() > 0){
                            counter++;
                            ds.cartProducts[index][i]->subtractQty(1);
                            ds.cartUsers[index]->deductAmount(price);
                        }
                    }
                    reverseVector(ds.cartProducts[index]);
                    // the products that are bought are taken out of the list.
                    for (int i = 0; i < counter; i++){
                        ds.cartProducts[index].pop_back();
                    }
                    reverseVector(ds.cartProducts[index]);
                }
                else{
                    cout << "Invalid user" << endl;
                }
            }
            else {
                cout << "Unknown command" << endl;
            }
        }
    }
    return 0;
}

void displayProducts(vector<Product*>& hits)
{
    int resultNo = 1;
    if (hits.begin() == hits.end()) {
    	cout << "No results found!" << endl;
    	return;
    }
    std::sort(hits.begin(), hits.end(), ProdNameSorter());
    for(vector<Product*>::iterator it = hits.begin(); it != hits.end(); ++it) {
        cout << "Hit " << setw(3) << resultNo << endl;
        cout << (*it)->displayString() << endl;
        cout << endl;
        resultNo++;
    }
}
