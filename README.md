# arduino-elevator

Elevator with call buttons and go-to buttons.

`main.ino` is the brain, it controls the motor.

`platine.ino` controls the arduino inside the elevator with go-to buttons.

The communication between the 2 parts is made with bluetooth modules.

We use RF sensors to detect the position of the elevator. Two of them for each floor: detect top and bottom of the elevator.  
