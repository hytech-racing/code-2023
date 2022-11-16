#include "FlexCAN_T4.h"
#include "HyTech_CAN.h"
#include <string.h>
#include <stdio.h>

char myData[20];
const char* strings[] = {"0xA0","0xA1","0xA2", "0xA3", "0xA4", "0xA5", "0xA6", "0xA7", "0xAA", "0xAB", "0xAC" , "0xAD", "0xAE", "0xAF", "0xC0", "0xC1", "0xC2", "0xC3", "0xC4", "0xCC", "0xD5", "0xD6", "0xD7", "0xD8", "0xD9", "0xDA", "0xDB","0xDD", "0xDE", "0xE2", "0xE7", "0xEA", "0xEB", "0xEE", "0x1806E0F4", "0x18FF50E0", "0x100", "0x400", "0x90", "0x91", "0x92", "0x93"};

int incomingByte[256];
int inByte = 0;
BMS_balancing_status balance;
BMS_coulomb_counts count;
BMS_detailed_temperatures dTemp;
BMS_detailed_voltages dVolt;
BMS_onboard_detailed_temperatures onDTemp;
BMS_onboard_temperatures onTemp;
BMS_status stat;
BMS_temperatures bmsTemp;
BMS_voltages bmsVolt;
CCU_status ccuStat;
Charger_configure chargeConfig;
Charger_data chargeData;
Dashboard_status dashStat;
EM_measurement emMeasure;
EM_status emStat;
IMU_accelerometer imuAccel;
IMU_gyroscope imuGyro;
MC_analog_input_voltages mcVolt;
MC_command_message mcMsg;
MC_current_information mcInfo;
MC_digital_input_status mcInputStat;
MC_fault_codes mcFCodes;
MC_firmware_information mcFirmInfo;
MC_flux_weakening_output mcFluxOut;
MC_internal_states mcIntStates;
MC_motor_position_information mcMotorInfo;
MC_read_write_parameter_command mcParamComm;
MC_read_write_parameter_response mcParamResp;
MC_temperatures_1 temperatures_1;
MC_temperatures_2 temperatures_2;
MC_temperatures_3 temperatures_3;
MC_torque_timer_information torqTimer;
MC_voltage_information mcVoltInfo;
MCU_analog_readings anaRead;
MCU_GPS_readings gpsRead;
MCU_pedal_readings pedalRead;
MCU_status mcuStat;
MCU_wheel_speed wheelSpeed;
SAB_readings_front sabFront;
SAB_readings_gps sabGPS;
SAB_readings_rear sabRear;


FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> CAN_bus;
CAN_message_t msg; //
CAN_message_t imu_msg; // For incoming IMU CAN message
unsigned char len = 0;
unsigned char buf[8];

void setup() {
  // put your setup code here, to run once:
  CAN_bus.begin();
  CAN_bus.setBaudRate(1000000);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

    if(Serial.available() > 0)
    {
      byte m = Serial.readBytesUntil('\n',myData, 20);
      myData[m] = '\0';

      for(int i = 0; i < 42; i++){
        if(strcmp(myData, strings[i]) == 0){
          if(strcmp(strings[i], "0xA0") == 0){
            temperatures_1.write(msg.buf);
            msg.len = sizeof(temperatures_1);
            msg.id = ID_MC_TEMPERATURES_1;
            CAN_bus.write(msg);
            Serial.println(msg.id, HEX);
          }
          else if(strcmp(strings[i], "0xA1") == 0){
            temperatures_2.write(msg.buf);
            msg.len = sizeof(temperatures_2);
            msg.id = ID_MC_TEMPERATURES_2;
            CAN_bus.write(msg);
            Serial.println(msg.id, HEX);
          }
          else if(strcmp(strings[i], "0xA2") == 0){
            temperatures_3.write(msg.buf);
            msg.len = sizeof(temperatures_3);
            msg.id = ID_MC_TEMPERATURES_3;
            CAN_bus.write(msg);
            Serial.println(msg.id, HEX);
          }
          else if(strcmp(strings[i], "0xA3") == 0){
            mcVolt.write(msg.buf);
            msg.len = sizeof(mcVolt);
            msg.id = ID_MC_ANALOG_INPUTS_VOLTAGES;
            CAN_bus.write(msg);
            Serial.println(msg.id, HEX);
          }
          else if(strcmp(strings[i], "0xA4") == 0){
            mcInputStat.write(msg.buf);
            msg.len = sizeof(mcInputStat);
            msg.id = ID_MC_DIGITAL_INPUT_STATUS;
            CAN_bus.write(msg);
            Serial.println(msg.id, HEX);
          }
          else if(strcmp(strings[i], "0xA5") == 0){
            mcMotorInfo.write(msg.buf);
            msg.len = sizeof(mcMotorInfo);
            msg.id = ID_MC_MOTOR_POSITION_INFORMATION;
            CAN_bus.write(msg);
            Serial.println(msg.id, HEX);
          }
          else if(strcmp(strings[i], "0xA6") == 0){
            mcInfo.write(msg.buf);
            msg.len = sizeof(mcInfo);
            msg.id = ID_MC_CURRENT_INFORMATION;
            CAN_bus.write(msg);
            Serial.println(msg.id, HEX);
          }
          else if(strcmp(strings[i], "0xA7") == 0){
            mcVoltInfo.write(msg.buf);
            msg.len = sizeof(mcVoltInfo);
            msg.id = ID_MC_VOLTAGE_INFORMATION;
            CAN_bus.write(msg);
            Serial.println(msg.id, HEX);
          }
          else if(strcmp(strings[i], "0xAA") == 0){
            mcIntStates.write(msg.buf);
            msg.len = sizeof(mcIntStates);
            msg.id = ID_MC_INTERNAL_STATES;
            CAN_bus.write(msg);
            Serial.println(msg.id, HEX);
          }
          else if(strcmp(strings[i], "0xAB") == 0){
            mcFCodes.write(msg.buf);
            msg.len = sizeof(mcFCodes);
            msg.id = ID_MC_FAULT_CODES;
            CAN_bus.write(msg);
            Serial.println(msg.id, HEX);
          }
          else if(strcmp(strings[i], "0xAC") == 0){
            torqTimer.write(msg.buf);
            msg.len = sizeof(torqTimer);
            msg.id = ID_MC_TORQUE_TIMER_INFORMATION;
            CAN_bus.write(msg);
            Serial.println(msg.id, HEX);
          }
          else if(strcmp(strings[i], "0xAD") == 0){
            mcFluxOut.write(msg.buf);
            msg.len = sizeof(mcFluxOut);
            msg.id = ID_MC_FLUX_WEAKENING_OUTPUT;
            CAN_bus.write(msg);
            Serial.println(msg.id, HEX);
          }
          else if(strcmp(strings[i], "0xAE") == 0){
            mcFirmInfo.write(msg.buf);
            msg.len = sizeof(mcFirmInfo);
            msg.id = ID_MC_FIRMWARE_INFORMATION;
            CAN_bus.write(msg);
            Serial.println(msg.id, HEX);
          }
          else if(strcmp(strings[i], "0xC0") == 0){
            mcMsg.write(msg.buf);
            msg.len = sizeof(mcMsg);
            msg.id = ID_MC_COMMAND_MESSAGE;
            CAN_bus.write(msg);
            Serial.println(msg.id, HEX);
          }
          else if(strcmp(strings[i], "0xC1") == 0){
            mcParamComm.write(msg.buf);
            msg.len = sizeof(mcParamComm);
            msg.id = ID_MC_READ_WRITE_PARAMETER_COMMAND;
            CAN_bus.write(msg);
            Serial.println(msg.id, HEX);
          }
          else if(strcmp(strings[i], "0xC2") == 0){
            mcParamResp.write(msg.buf);
            msg.len = sizeof(mcParamResp);
            msg.id = ID_MC_READ_WRITE_PARAMETER_RESPONSE;
            CAN_bus.write(msg);
            Serial.println(msg.id, HEX);
          }
          else if(strcmp(strings[i], "0xC3") == 0){
            mcuStat.write(msg.buf);
            msg.len = sizeof(mcuStat);
            msg.id = ID_MCU_STATUS;
            CAN_bus.write(msg);
            Serial.println(msg.id, HEX);
          }
          else if(strcmp(strings[i], "0xC4") == 0){
            pedalRead.write(msg.buf);
            msg.len = sizeof(pedalRead);
            msg.id = ID_MCU_PEDAL_READINGS;
            CAN_bus.write(msg);
            Serial.println(msg.id, HEX);
          }
          else if(strcmp(strings[i], "0xCC") == 0){
            anaRead.write(msg.buf);
            msg.len = sizeof(anaRead);
            msg.id = ID_MCU_ANALOG_READINGS;
            CAN_bus.write(msg);
            Serial.println(msg.id, HEX);
          }
          else if(strcmp(strings[i], "0xD5") == 0){
            onTemp.write(msg.buf);
            msg.len = sizeof(onTemp);
            msg.id = ID_BMS_ONBOARD_TEMPERATURES;
            CAN_bus.write(msg);
            Serial.println(msg.id, HEX);
          }
          else if(strcmp(strings[i], "0xD6") == 0){
            onDTemp.write(msg.buf);
            msg.len = sizeof(onDTemp);
            msg.id = ID_BMS_ONBOARD_DETAILED_TEMPERATURES;
            CAN_bus.write(msg);
            Serial.println(msg.id, HEX);
          }
          else if(strcmp(strings[i], "0xD7") == 0){
            bmsVolt.write(msg.buf);
            msg.len = sizeof(bmsVolt);
            msg.id = ID_BMS_VOLTAGES;
            CAN_bus.write(msg);
            Serial.println(msg.id, HEX);
          }
          else if(strcmp(strings[i], "0xD8") == 0){
            dVolt.write(msg.buf);
            msg.len = sizeof(dVolt);
            msg.id = ID_BMS_DETAILED_VOLTAGES;
            CAN_bus.write(msg);
            Serial.println(msg.id, HEX);
          }
          else if(strcmp(strings[i], "0xD9") == 0){
            bmsTemp.write(msg.buf);
            msg.len = sizeof(bmsTemp);
            msg.id = ID_BMS_TEMPERATURES;
            CAN_bus.write(msg);
            Serial.println(msg.id, HEX);
          }
          else if(strcmp(strings[i], "0xDA") == 0){
            dTemp.write(msg.buf);
            msg.len = sizeof(dTemp);
            msg.id = ID_BMS_DETAILED_TEMPERATURES;
            CAN_bus.write(msg);
            Serial.println(msg.id, HEX);
          }
          else if(strcmp(strings[i], "0xDB") == 0){
            stat.write(msg.buf);
            msg.len = sizeof(stat);
            msg.id = ID_BMS_STATUS;
            CAN_bus.write(msg);
            Serial.println(msg.id, HEX);
          }
          else if(strcmp(strings[i], "0xDD") == 0){
            ccuStat.write(msg.buf);
            msg.len = sizeof(ccuStat);
            msg.id = ID_CCU_STATUS;
            CAN_bus.write(msg);
            Serial.println(msg.id, HEX);
          }
          else if(strcmp(strings[i], "0xDE") == 0){
            balance.write(msg.buf);
            msg.len = sizeof(balance);
            msg.id = ID_BMS_BALANCING_STATUS;
            CAN_bus.write(msg);
            Serial.println(msg.id, HEX);
          }
          else if(strcmp(strings[i], "0xE2") == 0){
            count.write(msg.buf);
            msg.len = sizeof(count);
            msg.id = ID_BMS_COULOMB_COUNTS;
            CAN_bus.write(msg);
            Serial.println(msg.id, HEX);
          }
          else if(strcmp(strings[i], "0xE7") == 0){
            gpsRead.write(msg.buf);
            msg.len = sizeof(gpsRead);
            msg.id = ID_MCU_GPS_READINGS;
            CAN_bus.write(msg);
            Serial.println(msg.id, HEX);
          }
          else if(strcmp(strings[i], "0xEA") == 0){
            wheelSpeed.write(msg.buf);
            msg.len = sizeof(wheelSpeed);
            msg.id = ID_MCU_WHEEL_SPEED;
            CAN_bus.write(msg);
            Serial.println(msg.id, HEX);
          }
          else if(strcmp(strings[i], "0xEB") == 0){
            dashStat.write(msg.buf);
            msg.len = sizeof(dashStat);
            msg.id = ID_DASHBOARD_STATUS;
            CAN_bus.write(msg);
            Serial.println(msg.id, HEX);
          }
          else if(strcmp(strings[i], "0xEE") == 0){
            sabGPS.write(msg.buf);
            msg.len = sizeof(sabGPS);
            msg.id = ID_SAB_READINGS_GPS;
            CAN_bus.write(msg);
            Serial.println(msg.id, HEX);
          }
           else if(strcmp(strings[i], "0x1806E0F4") == 0){
            chargeConfig.write(msg.buf);
            msg.len = sizeof(chargeConfig);
            msg.id = ID_CHARGER_CONTROL;
            CAN_bus.write(msg);
            Serial.println(msg.id, HEX);
          }
          //chargeData cant do .write
           //else if(strcmp(strings[i], "0x18FF50E0") == 0){
            //chargeData.write(msg.buf);
            //msg.len = sizeof(chargeData);
            //msg.id = ID_CHARGER_DATA;
            //CAN_bus.write(msg);
            //Serial.println(msg.id, HEX);
          //}
           else if(strcmp(strings[i], "0x100") == 0){
            emStat.write(msg.buf);
            msg.len = sizeof(emStat);
            msg.id = ID_EM_STATUS;
            CAN_bus.write(msg);
            Serial.println(msg.id, HEX);
          }
           else if(strcmp(strings[i], "0x400") == 0){
            emMeasure.write(msg.buf);
            msg.len = sizeof(emMeasure);
            msg.id = ID_EM_MEASUREMENT;
            CAN_bus.write(msg);
            Serial.println(msg.id, HEX);
          }
           else if(strcmp(strings[i], "0x90") == 0){
            imuAccel.write(msg.buf);
            msg.len = sizeof(imuAccel);
            msg.id = ID_IMU_ACCELEROMETER;
            CAN_bus.write(msg);
            Serial.println(msg.id, HEX);
          }
           else if(strcmp(strings[i], "0x91") == 0){
            imuGyro.write(msg.buf);
            msg.len = sizeof(imuGyro);
            msg.id = ID_IMU_GYROSCOPE;
            CAN_bus.write(msg);
            Serial.println(msg.id, HEX);
          }
           else if(strcmp(strings[i], "0x92") == 0){
            sabFront.write(msg.buf);
            msg.len = sizeof(sabFront);
            msg.id = ID_SAB_READINGS_FRONT;
            CAN_bus.write(msg);
            Serial.println(msg.id, HEX);
          }
           else if(strcmp(strings[i], "0x93") == 0){
            sabRear.write(msg.buf);
            msg.len = sizeof(sabRear);
            msg.id = ID_SAB_READINGS_REAR;
            CAN_bus.write(msg);
            Serial.println(msg.id, HEX);
          }
        } 
      }
   }
}
      
