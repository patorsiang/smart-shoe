# Smart Shoe

this is a project for COMP8380 SPR: Internet of Things and Mobile Devices (2024/2025).

## Features

- Falling Detection with Alert
  - Sensor: MPU sensor
  - Filter: Low-pass filter + Kalman filter (for smoother motion estimation)
  - Network: BLE (low power for local device alert) + Wi-Fi (only for emergency alerts)

- Step Tracking
  - Sensor: Force sensor & MPU sensor
  - Filter: Adaptive threshold + Moving average filter
  - Network: BLE (low power, real-time step tracking on a phone)

- Uneven Weight Balancing
  - Sensor: Force sensor
  - Filter: Median filter + Adaptive threshold
  - Network: BLE (low power, continuous monitoring) + Wi-Fi (only for periodic uploads)

- Power Mode: Light Sleep

## References

- <https://www.mdpi.com/1424-8220/21/15/5240>

## Logbook

- [logbook](Logbook/readme.md)
