#Refrenenced https://roboticsbackend.com/raspberry-pi-arduino-serial-communication/

#!/usr/bin/env python3
import serial 
import time
import struct

if __name__ == '__main__':
    ser = serial.Serial('/dev/ttyUSB0', 500000, timeout=1)
    ser.reset_input_buffer()
    
    
    #Basic reading serial data from arduino and printing it

    while True:
        if ser.in_waiting > 0:
            xangle = ser.readline().decode("utf-8").rstrip()
            print(type(xangle))
            print(f"X Angle = {xangle}")
            pwm = int(float(xangle))
            str_pwm = str(pwm)
            print(f"X PWM = {pwm}")
            writevar = struct.pack(i, pwm)
            print(writevar)
            print(type(writevar))
            ser.write(writevar)
        
    """

    # Sending arduino data and then having the arduino send back same data
    # and printing the data from arduino that was originally sent from the pi
    while True:
        ser.write(b"Turn motor left!\n")
        line = ser.readline().decode('utf-8').rstrip()
        print(line)
        time.sleep(1)

    """

            