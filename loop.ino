
void loop() {
  byte but = touch();
  if (but != 0) {
    if (but == 1) {
      if (screen == main) screen = out_temp;
      else if (screen == out_temp) screen = out_hum;
      else if (screen == out_hum) screen = pressure;
      else if (screen == pressure) screen = in_temp;
      else if (screen == in_temp) screen = in_hum;
      else if (screen == in_hum) screen = main;
    }
    else if (but == 2) {
      if (screen == main)screen = work_time;
      else if (screen == work_time) screen = main;
    }
    tft.fillScreen(black);

  }
  screen_drawing();
  sensor_work();
}

byte touch() {
  static unsigned long e;
  static boolean f;
  if (analogRead(button) > 512 && f == 0) {
    f = 1;
    e = millis();
  }

  if (analogRead(button) < 512 && f == 1) {
    f = 0;
    if (millis() - e < 250) return 1;
    return 2;
  }
  return 0;
}
