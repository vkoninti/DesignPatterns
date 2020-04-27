#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
//Pull Mechanism: observer gets what is needed

class Observer;
class Subject
{
	protected:
		bool changed = false;
		void setChanged(){
				changed= true;
		}
	public:
		virtual void registerObserver(Observer *o) = 0;
		virtual void unregisterObserver(Observer *o) =0;
		virtual void notifyObservers() = 0;
};

class Observer
{
	public:
		virtual void update(Subject *) = 0;
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
			if(changed){
				for(vector<Observer*>::const_iterator iter = list.begin(); iter != list.end(); ++iter)
				{
					if(*iter != 0)
					{
						(*iter)->update(this);
					}
				}
				changed = false;
			}
		}
		void measurementsChanged(){
			setChanged();
			notifyObservers();
		}
		void setMeasurements(float temp, float humidity, float pressure){
			this->temp = temp;
			this->humidity = humidity;
			this->pressure = pressure;
			measurementsChanged();
		}		
		float getTemp(){
		    return temp;
		}		
		float getHumidity(){
		    return humidity;
		}		
		float getPressure(){
		    return pressure;
		}
};

class CurrentConditionsDisplay : public Observer, public DisplayElement {
	float temp;
    float humidity;
    Subject *subject;
	public:
		CurrentConditionsDisplay(Subject *w){
			//weatherData = dynamic_cast<WeatherData*>(w);
			subject = w;
			subject->registerObserver(this);
		}
		void display(){
			cout << "CurrentConditionsDisplay - T: " << temp << " H: " << humidity << endl;
		}
		void unregister(){
		    cout << "Unregister CurrentConditionsDisplay\n";
		    subject->unregisterObserver(this);
		}
		void update(Subject *w){
			WeatherData *wd = dynamic_cast<WeatherData*>(w);
			if(wd != NULL){
				//Pull Mechanism: observer needs only temp and humidity
				this->temp = wd->getTemp();
				this->humidity = wd->getHumidity();
				display();
			}
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
			subject->registerObserver(this);
		}
		void display(){
			cout << "StatisticsDisplay - T: " << temp << " H: " << humidity << " P: " << pressure << endl;
		}
		void unregister(){
		    cout << "Unregister StatisticsDisplay\n";
		    subject->unregisterObserver(this);
		}
		void update(Subject *w){
			WeatherData *wd = dynamic_cast<WeatherData*>(w);
			if(wd != NULL){
				//Pull Mechanism: observer needs temp, pressure and humidity
				this->temp = wd->getTemp();
				this->humidity = wd->getHumidity();
				this->pressure = wd->getPressure();
				display();
			}
		}
};

main(){
	WeatherData *w = new WeatherData();
	StatisticsDisplay s(w);
	CurrentConditionsDisplay c(w);
	w->setMeasurements(12.4,43.2,78.9);
	c.unregister();
	w->setMeasurements(22.4,58.2,89);
	s.unregister();
}
