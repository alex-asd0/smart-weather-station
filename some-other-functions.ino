byte minute() {
  DateTime now = rtc.now();
  return now.minute();
}
byte hour() {
  DateTime now = rtc.now();
  return now.hour();
}
byte sec() {
  DateTime now = rtc.now();
  return now.second();
}

float min_value(float graph[24]) {
  float res = 1000.0;
  for (int x = 23; x > -1; x--) {
    if (graphOutT[x] < -99.0)return res;
    res = min(res, graph[x]);
  }
  return res;
}

float max_value(float graph[24]) {
  float res = -100.0;
  for (int x = 23; x > -1; x--) {
    if (graphOutT[x] < -99.0)return res;
    res = max(res, graph[x]);
  }
  return res;
}
