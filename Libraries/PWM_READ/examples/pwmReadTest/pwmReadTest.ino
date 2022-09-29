#include "PWM_READ.h"


void setup() {
  // put your setup code here, to run once:
  
 PWM_READ::initPWM(6); //static function initializes PWMREAD instance with a passed in pin. this must be called before using PWM_READER object
 //Object is a pointer called PWM_READER
 //has functions
 //float getFrequency(), float getDuty(), String getWarning( frequency, duty ), void setFreqSigErr(err), void setDutySigErr(err)
 // bool hasReading (has a first value reading), float freqErr (sig error), float dutyErr (sig error)
 
}

unsigned long prevMillis = 0;
void loop() {
  
  if(prevMillis + 2000 < millis() && PWM_READ::hasReading){
    Serial.println("Warning: " + PWM_READ::PWM_READER->getWarning(PWM_READ::PWM_READER->getFrequency(), PWM_READ::PWM_READER->getDuty()));
    Serial.printf("Freq: %f, Duty: %f\n", PWM_READ::PWM_READER->getFrequency(), PWM_READ::PWM_READER->getDuty());
  }
 

  
}
