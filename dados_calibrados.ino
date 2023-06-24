#include<Wire.h>
#include<Math.h>

// Endereco I2C do sensor MPU-6050
const int MPU = 0x68;
int cont = 0;

// Variaveis para armazenar valores do sensor
double AccX, AccY, AccZ, AccXf, AccYf, AccZf, theta_pitch, theta_pitch2;

void setup() {
  // Inicializa Serial
  Serial.begin(9600);

  // Inicializa o MPU-6050
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);

  // Configura Acelerometro para fundo de escala desejado
  Wire.beginTransmission(MPU);
  Wire.write(0x1C);
  Wire.write(0b00000000);  // Trocar esse comando para fundo de escala desejado conforme acima
  Wire.endTransmission();
}

void loop() {
  // Comandos para iniciar transmissão de dados
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 14, true); // Solicita os dados ao sensor

  // Armazena o valor dos sensores nas variaveis correspondentes
  AccX = Wire.read() << 8 | Wire.read(); //0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  AccY = Wire.read() << 8 | Wire.read(); //0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AccZ = Wire.read() << 8 | Wire.read(); //0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)

  AccXf = ((AccX / 16384) - 0.01645);
  AccYf = ((AccY / 16384) + 0.0011);
  AccZf = ((AccZ / 16384) + 0.04805);

if (cont<100) {

  // Imprime na Serial os valores obtidos
Serial.print("X: ");
Serial.print(AccX / 16384);

Serial.print(" Y: ");
Serial.print(AccY / 16384);

Serial.print(" Z: ");
Serial.print(AccZ / 16384);

  //Imprime na Serial os valores obtidos CORRIGIDOS com offset
Serial.print("          X c/ Offset: ");
Serial.print(AccXf);

Serial.print("      Y c/ Offset: ");
Serial.print(AccYf);

Serial.print("      Z c/ Offset: ");
Serial.print(AccZf);

    // Cálculo do ângulo utilizando X como eixo de rotação com conversão de radianos para graus
theta_pitch = (atan( (AccYf / (sqrt ((square (AccXf)) + (square (AccZf)))) )))*180/M_PI;

Serial.print("      ANGULO ");
Serial.println(theta_pitch);

 cont++;}

    //Atraso de 100ms
  delay(100);
}
