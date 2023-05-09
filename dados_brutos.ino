// Inclui as bibliotecas Wire e MPU6050
#include <Wire.h>
#include <MPU6050.h>

// Cria uma instância da classe MPU6050
MPU6050 mpu;

// Configuração inicial
void setup() {
// Inicializa a comunicação com o protocolo I2C
Wire.begin();
// Inicializa a comunicação serial com a taxa de transmissão de 9600 bps
Serial.begin(9600);

// Inicializa o sensor MPU6050
mpu.initialize();
// Verifica a conexão com o MPU6050
Serial.println(mpu.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
}

// Loop principal
void loop() {
// Declara as variáveis que armazenam os valores de aceleração e rotação
int16_t ax, ay, az;
int16_t gx, gy, gz;

// Obtém os valores de aceleração e rotação do sensor MPU6050
mpu.getAcceleration(&ax, &ay, &az);
mpu.getRotation(&gx, &gy, &gz);

// Imprime os valores de aceleração e rotação no monitor serial
Serial.print("AcX: ");
Serial.print(ax); Serial.print(", ");
Serial.print("AcY: ");
Serial.print(ay); Serial.print(", ");
Serial.print("AcZ: ");
Serial.print(az); Serial.print(" ");
Serial.print("GyX: ");
Serial.print(gx); Serial.print(", ");
Serial.print("GyY: ");
Serial.print(gy); Serial.print(", ");
Serial.print("GyZ: ");
Serial.println(gz);

// Aguarda 100ms antes de executar o próximo ciclo do loop
delay(100);
}
