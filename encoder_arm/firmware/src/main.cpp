#include <Wire.h>

#define AS5600_ADDR 0x36
#define RAW_ANGLE_REGISTER 0x0C

// --- Function to read 12-bit raw angle via I2C ---
uint16_t readRawAngle() {
  // Step 1: Request register address 0x0C from AS5600
  Wire.beginTransmission(AS5600_ADDR);
  Wire.write(RAW_ANGLE_REGISTER);
  Wire.endTransmission(false); // Send repeated start condition

  // Step 2: Request 2 bytes of data (High byte & Low byte)
  Wire.requestFrom((uint8_t)AS5600_ADDR, (uint8_t)2);

  if (Wire.available() == 2) {
    uint8_t highByte = Wire.read(); // Read upper 8 bits (Reg 0x0C)
    uint8_t lowByte = Wire.read();  // Read lower 8 bits (Reg 0x0D)

    // Step 3: Combine two 8-bit values into a single 16-bit integer
    return ((uint16_t)highByte << 8) | lowByte;
  }
  return 0; // Return 0 on communication failure
}

// --- Hardware Initialization ---
void setup() {
  Serial.begin(115200);
  Wire.begin(); // Default I2C pins for XIAO RP2040 (SDA=P6, SCL=P7)
}

// --- Main Execution Loop ---
void loop() {
  // Get raw value (0 - 4095)
  uint16_t raw = readRawAngle();

  // Convert raw 12-bit value to angle in degrees (0.0 - 360.0 deg)
  float degrees = raw * (360.0 / 4096.0);

  // Print results to Serial Monitor
  Serial.print("RAW: ");
  Serial.print(raw);
  Serial.print(" | Angle: ");
  Serial.print(degrees, 2);
  Serial.println(" deg");

  delay(50);
}