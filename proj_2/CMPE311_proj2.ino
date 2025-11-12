// E.3 states that pins 2 and 3 are the outputs
#define LED1 2 
#define LED2 3 


//varibles created for timing, HL.5 the time is in msec
int ledSelect = 0;
int timing = 0;
unsigned long prevTime1 = millis();
unsigned long prevTime2 = millis(); 
long timeInt1 = 0;
long timeInt2 = 0;

int ledState1 = LOW;
int ledState2 = LOW;

//these boolean exist to control the serial monitor
  //since the loop keeps going constantly for the blinking 
  //the booleans must keep the print statements from 
  //looping forever so the user can input their values
bool flagPrint1 = true;
bool flagPrint2 = false;
bool flag3Check = true;
bool flag4Check = false;

void userControls(){
  timing = 0;

  //prints message to ask what LED
  if(flagPrint1){
    Serial.println("What LED? (1 or 2)?");
    flag3Check = true;
    flagPrint1 = false;
  }
  
  //takes user input (integer)
  if (flag3Check && Serial.available()) { 
    ledSelect = Serial.parseInt();
    if(ledSelect != 0) {
      flagPrint2 = true;
      flag3Check = false;
    }
  }

  //prints message to ask what time interval
  if(flagPrint2){
    Serial.println("What interval(in msec)?");
    flagPrint2 = false;
  }

  //takes the user input (integer)
  if (!flag3Check && Serial.available()) {
    timing = Serial.parseInt();
    if(timing != 0){
      flag4Check = true;
    }
  }
  
  //sets timeing Interval 1 to timing
  if(flag4Check && ledSelect == 1){
    timeInt1 = timing;

    if(timeInt1 < 0){
      ledState1 = LOW;
    }

    flagPrint1 = true;
    flagPrint2 = false;
    flag3Check = true;
    flag4Check = false;

    ledSelect = 0;
    timing = 0;
    
  }

  //sets timeing Interval 2 to timing
  else if(flag4Check && ledSelect == 2){
    timeInt2 = timing;

    if(timeInt2 < 0){
      ledState2 = LOW;
    }

    flagPrint1 = true;
    flagPrint2 = false;
    flag3Check = true;
    flag4Check = false;

    ledSelect = 0;
    timing = 0;
  }

  //if the user did not type the right number, the print statements reset and the LEDs are not impacted
  else if(flag4Check){
    //user did not type the right LED 
    flagPrint1 = true;
    flagPrint2 = false;
    flag3Check = true;
    flag4Check = false;

    ledSelect = 0;
    timing = 0;
  }
}

void led1Timing(){
  unsigned long currentTime = millis();
  if(timeInt1 != 0 && currentTime - prevTime1 > timeInt1){
    prevTime1 = currentTime;

    if(ledState1 == HIGH){
      ledState1 = LOW;
    }
    else {
      ledState1 = HIGH;
    }
    digitalWrite(LED1, ledState1); //updates the LED to on or off
  }
}

void led2Timing(){
  unsigned long currentTime = millis();
  if(timeInt2 != 0 && currentTime - prevTime2 > timeInt2){
    prevTime2 = currentTime;

    if(ledState2 == HIGH){
      ledState2 = LOW;
    }
    else {
      ledState2 = HIGH;
    }
    digitalWrite(LED2, ledState2);
  }  
}



void setup() {
  //sets the pinMode to output
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);

  //makes the serial monitor
  Serial.begin(9600); 
}

//create the fucntion array pointer
typedef void(*timingFunc)();
timingFunc funcList[] = {userControls, led1Timing, led2Timing};



void loop() {  
  //function array goes though all tasks
  for(int i = 0; i < 3; i++){
    funcList[i]();
  }

}
