/******************************************************************************

	Dynamic Strategy Pattern
	
*******************************************************************************/

#include <iostream>

using namespace std;

class FlyBehaviour{
    public:
    virtual void fly() = 0;    
};

class FlyWithWings : public FlyBehaviour{
    public:
    virtual void fly(){
        cout << "I can FlyWithWings" << endl;
    }
};

class NoFly : public FlyBehaviour{
    public:
    virtual void fly(){
        cout << "I can't Fly" << endl;
    }
};

class FlyRocketPowered : public FlyBehaviour{
    public:
    virtual void fly(){
        cout << "I can Fly using rocket" << endl;
    }
};

class QuackBehaviour{
    public:
    virtual void quack() = 0;
};

class Quack : public QuackBehaviour{
    public:
    virtual void quack(){
        cout << "I quack" << endl;
    }
};

class Squeak : public QuackBehaviour{
    public:
    virtual void quack(){
        cout << "I squeak" << endl;
    }
};

class MuteQuack : public QuackBehaviour{
    public:
    virtual void quack(){
        cout << "I MuteQuack" << endl;
    }
};

class Duck{
    protected:
    QuackBehaviour *qBehaviour;
    FlyBehaviour *fBehaviour;
    public:
    virtual void display() = 0;
    
    void performQuack(){
        qBehaviour->quack();
    }    
    
    void performFly(){
        fBehaviour->fly();
    }  
    
    void setFlyBehaviour(FlyBehaviour *flyBehaviour){
        if(fBehaviour != nullptr){
            delete fBehaviour;
        }
        fBehaviour = flyBehaviour;
    }
    
    void setQuackBehaviour(QuackBehaviour *quackBehaviour){
        if(qBehaviour != nullptr){
            delete qBehaviour;
        }
        qBehaviour = quackBehaviour;
    }
};

class ModelDuck : public Duck{
    public:
    ModelDuck(){
        fBehaviour = new NoFly();
        qBehaviour = new Squeak();
    }
    void display(){
        cout << "I'm ModelDuck" << endl;
    }
};

class MallardDuck : public Duck{
    public:
    MallardDuck(){
        fBehaviour = new FlyWithWings();
        qBehaviour = new Quack();
    }
    void display(){
        cout << "I'm MallardDuck" << endl;
    }
};

int main()
{
   Duck *d = new ModelDuck();
   d->display();
   d->performFly();
   d->performQuack();
   cout << "Changing FlyBehaviour" << endl;
   d->setFlyBehaviour(new FlyRocketPowered());
   d->performFly();
   
   cout << endl;
   
   d = new MallardDuck();
   d->display();
   d->performFly();
   d->performQuack();
   cout << "Changing QuackBehaviour" << endl;
   d->setQuackBehaviour(new MuteQuack());
   d->performQuack();
   
   cout << endl;
   
   return 0;
}
