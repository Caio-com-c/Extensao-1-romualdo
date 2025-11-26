class Arm6DOF {
public:
    // Juntas do braço
    ServoJoint base;
    ServoJoint shoulder;
    ServoJoint elbow;
    ServoJoint wrist1;
    ServoJoint wrist2;
    ServoJoint gripper;

    // Zeros
    int zeroMaquinaPose[6];
    int zeroPecaPose[6];

    // Construtor (define pinos)
    Arm6DOF() :
        base(2), shoulder(3), elbow(4),
        wrist1(5), wrist2(6), gripper(7)
    {
        // Zero máquina padrão
        zeroMaquinaPose[0] = 90;
        zeroMaquinaPose[1] = 90;
        zeroMaquinaPose[2] = 90;
        zeroMaquinaPose[3] = 90;
        zeroMaquinaPose[4] = 90;
        zeroMaquinaPose[5] = 60;

        // Zero peça começa igual (pode alterar depois)
        for(int i = 0; i < 6; i++)
            zeroPecaPose[i] = zeroMaquinaPose[i];
    }

    // Inicializa as juntas
    void init() {
        base.attach();
        shoulder.attach();
        elbow.attach();
        wrist1.attach();
        wrist2.attach();
        gripper.attach();
    }

    // Move cada junta individual
    void moveBase(int ang)     { base.moveTo(ang); }
    void moveShoulder(int ang) { shoulder.moveTo(ang); }
    void moveElbow(int ang)    { elbow.moveTo(ang); }
    void moveWrist1(int ang)   { wrist1.moveTo(ang); }
    void moveWrist2(int ang)   { wrist2.moveTo(ang); }
    void moveGripper(int ang)  { gripper.moveTo(ang); }

    // Move para toda a pose (6 ângulos)
    void moveToPose(int a0, int a1, int a2, int a3, int a4, int a5) {
        base.moveTo(a0);
        shoulder.moveTo(a1);
        elbow.moveTo(a2);
        wrist1.moveTo(a3);
        wrist2.moveTo(a4);
        gripper.moveTo(a5);
    }

    // ---------- ZERO MÁQUINA ----------
    void definirZeroMaquina(int a0, int a1, int a2, int a3, int a4, int a5) {
        zeroMaquinaPose[0] = a0;
        zeroMaquinaPose[1] = a1;
        zeroMaquinaPose[2] = a2;
        zeroMaquinaPose[3] = a3;
        zeroMaquinaPose[4] = a4;
        zeroMaquinaPose[5] = a5;
    }

    void zeroMaquina() {
        moveToPose(
            zeroMaquinaPose[0],
            zeroMaquinaPose[1],
            zeroMaquinaPose[2],
            zeroMaquinaPose[3],
            zeroMaquinaPose[4],
            zeroMaquinaPose[5]
        );
    }

    // ---------- ZERO PEÇA ----------
    void definirZeroPeca(int a0, int a1, int a2, int a3, int a4, int a5) {
        zeroPecaPose[0] = a0;
        zeroPecaPose[1] = a1;
        zeroPecaPose[2] = a2;
        zeroPecaPose[3] = a3;
        zeroPecaPose[4] = a4;
        zeroPecaPose[5] = a5;
    }

    void zeroPeca() {
        moveToPose(
            zeroPecaPose[0],
            zeroPecaPose[1],
            zeroPecaPose[2],
            zeroPecaPose[3],
            zeroPecaPose[4],
            zeroPecaPose[5]
        );
    }
};

Arm6DOF arm;

void setup() {
    arm.init();

    // Vai para o zero máquina
    arm.zeroMaquina();
    delay(2000);

    // Define um novo zero peça (exemplo)
    arm.definirZeroPeca(100, 70, 120, 40, 90, 50);
}

void loop() {
    // Vai para o zero peça
    arm.zeroPeca();
    delay(2000);

    // Movimento qualquer
    arm.moveToPose(0, 120, 60, 90, 90, 30);
    delay(2000);

    arm.zeroMaquina();
    delay(2000);
}
