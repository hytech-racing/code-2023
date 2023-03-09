#pragma once
#include <string.h>
#include <stdint.h>
#ifdef HT_DEBUG_EN
    #include "Arduino.h"
#endif

#pragma pack(push,1)

// @Parseclass
class MCU_GPS_readings 
#ifdef INHERITANCE_EN
: public CAN_message
#endif
{
public:
    MCU_GPS_readings() = default;
    MCU_GPS_readings(uint8_t buf[8]) { load(buf); }

    #ifdef INHERITANCE_EN
    inline void load(uint8_t buf[])        override { memcpy(this+sizeof(CAN_message), buf, sizeof(*this)-sizeof(CAN_message)); }
    inline void write(uint8_t buf[]) const override { memcpy(buf, this+sizeof(CAN_message), sizeof(*this)-sizeof(CAN_message)); }
    virtual inline int get_id()      const override { return ID_MCU_GPS_READINGS; }
    #else
    inline void load(uint8_t buf[])         { memcpy(this, buf, sizeof(*this)); }
    inline void write(uint8_t buf[])  const { memcpy(buf, this, sizeof(*this)); }
    #endif

    inline int32_t get_latitude()   const { return latitude; }
    inline int32_t get_longitude()  const { return longitude; }

    inline void set_latitude(int32_t latitude)      { this->latitude = latitude; }
    inline void set_longitude(int32_t longitude)    { this->longitude = longitude; }

#ifdef HT_DEBUG_EN
    void print() {
        Serial.println("\n\nGPS Readings");
        Serial.println(    "-----------");
        Serial.print("Latitude:  ");  Serial.println(latitude / 1000000.);
        Serial.print("Longitude: ");  Serial.println(longitude / 1000000.);
    }
#endif

private:
    int32_t latitude;   // @Parse @Scale(100000)
    int32_t longitude;  // @Parse @Scale(100000)
};

#pragma pack(pop)