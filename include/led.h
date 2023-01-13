#include <Arduino.h>

#ifndef CUTIL_LED
#define CUTIL_LED
namespace CUtil {
    enum LED_State {
        ON,
        OFF
    };
    class Led {
        private:
        LED_State state;
        int pinNum = 0;

        public:
        Led(int pinNum) {
            this->pinNum = pinNum;
        }

        LED_State currentState() {
            return this->state;
        }

        void setState(LED_State state) {
            if (state != this->state) {
                this->state = state;

                if (this->state == ON) {
                    digitalWrite(this->pinNum, HIGH);
                } else {
                    digitalWrite(this->pinNum, LOW);
                }
            }
        }
    };
}
#endif