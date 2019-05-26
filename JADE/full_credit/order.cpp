#include "order.h"
#include <iostream>
#include <ostream>
#include <sstream>
int Order::_next_order_number = 0;

Order::Order() : _order_number{_next_order_number++}, _is_paid{false}, _is_filled{false},_is_discarded{false} { }
Order::Order( const Order &other){
	_next_order_number = other.next_order_number();
	_order_number = other.order_number();
	_is_paid = other.paid();
	_is_filled = other.filled();
	_is_discarded = other.discarded();
	for(int i = 0; i < other._products.size();i++)
	{	
		_products.push_back(other._products[i]);
	}

}
double Order::total_price(){
	double total;
	for(int i=0;i<_products.size();i++){
	total =total+ _products[i]->price();
}
if(_is_paid == true)
{
	return total;
}else return 0.0;
}
int Order::order_number() const {return _order_number;}
void Order::add_product(Product* product) {_products.push_back(product);}
int Order::next_order_number()const{return _next_order_number;}
bool Order::paid()const {return _is_paid;}
void Order::pay() {
	if(_is_paid==false && _is_discarded==false)
	{
		_is_paid = true;		
}
}
bool Order::filled() const {return _is_filled;}
void Order::fill() {
	if(_is_filled==false && _is_discarded==false)
	{
		_is_filled = true;
}
}

bool Order::discarded() const {return _is_discarded;}

void Order::discard() {
	if(_is_discarded==false && completed()==false)
	{
	_is_discarded = true;
}
}

bool Order::pending() const {
	if(_is_filled==false || _is_paid==false){

		return true;
	}
	return false;
}

bool Order::completed() const {
	if(filled()==true && paid()== true){
		return true;
	}
	return false;
}
double Order::profit() {

	double total_profit = 0.0;

	for (int i =0;i < _products.size();i++)
{
	total_profit += _products[i]->profit();
}
return total_profit;
}

std::ostream& operator<<(std::ostream& ost, const Order& order) {
	if(order.discarded()== true){
    	ost << "Order #" << order._order_number << "("<<"discarded" <<")"<<":";
	}else if(order.paid()== true){
    	ost << "Order #" << order._order_number << "("<<"paid" <<")"<<":";
	}
	else if(order.filled()== true){
    	ost << "Order #" << order._order_number << "("<<"filled" <<")"<<":";
	}

	else if(order.pending()== true){
    	ost << "Order #" << order._order_number << "("<<"pending" <<")"<<":";
	}
	else{
    ost << "Order #" << order._order_number << ":";
   }
    std::string separator = "\n  ";
    for (auto p : order._products) {
        ost << separator << p->to_string();
    }
    return ost;
}

bool operator<(const Order& lhs, const Order& rhs) {
    return lhs.order_number() < rhs.order_number();
}


template<class T> 
std::string to_string(const T& t) {
    std::ostringstream os;
    os << t;
    return os.str();
}
