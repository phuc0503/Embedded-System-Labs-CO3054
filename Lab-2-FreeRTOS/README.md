# Lab 02: ESP32 GPIO and FreeRTOS task
## Goal
<ul>
  <li>Read the input from or write the output to an GPIO pin.</li>
  <li>Create, schedule, and destroy FreeRTOS tasks on the ESP32 development board.</li>
</ul>

## Exercises
Create 2 tasks and schedule them using FreeRTOS's task management functions:
<ul>
  <li>A cyclic task printing your srudent ID every second.</li>
  <li>An acyclic task polling a button and print "ESP32" every when the button is pressed.</li>
</ul>

## Required material:
| No.	| Name		      	| Quantity |
| ---	|:-------------------------|:--------:|
| 1	| ESP WROOM 32 board 		|   1	    	|
| 2	| Breadboard      		|   1 	|
| 3  | LED                |  1  |
| 4 	| 100Ohm resistor      	|   1 	|
| 5	| Jump wires      		|   3 	|
| 6 	| Push button SPST      	|   1 	|

## Cicuit diagram
|![Circuit diagram](https://github.com/phuc0503/Embedded-System-Labs-CO3054/blob/master/Images/Lab2/circuit%20diagram.png "Circuit diagram")|
|:--:| 
|*Circuit diagram*|
![Reality circuit](https://github.com/phuc0503/Embedded-System-Labs-CO3054/blob/master/Images/Lab2/reality%20circuit.jpg "Reality circuit")
*Reality circuit*

## Output
|![Output](https://github.com/phuc0503/Embedded-System-Labs-CO3054/blob/master/Images/Lab2/output.png "Ouput")|
|:--:| 
|*Output*|

## Demo
[Click here to watch demo video on Youtube](https://youtu.be/7jc0QhnAovw)

| Supported Targets | ESP32 | ESP32-C2 | ESP32-C3 | ESP32-S2 | ESP32-S3 |
| ----------------- | ----- | -------- | -------- | -------- | -------- |

# _Sample project_

(See the README.md file in the upper level 'examples' directory for more information about examples.)

This is the simplest buildable example. The example is used by command `idf.py create-project`
that copies the project to user specified path and set it's name. For more information follow the [docs page](https://docs.espressif.com/projects/esp-idf/en/latest/api-guides/build-system.html#start-a-new-project)



## How to use example
We encourage the users to use the example as a template for the new projects.
A recommended way is to follow the instructions on a [docs page](https://docs.espressif.com/projects/esp-idf/en/latest/api-guides/build-system.html#start-a-new-project).

## Example folder contents

The project **sample_project** contains one source file in C language [main.c](main/main.c). The file is located in folder [main](main).

ESP-IDF projects are built using CMake. The project build configuration is contained in `CMakeLists.txt`
files that provide set of directives and instructions describing the project's source files and targets
(executable, library, or both). 

Below is short explanation of remaining files in the project folder.

```
├── CMakeLists.txt
├── main
│   ├── CMakeLists.txt
│   └── main.c
└── README.md                  This is the file you are currently reading
```
Additionally, the sample project contains Makefile and component.mk files, used for the legacy Make based build system. 
They are not used or needed when building with CMake and idf.py.
