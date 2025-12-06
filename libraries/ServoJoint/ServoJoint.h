#ifndef SERVOJOINT_H
#define SERVOJOINT_H

#include <Arduino.h>
#include <VarSpeedServo.h>

class ServoJoint {
    private:
        VarSpeedServo servo;
        int pin;
        int minAngle;
        int maxAngle;
        int offset;
        int currentAngle;

    public:
    // Construtor
        ServoJoint(int pin, int minAngle = 0, int maxAngle = 180, int offset = 0)
            : pin(pin), minAngle(minAngle), maxAngle(maxAngle), offset(offset), currentAngle(90) {}
        void attach(int initialAngle = 90);
        void detach();
        void moveTo(int angle, int speed = 10, bool wait = false);
        void moveBy(int delta, int speed = 10, bool wait = false);
        int getAngle();
        void setOffset(int newOffset);
};
#endif
