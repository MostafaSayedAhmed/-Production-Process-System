# -Production-Process-System
Features:

Multi Function Machine has three modes with one switch to switch between these modes. The Machine is secured with settable password :

- Calculator Mode : to perform simple arithmetic operations like addition, subtraction, multiplication and division on two integers.

- Alarm System Mode : that depends on temperature sensor:
if value is greater than 50 degree, led will flash and buzzer go on and off every 100 ms and send signal to second Microcontroller to move motor in clockwise direction with max speed using UART
if value is lower than 50 degree, led will flash every 1 second while buzzer is turned off. the motor connected to second Microcontroller will rotate in counterclockwise direction.

- Sunlight Detection Mode : 
if LDR detect high light intensity, Led will be turned off and second MCU will send text to be printed on LCD "Morning" that is connected to the first Microcontroller through UART
if LDR detect low light intensity, Led will be turned on and the second Microcontroller will send text to be printed on LCD "Night" of the first Microcontroller through UART

Components:
- Two ATMEGA32 Microcontrollers
- LCD
- Keypad
- Temperature Sensor
- LDR Sensor
- Fan

Skills used:
- Leadership
- Drivers Writing
- Communication skills
- Problem Solving
