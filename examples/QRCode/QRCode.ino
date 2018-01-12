#include <Wire.h>
#include "qrcode.h"
#include <UTFT.h>

#define TFT_WR    4 //SCL
#define TFT_RS    3 //SDA
#define TFT_DC    6 //A0
#define TFT_REST  5 //RESET
#define TFT_CS    7 //CSE
UTFT myGLCD(ILI9341_S5P, TFT_RS, TFT_WR, TFT_CS, TFT_REST, TFT_DC);

void setup() {
  Serial.begin(115200);
  myGLCD.InitLCD();
  myGLCD.fillScr(255, 255, 255);
  myGLCD.setColor(0, 0, 0);
  // Start time
  uint32_t dt = millis();
  // Create the QR code
  QRCode qrcode;
  uint8_t version=6;
  uint8_t qrcodeData[qrcode_getBufferSize(version)];
  qrcode_initText(&qrcode, qrcodeData, version, 0, "Kongduino|HONG KONG|http://kongduino.wordpress.com|KONGDUINO@GMAIL.COM");
  // Delta time
  dt = millis() - dt;
  Serial.print(F("QR Code Generation Time: "));
  Serial.print(dt);
  Serial.print("\n");
  // Top quiet zone
  Serial.print("\n\n\n\n");
  uint8_t thickness=220/qrcode.size;
  uint8_t xOffset=(320-(qrcode.size*thickness))/2;
  uint8_t yOffset=(240-(qrcode.size*thickness))/2;
  for (uint8_t y = 0; y < qrcode.size; y++) {
    // Left quiet zone
    Serial.print("        ");
    // Each horizontal module
    for (uint8_t x = 0; x < qrcode.size; x++) {
      // Print each module (UTF-8 \u2588 is a solid block)
      bool q=qrcode_getModule(&qrcode, x, y);
      Serial.print(q ? "\u2588\u2588" : "  ");
      if(q) myGLCD.fillRect(x*thickness+xOffset, y*thickness+yOffset, x*thickness+xOffset+thickness-1, y*thickness+yOffset+thickness-1);
    }
    Serial.write('\n');
  }
  // Bottom quiet zone
  Serial.print("\n\n\n\n");
}

void loop() {
}
