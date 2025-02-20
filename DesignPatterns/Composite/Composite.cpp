#include <iostream>
#include <vector>
#include <memory>
#include <cstdint> 

using namespace std;

typedef enum { I2C, SPI, UART } typeofComminaction_t;
typedef enum { NTC, RTD, INFRARED, DHT11 } tempSensor_t;

class SensorCommpdnet {
public:
    virtual int readValue() = 0;
    virtual void showInformation() = 0;
    virtual ~SensorCommpdnet() {} 
};

int sensorRead() {
    return 23;
}

class TemperatureSensors : public SensorCommpdnet {
private:
    tempSensor_t typeOfSensor;
    int value;
public:
    TemperatureSensors(tempSensor_t type) : typeOfSensor(type) {}

    int readValue() override {
        value = sensorRead();
        return value;
    }

    void showInformation() override {
        cout << "Type of Sensor: " << typeOfSensor << " | Value: " << readValue() << endl;
    }
};

class NTC : public SensorCommpdnet {
private:
    uint8_t Pin;
public:
    NTC(uint8_t pin) : Pin(pin) {}

    int readValue() override {
        return 25; 
    }

    void showInformation() override {
        cout << "Type: NTC | Value: " << readValue() << endl;
    }
};

class SensorGroup : public SensorCommpdnet {
private:
    vector<shared_ptr<SensorCommpdnet>> sensors;
public:
    void addSensor(shared_ptr<SensorCommpdnet> sensor) {
        sensors.push_back(sensor);
    }

    int readValue() override {
        int total = 0;
        for (auto &sensor : sensors) {
            total += sensor->readValue();
        }
        return total;
    }

    void showInformation() override {
        for (auto &sensor : sensors) {
            sensor->showInformation();
        }
    }
};

int main() {
    auto sensorGroup = make_shared<SensorGroup>();

    auto ntcSensor = make_shared<NTC>(7);
    auto tempSensor = make_shared<TemperatureSensors>(NTC);

    sensorGroup->addSensor(ntcSensor);
    sensorGroup->addSensor(tempSensor);

    cout << "Sensor Group Data:\n";
    sensorGroup->showInformation();

    return 0;
}
