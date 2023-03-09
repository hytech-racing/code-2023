#pragma once
#include <string.h>
#include <stdint.h>
#ifdef HT_DEBUG_EN
    #include "Arduino.h"
#endif

#pragma pack(push,1)

class MC_status
#ifdef INHERITANCE_EN
: public CAN_message
#endif
{
public:
  MC_status() = default;
  MC_status(uint8_t buf[]) { load(buf); }

  #ifdef INHERITANCE_EN
  inline void load(uint8_t buf[])        override { memcpy(this+sizeof(CAN_message), buf, sizeof(*this)-sizeof(CAN_message)); }
  inline void write(uint8_t buf[]) const override { memcpy(buf, this+sizeof(CAN_message), sizeof(*this)-sizeof(CAN_message)); }
  virtual inline int get_id()      const override { return ID_MC1_STATUS; }
  #else
  inline void load(uint8_t buf[])         { memcpy(this, buf, sizeof(*this)); }
  inline void write(uint8_t buf[])  const { memcpy(buf, this, sizeof(*this)); }
  #endif

  inline uint16_t get_status_word()   const { return status_word; }
  inline int16_t get_speed()       const { return speed; }
  inline int16_t get_torque()       const { return torque; }
  inline int16_t get_torque_current()       const { return torque_current; }

  inline bool get_system_ready() const {return status_word & 0x100; }
  inline bool get_error() const {return status_word & 0x200; }
  inline bool get_warning() const {return status_word & 0x400; }
  inline bool get_quit_dc_on() const {return status_word & 0x800; }
  inline bool get_dc_on() const {return status_word & 0x1000; }
  inline bool get_quit_inverter_on() const {return status_word & 0x2000; }
  inline bool get_inverter_on() const {return status_word & 0x4000; }
  inline bool get_derating_on() const {return status_word & 0x8000; }

  inline void set_status_word(const uint16_t word)   { status_word = word; }

private:
    uint16_t status_word;
    int16_t speed; //speed in rpm
    int16_t torque; //torque in 0.1% mn
    int16_t torque_current; //torque current in 0.1A
};

#pragma pack(pop)
