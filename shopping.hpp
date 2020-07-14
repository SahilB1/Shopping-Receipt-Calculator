#ifndef SHOPPING_H
#define SHOPPING_H

#include<string>
#include <vector>

using std::vector;
using std::string;

struct Shopping {
    string item;
    string quantity;
    string price;
    string store;
    string location;
    Shopping() {
        item = "";
        quantity = "";
        price = "";
        store = "";
        location = "";
    }
    Shopping(string item_input, string quantity_input, string price_input, string store_input, string location_input) {
        item = item_input;
        quantity = quantity_input;
        price = price_input;
        store = store_input;
        location = location_input;
    }


};
    
#endif
