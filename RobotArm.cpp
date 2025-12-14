#include "RobotArm.h"

RobotArm::RobotArm(int p1, int p2, int p3, int p4, int p5, int p6) {
    pinos[0] = p1; pinos[1] = p2; pinos[2] = p3;
    pinos[3] = p4; pinos[4] = p5; pinos[5] = p6;

    // Valores padrão
    setMachineZero(0, 0, 0, 0, 0, 0);
    setWorkZero(0, 0, 0, 0, 0, 0);
    setParkPose(0, 0, 0, 0, 0, 0);
    speedGlobal = 25; 
}

void RobotArm::begin() {
    // Inicializa cada servo usando attachWithTrim
    // Isso garante que 90 graus seja tratado como o centro calibrado
    for (int i = 0; i < 6; i++) {
        
        // attachWithTrim(PINO, TRIM_DEGREE, START_DEGREE, MIN_MICROS, MAX_MICROS, MIN_ANGLE, MAX_ANGLE)
        // TRIM_DEGREE: 0 (onde o pulso é 1500us, aprox)
        // START_DEGREE: Posição de repouso (Park) para não dar tranco
        
        if (servos[i].attachWithTrim(
                pinos[i], 
                0,   // 90 graus
                parkPose.angles[i],  // Posição inicial
                SERVO_MIN_MICROS,    // 700 ou customizado
                SERVO_MAX_MICROS,     // 2300 ou customizado
                -90,
                90
            ) == INVALID_SERVO) {
             // Opcional: Serial.println("Erro servo");
        }
        
        // Define suavização Cúbica (Movimento natural)
        servos[i].setEasingType(EASE_CUBIC_IN_OUT); 
    }
}

void RobotArm::setMachineZero(int a1, int a2, int a3, int a4, int a5, int a6) {
    machineZero = {a1, a2, a3, a4, a5, a6};
}

void RobotArm::setWorkZero(int a1, int a2, int a3, int a4, int a5, int a6) {
    workZero = {a1, a2, a3, a4, a5, a6};
}

void RobotArm::setParkPose(int a1, int a2, int a3, int a4, int a5, int a6) {
    parkPose = {a1, a2, a3, a4, a5, a6};
}

void RobotArm::setSpeed(int degreesPerSecond) {
    speedGlobal = degreesPerSecond;
}

void RobotArm::attachAll() {
    for (int i = 0; i < 6; i++) {
        if (!servos[i].attached()) {
            // Usa attachWithTrim novamente ao reconectar
            servos[i].attachWithTrim(
                pinos[i], 
                SERVO_TRIM_DEGREE, 
                servos[i].getCurrentAngle(), // Mantém posição atual
                SERVO_MIN_MICROS, 
                SERVO_MAX_MICROS
            );
        }
    }
}

void RobotArm::detachAll() {
    for (int i = 0; i < 6; i++) {
        servos[i].detach();
    }
}

void RobotArm::stopAll() {
    // Função global da biblioteca
    stopAllServos(); 
}

void RobotArm::moveToPose(RobotPose pose) {
    uint16_t speedInt = (uint16_t)speedGlobal;

    for (int i = 0; i < 6; i++) {
        // setEaseTo apenas agenda o movimento
        servos[i].setEaseTo(pose.angles[i], speedInt);
    }
    
    // Sincroniza e inicia o movimento
    synchronizeAllServosAndStartInterrupt();
}

void RobotArm::goHome() {
    moveToPose(machineZero);
}

void RobotArm::goToWorkZero() {
    moveToPose(workZero);
}

void RobotArm::goToPark() {
    moveToPose(parkPose);
}

void RobotArm::moveClaw(int angle) {
    uint16_t speedInt = (uint16_t)speedGlobal;
    servos[5].startEaseTo(angle, speedInt);
}

bool RobotArm::isMoving() {
    return ServoEasing::areInterruptsActive();
}