#include <Arduino.h>

/*
 * braco_easing.ino
 * Controle de Braço Robótico 6-DOF com ServoEasing e AttachWithTrim
 */

// --- OBRIGATÓRIO: Inclua .hpp AQUI para o compilador gerar o código da biblioteca ---
#include <ServoEasing.hpp> 
#include "RobotArm.h"

void lerBotoes();
void executarCicloPassoAPasso();
void iniciarDelay(unsigned long);
void gerenciarEstados();

// --- PINOS DOS BOTÕES ---
const int PIN_START = 8;
const int PIN_STOP = 9;
const int PIN_EMERGENCIA = 10;

// --- CONFIGURAÇÃO DOS PINOS DOS SERVOS (Base -> Garra) ---
// Pinos: 2, 3, 4, 5, 6, 7
RobotArm robot(2, 3, 4, 5, 6, 7);

// --- ESTADOS DO SISTEMA ---
enum EstadoSistema {
    EM_ESPERA,      // Parado em Home/Park
    TRABALHANDO,    // Executando o ciclo
    PARANDO,        // Solicitado STOP, finalizando movimento
    EMERGENCIA      // Parada total (motores soltos)
};

EstadoSistema estadoAtual = EM_ESPERA;

// --- VARIÁVEIS DE CONTROLE ---
int faseAtual = 0;
unsigned long tempoInicioEspera = 0;
bool emPausaDelay = false;
unsigned long duracaoDelay = 0;

void setup() {
    Serial.begin(115200);
    
    pinMode(PIN_START, INPUT_PULLUP);
    pinMode(PIN_STOP, INPUT_PULLUP);
    pinMode(PIN_EMERGENCIA, INPUT_PULLUP);

    // 1. Configurações de Posição (Ângulos)
    // Park: Posição física de descanso (para evitar tranco ao ligar)
    // Esses valores serão usados como "START_DEGREE_VALUE" no attach
    robot.setParkPose(-90, -90, -90, -90, -90, -90); 
    
    // Zero Máquina e Zero Peça
    robot.setMachineZero(0, 0, -90, 0, 0, -90);
    robot.setWorkZero(10, -45, -60, 10, 30, -90);
    
    // Velocidade global
    robot.setSpeed(30);

    // 2. Inicialização do Robô
    Serial.println(F("Inicializando com attachWithTrim..."));
    
    // Attach com trim para calibração de 1500us = 90 graus
    robot.begin(); 
    
    delay(500);

    // Vai para Home
    Serial.println(F("Indo para Home..."));
    robot.goHome();
    
    // Aguarda chegar em Home
    while(robot.isMoving()) { 
        delay(10); 
    }
    
    Serial.println(F("Pronto. Aguardando Start."));
    estadoAtual = EM_ESPERA;
}

void loop() {
    lerBotoes();
    gerenciarEstados();
}

void lerBotoes() {
    if (digitalRead(PIN_EMERGENCIA) == LOW) {
        if (estadoAtual != EMERGENCIA) {
            Serial.println(F("!!! EMERGÊNCIA !!!"));
            robot.stopAll();
            robot.detachAll();
            estadoAtual = EMERGENCIA;
        }
    }

    if (digitalRead(PIN_STOP) == LOW) {
        if (estadoAtual == TRABALHANDO) {
            Serial.println(F("STOP. Voltando para Home..."));
            robot.stopAll();
            robot.attachAll();
            robot.setSpeed(30);
            robot.goHome();
            estadoAtual = PARANDO;
        }
    }

    if (digitalRead(PIN_START) == LOW) {
        if (estadoAtual != TRABALHANDO) {
            Serial.println(F("Iniciando Ciclo..."));
            robot.attachAll();
            if (estadoAtual == EMERGENCIA) {
                robot.goHome();
                while(robot.isMoving()); 
            }
            faseAtual = 0;
            emPausaDelay = false;
            robot.setSpeed(25);
            estadoAtual = TRABALHANDO;
            delay(300);
        }
    }
}

void gerenciarEstados() {
    switch (estadoAtual) {
        case EM_ESPERA: break;
        case EMERGENCIA: break;
        case PARANDO:
            if (!robot.isMoving()) {
                Serial.println(F("Parado em Home."));
                estadoAtual = EM_ESPERA;
            }
            break;
        case TRABALHANDO:
            executarCicloPassoAPasso();
            break;
    }
}

void executarCicloPassoAPasso() {
    if (robot.isMoving()) return;

    if (emPausaDelay) {
        if (millis() - tempoInicioEspera >= duracaoDelay) {
            emPausaDelay = false;
        } else {
            return;
        }
    }

    RobotPose deposito = {-90, 10, -30, 0, 0, -15};
    RobotPose subir    = {10, -45, -20, 10, 30, -90}; // zeroMaquina (10, -45, -60, 10, 30, -90) 

    switch (faseAtual) {
        case 0:
            robot.goToWorkZero();
            iniciarDelay(1000);
            faseAtual++;
            break;
        case 1:
            robot.moveClaw(-15);    // abre a garra
            iniciarDelay(2000);
            faseAtual++;
            break;
        case 2:
            robot.moveToPose(deposito);
            iniciarDelay(2300);
            faseAtual++;
            break;
        case 3:
            robot.moveClaw(-90);      // fecha a garra
            iniciarDelay(1000);
            faseAtual++;
            break;
        case 4:
            robot.moveToPose(subir);
            iniciarDelay(2000);
            faseAtual++;
            break;
        case 5:
            faseAtual = 0; // Reinicia ciclo
            break;
    }
}

void iniciarDelay(unsigned long ms) {
    emPausaDelay = true;
    tempoInicioEspera = millis();
    duracaoDelay = ms;
}