//With Arduino Mega 2569

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);


//pin numbers
const int SELECT = 11; 
const int INCREASE = 10;
const int DECREASE = 9;
const int CONFIRM = 8;

//Counter of total select button pushes. Uses modulus to find the variable selected.
int Counter = 0;


//intializes the button states pre and post loop
int buttonState1 = 0;         // current state of the button
int lastButtonState1 = 0;// previous state of the button
int buttonState2 = 0;
int lastButtonState2 = 0;
int buttonState3 = 0;         // current state of the button
int lastButtonState3 = 0;// previous state of the button
int buttonState4 = 0;
int lastButtonState4 = 0;


//DEFAULT VALUES, CHANGE TO SET PRECISE VALUES
float gellen = 50; //gel length, mm
float stretx = 5;   //stretch percentage, %
float strety = 5;
float timehr = 1;  //time of stretch, hr, determines speed


const int NUMBER_OF_VARIABLES = 4;


float gellenincrement = 0.5; //increment/decrement values of all variables
float stretincrement = 0.5;
float timehrincrement = 0.1;

float gellenmax = 100; //max values of each variable
float stretmax = 20;   //min values are set to be zero for all variables
float timehrmax = 24;  //if a increase/decrease button press will take a variable past the max/min values, nothing will happen


void setup() {
  //setup of pins and lcd display
  lcd.begin(20,4);
  pinMode(SELECT, INPUT);
  pinMode(INCREASE, INPUT);
  pinMode(DECREASE, INPUT);
  pinMode(CONFIRM, INPUT);

  //display the default initialized values and starts the loop
  displayVars();
}

void loop() {
  // read the pushbutton input pin for each button
  buttonState1 = digitalRead(SELECT);
  buttonState2 = digitalRead(INCREASE);
  buttonState3 = digitalRead(DECREASE);
  buttonState4 = digitalRead(CONFIRM);
  
  // compare the buttonState to its previous state,
  if (buttonState1 != lastButtonState1) {
    
    //if state changed compared to last loop, check if the button was being pushed
    if (buttonState1 == HIGH) {
      select();
      
      //display updated value or selection values,
      displayVars();
    }

    //important for preventing bouncing and registering more than one action per button press
    delay(50);

    //button 2 = increase
  } else if (buttonState2 != lastButtonState2) {
    if (buttonState2 == HIGH) {
      increase();
      displayVars();
    }
    delay(50);

    //button 3 = decrease
  } else if (buttonState3 != lastButtonState3) {
    if (buttonState3 == HIGH) {
      decrease();
      displayVars();
    }
    delay(50);

    //button 4 = confirm settings
  } else if (buttonState4 != lastButtonState4) {
    if (buttonState4 == HIGH) {
      confirm();
    }
    delay(50);
  }

  
  // save the current state as the last state, for next time through the loop
  lastButtonState1 = buttonState1;
  lastButtonState2 = buttonState2;
  lastButtonState3 = buttonState3;
  lastButtonState4 = buttonState4;
}



//Increments the select button counter
void select() {
  Counter++;
}


//increases the currently selected variable by the increment amount
void increase() {
  //modulus operation to get the varible selected
  int cur_selection = Counter % NUMBER_OF_VARIABLES;
  
  //check to make sure the action wont take the variable over the max
  if (cur_selection == 0) {
    if (gellen + gellenincrement <= gellenmax) {
      gellen += gellenincrement;
    }
  } else if (cur_selection == 1) {
    if (stretx + stretincrement <= stretmax) {
      stretx += stretincrement;
    }
  } else if (cur_selection == 2) {
    if (strety + stretincrement <= stretmax) {
      strety += stretincrement;
    }
  } else if (cur_selection == 3) {
    if (timehr + timehrincrement <= timehrmax) {
      timehr += timehrincrement;
    }
  }
}


//decreases the currently selected variable by the increment amount
void decrease() {
  int cur_selection = Counter % NUMBER_OF_VARIABLES;
  if (cur_selection == 0) {
    if (gellen > gellenincrement) {
      gellen -= gellenincrement;
    }
  } else if (cur_selection == 1) {
    if (stretx > stretincrement) {
      stretx -= stretincrement;
    }
  } else if (cur_selection == 2) {
    if (strety > stretincrement) {
      strety -= stretincrement;
    }
  } else if (cur_selection == 2) {
    if (timehr > timehrincrement) {
      timehr -= timehrincrement;
    }
  }
}

//display that the settings have been confirmed
void confirm() {
  int confCounter = 0;
  boolean q = false;
  lcd.setCursor(15, 2);
  lcd.print("CNFM?");

  //while loop to prompt the user for a final confirmation after pressing the confirm button
  //if "Y" is selected, the program will initiate a 10 second count down and then start the stretching
  //if "N" is selected, the program will return to the previous variable selection menu
  while(!q) {
    buttonState1 = digitalRead(SELECT);
    buttonState4 = digitalRead(CONFIRM);
    if (buttonState1 != lastButtonState1) {
      if (buttonState1 == HIGH) {  
        confCounter++;
        dispFinalSelection(confCounter);
        delay(50);
      }
    } else if (buttonState4 != lastButtonState4) {
      if (buttonState4 == HIGH) {
        int sel = confCounter % 2;
        if (sel == 0) {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("CONFIRMED SETTINGS");
          for (int i = 9; i >= 0; i--) {
            lcd.setCursor(0, 1);
            lcd.print(i);
            delay(1000);
          }
          stretch();
        }
        q = true; 
      }
    }
  }
}


//Helper Function to help display the final confirmation selection
void dispFinalSelection(int c) {
  int sel = c % 2;
  lcd.setCursor(15, 2);
  if (sel == 0) {
    lcd.print("Y<- N");
  } else if (sel == 1) {
    lcd.print("Y ->N");
  }
}

///////////////////TODO
void stretch() {
  //TODO, Using MultiStepper Library
}


//display the variables in their current state
//prints a "->" for currently selected variable
//note: important to clear screen
//note: lcd library does not have "\n", so must setCursor
void displayVars() {
  int cur_selection = Counter % NUMBER_OF_VARIABLES;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Gel Len");
  if (cur_selection == 0) {
    lcd.print(" - ");
    lcd.print(gellen);
  } else {
    lcd.print("   ");
    lcd.print(gellen);
  }

  //repeat for each variable
  lcd.setCursor(0, 1);
  lcd.print("X Str %");
  if (cur_selection == 1) {
    lcd.print(" - ");
    lcd.print(stretx);
  } else {
    lcd.print("   ");
    lcd.print(stretx);
  }

  lcd.setCursor(0, 2);
  lcd.print("Y Str %");
  if (cur_selection == 2) {
    lcd.print(" - ");
    lcd.print(strety);
  } else {
    lcd.print("   ");
    lcd.print(strety);
  }
  
  lcd.setCursor(0, 3);
  lcd.print("Time hr");
  if (cur_selection == 3) {
    lcd.print(" - ");
    lcd.print(timehr);
  } else {
    lcd.print("   ");
    lcd.print(timehr);
  }
}
