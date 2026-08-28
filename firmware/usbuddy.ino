/*
 * CH552G
 *   P3.7 : D-
 *   P3.6 : D+
 *   P1.6 : SCL
 *   P1.7 : SDA
 *   P1.5 : NEOPX
 */

#include <Adafruit_NeoPixel.h>
#include <U8x8lib.h>

#define NEOPIXEL_PIN 16 // P1.6
#define OLED_SDA_PIN 15 // P1.5
#define OLED_SCL_PIN 17 // P1.7

Adafruit_NeoPixel pixel(1, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

// (u8x8 = no framebuffer) - we don't really have enough ram for full
// framebuffer
U8X8_SSD1306_128X32_UNIVISION_SW_I2C
u8x8(OLED_SCL_PIN, OLED_SDA_PIN, U8X8_PIN_NONE);

// serial
char lineBuf[64];

void setup() {
  Serial.begin(115200);

  pixel.begin();
  pixel.setPixelColor(0, pixel.Color(0, 0, 0));
  pixel.show();

  u8x8.begin();
  u8x8.setFont(u8x8_font_chroma48medium8_r);
  u8x8.clear();
  u8x8.drawString(0, 0, "*-^-^-* hello world *-^-^-*");
  u8x8.drawString(0, 1, "-> ready.");
}

void loop() {
  if (Serial.available()) {
    size_t len = Serial.readBytesUntil('\n', lineBuf, sizeof(lineBuf) - 1);
    lineBuf[len] = '\0';

    handleCommand(lineBuf);
  }
}

void handleCommand(char *cmd) {
  if (strncmp(cmd, "TEXT:", 5) == 0) {
    char *text = cmd + 5;
    u8x8.clear();
    u8x8.drawString(0, 0, text);
  } else if (strncmp(cmd, "LED:", 4) == 0) {
    int r, g, b;
    if (sscanf(cmd + 4, "%d,%d,%d", &r, &g, &b) == 3) {
      pixel.setPixelColor(0, pixel.Color(r, g, b));
      pixel.show();
    }
  }
}
