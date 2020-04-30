#include <iostream>
#include <string>
using namespace std;

enum PizzaType{
    CHEESE,
    VEGGIE,
    PEPPERONI,
    CLAM,
    UNKNOWN
};

class Pizza{
    protected:
    string pizzaType = "Unknown";
    
    public:
    virtual void prepare() = 0;
    virtual void bake() = 0;
    virtual void cut() = 0;
    virtual void box() = 0;
};

class CheesePizza : public Pizza{
    public:
    CheesePizza(){
        pizzaType = "CheesePizza";    
    }
    
    virtual void prepare(){
        cout << "Preparing " << pizzaType << endl;
    }
    
    
    virtual void bake(){
        cout << "Baking " << pizzaType << endl;
    }
    
    
    virtual void cut(){
        cout << "Cutting " << pizzaType << endl;
    }
    
    
    virtual void box(){
        cout << "Boxing " << pizzaType << endl;
    }
};

class VeggiePizza : public Pizza{
    public:
    VeggiePizza(){
        pizzaType = "VeggiePizza";    
    }
    
    virtual void prepare(){
        cout << "Preparing " << pizzaType << endl;
    }
    
    
    virtual void bake(){
        cout << "Baking " << pizzaType << endl;
    }
    
    
    virtual void cut(){
        cout << "Cutting " << pizzaType << endl;
    }
    
    
    virtual void box(){
        cout << "Boxing " << pizzaType << endl;
    }
};


class ClamPizza : public Pizza{
    public:
    ClamPizza(){
        pizzaType = "ClamPizza";    
    }
    
    virtual void prepare(){
        cout << "Preparing " << pizzaType << endl;
    }
    
    
    virtual void bake(){
        cout << "Baking " << pizzaType << endl;
    }
    
    
    virtual void cut(){
        cout << "Cutting " << pizzaType << endl;
    }
    
    
    virtual void box(){
        cout << "Boxing " << pizzaType << endl;
    }
};

class PepperoniPizza : public Pizza{
    public:
    PepperoniPizza(){
        pizzaType = "PepperoniPizza";    
    }
    
    virtual void prepare(){
        cout << "Preparing " << pizzaType << endl;
    }
    
    
    virtual void bake(){
        cout << "Baking " << pizzaType << endl;
    }
    
    
    virtual void cut(){
        cout << "Cutting " << pizzaType << endl;
    }
    
    
    virtual void box(){
        cout << "Boxing " << pizzaType << endl;
    }
};

class SimplePizzaFactory{
    public:
    Pizza* createPizza(PizzaType type){
        Pizza *pizza = nullptr;
        
        switch(type){
            case CHEESE:
            pizza = new CheesePizza;
            break;    
            
            case PEPPERONI:
            pizza = new PepperoniPizza;
            break;    
            
            case CLAM:
            pizza = new ClamPizza;
            break;    
            
            case VEGGIE:
            pizza = new VeggiePizza;
            break;    
            
        }
        return pizza;
    }
};

class PizzaStore{
    SimplePizzaFactory *factory;
    public:
    PizzaStore(SimplePizzaFactory *f){
        factory = f;
    }
    
    Pizza* orderPizza(PizzaType type){
        Pizza *pizza = factory->createPizza(type);
        
        pizza->prepare();
        pizza->bake();
        pizza->cut();
        pizza->box();
        
        return pizza;
    }
};

int main()
{
    Pizza *pizza = nullptr;
    SimplePizzaFactory *factory = new SimplePizzaFactory();
    PizzaStore *pStore = new PizzaStore(factory);
    
    pizza = pStore->orderPizza(PizzaType::CHEESE);
    cout << endl;
    pizza = pStore->orderPizza(PizzaType::CLAM);
    cout << endl;
    
    return 0;
}
