# Proximity Alert System

An ESP32-based proximity alert system that uses an ultrasonic sensor to trigger visual and audible warnings via a 4-channel relay module, with a round TFT display showing a coloured eye whose iris matches the active LED zone.

## Features

- **Multi-Zone Detection**: Four distance zones (50cm, 40cm, 30cm, 20cm) for graduated alerts.
- **Visual Indicators**: Three relays dedicated to Green, Yellow, and Red LEDs to show proximity levels.
- **Audible Alert**: A fourth relay triggers a buzzer at the closest proximity zone.
- **Chase Pattern at Closest Zone**: When the closest zone is breached, the three LED relays cycle in a chase pattern (green → yellow → red, ~50ms each) while the buzzer stays solidly on.
- **Animated Eye Display**: GC9A01 1.28" round TFT shows an eye whose iris colour tracks the active zone — blue (calm), green, yellow, red, then flashing red on the closest zone.
- **ESP32 Powered**: Designed for the ESP32 WROOM development board.
- **Active-Low Relay Support**: Configured for standard active-low relay modules.

## Hardware Requirements

- **Microcontroller**: ESP32 WROOM
- **Sensor**: HC-SR04 Ultrasonic Sensor (with voltage divider on the ECHO line for 3.3V safety)
- **Actuators**: 4-Channel Relay Module
- **Indicators**: Green, Yellow, and Red LEDs + Buzzer
- **Display**: GC9A01 1.28" 240×240 round TFT (SPI)

## Pin Configuration

| Component        | ESP32 Pin |
|------------------|-----------|
| TRIG             | D5        |
| ECHO             | D18       |
| Relay 1 (Green)  | D19       |
| Relay 2 (Yellow) | D21       |
| Relay 3 (Red)    | D22       |
| Relay 4 (Buzzer) | D23       |
| Display SDA (MOSI) | D13     |
| Display SCL (SCLK) | D14     |
| Display CS       | D15       |
| Display DC       | D2        |
| Display RST      | D4        |
| Display VCC      | 3.3V      |
| Display GND      | GND       |

## Display Setup (TFT_eSPI)

The display uses the [TFT_eSPI](https://github.com/Bodmer/TFT_eSPI) library, which is configured via a `User_Setup.h` file inside the library folder rather than per-sketch.

1. Install **TFT_eSPI** from the Arduino Library Manager.
2. Open `User_Setup.h` inside the library folder (typically `~/Arduino/libraries/TFT_eSPI/User_Setup.h`) and set:

   ```cpp
   #define GC9A01_DRIVER
   #define TFT_MOSI 13
   #define TFT_SCLK 14
   #define TFT_CS   15
   #define TFT_DC    2
   #define TFT_RST   4
   #define SPI_FREQUENCY 27000000
   #define USE_HSPI_PORT
   ```

   `USE_HSPI_PORT` is required because GPIO 13/14 are HSPI pins on the ESP32 — without it the library defaults to VSPI and the panel stays dark.

3. If you've previously compiled the sketch, delete the cached library copy so the IDE picks up the edited `User_Setup.h`:

   ```bash
   rm -rf ~/.cache/arduino/sketches/*/libraries/TFT_eSPI
   ```

## Usage

1. Connect the hardware according to the pin configuration.
2. Configure `User_Setup.h` as above.
3. Open `prox-sense.ino` in the Arduino IDE.
4. Select your ESP32 board and the correct COM port.
5. Upload the sketch.
6. Monitor the proximity alerts via the LEDs/Buzzer/Display and the Serial Monitor (115200 baud).

## License

This project is licensed under the MIT License - see the LICENSE file for details.
