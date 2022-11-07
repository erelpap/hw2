#include "clothing.h"
#include "util.h"
#include <string>

using namespace std;

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, std::string size, std::string brand):Product(category, name, price, qty){
	brand_ = brand;
	size_ = size;
}

Clothing::~Clothing(){

}
// <name>
// Size: <size> Brand: <brand>
// <price> <quantity> left.
std::string Clothing::displayString() const{
	std::string clothingStr = name_ + '\n' + "Size: "  + size_ +  " Brand: "  + brand_ + '\n' + to_string(price_) + ' ' + to_string(qty_) + " left." + '\n';
	return clothingStr;
}

void Clothing::dump(std::ostream& os) const{
	os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_ << endl;
}


std::set<std::string> Clothing::keywords() const{
	// keywords in the name, brand are added
	std::set<std::string> parsedName = parseStringToWords(name_);
	std::set<std::string> parsedBrand = parseStringToWords(brand_);
	std::set<std::string> result = setUnion(parsedBrand, parsedName);
	std::set<std::string> resultLower;

// all the keywords are made lower case
	std::set<std::string>::iterator it;
	for(it = result.begin(); it != result.end(); ++it){
		resultLower.insert(convToLower(*it));
	}
	
	

	return resultLower;
}