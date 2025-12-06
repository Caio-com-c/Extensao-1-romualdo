#include "RobotArm.h"

// Construtor
RobotArm::RobotArm(ServoJoint* s1, ServoJoint* s2, ServoJoint* s3, ServoJoint* s4, ServoJoint* s5, ServoJoint* s6) {
    // Armazena os ponteiros para acessar os servos originais
    joints[0] = s1;
    joints[1] = s2;
    joints[2] = s3;
    joints[3] = s4;
    joints[4] = s5;
    joints[5] = s6;

    // Inicializa zeros com valores padrão (90 graus) para segurança
    setMachineZero(90, 90, 90, 90, 90, 90);
    setWorkZero(90, 90, 90, 90, 90, 90);
}

void RobotArm::setMachineZero(int a1, int a2, int a3, int a4, int a5, int a6) {
    machineZero = {a1, a2, a3, a4, a5, a6};
}

void RobotArm::setWorkZero(int a1, int a2, int a3, int a4, int a5, int a6) {
    workZero = {a1, a2, a3, a4, a5, a6};
}

void RobotArm::attachAll() {
    for (int i = 0; i < 6; i++) {
        // Anexa já na posição de Machine Zero para evitar movimentos bruscos
        joints[i]->attach(machineZero.angles[i]);
    }
}

void RobotArm::detachAll() {
    for (int i = 0; i < 6; i++) {
        joints[i]->detach();
    }
}

void RobotArm::goHome(int speed) {
    moveToPose(machineZero, speed);
}

void RobotArm::goToWorkZero(int speed) {
    moveToPose(workZero, speed);
}

void RobotArm::moveToPose(RobotPose pose, int speed) {
    for (int i = 0; i < 6; i++) {
        // wait = false: Isso é crucial!
        // Faz com que todos os servos recebam o comando quase ao mesmo tempo
        // e se movam juntos, em vez de um de cada vez.
        joints[i]->moveTo(pose.angles[i], speed, false);
    }
}