#include <Arduino.h>
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "string.h"

#define PIN_LED_RED  2
#define PIN_LED_BLUE 3
#define PIN_BUZZER   4

class GPIO_Device {
public:
    virtual void init() = 0;
    virtual void on() ;
    virtual void off() = 0;
    virtual ~GPIO_Device() {}

    
};
class LED : public GPIO_Device {
private:
    uint32_t pin;
  
public:
    LED(uint32_t gpio_pin) : pin(gpio_pin) {}
   
    void init() override {
          pinMode((gpio_num_t)pin, GPIO_MODE_OUTPUT);     
    }
    void on()  override { digitalWrite((gpio_num_t)pin,HIGH); }
    void off() override{ digitalWrite((gpio_num_t)pin,LOW);  }
    void toggle() { 
      static bool state;
      state=!state;
      digitalWrite((gpio_num_t)pin,state);
    }
    
};
class buzzer : public GPIO_Device {
private:
    uint32_t pin;
public:
    buzzer(uint32_t gpio_pin) : pin(gpio_pin) {}
   
    void init() override {
          pinMode((gpio_num_t)pin, GPIO_MODE_OUTPUT);     
    }
    void on()  override { digitalWrite((gpio_num_t)pin,HIGH); }
    void off() override{ digitalWrite((gpio_num_t)pin,LOW);  }
    void bibTone (uint32_t delayMs){

      digitalWrite((gpio_num_t)pin,HIGH);
      vTaskDelay(pdMS_TO_TICKS(delayMs));
      digitalWrite((gpio_num_t)pin,LOW);
      vTaskDelay(pdMS_TO_TICKS(delayMs));

      }
};

class GPIO_Factory {
public:
    static GPIO_Device* createDevice( String type,int pin) {
        if (type == "LED") {
          return new LED(pin);
        } else if (type == "Buzzer") {
          return new buzzer(pin);
        }
         return nullptr;
    }
};

GPIO_Device* LEDRed = GPIO_Factory::createDevice("LED", PIN_LED_RED);
GPIO_Device* LEDBlue = GPIO_Factory::createDevice("LED", PIN_LED_BLUE);
GPIO_Device* buzzer1 = GPIO_Factory::createDevice("Buzzer", PIN_BUZZER);

void setup() {
   LEDRed->init();
   LEDBlue->init();
   buzzer1->init(); 
}

void loop() {
  LEDRed->on();
  LEDBlue->off();
  buzzer1->off();
    LED* LEDRed = dynamic_cast<LED*>(LEDRed);
    if (LEDRed) {
        LEDRed->toggle(); 
    } 


}