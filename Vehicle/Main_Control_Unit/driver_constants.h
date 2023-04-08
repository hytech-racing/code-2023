#pragma once

#include "drivers.h"

#ifdef DRIVER
    #if DRIVER == DEFAULT_DRIVER
      #define BRAKE_ACTIVE 2200                // Threshold for brake pedal active  

        #define MIN_ACCELERATOR_PEDAL_1 1000    // Low accelerator implausibility threshold
        #define START_ACCELERATOR_PEDAL_1 1370  // Position to start acceleration //1140 + pressure 1151
        #define END_ACCELERATOR_PEDAL_1 2075    // Position to max out acceleration //1905
        #define MAX_ACCELERATOR_PEDAL_1 2300    // High accelerator implausibility threshold

        #define MIN_ACCELERATOR_PEDAL_2 500    // Low accelerator implausibility threshold
        #define START_ACCELERATOR_PEDAL_2 680  // Position to start acceleration 560 + pressure 570
        #define END_ACCELERATOR_PEDAL_2 1035    // Position to max out acceleration 948
        #define MAX_ACCELERATOR_PEDAL_2 1200   // High accelerator implausibility threshold

        #define MIN_BRAKE_PEDAL_1 1876    // Low brale implausibility threshold
        #define START_BRAKE_PEDAL_1 2090  // Position to start brake // 2078 + pressure
        #define END_BRAKE_PEDAL_1 2445    // Position to max out brake 2718 +-5
        #define MAX_BRAKE_PEDAL_1 2700
         
//brake 2 is negative slope
        #define MIN_BRAKE_PEDAL_2 2300    // Low brake implausibility threshold
        #define START_BRAKE_PEDAL_2 2030  // Position to start brake //2045 - pressure 
        #define END_BRAKE_PEDAL_2 1670    // Position to max out brake //1410 +- 5
        #define MAX_BRAKE_PEDAL_2 1400

        #define BRAKE_THRESHOLD_MECH_BRAKE_1 2345 // brake 1, mech brake threshold +-5
        #define BRAKE_THRESHOLD_MECH_BRAKE_2 1780 // brake 2, mech brake threshold +-5
    #else
        #error "Bad driver definition"
    #endif
#else
    #error "Driver required"
#endif

#define HALF_ACCELERATOR_PEDAL_1 ((START_ACCELERATOR_PEDAL_1 + END_ACCELERATOR_PEDAL_1)/2)
#define HALF_ACCELERATOR_PEDAL_2 ((START_ACCELERATOR_PEDAL_2 + END_ACCELERATOR_PEDAL_2)/2)
