#include <ESP8266WiFi.h>

// Enter your wifi network name and Wifi Password
const char* ssid = "Shasta 102 Test 4707";
const char* password = "Password@123";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;


// These variables store current output state of outlets
String outputStateOutlet1 = "off";
String outputStateOutlet2 = "off";
String outputStateOutlet3 = "off";
String outputStateOutlet4 = "off";

String outputStateOutlet5 = "off";
String outputStateOutlet6 = "off";
String outputStateOutlet7 = "off";
String outputStateOutlet8 = "off";

// Assign output variables to GPIO pins
const int outlet1 = 5;
const int outlet2 = 4;
const int outlet3 = 0;
const int outlet4 = 2;

const int outlet5 = 14;
const int outlet6 = 12;
const int outlet7 = 13;
const int outlet8 = 15;

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

void setup() {
Serial.begin(115200);
// Initialize the output variables as outputs
pinMode(outlet1, OUTPUT);
pinMode(outlet2, OUTPUT);
pinMode(outlet3, OUTPUT);
pinMode(outlet4,OUTPUT);

pinMode(outlet5, OUTPUT);
pinMode(outlet6, OUTPUT);
pinMode(outlet7, OUTPUT);
pinMode(outlet8,OUTPUT);
// Set outputs to LOW
digitalWrite(outlet1, LOW);
digitalWrite(outlet2, LOW);
digitalWrite(outlet3, LOW);
digitalWrite(outlet4, LOW);

digitalWrite(outlet5, LOW);
digitalWrite(outlet6, LOW);
digitalWrite(outlet7, LOW);
digitalWrite(outlet8, LOW);

// Connect to Wi-Fi network with SSID and password
Serial.print("Connecting to ");
Serial.println(ssid);
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
}
// Print local IP address and start web server
Serial.println("");
Serial.println("WiFi connected.");
Serial.println("IP address: ");
Serial.println(WiFi.localIP());
server.begin();
}

void loop(){
WiFiClient client = server.available(); // Listen for incoming clients

if (client) { // If a new client connects,
Serial.println("New Client."); // print a message out in the serial port
String currentLine = ""; // make a String to hold incoming data from the client
currentTime = millis();
previousTime = currentTime;
while (client.connected() && currentTime - previousTime <= timeoutTime) { // loop while the client's connected
currentTime = millis(); 
if (client.available()) { // if there's bytes to read from the client,
char c = client.read(); // read a byte, then
Serial.write(c); // print it out the serial monitor
header += c;
if (c == '\n') { // if the byte is a newline character
// if the current line is blank, you got two newline characters in a row.
// that's the end of the client HTTP request, so send a response:
if (currentLine.length() == 0) {
// HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
// and a content-type so the client knows what's coming, then a blank line:
client.println("HTTP/1.1 200 OK");
client.println("Content-type:text/html");
client.println("Connection: close");
client.println();

// turns the GPIOs on and off
if (header.indexOf("GET /5/on") >= 0) {
Serial.println("Oulet1 is on");
outputStateOutlet1 = "on";
digitalWrite(outlet1, HIGH);
} else if (header.indexOf("GET /5/off") >= 0) {
Serial.println("Oulet1 is off");
outputStateOutlet1 = "off";
digitalWrite(outlet1, LOW);
}else if (header.indexOf("GET /4/on") >= 0) {
Serial.println("Oulet2 is on");
outputStateOutlet2 = "on";
digitalWrite(outlet2, HIGH);
} else if (header.indexOf("GET /4/off") >= 0) {
Serial.println("Oulet2 is off");
outputStateOutlet2 = "off";
digitalWrite(outlet2, LOW);
}else if (header.indexOf("GET /0/on") >= 0) {
Serial.println("Oulet3 is on");
outputStateOutlet3 = "on";
digitalWrite(outlet3, HIGH);
} else if (header.indexOf("GET /0/off") >= 0) {
Serial.println("Oulet3 is off");
outputStateOutlet3 = "off";
digitalWrite(outlet3, LOW);
} else if (header.indexOf("GET /2/on") >= 0) {
Serial.println("Oulet4 is on");
outputStateOutlet4 = "on";
digitalWrite(outlet4, HIGH);
} else if (header.indexOf("GET /2/off") >= 0) {
Serial.println("Oulet4 is off");
outputStateOutlet4 = "off";
digitalWrite(outlet4, LOW);
}
// turns the GPIOs on and off
if (header.indexOf("GET /14/on") >= 0) {
Serial.println("Oulet5 is on");
outputStateOutlet5 = "on";
digitalWrite(outlet5, HIGH);
} else if (header.indexOf("GET /14/off") >= 0) {
Serial.println("Oulet5 is off");
outputStateOutlet5 = "off";
digitalWrite(outlet5, LOW);
}else if (header.indexOf("GET /12/on") >= 0) {
Serial.println("Oulet6 is on");
outputStateOutlet6 = "on";
digitalWrite(outlet6, HIGH);
} else if (header.indexOf("GET /12/off") >= 0) {
Serial.println("Oulet6 is off");
outputStateOutlet6 = "off";
digitalWrite(outlet6, LOW);
}else if (header.indexOf("GET /13/on") >= 0) {
Serial.println("Oulet7 is on");
outputStateOutlet7 = "on";
digitalWrite(outlet7, HIGH);
} else if (header.indexOf("GET /13/off") >= 0) {
Serial.println("Oulet7 is off");
outputStateOutlet7 = "off";
digitalWrite(outlet7, LOW);
} else if (header.indexOf("GET /15/on") >= 0) {
Serial.println("Oulet8 is on");
outputStateOutlet8 = "on";
digitalWrite(outlet8, HIGH);
} else if (header.indexOf("GET /15/off") >= 0) {
Serial.println("Oulet8 is off");
outputStateOutlet8 = "off";
digitalWrite(outlet8, LOW);
}

// Display the HTML web page
client.println("<!DOCTYPE html><html>");
client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
client.println("<link rel=\"icon\" href=\"data:,\">");
// CSS to style the on/off buttons 
client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
client.println(".OUTLET-1 { background-color: #ff0000; border: none; color: white; padding: 16px 40px; border-radius: 60%;");
client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
client.println(".OUTLET-2 { background-color: #ff0000; border: none; color: white; padding: 16px 40px; border-radius: 60%;");
client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
client.println(".OUTLET-3 { background-color: #00ff00; border: none; color: white; padding: 16px 40px; border-radius: 60%;");
client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
client.println(".OUTLET-4 { background-color: #feeb36; border: none; color: white; padding: 16px 40px; border-radius: 60%;");
client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
client.println(".OUTLET-5 { background-color: #ff0000; border: none; color: white; padding: 16px 40px; border-radius: 60%;");
client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
client.println(".OUTLET-6 { background-color: #ff0000; border: none; color: white; padding: 16px 40px; border-radius: 60%;");
client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
client.println(".OUTLET-7 { background-color: #00ff00; border: none; color: white; padding: 16px 40px; border-radius: 60%;");
client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
client.println(".OUTLET-8 { background-color: #feeb36; border: none; color: white; padding: 16px 40px; border-radius: 60%;");
client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
client.println(".buttonOff { background-color: #77878A; border: none; color: white; padding: 16px 40px; border-radius: 70%;");
client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}</style></head>");

// Web Page Heading
client.println("<body><h1>CANDELA RDT LAB</h1>");

// Display current state, and ON/OFF buttons for GPIO 2 OUTLET 1 
client.println("<p>OUTLET 1 is " + outputStateOutlet1 + "</p>");
// If the outputStateOutlet1 is off, it displays the OFF button 
if (outputStateOutlet1=="off") {
client.println("<p><a href=\"/5/on\"><button class=\"button buttonOff\">OFF</button></a></p>");
} else {
client.println("<p><a href=\"/5/off\"><button class=\"button OUTLET-1\">ON</button></a></p>");
} 
//adding new outlet
// Display current state, and ON/OFF buttons for GPIO 0 OUTLET 2
client.println("<p>OUTLET 2 is " + outputStateOutlet2 + "</p>");
// If the outputStateOutlet2 is off, it displays the OFF button 
if (outputStateOutlet2 =="off") {
client.println("<p><a href=\"/4/on\"><button class=\"button buttonOff\">OFF</button></a></p>");
} else {
client.println("<p><a href=\"/4/off\"><button class=\"button OUTLET-2\">ON</button></a></p>");
}

// Display current state, and ON/OFF buttons for GPIO 4 OUTLET 3 
client.println("<p>OUTLET 3 is " + outputStateOutlet3 + "</p>");
// If the outputStateOutlet3 is off, it displays the OFF button 
if (outputStateOutlet3 =="off") {
client.println("<p><a href=\"/0/on\"><button class=\"button buttonOff\">OFF</button></a></p>");
} else {
client.println("<p><a href=\"/0/off\"><button class=\"button OUTLET-3\">ON</button></a></p>");
}
client.println("</body></html>");

// Display current state, and ON/OFF buttons for GPIO 5 OUTLET 4
client.println("<p>OUTLET 4 is " + outputStateOutlet4 + "</p>");
// If the outputStateOutlet4 is off, it displays the OFF button 
if (outputStateOutlet4 =="off") {
client.println("<p><a href=\"/2/on\"><button class=\"button buttonOff\">OFF</button></a></p>");
} else {
client.println("<p><a href=\"/2/off\"><button class=\"button OUTLET-4\">ON</button></a></p>");
}

client.println("<p>OUTLET 5 is " + outputStateOutlet5 + "</p>");
// If the outputStateOutlet2 is off, it displays the OFF button 
if (outputStateOutlet5 =="off") {
client.println("<p><a href=\"/14/on\"><button class=\"button buttonOff\">OFF</button></a></p>");
} else {
client.println("<p><a href=\"/14/off\"><button class=\"button OUTLET-5\">ON</button></a></p>");
}


client.println("<p>OUTLET 6 is " + outputStateOutlet6 + "</p>");
// If the outputStateOutlet2 is off, it displays the OFF button 
if (outputStateOutlet6 =="off") {
client.println("<p><a href=\"/12/on\"><button class=\"button buttonOff\">OFF</button></a></p>");
} else {
client.println("<p><a href=\"/12/off\"><button class=\"button OUTLET-6\">ON</button></a></p>");
}

client.println("<p>OUTLET 7 is " + outputStateOutlet7 + "</p>");
// If the outputStateOutlet2 is off, it displays the OFF button 
if (outputStateOutlet7 =="off") {
client.println("<p><a href=\"/13/on\"><button class=\"button buttonOff\">OFF</button></a></p>");
} else {
client.println("<p><a href=\"/13/off\"><button class=\"button OUTLET-7\">ON</button></a></p>");
}

client.println("<p>OUTLET 8 is " + outputStateOutlet8 + "</p>");
// If the outputStateOutlet2 is off, it displays the OFF button 
if (outputStateOutlet8 =="off") {
client.println("<p><a href=\"/15/on\"><button class=\"button buttonOff\">OFF</button></a></p>");
} else {
client.println("<p><a href=\"/15/off\"><button class=\"button OUTLET-8\">ON</button></a></p>");
}

client.println("</body></html>");

// The HTTP response ends with another blank line
client.println();
// Break out of the while loop
break;
} else { // if you got a newline, then clear currentLine
currentLine = "";
}
} else if (c != '\r') { // if you got anything else but a carriage return character,
currentLine += c; // add it to the end of the currentLine
}
}
}
// Clear the header variable
header = "";
// Close the connection
client.stop();
Serial.println("Client disconnected.");
Serial.println("");
}
}
