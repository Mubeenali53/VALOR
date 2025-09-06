from flask import Flask, render_template, Response, jsonify
import cv2
import threading
import serial

app = Flask(__name__)

# === Global state ===
current_command = "STOP"
gps_data = {"lat": 0.0, "lon": 0.0}

# === Camera ===
camera = cv2.VideoCapture(0)

# === GPS ===
gps = serial.Serial("/dev/ttyUSB1", baudrate=9600, timeout=1)

def parse_gpgga(sentence):
    try:
        parts = sentence.split(",")
        if parts[0] == "$GPGGA" and parts[2] and parts[4]:
            lat = float(parts[2][:2]) + float(parts[2][2:]) / 60.0
            lon = float(parts[4][:3]) + float(parts[4][3:]) / 60.0
            if parts[3] == "S": lat = -lat
            if parts[5] == "W": lon = -lon
            return lat, lon
    except:
        return None
    return None

def gps_thread():
    global gps_data
    while True:
        line = gps.readline().decode(errors="ignore").strip()
        if line.startswith("$GPGGA"):
            coords = parse_gpgga(line)
            if coords:
                gps_data = {"lat": coords[0], "lon": coords[1]}

threading.Thread(target=gps_thread, daemon=True).start()

def gen_frames():
    while True:
        success, frame = camera.read()
        if not success:
            continue
        ret, buffer = cv2.imencode('.jpg', frame)
        yield (b'--frame\r\n'
               b'Content-Type: image/jpeg\r\n\r\n' + buffer.tobytes() + b'\r\n')

@app.route('/')
def index():
    return render_template("index.html")

@app.route('/video_feed')
def video_feed():
    return Response(gen_frames(),
                    mimetype='multipart/x-mixed-replace; boundary=frame')

@app.route('/status')
def status():
    return jsonify({
        "command": current_command,
        "gps": gps_data
    })

if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5000, debug=True)
