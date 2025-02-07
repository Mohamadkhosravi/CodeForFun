#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define MCU_IS_ESP


#define PIN_LED_RED  2
#define PIN_LED_BLUE 3
#define PIN_BUZZER   4

 enum Mode_t {Non,Input,Output,analog};

class GenericGPIO {
    public:
    //virtual void PinInit(uint32_t pin ,mode Mode) = 0;
    virtual void turnOn() = 0;
    virtual void turnOff() = 0;
    ~ GenericGPIO();
    
};
#ifdef MCU_IS_ESP
class ESP32_GPIO {
    private:

    gpio_num_t Pin;
   
    public:
        ESP32_GPIO(gpio_num_t pin,Mode_t mode) : Pin(pin){
            gpio_reset_pin(Pin);
            gpio_set_direction(Pin, GPIO_MODE_OUTPUT);
        }
        void setHigh(){ gpio_set_level(Pin, 1);}
        void setLow(){ gpio_set_level(Pin, 0);}
       
};
#endif
#ifdef MCU_IS_STM
 class STM_GPIO :public GenericGPIO{
    private:
     uint32_t Pin;
   
    public:
        STM_GPIO(uint32_t pin) : Pin(pin){
            MX_GPIO_Init();
        }
        void setHigh(){HAL_GPIO_WritePin(GPIOB, Pin, GPIO_PIN_SET);}
        void setLow(){ HAL_GPIO_WritePin(GPIOB, Pin, GPIO_PIN_RESET);}
       
       
 };
#endif
#ifdef MCU_IS_AVR
 class AVR_GPIO :public GenericGPIO{
    private:
     Mode_t Mode=Output;
     uint32_t Pin;
   
    public:
        AVR_GPIO(uint32_t pin) : Pin(pin){
           DDRB|= (1 << pin)
        }
            void setHigh(){PORTB |= (1 << Pin);}
            void setLow(){ PORTB |= (0 << Pin);}
       
 };
#endif

class ESP_GPIO_Adapter : public GenericGPIO {
    private:
        ESP32_GPIO* gpio;
    public:
        ESP_GPIO_Adapter(ESP32_GPIO* obj) : gpio(obj) {}
        
        void turnOn() override { gpio->setHigh(); }
        void turnOff() override { gpio->setLow(); }
    };
    
}

/*
class AVR_GPIO_Adapter : public GenericGPIO {
    private:
       AVR_GPIO* gpio;
    public:
        AVR_GPIO_Adapter(AVR_GPIO* obj) : gpio(obj) {}
        
        void setHigh() override { gpio->setHigh(); }
        void setHigh() override { gpio->setLow(); }
    };
    
} */
void setup()
{

}
void loop() {
 vTaskDelay(pdMS_TO_TICKS(500));
}

