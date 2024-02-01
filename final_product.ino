#include <IRremote.h>
#include "IR.h"
#include <NewTone.h>
#include <LiquidCrystal.h>
#define IR_RECEIVE_PIN  5  //赤外線受信ピンD5
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

IRrecv rcvdata(IR_RECEIVE_PIN); // 受信オブジェクトを作成
decode_results dec_results;     // 受信データの格納先

static int no_rcvcnt;         //未受信カウンターを設定

int BZ_bk = 3;                //ブザーはD3に接続
int duration = 200;           //音の長さを設定
int duration2 = 320;          //LCDの表示時間を設定

//液晶ディスプレイの関数を設定
void lcdWrite(int x, int y, char c){
  lcd.setCursor(x, y);
  lcd.print(c);
}

void setup() {
   rcvdata.enableIRIn();     // 赤外線受信開始
   no_rcvcnt = 0;            //0で初期化
   lcd.begin(16, 2);         //液晶文字表示は16×2マス
}

void loop() {
      // 受信したとき
   if (rcvdata.decode(&dec_results)) {      
      if (dec_results.value == 0xFF30CF){ // 1ボタンを押すとド
            NewTone(BZ_bk, 262, duration);
            lcd.clear();
            lcdWrite(6, 0, '-');
            lcdWrite(9, 0, '-');
            lcdWrite(7, 1, '-');
            lcdWrite(8, 1, '-');
            lcdWrite(14, 0, 'C');
            delay(duration2);    
       }
       
       else if(dec_results.value == 0xFF18E7){ // 2ボタンを押すとレ
            NewTone(BZ_bk, 294, duration);
            lcd.clear();
            lcdWrite(6, 0, '$');
            lcdWrite(9, 0, '$');
            lcdWrite(7, 1, '-');
            lcdWrite(8, 1, '-');
            lcdWrite(14, 0, 'D');
            delay(duration2);        
       }
       
       else if(dec_results.value == 0xFF7A85){ // 3ボタンを押すとミ
            NewTone(BZ_bk, 330, duration);
            lcd.clear();
            lcdWrite(6, 0, '^');
            lcdWrite(9, 0, '^');
            lcdWrite(7, 1, '-');
            lcdWrite(8, 1, '-');
            lcdWrite(14, 0, 'E');
            delay(duration2);    
       }

       else if(dec_results.value == 0xFF10EF){ // 4ボタンを押すとファ
            NewTone(BZ_bk, 349, duration);
            lcd.clear();
            lcdWrite(6, 0, '^');
            lcdWrite(9, 0, '^');
            lcdWrite(7, 1, '-');
            lcdWrite(8, 1, '-');
            lcdWrite(11, 1, 'b');
            lcdWrite(14, 0, 'F');
            delay(duration2);    
       }

       else if(dec_results.value == 0xFF38C7){ // 5ボタンを押すとソ
            NewTone(BZ_bk, 392, duration);
            lcd.clear();
            lcdWrite(6, 0, '^');
            lcdWrite(9, 0, '^');
            lcdWrite(8, 1, 'o');
            lcdWrite(14, 0, 'G');
            delay(duration2);    
       }

       else if(dec_results.value == 0xFF5AA5){ // 6ボタンを押すとラ
            NewTone(BZ_bk, 440, duration);
            lcd.clear();
            lcdWrite(6, 0, '^');
            lcdWrite(9, 0, '^');
            lcdWrite(8, 1, 'o');
            lcdWrite(11, 1, 'b');
            lcdWrite(14, 0, 'A');
            delay(duration2);    
       }

       else if(dec_results.value == 0xFF42BD){ // 7ボタンを押すとシ
            NewTone(BZ_bk, 494, duration);
            lcd.clear();
            lcdWrite(6, 0, '>');
            lcdWrite(9, 0, '<');
            lcdWrite(8, 1, 'o');
            lcdWrite(14, 0, 'B');
            delay(duration2);    
       }

       else if(dec_results.value == 0xFF4AB5){ // 8ボタンを押すとHiド
            NewTone(BZ_bk, 523, duration);
            lcd.clear();
            lcdWrite(6, 0, '>');
            lcdWrite(9, 0, '<');
            lcdWrite(8, 1, 'o');
            lcdWrite(11, 1, 'b');
            lcdWrite(14, 0, 'C');
            lcdWrite(15, 0, '!');
            delay(duration2);    
       }

       rcvdata.resume();                    //リセット
       no_rcvcnt = 0;
   }
   
   else{
      //受信していないとき
      if(no_rcvcnt >0){
          noNewTone(BZ_bk); //音を止める
          delay(10);
        }
        else{
          no_rcvcnt++;
        }
        lcd.clear();
        lcdWrite(6, 0, 'o');
        lcdWrite(9, 0, 'o');
        lcdWrite(7, 1, '-');
        lcdWrite(8, 1, '-');
        delay(100);
   }
   
   delay(10); 
}
