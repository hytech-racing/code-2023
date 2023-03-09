#pragma once

class CAN_message{
    public:
        CAN_message() = default;
        virtual inline void load(uint8_t buf[]) = 0;
        virtual inline void write(uint8_t buf[]) const = 0;
        virtual inline int get_id() const = 0;
};