#include "mainwin.h"
#include "customer.h"
#include <iostream>
#include <gtkmm.h>
#include "dialogs.h"
#include<string>
#include "store.h"


// /////////
// Help Menu


void Mainwin::on_fill_click() {
	msg->set_text("");
	Gtk::Dialog *dialog = new Gtk::Dialog{"Please, Select an Order to Fill", *this};

	Gtk::Label l_current;
	dialog->get_vbox()->pack_start(l_current, Gtk::PACK_SHRINK);

	Gtk::HBox hb_orders;
	Gtk::Label label1{"Order:"};
	label1.set_width_chars(15);
	hb_orders.pack_start(label1, Gtk::PACK_SHRINK);

	Gtk::ComboBoxText combo_orders;
	for(int i=0; i<_store.number_of_orders(); ++i) {
		combo_orders.append(std::to_string(i));
	}
	hb_orders.pack_start(combo_orders, Gtk::PACK_SHRINK);
	dialog->get_vbox()->pack_start(hb_orders, Gtk::PACK_SHRINK);

    // Show dialog
	dialog->add_button("Close", 0);
	dialog->add_button("Show", 1);
	dialog->add_button("Fill", 2);
	dialog->show_all();

	int result; 

	while (true) {
		result = dialog->run();
		if (result == 0) {delete dialog; return;}
		else if(result ==1) {l_current.set_text(_store.order_to_string(combo_orders.get_active_row_number()));}
		else if(result ==2)
		{
			int order_num = combo_orders.get_active_row_number();
			_store.fill_order(order_num);   
			int return_ans = Gtk::MessageDialog{*this,"The requested order was filled. Thank you"}.run();
			msg->set_text("The requested order was filled. Thank you");
			delete dialog;
			break;
		}
	}
}

void Mainwin::on_pay_click() {

	msg->set_text("");
	Gtk::Dialog *dialog = new Gtk::Dialog{"Please, select an Order to Pay", *this};


	Gtk::Label l_current;
	dialog->get_vbox()->pack_start(l_current, Gtk::PACK_SHRINK);

	Gtk::HBox hb_orders;
	Gtk::Label label1{"Order:"};
	label1.set_width_chars(15);
	hb_orders.pack_start(label1, Gtk::PACK_SHRINK);

	Gtk::ComboBoxText combo_orders;
	for(int i=0; i<_store.number_of_orders(); ++i) {
		combo_orders.append(std::to_string(i));
	}
	hb_orders.pack_start(combo_orders, Gtk::PACK_SHRINK);
	dialog->get_vbox()->pack_start(hb_orders, Gtk::PACK_SHRINK);

    // Show dialog
	dialog->add_button("Close", 0);
	dialog->add_button("Show", 1);
	dialog->add_button("Pay Now", 2);
	dialog->show_all();

    int result; // of the dialog (1 = OK)
    while (true) {
    	result = dialog->run();
    	if (result == 0) {delete dialog; return;}
    	else if(result ==1) {l_current.set_text(_store.order_to_string(combo_orders.get_active_row_number()));}
    	else if(result ==2)
    		{	int order_num = combo_orders.get_active_row_number();
    			try{
    				_store.pay_order(order_num);
    			}
    			catch(int x){
    				int return_va = Gtk::MessageDialog{*this,"Payment wasn't processed..."}.run();

    			}


    			int return_ans = Gtk::MessageDialog{*this,"Successfully Paid..."}.run();
    			msg->set_text("Successfully Paid...");
    			cash->set_text("Cash: $"+std::to_string(_store.cash()));
    			
    			delete dialog;
    			break;
    		}
    	}

    }

    void Mainwin::on_discard_click() {

    	msg->set_text("");
    	Gtk::Dialog *dialog = new Gtk::Dialog{"Please, Select an Order to Discard", *this};

    	Gtk::Label l_current;
    	dialog->get_vbox()->pack_start(l_current, Gtk::PACK_SHRINK);

    	Gtk::HBox hb_orders;
    	Gtk::Label label1{"Order:"};
    	label1.set_width_chars(15);
    	hb_orders.pack_start(label1, Gtk::PACK_SHRINK);

    	Gtk::ComboBoxText combo_orders;
    	for(int i=0; i<_store.number_of_orders(); ++i) {
    		combo_orders.append(std::to_string(i));
    	}
    	hb_orders.pack_start(combo_orders, Gtk::PACK_SHRINK);
    	dialog->get_vbox()->pack_start(hb_orders, Gtk::PACK_SHRINK);

    // Show dialog
    	dialog->add_button("Close", 0);
    	dialog->add_button("Show", 1);
    	dialog->add_button("Discard", 2);
    	dialog->show_all();

    	int result; 
    	while (true) {
    		result = dialog->run();
    		if (result == 0) {delete dialog; return;}
    		else if(result ==1) {l_current.set_text(_store.order_to_string(combo_orders.get_active_row_number()));}
    		else if(result ==2)
    		{
    			int order_num = combo_orders.get_active_row_number()-1;
    			_store.discard_order(order_num);
    			int x = Gtk::MessageDialog{*this,"Successfully discarded the selected order..."}.run();
    			msg->set_text("Successfully discarded the selected order..");
    			delete dialog;
    			break;
    		}
    	}
    }

  


