#Refrenenced https://roboticsbackend.com/raspberry-pi-arduino-serial-communication/

#!/usr/bin/env python3
import serial_test
import time

if __name__ == '__main__':
    ser = serial_test.Serial('/dev/ttyUSB0', 9600, timeout=1)
    ser.reset_input_buffer()
    
    """
    #Basic reading serial data from arduino and printing it

    while True:
        if ser.in_waiting > 0:
            line = ser.readline().decode('utf-8').rstrip()
            print(line)
    """

    # Sending arduino data and then having the arduino send back same data
    # and printing the data from arduino that was originally sent from the pi
    while True:
        ser.write(b"Turn motor left!\n")
        line = ser.readline().decode('utf-8').rstrip()
        print(line)
        time.sleep(1)


            