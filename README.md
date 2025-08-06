# 🗳️ Voting Machine - TinkerCAD Project

This project simulates a **secure electronic voting machine** built using **Arduino** in **TinkerCAD**. It includes password-protected voting, vote recording via push buttons, and result display on an LCD.

![Project Screenshot](capture.png)

---

## 📂 Repository Contents

- `code.cpp` – Arduino source code for the voting machine
- `Capture.PNG` – Screenshot of the project layout in TinkerCAD

---

## ⚙️ Features

- 🔐 **Password Protection**: Only authorized users can vote
- 🗳️ **Push Button Voting**: Each button corresponds to a different candidate
- 📺 **LCD Display**: Displays prompts, access messages, and voting results
- 🔄 **Vote Reset Option**: Reset functionality for starting a new election
- 🧠 **Multi-Arduino Communication** (if applicable): Coordination between two Arduino boards (if the code implements it)

---

## 🧰 Components Used (in TinkerCAD)

- 1 or 2 Arduino Uno boards
- 16x2 LCD Display
- 4x4 Matrix Keypad
- Push Buttons (for candidates)
- Servo Motor (optional for access control)
- Breadboard and jumper wires
- Voltage dividers (for analog input handling)
- TTP223 Touch Sensors (if included)

---

## 🚀 How It Works

1. **Startup**: System initializes and prompts for a password.
2. **Authentication**: Voter enters a password using the keypad.
3. **Voting Mode**: Upon correct entry, voter casts a vote using one of the buttons.
4. **Vote Recording**: The system confirms and stores the vote.
5. **Repeat/Reset**: Admin can reset the system to begin a new voting cycle.

---

## 📸 Project Screenshot

> ![TinkerCAD Simulation](capture.png)

---

## 💡 Future Improvements

- Display vote counts for each candidate
- Add real-time clock for timestamp logging
- Store votes to EEPROM or SD card
- Add buzzer feedback or LED indicators

---

## 📎 License

This project is open-source a
