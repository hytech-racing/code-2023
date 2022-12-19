/**
@author: Sahaj Purohit
Last Edited: November 6
*/

#include <ADIS16460.h>
#include <SPI.h>
#include <Metro.h>
// Call ADIS16460 Class
ADIS16460 IMU(10,2,23); // Chip Select, Data Ready, Reset Pin Assignments
// Integrating velocity
Metro timer_imu_integration = Metro(50);
float velocity_x;
// float distance_x;
int printcounter = 0;
// Vector for error
// vector<float> x_accel_vector;

void setup() {
    Serial.begin(115200); // Initialize serial output via USB
    IMU.configSPI(); // Configure SPI communication
    delay(1000); // Give the part time to start up
    IMU.regWrite(MSC_CTRL, 0xC1);  // Enable Data Ready, set polarity
    delay(20); 
    IMU.regWrite(FLTR_CTRL, 0x500); // Set digital filter
    delay(20);
    IMU.regWrite(DEC_RATE, 0), // Disable decimation
    delay(20);
}

// Main loop
void loop() {
  // INTEGRATING X ACCELERATION STATIONARY SHOULD BE 0
  // GITHUB LIBRARY WORK
  // float x_accel_off = IMU.regRead(XACCL_OFF); // TENDS TO ALWAYS BE 0
  // float x_delta_velocity = IMU.regRead(X_DELT_VEL);
  float accel_x = IMU.regRead(X_ACCL_OUT) * 0.00245; // 0.00245 is the scale
  // x_accel_vector.push_back(x_accel);
  // float y_accel = IMU.regRead(Y_ACCL_OUT) * 0.00245; // 0.00245 is the scale
  // float z_accel = IMU.regRead(Z_ACCL_OUT) * 0.00245; // 0.00245 is the scale
  // float x_gyro = IMU.regRead(X_GYRO_OUT) * 0.005; // 0.005 is the scale
  // float y_gyro = IMU.regRead(Y_GYRO_OUT) * 0.005; // 0.005 is the scale
  // float z_gyro = IMU.regRead(Z_GYRO_OUT) * 0.005; // 0.005 is the scale
  if (timer_imu_integration.check()) {
    float accel_x_corrected = (abs(accel_x) < 0.3) ? 0 : accel_x;
    velocity_x += (accel_x_corrected * 0.05); // Output in m/s   Mph correction 2.237
    // distance_x += (velocity_x * 0.05);
    // printcounter++;
  }
  // if (printcounter == 50) {
  //   Serial.printf("X_Velocity: %f m/s  X_ACCEL: %f m/s^2  Distance: %f m\n ", running_velocity_x, x_accel, distance);
  //   printcounter = 0;
  // }
  // Serial.printf("x_delta_velocity: %f \n", x_delta_velocity);
  // Serial.printf("X_ACCEL: %f     X_ACCEL_OFF: %f \n", x_accel, x_accel_off);
  // HAVING TO DOUBLE INTEGRATE FOR DISTANCE MEANS VERY INACCURATE VALUES
  // Serial.printf("Accel_x: %f m/s^2 | Velocity_x: %f m/s | Distance_x: %f m\n ", accel_x, velocity_x, distance_x);
  Serial.printf("Accel_x: %f m/s^2 | Velocity_x: %f m/s\n ", accel_x, velocity_x);
  // Serial.printf("X_ACC %0.4f m/s^2  Y_ACC %0.4f m/s^2  Z_ACC: %0.4f m/s^2  X_GYRO: %0.4f  Y_GYRO: %0.4f  Z_GYRO: %0.4f\n", x_accel, y_accel, z_accel, x_gyro, y_gyro, z_gyro);
  // delay(100);
}
