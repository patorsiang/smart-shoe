# Logbook

Written by Napatchol Thaipanich (nt375)

---

## 2025-01-21

**Note:**

- Listed an idea
  - Overview
  - Values for user
  - Mapping feature with sensor and where to place sensors

**Result:**

- Got three ideas
  - Smart Sport Shoe Insoles
  - Smart folding shopping trolley
  - Smart Laundry Basket

**/Logbook/snapshots:**

| ![1](/Logbook/snapshots/2025-01-21/1.png) | ![2](/Logbook/snapshots/2025-01-21/2.png) | ![3](/Logbook/snapshots/2025-01-21/3.png) | ![4](/Logbook/snapshots/2025-01-21/4.png) |
|-----------------------|-----------------------|-----------------------|-----------------------|
| ![5](/Logbook/snapshots/2025-01-21/5.png) | ![6](/Logbook/snapshots/2025-01-21/6.png) | ![7](/Logbook/snapshots/2025-01-21/7.png) | ![8](/Logbook/snapshots/2025-01-21/8.png) |

## 2025-01-27

**Note:**

- Show the original ideas listed and ask Dan for suggestions after class.
- Asked Keith for opinions on how possible there are.

**Insights:**

- Smart Sport Shoe Insoles: A worry about the sensor placement because the user has to step on the sensors
- Smart folding shopping: it has to handle a motor and wheels
- Smart Laundry Basket: too simple

**Next Action:**

- Revise all ideas and plan deeper in detail.

## 2025-01-28

**Note:**

- Rethinking again
  - Overview
  - Values for user
  - Reference
  - Mapping feature
    - with sensor and where to place sensors
    - with possible filters for each case and data collection
    - network
  - user interface
  - plan

**Result:**

- Got two ideas
  - Smart Water Bottle
  - Smart Shoe

**/Logbook/snapshots:**

| ![1](/Logbook/snapshots/2025-01-28/1.png) | ![2](/Logbook/snapshots/2025-01-28/2.png) | ![3](/Logbook/snapshots/2025-01-28/3.png) | ![4](/Logbook/snapshots/2025-01-28/4.png) |
|-----------------------|-----------------------|-----------------------|-----------------------|
| ![5](/Logbook/snapshots/2025-01-28/5.png) | ![6](/Logbook/snapshots/2025-01-28/6.png) | ![7](/Logbook/snapshots/2025-01-28/7.png) |  |

## 2025-02-03

**Note:**

- Got ESP32 from Hackspace to practice with Assignment 1 with wifi and Bluetooth.

## 2025-02-10

**Note:**

- Before having a seminar class, showed new ideas revised to Keith and asked his opinion.
- In the seminar class, showing the idea and receiving a comment to adjust.

**Result:**

The Smart Shoe as the final topic

## 2025-02-11

**Note:**

- Submit the Poster
- Get the sensors listed from Hackspace

## 2025-02-25 - 2025-02-28

**Note:**

- Initiated the project on GitHub
- Setup the sensors: force sensors and MPU6040
- Applied some simple filters like threshold, from input value observation
- Did all features in the simple ways
- Installing on a shoe
- Recorded the video and did slides for a demo.

![1](/Logbook/snapshots/2025-02-28/1.jpeg)

**Reflect:**

- When starting the project, I couldn't connect all the sensors properly. So, I had to consult Keith. I set up the wrong board. I initially set up Firebeetle 2 esp32-e, but I had to use Adafruit ESP32 Feather.
- A force sensor should be adapted with a resistor.
- There is some noise or error on the force sensor, which sometimes has no pressure, but there is a value on the debug console.
- Using one three-force sensor for step counting is not efficient enough.
- I planned to use Bluetooth and Wifi together, but when the storage size of ESP32 is not enough.

## 2025-03-10 - 2025-03-22

**Note:**

- Change the smaller Bluetooth library to follow Keith's suggestion.
- Trying to refactor code on Arduino
- Trying to explore web app technology

**Reflect:**

- I intentionally wanted to try using React Native, but I could not quickly improve my effectiveness, so based on my experience, I moved back to using NextJS.
- Implementing every feature in a single file makes maintaining and modifying the code complex. So, I separated the logic into modular functions or files to improve readability, reusability, and debugging efficiency.

## 2025-03-23 - 2025-03-30

**Note:**

- Trying new ways to calibrate the data from sensors first before using it in the feature.
- Revise the feature: uneven balance, step counting, and fall-detecting
- Adapted data within the Web using read data from BLE (decode) and MQTT (web socket).
- Try multithreaded

![1](/Logbook/snapshots/2025-03-30/1.jpg)

**Reflect:**

- When applying the multithread to every task, calling MQTT can sometimes be a problem, as is the limit for requesting test.mosquitto.org.

## 2025-04-02 - 2025-04-03

**Note:**

- Testing process
- Preparing IoT System final submission
