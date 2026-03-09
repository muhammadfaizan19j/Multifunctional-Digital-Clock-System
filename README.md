# Multifunctional Digital Clock System

A microcontroller-based embedded system that displays real-time clock data, temperature, humidity, and includes a stopwatch feature. The project integrates RTC, DHT sensor, I2C LCD, and push buttons to create a multifunctional digital clock.

---

## 📌 Features

• Real-time clock with accurate time and date  
• Temperature monitoring  
• Humidity monitoring  
• Stopwatch functionality  
• Mode switching using push buttons  
• Low wiring complexity using I2C communication  

---

## ⚙️ Hardware Components

| Component | Quantity |
|----------|----------|
| Arduino UNO / ESP32 | 1 |
| RTC Module (DS1307) | 1 |
| 16x2 LCD with I2C | 1 |
| DHT11 Temperature & Humidity Sensor | 1 |
| Push Buttons | 3 |
| Jumper Wires | As required |
| Breadboard | 1 |

---

## 🔌 Pin Configuration

### ESP32 Connections

| Component | Pin |
|----------|------|
| DHT11 | GPIO 27 |
| MODE Button | GPIO 14 |
| START Button | GPIO 12 |
| RESET Button | GPIO 13 |
| I2C SDA | GPIO 21 |
| I2C SCL | GPIO 22 |

RTC and LCD share the same I2C communication lines.

---

## 🧠 Working Principle

1. The system initializes the RTC, LCD, and DHT sensor when powered on.
2. The RTC module continuously provides accurate time and date.
3. The DHT sensor measures temperature and humidity.
4. The LCD displays time, temperature, and humidity.
5. Users can switch between **Clock Mode** and **Stopwatch Mode** using push buttons.
6. In stopwatch mode, elapsed time is calculated using internal timers of the microcontroller.

---

## 📊 Display Information

Clock Mode:
