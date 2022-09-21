/* Program to test ISB-300-A-802 Hall Effect Current Sensor
 * https://www.mouser.com/ProductDetail/ICE-Components/ISB-300-A-802?qs=6RXCB%2F3ptqS95L0cyUF1vw%3D%3D
 * Wire 1 (Red) - Vdd (Supply)
 * Wire 2 (Black) - Output
 * Wire 3 (Blue) - Ref. Output
 * Wire 4 (White) - Vss (Ground)
 *  
 * Jackson Holbrook, HyTech Racing, 9/21/2022
 */

#define sensorPin A0 //should be connected to sensor Pin 2 (black wire)
int rawSensorValue; //Raw sensor reading
double rawVoltage; //Raw sensor voltage (in Volts)
double sensorCurrent; //Current (in Amps) read from the sensor

void setup() {
  Serial.begin(9600);
  rawSensorValue = 0;
  rawVoltage = 0.0;
  sensorCurrent = 0.0;
}

void loop() {
  rawSensorValue = analogRead(sensorPin);
  rawVoltage = rawSensorValue * (5.0 / 1023.0); //formula from arduino.cc
  sensorCurrent = (rawVoltage-2.5) / 100 * 6.667; //conversion to Amps
  Serial.print("Raw Sensor Value:\t" + rawSensorValue); 
  Serial.print("\tRaw Voltage: \t" + String(rawVoltage));
  Serial.println("\tCurrent (A):\t" + String(sensorCurrent));
}
