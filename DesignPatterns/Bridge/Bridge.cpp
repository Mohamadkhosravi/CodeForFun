
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
public:
    Sensor(CommunicationInterface* comm) : comm(comm) {}
    virtual void sendData() = 0;
    virtual uint16_t readSensor() = 0;
};

class TemperatureSensor : public Sensor {
private:
    String data;
public:
    TemperatureSensor(CommunicationInterface* comm) : Sensor(comm) {}
    uint16_t readSensor() override {
        return analogRead(SENSOR_PIN);
    }
    void sendData() override {
        data = String(readSensor());
        comm->SendData(data);
    }
};

UARTCommunication uart;
I2CCommunication i2c;

TemperatureSensor tempSensor1(&uart);
TemperatureSensor tempSensor2(&i2c);

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

    xTaskCreate(SensorTask, "TempUART", 2048, &tempSensor1, 1, NULL);
    xTaskCreate(SensorTask, "TempI2C", 2048, &tempSensor2, 1, NULL);
}

void loop() {
    
}
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
public:
    Sensor(CommunicationInterface* comm) : comm(comm) {}
    virtual void sendData() = 0;
    virtual uint16_t readSensor() = 0;
};

class TemperatureSensor : public Sensor {
private:
    String data;
public:
    TemperatureSensor(CommunicationInterface* comm) : Sensor(comm) {}
    uint16_t readSensor() override {
        return analogRead(SENSOR_PIN);
    }
    void sendData() override {
        data = String(readSensor());
        comm->SendData(data);
    }
};

UARTCommunication uart;
I2CCommunication i2c;

TemperatureSensor tempSensor1(&uart);
TemperatureSensor tempSensor2(&i2c);

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

    xTaskCreate(SensorTask, "TempUART", 2048, &tempSensor1, 1, NULL);
    xTaskCreate(SensorTask, "TempI2C", 2048, &tempSensor2, 1, NULL);
}

void loop() {
    
}
