#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define PIN_LED_RED  2
#define PIN_LED_BLUE 3
#define PIN_BUZZER   4

class GPIO_Device {
public:
    virtual void init() = 0;
    virtual void on() = 0;
    virtual void off() = 0;
    virtual ~GPIO_Device() {}
};

class LED : public GPIO_Device {
private:
    uint32_t pin;
public:
    LED(uint32_t gpio_pin) : pin(gpio_pin) {}
    void init() override { pinMode((gpio_num_t)pin, GPIO_MODE_OUTPUT); }
    void on() override { digitalWrite((gpio_num_t)pin, HIGH); }
    void off() override { digitalWrite((gpio_num_t)pin, LOW); }
    void toggle(){ 
        static bool state = false;
        state = !state;
        digitalWrite((gpio_num_t)pin, state);
    }
};

class Buzzer : public GPIO_Device {
private:
    uint32_t pin;
public:
    Buzzer(uint32_t gpio_pin) : pin(gpio_pin) {}
    void init() override { pinMode((gpio_num_t)pin, GPIO_MODE_OUTPUT); }
    void on() override { digitalWrite((gpio_num_t)pin, HIGH); }
    void off() override { digitalWrite((gpio_num_t)pin, LOW); }
    void bibTone(uint32_t delayMs) {
        digitalWrite((gpio_num_t)pin, HIGH);
        vTaskDelay(pdMS_TO_TICKS(delayMs));
        digitalWrite((gpio_num_t)pin, LOW);
    }
};

class GPIO_Factory {
public:
    static GPIO_Device* createDevice(const String& type, int pin) {
        if (type == "LED") {
            return new LED(pin);
        } else if (type == "Buzzer") {
            return new Buzzer(pin);
        }
        return nullptr;
    }
};


GPIO_Device* LEDRed = GPIO_Factory::createDevice("LED", PIN_LED_RED);
GPIO_Device* LEDBlue = GPIO_Factory::createDevice("LED", PIN_LED_BLUE);
GPIO_Device* buzzer1 = GPIO_Factory::createDevice("Buzzer", PIN_BUZZER);
LED* ledRed = static_cast<LED*>(LEDRed);

void setup() {
    if (LEDRed) LEDRed->init();
    if (LEDBlue) LEDBlue->init();
    if (buzzer1) buzzer1->init();
}

void loop() {
   
    if (ledRed) {// static cast is ok 
        while (1) {
            vTaskDelay(pdMS_TO_TICKS(500));
            ledRed->toggle();
        }
    }
}
