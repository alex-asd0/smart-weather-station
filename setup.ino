void setup() {

  Serial.begin(9600);
  while (!Serial);
  delay(100);

  Wire.begin(4, 5, 0x42);
  rtc.begin();

  byte val;
  byte time[3]; // массив времени компиляции (час, минута, секунда)
  for (byte x = 0; x < 8; x++) { // перемещаемся по времени компиляции
    switch (__TIME__[x]) {
      case '1':
        val += (x % 3 == 0) ? 1 * 10 : 1; // если эта цифра - начало нового числа - то умножаем на 10
        break;
      case '2':
        val += (x % 3 == 0) ? 2 * 10 : 2;
        break;
      case '3':
        val += (x % 3 == 0) ? 3 * 10 : 3;
        break;
      case '4':
        val += (x % 3 == 0) ? 4 * 10 : 4;
        break;
      case '5':
        val += (x % 3 == 0) ? 5 * 10 : 5;
        break;
      case '6':
        val += (x % 3 == 0) ? 6 * 10 : 6;
        break;
      case '7':
        val += (x % 3 == 0) ? 7 * 10 : 7;
        break;
      case '8':
        val += (x % 3 == 0) ? 8 * 10 : 8;
        break;
      case '9':
        val += (x % 3 == 0) ? 9 * 10 : 9;
        break;
    }

    if (x == 2 || x == 5 || x == 7) { // число закончилось
      time[int(x / 3)] = val; // записываем данные
      val = 0;
      continue;
    }

  }

  int date[3] = {0, 0, 0}; // массив даты компиляции (год, месяц, день)
  val = 0;
  if (__DATE__[6] != ' ') { // день
    val = 10;
    if (__DATE__[6] == '1')val++;
    else val += 2;
  }
  else {
    switch (__DATE__[5]) {
      case '1':
        val = 1;
        break;
      case '2':
        val = 2;
        break;
      case '3':
        val = 3;
        break;
      case '4':
        val = 4;
        break;
      case '5':
        val = 5;
        break;
      case '6':
        val = 6;
        break;
      case '7':
        val = 7;
        break;
      case '8':
        val = 8;
        break;
      case '9':
        val = 9;
        break;
    }
  }
  date[2] = val;

  // месяца запианные как в __DATE__
  char months[12][4] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
  char month[3];
  for (byte x; x < 3; x++)month[x] = __DATE__[x]; // получаем 3 буквы месяца
  for (byte x = 0; x < 12; x++) { // определяем номер месяца
    byte z = 1;
    for (byte y = 0; y < 3; y++) {
      if (month[y] == months[x][y]) {
        z += 1;
      }
    }
    if (z == 3) { // совпало 3 буквы
      date[1] = x + 2; // прибавлям 2 к номеру месяца в массиве
      break;
    }
  }

  char year[4];
  for (byte x; x < 4; x++)year[x] = __DATE__[strlen(__DATE__) - (4 - x)]; // год строкой
  for (byte x; x < 4; x++) { // опредлям год
    switch (year[x]) {
      case '1':
        date[0] += 1 * degree(10, 3 - x);
        break;
      case '2':
        date[0] += 2 * degree(10, 3 - x);
        break;
      case '3':
        date[0] += 3 * degree(10, 3 - x);
        break;
      case '4':
        date[0] += 4 * degree(10, 3 - x);
        break;
      case '5':
        date[0] += 5 * degree(10, 3 - x);
        break;
      case '6':
        date[0] += 6 * degree(10, 3 - x);
        break;
      case '7':
        date[0] += 7 * degree(10, 3 - x);
        break;
      case '8':
        date[0] += 8 * degree(10, 3 - x);
        break;
      case '9':
        date[0] += 9 * degree(10, 3 - x);
        break;
    }
  }

  DateTime now = rtc.now();
  // сравниваем полученные данные с датиком времени, ели время отстоёт, то ставим новое
  if (
    (date[0] >= now.year() && date[1] >= now.month() && date[2] >= now.day() && time[0] >= now.hour() && time[1] >= now.minute() && time[2] > now.second()) ||
    (date[0] >= now.year() && date[1] >= now.month() && date[2] >= now.day() && time[0] >= now.hour() && time[1] > now.minute()) ||
    (date[0] >= now.year() && date[1] >= now.month() && date[2] >= now.day() && time[0] > now.hour()) ||
    (date[0] >= now.year() && date[1] >= now.month() && date[2] > now.day()) ||
    (date[0] >= now.year() && date[1] > now.month()) ||
    (date[0] > now.year())) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    Serial.println("New time");
  }
  //power.hardwareDisable(PWR_UART0);

  hdc.begin(0x40);
  bmp.begin();

  tft.initR(INITR_BLACKTAB);
  tft.fillScreen(black);

  tft.setTextColor(white);

  screen = main;
  Serial.println("ready");
}

int degree(int num, byte degr) { // возведение в степеень
  int result = 1;
  for (byte x = 0; x < degr; x++)result *= num;
  return result;
}
