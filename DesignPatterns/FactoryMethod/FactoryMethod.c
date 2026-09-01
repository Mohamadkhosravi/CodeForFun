#include "driver/gpio.h"
#include"esp_log.h"
#define LED_GPIO 2
#define BUZZER_GPIO 3

typedef enum  { LED, BUZZER, FAN,HITTER } DeviceType;
void LED_Init(gpio_num_t pin){};
void LED_ON(){};
void LED_OFF(){};
void LED_Toggle(){};

void BUZZER_Init(gpio_num_t pin){};
void BUZZER_ON(){};
void BUZZER_OFF(){};
void BUZZER_BIB(void* uS ){};

typedef struct  
{  
     void (*init)(gpio_num_t); 
     void (*on)(void); 
     void (*off)(void); 
     
}Device;

Device Devices[]={{LED_Init,LED_ON,LED_OFF},
                 {BUZZER_Init,BUZZER_ON,BUZZER_OFF}};

 
  const Device * CreatDevice(DeviceType type){
  return &Devices[type];
 }

void app_main() {
       const Device *ledRed=CreatDevice(LED);
       const Device *buzzer=CreatDevice(BUZZER);

       ledRed->init(LED_GPIO);
       buzzer->init(BUZZER_GPIO);
       while (1)
       {
       ledRed->on();
       }
       
}