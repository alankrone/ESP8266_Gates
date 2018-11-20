
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

void setup() {

// Replace these with your WiFi network settings
const char* ssid      = "homenet";      //replace this with your WiFi network name
const char* password  = "aaaaaaaaaa";   //replace this with your WiFi network password
const char* host      = "10.0.0.211";   //App Server IP

delay(1000);
 
  // initialize serial communication at 9600 bits per second:
  Serial.begin(115200);
  Serial.println("Init System");

  WiFi.mode(WIFI_OFF);        //Prevents reconnection issue (taking too long to connect)
  delay(1000);
  WiFi.mode(WIFI_STA);        //This line hides the viewing of ESP as wifi hotspot
  WiFi.begin(ssid, password);

  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("success!");
  Serial.print("IP Address is: ");
  Serial.println(WiFi.localIP());

}


//=======================================================================
//                    Main Program Loop
//=======================================================================
void loop() {
  HTTPClient http;    //Declare object of class HTTPClient
 
  String postData,hostip,idcard,access,pin;

  hostip = String (WiFi.localIP()[0]) + "." + String (WiFi.localIP()[1]) + "." + String (WiFi.localIP()[2]) + "." + String (WiFi.localIP()[3]);
  idcard = "12345";
  pin = "0000"; 
 
  //Post Data
  postData = "hostip=" + hostip + "&idcard=" + idcard + "&pin=" + pin;
  
  http.begin("http://10.0.0.211/verify.php");              //Specify request destination
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");    //Specify content-type header
 
  int httpCode = http.POST(postData);   //Send the request
  String payload = http.getString();    //Get the response payload
 
  Serial.println(httpCode);   //Print HTTP return code
  Serial.println(payload);    //Print request response payload
 
  http.end();  //Close connection

  if (payload != "") {Serial.println ("GRANTED");}
  else {Serial.println ("DENIED");}
  
  delay(5000);  //Post Data at every 5 seconds
}
//=======================================================================
