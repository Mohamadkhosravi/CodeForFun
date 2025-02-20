#include <iostream>
#include <vector>
#include <cstdint> 

using namespace std;

typedef enum { I2C, SPI, UART } typeofComminaction_t;
typedef enum { NTC, RTD, INFRARED, DHT11 } tempSensor_t;
typedef enum { CO, CO2, SMOKE, HUMIDITY } gasSensor_t;

const char* tempSensorToString(tempSensor_t type) {
    switch (type) {
        case NTC: return "NTC";
        case RTD: return "RTD";
        case INFRARED: return "INFRARED";
        case DHT11: return "DHT11";
        default: return "Unknown";
    }
}

const char* gasSensorToString(gasSensor_t type) {
    switch (type) {
        case CO: return "CO";
        case CO2: return "CO2";
        case SMOKE: return "SMOKE";
        case HUMIDITY: return "Humidity";
        default: return "Unknown";
    }
}

class SensorCommpdnet {
public:
    virtual int readValue() = 0;
    virtual void showInformation() = 0;
    virtual ~SensorCommpdnet() {} 
};

int sensorRead() {
    return 23;
}

class TemperatureSensor : public SensorCommpdnet {
protected:
    uint8_t pin;
public:
    TemperatureSensor(uint8_t pin) : pin(pin) {}
};

class GasSensor : public SensorCommpdnet {
protected:
    typeofComminaction_t communicationType;
public:
    GasSensor(typeofComminaction_t commType) : communicationType(commType) {}
};


class NTCSensor : public TemperatureSensor {
public:
    NTCSensor(uint8_t pin) : TemperatureSensor(pin) {}

    int readValue() override {
        return 25;
    }

    void showInformation() override {
        cout << "Type: NTC | Pin: " << (int)pin << " | Value: " << readValue() << endl;
    }
};

class RTDSensor : public TemperatureSensor {
public:
    RTDSensor(uint8_t pin) : TemperatureSensor(pin) {}

    int readValue() override {
        return 30;
    }

    void showInformation() override {
        cout << "Type: RTD | Pin: " << (int)pin << " | Value: " << readValue() << endl;
    }
};


class COSensor : public GasSensor {
public:
    COSensor(typeofComminaction_t commType) : GasSensor(commType) {}

    int readValue() override {
        return 35;
    }

    void showInformation() override {
        cout << "Type: CO | Communication: " << communicationType << " | Value: " << readValue() << endl;
    }
};

class CO2Sensor : public GasSensor {
public:
    CO2Sensor(typeofComminaction_t commType) : GasSensor(commType) {}

    int readValue() override {
        return 40;
    }

    void showInformation() override {
        cout << "Type: CO2 | Communication: " << communicationType << " | Value: " << readValue() << endl;
    }
};
class SmokeSensor : public GasSensor {  
public:
    SmokeSensor(typeofComminaction_t commType) : GasSensor(commType) {}

    int readValue() override {
        return 45;
    }

    void showInformation() override {
        cout << "Type: Smoke | Communication: " << communicationType << " | Value: " << readValue() << endl;
    }
};
class HumiditySensor : public GasSensor {
public:
    HumiditySensor(typeofComminaction_t commType) : GasSensor(commType) {}

    int readValue() override {
        return 50;
    }

    void showInformation() override {
        cout << "Type: Humidity | Communication: " << communicationType << " | Value: " << readValue() << endl;
    }
};

class SensorGroup : public SensorCommpdnet {
private:
    vector<SensorCommpdnet*> sensors; 
public:
    ~SensorGroup() { 
        for (auto sensor : sensors) {
            delete sensor; 
        }
        sensors.clear();
    }

    void addSensor(SensorCommpdnet* sensor) {
        sensors.push_back(sensor);
    }

    int readValue() override {
        int total = 0;
        for (auto sensor : sensors) {
            total += sensor->readValue();
        }
        return total;
    }

    void showInformation() override {
        for (auto sensor : sensors) {
            sensor->showInformation();
        }
    }
};


int main() {
    SensorGroup sensors;
    sensors.addSensor(new NTCSensor(1));
    sensors.addSensor(new RTDSensor(2));
    sensors.addSensor(new COSensor(UART));
    sensors.addSensor(new CO2Sensor(SPI));
    sensors.addSensor(new SmokeSensor (I2C));
    sensors.addSensor(new HumiditySensor(UART));
    sensors.readValue();
    sensors.showInformation();  
    return 0;
}
