void sensor_work() {
  if (hour() == 0 && minute() == 0 && sec() == 0) {
    for (byte x; x < 5; x++) {
      max_values[x] = -100;
      min_values[x] = 1000;
    }
  }
  if (millis() - sensor_timer > sensor_reading * 1000) {

    in_t = hdc.readTemperature();
    in_h = hdc.readHumidity();
    pres = bmp.readPressure() / 133.3;

    if (in_t > 100.0 || in_h > 99.0) {
      hdc.begin(0x40);
      in_t = hdc.readTemperature();
      in_h = hdc.readHumidity();
    }

    if (pres > 800.0) {
      bmp.begin();
      pres = bmp.readPressure() / 133.3;
    }

    if (rx.tick()) {
      dataPack data;     // "буферная" структура
      rx.readData(data); // переписываем данные в неё

      Serial.print("Received:  ");
      Serial.print(data.t_out);
      Serial.print("C  ");
      Serial.print(data.h_out);
      Serial.print("%  ");
      Serial.println(data.condition);
      //out_t = data.t_out;
      //out_h = data.h_out;

    }
    out_t = 0.0;
    out_h = 0.0;

    if (max_values[0] < out_t) {
      max_values[0] = out_t;
      max_time[0] = hour();
      max_time[1] = minute();
    }
    if (min_values[0] > out_t) {
      min_values[0] = out_t;
      min_time[0] = hour();
      min_time[1] = minute();
    }

    if (max_values[1] < out_h) {
      max_values[1] = out_h;
      max_time[2] = hour();
      max_time[3] = minute();
    }
    if (min_values[1] > out_h) {
      min_values[1] = out_h;
      min_time[2] = hour();
      min_time[3] = minute();
    }

    if (max_values[2] < pres) {
      max_values[2] = pres;
      max_time[4] = hour();
      max_time[5] = minute();
    }
    if (min_values[2] > pres) {
      min_values[2] = pres;
      min_time[4] = hour();
      min_time[5] = minute();
    }

    if (max_values[3] < in_t) {
      max_values[3] = in_t;
      max_time[6] = hour();
      max_time[7] = minute();
    }
    if (min_values[3] > in_t) {
      min_values[3] = in_t;
      min_time[6] = hour();
      min_time[7] = minute();
    }

    if (max_values[4] < in_h) {
      max_values[4] = in_h;
      max_time[8] = hour();
      max_time[9] = minute();
    }
    if (min_values[4] > in_h) {
      min_values[4] = in_h;
      min_time[8] = hour();
      min_time[9] = minute();
    }

    sensor_timer = millis();
  }

  static unsigned long graph_timer = 0;
  if (millis() - graph_timer > graph_time * 60 * 1000 || (graph_timer == 0 && pres != 0)) {
    for (byte x = 0; x < 23; x++) {
      graphOutT[x] = graphOutT[x + 1];
      graphP[x] = graphP[x + 1];
      graphOutH[x] = graphOutH[x + 1];
      graphInT[x] = graphInT[x + 1];
      graphInH[x] = graphInH[x + 1];
    }
    graphOutT[23] = out_t;
    graphOutH[23] = out_h;
    graphP[23] = pres;
    graphInT[23] = in_t;
    graphInH[23] = in_h;
    graph_timer = millis();
  }
}
