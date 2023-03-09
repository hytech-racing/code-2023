#pragma once
#include <string.h>
#include <stdint.h>
#ifdef HT_DEBUG_EN
    #include "Arduino.h"
#endif

#pragma pack(push,1)

// @Parseclass
class Charger_data 
#ifdef INHERITANCE_EN
: public CAN_message
#endif
{
public:
    Charger_data() = default;
    Charger_data(uint8_t buf[]) { load(buf); }

    #ifdef INHERITANCE_EN
    inline void load(uint8_t buf[])        override { memcpy(this+sizeof(CAN_message), buf, sizeof(*this)-sizeof(CAN_message)); }
    inline void write(uint8_t buf[]) const override { memcpy(buf, this+sizeof(CAN_message), sizeof(*this)-sizeof(CAN_message)); }
    virtual inline int get_id()      const override { return ID_CHARGER_DATA; }
    #else
    inline void load(uint8_t buf[])         { memcpy(this, buf, sizeof(*this)); }
    #endif

    inline uint8_t get_output_current_low() {return output_current_low;}
    inline uint8_t get_output_current_high() {return output_current_high;}
    inline uint8_t get_flags() {return flags;}
    inline uint8_t get_output_dc_voltage_high(){return output_dc_voltage_high;}
    inline uint8_t get_output_dc_voltage_low(){return output_dc_voltage_low;}
    inline uint8_t get_input_ac_voltage_high(){return input_ac_voltage_high;}
    inline uint8_t get_input_ac_voltage_low(){return input_ac_voltage_low;}

private:
    uint8_t output_dc_voltage_high;
    uint8_t output_dc_voltage_low;
    uint8_t output_current_high;
    uint8_t output_current_low;
    uint8_t flags;
    uint8_t input_ac_voltage_high;
    uint8_t input_ac_voltage_low;
};

#pragma pack(pop)