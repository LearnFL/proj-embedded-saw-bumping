// THIS SOFTWARE HAS BEEN WRITTEN BY DENNIS ROTNOV
// INITIAL DRAFT, REQUIRES A TUNE UP
// 5-4-22 Updated bounceButtonTimer(600) old value was 300 to address static or floating voltage
// 5-5-22 Updated Selector and Activator functions to fix static and false signals by checking after a delay if the button is pressed. Should have done this on 5/4/22
// 5-5-22 bounceButtonTimer(400)
// 5-11-22 Updated tempConversion = ((tempReading/205)*100)-50 since used new sensor for TMP36

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <NoDelay.h>

#define SCREEN_WIDTH 128  // OLED display width,  in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels
#define selectorButton 2  // Solenoid timer selector pin
#define solenoidOutput 12 // Gives power to solenoid driver board, controlled by a timer if Pin3 has been activated
#define activatorButton 3 // Activates or deactivates solenoid
#define tempLED 7         // Red LED for temperature alert

float tempReading;
float tempConversion;
const int tempPin = A1;    // Temperature sensor Pin
volatile uint8_t buttonState = 0;    // Reads button state
volatile uint8_t activatorFlag = 0;  // Tracks botton on pin 3
char* status[] = {"OFF", "ON"};      // Read out on the screen controlled by activity on Pin 3

noDelay bounceButtonTimer(400);      // None blovcing delay for a button debounce
noDelay temperatureTimer(3000);      // None blovcing delay for a button debounce

Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1); // declare an SSD1306 display object connected to I2C

void setup() {
  // Pin setup
  pinMode(selectorButton,INPUT_PULLUP);
  pinMode(activatorButton,INPUT_PULLUP);
  pinMode(solenoidOutput, OUTPUT);
  pinMode(tempLED, OUTPUT);
  pinMode(activatorButton,INPUT_PULLUP);
  digitalWrite(solenoidOutput, 0);        // Initiallly pin is LOW
  digitalWrite(tempLED, 0);               // Initiallly pin is LOW
  attachInterrupt(digitalPinToInterrupt(selectorButton), updateSelector, FALLING);    // Interrupt setup  
  attachInterrupt(digitalPinToInterrupt(activatorButton), updateActivator, FALLING);  // Interrupt setup 
  
  Serial.begin (9600); // For troubleshooting
   
  //initialize OLED display with address 0x3C for 128x64
  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true);
  }
  oled.clearDisplay();        // clear display
  oled.setTextSize(2);        // text size
  oled.setTextColor(WHITE);   // text color
  oled.setCursor(0, 10);      // position to display
  oled.println(status[0]);    // text to display
  oled.setCursor(0, 40);      // position to display
  oled.println(buttonState);  // text to display
  oled.setCursor(30, 40);     // position to display
  oled.println("min");        // text to display
  oled.display();             // show on OLED
}  

void loop() {
  screenUpdate(buttonState);
}

// Function controls timer selection and works with attachInterrupt
void updateSelector(){
  if (buttonState < 60){
    if(bounceButtonTimer.update()){
      if(digitalRead(selectorButton) == 0){
        buttonState = buttonState + 15;
      }
    }
  } 
  else{
    buttonState = 0;
  }
  Serial.println(buttonState);
}

//Function updates OLED screen and calls solenoid function
void screenUpdate(int buttonState){
  int i;
  if (activatorFlag == 1){
    i = 1;
  }
  else{
    i = 0;
  }

  oled.clearDisplay();          // clear display
  oled.setTextSize(2);          // text size
  oled.setTextColor(WHITE);     // text color
  oled.setCursor(0, 10);        // position to display
  oled.println(status[i]);      // text to display
  oled.setCursor(0, 40);        // position to display
  oled.println(buttonState);    // text to display
  oled.setCursor(30, 40);       // position to display
  oled.println("min");          // text to display
  temperatureSensor();          // Temperature
  oled.display();               // show on OLED

  if(i == 1 && buttonState > 0){
    solenoid();
  }
}

// Function activates/deactivates solenoid Pin12 and works with attachInterrupt
// if in ON postion, only then solenoid Pin12 can function
void updateActivator(){
  if(bounceButtonTimer.update()){
    if (digitalRead(activatorButton) == 0){
      if (activatorFlag == 0){
        activatorFlag = 1;
      }
      else{
        activatorFlag = 0;
      }
    }
  }
}

//Function controls solenoid work
void solenoid(){
  if (buttonState > 0 && activatorFlag == 1){
    digitalWrite(solenoidOutput, HIGH);
    delay(3000);
    digitalWrite(solenoidOutput, LOW);
    // For loop is used to perform multiple temperature checks during DELAY function, this way temperature is checked more often
    for (int i=0; i<15; i++){
      temperatureSensor();   
      delay((buttonState*60000)/15);    // 60000 milli seconds in each minute
    }
  }
  else{
    digitalWrite(solenoidOutput, LOW);
  }
}

// Function that reads temperature
void temperatureSensor(){
  tempReading = analogRead(tempPin);  // Read analog volt from sensor 
  //tempConversion = tempReading*0.488; // convert the analog volt to its temperature equivalent
  tempConversion = ((tempReading/205)*100)-50; //TMP36
  if (tempConversion >= 45){          // Temp over 45 degreeS *C will activate red LED
    digitalWrite(tempLED, 1);
  }
  else{
    digitalWrite(tempLED, 0);
  }

  // Used to display temperature on OLED
  int i;
  if (activatorFlag == 1){
    i = 1;
  }
  else{
    i = 0;
  }
  oled.clearDisplay();          // clear display
  oled.setTextSize(2);          // text size
  oled.setTextColor(WHITE);     // text color
  oled.setCursor(0, 10);        // position to display
  oled.println(status[i]);      // text to display
  oled.setCursor(0, 40);        // position to display
  oled.println(buttonState);    // text to display
  oled.setCursor(30, 40);       // position to display
  oled.println("min");          // text to display
  oled.setTextSize(2);            // text size
  oled.setTextColor(WHITE);       // text color
  oled.setCursor(60, 10);         // position to display
  oled.println(int(tempConversion));      // text to display
  oled.setCursor(95, 10);         // position to display
  oled.println("C");              // text to display
  oled.display();                 // show on OLED
  
  // For troubleshooting temperature function AND/OR sensor uncomment following lines: 
  //Serial.print("TEMPERATURE *C = ");
  //Serial.print(tempConversion); // display temperature value
  //Serial.println();
}
