/*** header block ***
 * code file name: final_project_AutoPetFeeder_EMT2460
 * code description: Program to take an inputted time and dispense a 
   user-designated amount of food into a bowl for a pet, such as a dog or cat
 * MCU board used: Arduino MEGA 2560 Microcontroller Development Board
 * IDE version used to test code: Arduino IDE v2.3.2
 * programmer(s) name: Frederick De Leon
 * date when code is created/modified: 05/22/2023
 * code version: v2.0 
 ***/

#include <LiquidCrystal.h>
#include <TimeLib.h>
#include <Servo.h>
#include <Keypad.h>

Servo servo_door; // servo motor object

// Keypad
const byte ROWS = 4; // four rows
const byte COLS = 4; // four columns
// define the symbols on the buttons of the keypad
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {22, 24, 26, 28}; // connect to the row pinouts of the keypad
byte colPins[COLS] = {30, 32, 34, 36}; // connect to the column pinouts of the keypad

// initialize an instance of class NewKeypad
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

// LCD Display
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

bool feedingActionInProgress = false;
int feedingHour = 0;
int feedingMinute = 0;

void setup() { //runs only once or when Arduino is reset
  Serial.begin(9600);
  servo_door.attach(13); // attach signal pin of servo to digital pin 13 on Arduino
  lcd.begin(16, 2);
  servo_door.write(55);
  setTime(22, 34, 30, 21, 5, 2023); // Set an initial time (hour, minute, second, day, month, year)
}

void loop() { //runs repeatedly 
  // Get current time
  int hours = hour();
  int minutes = minute();
  int seconds = second();

  // Check if the feeding time is reached
  if (feedingTimeReached(hours, minutes)) {
    if (!feedingActionInProgress) {
      performFeedingAction();
    }
  } else {
    feedingActionInProgress = false;
  }

  // Print the date and time on the LCD
  printDateTime(hours, minutes, seconds);

  delay(1000); // Delay for 1 second
}

bool feedingTimeReached(int currentHour, int currentMinute) {
  // Check for button press on the keypad
  char key = customKeypad.getKey();
  if (key == '#') {
    setFeedingTime();
    return false; // Return false to prevent immediate feeding action
  }

  // Check if the entered time matches the current time
  return (currentHour == feedingHour && currentMinute == feedingMinute);
}

void performFeedingAction() {
  feedingActionInProgress = true;
  servo_door.write(85); // Move the servo to the specified angle
  delay(200); //delay 200 ms
  servo_door.write(55); //return servo to original position
  lcd.clear();
  lcd.print("Feeding Complete");
  delay(2000); //dealy 2000 ms 
  lcd.clear();
}

void setFeedingTime() {
  // Prompt the user to enter the feeding time
  lcd.clear();
  lcd.print("Enter feeding time");
  lcd.setCursor(0, 1);
  lcd.print("HH:MM");

  String inputTime = ""; // variable to store the user input time

  // Wait for the user to enter the time
  while (inputTime.length() < 5) {
    char key = customKeypad.getKey();

    if (key) {
      if (key == '#') {
        break; // Exit the loop if the user presses '#'
      } else if (key == '*') {
        inputTime = ""; // Clear the entered time if the user presses '*'
      } else {
        inputTime += key; // Append the key value to the entered time
      }

      lcd.setCursor(0, 1);
      lcd.print("      "); // Clear the previously displayed time
      lcd.setCursor(0, 1);
      lcd.print(inputTime.substring(0, 2) + ":" + inputTime.substring(3)); // Display the entered time with colon
    }
  }

  // Store the feeding time
  feedingHour = inputTime.substring(0, 2).toInt();
  feedingMinute = inputTime.substring(3).toInt();
}

void printDateTime(int hours, int minutes, int seconds) { //function to print time in hours, minutes and seconds to LCD Display 
  // Print the date and time on the LCD
  lcd.clear();
  lcd.print("Date: ");
  lcd.print(month());
  lcd.print("/");
  lcd.print(day());
  lcd.print("/");
  lcd.print(year());
  lcd.setCursor(0, 1);
  lcd.print("Time: ");
  lcd.print(hours);
  lcd.print(":");
  if (minutes < 10) {
    lcd.print("0"); // Add zero for single-digit minutes
  }
  lcd.print(minutes);
  lcd.print(":");
  if (seconds < 10) {
    lcd.print("0"); // Add zero for single-digit seconds
  }
  lcd.print(seconds);
}
