/* Blue Robotics MS5837 Library Example for Raspberry Pi Pico W/W2
-----------------------------------------------------

Title: Blue Robotics MS5837 Library Example for Raspberry Pi Pico W/W2

Description: This example demonstrates the MS5837 Library with a connected
sensor on Raspberry Pi Pico W/W2. The example reads the sensor and prints 
the resulting values to the serial terminal.

Hardware Setup:
- Raspberry Pi Pico W or Pico W2
- MS5837 sensor connected via I2C
- Default I2C pins: GP4 (SDA), GP5 (SCL)
- Alternative I2C pins can be used with Wire1: GP2 (SDA), GP3 (SCL)

Wiring:
- MS5837 SDA -> Pico GP4 (or GP2 for Wire1)
- MS5837 SCL -> Pico GP5 (or GP3 for Wire1)
- MS5837 VCC -> Pico 3.3V
- MS5837 GND -> Pico GND

Installation:
1. Install the Raspberry Pi Pico/RP2040 board support in Arduino IDE:
   - File -> Preferences -> Additional Board Manager URLs
   - Add: https://github.com/earlephilhower/arduino-pico/releases/download/global/package_rp2040_index.json
   - Tools -> Board -> Board Manager -> Search for "pico" -> Install "Raspberry Pi Pico/RP2040"

2. Install the MS5837 library:
   - Sketch -> Include Library -> Manage Libraries
   - Search for "MS5837" -> Install "BlueRobotics MS5837 Library"

3. Select your board:
   - Tools -> Board -> Raspberry Pi RP2040 Boards -> Raspberry Pi Pico W

Usage:
- Upload this sketch to your Raspberry Pi Pico W/W2
- Open Serial Monitor at 115200 baud
- The sensor readings will be displayed every second

-------------------------------
The MIT License (MIT)

Copyright (c) 2015 Blue Robotics Inc.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
-------------------------------*/

#include <Wire.h>
#include "MS5837.h"

MS5837 sensor;

void setup() {
  // Initialize Serial at higher baud rate (Pico supports higher speeds)
  Serial.begin(115200);
  
  // Wait for serial connection (useful for debugging)
  while (!Serial && millis() < 5000) {
    delay(100);
  }

  Serial.println("Starting MS5837 on Raspberry Pi Pico W/W2");
  Serial.println("========================================");

  // Initialize I2C
  // Default I2C pins on Pico: SDA=GP4, SCL=GP5
  Wire.begin();
  
  // Alternative: Use I2C1 with different pins
  // Wire1.setSDA(2);  // GP2
  // Wire1.setSCL(3);  // GP3
  // Wire1.begin();

  // Initialize pressure sensor
  // Returns true if initialization was successful
  // We can't continue with the rest of the program unless we can initialize the sensor
  Serial.println("Initializing MS5837 sensor...");
  
  while (!sensor.init()) {
    Serial.println("Init failed!");
    Serial.println("Are SDA/SCL connected correctly?");
    Serial.println("Blue Robotics Bar30: White=SDA, Green=SCL");
    Serial.println("Pico Default I2C0: GP4=SDA, GP5=SCL");
    Serial.println("\n\n\n");
    delay(5000);
  }

  Serial.println("MS5837 sensor initialized successfully!");
  
  // Print detected sensor model
  // getModel() returns the sensor type that was auto-detected during init() based on
  // the sensor's calibration data. This can be MS5837_30BA, MS5837_02BA, or MS5837_UNRECOGNISED
  uint8_t model = sensor.getModel();
  Serial.print("Detected sensor model: ");
  if (model == MS5837::MS5837_30BA) {
    Serial.println("MS5837-30BA (30 Bar / 300m depth)");
  } else if (model == MS5837::MS5837_02BA) {
    Serial.println("MS5837-02BA (2 Bar / altitude)");
  } else {
    Serial.println("Unknown/Unrecognized");
  }

  // .init sets the sensor model for us but we can override it if required.
  // Uncomment the next line to force the sensor model to the MS5837_30BA.
  // sensor.setModel(MS5837::MS5837_30BA);

  // Set fluid density
  sensor.setFluidDensity(997); // kg/m^3 (freshwater, 1029 for seawater)
  
  Serial.println("Starting measurements...");
  Serial.println("========================================\n");
}

void loop() {
  // Update pressure and temperature readings
  sensor.read();

  Serial.print("Pressure: ");
  Serial.print(sensor.pressure());
  Serial.println(" mbar");

  Serial.print("Temperature: ");
  Serial.print(sensor.temperature());
  Serial.println(" deg C");

  Serial.print("Depth: ");
  Serial.print(sensor.depth());
  Serial.println(" m");

  Serial.print("Altitude: ");
  Serial.print(sensor.altitude());
  Serial.println(" m above mean sea level");
  
  Serial.println("----------------------------------------");

  delay(1000);
}
