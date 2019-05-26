#ifndef MAINWIN_H
#define MAINWIN_H

#include <gtkmm.h>
#include "store.h"
#include "customer.h"
#include "dialogs.h"
#include <exception>
#include <fstream>
#include <iostream>
enum class Show{Show, Fill, Pay, Discard };
class Mainwin : public Gtk::Window
{
    public:
        Mainwin();
        virtual ~Mainwin();
    protected:
        void on_quit_click();            // Exit the program
        void on_view_all_click();        // View all products
        void on_create_coffee_click();   // Create a new coffee product
        void on_create_donut_click();    // Create a new donut product
	void on_create_order_click();
        void on_list_customers_click();  // List all customers
        void on_new_customer_click();    // Create a new customer
        void on_about_click();           // About dialog
	void on_new_order_click();
	void on_save_click();
	void on_open_click();
	void on_view_orders_click();
	void on_fill_click();
        void on_pay_click();
        void on_discard_click();
        void on_test_click();

    private:
        Store _store;
        Gtk::Label *msg; 
        Gtk::Label *cash;     
        Gtk::MenuItem *menuitem_new_coffee;   // Create -> Coffee
        Gtk::MenuItem *menuitem_new_donut;    // Create -> Donut
	Gtk::MenuItem *menuitem_new_order;  
	Customer _customer;
	Dialogs _dialogs;
	std::string _filename;
    Gtk::Window* _window;
    bool _gui;
 void set_message(std::string message);
        void update_cash();
        void process_order(Show show);

};
#endif 

