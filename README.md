# STM32L4xx Watchdog Library

## Usage

### Creating Watchdog Object
```cpp
#include "WatchDog.hpp"

WatchDog watchdog;
```

### Initializing the Watchdog
```cpp
watchdog.init([seconds]);
```
[seconds] specifies the timeout period for the watchdog. If the watchdog is not "pet" within this amount of time (excluding when sleeping in `Shutdown` mode), the device will be reset and the IWDGRST RCC flag will be set.

### Petting/Refreshing the Watchdog Countdown
```cpp
watchdog.pet();
```

### Checking if the Watchdog is Currently Enabled
```cpp
watchdog.isEnabled();
```
This function returns a `bool`, where `true` means the watchdog is enabled and `false` designates the watchdog is not running. Note: this function only returns `true` when that watchdog instance has started the watchdog, and will not return `true` when another object has started the watchdog or the watchdog has been started manually.

### Checking if the Watchdog caused a system reset
```cpp
if(__HAL_RCC_GET_FLAG(RCC_FLAG_IWDGRST)) {
  //watchdog caused reset
}
else {
  //watchdog did not cause reset
}
__HAL_RCC_CLEAR_RESET_FLAGS(); // clears reset flags, otherwise on the next reset even though the watchdog may not have caused the reset `RCC_FLAG_IWDGRST` will still be set.
```