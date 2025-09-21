import serial
import time
from datetime import datetime
import pytz
import sys

class ArduinoClock:
    def __init__(self, port='COM11', baud=115200, timezone='Asia/Ho_Chi_Minh'):
        self.port = port
        self.baud = baud
        self.timezone = pytz.timezone(timezone)
        self.ser = None
        self.running = False
        
    def connect(self):
        try:
            self.ser = serial.Serial(
                port=self.port,
                baudrate=self.baud,
                timeout=1,
                write_timeout=1
            )
            time.sleep(2)  # Arduino reset time
            print(f"Connected to Arduino on {self.port} at {self.baud} baud")
            return True
        except serial.SerialException as e:
            print(f"Connection error: {e}")
            return False
            
    def get_time_string(self):
        now = datetime.now(self.timezone)
        return now.strftime('%H%M%S')
    
    def send_time(self):
        time_str = self.get_time_string()
        try:
            self.ser.write(f"{time_str}\n".encode('utf-8'))
            self.ser.flush()  # Ensure data is sent immediately
            print(f"Sent: {time_str}", end='\r')
        except serial.SerialException as e:
            print(f"\nCommunication error: {e}")
            self.close()
            sys.exit(1)
    
    def run(self):
        if not self.connect():
            return
            
        self.running = True
        print(f"Streaming time in {self.timezone.zone} (Ctrl+C to stop)")
        
        try:
            while self.running:
                self.send_time()
                time.sleep(0.9)  # Slightly faster than 1s to ensure no drift
        except KeyboardInterrupt:
            print("\nStopping clock...")
        finally:
            self.close()
    
    def close(self):
        if self.ser and self.ser.is_open:
            self.ser.close()
        self.running = False
        print("Connection closed")

if __name__ == "__main__":
    config = {
        'port': 'COM11',  # Update with your port
        'baud': 115200,   # Higher baud rate
        'timezone': 'Asia/Ho_Chi_Minh'
    }
    
    clock = ArduinoClock(**config)
    clock.run()

