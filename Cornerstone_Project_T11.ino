// ENGR 111 Cornerstone Project Skeleton Code

#include <LiquidCrystal_I2C.h>

/**********************************************************/
LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display
/**********************************************************/

// pin assignments (2 & 3 are the only iterrupt pins)
const int tachPin = 2;
const int buttonPin = 3;
const int motorPin = A0;

// LCD settings
int displaySetting = 1;
const int maxDisplays = 5;
unsigned long lastDisplaySwitch = millis();
const int displayDelay = 250;
int flag = 0;

// YOUR GLOBAL VARIABLES SHOULD BE DECLARED HERE

int startTime = 0;
const float v = 7.125;
const int   R = 10;

float RPM;
float pwr_out;
float bld_eff;
float mtr_eff;
float sys_eff;
int breakCount;
float pwm_shaft;
float p_wind;
float A;      
float V;

void setup() {
  // initialize LCD & its backlight
  lcd.init();
  lcd.backlight();

  // initialize pushbutton for LCD toggle
  pinMode(buttonPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(buttonPin), changeDisplaySettingFlag, FALLING);

  // initialize proximity sensor
  pinMode(tachPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(tachPin), broken, FALLING);

  // initialize motor input
  pinMode(motorPin, INPUT);

  // start timer for RPM calculation
  startTime = millis();

  breakCount = 0;
}

void loop() {
 
  //YOUR CODE GOES HERE!!!
  //BE SURE TO CREATE ANY VARIABLES YOU NEED IN THE 'Global Variables' ABOVE
  //REMEMBER TO COMMENT EACH SECTION OF CODE YOU WRITE INSIDE OF THE VOID LOOP!
  /* endTime 
   *  changeTime
   *  RPM_fan
   *  startTime
   *  endTime
   *  breakCount
   */
   //*****************************************************

   // RPM calculations:
   int rotations;
   float newTime = millis();
   int calcTime = newTime - startTime;    // time used in calculation is the elapsed time minus the time of start
   
   rotations = breakCount/6;              // counts 1 rotation when all 6 fan blades pass
   RPM = rotations/(calcTime/60000);      // rotations per minute

   
   //*****************************************************

  // Electrical Power Output Calculations:
  
      A = analogRead(motorPin); 
      
      V = (5.0*A)/(1023);     
      pwr_out = (V*V)/R;
     

  //******************************************************

  // Blade Efficiency Calculations:

  
  
  float nwm_shaft = RPM;
  
  pwm_shaft = ((0.0000096068*nwm_shaft)+0.06276256)*(nwm_shaft)/9549;
  p_wind = 0.25207*(v*v*v);
  
  bld_eff = 100*(pwm_shaft/p_wind);

  //******************************************************

  // Motot Efficiency Calculations:

  mtr_eff = 100*(pwr_out/pwm_shaft);

  //******************************************************

  // System Efficiency Calculations:
  
  sys_eff = 100*(pwr_out/p_wind);

  //******************************************************

  
  if(flag == 1) 
  {
    flag = 0;
    changeDisplaySetting();
  }

  delay(1000);
  displayLCD();
}

//Call this function when you want to update the LCD Display
void displayLCD() {
  lcd.clear();
  lcd.setCursor(0, 0);
  switch(displaySetting)
  {
    case 1:
    lcd.print("Windmill RPM");
    lcd.setCursor(0, 1);
    lcd.print(RPM);
    break;
    case 2:
    lcd.print("System Power Output");
    lcd.setCursor(0, 1);
    lcd.print(pwr_out);
    break;
    case 3:
    lcd.print("Blade Efficiency");
    lcd.setCursor(0, 1);
    lcd.print(bld_eff);
    break;
    case 4:
    lcd.print("Motor Efficiency");
    lcd.setCursor(0, 1);
    lcd.print(mtr_eff);
    break;
    case 5:
    lcd.print("System Efficiency");
    lcd.setCursor(0, 1);
    lcd.print(sys_eff);
    break;
    default:
    lcd.print("Unknown Setting!");
  }
}

void changeDisplaySettingFlag() {
    flag = 1;
}

void changeDisplaySetting() {
    if(lastDisplaySwitch + displayDelay < millis()) { // this limits how quickly the LCD Display can switch
    lastDisplaySwitch = millis();
    displaySetting++;
    if(displaySetting > maxDisplays) {
      displaySetting = 1;
    }
    displayLCD();
  }
}

void broken() {
  breakCount++;
}
