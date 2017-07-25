# this reads and writes from java and arduino

import subprocess
import os
import serial
import time

ser = serial.Serial("COM7", 9600, timeout = None)

def writeToJava():
    file = open("P2J", "w")
    file.write("hello_madam")
    file.close()

def readFromJava():
    while os.path.isfile("J2P") == False:
        pass
    while os.path.getsize("J2P") < 5:
        pass
    file = open("J2P", "r")
    print(file.read())
    file.close()
    os.remove("J2P")

def writeToArduino():
    time.sleep(5)
    print("hello")
    while 1:
        ser.write(b'agrawal')
        time.sleep(2)
        ser.write(b'shikhar')
        time.sleep(2)


writeToArduino()