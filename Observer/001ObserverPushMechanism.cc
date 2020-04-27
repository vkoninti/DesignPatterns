#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
//Push Mechanism: subject sends all attributes irrespective of whether observer needs it or not

class Observer;
class Subject
{
	public:
		virtual void registerObserver(Observer *o) = 0;
		virtual void unregisterObserver(Observer *o) =0;
		virtual void notifyObservers() = 0;
};

class Observer
{
	public:
		virtual void update(float temp, float humidity, float pressure) = 0;
};

class DisplayElement{
	public:
		virtual void display() = 0;
};

class WeatherData : public Subject{
    std::vector<Observer*> list;
    float temp;
    float humidity;
    float pressure;
	public:
		void registerObserver(Observer *o){
			list.push_back(o);
		}
		void unregisterObserver(Observer *o){
			list.erase(remove(list.begin(), list.end(), o), list.end()); 
		}
		void notifyObservers(){
			for(vector<Observer*>::const_iterator iter = list.begin(); iter != list.end(); ++iter)
			{
				if(*iter != 0)
				{
					//Push Mechanism: temp,humidity,pressure(all attributes) even if observer might not need all
					(*iter)->update(temp,humidity,pressure);
				}
			}
		}
		void measurementsChanged(){
			notifyObservers();
		}
		void setMeasurements(float temp, float humidity, float pressure){
			this->temp = temp;
			this->humidity = humidity;
			this->pressure = pressure;
			measurementsChanged();
		}	
};

class CurrentConditionsDisplay : public Observer, public DisplayElement {
	float temp;
    float humidity;
    Subject *subject;
	public:
		CurrentConditionsDisplay(Subject *w){
			subject = w;
			w->registerObserver(this);
		}
		
		void display(){
			cout << "CurrentConditionsDisplay - T: " << temp << " H: " << humidity << endl;
		}
		
		void update(float temp, float humidity, float pressure){
			this->temp = temp;
			this->humidity = humidity;
			display();
		}
		
		void unregister(){
		    subject->unregisterObserver(this);
		}
};

class StatisticsDisplay : public Observer, public DisplayElement {
	float temp;
    float humidity;
    float pressure;
    Subject *subject;
	public:
		StatisticsDisplay(Subject *w){
			subject = w;
			w->registerObserver(this);
		}
		void display(){
			cout << "StatisticsDisplay - T: " << temp << " H: " << humidity << " P: " << pressure << endl;
		}
		
		void update(float temp, float humidity, float pressure){
			this->temp = temp;
			this->humidity = humidity;
			this->pressure = pressure;
			display();
		}
		
		void unregister(){
		    subject->unregisterObserver(this);
		}
};

main(){
	WeatherData *w = new WeatherData();
	StatisticsDisplay s(w);
	CurrentConditionsDisplay c(w);
	w->setMeasurements(12.4,43.2,78.9);
	w->setMeasurements(22.4,58.2,89);
	s.unregister();
	c.unregister();
}
