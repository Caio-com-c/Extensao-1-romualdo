# Extensao-1-romualdo

Criar de modelos em POO: 

Classe 1 - Criação de cada servo/junta
Classe ServoJoint
Representa cada junta do robô:
pino do servo
ângulo atual
limites de ângulo
velocidade de movimento
métodos como moveTo(angle) ou moveSmooth(angle, speed)
Classe 2 - Criação do conjunto completo
Classe Arm6DOF
Gerencia o conjunto de juntas:
lista/array de 6 ServoJoint
método moveToPose({theta1..theta6})
sequências automáticas
Bibliotecas utilizadas: 
VarSpeedServo
ServoEasing
RoboticArm.h 
Dicas importante:
Servomotores precisam de fonte externa;
Zero máquina:
Posição mecânica de referência fixa, usada para inicializar, calibrar ou voltar a um estado seguro.
Zero peça:
É a referência relativa ao ambiente, por exemplo:
origem do plano de trabalho
o local onde está uma peça
um ponto (x, y, z) que você define
offset baseado em sensores, toques ou calibrações manuais
