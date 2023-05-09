#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    // aguarda a porta serial ficar disponível
  }

  Wire.begin();
  mpu.initialize();
}

void loop() {
  // lê os valores de medição do acelerômetro e do giroscópio
  int16_t ax, ay, az, gx, gy, gz;
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  // converte os valores de medição do acelerômetro de mg para g (fração de gravidade)
  float ax_g = ax / 16384.0; // 16384 LSB/g
  float ay_g = ay / 16384.0;
  float az_g = az / 16384.0;

  // imprime os valores no Monitor Serial
  Serial.print("AcX: ");
  Serial.print(ax_g, 4); // imprime com 4 casas decimais
  Serial.print("\t");
  Serial.print("AcY: ");
  Serial.print(ay_g, 4);
  Serial.print("\t");
  Serial.print("AcY: ");
  Serial.println(az_g, 4);

  // imprime os valores do giroscópio em graus por segundo
 Serial.print("GyX: ");
 Serial.print(gx);
 Serial.print("\t");
 Serial.print("GyY: ");
 Serial.print(gy);
 Serial.print("\t");
 Serial.print("GyZ: ");
 Serial.println(gz);
 
  delay(100);
}
