# Smart Shoe

this is a project for COMP8380 SPR: Internet of Things and Mobile Devices (2024/2025).

## Features

- Falling Detection with Alert
  - Sensor: MPU sensor
  - Filter: Low-pass filter + Kalman filter (for smoother motion estimation)
  - Network: BLE (low power for local device alert) + Wi-Fi (only for emergency alerts)
  - Power Mode:
    - Active Mode (160-260mA) → When significant motion is detected.
    - Modem Sleep (3-20mA) → If no movement for 30 seconds, turn off communication but wake up periodically.
    - Light Sleep (0.8mA) → If idle for 5 minutes, all peripherals off, CPU memory retained.
    - Deep Sleep (10μA) → If unused for 30 minutes, enters full sleep, wakes only on major impact.

- Step Tracking
  - Sensor: Force sensor & MPU sensor
  - Filter: Adaptive threshold + Moving average filter
  - Network: BLE (low power, real-time step tracking on a phone)
  - Power Mode:
    - Active Mode (160-260mA) → When movement is detected.
    - Modem Sleep (3-20mA) → If no step detected for 10 seconds, reduce sensor polling.
    - Light Sleep (0.8mA) → If inactive for 1 minute, reduce updates to once per second.
    - Deep Sleep (10μA) → If inactive for 1 hour, shuts down, waking only on pressure change.

- Uneven Weight Balancing
  - Sensor: Force sensor
  - Filter: Median filter
  - Network: BLE (low power, continuous monitoring) + Wi-Fi (only for periodic uploads)
  - Power Mode:
    - Active Mode (160-260mA) → While adjusting weight.
    - Modem Sleep (3-20mA) → If stable pressure detected for 1 minute, reduce data transmission.
    - Light Sleep (0.8mA) → If stable for 5 minutes, enter low-power mode.
    - Deep Sleep (10μA) → If stable for 30 minutes, disable force sensor until pressure change.

## References

- <https://www.mdpi.com/1424-8220/21/15/5240>
