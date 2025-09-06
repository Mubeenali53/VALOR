import serial

# Setup serial connection (update port if needed)
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

while True:
    line = gps.readline().decode(errors="ignore").strip()
    if line.startswith("$GPGGA"):
        coords = parse_gpgga(line)
        if coords:
            print(f"Latitude: {coords[0]}, Longitude: {coords[1]}")
