#include "driver/gpio.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

typedef unsigned char uint8_t;
typedef struct {
    uint8_t initialized;
} Handle_t;

#define LED_PIN 2
typedef Handle_t GPIO_Handler;

GPIO_Handler *GPIO_Instance(){
    static GPIO_Handler Instance = {0};
    return &Instance;
}

void GPIO_Init(){
    GPIO_Handler* gpio = GPIO_Instance();  

    if (!gpio->initialized){
        gpio_reset_pin(LED_PIN);
        gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);
        gpio->initialized = 1;
        ESP_LOGI("GPIO", "GPIO Initialized.");
    } 
}

void GPIO_Toggle() {
    static uint8_t state = 0;
    state = !state;
    gpio_set_level(LED_PIN, state);
    ESP_LOGI("GPIO", "LED State: %d", state);
}

void app_main() {
    GPIO_Init(); 
    while (1) {
        GPIO_Toggle();
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
