# Safety Box System with AVR ATmega32

### The system simulates a safty box and performs 4 main functions:
- Saves and changes the password *(saved in eeprom)* for the user using Keypad.
- Locks the user if the password is incorrect 3 consecutive times and activates buzzer and led to *simulate the alarm system*.
- Controls servo motor to *simulate the saftey box door*. 
- Shows time on LCD.

#### Designed using Embedded C programming language for AVR ATmega32.

#### Using Timers, Interrupts, I2C configuration to control EEPROM (Two Wire Interface), Keypad, LCD, Servo, Buzzer and Leds.
