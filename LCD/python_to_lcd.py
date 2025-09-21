import serial
import time

# Change COM port to match your Arduino
arduino = serial.Serial('COM11', 9600, timeout=1)
time.sleep(2)  # Wait for Arduino to reset

def send_to_lcd(message):
    arduino.write((message + "\n").encode())

# Example
send_to_lcd("yeu linhphan")

