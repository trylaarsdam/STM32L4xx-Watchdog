#include <Arduino.h>
#include "watchdog.hpp"
#include "stm32l4xx_hal_rcc.h"
#include "stm32lowpower.h"

WatchDog watchdog;
#define LED_PIN D3
#define BUTTON_PIN USER_BTN
#define TEST_PIN D2
#define WATCHDOG_HOLD_PIN D7

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
  pinMode(TEST_PIN, OUTPUT);
  pinMode(WATCHDOG_HOLD_PIN, INPUT);
  if(__HAL_RCC_GET_FLAG(RCC_FLAG_IWDGRST)) {
    digitalWrite(LED_PIN, HIGH);
  }
  else {
    digitalWrite(LED_PIN, LOW);
  }
  __HAL_RCC_CLEAR_RESET_FLAGS();

  watchdog.init(10);
  LowPower.begin();
}

void loop() {
  digitalWrite(TEST_PIN, HIGH);
  delay(100);
  digitalWrite(TEST_PIN, LOW);
  while(!digitalRead(BUTTON_PIN)) {
    if(digitalRead(WATCHDOG_HOLD_PIN)) {
    }
    else {
      watchdog.pet();
    }
  }
  while(1) {
    digitalWrite(LED_PIN, HIGH);
    delay(300);
    digitalWrite(LED_PIN, LOW);
    delay(300);
    digitalWrite(LED_PIN, HIGH);
    delay(300);
    digitalWrite(LED_PIN, LOW);
    // watchdog.enableFreezeForShutdown();
    LowPower.shutdown(30000);
  }
}