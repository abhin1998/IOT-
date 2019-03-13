/*
 Arduino --> ThingTweet via Ethernet
 
 The ThingTweet sketch is designed for the Arduino + Ethernet Shield.
 This sketch updates a Twitter status via the ThingTweet App
 (https://thingspeak.com/docs/thingtweet) using HTTP POST.
 ThingTweet is a Twitter proxy web application that handles the OAuth.
 
 Getting Started with ThingSpeak and ThingTweet:
 
    * Sign Up for a New User Account for ThingSpeak - https://www.thingspeak.com/users/new
    * Link your Twitter account to the ThingTweet App - Apps / ThingTweet
    * Enter the ThingTweet API Key in this sketch under "ThingSpeak Settings"
  
 Arduino Requirements:
 
   * Arduino with Ethernet Shield or Arduino Ethernet
   * Arduino 1.0 IDE
   * Twitter account linked to your ThingSpeak account
   
  Network Requirements:
   * Ethernet port on Router    
   * DHCP enabled on Router
   * Unique MAC Address for Arduino
*/

#include <SPI.h>
#include <Ethernet.h>

// Local Network Settings
byte mac[] = { 0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x21 }; // Must be unique on local network
//byte ip[] = { 192, 168, 43, 154 }; //                    <------- PUT YOUR IP Address Here
//byte gateway[] = { 192, 168, 43, 1 }; //               <------- PUT YOUR ROUTERS IP Address to which your shield is connected Here
//byte subnet[] = { 255, 255, 255, 0 }; //                <------- It will be as it is in most of the cases
//EthernetServer server(8080); //                           <------- It's Defaulf Server Port for Ethernet Shield

// ThingSpeak Settings
char thingSpeakAddress[] = "api.thingspeak.com";
String thingtweetAPIKey = "RUQYJMNOS5ZXLJ1Y";

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
  
  delay(1000);
  
  // Update Twitter via ThingTweet
  updateTwitterStatus("Attending IoT Workshop by Innovians Technologies, now my things are Social @innovians");
}

void loop()
{  
  // Print Update Response to Serial Monitor
  if (client.available())
  {
    char c = client.read();
    Serial.print(c);
  }

  // Disconnect from ThingSpeak
  if (!client.connected() && lastConnected)
  {
    Serial.println("...disconnected");
    Serial.println();
    
    client.stop();
  }
    
  // Check if Arduino Ethernet needs to be restarted
  if (failedCounter > 3 ) {startEthernet();}
  
  lastConnected = client.connected();
}

void updateTwitterStatus(String tsData)
{
  if (client.connect(thingSpeakAddress, 80))
  { 
    // Create HTTP POST Data
    tsData = "api_key="+thingtweetAPIKey+"&status="+tsData;
            
    client.print("POST /apps/thingtweet/1/statuses/update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
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
