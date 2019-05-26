#include "donut.h"

Donut::Donut(std::string name, double price, double cost, Frosting frosting, bool sprinkles, Filling filling)
    : Product{name, price, cost}, _frosting{frosting}, _sprinkles{sprinkles}, _filling{filling} { }

  Donut::Donut(std::istream& ist): Product{ist} {
    int temp;
    ist >> temp; ist.ignore();
    if(temp ==1) _sprinkles = true;
    else _sprinkles = false;
    ist >> temp; ist.ignore();
    _frosting = (Frosting)temp;

    ist >> temp; ist.ignore();
    _filling = (Filling)temp;
      
}

void Donut::save(std::ostream& ost) {
    ost << "(DONUT)"<< std::endl;
    ost << _name << std::endl;
    ost << _price << std::endl;
    ost << _cost << std::endl;
    ost << _sprinkles << std::endl;
    ost <<(int) _frosting << std::endl;
    ost << (int)_filling << std::endl;    
 
}


std::string Donut::to_string() {
    std::string result = Product::to_string();
    std::string separator = " (";
    std::string terminator = "";
    if (_frosting != Unfrosted) {
        result += separator + "frosted with " + frosting_to_string[_frosting];
        if (_sprinkles) result += " and sprinkles";
        separator = ", ";
        terminator = ")";
    }
    if (_filling != Unfilled) {
        result += separator + "filled with " + filling_to_string[_filling];
        terminator = ")";
    }
    result += terminator;
    return result;
}
