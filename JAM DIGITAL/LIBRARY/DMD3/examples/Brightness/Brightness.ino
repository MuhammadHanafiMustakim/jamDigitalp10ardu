/*untuk perubahan brightness yg maksimal,pasang Resistor pullup 4.7k pada pin 9(OE)
	saya cuma merubah sedikit isi library,semoga bermanfaat :)
	
*/

#include <DMD3.h> //Library U/ dsiplay P10
#include <SystemFont5x7.h>// font yang akan dipaki
#define kolom 1 //jumlah kolom
#define baris 1//jumlah baris
#define OE 9 // digital pin yg mengatur kecerahaan P10

int x; //Variable untuk kecerahan 

DMD3 display (kolom,baris); //inisialisasi library

/* method u/ mengupdate tampilan*/
void scan(){
  display.refresh(); // update display
  Timer1.setPwmDuty(OE,x);//set kecerahan berdasarkan nilai x
}
void setup(){
  Timer1.initialize(2000); // set waktu  2000us u/ memanggil method interrupt
  Timer1.attachInterrupt(scan); //nama method yg akan di akses saat timer tercapai
  Timer1.pwm(OE,20);//inisialisasi kecerahan
}
void loop(){
  display.setFont(SystemFont5x7); // pilih font
 display.drawText(7,0,"Tes"); // tampilkan teks "tes" pada kordinat x=7 y=0
 display.drawText(7,8,"BOS"); // // tampilkan teks "BOS" pada kordinat x=7 y=8
 x<30?x++:x=0; // jika nilai x kurang dari 30 maka nilai x ditambh 1,jika salah maka nilai x kembali 0
 delay(500); //tuda waktu u/ perubahan kecerahan
}

