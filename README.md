# Proximity Alert System

An ESP32-based proximity alert system that uses an ultrasonic sensor to trigger visual and audible warnings via a 4-channel relay module.

## Features

- **Multi-Zone Detection**: Four distinct distance zones (70cm, 50cm, 30cm, 20cm) for graduated alerts.
- **Visual Indicators**: Three relays dedicated to Green, Yellow, and Red LEDs to show proximity levels.
- **Audible Alert**: A fourth relay triggers a buzzer for the closest proximity zone.
- **ESP32 Powered**: Designed for the ESP32 WROOM development board.
- **Active-Low Relay Support**: Configured for standard active-low relay modules.

## Hardware Requirements

- **Microcontroller**: ESP32 WROOM
- **Sensor**: HC-SR04 Ultrasonic Sensor
- **Actuators**: 4-Channel Relay Module
- **Indicators**: Green, Yellow, and Red LEDs + Buzzer

## Pin Configuration

| Component | ESP32 Pin |
|-----------|-----------|
| TRIG      | D5        |
| ECHO      | D18       |
| Relay 1 (Green) | D19 |
| Relay 2 (Yellow) | D21 |
| Relay 3 (Red) | D22 |
| Relay 4 (Buzzer) | D23 |

## Usage

1. Connect the hardware according to the pin configuration.
2. Open `prox-sense.ino` in the Arduino IDE.
3. Select your ESP32 board and the correct COM port.
4. Upload the sketch.
5. Monitor the proximity alerts via the LEDs/Buzzer and the Serial Monitor (115200 baud).

## License

This project is licensed under the MIT License - see the LICENSE file for details.
