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

    | Feature | Trigger | Power Usage | Wake-Up Method |
    | - | - | - | - |
    | Active Mode | Walking, force applied | 160-260mA | Always on |
    | Modem Sleep | No movement for 5 min | 3-20mA | Any movement |
    | Light Sleep | No movement for 30 min | 0.8mA | Any movement |
    | Deep Sleep | (1hr inactivity) No movement for 1 hour | 10μA | Force sensor press |
    | Midnight Deep Sleep | Reset Every 12 AM | 10μA | Force sensor press |
    | Charging Deep Sleep | Device plugged in | 10μA | Wakes when unplugged |
    | Step Count Storage | Before Deep Sleep | 10μA | RTC Memory |

## References

- <https://www.mdpi.com/1424-8220/21/15/5240>
