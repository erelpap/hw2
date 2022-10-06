#ifndef CLOTHING_H
#define CLOTHING_H

#include "product.h"
#include <string>
#include <set>

class Clothing : public Product{
	public:
		Clothing(const std::string category, const std::string name, double price, int qty, std::string size, std::string brand);
		virtual ~Clothing();
		virtual std::string displayString() const;
		virtual void dump(std::ostream& os) const;
		virtual std::set<std::string> keywords() const;
	private:
		std::string brand_;
		std::string size_;
};

#endif
