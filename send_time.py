import serial
import time

ser = serial.Serial(
    '/dev/tty.usbserial-10',
    115200
)

while True:
    current = time.strftime("%H:%M")

    ser.write(current.encode())

    print(current)

    time.sleep(1)