#ifndef MOVIE_H
#define MOVIE_H

#include "product.h"
#include <string>
#include <set>

class Movie : public Product{
	public:
		Movie(const std::string category, const std::string name, double price, int qty, std::string genre, std::string rating);
		virtual ~Movie();
		virtual std::string displayString() const;
		virtual void dump(std::ostream& os) const;
		virtual std::set<std::string> keywords() const;
	private:
		std::string genre_;
		std::string rating_;
};

#endif
