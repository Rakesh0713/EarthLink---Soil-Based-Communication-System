# 🌍 EarthLink – Soil-Based EMF Communication System

**EarthLink** is a soil-based communication system that transmits real-time text and sensor data through electromagnetic fields (EMF) in the soil. It serves as a cost-effective alternative for underground or tunnel-based communication where traditional RF and wired systems struggle.

---

## 📷 Project Kit Overview

> 🛠️ Below are images of the project kit used in the development:

**Transmitter Kit**
![TX](https://github.com/user-attachments/assets/c34737e1-fdfc-4656-957e-70eb57818e70)

**Receiver Kit**
![RX](https://github.com/user-attachments/assets/fcadefd6-5e50-435e-8e7e-e3e08c74f817)


**Complete Setup**
![Complete kit](https://github.com/user-attachments/assets/90115892-8562-4e80-92d1-6187dc9eae75)

---

## 🧠 Architecture Diagram:
![Architecture](https://github.com/user-attachments/assets/8b328d68-d894-4980-b893-c5b49188e0d7)

💡 Explanation:
Sender Side: The Arduino UNO collects both user text input and real-time sensor data (temperature, vibration, heart rate), and combines them into a message.

Modulation: Data is modulated using Frequency Shift Keying (FSK), converting binary values into two distinct frequencies (100kHz & 150kHz).

Medium: The signal travels underground through the soil as EMF pulses.

Receiver Side: The EMF signal is demodulated and decoded by a receiver circuit and processed by the NodeMCU ESP8266.

Display: The decoded message is displayed on an Adafruit IO dashboard in real-time for monitoring.

---

🔧 Technology Stack
Embedded C – Microcontroller Programming

Arduino UNO – Transmitter-side Controller

NodeMCU ESP8266 – Receiver-side IoT Controller

DHT11, SW420, Heart Rate Sensor – Environmental & Biological Monitoring

Adafruit IO – Cloud-based Dashboard Display

FSK Modulation – Frequency Shift Keying for EMF Transmission

---

📊 Features

Real-time message and sensor data transmission through soil

Emergency message framing with start (*) and end (#) tags

Reliable underground communication for mining/tunnel environments

Cloud display for remote monitoring (via Adafruit IO)


