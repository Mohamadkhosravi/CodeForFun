#include <iostream>
#include <stdio.h>
#include "string.h"

/*   case RAW:        return &noFilter;
 case AVERAGE:    return &avgFilter;
 case EXPONENTIAL:return &expFilter;
 case MEDIAN:     return &medianFilter;
 case LOWPASS:    return &lowpassFilter;
 case KALMAN:     return &kalmanFilter;*/
class FilterStrategy{
public:
    FilterStrategy(){};
    virtual float apply(float RawData);
    virtual char *name(void);
};
class noFilter :public FilterStrategy{
private:
   std::string Name="NoFilter";
public:
    noFilter();
    void apply();
    char* name();
    
};
class kalman :public FilterStrategy{
private:
   std::string Name="Kalman";
public:
    kalman();
    void apply();
    char* name();
    
};
class  avarage  :public FilterStrategy{
private:
   std::string Name="Avarage";
public:
    avarage();
    void apply();
    char* name();
    
};
class median :public FilterStrategy{
private:
   std::string Name="Median";
public:
    median();
    void apply();
    char* name();
    
};
class lowPass :public FilterStrategy{
private:
   std::string Name="LowPass";
public:
    lowPass();
    void apply();
    char* name();
    
};

class Filter{
private:
    FilterStrategy* Strategy;
    void setFilter(FilterStrategy* strategy ){
        Strategy=strategy;
        
    }
    Filter();
    float readFilter(float raw){
        return Strategy->apply(raw);
    }
    
};
int main() {
    
    return 0;
}
