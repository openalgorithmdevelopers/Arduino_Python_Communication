# -- coding: utf-8 --
"""
Created on Fri Jul 29 13:50:50 2022

@author: bhupendra.singh
"""

import serial
import time

## check first three bits to find the command type
#  
#  000 for button
#  010 for IMU
#  111 or 224 for Joystick X
#  110 or 192 for Joystick Y

def getCommandType(cmdString):
    commandMask = 224   #first three left bit 1 and rest 5 are 0
    cmd = int(cmdString)
    result = cmd & commandMask
    if(result == 224):
        return "JoystickX"
    if(result == 192):
        return "JoystickY"
    if(result == 0):
        return "Button"
    if(result == 64):
        return "IMU"

def handleJoystick(axis, cmdString):
    jsValue = 31 & int(cmdString)   #31 is 00011111 which means setting the cmd bits to 0
    print(axis + str(jsValue))
# windows 7
ser = serial.Serial(port='COM4', baudrate=9600, bytesize=8)

#ser.read()
ser.flushInput()
ser.flushOutput()

while True:
    commandString = ""
    while(True):
        data = ser.read().decode('utf-8')
#        print(data)
        if(data == '\r' or data == '\n'):
            break
        commandString += data
    if(commandString == ""):
        continue
    commandType = getCommandType(commandString)
    if(commandType == "JoystickX"):
        handleJoystick("X",commandString)
    if(commandType == "JoystickY"):
        handleJoystick("Y",commandString)        
#    print(commandType)
    time.sleep(0.01)
    
#ser.write(str.encode('z'))
#time.sleep(0.1)
    
ser.close()