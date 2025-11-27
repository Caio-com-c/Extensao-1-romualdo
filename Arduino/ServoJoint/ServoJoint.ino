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

    // Anexa o servo ao pino
    void attach() {
        servo.attach(pin);
        //servo.slowmove(currentAngle + offset, 10);
    }

    // Mover para ângulo absoluto
    void moveTo(int angle) {
        angle = constrain(angle, minAngle, maxAngle);
        currentAngle = angle;
        servo.slowmove(angle + offset, 10);
    }

    // Incremental
    void moveBy(int delta) {
        moveTo(currentAngle + delta);
    }

    // Ler ângulo atual
    int getAngle() {
        return currentAngle;
    }

    // Definir offset no eixo
    void setOffset(int o) {
        offset = o;
        servo.slowmove(currentAngle + offset, 10);
    }
};


//Criação dos Servos
// Manipulador de 6 DOF
ServoJoint servo1(5, 0, 180);         // SERVO 1

void setup() {
    servo1.attach();

    // Posição inicial
    servo1.moveTo(0);
}


void loop() {
    
    servo1.moveTo(0);
    delay(1500);
    
    // Volta para o zero máquina
    servo1.moveTo(20);
    delay(1500);

    
}
