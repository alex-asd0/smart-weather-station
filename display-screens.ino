void screen_drawing() {
  if (screen == main) {
    DateTime now = rtc.now();
    static byte hour = -1, minute = -1, dayOfTheWeek = -1, day, month;
    static int year = 0;

    tft.setCursor(36, 5);
    tft.setTextSize(2);
    tft.setTextColor(white);

    if (hour != now.hour()) {
      tft.fillRect(36, 5, 23, 14, black);
      hour = now.hour();
    }
    if (hour < 10)tft.print(0);
    tft.print(hour);

    tft.setCursor(60, 5);
    if (now.second() % 2 == 1) tft.print(":");
    else {
      tft.fillRect(60, 5, 11, 14, black);
      tft.print(' ');

    }

    if (now.minute() != minute) {
      tft.fillRect(72, 5, 23, 14, black);
      minute = now.minute();
    }
    if (minute < 10) tft.print(0);
    tft.print(minute);


    if (dayOfTheWeek != now.dayOfTheWeek()) {
      tft.fillRect(10, 20, 108, 14, black);
      dayOfTheWeek = now.dayOfTheWeek();
    }
    tft.setCursor(int((128 - strlen(daysOfTheWeek[now.dayOfTheWeek()]) * 11 - strlen(daysOfTheWeek[now.dayOfTheWeek()])) / 2), 20);
    tft.print(daysOfTheWeek[now.dayOfTheWeek()]);


    if (day != now.day()) {
      tft.fillRect(39, 38, 10, 7, black);
      day = now.day();
    }
    tft.setCursor(39, 38);
    tft.setTextSize(1);
    if (day < 10) tft.print(0);
    tft.print(day);

    tft.setCursor(49, 38);
    tft.print('/');
    if (month != now.month()) {
      tft.fillRect(54, 38, 10, 7, black);
      month = now.month();
    }
    if (month < 10) tft.print(0);
    tft.print(month);

    tft.setCursor(64, 38);
    tft.print('/');
    if (year != now.year()) {
      tft.fillRect(69, 38, 20, 7, black);
      year = now.year();
    }
    tft.print(year);


    tft.setCursor(10, 55);
    tft.setTextSize(2);
    byte out_color;
    int color;

    out_color = round((float)((out_t - min_values[0]) / (float)((max_values[0] - min_values[0]) / 5)));
    if (max_values[0] == 0.0 && min_values[0] == 0.0 && out_t == 0.0)out_color = 0;

    switch (out_color) {
      case 0:
        color = blue;
        break;
      case 1:
        color = blue;
        break;
      case 2:
        color = cyan;
        break;
      case 3:
        color = green;
        break;
      case 4:
        color = yellow;
        break;
      case 5:
        color = red;
        break;
    }
    static float l_o_t, l_o_h;
    if (l_o_t != out_t) {
      l_o_t = out_t;
      tft.fillRect(10, 55, 83, 14, black);
    }
    tft.setTextColor(color);
    tft.print(out_t);
    tft.print(" C");

    if (l_o_h != out_h) {
      l_o_h = out_h;
      tft.fillRect(10, 75, 83, 14, black);
    }
    tft.setTextColor(cyan);
    tft.setCursor(10, 75);
    tft.print(out_h);
    tft.print(" %");

    tft.setCursor(30, 100);
    tft.setTextSize(2);
    byte in_color;

    in_color = round((float)((in_t - min_values[3]) / (float)((max_values[3] - min_values[3]) / 5)));
    if (max_values[3] == 0.0 && min_values[3] == 0.0 && in_t == 0.0)in_color = 0;

    switch (in_color) {
      case 0:
        color = blue;
        break;
      case 1:
        color = blue;
        break;
      case 2:
        color = cyan;
        break;
      case 3:
        color = green;
        break;
      case 4:
        color = yellow;
        break;
      case 5:
        color = red;
        break;
    }
    tft.setTextColor(color);

    static float l_i_t, l_i_h;
    if (l_i_t != in_t) {
      l_i_t = in_t;
      tft.fillRect(30, 100, 83, 14, black);
    }
    tft.print(in_t);
    tft.print(" C");

    tft.setCursor(30, 120);
    tft.setTextColor(cyan);
    if (l_i_h != in_h) {
      l_i_h = in_h;
      tft.fillRect(30, 120, 83, 14, black);
    }
    tft.print(in_h);
    tft.print(" %");

    static float l_p;
    if (l_p != pres) {
      l_p = pres;
      tft.fillRect(10, 140, 107, 14, black);
    }
    tft.setCursor(10, 140);
    tft.setTextColor(white);
    tft.print(pres);
    tft.print(" mm");
  }
  if (screen == out_temp) {
    byte out_color;
    int color;

    out_color = round((float)((out_t - min_values[0]) / (float)((max_values[0] - min_values[0]) / 5)));
    if (max_values[0] == 0.0 && min_values[0] == 0.0 && out_t == 0.0)out_color = 0;

    switch (out_color) {
      case 0:
        color = blue;
        break;
      case 1:
        color = blue;
        break;
      case 2:
        color = cyan;
        break;
      case 3:
        color = green;
        break;
      case 4:
        color = yellow;
        break;
      case 5:
        color = red;
        break;
    }
    static float last_o_t;
    if (last_o_t != out_t) {
      last_o_t = out_t;
      tft.fillRect(21, 5, 83, 14, black);
    }
    tft.setTextSize(2);
    tft.setCursor(21, 5);
    tft.setTextColor(color);
    tft.print(out_t);
    tft.print(" C");

    float max = max_value(graphOutT), min = min_value(graphOutT);

    for (byte x = 0; x < 24; x++) {
      byte graph = round((float)((graphOutT[x] - min) / (float)((max - min) / graph_high)));
      if (graph > graph_high || graph == 0 || graphOutT[x] < -99.0)graph = 1;
      byte graph_color = round((float)((graphOutT[x] - min_values[0]) / (float)((max_values[0] - min_values[0]) / 5)));
      switch (graph_color) {
        case 0:
          color = blue;
          break;
        case 1:
          color = blue;
          break;
        case 2:
          color = cyan;
          break;
        case 3:
          color = green;
          break;
        case 4:
          color = yellow;
          break;
        case 5:
          color = red;
          break;
      }

      tft.fillRect(x * 5 + 4, 20 + graph_high - graph, 5, graph, color);
    }
    static float l_mi_t;
    if (l_mi_t != min_values[0]) {
      l_mi_t = min_values[0];
      tft.fillRect(48, sec_line, 95, 14, black);
      tft.fillRect(5, sec_line + 17, 59, 14, black);
    }
    tft.setCursor(5, sec_line);
    tft.setTextColor(blue);
    tft.print("min:");
    tft.print(min_values[0]);
    tft.print("C");

    tft.setCursor(5, sec_line + 17);
    if (min_time[0] < 10)tft.print(0);
    tft.print(min_time[0]);
    tft.print(':');
    if (min_time[1] < 10) tft.print(0);
    tft.print(min_time[1]);

    static float l_ma_t;
    if (l_ma_t != max_values[0]) {
      l_ma_t = max_values[0];
      tft.fillRect(48, third_line, 95, 14, black);
      tft.fillRect(5, third_line + 17, 59, 14, black);
    }
    tft.setCursor(5, third_line);
    tft.setTextColor(red);
    tft.print("max:");
    tft.print(max_values[0]);
    tft.print("C");

    tft.setCursor(5, third_line + 17);
    if (max_time[0] < 10)tft.print(0);
    tft.print(max_time[0]);
    tft.print(':');
    if (max_time[1] < 10) tft.print(0);
    tft.print(max_time[1]);
  }
  if (screen == out_hum) {
    static float last_o_h;
    if (last_o_h != out_h) {
      last_o_h = out_h;
      tft.fillRect(21, 5, 83, 14, black);
    }
    tft.setTextSize(2);
    tft.setCursor(21, 5);
    tft.setTextColor(cyan);
    tft.print(out_h);
    tft.print(" %");

    float max = max_value(graphOutH), min = min_value(graphOutH);
    for (byte x = 0; x < 24; x++) {
      byte graph = round((float)((graphOutH[x] - min) / (float)((max - min) / graph_high)));
      if (graph > graph_high || graph == 0 || graphOutT[x] < -99.0)graph = 1;

      tft.fillRect(x * 5 + 4, 20 + graph_high - graph, 5, graph, cyan);
    }
    static float l_mi_o_h;
    if (l_mi_o_h != min_values[1]) {
      l_mi_o_h = min_values[1];
      tft.fillRect(48, sec_line, 95, 14, black);
      tft.fillRect(5, sec_line + 17, 59, 14, black);
    }
    tft.setCursor(5, sec_line);
    tft.setTextColor(yellow);
    tft.print("min:");
    tft.print(min_values[1]);
    tft.print("%");

    tft.setCursor(5, sec_line + 17);
    if (min_time[2] < 10)tft.print(0);
    tft.print(min_time[2]);
    tft.print(':');
    if (min_time[3] < 10) tft.print(0);
    tft.print(min_time[3]);

    static float l_ma_o_h;
    if (l_ma_o_h != max_values[1]) {
      l_ma_o_h = max_values[1];
      tft.fillRect(48, third_line, 95, 14, black);
      tft.fillRect(5, third_line + 17, 59, 14, black);
    }
    tft.setCursor(5, third_line);
    tft.setTextColor(blue);
    tft.print("max:");
    tft.print(max_values[1]);
    tft.print("%");

    tft.setCursor(5, third_line + 17);
    if (max_time[2] < 10)tft.print(0);
    tft.print(max_time[2]);
    tft.print(':');
    if (max_time[3] < 10) tft.print(0);
    tft.print(max_time[3]);
  }
  if (screen == pressure) {
    static float last_p;
    if (last_p != pres) {
      last_p = pres;
      tft.fillRect(10, 5, 107, 14, black);
    }
    tft.setTextSize(2);
    tft.setCursor(10, 5);
    tft.setTextColor(white);
    tft.print(pres);
    tft.print(" mm");

    float max = max_value(graphP), min = min_value(graphP);


    for (byte x = 0; x < 24; x++) {
      byte graph = round((float)((graphP[x] - min) / (float)((max - min) / graph_high)));
      if (graph > graph_high || graph == 0 || graphOutT[x] < -99.0)graph = 1;
      tft.fillRect(x * 5 + 4, (20 + graph_high) - graph, 5, graph, white);
    }
    static float l_mi_p;
    if (l_mi_p != min_values[2]) {
      l_mi_p = min_values[2];
      tft.fillRect(48, sec_line, 95, 14, black);
      tft.fillRect(5, sec_line + 17, 59, 14, black);
    }
    tft.setCursor(5, sec_line);
    tft.setTextColor(blue);
    tft.print("min:");
    tft.print(min_values[2]);

    tft.setCursor(5, sec_line + 15);
    if (min_time[4] < 10)tft.print(0);
    tft.print(min_time[4]);
    tft.print(':');
    if (min_time[5] < 10) tft.print(0);
    tft.print(min_time[5]);

    static float l_ma_p;
    if (l_ma_p != max_values[2]) {
      l_ma_p = max_values[2];
      tft.fillRect(48, third_line, 95, 14, black);
      tft.fillRect(5, third_line + 17, 59, 14, black);
    }
    tft.setCursor(5, third_line);
    tft.setTextColor(red);
    tft.print("max:");
    tft.print(max_values[2]);

    tft.setCursor(5, third_line + 17);
    if (max_time[4] < 10)tft.print(0);
    tft.print(max_time[4]);
    tft.print(':');
    if (max_time[5] < 10) tft.print(0);
    tft.print(max_time[5]);
  }
  if (screen == in_temp) {
    byte in_color;
    int color;

    in_color = round((float)((in_t - min_values[3]) / (float)((max_values[3] - min_values[3]) / 5)));
    if (max_values[3] == 0.0 && min_values[3] == 0.0 && in_t == 0.0)in_color = 0;

    switch (in_color) {
      case 0:
        color = blue;
        break;
      case 1:
        color = blue;
        break;
      case 2:
        color = cyan;
        break;
      case 3:
        color = green;
        break;
      case 4:
        color = yellow;
        break;
      case 5:
        color = red;
        break;
    }
    static float last_i_t;
    if (last_i_t != in_t) {
      last_i_t = in_t;
      tft.fillRect(20, 4, 85, 16, black);
    }
    tft.setTextSize(2);
    tft.setCursor(21, 5);
    tft.setTextColor(color);
    tft.print(in_t);
    tft.print(" C");

    float max = max_value(graphInT), min = min_value(graphInT);
    for (byte x = 0; x < 24; x++) {
      byte graph = round((float)((graphInT[x] - min) / (float)((max - min) / graph_high)));
      if (graph > graph_high || graph == 0 || graphOutT[x] < -99.0)graph = 1;
      byte graph_color = round((float)((graphInT[x] - min_values[3]) / (float)((max_values[3] - min_values[3]) / 5)));
      switch (graph_color) {
        case 0:
          color = blue;
          break;
        case 1:
          color = blue;
          break;
        case 2:
          color = cyan;
          break;
        case 3:
          color = green;
          break;
        case 4:
          color = yellow;
          break;
        case 5:
          color = red;
          break;
      }

      tft.fillRect(x * 5 + 4, (20 + graph_high) - graph, 5, graph, color);
    }
    static float l_mi_i_t;
    if (l_mi_i_t != min_values[3]) {
      l_mi_i_t = min_values[3];
      tft.fillRect(48, sec_line, 95, 14, black);
      tft.fillRect(5, sec_line + 15, 59, 14, black);
    }
    tft.setCursor(5, sec_line);
    tft.setTextColor(blue);
    tft.print("min:");
    tft.print(min_values[3]);
    tft.print("C");

    tft.setCursor(5, sec_line + 17);
    if (min_time[6] < 10)tft.print(0);
    tft.print(min_time[6]);
    tft.print(':');
    if (min_time[7] < 10) tft.print(0);
    tft.print(min_time[7]);

    static float l_ma_i_t;
    if (l_ma_i_t != max_values[3]) {
      l_ma_i_t = max_values[3];
      tft.fillRect(48, third_line, 95, 14, black);
      tft.fillRect(5, third_line + 15, 59, 14, black);
    }
    tft.setCursor(5, third_line);
    tft.setTextColor(red);
    tft.print("max:");
    tft.print(max_values[3]);
    tft.print("C");

    tft.setCursor(5, third_line + 17);
    if (max_time[6] < 10)tft.print(0);
    tft.print(max_time[6]);
    tft.print(':');
    if (max_time[7] < 10) tft.print(0);
    tft.print(max_time[7]);
  }
  if (screen == in_hum) {
    static float last_i_h;
    if (last_i_h != in_h) {
      last_i_h = in_h;
      tft.fillRect(21, 5, 83, 14, black);
    }
    tft.setTextSize(2);
    tft.setCursor(21, 5);
    tft.setTextColor(cyan);
    tft.print(in_h);
    tft.print(" %");

    float max = max_value(graphInH), min = min_value(graphInH);
    for (byte x = 0; x < 24; x++) {
      byte graph = round((float)((graphInH[x] - min) / (float)((max - min) / graph_high)));
      if (graph > graph_high || graph == 0 || graphOutT[x] < -99.0)graph = 1;
      tft.fillRect(x * 5 + 4, (20 + graph_high) - graph, 5, graph, cyan);
    }
    static float l_mi_i_h;
    if (l_mi_i_h != min_values[4]) {
      l_mi_i_h = min_values[4];
      tft.fillRect(48, sec_line, 95, 14, black);
      tft.fillRect(5, sec_line + 17, 59, 14, black);
    }
    tft.setCursor(5, sec_line);
    tft.setTextColor(yellow);
    tft.print(F("min:"));
    tft.print(min_values[4]);
    tft.print("%");

    tft.setCursor(5, sec_line + 17);
    if (min_time[8] < 10)tft.print(0);
    tft.print(min_time[8]);
    tft.print(':');
    if (min_time[9] < 10) tft.print(0);
    tft.print(min_time[9]);

    static float l_ma_i_h;
    if (l_ma_i_h != max_values[4]) {
      l_ma_i_h = max_values[4];
      tft.fillRect(48, third_line, 95, 14, black);
    }
    tft.setCursor(5, third_line);
    tft.setTextColor(blue);
    tft.print("max:");
    tft.print(max_values[4]);
    tft.print("%");

    tft.setCursor(5, third_line + 17);
    if (max_time[8] < 10)tft.print(0);
    tft.print(max_time[8]);
    tft.print(':');
    if (max_time[9] < 10) tft.print(0);
    tft.print(max_time[9]);
  }
  if (screen == work_time) {
    tft.setTextSize(2);
    tft.setTextColor(red);
    tft.setCursor(21, 5);
    tft.print(F("Hi!"));

    tft.setTextColor(white);
    tft.setTextSize(1);
    tft.setCursor(16, 25);
    tft.print(F("I'm meteostation"));

    tft.setCursor(22, 35);
    tft.print(F("my version is:"));

    tft.setCursor(int((128 - (strlen(meteo_version) * 6 - 1)) / 2), 45);
    tft.print(meteo_version);

    tft.setCursor(4, 55);
    tft.print(F("and I'm working for:"));

    //                   РАСЧЁТЫ
    tft.setTextSize(2);
    tft.setCursor(5, 75);
    byte days = millis() / 1000 / 60 / 60 / 24;
    static byte l_day;
    if (l_day != days) {
      tft.fillRect(5, 75, 23, 14, black);
      l_day = days;
    }
    if (days < 10)tft.print(0);
    tft.print(days);
    tft.print(F(" days "));

    tft.setCursor(5, 95);
    int hours = millis() / 1000 / 60 / 60;
    static byte l_hour;
    if (l_hour != hours - 24 * days) {
      l_hour = hours - 24 * days;
      tft.fillRect(5, 95, 23, 14, black);
    }
    if (hours - 24 * days < 10)tft.print(0);
    tft.print(hours - 24 * days);
    tft.print(F(" hours "));

    tft.setCursor(5, 115);
    int minutes = millis() / 1000 / 60;
    static byte l_min;
    if (l_min != minutes - 60 * hours) {
      tft.fillRect(5, 115, 23, 14, black);
      l_min = minutes - 60 * hours;
    }
    if (minutes - 60 * hours < 10)tft.print(0);
    tft.print(minutes - 60 * hours);
    tft.print(F(" minutes "));

    tft.setCursor(5, 135);
    int seconds = millis() / 1000;
    static byte l_sec;
    if (l_sec != seconds - 60 * minutes) {
      tft.fillRect(5, 135, 23, 14, black);
      l_sec = seconds - 60 * minutes;
    }
    if (seconds - 60 * minutes < 10)tft.print(0);
    tft.print(seconds - 60 * minutes);
    tft.print(F(" seconds "));
  }
}
