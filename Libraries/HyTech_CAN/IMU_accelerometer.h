#pragma once
#include <string.h>
#include <stdint.h>

#pragma pack(push,1)

// @Parseclass
class IMU_accelerometer 
#ifdef INHERITANCE_EN
: public CAN_message
#endif
{
public:
    IMU_accelerometer() = default;
    IMU_accelerometer(const uint8_t buf[8]) { load(buf); }

    #ifdef INHERITANCE_EN
    inline void load(uint8_t buf[])        override { memcpy(this+sizeof(CAN_message), buf, sizeof(*this)-sizeof(CAN_message)); }
    inline void write(uint8_t buf[]) const override { memcpy(buf, this+sizeof(CAN_message), sizeof(*this)-sizeof(CAN_message)); }
    virtual inline int get_id()      const override { return ID_IMU_ACCELEROMETER; }
    #else
    inline void load(const uint8_t buf[8]) { memcpy(this, buf, sizeof(*this)); }
    inline void write(uint8_t buf[])    const { memcpy(buf, this, sizeof(*this)); }
    #endif

    inline int16_t get_lat_accel() const { return lat_accel; }
    inline int16_t get_long_accel() const { return long_accel; }
    inline int16_t get_vert_accel() const { return vert_accel; }

    // New Setters
    inline void set_lat_accel(int16_t lat_accel) { this->lat_accel = lat_accel; }
    inline void set_long_accel(int16_t long_accel) { this->long_accel = long_accel; }
    inline void set_vert_accel(int16_t vert_accel) { this->vert_accel = vert_accel; }

private:
    // @Parse @Unit(m/s/s) @Scale(102)
    int16_t lat_accel;
    // @Parse @Unit(m/s/s) @Scale(102)
    int16_t long_accel;
    // @Parse @Unit(m/s/s) @Scale(102)
    int16_t vert_accel;
    
};

#pragma pack(pop)