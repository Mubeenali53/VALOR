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
```

## 📊 System Architecture

The architecture of **VALOR (Vision-based Autonomous Location and Obstacle-avoidance Robot)** is divided into three major layers:

### 1. Perception Layer

- **Camera (USB Webcam)**: Captures real-time video feed from the front of the robot.  
- **YOLOv8 Object Detection (Jetson Nano)**: Processes video frames using a custom-trained model (IDD dataset) to detect pedestrians, vehicles, two-wheelers, and animals.  
- **GPS Module (Neo-6M)**: Provides live latitude/longitude coordinates for location tracking.

### 2. Decision Layer

- **Jetson Nano**:
  - Runs YOLOv8 inference (optimized with TensorRT).  
  - Estimates distance of detected objects.  
  - Decides movement commands: `FORWARD`, `SLOW`, `STOP` .
  - Sends commands to ESP32 over **UART Serial Communication**.  

### 3. Control & Actuation Layer

- **ESP32-WROOM**:
  - Receives commands from Jetson Nano.  
  - Controls **4 independent DC motors** using **BTS7960 motor drivers** with PWM.  
  - Executes motion control (forward, backward, turning, braking).  
- **Motors & Wheels**: Provide movement to the robot.

### 4. User Interface Layer

- **Flask Web Server (Jetson Nano)**:
  - Streams **live video feed** from the camera.  
  - Displays **current command** and **GPS location**.  
  - Integrates with **Leaflet.js map** for real-time tracking.

---

### 🔄 Data Flow

1. **Camera → Jetson Nano**: Frame capture.  
2. **YOLO Model**: Detects objects, estimates distance, determines command.  
3. **Jetson Nano → ESP32**: Sends movement command over UART.  
4. **ESP32 → Motors**: Executes command using PWM control.  
5. **GPS → Jetson Nano → Flask UI**: Sends live coordinates for map display.  
6. **Flask Dashboard**: Shows live video, GPS, and current command to user.

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

### 🎥 Demo

- Video Link :-

## 📈 Future Scope

- **Improved Object Detection:** Upgrade to YOLOv9 or Transformer-based models (DETR, RT-DETR); train on larger datasets for diverse conditions.  
- **Sensor Fusion:** Combine LiDAR/Ultrasonic with vision; integrate GPS with IMU for robust localization in GPS-denied areas.  
- **Path Planning & Navigation:** Implement SLAM; use advanced algorithms like A*, D*, RRT* for dynamic path planning.  
- **Edge Optimization:** Apply TensorRT, INT8 quantization, pruning for faster inference; explore higher-performance edge devices.  
- **V2V & Cloud Connectivity:** Enable multi-robot communication; use cloud dashboards for real-time fleet monitoring.  
- **Enhanced UI:** Add manual override controls; display path traces and system health (battery, motors) on the dashboard.  
- **Scalability & Applications:** Adapt for autonomous delivery, agriculture, disaster rescue, or smart city testbeds.

## 📜 License

- This project is licensed under the MIT License.

## 👨‍💻 Authors

- **Syed Mubeen Ali**  
  Electronics and Communication Engineering (ECE)  
  Muffakham Jah College of Engineering and Technology  
  📧 Email: syedmubeenali553@gmail.com

- **Danish Ahmed**  
  Electronics and Communication Engineering (ECE)  
  Muffakham Jah College of Engineering and Technology  

- **Syed Zeeshan**  
  Electronics and Communication Engineering (ECE)  
  Muffakham Jah College of Engineering and Technology  
