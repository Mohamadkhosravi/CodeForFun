#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>


#define ENABLE 1
#define DISABLE 0

#define DEBUG      ENABLE
#define COLOR_LOG  ENABLE


#define LOGER      printf
//#define LOGER      Serial.printf

#if COLOR_LOG
    #define COLOR_RESET   "\x1b[0m"
    #define COLOR_RED     "\x1b[31m"
    #define COLOR_GREEN   "\x1b[32m"
    #define COLOR_YELLOW  "\x1b[33m"
    #define COLOR_CYAN    "\x1b[36m"
#else
    #define COLOR_RESET   ""
    #define COLOR_RED     ""
    #define COLOR_GREEN   ""
    #define COLOR_YELLOW  ""
    #define COLOR_CYAN    ""
#endif
 #if DEBUG
    #define LOG_INFO(format, ...)LOGER(COLOR_GREEN "[INFO] %s::%s(%d): " COLOR_RESET format "\n", __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)
    #define LOG_WARN(format, ...)LOGER(COLOR_YELLOW "[WARN] %s::%s(%d): " COLOR_RESET format "\n", __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)
    #define LOG_ERR(format, ...)LOGER(COLOR_RED "[ERR] %s::%s(%d): "COLOR_RESET format "\n", __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)
 #else
    #define LOG_INFO(format, ...)      
    #define LOG_WARN(format, ...) 
    #define LOG_ERR(format, ...) 
 #endif

#endif