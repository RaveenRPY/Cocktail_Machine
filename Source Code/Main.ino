
//--------------------------- 74HC595 Configs ------------------------------

int SER_Pin = 2;
int RCLK_Pin = 3;
int SRCLK_Pin = 4;

#define number_of_74hc595s 1
#define numOfRegisterPins number_of_74hc595s * 8

boolean registers[numOfRegisterPins];

//--------------------------- I2C LCD Configs ------------------------------

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 16, 2);

//--------------------------- KeyPad Configs ------------------------------

#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};

byte rowPins[ROWS] = { 12, 11, 10, 9 };
byte colPins[COLS] = { 8, 7, 6, 5 };

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

//----------------------------- IR Sensor ---------------------------------

#define IR 13
int preIR = 1;

//----------------------------- Relay Module ------------------------------

#define LimeJuice 14
#define SimpleSyrup 15
#define Gin 16
#define WhiteRum 17
#define SodaWater 0

////------------------------------- LEDs ----------------------------------

#define LimeJuiceLED 2
#define SimpleSyrupLED 3
#define GinLED 4
#define WhiteRumLED 5
#define SodaWaterLED 6

//-------------------------------------------------------------------------

char *recipies[4] = { "Gin Gimlet", "Classic Daiquiri", "Classic Mojito", "Lime Rickey" };
char *ingred[5] = { "Lime Juice", "Simple Syrup", "Gin", "White Rum", "Soda Water" };
int pins[5] = { 14, 15, 16, 17, 0 };
int Leds[5] = { 2, 3, 4, 5, 6 };

#define buzzer 1
#define volume 300  // Net volume of a Cup

int calibTime = (22800 / 500) * volume;  // Calibrated Filling Time for 500 ml

//-------------------------------------------------------------------------

void setup() {
  pinMode(SER_Pin, OUTPUT);
  pinMode(RCLK_Pin, OUTPUT);
  pinMode(SRCLK_Pin, OUTPUT);

  pinMode(IR, INPUT);

  for (int i = 0; i < 4; i++) {
    pinMode(pins[i], OUTPUT);
  }

  for (int i = 0; i < 4; i++) {
    digitalWrite(pins[i], 1);
  }

  Serial.begin(9600);

  clearRegisters();
  writeRegisters();

  setRegisterPin(SodaWater, 1);
  setRegisterPin(buzzer, 0);
  writeRegisters();

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("~SMART COCKTAIL~");
  lcd.setCursor(0, 1);
  lcd.print("____MACHINE_____");

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 5; j++) {
      setRegisterPin(Leds[j], 1);
      writeRegisters();
      delay(300);
      setRegisterPin(Leds[j], 0);
      writeRegisters();
    }
  }

  delay(3000);
  lcd.clear();
}

//---------------------------------------------------------------

void clearRegisters() {
  for (int i = numOfRegisterPins - 1; i >= 0; i--) {
    registers[i] = LOW;
  }
}

void writeRegisters() {

  digitalWrite(RCLK_Pin, LOW);

  for (int i = numOfRegisterPins - 1; i >= 0; i--) {
    digitalWrite(SRCLK_Pin, LOW);

    int val = registers[i];

    digitalWrite(SER_Pin, val);
    digitalWrite(SRCLK_Pin, HIGH);
  }
  digitalWrite(RCLK_Pin, HIGH);
}

void setRegisterPin(int index, int value) {
  registers[index] = value;
}

//----------------------------- Recipie Functions ------------------------------

void GinGimlet() {  //#A - Gin Gimlet

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Processing...");
  lcd.setCursor(0, 1);
  lcd.print(recipies[0]);

  setRegisterPin(GinLED, 1);
  writeRegisters();
  digitalWrite(Gin, 0);
  delay(calibTime * (50 / 100.0));
  digitalWrite(Gin, 1);
  setRegisterPin(GinLED, 0);
  writeRegisters();

  setRegisterPin(LimeJuiceLED, 1);
  writeRegisters();
  digitalWrite(LimeJuice, 0);
  delay(calibTime * (20 / 100.0));
  digitalWrite(LimeJuice, 1);
  setRegisterPin(LimeJuiceLED, 0);
  writeRegisters();

  setRegisterPin(SimpleSyrupLED, 1);
  writeRegisters();
  digitalWrite(SimpleSyrup, 0);
  delay(calibTime * (20 / 100.0));
  digitalWrite(SimpleSyrup, 1);
  setRegisterPin(SimpleSyrupLED, 0);
  writeRegisters();

  setRegisterPin(SodaWaterLED, 0);
  writeRegisters();
  setRegisterPin(SodaWater, 0);
  writeRegisters();
  delay(calibTime * (10 / 100.0));
  setRegisterPin(SodaWater, 1);
  writeRegisters();
  setRegisterPin(SodaWaterLED, 0);
  writeRegisters();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Finish You Order..");

  setRegisterPin(buzzer, 1);
  writeRegisters();
  delay(500);
  setRegisterPin(buzzer, 0);
  writeRegisters();

  delay(2000);
  lcd.clear();
}

void ClassicDaiquiri() {  //#B - Classic Daiquiri

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Processing...");
  lcd.setCursor(0, 1);
  lcd.print(recipies[1]);

  setRegisterPin(WhiteRumLED, 0);
  writeRegisters();
  digitalWrite(WhiteRum, 0);
  delay(calibTime * (40 / 100.0));
  digitalWrite(WhiteRum, 1);
  setRegisterPin(WhiteRumLED, 0);
  writeRegisters();

  setRegisterPin(LimeJuiceLED, 0);
  writeRegisters();
  digitalWrite(LimeJuice, 0);
  delay(calibTime * (20 / 100.0));
  digitalWrite(LimeJuice, 1);
  setRegisterPin(LimeJuiceLED, 0);
  writeRegisters();

  setRegisterPin(SimpleSyrupLED, 0);
  writeRegisters();
  digitalWrite(SimpleSyrup, 0);
  delay(calibTime * (40 / 100.0));
  digitalWrite(SimpleSyrup, 1);
  setRegisterPin(SimpleSyrupLED, 0);
  writeRegisters();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Finish You Order..");

  setRegisterPin(buzzer, 1);
  writeRegisters();
  delay(500);
  setRegisterPin(buzzer, 0);
  writeRegisters();

  delay(2000);
  lcd.clear();
}

void ClassicMojito() {  //#C - Classic Mojito

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Processing...");
  lcd.setCursor(0, 1);
  lcd.print(recipies[2]);

  setRegisterPin(LimeJuiceLED, 0);
  writeRegisters();
  digitalWrite(LimeJuice, 0);
  delay(calibTime * (35 / 100.0));
  digitalWrite(LimeJuice, 1);
  setRegisterPin(LimeJuiceLED, 0);
  writeRegisters();

  setRegisterPin(WhiteRumLED, 0);
  writeRegisters();
  digitalWrite(WhiteRum, 0);
  delay(calibTime * (15 / 100.0));
  digitalWrite(WhiteRum, 1);
  setRegisterPin(WhiteRumLED, 0);
  writeRegisters();

  setRegisterPin(SimpleSyrupLED, 0);
  writeRegisters();
  digitalWrite(SimpleSyrup, 0);
  delay(calibTime * (30 / 100.0));
  digitalWrite(SimpleSyrup, 1);
  setRegisterPin(SimpleSyrupLED, 0);
  writeRegisters();

  setRegisterPin(SodaWaterLED, 0);
  writeRegisters();
  setRegisterPin(SodaWater, 0);
  writeRegisters();
  delay(calibTime * (20 / 100.0));
  setRegisterPin(SodaWater, 1);
  writeRegisters();
  setRegisterPin(SodaWaterLED, 0);
  writeRegisters();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Finish You Order..");

  setRegisterPin(buzzer, 1);
  writeRegisters();
  delay(500);
  setRegisterPin(buzzer, 0);
  writeRegisters();

  delay(2000);
  lcd.clear();
}

void LimeRickey() {  //#D - Lime Rickey

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Processing...");
  lcd.setCursor(0, 1);
  lcd.print(recipies[3]);

  setRegisterPin(GinLED, 0);
  writeRegisters();
  digitalWrite(Gin, 0);
  delay(calibTime * (20 / 100.0));
  digitalWrite(Gin, 1);
  setRegisterPin(GinLED, 0);
  writeRegisters();

  setRegisterPin(SodaWaterLED, 0);
  writeRegisters();
  setRegisterPin(SodaWater, 0);
  writeRegisters();
  delay(calibTime * (10 / 100.0));
  setRegisterPin(SodaWater, 1);
  writeRegisters();
  setRegisterPin(SodaWaterLED, 0);
  writeRegisters();

  setRegisterPin(LimeJuiceLED, 0);
  writeRegisters();
  digitalWrite(LimeJuice, 0);
  delay(calibTime * (70 / 100.0));
  digitalWrite(LimeJuice, 1);
  setRegisterPin(LimeJuiceLED, 0);
  writeRegisters();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Finish You Order..");

  setRegisterPin(buzzer, 1);
  writeRegisters();
  delay(500);
  setRegisterPin(buzzer, 0);
  writeRegisters();

  delay(2000);
  lcd.clear();
}

//---------------------------------------------------------------------------

long getManual() {

  long value = 0;  // the number accumulator
  long keyvalue;   // the key pressed at current moment
  int isnum;

  lcd.setCursor(15, 0);
  lcd.print("%");
  lcd.setCursor(12, 0);

  do {
    keyvalue = customKeypad.getKey();  // input the key
    if (Serial.available()) {
      keyvalue = Serial.read();
    }
    isnum = (keyvalue >= '0' && keyvalue <= '9');  // is it a digit?
    if (isnum) {
      lcd.print(keyvalue - '0');

      value = value * 10 + keyvalue - '0';  // accumulate the input number
    }

  } while (isnum || !keyvalue);  // until not a digit or while no key pressed
  return value;
}

//---------------------------------------------------------------------------

char type = 0;
char start = 0;
int mix = 0;

//---------------------------------------------------------------------------

void loop() {

  char mode = customKeypad.getKey();
  int IR_val = digitalRead(13);

  int *manualMix[5];

  lcd.setCursor(0, 0);
  lcd.print("1) Auto Mode");
  lcd.setCursor(0, 1);
  lcd.print("2) Manual Mode");

  while ((!mode) && (!Serial.available())) {
    mode = customKeypad.getKey();
    if (Serial.available()) {
      mode = Serial.read();
    }
  }

  switch (mode) {

    //--------------------------------- AUTO Mode -------------------------------
    case '1':
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("What you want ?");
      lcd.setCursor(1, 1);
      lcd.print("A / B / C / D");

      type = customKeypad.getKey();

      while ((!type) && (!Serial.available())) {
        type = customKeypad.getKey();
        IR_val = digitalRead(13);
        if (Serial.available()) {
          type = Serial.read();
        }
      }

      if (type) {
        lcd.clear();

        while (IR_val != 0) {
          IR_val = digitalRead(13);

          lcd.setCursor(0, 0);
          lcd.print("Please insert");
          lcd.setCursor(0, 1);
          lcd.print("a Cup...");
        }

        if ((type == 'A') || (type == 'B') || (type == 'C') || (type == 'D')) {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("You want :");
          lcd.setCursor(11, 0);
          lcd.print(type);
          delay(1000);

          switch (type) {
            case 'A':
              GinGimlet();
              break;
            case 'B':
              ClassicDaiquiri();
              break;
            case 'C':
              ClassicMojito();
              break;
            case 'D':
              LimeRickey();
              break;
          }
        } else {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Invalid Input !");
          delay(2000);
        }
      }
      break;

    //--------------------------------- MANUAL Mode -------------------------------
    case '2':
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("You have select");
      lcd.setCursor(2, 1);
      lcd.print("Manual Mode");
      delay(2000);
      lcd.clear();

      lcd.setCursor(0, 0);
      lcd.print("Your cup volume");
      lcd.setCursor(3, 1);
      lcd.print("is 300 ml");
      delay(3000);
      lcd.clear();

      lcd.setCursor(0, 0);
      lcd.print("Enter you need");
      lcd.setCursor(0, 1);
      lcd.print("as Precentage %");
      delay(3000);
      lcd.clear();

      int mixCount = 0;

      for (int i = 0; i < 5; i++) {

        lcd.setCursor(0, 0);
        lcd.print(ingred[i]);

        long mix = getManual();
        mixCount += mix;

        if (mixCount > 100) {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Volume Exceeded");
          lcd.setCursor(0, 1);
          lcd.print("!!!!!!!!!!!!!!!!");

          setRegisterPin(buzzer, 1);
          writeRegisters();
          delay(500);
          setRegisterPin(buzzer, 0);
          writeRegisters();
          delay(500);
          setRegisterPin(buzzer, 1);
          writeRegisters();
          delay(500);
          setRegisterPin(buzzer, 0);
          writeRegisters();
          delay(500);

          break;
        }
        manualMix[i] = mix;
        lcd.clear();
      }

      if (mixCount > 100) {
        lcd.clear();
        break;
      }

      start = customKeypad.getKey();

      if (Serial.available()) {
        start = Serial.read();
      }

      lcd.clear();
      lcd.setCursor(5, 0);
      lcd.print("START ~");
      lcd.setCursor(0, 1);
      lcd.print("(Press * Button))");

      while ((!start) && (!Serial.available())) {
        start = customKeypad.getKey();
        IR_val = digitalRead(13);

        if (Serial.available()) {
          start = Serial.read();
        }
      }

      if (start == '*') {

        lcd.clear();

        while (IR_val != 0) {
          IR_val = digitalRead(13);
          lcd.setCursor(0, 0);
          lcd.print("Please insert");
          lcd.setCursor(0, 1);
          lcd.print("a Cup...");
        }

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Processing");
        lcd.setCursor(0, 1);
        lcd.print("Your Choice....");

        for (int j = 0; j < 4; j++) {
          digitalWrite(pins[j], 0);
          setRegisterPin(Leds[j], 1);
          writeRegisters();
          int mix = manualMix[j];
          delay(calibTime * (mix / 100.0));
          digitalWrite(pins[j], 1);
          setRegisterPin(Leds[j], 0);
          writeRegisters();
          delay(1000);
        }
        setRegisterPin(pins[4], 0);
        setRegisterPin(Leds[4], 1);
        writeRegisters();
        int mix = manualMix[4];
        delay(calibTime * (mix / 100.0));
        setRegisterPin(pins[4], 1);
        setRegisterPin(Leds[4], 0);
        writeRegisters();
        delay(1000);

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Finish You Order..");

        delay(500);
      }

      else {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Declined By User !");
      }

      setRegisterPin(buzzer, 1);
      writeRegisters();
      delay(500);

      setRegisterPin(buzzer, 0);
      writeRegisters();

      delay(1000);
      lcd.clear();
      break;

      //-----------------------------------------------------------------------------
    case '3':
      break;
  }
}