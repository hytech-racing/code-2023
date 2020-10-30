/*
 * MC_read_write_parameter_response.cpp - CAN message parser: RMS Motor Controller read / write parameter response message - response from PM
 * Created by Nathan Cheek, November 22, 2016.
 */

#pragma once
#include <string.h>
#include <cstdint>

#pragma pack(push,1)

class MC_read_write_parameter_response {
public:
    MC_read_write_parameter_response() = default;
    MC_read_write_parameter_response(uint8_t buf[8]) { load(buf); }

    inline void load(uint8_t buf[])     { memcpy(this, buf, sizeof(*this)); }
    inline void write(uint8_t buf[])    { memcpy(buf, this, sizeof(*this)); }

    inline uint16_t get_parameter_address() const { return parameter_address; }
    inline bool get_write_success()         const { return write_success; }
    inline uint32_t get_data()              const { return data; }
private:
    uint16_t parameter_address;
    bool write_success;
    uint8_t reserved1;
    uint32_t data;
} CAN_message_mc_read_write_parameter_response_t;

#pragma pack(pop)