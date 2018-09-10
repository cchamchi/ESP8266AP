#include <ESP8266WiFi.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 0  // GPIO0
Adafruit_SSD1306 display(OLED_RESET);

const char* ssid     = "RaspAP_01";
const char* password = "1234asdf";

IPAddress local_IP(192,168,5,1);
IPAddress gateway(192,168,5,100);
IPAddress subnet(255,255,255,0);

void setup()
{

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  // Clear the buffer.
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.setTextColor(WHITE);  // Clear the buffer.  
  
  Serial.begin(115200);
  Serial.println();

  
  //Serial.print("Setting soft-AP configuration ... ");
  //Serial.println(WiFi.softAPConfig(local_IP, gateway, subnet) ? "Ready" : "Failed!");
  Serial.print("Setting soft-AP ... ");
  Serial.println(WiFi.softAP(ssid,password) ? "Ready" : "Failed!");


  display.println("Start AP");
  display.println(ssid);
  display.println(password);
  display.println(WiFi.softAPIP());
  display.display();
  
  
}

void loop()
{
  int num=WiFi.softAPgetStationNum();
  Serial.printf("Stations connected = %d\n",num );
  display.setCursor(0, 5*8);
  display.setTextColor(WHITE, BLACK);
  display.print("          ");
  display.setCursor(0, 5*8);
  display.setTextColor(WHITE);  
  display.printf("station=%d", num);
  display.display();
  delay(3000);
}
