#include <Wire.h> 
#include <WiFi.h>
#include <WebServer.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"

const char* ssid = "abcdefg";
const char* password = "abc123";

WebServer server(80);

LiquidCrystal_I2C lcd(0x27, 20, 4);

#define DHTPIN 32    
#define DHTTYPE DHT11   
#define SOIL_PIN 33

 int POMPA = 26;
 int KIPAS = 25;
 int LAMPU = 27;
 float A,B,C;

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);

  // WiFi.begin(wipi, psw);
  
  // Serial.println(F("DHTxx test!"));

  dht.begin();
  lcd.begin();
	lcd.backlight();

  pinMode(POMPA, OUTPUT);
  pinMode(KIPAS, OUTPUT);
  pinMode(LAMPU, OUTPUT);

  digitalWrite(POMPA, LOW);
  digitalWrite(KIPAS, LOW);
  digitalWrite(LAMPU, LOW);

    WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi Connected");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.begin();
}

void loop() {

   server.handleClient();

  // delay(2000);
  // lcd.clear();

  // float h = dht.readHumidity();
  // float t = dht.readTemperature();
  // float f = dht.readTemperature(true);

  // // if (isnan(h) || isnan(t) || isnan(f)) {
  // //   Serial.println(F("Failed to read from DHT sensor!"));
  // //   return;
  // // }
  // // float hif = dht.computeHeatIndex(f, h);
  // // float hic = dht.computeHeatIndex(t, h, false);

  // A = analogRead(SOIL_PIN);
  // B = ( 100 - ( (A/4095.00) * 100 ) ); 
  // C = map(A, 0, 4095, 100, 0);

  // // if(B < 20 ) digitalWrite(POMPA) = HIGH;
  // // if(t > 25 ) digitalWrite(KIPAS) = HIGH;
  // // if(h < 40 ) digitalwrite(LAMPU) = HIGH;

  // digitalWrite(POMPA, C < 20 ? LOW : HIGH);
  // digitalWrite(KIPAS, t > 30 ? LOW : HIGH);
  // digitalWrite(LAMPU, h < 55 ? LOW : HIGH);
  
  // // if(B<20){
  // //   digitalWrite(POMPA, HIGH);
  // // }else{
  // //   digitalWrite(POMPA, LOW);
  // // }
  // // if(t>30){
  // //   digitalWrite(KIPAS, HIGH);
  // // }else{
  // //       digitalWrite(POMPA, LOW);
  // // }
  // // if(h<55){
  // //   digitalWrite(LAMPU, HIGH);
  // // }else{
  // //       digitalWrite(POMPA, LOW);
  // // }

  // Serial.print("Moisture = ");
  // Serial.print(B);           
  // Serial.print("%");
  // Serial.print(" / ");
  // Serial.print(C);

  // Serial.print(F("Humidity: "));
  // Serial.print(h);
  // Serial.print(F("%  Temperature: "));
  // Serial.print(t);
  // Serial.println(F("°C "));
  // // Serial.print(f);
  // // Serial.println(F("°F"));
  // // Serial.print(hic);
  // // Serial.print(F("°C "));
  // // Serial.print(hif);
  // // Serial.println(F("°F"));

  // lcd.setCursor(0, 0);
  // // lcd.print("MINI SMART GARDEN");
  // // lcd.setCursor(0, 1);
  // lcd.print("Tanah:");
  // lcd.setCursor(6, 0);
  // lcd.print(B);
  // lcd.setCursor(11, 0);
  // lcd.print("Suhu: ");
  // lcd.setCursor(16, 0);
  // lcd.print(t);
  // lcd.setCursor(0, 1);
  // lcd.print("Udara: ");
  // lcd.setCursor(6, 1);
  // lcd.print(h);
  // lcd.setCursor(0, 2);
  // lcd.print("Pompa:");
  // lcd.setCursor(6, 2);
  // lcd.print(B < 30 ? "ON " : "OFF");
  // lcd.setCursor(9, 2);
  // lcd.print(" Kipas:");
  // lcd.setCursor(16, 2);
  // lcd.print(t > 30 ? "ON " : "OFF");
  // lcd.setCursor(0, 3);
  // lcd.print("Lampu:");
  // lcd.setCursor(6, 3);
  // lcd.print(h < 55 ? "ON" : "OFF");

  // lcd.clear();
}

void handleRoot() {
  float suhu = dht.readTemperature();
  float kelembapanUdara = dht.readHumidity();
  int soilRaw = analogRead(SOIL_PIN);
  // float kelembapanTanah = map(soilRaw, 0, 4095, 100, 0);
  float kelembapanTanah = ( 100 - ( (soilRaw/4095.00) * 100 ) ); 

  bool pompaStatus = kelembapanTanah < 20;
  bool kipasStatus = suhu > 30;
  bool lampuStatus = kelembapanUdara < 40;

  digitalWrite(POMPA, pompaStatus ? LOW : HIGH);
  digitalWrite(KIPAS, kipasStatus ? LOW : HIGH);
  digitalWrite(LAMPU, lampuStatus ? LOW : HIGH);

  // digitalWrite(POMPA, kelembapanTanah < 20 ? LOW : HIGH);
  // digitalWrite(KIPAS, suhu > 33 ? LOW : HIGH);
  // digitalWrite(LAMPU, kelembapanUdara < 55 ? LOW : HIGH);

  //  delay(2000);
  // lcd.clear();

  // float h = dht.readHumidity();
  // float t = dht.readTemperature();
  // float f = dht.readTemperature(true);

  // A = analogRead(SOIL_PIN);
  // B = ( 100 - ( (A/4095.00) * 100 ) ); 
  // C = map(A, 0, 4095, 100, 0);

  // digitalWrite(POMPA, C < 20 ? LOW : HIGH);
  // digitalWrite(KIPAS, t > 30 ? LOW : HIGH);
  // digitalWrite(LAMPU, h < 55 ? LOW : HIGH);
  
  Serial.print("Moisture = ");
  Serial.print(kelembapanTanah);           
  Serial.print("%");
  Serial.print(" / ");
  Serial.print(C);

  Serial.print(F("Humidity: "));
  Serial.print(kelembapanUdara);
  Serial.print(F("%  Temperature: "));
  Serial.print(suhu);
  Serial.println(F("°C "));

  lcd.setCursor(0, 0);
  // lcd.print("MINI SMART GARDEN");
  // lcd.setCursor(0, 1);
  lcd.print("Tanah:");
  lcd.setCursor(6, 0);
  lcd.print(kelembapanTanah);
  lcd.setCursor(11, 0);
  lcd.print("Suhu: ");
  lcd.setCursor(16, 0);
  lcd.print(suhu);
  lcd.setCursor(0, 1);
  lcd.print("Udara: ");
  lcd.setCursor(6, 1);
  lcd.print(kelembapanUdara);
  lcd.setCursor(0, 2);
  lcd.print("Pompa:");
  lcd.setCursor(6, 2);
  lcd.print(kelembapanTanah < 20 ? "ON " : "OFF");
  lcd.setCursor(9, 2);
  lcd.print(" Kipas:");
  lcd.setCursor(16, 2);
  lcd.print(suhu > 30 ? "ON " : "OFF");
  lcd.setCursor(0, 3);
  lcd.print("Lampu:");
  lcd.setCursor(6, 3);
  lcd.print(kelembapanUdara < 40 ? "ON" : "OFF");

 String html = "<!DOCTYPE html><html><head><meta http-equiv='refresh' content='5'>";
  html += "<style>";
  html += "body { font-family: Arial; background:#f0f8ff; text-align:center; }";
  html += ".card { background:#fff; border-radius:10px; padding:15px; margin:10px auto; width:80%; box-shadow:0 0 10px rgba(0,0,0,0.1); }";
  html += ".status-on { color:green; font-weight:bold; }";
  html += ".status-off { color:gray; font-weight:bold; }";
  html += "h2 { color:#2e8b57; }";
  html += "</style></head><body>";
  html += "<h2> Smart Garden Monitor</h2>";

  html += "<div class='card'><h3>Sensor Data</h3>";
  html += "<p>Suhu: " + String(suhu, 1) + " °C</p>";
  html += "<p>Kelembapan Udara: " + String(kelembapanUdara, 1) + " %</p>";
  html += "<p>Kelembapan Tanah: " + String(kelembapanTanah, 1) + " %</p></div>";

  html += "<div class='card'><h3>Status Perangkat</h3>";
  html += "<p>Pompa: <span class='" + String(pompaStatus ? "status-on" : "status-off") + "'>" + (pompaStatus ? "ON" : "OFF") + "</span></p>";
  html += "<p>Kipas: <span class='" + String(kipasStatus ? "status-on" : "status-off") + "'>" + (kipasStatus ? "ON" : "OFF") + "</span></p>";
  html += "<p>Lampu: <span class='" + String(lampuStatus ? "status-on" : "status-off") + "'>" + (lampuStatus ? "ON" : "OFF") + "</span></p></div>";

  html += "</body></html>";

  server.send(200, "text/html", html);
}
