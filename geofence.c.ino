#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>

TinyGPSPlus gps;
//SoftwareSerial SerialGPS(14, 12);   //GPS pins(RX, TX)
SoftwareSerial SerialGPS(14, 12);   //GPS pins(RX, TX)

//wifi hotspot name and password
const char* ssid = "BabyBoy";
const char* password = "0833126198.mine";

float Latitude , Longitude;
int year , month , date, hour , minute , second;
String DateString , TimeString , LatitudeString , LongitudeString;


int temp = 36;
int buzzer = 13;    //buzzer pin

WiFiServer server(80);
void setup()
{
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);
  SerialGPS.begin(9600);
  Serial.println();
  Serial.print("Connecting");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  server.begin();
  Serial.println("Server started");
  Serial.println(WiFi.localIP());
}

void loop()
{
  while (SerialGPS.available() > 0)

    if (gps.encode(SerialGPS.read()))
    {
      if (gps.location.isValid())
      {
        Latitude = gps.location.lat();
        Serial.println(Latitude);
        LatitudeString = String(Latitude , 6);
        Longitude = gps.location.lng();
        LongitudeString = String(Longitude , 6);
        Serial.println(Longitude);
      }

      // Serial.println(SerialGPS.read());

      Latitude = gps.location.lat();
      // Serial.println(Latitude);
      LatitudeString = String(Latitude , 6);
      Longitude = gps.location.lng();
      LongitudeString = String(Longitude , 6);
      // Serial.println(Longitude);

      if (gps.date.isValid())
      {
        DateString = "";
        date = gps.date.day();
        month = gps.date.month();
        year = gps.date.year();

        if (date < 10)
        DateString = '0';
        DateString += String(date);

        DateString += " / ";

        if (month < 10)
        DateString += '0';
        DateString += String(month);
        DateString += " / ";

        if (year < 10)
        DateString += '0';
        DateString += String(year);
      }

      if (gps.time.isValid())
      {
        TimeString = "";
        hour = gps.time.hour()+ 5; //adjust UTC
        minute = gps.time.minute();
        second = gps.time.second();
    
        if (hour < 10)
        TimeString = '0';
        TimeString += String(hour);
        TimeString += " : ";

        if (minute < 10)
        TimeString += '0';
        TimeString += String(minute);
        TimeString += " : ";

        if (second < 10)
        TimeString += '0';
        TimeString += String(second);
      }

    }
  WiFiClient client = server.available();
  if (!client)
  {
    return;
  }

  String s =  "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n <!DOCTYPE html>";
s += "<html lang=""en"">";
s += "<head>";
s += "<meta charset=""UTF-8"">";
s += "<meta http-equiv=""X-UA-Compatible"" content=""IE=edge"">";
s += "<meta name=""viewport"" content=""width=device-width, initial-scale=1.0"">";
s += "<link rel=""stylesheet"" href=""style.css"">";
s += "<link rel=""stylesheet"" href=""utilities.css"">";
s += "<title>Project</title>";
s += "<style>";
s += "* {";
s += "margin: 0;";
s += "padding: 0;";
s += "box-sizing: border-box;";
s += "}";
s += "a {";
s += "text-decoration: none;";
s += "}";
s += "body {";
s += "background-color: #2F2F2F;";
s += "width: 100%;";
s += "height: 100%;";
s += "color: #FFFFFF;";
s += "font-family:'Gill Sans', 'Gill Sans MT', Calibri, 'Trebuchet MS', sans-serif;";
s += "}";
s += ".web-page {";
s += "display: flex;";
s += "flex-direction: row;";
s += "}";
s += ".navigation {";
s += "width: 15%;";
s += "height: 100vh;";
s += "background-color: #161616;";
s += "display: flex;";
s += "flex-direction: row;";
s += "justify-content: center;";
s += "align-items: center;";
s += "justify-items: center;";
s += "cursor: pointer;";
s += "}";
s += ".navigation img {";
s += "width: 18px;";
s += "margin-right: 15px;";
s += "}";
s += ".home-text {";
s += "padding-top: 5px;";
s += "font-size: 0.9em; ";
s += "}";
s += ".main-area{";
s += "width: 85%;";
s += "padding: 40px;";
s += "}";
s += ".top-part {";
s += "display: flex;";
s += "justify-content: space-between;";
s += "width: 100%;";
s += "}";
s += ".header {";
s += "font-size: 2.1em;";
s += "}";
s += ".lower-part {";
s += "padding-top: 30px;";
s += "}";
s += ".animal-card {";
s += "padding: 20px 15px;";
s += "background-color: #3C3B3B;";
s += "width: 100%;";
s += "border-radius: 10px;";
s += "display: flex;";
s += "justify-content: space-between;";
s += "}";
s += ".cow-details-left img {";
s += "width: 90px;";
s += "}";
s += ".cow-details-left p {";
s += "margin-top: 20px;";
s += "font-weight: 600;";
s += "}";
s += ".small {";
s += "font-weight: 100;";
s += "font-size: 0.9em;";
s += "}";
s += ".right-side-cow {";
s += "height: 100%;";
s += "display: flex;";
s += "justify-content: center;";
s += "align-items: center;";
s += "justify-items: center;";
s += "}";
s += ".location-btn {";
s += "padding: 5px 20px;";
s += "border-radius: 10px;";
s += "border: 3px solid #32C0DF;";
s += "font-size: 0.8rem;";
s += "margin-top: 20px;";
s += "}";
s += ".location-btn:hover {";
s += "background-color: #073640; ";
s += "transition: all 0.3s ease-in-out;";
s += "}";
s += ".right-words {";
s += "height: 100%;";
s += "padding-right: 50px;";
s += "}";
s += ".temperature-circle {";
s += "display: flex;";
s += "justify-content: center;";
s += "align-items: center;";
s += "border-radius: 50%;";
s += "padding: 10px;";
s += "height: 140px;";
s += "width: 140px;";
s += "border: 8px solid #32C0DF;";
s += "}";
s += ".temperature-circle p {";
s += "font-size: 1.8rem;";
s += "}";
s += ".power {";
s += "font-weight: 300;";
s += "font-size: medium;";
s += "}";
s += "a {";
s += "color: #ffffff;";
s += "display: inline-block;";
s += "}";
s += "@media screen and (max-width: 800px){";
s += ".navigation {";
s += "display: none;";
s += "}";
s += ".main-area {";
s += "width: 100%;";
s += "padding: 20px;";
s += "}";
s += "}";
s += "@media screen and (max-width: 600px){";
s += ".animal-card {";
s += "display: flex;";
s += "flex-direction: column;";
s += "}";
s += ".cow-details-left {";
s += "display: flex;";
s += "justify-content: space-between;";
s += "}";
s += ".right-side-cow {";
s += "flex-direction: row-reverse;";
s += "justify-content: space-between;";
s += "border-top: 2px solid #ffffff2d;";
s += "margin-top: 10px;";
s += "padding-top: 20px;";
s += "transition: all 0.4s ease-in-out;";
s += "margin-bottom: 15px;";
s += "}";
s += ".show-up .right-side-cow {";
s += "display: flex;";
s += "}";
s += ".right-words {";
s += "padding-right: 0px;";
s += "}";
s += ".view-more-btn {";
s += "background: none;";
s += "border: none;";
s += "outline: none;";
s += "color: #FFFFFF;";
s += "display: flex;";
s += "align-items: center;";
s += "margin-top: 20px;";
s += "padding-bottom: 5px;";
s += "border-bottom: 2px solid #32C0DF;";
s += "font-weight: 100;";
s += "}";
s += ".view-more-btn img {";
s += "width: 15px;";
s += "margin-left: 10px;";
s += "}";
s += "}";
s += "</style>";
s += "</head>";
s += "<body>";
s += "<section class=""web-page"">";
s += "<section class=""navigation"">";
s += "<img src=""./hut.png"" alt="" class=""home-font"">";
s += "<p class=""home-text"">Home</p>";
s += "</section>";
s += "<section class=""main-area"">";
s += "<div class=""top-part"">";
s += "<p class=""header"">Animal's</p>";
s += "<p class=""date"">";
s += DateString;
s += "</p>";
s += "</div>";
s += "<div class=""lower-part"">";
s += "<div class=""animal-card"">";
s += "<div class=""contaier-cow"">";
s += "<div class=""cow-details-left"">";
s += "<img src=""./qurbani.png"" alt="">";
s += "<p>Number : <span class=""small""> 007<span></p>";
s += "</div>";
s += "</div>";
s += "<div class=""right-side-cow"">";
s += "<div class=""right-words"">";
//link address to google maps 
s += "<p>Location : <span class=""small"">";
s += LatitudeString;
s += " ,";
s += LongitudeString;
s += "</span></p>";
s += "<a href=""http://maps.google.com/maps?&z=15&mrt=yp&t=k&q=";
s += LatitudeString;
s += LongitudeString;
s+= "class=""location-btn"">Location</a>";
s += "</div>";
s += "<div class=""temperature-circle"">";
s += "<p>";
s += temp;
s += "<span class=""power"">°C</span></p>";
s += "</div>";
s += "</div>";
s += "</div>";
s += "</div>";
s += "</section>";
s += "</section>";
s += "</body>";
s += "</html>";


  //Response //html page
  // String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n <!DOCTYPE html> <html> <head> <title>NEO-6M GPS Readings</title> <style>";
  // s += "table, th, td {border: 1px solid blue;} </style> </head> <body> <h1  style=";
  // s += "font-size:300%;";
  // s += " ALIGN=CENTER>COW NUMBER 113</h1>";
  // s += "<p ALIGN=CENTER style=""font-size:150%;""";
  // s += "> <b>DETIALS</b></p> <table ALIGN=CENTER style=";
  // s += "width:65%";
  // s += "> <tr> <th>Latitude</th>";
  // s += "<td ALIGN=CENTER >";
  // s += LatitudeString;
  // s += "</td> </tr> <tr> <th>Longitude</th> <td ALIGN=CENTER >";
  // s += LongitudeString;
  // s += "</td> </tr> <tr>  <th>Date</th> <td ALIGN=CENTER >";
  // s += DateString;
  // s += "</td></tr> <tr> <th>Time</th> <td ALIGN=CENTER >";
  // s += TimeString;
  //   s += "</td></tr> <tr> <th>Temperature</th> <td ALIGN=CENTER >";
  // s += temp;
  // s += "</td>  </tr> </table> ";
 
  
  if (gps.location.isValid())
  {
    s += "<p align=center><a style=""color:RED;font-size:125%;"" href=""http://maps.google.com/maps?&z=15&mrt=yp&t=k&q=";
    s += LatitudeString;
    s += "+";
    s += LongitudeString;
    s += """ target=""_top"">Click here</a> to open the location is Google Maps.</p>";
  }

  s += "</body> </html> \n";

  client.print(s);
  delay(100);


      float LNG = (gps.location.lng());
      float LAT = (gps.location.lat());
      
      //GEOFANCING COORDINATES(range)      
       if ( LAT > -13.974500 || LAT < -13.975000) {
        digitalWrite(buzzer, HIGH);
        delay(250);
        digitalWrite(buzzer, LOW);
        delay(250);
      }
      
      if ( LNG < 33.742250 || LNG > 33.743000) {
        digitalWrite(buzzer, HIGH);
        delay(250);
        digitalWrite(buzzer, LOW);
        delay(250);
      }
}