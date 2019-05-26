#pragma once
#include <string>
#include <ostream>


class Product {
  public:
    Product(std::string name, double price, double cost);
    std::string name();
Product(std::istream& ist);
	virtual void save(std::ostream& ost);
    virtual std::string to_string();

double price();
    double profit();
  protected:
    std::string _name;
    double _price;
    double _cost;
};
