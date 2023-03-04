#ifndef __ADC_SPI_H__
#define __ADC_SPI_H__

#include <stdint.h>
#include <stddef.h>

#define DEFAULT_ADC_SPI_CS 10
#define DEFAULT_ADC_SPI_SPEED 2000000

class ADC_SPI {
	public:
		ADC_SPI();
		ADC_SPI(int CS);
        ADC_SPI(int CS, unsigned int SPIspeed);
		void init(int CS, unsigned int SPIspeed);
		uint16_t read_channel(int channel);
		void read_all_channels(uint16_t* array);
	private:
		int ADC_SPI_CS;
        unsigned int SPI_SPEED;
};


#endif // !<ADC_SPI.H>
#pragma once
