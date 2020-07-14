#include "shopping.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm> 
#include <numeric>
#include <map>
#include <set>
#include <iomanip>

using std::sort;
using std::make_pair;
using std::set;
using std::pair;
using std::map;
using std::reverse;
using std::vector;
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::getline;
using std::boolalpha;
using std::accumulate;

// LetsGoShopping() is the all encapsulating function that contains all the steps and algorithms for the project

// The header file contains a struct object of type Shopping that takes the item name, quantity, price, store, and location as arguments. 

void LetsGoShopping() {

    // Here we create all of our necessary data structures that we will use to organize and keep track of the data and properties of all 
    // the items we will be reading in. 

    string num_stores;
    string store_name;
    string store_loc;
    string input_line;
    typedef pair<string, string> pairs_loc;
    typedef pair<string, int> pairs_num_items;
    set<pairs_loc> stores_locs;
    vector<pairs_num_items> num_items;
    vector<vector<Shopping>> stores_items;
    map<string, int> all_unique_items;
    vector<pair<string, int>> shopping_list_map;
    vector<string> attributes;
    vector<Shopping> shop_vec;
    vector<string> unique_items;
    vector<string> shopping_list_vec;
    string shopping_item = "";
    string shopping_quantity = "";

    vector<vector<string>> shopping_receipt;
    vector<string> shopping_receipt_per_line;
    
    int line_counter = 1;
    int item_counter = 0;
    double final_price = 0;

    // Below we read in the first line separately since it is a one time occurrence and does not repeat or follow a pattern elsewhere in our input

    getline(cin, num_stores);

    // We now begin our loop to read through the main contents of the file. We will be using a line_counter to keep track of which line we are on
    // within each individual store. This helps us to know what to do with the information of the line we are on. We know that the first line of each data set for each store
    // tells us the name of the store and that the second line tells us the location of the store and that every subsequent line gives us information about the items in the
    // store. Using this pattern we can populate our data structures accordingly. 

    // The general strategy here is to populate "sub" vectors / maps which essentially are vectors / maps that get filled with the necessary inforamtion through each loop and get cleared after pushing that information 
    // into the main vectors / maps that are used to filter through and organize all of the information in such a way that we can identify and relay all of the correct information out to the user. 
    // These data structures make the information we need easily accessible and easy to modify. 

    while(getline(cin, input_line)) {
        if(input_line.length() == 0) {
            stores_items.push_back(shop_vec);

            pairs_num_items num_pair = make_pair(store_name, item_counter);
            
            num_items.push_back(num_pair);
            attributes.clear();
            shop_vec.clear();

            line_counter = 1;
            item_counter = 0;
            unique_items.clear();
            continue;
        }
        if(line_counter == 1) {
            store_name = input_line;
        }
        if(line_counter == 2) {
            store_loc = input_line;
            if(store_loc[0] < 48 || store_loc[0] > 57) {
                pairs_loc store_loc_pair = make_pair(store_name, store_loc);
                stores_locs.insert(store_loc_pair);
            } else {
                for(std::size_t i = 0; i < input_line.length(); i++) {
                    if(input_line[i] == ' ') {
                        shopping_quantity = input_line.substr(0, i);
                        shopping_item = input_line.substr(i+1, input_line.length());
                        break;
                    }
                }
                shopping_list_map.push_back(pair<string, int>(shopping_item, stoi(shopping_quantity)));
                shopping_list_vec.clear();
            }
        }
        if(line_counter > 2) {
            item_counter++;
            if(input_line[0] < 48 || input_line[0] > 57) {
                string buildstr = "";
                // This for loop is used to break apart the input line and format it so that we can make use of each individual aspect.
                for(std::size_t i = 0; i < input_line.length(); i++) {
                    if(input_line[i] == ',') {
                        attributes.push_back(buildstr);
                        buildstr = "";
                    }
                   
                    else if(i == input_line.length() - 1) {
                        buildstr += input_line[i];
                        attributes.push_back(buildstr);
                        buildstr = "";
                    }
                    else {
                        buildstr += input_line[i];
                    }
                }
                
                shop_vec.push_back(Shopping(attributes[0], attributes[1], attributes[2], store_name, store_loc));

                if(all_unique_items.size() > 0) {
                    if(all_unique_items.find(attributes[0]) != all_unique_items.end()) {
                        all_unique_items.at(attributes[0]) += stoi(attributes[1]);
                    } 
                }
                                
                if(all_unique_items.find(attributes[0]) == all_unique_items.end()) {
                    all_unique_items.insert(pair<string, int>(attributes[0], stoi(attributes[1])));
                }
            } else {
                for(std::size_t i = 0; i < input_line.length(); i++) {
                    if(input_line[i] == ' ') {
                        shopping_quantity = input_line.substr(0, i);
                        shopping_item = input_line.substr(i+1, input_line.length());
                        break;
                    }
                }
                shopping_list_map.push_back(pair<string, int>(shopping_item, stoi(shopping_quantity)));
                shopping_list_vec.clear();
            }
            attributes.clear();
        }
        line_counter++;
    }

    cout << "Store Related Information (ordered by in-file order):" << endl;
    cout << "There are " << num_stores[0] << " store(s)." << endl;
    for(auto elem: num_items) {
        cout << elem.first << " has " << elem.second << " distinct items." << endl;
    }
    cout << endl;
    cout << "Item Related Information (ordered alphabetically):" << endl;
    cout << "There are " << all_unique_items.size() << " distinct item(s) available for purchase." << endl;
    for(auto elem: all_unique_items) {
        cout << "There are " << elem.second << " " << elem.first << "(s)." << endl;
    }
    cout << endl;
    cout << "Shopping:" << endl;

    // Below we print out all of the information pertaining to each store including the quantities to buy and prices to pay for each item at each store.

    // We use a similar strategy to the one above in that we create some vectors to hold information that we will need later and feed that vector into a 2D vector which holds all of the 
    // data we will use to organize and sort through the data we've aggregated. Essentially here we use a price check comparison when we need to find the lowest possible price and populate our
    // data structures by adding the items in order of cheapest to most expensive so that we guarantee we purchase the best priced combination of the desired items. 

    for(auto elem: shopping_list_map) {
        int total_stores_selling = 0;
        double total_price_item = 0;
        int quantity_counter = 0;
        double best_price = 0.0;
        string store = "";
        string location = "";
        string best_price_store = "";
        string best_price_location = "";
        string best_price_quantity = "";
        int best_price_quantity_counter = 0;
        vector<string> optimal_price_line_vector;
        vector<vector<string>> optimal_price_vector;
        int optimal_price_vector_quantity_counter = 0;
        cout << "Trying to order " <<  elem.second << " " << elem.first << "(s)." << endl;
        for(auto stores_item: stores_items) {
            for(auto item_property: stores_item) {
                if(item_property.item == elem.first) {
                    total_stores_selling++;
                    store = item_property.store;
                    location = item_property.location;
                    if(best_price == 0.0) {
                        best_price = stod(item_property.price.substr(1, item_property.price.length()));
                        best_price_quantity = item_property.quantity;
                        best_price_store = item_property.store;
                        best_price_location = item_property.location;
                    }
                    if((stoi(item_property.quantity) < all_unique_items.at(elem.first) && stoi(item_property.quantity) > 0) || (elem.second > all_unique_items.at(elem.first))) { 
                        optimal_price_line_vector.push_back(item_property.item);
                        optimal_price_line_vector.push_back(item_property.quantity);
                        optimal_price_line_vector.push_back(item_property.store);
                        optimal_price_line_vector.push_back(item_property.price);
                        optimal_price_line_vector.push_back(item_property.location);

                        optimal_price_vector.push_back(optimal_price_line_vector);
                        optimal_price_line_vector.clear();

                        best_price_quantity_counter += stoi(item_property.quantity);

                        sort(optimal_price_vector.begin(), optimal_price_vector.end(), [](const vector<string> &item1, const vector<string> &item2) {
                            return stod(item1[3].substr(1, item1[3].length())) < stod(item2[3].substr(1, item2[3].length()));
                        });

                        if(best_price_quantity_counter >= all_unique_items.at(elem.first)) {
                            for(auto item: optimal_price_vector) {
                                if(stoi(item[1]) <= elem.second) {
                                    if(stoi(item[1]) <= (elem.second - optimal_price_vector_quantity_counter)) {
                                        total_price_item += stoi(item[1]) * stod(item[3].substr(1, item[3].length()));
                                        shopping_receipt_per_line.push_back(item[1]);
                                        shopping_receipt_per_line.push_back(item[2]);
                                        shopping_receipt_per_line.push_back(item[4]);
                                        shopping_receipt.push_back(shopping_receipt_per_line);
                                        shopping_receipt_per_line.clear();
                                        optimal_price_vector_quantity_counter += stoi(item[1]);
                                    } else {
                                        total_price_item += (elem.second - optimal_price_vector_quantity_counter) * stod(item[3].substr(1, item[3].length()));
                                        shopping_receipt_per_line.push_back(std::to_string((elem.second - optimal_price_vector_quantity_counter)));
                                        shopping_receipt_per_line.push_back(item[2]);
                                        shopping_receipt_per_line.push_back(item[4]);
                                        shopping_receipt.push_back(shopping_receipt_per_line);
                                        shopping_receipt_per_line.clear();
                                        optimal_price_vector_quantity_counter += (elem.second - optimal_price_vector_quantity_counter);
                                    }
                                }
                                if(stoi(item[1]) > elem.second) {
                                    total_price_item += (elem.second - optimal_price_vector_quantity_counter) * stod(item[3].substr(1, item[3].length()));
                                    shopping_receipt_per_line.push_back(std::to_string(elem.second - optimal_price_vector_quantity_counter));
                                    shopping_receipt_per_line.push_back(item[2]);
                                    shopping_receipt_per_line.push_back(item[4]);
                                    shopping_receipt.push_back(shopping_receipt_per_line);
                                    shopping_receipt_per_line.clear();
                                    optimal_price_vector_quantity_counter += (elem.second - optimal_price_vector_quantity_counter);
                                }
                                if(optimal_price_vector_quantity_counter >= elem.second) {
                                    break;
                                }
                            }
                            
                        }
                    }
                    
                    else if(elem.second <= stoi(item_property.quantity) && stoi(item_property.quantity) > 0 && quantity_counter < elem.second) {
                        shopping_receipt_per_line.push_back(std::to_string(elem.second));
                        shopping_receipt_per_line.push_back(store);
                        shopping_receipt_per_line.push_back(location);

                        shopping_receipt.push_back(shopping_receipt_per_line);
                        shopping_receipt_per_line.clear();
                        
                        total_price_item += elem.second * stod(item_property.price.substr(1, item_property.price.length()));
                        quantity_counter += stoi(item_property.quantity);
                        item_property.quantity = "0";
                        best_price = 0.0;
                    }
                }
            }
        }
        final_price += total_price_item;
        cout << total_stores_selling << " store(s) sell " << elem.first << "." << endl;
        cout << std::setprecision(2);
        cout << std::fixed;
        cout << "Total price: $" << total_price_item << endl;
        for(auto receipt_item: shopping_receipt) {
            cout << "Order " << receipt_item[0] << " from " << receipt_item[1] << " in " <<  receipt_item[2] << endl;
        }
        shopping_receipt.clear();
        cout << endl;
        
        }
        cout << std::setprecision(2);
        cout << std::fixed;
        cout << "Be sure to bring $" << final_price << " when you leave for the stores." << endl;

}

int main() {
    LetsGoShopping();
}
