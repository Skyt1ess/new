#include <iostream>
#include <vector>

using namespace std;

class Products {
private:
    string name;
    double weight;
    double price;
    string date, spoiled_date;
    string type;
    int days;
public:
    Products() = default;

    Products(string name, double weight, double price, string date) {
        set_name(name);
        set_weight(weight);
        set_price(price);
        set_date(date);
    }

    virtual string get_name() const {return name;}
    virtual double get_weight() const {return weight;}
    virtual double get_price() const {return price;}
    virtual string get_date() const {return date;}
    virtual string get_type() const {return type;}

    string get_spoiled_date() const {return spoiled_date;}
    void set_spoiled_date(string date) {spoiled_date = date;}
    virtual void set_name(string name) {this->name = name;}
    virtual void set_weight(double weight) {this->weight = weight;}
    virtual void set_date(string date) {this->date = date;}
    virtual void set_price(double price) {this->price = price;}
    virtual void set_type(string type) {this->type = type;}

    virtual bool get_forsale(Products prod) const {
        if (prod.get_date().substr(6, 4) > prod.get_spoiled_date().substr(6, 4)) return false;
        if (prod.get_date().substr(4, 2) > prod.get_spoiled_date().substr(4, 2)) return false;
        if (prod.get_date().substr(0, 2) > prod.get_spoiled_date().substr(0, 2)) return false;
        return true;
    }

    friend ostream& operator<<(ostream& out, const Products& obj) {
        out << obj.get_name() << ' ' << obj.get_weight() << ' ' << obj.get_price() << ' ' << obj.get_date() << endl;
        return out;
    }

    friend istream& operator>>(istream& in, Products& obj) {
        in >> obj.name;
        return in;
    }
};


class Nonperishable: public Products {
public:
    Nonperishable() = default;

    Nonperishable(string name, double weight, double price, string date): Products(name, weight, price, date) {
        set_type("Nonperishable");
    }

    virtual bool get_forsale(Nonperishable product) const {return true;}

};


class Perishable: public Products {
private:
    string spoiled_date;
public:
    Perishable() = default;

    Perishable(string name, double weight, double price, string date, string spoiled_date): Products(name, weight, price, date) {
        set_spoiled_date(spoiled_date);
        set_type("Perishable");
    }



    virtual bool get_forsale(Perishable prod) const {
        if (prod.get_date().substr(6, 4) > prod.get_spoiled_date().substr(6, 4)) return false;
        if (prod.get_date().substr(4, 2) > prod.get_spoiled_date().substr(4, 2)) return false;
        if (prod.get_date().substr(0, 2) > prod.get_spoiled_date().substr(0, 2)) return false;
        return true;
    }
};


class Shop {
private:
    string status;
    vector<Products> shop;
public:
    vector<Products> get_shop() const {return shop;}

    Products get_ind(int i) const {return shop[i];}

    virtual void list() {
        for (int i = 0; i < shop.size(); i++) {
            cout << shop[i].get_name() << ' ' << shop[i].get_price() << ' ' << shop[i].get_weight() << endl;
        }
    }

    virtual void set_Pweight(int i, double weight) {
        shop[i].set_weight(weight);
    }

    bool isproduct(string name) const {
        for (int i = 0; i < get_shop().size(); i++) {
            if (get_ind(i).get_name() == name) {
                return true;
            } else {return false;}
        }
    }


    void add() {
        string product;
        string command;
        double weight;
        string date, spoiled_date, type;
        int days;
        double price;

while (true) {
            cout << "Enter name of product:\n";
            cin >> product;
            for (int i = 0; i < get_shop().size(); i++) {
                if (product == get_ind(i).get_name()) {
                    cout << "Product has already been added\n";
                    while (true) {
                        cout << "Do you want to change the position?\n";
                        cin >> command;
                        if (command == "Yes") {
                            cout << "Do you want to change weight, price or date?\n";
                            cin >> command;
                            if (command == "weight") {
                                cout << "Enter new weight:\n";
                                cin >> weight;
                                get_ind(i).set_weight(weight);
                                cout << "Weight was changed.\n";
                                continue;
                            } else
                            if (command == "price") {
                                cout << "Enter new price:\n";
                                cin >> price;
                                get_ind(i).set_price(price);
                                cout << "Price was changed.\n";
                                continue;
                            } else
                            if (command == "date") {
                                cout << "Enter new date:\n";
                                cin >> date;
                                get_ind(i).set_date(date);
                                cout << "Date was changed.\n";
                                continue;
                            } else {
                                cout << "See you again!\n";
                                return;
                            }
                        }
                    }
                }
            }
            cout << "Enter weight, price, date and type of product:\n";
            cin >> weight >> price >> date >> type;
            if (type == "Perishable") {
                cout << "Enter spoiled date:\n";
                cin >> spoiled_date;
                Perishable prod(product, weight, price, date, spoiled_date);
                if (prod.get_forsale(prod)){
                   shop.push_back(prod);
                } else {
                    cout << "The product is spoiled.\n";
                    return;
                }
            } else
            if (type == "Nonperishable"){
                Nonperishable prod(product, weight, price, date);
                shop.push_back(prod);
            } else {
                cout << "Wrong type.\n";
                return;
            }
            cout << "The product was added!\n";
            cout << "Do you want to add another position?\n";
            cin >> command;
            if (command == "Yes") continue;
            return;
        }
    }


    void remove() {
        string product;

        cout << "Enter name of product:\n";
        cin >> product;

        if (isproduct(product) == 0) {
            cout << "The product does not exist.\n";
            return;
        } else {
            for (int i = 0; i < get_shop().size(); i++) {
                if (get_ind(i).get_name() == product) {
                    get_shop().erase(get_shop().begin() + i);
                    return;
                }
            }
            cout << "The product was removed.\n";
            return;
        }
    }

    void remove1(string name) {
        if (isproduct(name)) {
            for (int i = 0; i < shop.size(); i++) {
                if (shop[i].get_name() == name) {
                    shop.erase(shop.begin() + i);
                    return;
                }
            }
            return;
        }
    }

    virtual string get_status() const {return status;}
    virtual void set_status(string status) {this->status = status;}

    virtual bool Is_open() {
        if (get_status() == "Open") return true;
        return false;
    }
};

class Customer {
private:
    string Cname;
    vector<Customer> names;
    double budget;
public:
    Customer() = default;
    Customer(string name, double budget) {
        set_Cname(name);
        set_budget(budget);
    }

    virtual string get_Cname() const {return Cname;}
    virtual void set_Cname(string name) {Cname = name;}
    virtual vector<Customer> get_names() const {return names;}
    virtual Customer get_nind(int i) const {return names[i];}
    virtual double get_budget() const {return budget;}
    virtual void set_budget(double new_budget) {budget = new_budget;}
    void remove_customer(string name) {
        for (int i = 0; i < get_names().size(); i++) {
            if (get_names()[i].get_Cname() == name) {
                get_names().erase(get_names().begin() + i);
                return;
            }
        }
    }

    void begin() {
        string name, Cname, command;
        double budget;
        while (true) {
            cout << "Hello. Enter your name:\n";
            cin >> Cname;
            for (int i = 0; i < get_names().size(); i++) {
                if (Cname == get_nind(i).get_Cname()) {
                    cout << "Customer has already been added\n";
                    while (true) {
                        cout << "Do you want to change your profile?\n";
                        cin >> command;
                        if (command == "Yes") {
                            cout << "Do you want to change name or budget?\n";
                            cin >> command;
                            if (command == "name") {
                                cout << "Enter new name:\n";
                                cin >> Cname;
                                get_nind(i).set_Cname(name);
                                cout << "Name was changed.\n";
                                continue;
                            } else
                            if (command == "budget") {
                                cout << "Enter new budget:\n";
                                cin >> budget;
                                get_nind(i).set_budget(budget);
                                cout << "Budget was changed.\n";
                                continue;
                            } else {
                                return;
                            }
                        }
                    }
                }
            }
            cout << "Enter your budget:\n";
            cin >> budget;
            Customer customer(Cname, budget);
            names.push_back(customer);
            cout << "The customer was added!\n";
            cout << "Do you want to add another profile?\n";
            cin >> command;
            if (command == "Yes") continue;
            return;
        }
    }


void buy(Shop& shop) {
        string name, command;
        double weight, price;
        if (shop.get_shop().size() == 0) {
            cout << "The shop is empty.\n";
            cout << "Do you want to add product?\n";
            cin >> command;
            if (command == "Yes") {
                shop.add();
            } else {
                return;
            }
        }
        cout << "Enter name of product you want to buy:\n";
        cin >> name;
        if (shop.isproduct(name)) {
            cout << "Enter the weight:\n";
            cin >> weight;
            for (int i = 0; i < shop.get_shop().size(); i++) {
                if (name == shop.get_ind(i).get_name()) {
                    while (true) {
                        if (shop.get_ind(i).get_forsale(shop.get_ind(i))) {
                            if (weight > shop.get_ind(i).get_weight()) {
                                cout << "The amount of product is not enough.\n";
                                cout << "Do you want to change the weight?\n";
                                cin >> command;
                                if (command == "Yes") {
                                    cout << "Enter new weight:\n";
                                    cin >> weight;
                                    continue;
                                } else {
                                    cout << "Do you want to buy another product?\n";
                                    cin >> command;
                                    if (command == "Yes") buy(shop);
                                    cout << "See you again!";
                                    return;
                                }
                            } else
                            if (weight < shop.get_ind(i).get_weight()) {
                                price = weight * shop.get_ind(i).get_price();
                                if (price > get_budget()) {
                                    cout << "Your budget is not enough.\n";
                                    cout << "Do you want to change the weight?\n";
                                    cin >> command;
                                    if (command == "Yes") {
                                        cout << "Enter new weight:\n";
                                        cin >> weight;
                                        continue;
                                    } else {
                                        cout << "Do you want to buy another product?\n";
                                        cin >> command;
                                        if (command == "Yes") buy(shop);
                                        return;
                                    }
                                } else {
                                    shop.set_Pweight(i, shop.get_ind(i).get_weight() - weight);
                                    set_budget(get_budget() - price);
                                    cout << "Purchase is successful!\n";
                                    return;
                                }
                            } else {
                                if (price > get_budget()) {
                                    cout << "Your budget is not enough.\n";
                                    cout << "Do you want to change the weight?\n";
                                    cin >> command;
                                    if (command == "Yes") {
                                        cout << "Enter new weight:\n";
                                        cin >> weight;
                                        continue;
                                    } else {
                                        cout << "Do you want to buy another product?\n";
                                        cin >> command;
                                        if (command == "Yes") buy(shop);
                                        return;
                                    }
                                } else {

set_budget(get_budget() - price);
                                    shop.remove1(name);
                                    cout << "Purchase is successful!\n";
                                    return;
                                }
                            }
                        }
                    }
                }
            }
        } else {
            cout << "The product does not exist.\n";
            cout << "Do you want to buy another product?\n";
            cin >> command;
            if (command == "Yes") buy(shop);
            return;
        }
    }

    virtual bool find_customer(string name) {
        for (int i = 0; i < get_names().size(); i++) {
            if (name == get_nind(i).get_Cname()) {
                return true;
            }
        }
        return false;
    }
};



int main() {
    Shop shop;
    Customer customer("sjkf", 1000);
    shop.add();
    customer.buy(shop);

    return 0;
}
