/*****************************************PROGRAM INI FULL MENGGUNAKAN MILLIS(), TANPA DELAY************************************/
/*JANGAN LUPA TAMBAHKAN LIBRARY YANG DIGUNAKAN
   DMD3
   Sodaq_DS3231
*/
/*CARA MENAMBAHKAN LIBRARY
   1.copy library dmd3 dan Sodaq_DS3231
   2.masuk pada folder arduino kemudian paste di dalam folder libraries
*/
/*BAHAN YANG DIBUTUHKAN
   1.ARDUINO UNO/NANO
   2.PANEL P10 1 WARNA
   3.POWER SUPPLY 5V 5A
   4.DS3231SN (USAHAKAN PAKAI YANG SERI SN)
   5.KABEL JUMPER
   6.RESISTOR 10K (Khusus library DMD3 menggunakan resistor 10K untuk pull down di PIN OE agar panel TIDAK BERBAYANG)
*/
/*SARAN
   Usahakan panel p10 mengunakan tegangan eksternal vcc=5v DC
   spesifikasi untuk satu panel p10 1 warna adalah 5v 5ampere
*/
/*
 * PIN 6 => A                 OE *  * A
 * PIN 7 => B                GND *  * B
 *                               *  *
 * PIN 8 => SCLK                 *  * CLK
 * PIN 9 => OE                   *  * SCLK
 * PIN 11 => DATA                *  * DATA
 * PIN 13 => CLK                 *  *
 *                               *  *
 * PIN A5 => SCL
 * PIN A4 => SDA
 * 
 * khusus dmd3 agar tidak berbayang gunakan resistor 10k untuk pullDown
 * kaki resistor menyambung di ground dan kaki yang satunya di sambung dengan oe dan PIN 9 (PULL down)
 * 
*/
#include <DMD3.h>
#include <Wire.h>
#include <SPI.h>
#include "Sodaq_DS3231.h"

#include <font/Mono5x7.h>//<<<---TANDA /(garis miring)pada font/Mono5x7.h artinya terletak di dalam sebuah folder yang bernama font
#include <font/BigNumber.h>
#include <font/Arial_Black_16.h>

//untuk step tampilan
bool step1 = true;
bool step2 = false;
bool step3 = false;
bool step4 = false;

//untuk millis running taxt 2
bool State1 = LOW;
unsigned long waktuSesudahIni1 = 0;


//untuk parameter millis() di fungsi detik()
unsigned long waktuSesudahIni = 0;
const long interval = 1;
int State = LOW;

//untuk parameter millis() di fungsi jam1()
unsigned long  waktuSesudahIni2 = 0;
int State2 = LOW;
bool Stat2 = LOW;
int x = 0;

//jumlah display p10
DMD3 disp(1, 1);  //disp(lebarPanel, tinggi panel); 1 pada koma pertama artinya

/***********************************************************UNTUK SETTING***********************************************************/

//untuk setting waktu
bool settingWaktusaatini = false; /*set=> settingWaktusaatini = true; dan upload program untuk setting waktu,
                                    setelah waktu cocok set=> settingWaktusaatini = false; dan upload ulang
                                    program.
*/
DateTime dt(2021, 10, 3, 22, 26, 55, 0); /*dt(tahun,bulan,tanggal,jam,menit,detik,hari)
                                         hari 0 = minggu
                                         hari 1 = senin
                                         hari 2 = selasa
                                         hari 3 = rabu
                                         hari 4 = kamis
                                         hari 5 = jumat
                                         hari 6 = sabtu
*/
//untuk setting lama Tampil ja besar /********Step1********/
unsigned int jambesar = 10000;    // 1000 = 1 DETIK

//untuk ubah kecepatan hari tanggal bulan dan tahun /********Step2********/
int kecepatanwaktu = 50;

//untuk ubah pesan 1 DAN 2 max 200 karakter
String pesan1 = "RUNNING TAXT1";   // /********Step3********/
String pesan2 = "RUNNING TAXT2";   // /********Step4********/

//untuk ubah kecepatan runningtaxt 1 DAN 2
int kecepatanpesan1 = 50;  // 1000 = 1 DETIK // /********Step3********/
int kecepatanpesan2 = 50;  // 1000 = 1 DETIK // /********Step4********/

/************************************************************************************************************************************/

//untuk penyimpanan NAMA hari dengan string array
static const char namaHari[][7] = {"MINGGU", "SENIN", "SELASA", "RABU", "KAMIS", "JUM\'AT", "SABTU",};

//untuk penyimpanan NAMA bulan dengan string array
static const char namaBulan[][10] = {"JANUARI", "FEBRUARI", "MARET", "APRIL", "MEI", "JUNI", "JULI", "AGUSTUS", "SEPTEMBER", "OKTOBER", "NOVEMBER", "DESEMBER"};

void scan()
{
  disp.refresh();
}
void Disp_init()
{
  Timer1.initialize(2000);
  Timer1.attachInterrupt(scan);
  Timer1.pwm(9, 200);  //pwm(pin oe, mengatur_kecerahan)
  //
  //kecerahan dapat di atur 0-255
  //                        0-5v
  //
  disp.setDoubleBuffer(true);
  disp.clear();
  disp.swapBuffers();
}
void SettingWaktu() {
  if (settingWaktusaatini) {
    rtc.setDateTime(dt);
  } else {
    rtc.now();
  }
}
void setup() {                                  /****************************INISIALISASI BERJALAN 1X**************************/
  Serial.begin(9600);
  Wire.begin();
  SettingWaktu();
  Disp_init();
}
void loop() {                                 /****************************LOOPING BERJALAN TERUS MENERUS**************************/
  disp.clear();
  if (step1 == true) {
    animasi(jambesar); //waktu tampil jam
  }
  else if (step2 == true) {
    jam1(kecepatanwaktu);
  }
  else if (step3 == true) {
    runningText1(pesan1, kecepatanpesan1);
  }
  else if (step4 == true) {
    runningText2(pesan2, kecepatanpesan2);
  }
  disp.swapBuffers();
}
void detik() {                                         /****************************KEDIP**************************/
  DateTime detik = rtc.now();
  unsigned long waktuSaatIni = detik.second();
  if (waktuSaatIni - waktuSesudahIni >= interval) {
    waktuSesudahIni = waktuSaatIni;
    if (State == LOW) {
      Stat2 = LOW;
      State = HIGH;
    } else if (State == HIGH) {
      State = LOW;
      Stat2 = HIGH;
    }
  }
  if ( Stat2 == HIGH) {                //UNTUK KEDIP
    disp.drawFilledRect(16, 1, 15, 2, 0);
    disp.drawFilledRect(16, 4, 15, 5, 0);
  } else if (Stat2 == LOW) {
    disp.drawFilledRect(16, 1, 15, 2, 1);
    disp.drawFilledRect(16, 4, 15, 5, 1);
  }
}
void animasi(int waktu) /**************************************STEP1**************************************/
{
  static uint8_t    y;
  static uint8_t    s; // 0=in, 1=out
  static uint16_t   lsRn;
  uint16_t          Tmr = millis();

  if ((Tmr - lsRn) > 100)
  {
    if (s == 0 and y < 17) {
      lsRn = Tmr;
      y++;
    }
    if (s == 1 and y > 0) {
      lsRn = Tmr;
      y--;
    }
  }
  if ((Tmr - lsRn) > waktu and y == 17) {
    s = 1;
  }
  if (y == 7)
  {
  }
  if (y == 0 and s == 1) {
    step2 = true;
    step1 = false;
    s = 0;
  }
  JamBesar(17 - y);
}
void JamBesar(uint16_t y)   // jam besar
{
  DateTime waktu = rtc.now();
  char  JAM[5];
  char  MENIT[3];
  char  DETIK[3];
  byte det = waktu.second();

  sprintf(JAM, "%02d", waktu.hour());
  sprintf(MENIT, "%02d", waktu.minute());
  sprintf(DETIK, "%02d", waktu.second());

  disp.drawFilledRect(14, y + 3, 16, y + 5, 1);
  disp.drawFilledRect(14, y + 9, 16, y + 11, 1);
  disp.setFont(Mono5x7);
  disp.drawText(0, y, JAM);
  disp.drawText(0, y + 8, MENIT);
  disp.setFont(BigNumber);
  disp.drawText(19, y, DETIK);
}
void jam1(int waktu)  /**************************************STEP2**************************************/
{
  DateTime no = rtc.now();
  static char  Buff[30];
  int width = disp.width();
  char  BuffJ[2];
  char  BuffM[2];
  char  BuffD[6];
  bool stat1 = true;
  if (stat1) {
    uint16_t waktuSaatIni2 = millis();
    if (waktuSaatIni2 - waktuSesudahIni2 >= waktu) {
      waktuSesudahIni2 = waktuSaatIni2;
      if (State2 == LOW) {
        x++;
        State2 = HIGH;
      } else {
        State2 = LOW;
      }
    }
    detik();
    disp.setFont(Mono5x7);

    int msgWidth = disp.textWidth(Buff);
    int fullScroll = msgWidth + width + 1;
    char hari = namaHari[no.dayOfWeek()];
    sprintf(Buff, "%s, %d %s %d", namaHari[no.dayOfWeek()], no.date(), namaBulan[no.month() - 1], no.year());
    sprintf(BuffJ, "%02d", no.hour());
    disp.drawText(2, 0, BuffJ);
    sprintf(BuffM, "%02d", no.minute());
    disp.drawText(19, 0, BuffM);
    disp.drawRect(1, 8, 30, 8, 1);
    disp.drawText(width - x, 9, Buff);
    if (x == fullScroll) {
      step4 = false;
      step3 = true;
      step2 = false;
      step1 = false;
      stat1 = true;
      x = 0;
    }
  }
}
void runningText1( String message, int waktu) {   /**************************************STEP3**************************************/
  DateTime no = rtc.now();
  int width = disp.width();
  char  BuffJ[2];
  char  BuffM[2];

  bool stat1 = true;
  if (stat1) {
    uint16_t waktuSaatIni2 = millis();
    if (waktuSaatIni2 - waktuSesudahIni2 >= waktu) {
      waktuSesudahIni2 = waktuSaatIni2;
      if (State2 == LOW) {
        x++;
        State2 = HIGH;
      } else {
        State2 = LOW;
      }
    }
    detik();
    disp.setFont(Mono5x7);

    int msgWidth = disp.textWidth(message);
    int fullScroll = msgWidth + width + 1;

    sprintf(BuffJ, "%02d", no.hour());
    disp.drawText(2, 0, BuffJ);
    sprintf(BuffM, "%02d", no.minute());
    disp.drawText(19, 0, BuffM);
    disp.drawRect(1, 8, 30, 8, 1);
    disp.drawText(width - x, 9, message);
    if (x == fullScroll) {
      step4 = true;
      step3 = false;
      step2 = false;
      step1 = false;

      stat1 = false;
      x = 0;
    }
  }
}
void runningText2(String message, int waktu) {    /**************************************STEP4**************************************/
  int width = disp.width();

  bool stat2 = true;
  if (stat2) {
    uint16_t waktuSaatIni1 = millis();
    if (waktuSaatIni1 - waktuSesudahIni1 >= waktu) {
      waktuSesudahIni1 = waktuSaatIni1;
      if (State1 == LOW) {
        x++;
        State1 = HIGH;
      } else {
        State1 = LOW;
      }
    }

    disp.setFont(Arial_Black_16);
    int msgWidth = disp.textWidth(message);
    int fullScroll = msgWidth + width + 1;
    disp.drawText(width - x, 0, message);

    if (x == fullScroll) {
      step4 = false;
      step3 = false;
      step2 = false;
      step1 = true;

      stat2 = false;
      x = 0;
    }
  }
}
