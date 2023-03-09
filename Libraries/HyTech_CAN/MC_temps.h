#pragma once
#include <string.h>
#include <stdint.h>
#ifdef HT_DEBUG_EN
    #include "Arduino.h"
#endif

#pragma pack(push,1)

class MC_temps
#ifdef INHERITANCE_EN
: public CAN_message
#endif
{
public:
  MC_temps() = default;
  MC_temps(uint8_t buf[]) { load(buf); }

  #ifdef INHERITANCE_EN
  inline void load(uint8_t buf[])        override { memcpy(this+sizeof(CAN_message), buf, sizeof(*this)-sizeof(CAN_message)); }
  inline void write(uint8_t buf[]) const override { memcpy(buf, this+sizeof(CAN_message), sizeof(*this)-sizeof(CAN_message)); }
  virtual inline int get_id()      const override { return ID_MC1_TEMPS; }
  #else
  inline void load(uint8_t buf[])         { memcpy(this, buf, sizeof(*this)); }
  inline void write(uint8_t buf[])  const { memcpy(buf, this, sizeof(*this)); }
  #endif

  inline uint16_t get_motor_temp()   const { return motor_temp; }
  inline uint16_t get_inverter_temp()       const { return inverter_temp; }
  inline uint16_t get_igbt_temp()      const { return igbt_temp; }
  inline uint16_t get_diagnostic_number()     const { return diagnostic_number; }
private: // all temps in 0.1C
    int16_t motor_temp;
    int16_t inverter_temp; //cold plate temp
    int16_t igbt_temp;
    int16_t diagnostic_number;
};

#pragma pack(pop)
