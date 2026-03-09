#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <RTClib.h>
#include "DHT.h"

#define DHTPIN 27
#define DHTTYPE DHT11

#define BTN_MODE 14
#define BTN_START 12
#define BTN_RESET 13

LiquidCrystal_I2C lcd(0x27, 16, 2);
RTC_DS1307 rtc;
DHT dht(DHTPIN, DHTTYPE);

byte mode = 0;
bool stopwatchRunning = false;

unsigned long startMillis = 0;
unsigned long elapsedMillis = 0;

unsigned long lastBtnTime = 0;
const unsigned long debounceDelay = 200;

const char* daysOfWeek[] = {
 "SUN","MON","TUE","WED","THU","FRI","SAT"
};

void setup() {

 pinMode(BTN_MODE, INPUT_PULLUP);
 pinMode(BTN_START, INPUT_PULLUP);
 pinMode(BTN_RESET, INPUT_PULLUP);

 Wire.begin(21, 22);

 lcd.begin();
 lcd.backlight();

 dht.begin();

 if (!rtc.begin()) {
   lcd.print("RTC ERROR");
   while (1);
 }

 if (!rtc.isrunning()) {
   rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
 }

 lcd.clear();
}

void loop() {

 readButtons();

 if (mode == 0) {
   displayClockMode();
 } 
 else {
   displayStopwatchMode();
 }

}

void readButtons() {

 if (millis() - lastBtnTime < debounceDelay) return;

 if (digitalRead(BTN_MODE) == LOW) {
   mode = !mode;
   lcd.clear();
   lastBtnTime = millis();
 }

 if (mode == 1 && digitalRead(BTN_START) == LOW) {

   stopwatchRunning = !stopwatchRunning;

   if (stopwatchRunning) {
     startMillis = millis() - elapsedMillis;
   }

   lastBtnTime = millis();
 }

 if (mode == 1 && digitalRead(BTN_RESET) == LOW) {

   stopwatchRunning = false;
   elapsedMillis = 0;
   lastBtnTime = millis();
 }

}

void displayClockMode() {

 DateTime now = rtc.now();

 float temp = dht.readTemperature();
 float hum = dht.readHumidity();

 int hour12 = now.hour() % 12;

 if (hour12 == 0) hour12 = 12;

 String ampm = now.hour() >= 12 ? "PM" : "AM";

 lcd.setCursor(0, 0);

 print2digit(hour12);
 lcd.print(":");
 print2digit(now.minute());
 lcd.print(":");
 print2digit(now.second());

 lcd.print(" ");
 lcd.print(ampm);

 lcd.print(" ");
 lcd.print(daysOfWeek[now.dayOfTheWeek()]);

 lcd.setCursor(0, 1);

 lcd.print("T:");
 lcd.print((int)temp);
 lcd.print("C ");

 lcd.print("H:");
 lcd.print((int)hum);
 lcd.print("%");

}

void displayStopwatchMode() {

 if (stopwatchRunning) {
   elapsedMillis = millis() - startMillis;
 }

 unsigned long ms = elapsedMillis % 1000;

 unsigned long seconds = elapsedMillis / 1000;

 byte hrs = seconds / 3600;
 byte mins = (seconds % 3600) / 60;
 byte secs = seconds % 60;

 lcd.setCursor(0, 0);

 lcd.print("STOPWATCH ");
 lcd.print(stopwatchRunning ? "RUN" : "STOP");

 lcd.setCursor(0, 1);

 print2digit(hrs);
 lcd.print(":");

 print2digit(mins);
 lcd.print(":");

 print2digit(secs);
 lcd.print(":");

 if (ms < 100) lcd.print("0");
 if (ms < 10) lcd.print("0");

 lcd.print(ms);

}

void print2digit(byte num) {

 if (num < 10)
   lcd.print("0");

 lcd.print(num);

}