/* Program to test ISB-300-A-802 Hall Effect Current Sensor
 * https://www.mouser.com/ProductDetail/ICE-Components/ISB-300-A-802?qs=6RXCB%2F3ptqS95L0cyUF1vw%3D%3D
 * Wire 1 (Red) - Vdd (Supply)
 * Wire 2 (Black) - Output
 * Wire 3 (Blue) - Ref. Voltage Output
 * Wire 4 (White) - Vss (Ground)
 *  
 * This code must be run on an arduino uno, or another board that can analogRead up to 5V.
 *  
 * Jackson Holbrook, HyTech Racing, 9/21/2022
 */

#define sensorPin A0 //should be connected to sensor Pin 2 (black wire)
#define refPin A1 //should be connected to sensor Pin 3 (blue wire)
int sensorValue; //Raw sensor reading
double rawVoltage; //Raw sensor voltage (in Volts)
double sensorCurrent; //Current (in Amps) read from the sensor

void setup() {
  Serial.begin(9600);
  sensorValue = 0;
  rawVoltage = 0.0;
  sensorCurrent = 0.0;
}

void loop() {
  sensorValue = analogRead(sensorPin) - analogRead(refPin);
  rawVoltage = sensorValue * (5.0 / 1023.0); //convert to Volts
  sensorCurrent = rawVoltage / .006667; //convert to Amps
//  Serial.printf("RSV: %4d\tRV: %4.4f\tAmps: %4.4f\n", analogRead(sensorPin), rawVoltage, sensorCurrent);
  Serial.print("Raw: " + String(analogRead(sensorPin)));
  Serial.print("\tV: " + String(rawVoltage));
  Serial.print(" \tA: " + String(sensorCurrent));
  Serial.println("");
  delay(10);
}
