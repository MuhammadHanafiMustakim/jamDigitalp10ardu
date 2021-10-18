#include <DMD3.h>
#include <SystemFont5x7.h>
#include <Arial_Black_16.h>
#include <Wire.h>
#include<Sodaq_DS3231.h>
DMD3 display(3,1);
byte ldtk,lmnt,ljam,jam,mnt,dtk,count;

void scan(){
  display.refresh();
}
String konvert(byte nilai){
   if(nilai<10){ return "0"+String(nilai); }
  else { return String(nilai);}
}
void up_in(String text){
    for(int x=0;x<display.height();x++){
      display.clear();
    display.drawText((display.width()-display.textWidth(text))/2,0,text);
    display.drawFilledRect(0,-1,96,(display.height()/2)-(x+1),0);
    display.swapBuffers();
    delay(80);
    }
  }
void down_out(String text){
  for(int x=0;x<display.height();x++){
    display.clear();
    display.drawText((display.width()-display.textWidth(text))/2,0,text);
    display.drawFilledRect(0,0,display.width(),x,0);
    display.swapBuffers();
    delay(80);
}

}
void right_in(String text){
   for(int x=0;x<display.width();x++){
    display.clear();
   display.drawText((display.width()-display.textWidth(text))/2,0,text);
   display.drawFilledRect(x,0,display.width(),16,0);
   display.swapBuffers();
   delay(30);
  }
}
void left_out(String text){
   for(int x=0;x<display.width();x++){
   display.clear();
   display.drawText((display.width()-display.textWidth(text))/2,0,text);
   display.drawFilledRect(x,0,0,16,0);
   display.swapBuffers();
   delay(30);
  }
}
void center_out(String text){
  for(int x=0;x<=(display.width()/2)+1;x++){
    display.clear();
   display.drawText((display.width()-display.textWidth(text))/2,0,text);
   display.drawFilledRect(48-x,0,49+x,16,0);
   display.drawLine(48-x,0,48-x,9);
   display.drawLine(49+x,0,49+x,9);
   display.swapBuffers();
   delay(30);
  }
}
void center_in(String text){
  for(int x=0;x<=(display.width()/2)+1;x++){
   display.clear();
   display.drawText((display.width()-display.textWidth(text))/2,0,text);
   display.drawFilledRect(0,0,48-x,16,0);
   display.drawFilledRect(49+x,0,96,16,0);
   display.drawLine(48-x,0,48-x,9);
   display.drawLine(49+x,0,49+x,9);
    display.swapBuffers();
    delay(30);
  }
}
void movedown_in(String text){
   for(int x=0;x<=(display.height()/2);x++){
    display.clear();
    display.drawText((display.width()-display.textWidth(text))/2,-8+x,text);
    display.swapBuffers();
    delay(80);
  }
}
void circle_out(String text){
  for(int x=0;x<=(display.width()/2)+5;x++){    
    display.clear();
    display.drawText((display.width()-display.textWidth(text))/2,0,text);
    display.drawFilledCircle(48,8,x,0);
    display.drawCircle(48,8,x);
    display.swapBuffers();
    delay(50);
  }
}
void draw(byte pos){
  (count<3)?count++:count=0;
   if (pos==0){
     for (byte x=0;x<16;x++){
    display.drawFilledRect(11,0,29,16,0);
    display.drawText(11,0-x,String (konvert(ljam))); 
    display.drawText(11,16-x,String (konvert(jam)));
    display.swapBuffersAndCopy(); 
    delay(15);
    }
  }
  if (pos==1){
     for (byte x=0;x<16;x++){
    display.drawFilledRect(40,0,58,16,0);
    display.drawText(40,0-x,String (konvert(lmnt))); 
    display.drawText(40,16-x,String (konvert(mnt)));
    display.swapBuffersAndCopy(); 
    delay(15);
    }
  }
  if (pos==2){
    display.drawFilledRect(30,0,37,16,0);
    display.drawFilledRect(59,0,66,16,0);
    display.drawFilledCircle(33,3,count);
    display.drawFilledCircle(33,12,count);
    display.drawFilledCircle(62,3,count);
    display.drawFilledCircle(62,12,count);
    if(count>0){
      display.drawFilledCircle(33,3,count-1,0);
      display.drawFilledCircle(33,12,count-1,0);
      display.drawFilledCircle(62,3,count-1,0);
      display.drawFilledCircle(62,12,count-1,0);}
    for (byte x=0;x<16;x++){
    display.drawFilledRect(68,0,97,16,0);
    display.drawText(68,0-x,String (konvert(ldtk))); 
    display.drawText(68,16-x,String (konvert(dtk)));
    display.swapBuffersAndCopy(); 
    delay(15);
    }
  } 
}
void drawaziz(){
  char text[14]={"AZIZ_KUROSAKI"};
  display.setFont(SystemFont5x7);
  for (byte x=0;x<sizeof(text);x++){
    for(byte y=0;y<(x*6)+8;y++){
      display.clear();
      for(byte z=0;z<sizeof(text);z++){
        if (z<x){
          display.drawChar((z*6)+8,0,text[z]);
        }
      }
      display.drawChar(y,0,text[x]);
      display.swapBuffers();
      delay(8);
    }
  }
  delay(500);
  for (byte x=sizeof(text);x>0;x--){
    for(byte y=(x*6)+8;y<97;y++){
      display.clear();
      for(byte z=0;z<sizeof(text);z++){
        if (z<x-1){
          display.drawChar((z*6)+8,0,text[z]);
        }
      }
      display.drawChar(y,0,text[x-1]);
      display.swapBuffers();
      delay(8);
    }
  }
  delay(500);
}

void setup(){
  Timer1.initialize(2000);
  Timer1.attachInterrupt(scan);
  Timer1.pwm(9,10);
  display.setDoubleBuffer(1);
  Wire.begin();
  rtc.begin();
  String tes ="Aziz Kurosaki";
  drawaziz();
  delay(1000);
  up_in(tes);
  delay(1000);
  down_out(tes);
  delay(1000);
  right_in(tes);
  delay(1000);
  left_out(tes);
  delay(1000);
  center_in(tes);
  delay(1000);
  center_out(tes);
  delay(1000);
  movedown_in(tes);
  delay(1000);
  circle_out(tes);
  delay(1000);
  display.clear();
  display.setFont(Arial_Black_16);
  DateTime now=rtc.now();
  ljam=now.hour()-1;
  lmnt=now.minute()-1;
  ldtk=now.second();
  delay(1000);
}

void loop(){
  DateTime now=rtc.now();
  jam=now.hour();
  mnt=now.minute();
  dtk=now.second();
  if (ldtk!=dtk){
    draw(2);
    ldtk=dtk;
  }
  if (lmnt!=mnt){
    draw(1);
    lmnt=mnt;
  }
  if (ljam!=jam){
    draw(0);
    ljam=jam;
  }
}
