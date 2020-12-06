#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#include <Arduino.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <SocketIoClient.h>
#include <SoftwareSerial.h>
#include <WiFiManager.h>
#include <Wire.h>
#ifdef __AVR__
#include <avr/power.h>
#endif
#include <TM1637Display.h>

const char* deviceName = "lampRien";

const byte pinPixels = D1;
const int neoPixelCount = 60;
const int matrixWidth = 6;
const int matrixHeight = 8;
//Adafruit_NeoPixel strip = Adafruit_NeoPixel(neoPixelCount, pinNeoPixels, NEO_GRB + NEO_KHZ800);

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(matrixWidth, matrixHeight, pinPixels,
                                               NEO_MATRIX_BOTTOM + NEO_MATRIX_RIGHT +
                                                   NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
                                               NEO_GRB + NEO_KHZ800);

const int colorLenght = 3;
const uint16_t colors[colorLenght] = {
    matrix.Color(255, 0, 0), matrix.Color(0, 255, 0), matrix.Color(0, 0, 255)};

/*
WiFiManager wifiManager;
WiFiClient client;

WiFiUDP ntpUDP;
int GTMOffset = 1;
NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", GTMOffset * 60 * 60, 60000);
long lastTimeUpdate = 0;
int lastBlinkTime = 0;
int displayTime = 0;
bool lastBlink;

const byte pinCLK = D2;
const byte pinDIO = D3;

TM1637Display clockDisplay(pinCLK, pinDIO);

SocketIoClient webSocket;

String getValue(String data, char separator, int index) {
    int found = 0;
    int strIndex[] = {0, -1};
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i + 1 : i;
        }
    }

    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void handleMessage(const char* payload, size_t length) {
    String receivedText = String(payload);
    Serial.println(receivedText);
}

void colorWipe(uint32_t c, uint8_t wait) {
    for (uint16_t i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, c);
        strip.show();
        delay(wait);
    }
}

void updateTime() {
    if ((displayTime == 0) || (millis() >= (lastTimeUpdate + 60000))) {
        lastTimeUpdate = millis();
        timeClient.update();
        int minutes = timeClient.getMinutes();
        int hours = timeClient.getHours();

        Serial.println(timeClient.getFormattedTime());

        displayTime = (int)hours / 10 * 1000 + (hours - ((int)hours / 10) * 10) * 100 + (int)minutes / 10 * 10 + minutes - ((int)minutes / 10) * 10;

        Serial.println(displayTime);
    }
}

void updateClockDisplay() {
    if (millis() > lastBlinkTime + 500) {
        updateTime();
        lastBlinkTime = millis();
        uint8_t dots;
        lastBlink = !lastBlink;
        dots = (lastBlink) ? 0 : (0x80 >> 1);
        clockDisplay.showNumberDecEx(displayTime, dots, true);
    }
}
*/

void setup() {
    Serial.begin(115200);
    delay(10);

    Serial.println("###");
    Serial.println("start");

    matrix.begin();
    matrix.setBrightness(40);
    /*
    clockDisplay.setBrightness(5);
    clockDisplay.clear();
    clockDisplay.showNumberDec(1234, true);
    delay(500);
    clockDisplay.clear();

    strip.begin();
    strip.setBrightness(50);
    strip.show();

    colorWipe(strip.Color(255, 0, 0), 5);

    WiFiManager wifiManager;
    wifiManager.autoConnect(deviceName);

    strip.clear();
    colorWipe(strip.Color(0, 255, 0), 5);
    strip.clear();
    strip.show();

    delay(10);

    Serial.println("WiFi connected!!");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    timeClient.begin();

    while (displayTime == 0) {
        updateTime();
    }

    
    delay(100);

    webSocket.on(deviceName, handleMessage);
    webSocket.begin("wifilamp.postduif.be", 80);

    delay(100);
*/
}

void loop() {
    for (int i = 0; i < colorLenght; i++) {
        for (int x = 0; x < matrixWidth; x++) {
            for (int y = 0; y < matrixHeight; y++) {
                matrix.drawPixel(x, y, colors[i]);
                matrix.show();
                delay(10);
            }
        }
    }

    //  updateClockDisplay();
    //    webSocket.loop();
}