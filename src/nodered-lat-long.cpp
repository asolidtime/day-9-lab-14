/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "/home/maxwell/CTD-IoT/d9/nodered-lat-long/src/nodered-lat-long.ino"
/*
 * Project nodered-lat-long
 * Description:
 * Author:
 * Date:
 */
#include "MQTT.h"
#include "oled-wing-adafruit.h"
void callback(char* topic, byte* payload, unsigned int length);
void setup();
void loop();
#line 9 "/home/maxwell/CTD-IoT/d9/nodered-lat-long/src/nodered-lat-long.ino"
OledWingAdafruit display;

String latitude = "";
String longitude = "";
int textSize = 1;
void callback(char* topic, byte* payload, unsigned int length) 
{
  char p[length + 1];
  memcpy(p, payload, length);
  p[length] = NULL;
  Serial.println(String(topic));
  Serial.printf("%s",p);
  Serial.println();

	// //To parse an int
	// int receivedInt = atoi(p);
	// //To parse a float
	// float receivedFloat = atof(p);

	//To go from int to c_str
	// int i;
	// itoa(i, p, length); //destination int, c_str buffer, length
  if (String(topic).endsWith("long")) {
    longitude = String(p);
  } else if (String(topic).endsWith("lat")) {
    latitude = String(p);
  }
}
MQTT client("lab.thewcl.com", 1883, callback);

// setup() runs once, when the device is first turned on.
void setup() {
  // Put initialization like pinMode and begin functions here.
  display.setup();
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  display.loop();
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(textSize);
  display.setCursor(0, 0);
  display.print("lat: ");
  display.println(latitude);
  display.print("long: ");
  display.println(longitude);
  display.display();
  // The core of your code will likely live here.
  if (client.isConnected()) {
    client.loop();
  } else {
    client.connect(System.deviceID());
    client.subscribe("maximus's channel/ISS/lat");
    client.subscribe("maximus's channel/ISS/long");    
  }
}