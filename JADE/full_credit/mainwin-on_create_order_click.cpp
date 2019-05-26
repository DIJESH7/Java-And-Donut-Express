#include "mainwin.h"
#include "donut.h"


// //////////////////
// Create a new order
template<class T> 
std::string to_string(const T& t) {
    std::ostringstream os;
    os << t;
    return os.str();
}
void Mainwin::on_create_order_click() {
    if (_store.number_of_customers() == 0) {
       int result = Gtk::MessageDialog{*this, "Create a Customer first!"}.run();
       return;
    }

    Order order;
    Gtk::Dialog *dialog = new Gtk::Dialog{"Create an Order", *this};

    // List of current order contents
    Gtk::Label label_current;
    dialog->get_vbox()->pack_start(label_current, Gtk::PACK_SHRINK);

    // Predefined products
    Gtk::HBox box_pre;

    Gtk::Label label_pre{"Product:"};
    label_pre.set_width_chars(15);
    box_pre.pack_start(label_pre, Gtk::PACK_SHRINK);

    Gtk::ComboBoxText c_pre;
    //c_pre.set_max_length(50);
    for(int i=0; i<_store.number_of_products(); ++i) {
        c_pre.append(_store.product_to_string(i));
    }
    box_pre.pack_start(c_pre, Gtk::PACK_SHRINK);
    dialog->get_vbox()->pack_start(box_pre, Gtk::PACK_SHRINK);

    // Show dialog
    dialog->add_button("Cancel", 0);
    dialog->add_button("Add", 1);
    dialog->add_button("Next", 2);
    dialog->show_all();

    int result; // of the dialog (1 = OK)

    while (true) {
        label_current.set_text(to_string(order));

        result = dialog->run();
        if (result == 0) {delete dialog; return;}
        if (result == 1) {order.add_product(_store.get_product(c_pre.get_active_row_number()));}
        if (result == 2) break;
    }

    // Select Customer
    delete dialog;
    dialog = new Gtk::Dialog{"Select Customer", *this};

    Gtk::ComboBoxText c_cust;
    for (int i=0; i<_store.number_of_customers(); ++i) {
        c_cust.append(_store.customer_to_string(i));
    }
    dialog->get_vbox()->pack_start(c_cust, Gtk::PACK_SHRINK);

    dialog->add_button("Cancel", 0);
    dialog->add_button("Place Order " + std::to_string(order.order_number()), 1);
    dialog->show_all();

    result = dialog->run();

    // Place order
    if (result == 1) {
        _store.place_order(order, c_cust.get_active_row_number());
        msg->set_text("Order " + std::to_string(order.order_number()) + " placed");
    } else {
        msg->set_text("Order " + std::to_string(order.order_number()) + " cancelled");
    }
    delete dialog;
}
