#include <Arduino.h>
#include <ESP8266WiFi.h>            
#include <ESP8266WebServer.h>
int forward = D1;
int rev = D2;
int left = D3;
int right = D4;

ESP8266WebServer server(80);   //Web server object. Will be listening in port 80 (default for HTTP)
bool dir[4];
void setup() {
pinMode(forward,OUTPUT);
pinMode(rev,OUTPUT);
pinMode(left,OUTPUT);
pinMode(right,OUTPUT);
Serial.begin(115200);
WiFi.begin("dobrevi", "password345"); //Connect to the WiFi network

while (WiFi.status() != WL_CONNECTED) { //Wait for connection

delay(500);
Serial.println("Waiting to connect…");

}

Serial.print("IP address: ");
Serial.println(WiFi.localIP());  //Print the local IP to access the server

server.on("/genericArgs", handleGenericArgs); //Associate the handler function to the path

server.begin();                                       //Start the server
Serial.println("Server listening");   

}

void loop() {

server.handleClient();    //Handling of incoming requests

}
void handleGenericArgs() { //Handler

String message = "Tf are you doing here";
for (int i = 0; i < server.args(); i++) {
if(server.argName(i) == "dir"){
// String a = server.arg(i);
 Serial.print(server.arg(i));
 if (server.arg(i) == "1000"){
  dir[0]=1;
  dir[1]=0;
  dir[2]=0;
  dir[3]=0;
 }
  if (server.arg(i) == "0100"){
  dir[0]=0;
  dir[1]=1;
  dir[2]=0;
  dir[3]=0;
 }
  if (server.arg(i) == "0010"){
  dir[0]=0;
  dir[1]=0;
  dir[2]=1;
  dir[3]=0;
 }
  if (server.arg(i) == "0001"){
  dir[0]=0;
  dir[1]=0;
  dir[2]=0;
  dir[3]=1;
 }
  if (server.arg(i) == "1010"){
  dir[0]=1;
  dir[1]=0;
  dir[2]=1;
  dir[3]=0;
 }
  if (server.arg(i) == "1001"){
  dir[0]=1;
  dir[1]=0;
  dir[2]=0;
  dir[3]=1;
 }
  if (server.arg(i) == "0110"){
  dir[0]=0;
  dir[1]=1;
  dir[2]=1;
  dir[3]=0;
 }
  if (server.arg(i) == "0101"){
  dir[0]=0;
  dir[1]=1;
  dir[2]=0;
  dir[3]=1;
 }
  if (server.arg(i) == "0000"){
  dir[0]=0;
  dir[1]=0;
  dir[2]=0;
  dir[3]=0;
 }
 for(int j=0;j<4;j++){
  Serial.print(dir[j]);
 }
 Serial.print("\n");
 digitalWrite(forward, dir[0]);
 digitalWrite(rev, dir[1]);
 digitalWrite(left,dir[2]);
 digitalWrite(right,dir[3]);
}
}  

server.send(200, "text/plain", message);       //Response to the HTTP request

}