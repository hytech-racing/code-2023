#pragma once
#include <string.h>
#include <stdint.h>

#pragma pack(push,1)

// @Parseclass
class IMU_gyroscope 
#ifdef INHERITANCE_EN
: public CAN_message
#endif
{
public:
    IMU_gyroscope() = default;
    IMU_gyroscope(const uint8_t buf[8]) { load(buf); }

    #ifdef INHERITANCE_EN
    inline void load(uint8_t buf[])        override { memcpy(this+sizeof(CAN_message), buf, sizeof(*this)-sizeof(CAN_message)); }
    inline void write(uint8_t buf[]) const override { memcpy(buf, this+sizeof(CAN_message), sizeof(*this)-sizeof(CAN_message)); }
    inline int get_id()              const override { return ID_IMU_GYROSCOPE; }
    #else
    inline void load(const uint8_t buf[8]) { memcpy(this, buf, sizeof(*this)); }
    inline void write(uint8_t buf[])    const { memcpy(buf, this, sizeof(*this)); }
    #endif

    //Getters
    inline int16_t get_yaw() const { return yaw; }
    inline int16_t get_pitch() const { return pitch; }
    inline int16_t get_roll() const { return roll; }

    // Setters
    inline void set_yaw(int16_t yaw) { this->yaw = yaw; }
    inline void set_pitch(int16_t pitch) { this->pitch = pitch; }
    inline void set_roll(int16_t roll) { this->roll = roll; }

private:
    // @Parse @Unit(DEG/S) @Scale(3)
    int16_t yaw;
    // @Parse @Unit(DEG/S) @Scale(3)
    int16_t pitch;
    // @Parse @Unit(DEG/S) @Scale(3)
    int16_t roll;

};

#pragma pack(pop)