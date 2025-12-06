#ifndef ROBOTARM_H
#define ROBOTARM_H

#include <Arduino.h>
#include "ServoJoint.h"

// Estrutura para facilitar o envio de 6 coordenadas de uma vez
struct RobotPose {
    int angles[6];
};

class RobotArm {
    private:
        ServoJoint* joints[6]; // Array de ponteiros para manipular os servos
        RobotPose machineZero; // Armazena a calibração física (Zero Máquina)
        RobotPose workZero;    // Armazena o ponto de referência do trabalho (Zero Peça)

    public:
        // Construtor: Recebe os endereços dos 6 objetos ServoJoint
        RobotArm(ServoJoint* s1, ServoJoint* s2, ServoJoint* s3, ServoJoint* s4, ServoJoint* s5, ServoJoint* s6);

        // Define onde é o Zero Máquina (calibração física)
        void setMachineZero(int a1, int a2, int a3, int a4, int a5, int a6);

        // Define onde é o Zero Peça (offset de trabalho)
        void setWorkZero(int a1, int a2, int a3, int a4, int a5, int a6);

        // Inicializa todos os servos na posição de Machine Zero (evita pulos bruscos ao ligar)
        void attachAll();

        // Solta todos os motores
        void detachAll();

        // Move o robô para o Zero Máquina
        void goHome(int speed = 20);

        // Move o robô para o Zero Peça
        void goToWorkZero(int speed = 20);

        // Move todos os eixos simultaneamente para uma pose específica
        // Se wait = true, ele tenta estimar uma espera (ou você usa delay no loop)
        void moveToPose(RobotPose pose, int speed);
};

#endif