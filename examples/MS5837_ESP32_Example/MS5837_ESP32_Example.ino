/* Blue Robotics MS5837 Library ESP32 Example
-----------------------------------------------------

Title: Blue Robotics MS5837 Library ESP32 Example

Description: This example demonstrates the MS5837 Library with a connected
sensor using an ESP32 microcontroller. The example reads the sensor and prints 
the resulting values to the serial terminal.

The code is designed for ESP32 boards and can be compiled and uploaded via 
the Arduino IDE or PlatformIO.

ESP32 I2C Default Pins:
- SDA: GPIO 21
- SCL: GPIO 22

You can also use custom I2C pins by calling Wire.begin(SDA_PIN, SCL_PIN);

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

  Serial.begin(115200);
  
  // Wait for serial connection (useful for ESP32 USB CDC)
  delay(1000);

  Serial.println("Starting MS5837 on ESP32");

  // Initialize I2C on default ESP32 pins (SDA=GPIO21, SCL=GPIO22)
  Wire.begin();
  
  // Alternatively, you can specify custom I2C pins:
  // Wire.begin(SDA_PIN, SCL_PIN);
  // For example: Wire.begin(21, 22);

  // Initialize pressure sensor
  // Returns true if initialization was successful
  // We can't continue with the rest of the program unless we can initialize the sensor
  while (!sensor.init()) {
    Serial.println("Init failed!");
    Serial.println("Are SDA/SCL connected correctly?");
    Serial.println("Blue Robotics Bar30: White=SDA, Green=SCL");
    Serial.println("ESP32 Default I2C: SDA=GPIO21, SCL=GPIO22");
    Serial.println("\n\n\n");
    delay(5000);
  }

  Serial.println("MS5837 sensor initialized successfully!");
  
  // Report the detected sensor model
  uint8_t model = sensor.getModel();
  if (model == MS5837::MS5837_30BA) {
    Serial.println("Sensor model: MS5837-30BA");
  } else if (model == MS5837::MS5837_02BA) {
    Serial.println("Sensor model: MS5837-02BA");
  } else {
    Serial.println("Sensor model: Unrecognised");
  }

  // .init sets the sensor model for us but we can override it if required.
  // Uncomment the next line to force the sensor model to the MS5837_30BA.
  //sensor.setModel(MS5837::MS5837_30BA);

  sensor.setFluidDensity(997); // kg/m^3 (freshwater, 1029 for seawater)
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

  delay(1000);
}
