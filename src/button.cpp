#include <Arduino.h>
#include "button.h"

class Button {
    private:
        int lastRegisterTime = 0;
        int marginTime = 50; // time margin that prevents events of button, default 50 ms
        int buttonDownTime = 0; // how long has the button been down
        bool prevButtonDownState = false;
        bool buttonDown = false;

        // hardware
        int pinNum;
    
    public:
        Button(int marginTime, int pinNum) {
            this->marginTime = marginTime;
            this->pinNum = pinNum;
        }

        Button(int pinNum): Button(50, pinNum){}

        // method to registering a button, this should be called in the beginning of each execution loop
        // input: currentTime: the currentTime of the execution in Millis
        void registerButton(int currentTime) {
            this->prevButtonDownState = this->buttonDown; // storing click state

            if (currentTime >= this->lastRegisterTime + this->marginTime) {
                this->buttonDown = digitalRead(this->pinNum) == HIGH;

                // update button down Time
                if (!this->buttonDown) {
                    this->buttonDownTime = 0;
                } else if (this->buttonDown && this->prevButtonDownState) {
                    this->buttonDownTime += currentTime - this->lastRegisterTime;
                }

                // update register time
                lastRegisterTime = currentTime;
            }
        }

        bool isClicked() {
            return this->buttonDown && !this->prevButtonDownState;
        }

        bool isReleased() {
            return !this->buttonDown && this->prevButtonDownState;
        }

        int getButtonDownTime() {
            return this->buttonDownTime;
        }
};