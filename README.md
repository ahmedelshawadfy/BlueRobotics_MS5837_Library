# BlueRobotics MS5837 Library ![Test](https://github.com/bluerobotics/BlueRobotics_MS5837_Library/workflows/Test/badge.svg)

Arduino library for the MS5837 pressure sensor. The MS5837 is a tiny SMT pressures sensor from Measurement Specialties that can measure pressure of up to 30 Bar (300m depth) with resolution of 0.2 mbar.

This library also supports the MS5837-02BA which has a much smaller measurement range and is better suited for altitude measurement in air.

## Platform Compatibility

This library is compatible with a wide range of Arduino-compatible platforms, including:

- **Arduino boards**: Uno, Mega, Nano, etc.
- **Raspberry Pi Pico W/W2**: Fully compatible using the [arduino-pico core](https://github.com/earlephilhower/arduino-pico)
- **ESP32/ESP8266**: Compatible with all variants
- **STM32**: Compatible with STM32duino
- **Any platform with Arduino Wire library support**

### Raspberry Pi Pico W/W2 Setup

The library works seamlessly with Raspberry Pi Pico W and Pico W2. To use it:

1. **Install Board Support**: Add the arduino-pico core to your Arduino IDE
   - Add `https://github.com/earlephilhower/arduino-pico/releases/download/global/package_rp2040_index.json` to Board Manager URLs
   - Install "Raspberry Pi Pico/RP2040" from Board Manager

2. **Wiring**: Connect the MS5837 sensor to Pico's I2C pins:
   - SDA → GP4 (default I2C0) or GP2 (I2C1)
   - SCL → GP5 (default I2C0) or GP3 (I2C1)
   - VCC → 3.3V
   - GND → GND

3. **Example**: See `examples/MS5837_Pico_Example` for a complete Pico-specific example with detailed setup instructions.

# Documentation

Please see the examples for normal operation. Below are the available functions used in the library.

**Examples:**
- `MS5837_Example` - Basic example for Arduino boards
- `MS5837_Pico_Example` - Raspberry Pi Pico W/W2 specific example with detailed setup

## API Reference

``` cpp
MS5837();

/** Must be called before attempting to operate the sensor.
 * Returns true if the sensor was initialized successfully.
 * wirePort is optional and defaults to Wire.
 * You can select a different port by calling (e.g.) init(Wire1)
 */
bool init(TwoWire &wirePort);

/** Calls init.
 * Returns true if the sensor was initialized successfully.
 */
bool begin(TwoWire &wirePort);

/** Set model of MS5837 sensor. Valid options are MS5837::MS5837_30BA (default)
 * and MS5837::MS5837_02BA.
 */
void setModel(uint8_t model);

/** Provide the density of the working fluid in kg/m^3. Default is for
 * seawater. Should be 997 for freshwater.
 */
void setFluidDensity(float density);

/** The read from I2C takes up for 40 ms, so use sparingly if possible.
 */
void read();

/** Pressure returned in mbar or mbar*conversion rate.
 */
float pressure(float conversion = 1.0f);

/** Temperature returned in deg C.
 */
float temperature();

/** Depth returned in meters (valid for operation in incompressible
 *  liquids only. Uses density that is set for fresh or seawater.
 */
float depth();

/** Altitude returned in meters (valid for operation in air only).
 */
float altitude();

```

# Versions

1.0.0 - First release, included in Arduino Library Manager

# Reference

You can find the [MS5837-30BA datasheet here](http://www.mouser.com/ds/2/418/MS5837-30BA-736494.pdf).
