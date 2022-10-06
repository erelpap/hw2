#include "book.h"
#include "util.h"
#include <string>
#include <cctype>

using namespace std;

Book::Book(const std::string category, const std::string name, double price, int qty, std::string author, std::string isbn):Product(category, name, price, qty){
	author_ = author;
	isbn_ = isbn;
}

Book::~Book(){
	
}


// <name>
// Author: <author> ISBN: <isbn>
// <price> <quantity> left.
std::string Book::displayString() const{
	std::string bookStr = name_ + '\n' + "Author: "  + author_ +  " ISBN: "  + isbn_ + '\n' + to_string(price_) + ' ' + to_string(qty_) + " left." + '\n';
	return bookStr;
}

void Book::dump(std::ostream& os) const{
  os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << isbn_ << endl;
}

// the words in the author’s name should be searchable keywords as 
// well as the book’s ISBN number
std::set<std::string> Book::keywords() const{
	std::set<std::string> parsedAuthor = parseStringToWords(author_);
	std::set<std::string> parsedName = parseStringToWords(name_);
	std::set<std::string> result = setUnion(parsedName, parsedAuthor);
	result.insert(isbn_);
	std::set<std::string> resultLower;
	std::set<std::string>::iterator it;

	// all the keywords are made lower case
	for(it = result.begin(); it != result.end(); ++it){
		resultLower.insert(convToLower(*it));
	}
	return resultLower;
}