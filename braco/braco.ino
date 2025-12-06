#include <ServoJoint.h>
#include "RobotArm.h" // Inclua a nova classe

// Criação dos Servos (Hardware)
ServoJoint servo1(2, 0, 180);
ServoJoint servo2(3, 0, 180);
ServoJoint servo3(4, 0, 180);
ServoJoint servo4(5, 0, 180);
ServoJoint servo5(6, 0, 180);
ServoJoint servo6(7, 0, 180);

// Criação do objeto Robô (Gerenciador)
// Passamos o endereço (&) de cada servo para o gerenciador controlar
RobotArm robot(&servo1, &servo2, &servo3, &servo4, &servo5, &servo6);

void setup() {
    //Serial.begin(9600);
    
    // 1. Defina aqui a calibração física do seu robô (Onde ele "nasce")
    robot.setMachineZero(90, 90, 0, 90, 90, 0); 
    
    // 2. Defina o ponto onde a peça está (Zero Peça)
    // Se mudar o layout da mesa, altere apenas esta linha!
    robot.setWorkZero(100, 45, 30, 110, 120, 0);

    // Inicializa e vai suavemente para o Machine Zero
    robot.attachAll(); 
    delay(2000);
}

void loop() {
    // Vai para o ponto de trabalho (Zero Peça)
    robot.goToWorkZero(15);
    delay(1500); // Delay necessário pois os servos movem em background

    // Fecha a garra (Acessando o servo específico para ação pontual)
    servo6.moveTo(75, 12, true); 
    
    // Define uma nova posição (ex: ponto de depósito)
    RobotPose deposito = {180, 100, 40, 90, 90, 75};
    RobotPose subir = {100, 45, 15, 110, 120, 0};
    
    // Move o robô inteiro para o depósito
    robot.moveToPose(deposito, 12);
    delay(4000);
    // Abre a garra (Acessando o servo específico para ação pontual)
    servo6.moveTo(0, 12, true); 

    // subir para casa
    //robot.goHome(30);
    robot.moveToPose(subir, 12);

    delay(3000);
}