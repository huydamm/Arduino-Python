import serial
import time

# Set this to your Arduino's COM port (check in Arduino IDE)
SERIAL_PORT = 'COM11'
BAUD_RATE = 9600

def send_countdown(seconds):
    with serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1) as ser:
        time.sleep(2)  # wait for Arduino reset
        for sec in range(seconds, -1, -1):
            time_str = f"{sec:04}"  # format to 4 digits
            print(f"Sending: {time_str}")
            ser.write((time_str + '\n').encode('utf-8'))
            time.sleep(1)

send_countdown(120)  # example: count down from 30
