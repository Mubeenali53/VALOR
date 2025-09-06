import serial
import time

ser = serial.Serial('/dev/ttyUSB0', 115200, timeout=1)

def send_command(cmd):
    ser.write((cmd + "\n").encode())
    print(f"[INFO] Sent command: {cmd}")
    time.sleep(0.1)

if __name__ == "__main__":
    try:
        send_command("FORWARD")
        time.sleep(2)
        send_command("SLOW")
        time.sleep(2)
        send_command("STOP")
    except KeyboardInterrupt:
        print("Stopped by user")
