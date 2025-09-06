# 🚘 VALOR - Vision-based Autonomous Location and Obstacle-avoidance Robot

VALOR (Vision-based Autonomous Location and Obstacle-avoidance Robot) is my **final year ECE major project**, designed to demonstrate the integration of **AI, IoT, and Robotics** for real-world autonomous navigation.  
It combines **YOLO-based object detection**, **GPS tracking**, and **motor control** to autonomously move in an environment while avoiding obstacles.  

---

## ✨ Features

- 🧠 **AI-powered Object Detection** using YOLO optimized with TensorRT on NVIDIA Jetson Nano 2GB  
- 📡 **Real-time GPS Tracking** with live location updates  
- ⚙️ **4-Motor Independent Drive System** using BTS7960 motor drivers controlled by ESP32-WROOM  
- 🌐 **Flask-based Web UI** to display:
  - Live camera feed
  - GPS coordinates and map
  - System status  
- ✋ **Gesture Control Mode** (via OpenCV Mediapipe) for manual navigation  
- 🔗 **Jetson–ESP32 communication** for autonomous motor control  

---

## 🛠️ Tech Stack

- **Hardware**
  - NVIDIA Jetson Nano 2GB Dev Kit
  - ESP32-WROOM microcontroller
  - 4 × BTS7960 motor drivers
  - GPS module (Neo-6M)
  - USB camera (mounted 1m above ground)
  - 4 DC motors with independent drive
- **Software**
  - Python (Flask, OpenCV, Mediapipe, PySerial)
  - YOLO object detection (TensorRT optimized)
  - Jetson Inference SDK
  - Arduino IDE (ESP32 firmware)
  - HTML, CSS, JavaScript (Web UI)

---

## 📂 Repository Structure

```planetext

VALOR/
│── esp32/ # ESP32 firmware for motor control
│ └── motor_control.ino
│
│── jetson/ # Jetson Nano AI & control code
│ ├── object_detection.py
│ ├── gps_tracking.py
│ ├── motor_comm.py
│ └── app.py # Flask server
│
│── ui/ # Frontend files
│ ├── templates/
│ │ └── index.html
│ └── static/
│ ├── style.css
│ └── script.js
│
│── docs/ # Documentation & diagrams
│ ├── architecture.png
│ └── wiring_diagram.png
│
└── README.md # Project showcase

---

## 🚀 Getting Started

### 1. Clone the repository

```bash
git clone https://github.com/<your-username>/VALOR.git
cd VALOR
```

### 2. Setup Jetson Nano

```bash
sudo apt-get update
sudo apt-get install python3-pip
pip3 install flask opencv-python pyserial
```

- Setup Jetson Inference for YOLO object detection

### 3. Setup ESP32

- Flash esp32/motor_control.ino using Arduino IDE

- Connect BTS7960 motor drivers to ESP32 PWM pins

### 4. Run the system

```bash
python3 jetson/app.py
```

- Open browser at http://<jetson-ip>:5000 to access UI

## 📂 Dataset

This project uses the **IDD (Indian Driving Dataset)** developed by IIIT Hyderabad.  
The dataset contains diverse traffic scenarios from Indian roads, including cars, buses, pedestrians, two-wheelers, and animals — making it suitable for training robust models for mixed-traffic environments.

- **Dataset Name:** Indian Driving Dataset (IDD)
- **Source:** IIIT Hyderabad
- **Download Link:** [Indian Driving Dataset - IDD](https://idd.insaan.iiit.ac.in/dataset/download)
- **Usage in VALOR:**  
  - Trained YOLOv8 model for object detection on Indian road scenarios  
  - Used annotated images for segmentation and bounding box extraction  
  - Classes used in this project: Pedestrians, Cars, Buses, Two-Wheelers, Animals  

📌 *Note: Dataset is large, so it is not included directly in this repository. Please download it separately from the official source above.*

## 📊 System Architecture

### 🎥 Demo

- Video Link :-

## 📜 License

- This project is licensed under the MIT License.
