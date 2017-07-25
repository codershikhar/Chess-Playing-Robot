# this reads and writes from java and arduino

import os
import serial
import time

ser = serial.Serial("COM7", 9600, timeout = None)

def writeToJava(s):
    file = open("P2J", "w")
    file.write(s)
    file.close()

def readFromJava():
    while os.path.isfile("J2P") == False:
        pass
    while os.path.getsize("J2P") < 1:
        pass
    file = open("J2P", "r")
    str1 = file.read()
    # print(file.read())
    file.close()
    os.remove("J2P")
    print("read from java")
    return str1

def writeToArduino(s):
    time.sleep(5)
    ser.write(s)


# Main

while True:
    # read from arduino and send to java
    str1 = str(ser.readline())
    writeToJava(str1[2:].split("\\")[0])
    print("read and writen", str1[2:].split("\\")[0])
    # check if right or wrong
    str1 = readFromJava()
    print(str1)
    if str1 == '1':
        writeToArduino(b'1')
        str1 = readFromJava()[0:5]
        writeToArduino(str1.encode())
    else:
        writeToArduino(b'0')