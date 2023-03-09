#pragma once
#include <string.h>
#include <stdint.h>
#ifdef HT_DEBUG_EN
    #include "Arduino.h"
#endif

#pragma pack(push,1)

// @Parseclass
class Charger_configure 
#ifdef INHERITANCE_EN
: public CAN_message
#endif
{
public:
    Charger_configure() = default;
    Charger_configure(uint8_t buf[]) { load(buf); }

    #ifdef INHERITANCE_EN
    inline void load(uint8_t buf[])        override { memcpy(this+sizeof(CAN_message), buf, sizeof(*this)-sizeof(CAN_message)); }
    inline void write(uint8_t buf[]) const override { memcpy(buf, this+sizeof(CAN_message), sizeof(*this)-sizeof(CAN_message)); }
    virtual inline int get_id()      const override { return ID_CHARGER_CONTROL; } // Is that the correct one?
    #else
    inline void load(uint8_t buf[])         { memcpy(this, buf, sizeof(*this)); }
    inline void write(uint8_t buf[])        { memcpy(buf, this, sizeof(*this)); }
    #endif

    inline uint8_t get_control()      { return control; }
    inline void set_control(uint8_t con) { this->control = con; }
    inline uint8_t get_max_charging_voltage_high()  { return max_charging_voltage_high; }
    inline void set_max_charging_voltage_high(uint8_t max_charging_voltage_high) { this->max_charging_voltage_high = max_charging_voltage_high; }
    inline uint8_t get_max_charging_voltage_low()  { return max_charging_voltage_low; }
    inline void set_max_charging_voltage_low(uint8_t max_charging_voltage_low) { this->max_charging_voltage_low = max_charging_voltage_low; }
    inline uint8_t get_max_charging_current_high()  { return max_charging_current_high; }
    inline void set_max_charging_current_high(uint8_t max_charging_current_high) { this->max_charging_current_high = max_charging_current_high; }
    inline uint8_t get_max_charging_current_low()  { return max_charging_current_low; }
    inline void set_max_charging_current_low(uint8_t max_charging_current_low) { this->max_charging_current_low = max_charging_current_low; }

private:
    uint8_t max_charging_voltage_high;
    uint8_t max_charging_voltage_low;
    uint8_t max_charging_current_high;
    uint8_t max_charging_current_low;
    uint8_t control;
};

#pragma pack(pop)