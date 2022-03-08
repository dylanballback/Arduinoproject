#Refrenenced https://roboticsbackend.com/raspberry-pi-arduino-serial-communication/

#!/usr/bin/env python3
import serial 
import time
import struct
from simple_pid import PID

#Define PID Constands
p = 1
i = 0
d = 0
set_angle = 0

def pid_calc(angle, set):
    pid = PID(p, i, d, setpoint=set)
    pid.output_limits(-400, 400)
    pid_out = pid(angle)
    if pid > 0:
        dir = 0
    elif pid < 0:
        dir = 1
    return pid_out, dir        

if __name__ == '__main__':
    ser = serial.Serial('/dev/ttyUSB0', 500000, timeout=1)
    ser.reset_input_buffer()

    while True:
        if ser.in_waiting > 0:
            xangle = ser.readline().decode("utf-8").rstrip()
            print(f"X Angle = {xangle}")
            xangle = float(xangle)
            pid_out = pid_calc(xangle, set_angle)
            print(f"PWM = {pid_out[0]}")
            print(f"DIR = {pid_out[1]}")


            writevar = struct.pack('i', pid_out[0], pid_out[1])
            ser.write(writevar)



