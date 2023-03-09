#pragma once
#include <string.h>
#include <stdint.h>
#ifdef HT_DEBUG_EN
    #include "Arduino.h"
#endif

#pragma pack(push,1)

// @Parseclass
class CCU_status 
#ifdef INHERITANCE_EN
: public CAN_message
#endif
{
public:
    CCU_status() = default;
    CCU_status(uint8_t buf[]) { load(buf); }

    #ifdef INHERITANCE_EN
    inline void load(uint8_t buf[])        override { memcpy(this+sizeof(CAN_message), buf, sizeof(*this)-sizeof(CAN_message)); }
    inline void write(uint8_t buf[]) const override { memcpy(buf, this+sizeof(CAN_message), sizeof(*this)-sizeof(CAN_message)); }
    virtual inline int get_id()      const override { return ID_CCU_STATUS; }
    #else
    inline void load(uint8_t buf[])         { memcpy(this, buf, sizeof(*this)); }
    inline void write(uint8_t buf[])  const { memcpy(buf, this, sizeof(*this)); }
    #endif

    inline bool get_charger_enabled() const { return charger_enabled; }
    inline void set_charger_enabled(bool charger_enabled) { this->charger_enabled = charger_enabled; }

#ifdef HT_DEBUG_EN
    void print() {
        Serial.println("\n\nCCU STATUS");
		Serial.println(     "---------");
		Serial.print("CHARGING: "); Serial.println(charger_enabled);
	}
#endif

private:
    bool charger_enabled; // @Parse
};

#pragma pack(pop)