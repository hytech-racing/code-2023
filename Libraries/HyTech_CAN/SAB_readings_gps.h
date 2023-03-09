#pragma once
#include <string.h>
#include <stdint.h>

#pragma pack(push,1)

// @Parseclass
class SAB_readings_gps 
#ifdef INHERITANCE_EN
: public CAN_message
#endif
{
public:
    SAB_readings_gps() = default;

    SAB_readings_gps(const uint8_t buf[8]) { load(buf); }

    #ifdef INHERITANCE_EN
    inline void load(uint8_t buf[])        override { memcpy(this+sizeof(CAN_message), buf, sizeof(*this)-sizeof(CAN_message)); }
    inline void write(uint8_t buf[]) const override { memcpy(buf, this+sizeof(CAN_message), sizeof(*this)-sizeof(CAN_message)); }
    virtual inline int get_id()      const override { return ID_SAB_READINGS_GPS; }
    #else
    inline void load(const uint8_t buf[8]) { memcpy(this, buf, sizeof(*this)); }
    inline void write(uint8_t buf[8]) const { memcpy(buf, this, sizeof(*this)); }
    #endif

    // Getters
    inline int32_t get_gps_latitude() const { return gps_latitude; }
    inline int32_t get_gps_longitude() const { return gps_longitude; }

    // Setters
    inline void set_gps_latitude(int32_t reading) { gps_latitude = reading; }
    inline void set_gps_longitude(int32_t reading) { gps_longitude = reading; }

private:
    // @Parse @Scale(1000000)
    int32_t gps_latitude;
    // @Parse @Scale(1000000)
    int32_t gps_longitude;
};

#pragma pack(pop)