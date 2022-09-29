//PWM_READ.h


#ifndef PWM_READ_h
#define PWM_READ_h

#include <Arduino.h>

//try to make this a struct bro

//or find out what its called when you have a class that can only exist as static but also
//also has its own instances
//either make a struct and functions
//or make a static function with static array of pwmReading objects and run a for loop. 

struct PWM_READ { //make this a struct
  
  static float freqErr; //frequency significant error
  static float dutyErr; //duty significant error
  static PWM_READ* PWM_READER; //static instance for referencing in onTrigger interrupt
  static bool hasReading; //flags if a new reading has been received
  
  static void onTrigger(); //interrupt handler
  static float freqCalc(unsigned long cycleTimer); //calculate frequency
  static float dutyCalc(unsigned long dutyTimer, unsigned long cycleTimer); //calculate duty
  static String getWarning(float freq, float duty); //get warning message
  static bool initPWM(int pin); //validate singleton property
  static float getFrequency();
  static float getDuty();
  static void setFreqSigErr(float err); //set frequency significant error
  static void setDutySigErr(float err); //set duty significant error
  


  
  

 
  ~PWM_READ();
  
  private:
    PWM_READ(int pin);
    const int pwmPin;
    bool newFreq = false;
    bool prevState = LOW;

    unsigned long cycleTimer = 0;
    unsigned long dutyTimer = 0;
    unsigned long pwmTimer = 0; 
    float freq = 0, duty  = 0;
  
  
    String warning = "";
    



};


#endif
