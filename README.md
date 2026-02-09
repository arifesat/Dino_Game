# Dino Game for ESP32

A simple dino runner game developed for the ESP32 microcontroller using an SSD1306 OLED display.

## Hardware Requirements

- **Microcontroller**: ESP32
- **Display**: SSD1306 OLED (128x64)
- **Input**:
  - Button 1: Jump (Pin 4)
  - Button 2: Crouch (Pin 16)

## Features

- **Controls**: Dedicated buttons for jumping and crouching.
- **Animations**: Animated dino walking/crouching steps and bird wing flapping.
- **Obstacles**:
  - Cactus: Standard ground obstacle.
  - Bird: Flying obstacle (requires crouching). Starts appearing after score 10.
- **Difficulty**: Speed increases every 10 points after reaching score 20.

## Setup

### PlatformIO
This project is structured for PlatformIO. Clone the repository and upload to your ESP32.

### Arduino IDE
If using the Arduino IDE, simply copy the contents of `src/main.cpp` into a new sketch. Ensure you have the necessary libraries installed:
- Adafruit GFX Library
- Adafruit SSD1306

Arduino version has lower framerate due to the device limitations. If you can manage to make it run faster, please open a PR.

## Tools Used

- **Assets**: 1-bit Image Canvas (https://arifesat.github.io/1bit-Image-Canvas/) to create and edit images.