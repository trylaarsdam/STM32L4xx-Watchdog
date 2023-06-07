#include "watchdog.hpp"


void WatchDog::init(uint32_t secondsToTimeout) {
  watchdogEnabled = true;
  IwdgHandle.Instance = IWDG;
	IwdgHandle.Init.Prescaler = IWDG_PRESCALER_256;
	IwdgHandle.Init.Reload    = secondsToTimeout * kWatchdogPulsesPerSecond;
  IwdgHandle.Init.Window    = 0xFFF;
  HAL_IWDG_Init(&IwdgHandle);

	if(HAL_IWDG_Init(&IwdgHandle) != HAL_OK)
	{
		/* Initialization Error */
    digitalWrite(D4, HIGH);
	}
}

void WatchDog::pet() {
  HAL_IWDG_Refresh(&IwdgHandle); // resets the IWDG counter back to 0
}

bool WatchDog::isEnabled() {
  return watchdogEnabled;
}