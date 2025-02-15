#include <iostream>
using namespace std;

typedef enum{
NTC,
RTD,
INFRARED,
DHT11,
}
tempSensor_t;
class SensorCommpdnet{
virtual int readValue()=0;
virtual void showInformation()=0;

};
int sensorRead(){
return 23;
}
class TemperatureSensors : public SensorCommpdnet
{
private:
tempSensor_t typeOfSensor;
  int value;
public:
    TemperatureSensors (tempSensor_t type):typeOfSensor(type){
    };
    int readValue() override{
        value=sensorRead();
    }
    void showInformation() override{
        cout<<"Type of Sensor is " << typeOfSensor<<"and value is :"<<value << endl;
    }
    ~TemperatureSensors ();
};

class NTC : public SensorCommpdnet{
    private:
    uint8_t Pin;
    public:
    NTC(uint8_t pin):Pin(pin){};
    int readValue() override{
     //analogRead(pin)
     return 25;
    }
    void showInformation() override{
        cout<<"Type of Sensor is NTC and value is :"<<readValue()<< endl;
    }
} ;
class  RTD : public SensorCommpdnet{
    private:
    uint8_t Pin;
    public:
   RTD(uint8_t pin):Pin(pin){};
    int readValue() override{
     //analogRead(pin)
     return 45;
    }
    void showInformation() override{
        cout<<"Type of Sensor is RTD and value is :"<<readValue()<< endl;
    }
} ;

class SensorGroup : public SensorCommpdnet {
    private:
        std::vector<SensorCommpdnet*> sensors;   
        public:
        void addSensor(SensorCommpdnet* sensor) {
            sensors.push_back(sensor);
        }
    
        int readValue() override {
            // Serial.println("Reading all sensors:");
            for (auto & sensors : sensors) {
            
            
            }
        }
        void showInformation() override {
            for (auto & sensors : sensors) {
                
            }
        }
    };

int main(int argc, char const *argv[])
{   string FirstName=" ";
    cout << "Enter your first name: ";
    cin>>FirstName;
    cout<<"\n ====================\n";
    cout<<"Hello " << FirstName<<"!"<<endl;
    return 0;
}
