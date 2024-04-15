#include "deep_sleep.h"

void deep_sleep(uint16_t start_time)
{
  uint16_t time_awake = millis() - start_time;

  #if DEBUG_ENABLE == 1
    Serial.println("Going to sleep now");
    Serial.println("Total time awake: " + String(time_awake) + "ms");
  #endif
  
  uint32_t calculated_sleep_time = TIME_TO_SLEEP * uS_TO_S_FACTOR - (time_awake * mS_TO_S_FACTOR);
  if(calculated_sleep_time < 0){
    calculated_sleep_time = TIME_TO_SLEEP * uS_TO_S_FACTOR;
  }

  esp_sleep_enable_timer_wakeup(calculated_sleep_time);
  delay(200); // without this the deep sleep doesnt work properly
  esp_deep_sleep_start();
}