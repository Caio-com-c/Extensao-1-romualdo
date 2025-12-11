# Braço Robótico com Easing

Sistema de controle para braço robótico de 6 graus de liberdade (6-DOF) utilizando servomotores com movimento suave (easing) baseado na biblioteca `ServoEasing` para Arduino.

## 📋 Descrição

Este projeto implementa uma biblioteca e um programa de controle completo para um braço robótico, permitindo movimentos sincronizados e suaves de todos os servos. O sistema inclui controle manual via botões, máquina de estados para gerenciamento de operações e ciclo automático de trabalho.

## 🎯 Características

- **Movimento Suave**: Utiliza easing cúbico para movimentos naturais e fluidos
- **Sincronização**: Todos os servos se movem sincronizadamente para posições definidas
- **Múltiplas Posições de Referência**: Suporte para Home, Zero Peça e Park Pose
- **Controle de Velocidade**: Velocidade global configurável em graus por segundo
- **Máquina de Estados**: Sistema robusto de gerenciamento de estados (Espera, Trabalhando, Parando, Emergência)
- **Controle Manual**: Botões para Start, Stop e Emergência
- **Ciclo Automático**: Execução automática de sequências de movimentos

## 🔧 Hardware Necessário

- Arduino (Uno, Nano ou compatível)
- 6 Servomotores (ex: SG90, MG996R)
- 3 Botões (para Start, Stop e Emergência)
- Fonte de alimentação adequada para os servos (recomendado: 5V externa)
- Protoboard e jumpers

## 📦 Dependências

### Bibliotecas Arduino

- **ServoEasing**: Biblioteca para controle suave de servos
  - Instalação: Gerenciador de Bibliotecas do Arduino IDE → Buscar "ServoEasing" → Instalar

## 🔌 Conexões

### Servos
- Servo 1 (Base): Pino Digital 2
- Servo 2: Pino Digital 3
- Servo 3: Pino Digital 4
- Servo 4: Pino Digital 5
- Servo 5: Pino Digital 6
- Servo 6 (Garra): Pino Digital 7

### Botões (com Pull-Up interno)
- START: Pino Digital 8
- STOP: Pino Digital 9
- EMERGÊNCIA: Pino Digital 10

**Nota**: Os botões devem ser conectados entre o pino e GND (acionam com LOW devido ao pull-up interno).

## 📁 Estrutura do Projeto

```
Extensao-1-romualdo/
├── braco_easing.h      # Definição da classe RobotArm e estrutura RobotPose
├── braco_easing.cpp    # Implementação dos métodos da classe RobotArm
├── braco_easing.ino    # Programa principal com máquina de estados e ciclo automático
└── README.md           # Este arquivo
```

## 🚀 Como Usar

### 1. Instalação

1. Clone ou baixe este repositório
2. Abra o arquivo `braco_easing.ino` no Arduino IDE
3. Instale a biblioteca `ServoEasing` via Gerenciador de Bibliotecas
4. Conecte os servos e botões conforme a seção de Conexões
5. Faça upload do código para o Arduino

### 2. Configuração Inicial

No arquivo `braco_easing.ino`, ajuste as posições conforme seu hardware:

```cpp
// Posição de descanso (evita "pulo" ao ligar)
robot.setParkPose(90, 90, 90, 90, 90, 0);

// Posição Home (calibração)
robot.setZeroMaquina(90, 90, 90, 90, 90, 0);

// Posição Zero Peça (onde o trabalho começa)
robot.setZeroPeca(100, 45, 30, 110, 120, 0);

// Velocidade global (graus por segundo)
robot.setSpeed(40);
```

### 3. Operação

- **START**: Inicia o ciclo automático de trabalho
- **STOP**: Para o ciclo e retorna o robô para Home
- **EMERGÊNCIA**: Para imediatamente e desliga os motores

## 📚 API da Classe RobotArm

### Inicialização

```cpp
RobotArm robot(pino1, pino2, pino3, pino4, pino5, pino6);
robot.begin();
```

### Configuração de Posições

```cpp
// Define posição Home
robot.setZeroMaquina(a1, a2, a3, a4, a5, a6);

// Define posição Zero Peça
robot.setZeroPeca(a1, a2, a3, a4, a5, a6);

// Define posição Park
robot.setParkPose(a1, a2, a3, a4, a5, a6);

// Define velocidade global
robot.setSpeed(grausPorSegundo);
```

### Movimentos

```cpp
// Vai para Home
robot.goHome();

// Vai para Zero Peça
robot.goToZeroPeca();

// Vai para Park
robot.goToPark();

// Move para uma pose customizada
RobotPose minhaPose = {90, 90, 90, 90, 90, 0};
robot.moveToPose(minhaPose);

// Move apenas a garra
robot.moveClaw(angulo);
```

### Controle de Hardware

```cpp
// Liga todos os servos
robot.attachAll();

// Desliga todos os servos
robot.detachAll();

// Para todos os movimentos imediatamente
robot.stopAll();

// Verifica se está se movendo
if (robot.isMoving()) {
    // Robô em movimento
}
```

## 🔄 Ciclo Automático

O ciclo automático executa a seguinte sequência:

1. **Fase 0**: Move para Zero Peça
2. **Fase 1**: Fecha a garra
3. **Fase 2**: Move para posição de depósito
4. **Fase 3**: Abre a garra
5. **Fase 4**: Retorna para posição elevada
6. **Fase 5**: Reinicia o ciclo

As poses e tempos de espera podem ser ajustados na função `executarCicloPassoAPasso()`.

## ⚙️ Estados do Sistema

- **EM_ESPERA**: Robô parado em Home/Park, aguardando comando
- **TRABALHANDO**: Executando ciclo automático
- **PARANDO**: Processando comando de Stop, retornando para Home
- **EMERGENCIA**: Parada total, motores desligados

## ⚠️ Segurança

- O botão de **EMERGÊNCIA** tem prioridade máxima e desliga os motores imediatamente
- O sistema verifica continuamente o estado dos botões
- Movimentos são sincronizados para evitar colisões
- Inicialização suave na posição Park evita "pulos" ao ligar

## 🛠️ Personalização

### Ajustar Poses do Ciclo

Edite as poses na função `executarCicloPassoAPasso()`:

```cpp
RobotPose deposito = {180, 100, 40, 90, 90, 75};
RobotPose subir    = {100, 45, 15, 110, 120, 0};
```

### Modificar Velocidades

Altere a velocidade global ou defina velocidades específicas por movimento:

```cpp
robot.setSpeed(50); // Mais rápido
robot.setSpeed(20); // Mais lento
```

### Adicionar Novas Fases

Adicione novos casos no `switch` da função `executarCicloPassoAPasso()`:

```cpp
case 6:
    Serial.println(F("Fase 6: Nova ação"));
    robot.moveToPose(novaPose);
    iniciarDelay(1000);
    faseAtual++;
    break;
```

## 📝 Notas Técnicas

- O easing padrão é `EASE_CUBIC_IN_OUT` para movimentos naturais
- A biblioteca ServoEasing usa interrupções para sincronização
- Todos os movimentos são não-bloqueantes (non-blocking)
- O sistema usa `millis()` para delays não-bloqueantes

## 🐛 Troubleshooting

**Problema**: Servos não se movem
- Verifique as conexões de alimentação
- Confirme que os pinos estão corretos
- Verifique se os servos estão anexados (`robot.attachAll()`)

**Problema**: Movimentos bruscos
- Reduza a velocidade com `robot.setSpeed()`
- Verifique se a posição Park está correta

**Problema**: Botões não funcionam
- Verifique se estão conectados corretamente (pino → botão → GND)
- Teste com multímetro se o botão está funcionando

## 📄 Licença

Este projeto é fornecido como está, para uso educacional e pessoal.

## 👤 Autor

Projeto desenvolvido para controle de braço robótico com extensão de easing.

---

**Versão**: 1.0  
**Última atualização**: 2024

