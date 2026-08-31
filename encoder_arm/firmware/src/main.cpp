#include <Arduino.h>
#include <Wire.h>

// AS5600 Constants
const uint8_t AS5600_ADDR = 0x36;
const uint8_t REG_RAW_ANGLE = 0x0C;
const uint8_t REG_STATUS = 0x0B;

// Pin definitions (passed from platformio.ini or defined fallback)
#ifndef SDA0_PIN
#define SDA0_PIN 6 // XIAO D4 (GPIO6)
#define SCL0_PIN 7 // XIAO D5 (GPIO7)
#endif

#ifndef SDA1_PIN
#define SDA1_PIN 26 // XIAO D0 (GPIO26)
#define SCL1_PIN 27 // XIAO D1 (GPIO27)
#endif

// Scan an I2C bus for device presence at target address
bool pingI2CDevice(TwoWire &bus, uint8_t addr) {
  bus.beginTransmission(addr);
  return (bus.endTransmission() == 0);
}

// Read raw 12-bit angle (0 - 4095) from AS5600
uint16_t readRawAngle(TwoWire &bus) {
  bus.beginTransmission(AS5600_ADDR);
  bus.write(REG_RAW_ANGLE);
  if (bus.endTransmission() != 0)
    return 0xFFFF; // Error

  bus.requestFrom(AS5600_ADDR, (uint8_t)2);
  if (bus.available() >= 2) {
    uint16_t high = bus.read();
    uint16_t low = bus.read();
    return ((high & 0x0F) << 8) | low;
  }
  return 0xFFFF;
}

// Read status register to verify magnet detection
uint8_t readStatus(TwoWire &bus) {
  bus.beginTransmission(AS5600_ADDR);
  bus.write(REG_STATUS);
  if (bus.endTransmission() != 0)
    return 0x00;

  bus.requestFrom(AS5600_ADDR, (uint8_t)1);
  if (bus.available() >= 1) {
    return bus.read();
  }
  return 0x00;
}

void setup() {
  Serial.begin(115200);
  delay(2000); // Wait for USB Serial connection

  Serial.println("\n==========================================");
  Serial.println("   CoDraw Encoder Arm - Dual I2C Test     ");
  Serial.println("==========================================");

  // Initialize I2C Bus 0 (Joint 1)
  Wire.setSDA(SDA0_PIN);
  Wire.setSCL(SCL0_PIN);
  Wire.begin();
  Wire.setClock(400000); // 400kHz Fast Mode

  // Initialize I2C Bus 1 (Joint 2)
  Wire1.setSDA(SDA1_PIN);
  Wire1.setSCL(SCL1_PIN);
  Wire1.begin();
  Wire1.setClock(400000); // 400kHz Fast Mode

  // Verify I2C Bus 0
  Serial.print("[Bus 0 / Joint 1] Pins SDA: D4 (GPIO6), SCL: D5 (GPIO7) --> ");
  if (pingI2CDevice(Wire, AS5600_ADDR)) {
    Serial.println("SUCCESS (AS5600 detected at 0x36)");
  } else {
    Serial.println("FAILED (No ACK at 0x36 - Check wiring/power)");
  }

  // Verify I2C Bus 1
  Serial.print(
      "[Bus 1 / Joint 2] Pins SDA: D0 (GPIO26), SCL: D1 (GPIO27) --> ");
  if (pingI2CDevice(Wire1, AS5600_ADDR)) {
    Serial.println("SUCCESS (AS5600 detected at 0x36)");
  } else {
    Serial.println("FAILED (No ACK at 0x36 - Check wiring/power)");
  }

  Serial.println("------------------------------------------");
}

void loop() {
  // Read Joint 1
  uint16_t raw1 = readRawAngle(Wire);
  uint8_t stat1 = readStatus(Wire);
  bool mag1_ok = (stat1 & 0x20); // Bit 5 = MD (Magnet Detected)

  // Read Joint 2
  uint16_t raw2 = readRawAngle(Wire1);
  uint8_t stat2 = readStatus(Wire1);
  bool mag2_ok = (stat2 & 0x20); // Bit 5 = MD (Magnet Detected)

  // Display Joint 1
  Serial.print("J1 (0x36): ");
  if (raw1 != 0xFFFF) {
    float deg1 = (raw1 * 360.0) / 4096.0;
    Serial.print(deg1, 2);
    Serial.print(" deg [Raw: ");
    Serial.print(raw1);
    Serial.print("] ");
    Serial.print(mag1_ok ? "(Mag: OK) " : "(Mag: MISSING/WEAK) ");
  } else {
    Serial.print("ERR ");
  }

  Serial.print(" | ");

  // Display Joint 2
  Serial.print("J2 (0x36): ");
  if (raw2 != 0xFFFF) {
    float deg2 = (raw2 * 360.0) / 4096.0;
    Serial.print(deg2, 2);
    Serial.print(" deg [Raw: ");
    Serial.print(raw2);
    Serial.print("] ");
    Serial.println(mag2_ok ? "(Mag: OK)" : "(Mag: MISSING/WEAK)");
  } else {
    Serial.println("ERR");
  }

  delay(50); // 20 Hz output rate
}