#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "HardwareSerial.h"
#include "Wire.h"

#define PIN_LED_RED  2
#define PIN_LED_BLUE 3
#define PIN_BUZZER   4
#define SENSOR_PIN   5

class CommunicationInterface {
public:
    virtual void SendData(String &Data) = 0;
};

class UARTCommunication : public CommunicationInterface {
private:
    uint32_t baudRate = 9600;
public:
    UARTCommunication() {
        Serial1.begin(baudRate);
    }
    void SendData(String &Data) override {
        Serial1.printf("Sending with UART: %s\n", Data.c_str());
    }
};

class I2CCommunication : public CommunicationInterface {
private:
    uint8_t address = 0x2;
public:
    I2CCommunication() {
        Wire.begin();
    }
    void SendData(String &Data) override {
        Wire.beginTransmission(address);
        Wire.write(Data.c_str());
        Wire.endTransmission();
    }
};

class Sensor {
protected:
    CommunicationInterface* comm;
    uint8_t pin;
public:
    Sensor(CommunicationInterface* comm,uint8_t pin) : comm(comm), pin(pin)  {
        pinMode(pin, INPUT);
    }
    virtual void sendData() = 0;
    virtual uint16_t readSensor() = 0;
};

class TemperatureSensor : public Sensor {
private:
   
    uint8_t pin;
public:
    TemperatureSensor(CommunicationInterface* comm, uint8_t pin) : Sensor(comm, pin) {}
    uint16_t readSensor() override {
        return analogRead(pin);
    }
    void sendData() override {
        String data = "Temp from PIN " + String(pin) + ": " + String(readSensor());
        comm->SendData(data);
    }
};

class GasSensor : public Sensor {
    public:
        GasSensor(CommunicationInterface* comm, uint8_t pin) : Sensor(comm, pin) {}
        
        uint16_t readSensor() override {
            return analogRead(pin);
        }
        
        void sendData() override {
            String data = "Gas Level from PIN " + String(pin) + ": " + String(readSensor());
            comm->SendData(data);
        }
    };

UARTCommunication uart;
I2CCommunication i2c;

TemperatureSensor tempSensor1(&uart,32);
TemperatureSensor tempSensor2(&i2c,33);
GasSensor gasSensor(&uart, 34);

void SensorTask(void* parameter) {
    TemperatureSensor* sensor = (TemperatureSensor*)parameter;
    while (1) {
        sensor->sendData();
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void setup() {
    Serial.begin(115200);
    pinMode(SENSOR_PIN, INPUT);

    xTaskCreate(SensorTask, "Temp1Task", 1024, &tempSensor1, 1, NULL);
    xTaskCreate(SensorTask, "Temp2Task", 1024, &tempSensor2, 1, NULL);
    xTaskCreate(SensorTask, "GasTask", 1024, &gasSensor, 1, NULL);


void loop() {
    
}
