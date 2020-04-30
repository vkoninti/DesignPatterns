#include <iostream>
#include <string>
#include <vector>
using namespace std;

enum PizzaType{
    NY_CHEESE,
    NY_VEGGIE,
    CH_CHEESE,
    CH_VEGGIE,
    UNKNOWN
};

class Pizza{
    protected:
    string name;
    string dough;
    string sauce;
    vector<string> toppings;
    
    public:
    string getName(){
        return name;
    }
    
    virtual void prepare(){
        cout << "Preparing " << name << endl;
        cout << "Tossing " << dough << endl;
        cout << "Adding " << sauce << endl;
        cout << "Adding toppings" << endl;
        for(string s : toppings){
            cout << s  << ", " ;
        }
        cout << endl;
    }
    
    virtual void bake(){
        cout << "Bake for 25 minutes at 350" << endl;
    }
    
    virtual void cut(){
        cout << "Cutting the pizza into diagonal slices" << endl;
    }
    
    virtual void box(){
        cout << "Place pizza in official PizzaStore box" << endl;
    }
};

class NYStyleCheesePizza : public Pizza{
    public:    
    NYStyleCheesePizza(){
        name = "NY Style Sauce and Cheese Pizza";
        dough = "Thin Crust Dough";
        sauce = "Marinara Sauce";
        toppings.push_back("Grated Reggiano Cheese");
    }
};

class ChicagoStyleCheesePizza : public Pizza {
    public:
    ChicagoStyleCheesePizza() {
        name = "Chicago Style Deep Dish Cheese Pizza";
        dough = "Extra Thick Crust Dough";
        sauce = "Plum Tomato Sauce";
        toppings.push_back("Shredded Mozzarella Cheese");
    }
    
    void cut() {
        cout << "Cutting the pizza into square slices" << endl;
    }
};

class NYStyleVeggiePizza : public Pizza{
    public:    
    NYStyleVeggiePizza(){
        name = "NY Style Sauce and Veggie Pizza";
        dough = "Thin Crust Dough";
        sauce = "Pineapple Sauce";
        toppings.push_back("Sliced onions");
        toppings.push_back("Corn");
    }
};

class ChicagoStyleVeggiePizza : public Pizza {
    public:
    ChicagoStyleVeggiePizza() {
        name = "Chicago Style Veggie Pizza";
        dough = "Thick Crust Dough";
        sauce = "Chilli Sauce";
        toppings.push_back("Capsicum");
        toppings.push_back("Mushroom");
        toppings.push_back("Tomato");
    }
    
    void cut() {
        cout << "Cutting the pizza into square slices" << endl;
    }
};

class PizzaStore{
    public:
    virtual Pizza* createPizza(PizzaType type) = 0;
    
    Pizza* orderPizza(PizzaType type){
        Pizza* pizza = createPizza(type);
        
        pizza->prepare();
        pizza->bake();
        pizza->cut();
        pizza->box();
        
        return pizza;
    }
};

class NewYorkStylePizzaStore : public PizzaStore {
    Pizza *pizza;
    public:
    Pizza* createPizza(PizzaType type){
        switch(type){
            case NY_CHEESE:
                pizza = new NYStyleCheesePizza;
                break;
            case NY_VEGGIE:
                pizza = new NYStyleVeggiePizza;
                break;
        }
        return pizza;
    }
};

class ChicagoStylePizzaStore : public PizzaStore {
    Pizza *pizza;
    public:
    Pizza* createPizza(PizzaType type){
        switch(type){
            case CH_CHEESE:
                pizza = new ChicagoStyleCheesePizza;
                break;
            case CH_VEGGIE:
                pizza = new ChicagoStyleVeggiePizza;
                break;
        }
        return pizza;
    }
};

int main()
{
    PizzaStore *nyStore = new NewYorkStylePizzaStore;
    PizzaStore *chStore = new ChicagoStylePizzaStore;
    
    Pizza *pizza = nullptr;
    
    pizza = nyStore->orderPizza(NY_CHEESE);
    cout << "Ethan ordered " << pizza->getName() << endl << endl;
    
    pizza = chStore->orderPizza(CH_VEGGIE);
    cout << "Joel ordered " << pizza->getName() << endl << endl;
    
    return 0;
}
