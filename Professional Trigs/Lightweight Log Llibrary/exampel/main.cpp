
#include <iostream>
#include<Logger.h>
void motor_init() ;
void motor_check_temp(int temp);
int main() {
    motor_init();
    motor_check_temp(85); 
    return 0;
}

void motor_init() {
    LOG_INFO("motor init done");
}

void motor_check_temp(int temp) {
    if (temp > 80)
        LOG_WARN("temp high: %d", temp);
    if (temp > 100)
        LOG_ERROR("motor overheating!");
}