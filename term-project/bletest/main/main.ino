
#include <Wire.h>
#include <SoftwareSerial.h>
#include <math.h>

// Address of each MPU-6050 sensor for I2C
#define MPU6050_I2C_ADDRESS1 0x68
#define MPU6050_I2C_ADDRESS2 0x69
                                                
#define FREQ  30.0 // sample freq in Hz

// Bluetooth transmitter(HM-10), used optionally
SoftwareSerial BTSerial(2, 3); // RX | TX

// global angle, gyro derived
double gSensitivity = 65.5; // for 500 deg/s, check data sheet
double gyrXoffs = -281.00, gyrYoffs = 18.00, gyrZoffs = -83.00;

double gx1 = 0, gy1 = 0, gz1 = 0;
double gx2 = 0, gy2 = 0, gz2 = 0;

double gyrX1 = 0, gyrY1 = 0, gyrZ1 = 0;
double gyrX2 = 0, gyrY2 = 0, gyrZ2 = 0;

int16_t accX1 = 0, accY1 = 0, accZ1 = 0;
int16_t accX2 = 0, accY2 = 0, accZ2 = 0;



// Code for initialization
void setup() {
  int error;
  uint8_t c;
  uint8_t sample_div;

  BTSerial.begin(9600);
  Serial.begin(9600);

  // LED for checking status
  pinMode(13, OUTPUT); 

  // Initialize the 'Wire' class for the I2C-bus.
  Wire.begin();

  // PWR_MGMT_1:
  // wake up 
  i2c_write_reg (MPU6050_I2C_ADDRESS1, 0x6b, 0x00);
  i2c_write_reg (MPU6050_I2C_ADDRESS2, 0x6b, 0x00);

  // CONFIG:
  // Low pass filter samples, 1khz sample rate
  i2c_write_reg (MPU6050_I2C_ADDRESS1, 0x1a, 0x01);
  i2c_write_reg (MPU6050_I2C_ADDRESS2, 0x1a, 0x01);

  // GYRO_CONFIG:
  // 500 deg/s, FS_SEL=1
  // This means 65.5 LSBs/deg/s
  i2c_write_reg(MPU6050_I2C_ADDRESS1, 0x1b, 0x08);
  i2c_write_reg(MPU6050_I2C_ADDRESS2, 0x1b, 0x08);

  // CONFIG:
  // set sample rate
  // sample rate FREQ = Gyro sample rate / (sample_div + 1)
  // 1kHz / (div + 1) = FREQ  
  // reg_value = 1khz/FREQ - 1
  sample_div = 1000 / FREQ - 1;
  i2c_write_reg (MPU6050_I2C_ADDRESS1, 0x19, sample_div);
  i2c_write_reg (MPU6050_I2C_ADDRESS2, 0x19, sample_div);

  digitalWrite(13, HIGH);
  calibrate();
  digitalWrite(13, LOW);
}



// Code for business logic
void loop() {
  int error;
  double dT;
  double ax1, ay1, az1;
  double ax2, ay2, az2;

  read_sensor_data();

  // angles based on accelerometer
  ay1 = atan2(accX1, sqrt( pow(accY1, 2) + pow(accZ1, 2))) * 180 / M_PI;
  ax1 = atan2(accY1, sqrt( pow(accX1, 2) + pow(accZ1, 2))) * 180 / M_PI;

  ay2 = atan2(accX2, sqrt( pow(accY2, 2) + pow(accZ2, 2))) * 180 / M_PI;
  ax2 = atan2(accY2, sqrt( pow(accX2, 2) + pow(accZ2, 2))) * 180 / M_PI;

  // angles based on gyro (deg/s)
  gx1 = gx1 + gyrX1 / FREQ;
  gy1 = gy1 - gyrY1 / FREQ;
  gz1 = gz1 + gyrZ1 / FREQ;

  gx2 = gx2 + gyrX2 / FREQ;
  gy2 = gy2 - gyrY2 / FREQ;
  gz2 = gz2 + gyrZ2 / FREQ;

  // complementary filter
  gx1 = gx1 * 0.96 + ax1 * 0.04;
  gy1 = gy1 * 0.96 + ay1 * 0.04;

  gx2 = gx2 * 0.96 + ax2 * 0.04;
  gy2 = gy2 * 0.96 + ay2 * 0.04;

  // Send data through HM-10 (notify:characteristic:FFE1)
  digitalWrite(13, HIGH);
  String rtn = String(round(gx1)) + "/" + String(round(gy1)) + "/" + String(round(gx2)) + "/" + String(round(gy2));
  
  Serial.println(rtn);
  BTSerial.println(rtn);
  
  digitalWrite(13, LOW);

  delay(50);
}



// Set defalut preset
void calibrate(){

  int x;
  long xSum = 0, ySum = 0, zSum = 0;
  uint8_t i2cData[6]; 
  int num = 500;
  uint8_t error1;
  uint8_t error2;

  // Set default value (average of 500 samples)
  for (x = 0; x < num; x++){
    error1 = i2c_read(MPU6050_I2C_ADDRESS1, 0x43, i2cData, 6);
    error2 = i2c_read(MPU6050_I2C_ADDRESS2, 0x43, i2cData, 6);
    if(error1!=0) return;
    if(error2!=0) return;

    xSum += ((i2cData[0] << 8) | i2cData[1]);
    ySum += ((i2cData[2] << 8) | i2cData[3]);
    zSum += ((i2cData[4] << 8) | i2cData[5]);
  }

  gyrXoffs = xSum / num;
  gyrYoffs = ySum / num;
  gyrZoffs = zSum / num;
  
} 



// Get accelerometer, gyro value
void read_sensor_data() {
  uint8_t i2cData1[14];
  uint8_t i2cData2[14];
  uint8_t error1;
  uint8_t error2;

  // read imu data
  error1 = i2c_read(MPU6050_I2C_ADDRESS1, 0x3b, i2cData1, 14);
  if(error1!=0) return;

  error2 = i2c_read(MPU6050_I2C_ADDRESS2, 0x3b, i2cData2, 14);
  if(error2!=0) return;

  // assemble 16 bit sensor data
  //           1        2        3        4        5        6        7       8
  // i2cData = axisX_H, axisX_L, axisY_H, axisY_L, axisZ_H, axisZ_L, temp_H, temp_L, 
  //           gyroX_H, gyroX_L, gyroY_H, gyroY_L, gyroZ_H, gyroZ_L, N/A,    N/A

  accX1 = ((i2cData1[0] << 8) | i2cData1[1]);
  accY1 = ((i2cData1[2] << 8) | i2cData1[3]);
  accZ1 = ((i2cData1[4] << 8) | i2cData1[5]);

  accX2 = ((i2cData2[0] << 8) | i2cData2[1]);
  accY2 = ((i2cData2[2] << 8) | i2cData2[3]);
  accZ2 = ((i2cData2[4] << 8) | i2cData2[5]);

  // (actual - offset) / sensitivity
  gyrX1 = (((i2cData1[8] << 8) | i2cData1[9]) - gyrXoffs) / gSensitivity;
  gyrY1 = (((i2cData1[10] << 8) | i2cData1[11]) - gyrYoffs) / gSensitivity;
  gyrZ1 = (((i2cData1[12] << 8) | i2cData1[13]) - gyrZoffs) / gSensitivity;

  gyrX2 = (((i2cData2[8] << 8) | i2cData2[9]) - gyrXoffs) / gSensitivity;
  gyrY2 = (((i2cData2[10] << 8) | i2cData2[11]) - gyrYoffs) / gSensitivity;
  gyrZ2 = (((i2cData2[12] << 8) | i2cData2[13]) - gyrZoffs) / gSensitivity;
}



// Get data from sensor through I2C Communication
int i2c_read(int addr, int start, uint8_t *buffer, int size) {
  int i, n, error;

  Wire.beginTransmission(addr);
  n = Wire.write(start);
  if (n != 1) return (-10);

  n = Wire.endTransmission(false); // hold the I2C-bus
  if (n != 0) return (n);

  // Third parameter is true: relase I2C-bus after data is read.
  Wire.requestFrom(addr, size, true);
  i = 0;
  while(Wire.available() && i<size) {
    buffer[i++]=Wire.read();
  }

  if ( i != size) return (-11);

  return (0);  // return : no error
}



// Write data from sensor through I2C Communication
int i2c_write(int addr, int start, const uint8_t *pData, int size) {
  int n, error;

  Wire.beginTransmission(addr);
  n = Wire.write(start); // write the start address
  if (n != 1)
  return (-20);

  n = Wire.write(pData, size); // write data bytes
  if (n != size)
  return (-21);

  error = Wire.endTransmission(true); // release the I2C-bus
  if (error != 0)
  return (error);

  return (0); // return : no error
}

// Write register from sensor through I2C Communication
int i2c_write_reg(int addr, int reg, uint8_t data) {
  int error;
  error = i2c_write(addr, reg, &data, 1);
  return (error);
}
