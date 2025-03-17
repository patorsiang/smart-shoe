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

- Power Mode:
  - Active Mode (160-260mA) → While adjusting weight.
  - Modem Sleep (3-20mA) → If stable pressure detected for 1 minute, reduce data transmission.
  - Light Sleep (0.8mA) → If stable for 5 minutes, enter low-power mode.
  - Deep Sleep (10μA) → If stable for 30 minutes, disable force sensor until pressure change.

## References

- <https://www.mdpi.com/1424-8220/21/15/5240>
