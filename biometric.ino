#include <Adafruit_Fingerprint.h>
#include <ESP8266WiFi.h>
#include <LiquidCrystal_PCF8574.h>
LiquidCrystal_PCF8574 lcd(0x27);

SoftwareSerial mySerial(D3, D4);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

const char* ssid     = "admin";   //replace with your own SSID
const char* password = "12345678";    //replace with your own password
const char* host = "api.pushingbox.com";

unsigned int ent= 10;

String member = "";
int flag = 0;
void setup()
{
  lcd.begin(16, 2);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(4, 0);
  lcd.print("WELCOME");
  delay(2000);

  lcd.clear();

  Serial.begin(115200);
  delay(10);
  Serial.println();
  Serial.println();
  lcd.setCursor(0, 0);
  Serial.print("Connecting to WiFi...       ");
  Serial.print("Connecting to ");
  Serial.println(ssid);
  //WiFi.mode(WIFI_STA);
  //WiFi.begin(ssid, password);
/*
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

 //// Serial.println("");
 // Serial.println("WiFi connected");
 // Serial.println("IP address: ");
 // Serial.println(WiFi.localIP());



  lcd.setCursor(0, 0);
  lcd.print("WiFi connected          ");
  lcd.setCursor(0, 1);
  lcd.print("IP:");
  lcd.setCursor(4, 1);
  lcd.print(WiFi.localIP());
  delay(1500);

  while (!Serial);
  delay(100);
  Serial.println("\n\n Waiting for Fingerprint Sensor");
  lcd.setCursor(0, 0);
  lcd.print("    Waiting for           ");
  lcd.setCursor(0, 1);
  lcd.print("      Sensor              ");    */
  delay(1500);
  finger.begin(57600);
  pinMode(ent,INPUT_PULLUP);
}

void loop()
{


if(digitalRead(ent)==LOW)
  {
   lcd.setCursor(0,1);
   lcd.print("ent");
   delay(100);
   int fingerprintID = getFingerprintID();

  }

  
  delay(50);
  if (fingerprintID == 1)
  {
    Serial.println("Welcome Debasis");
    lcd.setCursor(0, 0);
    lcd.print("Welcome Debasis         ");
    lcd.setCursor(0, 1);
    lcd.print("                       ");
    //connecthost("Debasis");
    flag = 0;
  }
  else if (fingerprintID == 2)
  {
    Serial.println("Welcome Manas");
    lcd.setCursor(0, 0);
    lcd.print("Welcome Manas          ");
    lcd.setCursor(0, 1);
    lcd.print("                       ");
    //connecthost("Manas");
    flag = 0;
  }
  else if (fingerprintID == 3)
  {
    Serial.println("Welcome Tara");
    lcd.setCursor(0, 0);
    lcd.print("Welcome Tara           ");
    lcd.setCursor(0, 1);
    lcd.print("                       ");
   // connecthost("Tara");
    flag = 0;
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

void connecthost(String data)
{
  if (flag == 0)
  {
    member = data;
    flag = 1;
    Serial.print("connecting to ");
    Serial.println(host);
    //WiFiClient client;
    const int httpPort = 80;

    if (!client.connect(host, httpPort)) 
    {
      Serial.println("connection failed");
      return;
    }

    // We now create a URL for the request
    String url = "/pushingbox?";
    url += "devid=";
    url += "v810401C3XXXXX";
    url += "&Name=" + String(member);

    Serial.print("Requesting URL: ");
    Serial.println(url);
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n\r\n");
    unsigned long timeout = millis();
    while (client.available() == 0) {
      if (millis() - timeout > 5000) {
        Serial.println(">>> Client Timeout !");
        client.stop();
        return;
      }
    }
    while (client.available()) {
      String line = client.readStringUntil('\r');
      Serial.print(line);
      Serial.print("Data Sent!");
    }

    Serial.println();
    Serial.println("closing connection");
  }
}
