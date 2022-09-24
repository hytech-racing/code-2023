const byte pwmPin = 9; //designated pwm pin on teensy 3.0

 
volatile unsigned long dutyTimer = 0; // //timer on duty cycle
unsigned long cycleTimer = 0; //timer on cycle
unsigned long pwmTimer = 0; //stores previous trigger time
unsigned long prevMillis = millis();


bool prevState = LOW;
volatile bool newFreq = false; //flags frequency changes


float currFreq = 0; //frequency
float currDuty = 0; //duty cycle
float sigErr = 1.0;
float freqVariation = 5.0;

String warning = "";

// the setup routine runs once when you press reset:
void setup() {
  // initialize the digital pin as an output.
  Serial.begin(9600);
  pinMode(pwmPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(pwmPin), onTrigger , CHANGE); //can be initialized in object init
}

// the loop routine runs over and over again forever:



void loop() {
 //can become a instance method called check frequency loop
  if(!newFreq){
    PWM_freq();
    PWM_duty();
    warning = getWarning();
  }
  if(prevMillis + 100 < millis()){
    Serial.printf("Freq: %f, ", currFreq, warning);
    
    prevMillis= millis();
  }
  if(micros() - pwmTimer > 1000000){
    newFreq = true;
  }
  
}


void PWM_freq(){ // can be a static method
  currFreq = 1000000 / cycleTimer;
}

void PWM_duty(){ //can be a static method
  currDuty =  dutyTimer / cycleTimer * 100;
}

void onTrigger(){ //will be static method
  
  unsigned long triggerTime = micros();
  unsigned long prevCycle = cycleTimer;
  
  if(prevState == LOW){ //when start of pulse is detected
   
   cycleTimer = triggerTime - pwmTimer; //calculate cycle length
   
   pwmTimer = triggerTime; //detect cycleTime

  } else { //when end of pulse is detected
    dutyTimer = triggerTime - pwmTimer; //pulse time
  }

  if( abs( 1000000.0 / (prevCycle - cycleTimer)) > freqVariation ){ //if there was a significant frequency change
    newFreq = true;
   } else {
    newFreq = false;
   }
  //new data received
  prevState = !prevState;
}

String getWarning(){ //static method with two params
  
  if( abs(currFreq - 10) < sigErr) { //Device Error
    if(currDuty >= 5.0 &&  currDuty <= 95.5){
      return "Normal";
    } 
  }
  else if( abs(currFreq - 20) < sigErr) { //Device Error
    if(currDuty >= 5.0 &&  currDuty <= 95.5){
      return "Undervoltage Detected";
    } 
  }
  else if( abs(currFreq - 30) < sigErr) { //SST
    if(currDuty >= 5.0 &&  currDuty <= 10.0){
      return "good";
    } else if( currDuty >= 90.0 && currDuty <= 95.0){
      return "bad";
    }
  }
  else if( abs(currFreq - 40) < sigErr) { //Device Error
    if(currDuty >= 47.5 &&  currDuty <= 52.5){
      return "Device Error";
    } 
  }
  else if( abs(currFreq - 50) < sigErr) { //Device Error
    if(currDuty >= 47.5 &&  currDuty <= 52.5){
      return "Kl.31 fault";
    } 
  }
  return "undefined";
}
