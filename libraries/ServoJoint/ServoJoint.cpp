#include <ServoJoint.h>

// Anexa o servo ao pino e define posição inicial
void ServoJoint::attach(int initialAngle = 90) {
    if (!servo.attached()) {
        initialAngle = constrain(initialAngle, minAngle, maxAngle);
        currentAngle = initialAngle;

        // Move internamente antes de anexar para evitar "pulos"
        servo.write(currentAngle + offset);
        servo.attach(pin);
    }
}

// Desanexa o servo (economiza energia/para de forçar o motor)
void ServoJoint::detach() {
    if (servo.attached()) {
        servo.detach();
    }
}

void ServoJoint::moveTo(int angle, int speed = 10, bool wait = false) {
    if (!servo.attached()) return;

    // Limita o ângulo lógico
    angle = constrain(angle, minAngle, maxAngle);
    currentAngle = angle;

    // Calcula posição física considerando o offset
    int physicalAngle = constrain(angle + offset, 0, 180);

    servo.slowmove(physicalAngle, speed);

    if (wait) {
        servo.wait(); // Espera o movimento terminar
    }
}

// Movimento Incremental (relativo à posição atual)
void ServoJoint::moveBy(int delta, int speed = 10, bool wait = false) {
    moveTo(currentAngle + delta, speed, wait);
}

// Retorna o ângulo lógico atual
int ServoJoint::getAngle() {
    return currentAngle;
}

// Ajusta o offset (calibração de zero)
void ServoJoint::setOffset(int newOffset) {
    offset = newOffset;
    // Atualiza a posição atual com o novo offset
    moveTo(currentAngle);
}
