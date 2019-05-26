#include "store.h"
#include "java.h"
#include "donut.h"
#include "to_string.h"
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <iterator>
Store::Store(std::string store_name) : _name{store_name} { }
std::string Store::name() {return _name;}

Store::Store(std::istream& ist){
    int record = 0;
    std::string obj;
    while (std::getline(ist, obj)) {
        ++record;
        if (obj == "#CUSTOMER") _customers.push_back(new Customer{ist});
        else if (obj == "#PRODUCTS(JAVA)"){
            _products.push_back(new Java{ist});

        }
        else if(obj == "#PRODUCTS(DONUT)"){
             _products.push_back(new Donut{ist});
        }
        else if (!obj.size()) throw std::runtime_error{"Invalid object type: " + obj + " at record " + std::to_string(record)};
    }


}


void Store::save(std::ostream& ost) {
    for (auto re : _customers) {
        ost << "#CUSTOMER" << std::endl;
        re->save(ost);
    }
     for (auto pr : _products) {
         ost << "#PRODUCTS";
         pr->save(ost);
    }
}
void Store::add_product(Product* product) {_products.push_back(product);}
int Store::number_of_products() {return _products.size();}
Product* Store::get_product(int product) {return _products[product];}
std::string Store::product_to_string(int product) {
    std::ostringstream oss;
    oss << _products[product]->to_string();
    return oss.str();
}

void Store::add_customer(Customer* customer) {_customers.push_back(customer);}
int Store::number_of_customers() {return _customers.size();}
std::string Store::customer_to_string(int customer) {
    std::ostringstream oss;
    oss << *_customers[customer];
    return oss.str();
}

void Store::place_order(Order order, int customer) {_orders[order] = *_customers[customer];} // Places a new order
int Store::number_of_orders() {return _orders.size(); } // # of orders defined
std::string Store::order_to_string(int order_number) {
    for (auto it : _orders) if (it.first.order_number() == order_number) return to_string(it.first) + "\n" + to_string(it.second);
        throw std::runtime_error{"Order " + std::to_string(order_number) + " not found"};
} // string version of an order

std::ostream& operator<<(std::ostream& ost, Store& store) {
    ost << "Store " << store._name << std::endl << std::endl;
    ost << "Products: " << std::endl;
    for (auto p : store._products) ost << "  " << p->to_string() << std::endl;
        return ost;
}

double Store::cash(){

    return _cash_register;
}
void Store::pay_order(int order_number){
    for (auto it : _orders){

      if (it.first.order_number() == order_number) {
        Order new_order(it.first);
        Customer new_customer = it.second;
        new_order.pay();
        _cash_register += new_order.total_price();
        _orders.erase(it.first);
        _orders[new_order] = new_customer;
        break;
     }
    }
    }

bool Store::order_is_paid(int order_number){
    for (auto it : _orders) if (it.first.order_number() == order_number) return it.first.paid();

}

void Store::fill_order(int order_number){
     for (auto it : _orders){

      if (it.first.order_number() == order_number) {
        Order new_order(it.first);
        Customer new_customer = it.second;
        new_order.fill();
        _orders.erase(it.first);
        _orders[new_order] = new_customer;
        break;
     }
    }
    }

bool Store::order_is_filled(int order_number){
    for (auto it : _orders) if (it.first.order_number() == order_number) return it.first.filled();

}

void Store::discard_order(int order_number){for (auto it : _orders){

      if (it.first.order_number() == order_number) {
        Order new_order(it.first);
        Customer new_customer = it.second;
        new_order.discard();
        _orders.erase(it.first);
        _orders[new_order] = new_customer;
        break;
     }
    }
    }

bool Store::order_is_discarded(int order_number){
    for (auto it : _orders) if (it.first.order_number() == order_number) return it.first.discarded();

}

bool Store::order_is_completed(int order_number){
    for (auto it : _orders) if (it.first.order_number() == order_number) return it.first.completed();

}

bool Store::order_is_pending(int order_number){
    for (auto it : _orders) if (it.first.order_number() == order_number) return it.first.pending();

}

std::pair<Order, Customer>& Store::find_order_pair(int order_number){
    for (auto it : _orders) if (it.first.order_number() == order_number) {
        static std::pair<Order, Customer> found = it;
        return found;
    }

}

