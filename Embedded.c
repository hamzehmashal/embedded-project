 void myDelay(unsigned int x);
void hamzeh();
unsigned int ctr1;
unsigned int angle;
unsigned char HL;//High Low
unsigned int loop;
void Khaled();
void f_Delay(unsigned int ms_Count);

void interrupt(){
if(INTCON & 0x04)// tmr0
 {
   TMR0=248;
   ctr1++;
   INTCON = INTCON & 0xFB;


   if (PORTC & 0x02 )  //RC1  1st push button
   {
    angle = 800;


   }
   else
   {
   angle = 3500;
   }

    if(PORTC & 0x08){ //RC3 2nd push button

    Khaled();

    }
    else{
      PORTC = 0x40; // RC6 green on 5th light.

    }


 }




 if(PIR1&0x04){//CCP1 interrupt
   if(HL){ //high
     CCPR1H= angle >>8;
     CCPR1L= angle;
     HL=0;//next time low
     CCP1CON=0x09;//next time Falling edge
     TMR1H=0;
     TMR1L=0;
   }
   else{  //low
     CCPR1H= (40000 - angle) >>8;
     CCPR1L= (40000 - angle);
     CCP1CON=0x08; //next time rising edge
     HL=1; //next time High
     TMR1H=0;
     TMR1L=0;

   }

 PIR1=PIR1&0xFB;
 }
 if(PIR1&0x01){ //TMR1 ovwerflow

   PIR1=PIR1&0xFE;
 }

}
void main() {
     ADCON1 = 0x06; // convert all portA to digital
     OPTION_REG = 0x87;
     TMR0=248;
     INTCON =0xA0;
     TRISD = 0x00;
     TRISB = 0x80;  //edit
     PORTB = 0x00 ;
     TRISC = 0x88 ; // 1000 1000 in decimal
     PORTC = 0x00;
     T1CON=0x01;
     TMR1H=0;
     TMR1L=0;
     HL=1;
     CCP1CON=0x08;
     PIE1=PIE1|0x04;
     CCPR1H=2000>>8;
     CCPR1L=2000;
     angle = 1100;
     TRISA = 0xFE;  // 1111 1110 in decimal.

     while(1){

          PORTC = 0x40; // RC6 green on 5th light.
          hamzeh();

     }
}



void myDelay(unsigned int x){
   ctr1=0;
   while(ctr1<x);

}


void hamzeh(){
     PORTC = 0x40; //green RC6  for 5th traffic light. for 5th traffic light

      loop = 0x04;
while(loop) {
            if(PORTA & 0x02){  // RA1

            loop = 0x00;
            }
            else{

            loop -- ; } // 0x03

        PORTB = 0x0C; //Green ON for the 1st & Red ON for the 2nd traffic ligh.
        PORTD = 0x09; // Both 2nd & 3rd traffic lights are Red.
        myDelay(2500);  //means 4s

        }
        PORTB = 0x0A; // yellow ON for 1st & red ON for 2nd
        myDelay(750);
              loop = 0x04;
while(loop) {
            if(PORTA & 0x04)  // RA2
            {
            loop = 0x00;
            }
            else
            {
            loop -- ;  // 0x03
            }
        //2nd Case:
        PORTB = 0x21; //Second is green & 1st is Red
        PORTD = 0x09; //Both 2nd & 3rd traffic lights are Red.
        myDelay(2500);
        }
        PORTB = 0x11; // 2nd yellow ON & 1st is RED
        myDelay(750);
               loop = 0x04;
while(loop) {
            if(PORTA & 0x08)  // RA3
            {
            loop = 0x00;
            }
            else
            {
            loop -- ;  // 0x03
            }
        //3rd Case:
        PORTB = 0x09; //Both 1st & 2nd are Red
        PORTD = 0x0C; //3rd is green & 4th is Red
        myDelay(2500);
        }
        PORTD = 0x0A; // 3rd is yellow & 4th is Red.
        myDelay(750);
               loop = 0x04;
while(loop) {
            if(PORTA & 0x10)  // RA4
            {
            loop = 0x00;
            }
            else
            {
            loop -- ;  // 0x03
            }
        //4th case
        PORTB = 0x09; //Both 1st & 2nd are Red
        PORTD = 0x21; //4th is green & 3rd is Red
        myDelay(2500);
        }
        PORTD = 0x11; // 4th is yellow & 3rd is red
        myDelay(750);

}


void f_Delay(unsigned int ms_Count)
{
    unsigned int i,j;
    for(i=0;i<ms_Count;i++)
    {
        for(j=0;j<500;j++);
    }
}

void Khaled(){

        //5th traffic light:
        PORTC = 0x10; //RC4 (Red)
        f_Delay(500);

        //3rd Case:
        PORTB = 0x09; //Both 1st & 2nd are Red
        PORTD = 0x0C; //3rd is green & 4th is Red
        f_Delay(3500);
        PORTD = 0x0A; // 3rd is yellow & 4th is Red.
        f_Delay(700);

}