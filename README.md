# Smart Shoe

An IoT smart shoe prototype built for COMP8380: Internet of Things and Mobile Devices (2024/2025) at the University of Kent.

The project explores how a shoe or insole can collect motion and pressure data, process it on an ESP32-based device, and display useful signals in a web/mobile dashboard. The prototype focuses on fall detection, step tracking, uneven weight balance detection, battery monitoring, and low-power operation.

## Overview

Smart Shoe combines embedded firmware, sensors, Bluetooth Low Energy, MQTT, and a browser-based dashboard.

The firmware runs on an ESP32 board, reads force and motion sensors, applies simple filtering and threshold-based detection, sends real-time data over BLE, and uploads selected readings/events over Wi-Fi using MQTT. The companion web app connects to the device, visualizes sensor readings, and shows user-facing status such as step count, battery level, alerts, and force distribution.

This is a working academic prototype, not a production medical or safety device.

## Why I Built This

I built this project to explore a practical IoT/mobile use case where embedded sensing, wireless communication, and a user interface need to work together.

The initial idea was to investigate whether a shoe-mounted prototype could help monitor:

- movement patterns,
- step activity,
- pressure distribution,
- possible imbalance,
- possible fall events,
- and device power status.

The project also gave me a chance to practice working with real sensor noise, hardware constraints, BLE communication, MQTT messaging, and a frontend dashboard for live device data.

## Features

- **Fall detection**
  - Uses acceleration and rotation magnitude from the MPU sensor.
  - Publishes a warning event when threshold conditions are met.

- **Step tracking**
  - Uses force sensor readings and acceleration changes.
  - Applies threshold and debounce logic to avoid counting every noisy reading as a step.

- **Uneven weight balance detection**
  - Compares front, middle, and heel pressure distribution.
  - Raises an imbalance warning after repeated out-of-range readings.

- **Force sensor visualization**
  - Sends force readings for three pressure points.
  - Displays a foot heatmap-style view in the web app.

- **Battery monitoring**
  - Reads and sends battery level/status from the device firmware.

- **BLE dashboard connection**
  - Provides BLE characteristics for force, step count, fall event, battery, gyroscope, temperature, acceleration, and commands.

- **MQTT data upload**
  - Uploads selected readings/events to MQTT topics through Wi-Fi.

- **Power mode experimentation**
  - Includes light sleep behavior when no pressure is detected for a period of time.

## Hardware Components

Confirmed from the code and logbook:

- ESP32-based development board
  - Logbook notes that the prototype moved to an Adafruit ESP32 Feather after an initial board setup issue.
- MPU6050 motion sensor
  - Used for accelerometer, gyroscope, and temperature readings.
- 3 force sensors
  - Mapped to front, middle, and heel pressure points.
- Resistors for force sensor wiring
  - The logbook notes that the force sensors needed resistor adaptation.
- Shoe/insole prototype mounting
  - Used to test sensor placement and gait-related readings.

TODO:

- Add exact ESP32 board model used in the final submission.
- Add exact force sensor model/specification.
- Add wiring diagram.
- Add battery/power module details.
- Add photos of the final hardware build.

## Software Architecture

```text
Smart Shoe Prototype

ESP32 firmware (IoT/)
  - Reads force sensors and MPU6050 motion data
  - Filters and interprets readings
  - Detects steps, possible falls, and imbalance
  - Exposes BLE characteristics for live dashboard data
  - Publishes selected data/events to MQTT over Wi-Fi
  - Experiments with light sleep for power saving

Web/mobile dashboard (my-app/)
  - Next.js app with Material UI
  - Connects to the shoe over Web Bluetooth
  - Subscribes to MQTT topics where needed
  - Displays battery, alerts, step count, force distribution, and MPU readings
```

Important firmware modules:

- `IoT/IoT.ino` - main setup and loop
- `IoT/ble_manager.*` - BLE service, characteristics, and command handling
- `IoT/wifi_manager.*` - Wi-Fi and MQTT publishing
- `IoT/force.*` - force sensor setup, median filtering, pressure readings, sleep trigger
- `IoT/mpu.*` - MPU6050 setup, calibration, acceleration, gyroscope, and temperature readings
- `IoT/detectStep.*` - step detection logic
- `IoT/detectFalling.*` - possible fall detection logic
- `IoT/detectPostureImbalance.*` - uneven balance detection logic
- `IoT/battery.*` - battery monitoring

Important dashboard modules:

- `my-app/src/app/page.tsx` - main dashboard page
- `my-app/src/components/BLEConnectButton.tsx` - BLE connection UI
- `my-app/src/components/FootHeatMap.tsx` - force distribution display
- `my-app/src/components/CountStep.tsx` - step count display
- `my-app/src/components/MPUPaper.tsx` - motion data display
- `my-app/src/components/Battery.tsx` - battery display
- `my-app/src/components/AlertMessage.tsx` - alert display
- `my-app/src/utils/hooks/mqttHook.tsx` - MQTT websocket subscription helper

## Tech Stack

Firmware:

- Arduino/C++
- ESP32
- BLE via NimBLE
- Wi-Fi
- MQTT
- Arduino_JSON
- Adafruit MPU6050 sensor library

Dashboard:

- Next.js 15
- React 19
- TypeScript
- Material UI
- MQTT.js
- Web Bluetooth API
- Three.js

## Data Flow

```text
Force sensors + MPU6050
        |
        v
ESP32 firmware reads raw values
        |
        v
Filtering / thresholds / calibration
        |
        +--> BLE notifications for local live dashboard data
        |
        +--> Wi-Fi + MQTT publish for selected readings and events
        |
        v
Next.js dashboard
        |
        v
Battery, alerts, steps, force distribution, and motion readings
```

Example data categories:

- Force readings from three pressure points
- Step count
- Acceleration
- Gyroscope
- Temperature
- Battery level
- Possible fall warnings
- Uneven balance warnings
- Device info/status messages

## Setup / How to Run

### Firmware

TODO: Add exact Arduino IDE / PlatformIO setup steps.

Known project entry point:

```text
IoT/IoT.ino
```

Before flashing:

1. Install the required ESP32 board support.
2. Install the required Arduino libraries for ESP32, BLE, MQTT, JSON, and MPU6050.
3. Review configuration in `IoT/global_params.h`.
4. Replace local Wi-Fi settings with your own environment-specific configuration.
5. Connect the ESP32 board and upload the sketch.

Security note:

- Do not commit real Wi-Fi credentials or private broker credentials.
- Move secrets into local-only config before using this project beyond coursework/prototyping.

### Dashboard

The dashboard is in `my-app/`.

Install dependencies:

```bash
cd my-app
npm install
```

Run the development server:

```bash
npm run dev
```

Open:

```text
http://localhost:3000
```

Notes:

- Web Bluetooth support depends on browser and device support.
- Use a browser that supports the Web Bluetooth API.
- BLE usually requires a secure context. `localhost` is normally allowed for local development.
- MQTT websocket data currently points to a public test broker in the app code.

## Demo or Screenshots

TODO: Add final screenshots or demo GIFs here.

Available project artifacts:

- `Final_IoT_Presentation.pdf`
- `Logbook/readme.md`
- `Logbook/snapshots/`

Suggested screenshots to add:

- Hardware prototype mounted on the shoe
- BLE connection state
- Force heatmap view
- Step counter view
- Fall or imbalance alert state
- MPU readings panel

## What I Learned

- Sensor placement matters. Force sensor readings are affected by where and how pressure is applied.
- Hardware setup details can block progress quickly, especially board selection and sensor wiring.
- Force sensors can be noisy and need filtering, thresholds, and calibration.
- Step counting from a small number of pressure sensors is harder than it first appears.
- BLE is useful for low-power local device communication, but it requires careful characteristic design.
- Combining BLE and Wi-Fi/MQTT introduces memory, timing, and power tradeoffs on ESP32-class hardware.
- Keeping firmware logic modular makes debugging easier than putting every feature into one sketch file.
- A familiar web stack can be a practical way to build a fast prototype dashboard.

## Limitations

- This is an academic prototype, not a validated health, safety, or medical device.
- Fall detection is threshold-based and can produce false positives or false negatives.
- Step tracking is simple and depends on sensor placement, pressure thresholds, and walking style.
- Uneven balance detection uses approximate pressure distribution rules.
- Sensor calibration is still basic.
- MQTT uses a public test broker in the current code.
- Firmware configuration needs cleanup before broader reuse.
- Hardware wiring and exact bill of materials are not fully documented yet.
- The dashboard depends on browser support for Web Bluetooth.

## Future Improvements

- Move Wi-Fi and broker configuration out of committed source files.
- Add a full wiring diagram and bill of materials.
- Add calibration UI and persistent calibration settings.
- Improve fall detection with more robust signal processing or a trained model.
- Improve step counting with better sensor placement and validation tests.
- Add local data logging for offline testing.
- Add charts for historical force and motion data.
- Add clearer error states for BLE and MQTT connection failures.
- Add automated tests or simulation utilities for detection logic.
- Add demo screenshots, videos, and a concise project case study.

## Status

Status: coursework prototype / portfolio polish in progress.

The repository contains firmware, a dashboard app, a logbook, and final presentation material. The next README/documentation tasks are to add exact hardware details, wiring diagrams, screenshots, and a short demo walkthrough.

## References

- <https://www.mdpi.com/1424-8220/21/15/5240>
- [Project logbook](Logbook/readme.md)
