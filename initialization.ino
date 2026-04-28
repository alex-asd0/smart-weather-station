/*
  25.06 начало разработки
  02.07 - 03.07 автоматиеское обновление времени
  05.07 скрины: out_temp, in_temp, in_hum, pressure, out_hum
  06.07, 08.07 доработка графиков (регулируемая высота, время макс/мин)
*/
#define sensor_reading 10 // в секундах
#define graph_time 60   // в минутах
#define graph_high 50
#define meteo_version "Meteonator 1.1"

#include "RTClib.h"

RTC_DS3231 rtc;


#define button A0 // кнопка
#define sec_line 20 + graph_high + 5
#define third_line sec_line + 17 + 15 + 5

#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

#define TFT_CS 15
#define TFT_RST 2
#define TFT_DC 16

#define SCLK 14
#define MOSI 13


Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);

#define red   ST7735_RED
#define black ST7735_BLACK
#define white ST7735_WHITE
#define green ST7735_GREEN
#define cyan ST7735_CYAN
#define yellow ST7735_YELLOW
#define blue ST7735_BLUE

#include <Wire.h>

#include "ClosedCube_HDC1080.h"
ClosedCube_HDC1080 hdc;

#include <Adafruit_BMP085.h>
Adafruit_BMP085 bmp;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

#include <Gyver433.h>
Gyver433_RX<0, 20> rx;


struct dataPack {
  byte address;
  float t_out;
  float h_out;
  boolean condition;
};

enum {main = 0, out_temp, out_hum, pressure, in_temp, in_hum, alarm_setting, work_time} screen;

unsigned long sensor_timer;
unsigned long graph_timer;



float max_values[5] = { -100, -1, 100, -100, -1}, min_values[5] = {100, 101, 1000, 100, 101};
byte max_time[10], min_time[10];

float out_t, out_h, pres = 0, in_t = 0, in_h;

float graphOutT[24] = { -100.0, -100.0, -100.0, -100.0, -100.0, -100.0, -100.0, -100.0, -100.0, -100.0, -100.0, -100.0, -100.0, -100.0, -100.0, -100.0,
                        -100.0, -100.0, -100.0, -100.0, -100.0, -100.0, -100.0, -100.0
                      },
                      graphOutH[24], graphP[24], graphInT[24], graphInH[24];
