
//for use with IDE 1.0
//open serial monitor to see what the arduino receives
//use the \ slash to escape the " in the html
//for use with W5100 based ethernet shields
 
#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x21 }; // <------- PUT YOUR MAC Address Here
byte ip[] = { 192, 168, 43, 237  }; //                    <------- PUT YOUR IP Address Here
byte gateway[] = { 192, 168, 43, 1 }; //               <------- PUT YOUR ROUTERS IP Address to which your shield is connected Here
byte subnet[] = { 255, 255, 255, 0 }; //                <------- It will be as it is in most of the cases
EthernetServer server(80); //                           <------- It's Defaulf Server Port for Ethernet Shield
 
String readString;
 
//////////////////////
 
void setup()
{  
 
  pinMode(6, OUTPUT); // Pin Assignment through which relay will be controlled
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  
  
  //start Ethernet
  
  Ethernet.begin(mac, ip, gateway, subnet);
  server.begin();
  
  //enable serial data print
  
  Serial.begin(9600);
  Serial.println("server LED test 1.0"); // so that we can know what is getting loaded
}
 
void loop()
{  
   
  
  // Create a client connection
 
  EthernetClient client = server.available();
  if (client) {
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
 
        
        //read char by char HTTP request
        if (readString.length() < 100) {
 
          //store characters to string
          readString += c;
          //Serial.print(c);
        }
 
        //if HTTP request has ended
        if (c == '\n') {
 
          ///////////////
          Serial.println(readString); //print to serial monitor for debuging
 
          /* Start OF HTML Section. Here Keep everything as it is unless you understands its working */
          
          client.println("HTTP/1.1 200 OK"); //send new page
          client.println("Content-Type: text/html");
          client.println();
          //client.println("<meta http-equiv=\"refresh\" content=\"5\">");
 
          client.println("<HTML>");
          client.println("<HEAD>");
          client.println("<meta name='apple-mobile-web-app-capable' content='yes' />");
          client.println("<meta name='apple-mobile-web-app-status-bar-style' content='black-translucent' />");
          client.println("<link rel=\"stylesheet\" type=\"text/css\" href=\"http://innovianstechnologies.com/iot123/autohome.css\" />");
          
          
          client.println("</HEAD>");
          client.println("<body bgcolor=\"#D0D0D0\">");
          
          client.println("<hr/>");
          client.println("<hr/>");
          client.println("<h4><center><img border=\"2\" src=\"http://innovianstechnologies.com/iot123/Logo.jpg\" /></center></h4>");
          client.println("<hr/>");
          client.println("<hr/>");
          
          client.println("<br />");
          client.println("<br />");
          client.println("<br />");
          client.println("<br />");
          client.println("<br />");
         
         // Relay Control Code
          client.println("<a href=\"/?relay1on\"\">Turn On Light 1</a>");
          client.println("<a href=\"/?relay1off\"\">Turn Off Light 1</a><br />"); 
          
          client.println("<br />");
          client.println("<br />");
          client.println("<br />");
          client.println("<br />");
          
          client.println("<a href=\"/?relay2on\"\">Turn On Light 2</a>");
          client.println("<a href=\"/?relay2off\"\">Turn Off Light 2</a><br />");
          
          client.println("<br />");
          client.println("<br />");
          client.println("<br />");
          client.println("<br />");
          
          client.println("<a href=\"/?relay3on\"\">Turn On Light 3</a>");
          client.println("<a href=\"/?relay3off\"\">Turn Off Light 3</a><br />");
          
          client.println("<br />");
          client.println("<br />");
          client.println("<br />");
          client.println("<br />");
          
          client.println("<a href=\"/?relay4on\"\">Turn On Light 4</a>");
          client.println("<a href=\"/?relay4off\"\">Turn Off Light 4</a><br />");
 
          client.println("<br />");
          client.println("<br />");
          
          
          
         
            // control arduino pin via ethernet Start //
          
          
          if(readString.indexOf("?relay1on") >0)//checks for on
          {
            digitalWrite(6, HIGH);    // set pin 4 high
            Serial.println("Led On");
            client.println("<link rel='apple-touch-icon' href='http://chriscosma.co.cc/on.png' />");
            //client.println("Light 1 Is On");
            client.println("<br />");
        }
          else{
          if(readString.indexOf("?relay1off") >0)//checks for off
          {
            digitalWrite(6, LOW);    // set pin 4 low
            Serial.println("Led Off");
            client.println("<link rel='apple-touch-icon' href='http://chriscosma.co.cc/off.png' />");
            //client.println("Light 1 Is Off");
            client.println("<br />");
        }
          }
          
          if(readString.indexOf("?relay2on") >0)//checks for on
          {
            digitalWrite(7, HIGH);    // set pin 4 high
            Serial.println("Led On");
            client.println("<link rel='apple-touch-icon' href='http://chriscosma.co.cc/on.png' />");
            //client.println("Light 2 Is On");
            client.println("<br />");
          }
          else{
          if(readString.indexOf("?relay2off") >0)//checks for off
          {
            digitalWrite(7, LOW);    // set pin 4 low
            Serial.println("Led Off");
            client.println("<link rel='apple-touch-icon' href='http://chriscosma.co.cc/off.png' />");
            //client.println("Light 2 Is Off");
            client.println("<br />");
          }
          }
          
           if(readString.indexOf("?relay3on") >0)//checks for on
          {
            digitalWrite(8, HIGH);    // set pin 4 high
            Serial.println("Led On");
            client.println("<link rel='apple-touch-icon' href='http://chriscosma.co.cc/on.png' />");
           // client.println("Light 3 Is On");
            client.println("<br />");
          }
          else{
          if(readString.indexOf("?relay3off") >0)//checks for off
          {
            digitalWrite(8, LOW);    // set pin 4 low
            Serial.println("Led Off");
            client.println("<link rel='apple-touch-icon' href='http://chriscosma.co.cc/off.png' />");
            //client.println("Light 3 Is Off");
            client.println("<br />");
          }
          }
          
          
           if(readString.indexOf("?relay4on") >0)//checks for on
          {
            digitalWrite(9, HIGH);    // set pin 4 high
            Serial.println("Led On");
            client.println("<link rel='apple-touch-icon' href='http://chriscosma.co.cc/on.png' />");
            //client.println("Light 4 Is On");
            client.println("<br />");
          }
          else{
          if(readString.indexOf("?relay4off") >0)//checks for off
          {
            digitalWrite(9, LOW);    // set pin 4 low
            Serial.println("Led Off");
            client.println("<link rel='apple-touch-icon' href='http://chriscosma.co.cc/off.png' />");
            //client.println("Light 4 Is Off");
            client.println("<br />");
          }
          }
          
         // control arduino pin via ethernet End //
         
         
         
          // Relay Status Display
          client.println("<center>");
          client.println("<table border=\"5\">");
          client.println("<tr>");
          
          if (digitalRead(6))
          { 
           client.print("<td>Light 1 is ON</td>");
           
          }
          else
          {
            client.print("<td>Light 1 is OFF</td>");
           
          }
          
          
          client.println("<br />");
          
          if (digitalRead(7))
          { 
           client.print("<td>Light 2 is ON</td>");
           
          }
          else
          {
            client.print("<td>Light 2 is OFF</td>");
            
          }
          
          client.println("</tr>");
          client.println("<tr>");
          
          if (digitalRead(8))
          { 
           client.print("<td>Light 3 is ON</td>");
           
          }
          else
          {
            client.print("<td>Light 3 is OFF</td>");
            
          }
          
         
        
         
          if (digitalRead(9))
          { 
           client.print("<td>Light 4 is ON</td>");
          
          }
          else
          {
            client.print("<td>Light 4 is OFF</td>");
           
          }
          
          client.println("</tr>");
          client.println("</table>");
          
          client.println("</center>");
          
          
          
          //clearing string for next read
          
          readString="";
 
          client.println("</body>");
          client.println("</HTML>");
 
          delay(1);
          //stopping client
          client.stop();
 
        }
      }
    }
  }
}
