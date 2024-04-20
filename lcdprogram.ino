#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>
#include <Adafruit_Fingerprint.h>
SoftwareSerial mySerial(D3, D4);

LiquidCrystal_PCF8574 lcd(0x27);  // set the LCD address to 0x27 for a 16 chars and 2 line display
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
int show = -1;

unsigned int ent= 10;
unsigned int inc= 16;
unsigned int dec= 14;

// 2 custom characters

byte dotOff[] = { 0b00000, 0b01110, 0b10001, 0b10001,
                  0b10001, 0b01110, 0b00000, 0b00000 };
byte dotOn[] = { 0b00000, 0b01110, 0b11111, 0b11111,
                 0b11111, 0b01110, 0b00000, 0b00000 };

void setup() {
  int error;

  pinMode(ent,INPUT_PULLUP);
  pinMode(inc,INPUT_PULLUP);
  pinMode(dec,INPUT_PULLUP);

  Serial.begin(115200);
  Serial.println("LCD...");

  // wait on Serial to be available on Leonardo
  while (!Serial)
    ;

  Serial.println("Probing for PCF8574 on address 0x27...");

  // See http://playground.arduino.cc/Main/I2cScanner how to test for a I2C device.
  Wire.begin();
  Wire.beginTransmission(0x27);
  error = Wire.endTransmission();
  Serial.print("Error: ");
  Serial.print(error);

  if (error == 0) {
    Serial.println(": LCD found.");
    show = 0;
    lcd.begin(16, 2);  // initialize the lcd

    lcd.createChar(1, dotOff);
    lcd.createChar(2, dotOn);

  } else {
    Serial.println(": LCD not found.");
  }  // if
  finger.begin(57600);

}  // setup()


void loop() {
  if (show == 0) {
    lcd.setBacklight(255);
    lcd.home();
    lcd.clear();
    lcd.print("      BIKERZ      ");
    delay(1000);               

  }

  if(digitalRead(ent)==LOW)
  {
    lcd.setCursor(0,1);
   lcd.print("ent");
    delay(100);
   int fingerprintID = getFingerprintID();

  

  
  delay(50);
  if (fingerprintID == 1)
  {
    Serial.println("Welcome Debasis");
    lcd.setCursor(0, 0);
    lcd.print("Welcome Debasis         ");
    lcd.setCursor(0, 1);
    lcd.print("                       ");
    //connecthost("Debasis");


    
  }
  else if (fingerprintID == 2)
  {
    Serial.println("Welcome Manas");
    lcd.setCursor(0, 0);
    lcd.print("Welcome Manas          ");
    lcd.setCursor(0, 1);
    lcd.print("                       ");
    //connecthflag = 0;
  }
  else if (fingerprintID == 3)
  {
    Serial.println("Welcome akshay");
    lcd.setCursor(0, 0);
    lcd.print("Welcome akshy          ");
    lcd.setCursor(0, 1);
    lcd.print("                       ");
   // connecthost("Tara");delay(1000);delay(1000);
    
  }
   else if (fingerprintID == 5)
  {
    Serial.println("Welcome dharsan");
    lcd.setCursor(0, 0);
    lcd.print("Welcome dharsan        ");
    lcd.setCursor(0, 1);
    lcd.print("                       ");
   // connecthost("Tara");
   delay(1000);delay(1000);
    
  }
   else if (fingerprintID == 4)
  {
    Serial.println("Welcome sagar");
    lcd.setCursor(0, 0);
    lcd.print("Welcome sagar          ");
    lcd.setCursor(0, 1);
    lcd.print("                       ");
   // connecthost("Tara");
   delay(1000);delay(1000);
    
  }
  else
  {
    Serial.println("Waiting for valid finger!!!");
    lcd.setCursor(0, 0);
    lcd.print(" Place a Valid       ");
    lcd.setCursor(0, 1);
    lcd.print("     Finger           ");
  }
}

 else if(digitalRead(dec)==LOW)
  {
    lcd.setCursor(0,1);
    lcd.print("dec");
    delay(100);

  }
  else
  {

    lcd.setCursor(0,1);
    lcd.print("         ");
    delay(100);
  }




 // delay(1400);
}  // loop()


int getFingerprintID()
{
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;

  return finger.fingerID;





  }
