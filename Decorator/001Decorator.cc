#include<iostream>
using namespace std;

enum CoffeeSize{
	small, medium, large
};

class Beverage{
	protected:
		string description = "Unknown Beverage";
		CoffeeSize size;
	public:
		Beverage(){
			size = CoffeeSize::small;
		}
		
		virtual string getDescription(){
			return description;
		}
		virtual double cost() = 0;
		
		void setSize(CoffeeSize s){
			size = s;
		}
		
		CoffeeSize getSize(){
			return size;
		}
};

class CondimentDecorator : public Beverage{
	public:
		string getDescription() = 0;
};

class Espresso : public Beverage{
	public:
		Espresso(){
			description = "Espresso";
		}
		
		double cost(){
			return 1.99;
		}
};

class HouseBlend : public Beverage{
	public:
		HouseBlend(){
			description = "House Blend Coffee";
		}
		
		double cost(){
			return .89;
		}
};

class Whip : public CondimentDecorator {
	Beverage *beverage;
	public:
		Whip(Beverage *b){
			beverage = b;
		}
		
		string getDescription(){
			return beverage->getDescription() + ", Whip";
		}

		double cost(){
			return .15 + beverage->cost();
		}
};

class Mocha : public CondimentDecorator {
	Beverage *beverage;
	public:
		Mocha(Beverage *b){
			beverage = b;
		}
		
		string getDescription(){
			return beverage->getDescription() + ", Mocha";
		}

		double cost(){
			return .20 + beverage->cost();
		}
};

class Soy : public CondimentDecorator {
	Beverage *beverage;
	public:
		Soy(Beverage *b){
			beverage = b;
		}
		
		string getDescription(){
			return beverage->getDescription() + ", Soy";
		}

		double cost(){
			if(getSize() == CoffeeSize::small){
				return .10 + beverage->cost();
			}else if(getSize() == CoffeeSize::medium){
				return .15 + beverage->cost();
			}else{
				return .20 + beverage->cost();
			}	
		}
};


main(){
	Beverage *beverage = new Espresso();
	cout << beverage->getDescription() << " $" << beverage->cost() << endl;
	
	Beverage *beverage2 = new HouseBlend();
	beverage2 = new Mocha(beverage2);
	beverage2 = new Mocha(beverage2);
	beverage2 = new Whip(beverage2);
	cout << beverage2->getDescription() << " $" << beverage2->cost() << endl;
	beverage2 = new Soy(beverage2);
	beverage2->setSize(CoffeeSize::large);
	cout << beverage2->getDescription() << " $" << beverage2->cost() << endl;
}
