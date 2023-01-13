#include <Arduino.h>
#include "button.h"
#include "timer.h"
#include "led.h"

#define TIMER_LED_PIN 4
#define TIMER_EX_LED_PIN 6
#define TIMER_BUTTON_PIN 5

#define TIMER_RESET_BUTTON_PIN 7

#define DEBUG_PIN 10

CUtil::Led timerLed(TIMER_LED_PIN);
CUtil::Led timerExLed(TIMER_EX_LED_PIN);

CUtil::Button timerButton(TIMER_BUTTON_PIN);
CUtil::Button timerResetButton(TIMER_RESET_BUTTON_PIN);
CUtil::Button debugButton(DEBUG_PIN);

long timerTarget = (long) 1000L* 60*30;
Timer timer(timerTarget);

void setup()
{
  Serial.begin(9600);
  pinMode(TIMER_LED_PIN, OUTPUT);
  pinMode(TIMER_EX_LED_PIN, OUTPUT);
  pinMode(TIMER_BUTTON_PIN, INPUT);
  pinMode(TIMER_RESET_BUTTON_PIN, INPUT);

  // timerLed = new CUtil::Led(TIMER_LED_PIN);
  // timerExLed = new CUtil::Led(TIMER_EX_LED_PIN);
  // timerButton = new CUtil::Button((int)TIMER_BUTTON_PIN);
  // timerResetButton = new CUtil::Button((int)TIMER_RESET_BUTTON_PIN);

  // timer = new Timer(1000 * 5);
}

void loop()
{
  long currentTimeMillis = millis();

  timerButton.registerButton(currentTimeMillis);
  timerResetButton.registerButton(currentTimeMillis);
  debugButton.registerButton(currentTimeMillis);

  timer.registerTimer(currentTimeMillis);

  if (timerResetButton.isClicked())
  {
    timer.reset();
  }

  if (timerButton.isClicked())
  {
    timer.toggleTimer();
  }

  if (timer.isTimerOn())
  {
    timerLed.setState(CUtil::LED_State::ON);
  }
  else
  {
    timerLed.setState(CUtil::LED_State::OFF);
  }

  if (timer.timerExceeded())
  {
    timerExLed.setState(CUtil::LED_State::ON);
  }
  else
  {
    timerExLed.setState(CUtil::LED_State::OFF);
  }

  if (debugButton.isClicked()) {
    Serial.print("Count Millis: ");
    Serial.println(timer.getCount());
    Serial.print("Target Time: ");
    Serial.println(timer.getTargetTime());
    Serial.print("Current Time: ");
    Serial.println(currentTimeMillis);
  }
}
