import cv2
from ultralytics import YOLO
import serial
import time

# === Serial communication with ESP32 ===
try:
    ser = serial.Serial('/dev/ttyUSB0', 115200, timeout=1)
    print("[INFO] Serial port opened successfully.")
except:
    print("[ERROR] Could not open serial port.")
    exit()

# === Load YOLOv8 model ===
model = YOLO("best.pt")  # Replace with your trained model path

# === Open webcam ===
cap = cv2.VideoCapture(0)
if not cap.isOpened():
    print("[ERROR] Cannot open camera.")
    exit()

# === Main loop ===
try:
    while True:
        ret, frame = cap.read()
        if not ret:
            print("[WARNING] Empty frame, skipping.")
            continue

        # YOLO detection
        results = model.predict(source=frame, imgsz=640, conf=0.5)
        frame = results[0].plot()

        # Distance estimation
        speed_command = "FORWARD"
        min_distance = 1000

        for result in results:
            for box in result.boxes:
                xywh = box.xywh[0]
                bbox_width = xywh[2]
                distance_est = 1000 / bbox_width  # pseudo distance

                if distance_est < min_distance:
                    min_distance = distance_est

        # Decision logic
        if min_distance < 50:
            speed_command = "STOP"
        elif min_distance < 100:
            speed_command = "SLOW"
        else:
            speed_command = "FORWARD"

        # Send command
        ser.write((speed_command + "\n").encode())
        print(f"[INFO] Sent: {speed_command}, Distance: {min_distance:.2f}")

        # Show video
        cv2.imshow("YOLOv8 Detection", frame)
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

except KeyboardInterrupt:
    print("\n[INFO] Stopped by user.")
finally:
    cap.release()
    cv2.destroyAllWindows()
    ser.close()
    print("[INFO] Resources released. Exiting.")
