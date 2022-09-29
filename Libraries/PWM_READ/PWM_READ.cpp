//PWM_READ.cpp
#include "PWM_READ.h"

float PWM_READ::freqErr = 2.5;
float PWM_READ::dutyErr = 1.0;
void PWM_READ::setFreqSigErr(float err){
  freqErr = err;
}
void PWM_READ::setDutySigErr(float err){
  dutyErr = err;
}


PWM_READ* PWM_READ::PWM_READER = nullptr;
bool PWM_READ::hasReading = false; 

float PWM_READ::freqCalc(unsigned long cycleTimer){
  return (1000000 / (float)(cycleTimer));
}

float PWM_READ::dutyCalc(unsigned long dutyTimer, unsigned long cycleTimer){
  return (float) dutyTimer / cycleTimer * 100;
}

float PWM_READ::getFrequency(){
  if(PWM_READER == nullptr) return 0.0;

  return PWM_READER->freq;
}

float PWM_READ::getDuty(){
  if(PWM_READER == nullptr) return 0.0;

  return PWM_READER->duty;
}

void PWM_READ::onTrigger(){
  hasReading = true; 
  unsigned long triggerTime = micros();
  unsigned long prevCycle = PWM_READER->cycleTimer;
  
  if(PWM_READER->prevState == LOW){ //when start of pulse is detected
   
   PWM_READER->cycleTimer = triggerTime - PWM_READER->pwmTimer; //calculate cycle length
   
   PWM_READER->pwmTimer = triggerTime; //detect cycleTime

  } else { //when end of pulse is detected
    PWM_READER->dutyTimer = triggerTime - PWM_READER->pwmTimer; //pulse time
  }

  if( !(abs( 1000000.0 / (prevCycle - PWM_READER->cycleTimer)) > freqErr) ){ //if there was a significant frequency change
    PWM_READER->newFreq = true;
   } else {
    PWM_READER->newFreq = false;
   }

   if(!PWM_READER->newFreq){
    PWM_READER->freq = freqCalc(PWM_READER->cycleTimer);
    PWM_READER->duty = dutyCalc(PWM_READER->dutyTimer, PWM_READER->cycleTimer);
    PWM_READER->warning = getWarning(PWM_READER->freq, PWM_READER->duty);
   }
  //new data received
  PWM_READER->prevState = !PWM_READER->prevState; //yikes
}


String PWM_READ::getWarning(float freq, float duty){
    if( abs(freq - 10) <= dutyErr) { 
    if(duty >= 5.0 &&  duty <= 95.5){
      return "Normal";
    } 
  }
  else if( abs(freq - 20) <= dutyErr) { 
    if(duty >= 5.0 &&  duty <= 95.5){
      return "Undervoltage Detected";
    } 
  }
  else if( abs(freq - 30) <= dutyErr) { 
    if(duty >= 5.0 &&  duty <= 10.0){
      return "good";
    } else if( duty >= 90.0 && duty <= 95.0){
      return "bad";
    }
  }
  else if( abs(freq - 40) <= dutyErr) { 
    if(duty >= 47.5 &&  duty <= 52.5){
      return "Device Error";
    } 
  }
  else if( abs(freq - 50) <= dutyErr) {
    if(duty >= 47.5 &&  duty <= 52.5){
      return "Kl.31 fault";
    } 
  }
  return "undefined";
}

bool PWM_READ::initPWM(int pin){
  if(PWM_READER == nullptr){
    PWM_READER = new PWM_READ(pin);
    return true;
  } else {
    return false;
  }
}

PWM_READ::PWM_READ(int pin) : pwmPin( pin ) 
{
  PWM_READER = this; 
  pinMode(this->pwmPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(this->pwmPin), onTrigger , CHANGE); 
}

PWM_READ::~PWM_READ(){
  delete PWM_READER ;
}

// float PWM_READ::getFreq(){
//   return freq;
// }

// float PWM_READ::getDuty(){
//   return duty;
// }

// String PWM_READ::getWarning(){
//   return PWM_READ::warning(freq, duty);
// }
