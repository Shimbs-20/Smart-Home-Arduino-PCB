# Smart Home IoT Shield for Arduino (220V Control) 🏠

This project is a custom-designed PCB Shield for Arduino that enables safe control of high-voltage home appliances (220V AC) via a mobile application.

## ⚡ Features
* **Safety First:** Designed with proper **creepage and clearance** slots to isolate 220V AC from the 5V logic.
* **Wireless Control:** Integrated header for ESP8266/HC-05 modules for WiFi/Bluetooth connectivity.
* **Noise Immunity:** Optical isolation (Optocouplers) to prevent relay switching noise from resetting the microcontroller.
* **Power Management:** On-board SMPS / Linear regulator to power the Arduino from 12V.

## 🛠️ Hardware Specs
* **Relays:** 4x 10A 220V SPDT Relays.
* **Isolation:** PC817 Optocouplers.
* **Connectors:** High-current screw terminals for AC loads.

## 📂 Folder Structure
* `hardware/` - Source files (KiCad) and Gerber production files.
* `firmware/` - Arduino code for serial communication with the Mobile App.
* `docs/` - PDF Schematic and BOM (Bill of Materials).

## 👨‍💻 Author
**Youssef S.** - Mechatronics & PCB Design Engineer
