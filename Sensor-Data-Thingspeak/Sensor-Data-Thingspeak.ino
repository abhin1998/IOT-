#include <SPI.h>
#include <Ethernet.h>
#include <dht11.h>
#include <Wire.h>
#define DHT11PIN 5  // The Temperature/Humidity sensor
dht11 DHT11;

// Local Network Settings
byte mac[] = { 0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x21 }; // Must be unique on local network
// ThingSpeak Settings
char thingSpeakAddress[] = "api.thingspeak.com";
String writeAPIKey = "R1URNNY1B3209G1M";
const int updateThingSpeakInterval = 16 * 1000; // Time interval in milliseconds to update ThingSpeak (number of seconds * 1000 = interval)
// Variable Setup
long lastConnectionTime = 0;
boolean lastConnected = false;
int failedCounter = 0;
// Initialize Arduino Ethernet Client
EthernetClient client;
void setup()
{
// Start Serial for debugging on the Serial Monitor
Serial.begin(9600);
// Start Ethernet on Arduino
startEthernet();
}
void loop()
{
// Read value from Analog Input Pin 0
String analogPin0 = String(analogRead(A0), DEC);
// Print Update Response to Serial Monitor
if (client.available())
{
char c = client.read();
Serial.print(c);
}
//------DHT11--------
int chk = DHT11.read(DHT11PIN);
char t_buffer[10];
char h_buffer[10];
float t=(DHT11.temperature);
String temp=dtostrf(t,0,5,t_buffer);
//Serial.print(temp);
//Serial.print(" ");
float h=(DHT11.humidity);
String humid=dtostrf(h,0,5,h_buffer);
//Serial.println(humid);
//delay(16000);

// Disconnect from ThingSpeak
if (!client.connected() && lastConnected)
{
Serial.println("...disconnected");
Serial.println();
client.stop();
}
// Update ThingSpeak
if(!client.connected() && (millis() - lastConnectionTime > updateThingSpeakInterval))
{
updateThingSpeak("field1="+temp+"&field2="+humid);
}
// Check if Arduino Ethernet needs to be restarted
if (failedCounter > 3 ) {startEthernet();}
lastConnected = client.connected();
}
void updateThingSpeak(String tsData)
{
if (client.connect(thingSpeakAddress, 80))
{
client.print("POST /update HTTP/1.1\n");
client.print("Host: api.thingspeak.com\n");
client.print("Connection: close\n");
client.print("X-THINGSPEAKAPIKEY: "+writeAPIKey+"\n");
client.print("Content-Type: application/x-www-form-urlencoded\n");
client.print("Content-Length: ");
client.print(tsData.length());
client.print("\n\n");
client.print(tsData);
lastConnectionTime = millis();
if (client.connected())
{
Serial.println("Connecting to ThingSpeak...");
Serial.println();
failedCounter = 0;
}
else
{
failedCounter++;
Serial.println("Connection to ThingSpeak failed ("+String(failedCounter, DEC)+")");
Serial.println();
}
}
else
{
failedCounter++;
Serial.println("Connection to ThingSpeak Failed ("+String(failedCounter, DEC)+")");
Serial.println();
lastConnectionTime = millis();
}
}
void startEthernet()
{
client.stop();
Serial.println("Connecting Arduino to network...");
Serial.println();
delay(1000);
// Connect to network amd obtain an IP address using DHCP
if (Ethernet.begin(mac) == 0)
{
Serial.println("DHCP Failed, reset Arduino to try again");
Serial.println();
}
else
{
Serial.println("Arduino connected to network using DHCP");
Serial.println();
}
delay(1000);
}
