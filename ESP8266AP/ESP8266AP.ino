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

struct station_info *stat_info;
struct ip_addr *IPaddress;
IPAddress address;

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

  display.println(ssid);
  display.println(password);
  display.println(WiFi.softAPIP());
  display.display();
  
  
}

void loop()
{
  int num=WiFi.softAPgetStationNum();

  if(num<1){
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println(ssid);
    display.println(password);
    display.println(WiFi.softAPIP());
    display.println(" ");
    display.print("No station");
    display.display();
    
  }else{
  
    Serial.printf("Stations connected = %d\n",num );
    dumpClients();

    display.clearDisplay();
    display.setCursor(0, 0);
     
    display.printf("station=%d", num);
    dumpClientsOLED();
    display.display();

  }
  delay(3000);

  
}

void dumpClients()
{
  Serial.print(" Clients:\r\n");
  stat_info = wifi_softap_get_station_info();
  while (stat_info != NULL)
  {
    IPaddress = &stat_info->ip;
    address = IPaddress->addr;

    Serial.print("\t");
    Serial.print(address);
    Serial.print("\r\n");
    stat_info = STAILQ_NEXT(stat_info, next);
  } 
}

void dumpClientsOLED()
{
  
  
  stat_info = wifi_softap_get_station_info();
  display.setCursor(0, 8);
  display.print(address[0]);display.print(".");display.print(address[1]);display.print(".");display.print(address[2]);
  display.setCursor(0, 2*8);
  while (stat_info != NULL)
  {
    IPaddress = &stat_info->ip;
    address = IPaddress->addr;   
    display.print(".");display.print(address[3]);display.print(" ");
    stat_info = STAILQ_NEXT(stat_info, next);
    
  } 
}
