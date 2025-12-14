#ifndef ROBOTARM_H
#define ROBOTARM_H

#include <Arduino.h>
#include <ServoEasing.h> // Header apenas para tipos

// --- CONSTANTES DE CALIBRAÇÃO DOS SERVOS ---
// Ajuste estes valores conforme o datasheet do seu servo específico
// Para a maioria dos servos analógicos padrão (SG90, MG996R):
#define SERVO_MIN_MICROS      500  // Valor de pulso para 0 graus (700)
#define SERVO_MAX_MICROS      2500 // Valor de pulso para 180 graus (2500)

struct RobotPose {
    int angles[6];
};

class RobotArm {
    private:
        ServoEasing servos[6]; 
        int pinos[6];          
        
        RobotPose machineZero; 
        RobotPose workZero;    
        RobotPose parkPose;    

        int speedGlobal;     

    public:
        RobotArm(int p1, int p2, int p3, int p4, int p5, int p6);

        void begin(); 

        void setMachineZero(int a1, int a2, int a3, int a4, int a5, int a6);
        void setWorkZero(int a1, int a2, int a3, int a4, int a5, int a6);
        void setParkPose(int a1, int a2, int a3, int a4, int a5, int a6);
        void setSpeed(int degreesPerSecond);

        void attachAll();       
        void detachAll();       
        void stopAll();         

        void goHome();
        void goToWorkZero();
        void goToPark();
        void moveToPose(RobotPose pose);
        void moveClaw(int angle);

        bool isMoving();
};

#endif