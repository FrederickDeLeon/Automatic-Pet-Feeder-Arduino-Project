The objective of this project is to dispense a certain amount of food at a user-set time (in hours and minutes) through a keypad into a dog's or some other pet's bowl. 
It is expected to work in the case that a user wants to set a time in hours and minutes that the pet food is supposed to be dispensed to their pet. 
The project will keep track of the time and date on an LCD screen, display the time the user is entering using the keypad, then actuate a servo motor at a set angle for a set duration of time to dispense food below into a bowl/dish/plate for a pet.
The project will also aim to have the functionality of an ultrasonic sensor that will dispense the food if it detects an animal a certain distance from the automatic feeder but ONLY if it is within 10 minutes of the feeding time set by the user. 
So in the case that a pet comes near the automatic feeder, perhaps expecting food, the food will only dispense if it 1) is the time the user previously set for dispensing the food or 2) if it is within 10 minutes of the user set feeding time. 
The project will only be able to remember one user set time at a time, it will not take more than one set time. 
In such a case of entering more than one set time, the second time set by the user will be the time the food will be dispensed by the Arduino. 
The Arduino will only work with time set in the format of HH:MM (as in hourhour:minuteminute) hours being from 0-23 (0 being midnight) and minutes 0-59, for example, if you wanted food to be dispensed to your pet at 10:43 pm, you would need to enter 22:43. 
The user cannot control the angle or time duration of the servo motor actuating to dispense the food (thereby controlling the amount of food dispensed) externally, to change that they would have to modify the code manually. 


















