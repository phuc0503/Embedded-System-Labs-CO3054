# Lab 05: FreeRTOS Software Timer

## Goal
  Able to understand and use FreeRTOS Software Timer.

## Exercises
Create 2 software timers sharing only one timer callback function, in which:
- The first timer is used to print "ahihi" every 2 seconds and will stop after 10 times printing.
- The second timer is used to print "ihaha" every 3 seconds and will stop after 5 times printing.

## Output
|![Output](https://github.com/phuc0503/Embedded-System-Labs-CO3054/blob/master/Images/Lab5/output.png "Ouput")|
|:--:| 
|*Output*|

## To build and run project
- Build:
```
idf.py build
```
- Flash and monitor (replace `[PORT]` with the actual port, you can open `Device Manager > Ports (COM & LPT)` to check which port ESP32 is using):
```
idf.py -p [PORT] flash monitor
```
