#pragma once
#include <Arduino.h>
#include <stm32l4xx.h>
#include <stm32l4xx_hal_iwdg.h>
#include "constants.hpp"
#include <stm32l4xx_hal_flash.h> 

#define kWatchdogPulsesPerSecond 128 // assuming LSE at 32.768kHz, prescaler = 256, 155 * seconds, 155 gives an accurate reload value

class WatchDog {
    private:
        bool watchdogEnabled = false;
        IWDG_HandleTypeDef IwdgHandle;
    public:
        void init(uint32_t secondsToTimeout);
        void pet();

        bool isEnabled();
        // void runWhileSleeping(bool yes = true);
        // void runWhileAtBreakpoint(bool yes = true);
};
