//#include <pic16f877.h>
#include <xc.h>
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator: High-speed crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE = ON       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown Out Reset Selection bits (BOR enabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.
void DELAY_ms(unsigned int ms_Count)
{
    unsigned int i,j;
    for(i=0;i<ms_Count;i++)
    {
        for(j=0;j<11;j++);
    }
}

#define true 1
#define false 0
typedef int bool;

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lcd.c"
#define _XTAL_FREQ 8000000




int in1;
int in2;
int in3;
bool p1;
bool p2;
bool p3;

char buffer[10];
int mode = 1;
int fisher;
int delayTime;
int h1 = 0;
int min1 = 0;
int sec1 = 0;
int h2 = 0;
int min2 = 0;
int sec2 = 0;
int delay1 = 0;
int delay2 = 0;
int ms1 = 161;
int ms2 = 161;
bool pause = true;
bool whiteMove = true;

bool p1 = false;
bool p2 = false;
bool p3 = false;

void main()
{
    
    
    PORTC = 0x00;
    TRISC = 0; 
    PORTD = 0x00;
    TRISD = 1; 
    LCD lcd = { &PORTC, 2, 3, 4, 5, 6, 7 };
    LCD_Init(lcd);
    while (true){
        LCD_Clear();
        
        
        RC0=1;
      if (RD1 == 1 && in1 == 0){
        p1 = true;
      }
      else{
        p1 = false;
      }
      if (RD2 == 1 && in2 == 0){
        p2 = true;
      }
      else{
        p2 = false;
      }
      if (RD3 == 1 && in3 == 1){
        p3 = true;
      }
      else{
        p3 = false;
      }
        in1 = RD1;
        in2 = RD2;
        in3 = RD3;
        LCD_Set_Cursor(0,1);
        switch(mode){
        case 1:
            sprintf(buffer, "%d", fisher);
          LCD_putrs("fisher: ");
          LCD_putrs(buffer);
          if (p1==true){
            fisher++;
          }
          if (p3==true){
            fisher--;
          }
          if (p2==true){
            mode++;            
          }
          fisher = fisher % 100;
          if (fisher < 0){
            fisher = 99;
          }
          break;

        case 2:
            sprintf(buffer, "%d", delayTime);
          LCD_putrs("delay: ");
          LCD_putrs(buffer);
          if (p1==true){
            delayTime++;
          }
          if (p3==true){
            delayTime--;
          }
          if (p2==true){
            delay1 = delayTime*161;
            delay2 = delayTime*161;
            mode++;
          }
          delayTime = delayTime % 100;
          if (delayTime < 0){
            delayTime = 99;
          }
          break;

        case 3:
            sprintf(buffer, "%d", h1);
          LCD_putrs("white h: ");
          LCD_putrs(buffer);
          if (p1==true){
            h1++;
          }
          if (p3==true){
            h1--;
          }
          if (p2==true){
            mode++;
          }
          h1 = h1 % 60;
          if (h1 < 0){
            h1 = 59;
          }
          break;

        case 4:
            sprintf(buffer, "%d", min1);
          LCD_putrs("white min: ");
          LCD_putrs(buffer);
          if (p1==true){
            min1++;
          }
          if (p3==true){
            min1--;
          }
          if (p2==true){
            mode++;
          }

          min1 = min1 % 60;
          if (min1 < 0){
            min1 = 59;
          }
          break;

        case 5:
            sprintf(buffer, "%d", sec1);
          LCD_putrs("white sec: ");
          LCD_putrs(buffer);
          if (p1==true){
            sec1++;
          }
          if (p3==true){
            sec1--;
          }
          if (p2==true){
            mode++;
          
          }

          sec1 = sec1 % 60;
          if (sec1 < 0){
            sec1 = 59;
                    
          break;

          case 6:
              sprintf(buffer, "%d", h2);
          LCD_putrs("black h: ");
          LCD_putrs(buffer);
          if (p1==true){
            h2++;
          }
          if (p3==true){
            h2--;
          }
          if (p2==true){
            mode++;
          }
          h2 = h2 % 60;
          if (h2 < 0){
            h2 = 59;
          }
          break;

          case 7:
              sprintf(buffer, "%d", min2);
          LCD_putrs("black min: ");
          LCD_putrs(buffer);
          if (p1==true){
            min2++;
          }
          if (p3==true){
            min2--;
          }
          if (p2==true){
            mode++;
          }
          min2 = min2 % 60;
          if (min2 < 0){
            min2 = 59;
          }
          break;

          case 8:
              sprintf(buffer, "%d", sec2);
          LCD_putrs("black sec: ");
          LCD_putrs(buffer);
          if (p1==true){
            sec2++;
          }
          if (p3==true){
            sec2--;
          }
          if (p2==true){
            mode++;
          }
          sec2 = sec2 % 60;
          if (sec2 < 0){
            sec2 = 59;
          }
          break;
          

          case 9:
            if (p2==true){
              if (pause==true){
                pause=false;
              }
              else{
                pause=true;
              }
            }
            LCD_Set_Cursor(0,1);
            sprintf(buffer, "%d", h1);
            LCD_putrs(buffer);
            LCD_putrs(":");
            sprintf(buffer, "%d", min1);
            LCD_putrs(buffer);
            LCD_putrs(":");
            sprintf(buffer, "%d", sec1);
            LCD_putrs(buffer);
            LCD_Set_Cursor(1,7);
            sprintf(buffer, "%d", h2);
            LCD_putrs(buffer);
            LCD_putrs(":");
            sprintf(buffer, "%d", min2);
            LCD_putrs(buffer);
            LCD_putrs(":");
            sprintf(buffer, "%d", sec2);
            LCD_putrs(buffer);
                

            //actual clock
            if (!pause){
            if (whiteMove==true){
              if (delay1 > 0){
                delay1 -= 45;
              }
              else{
                if (ms1 > 0){
                  ms1 -= 45;
                }
                else{
                  sec1 -= 1;
                  ms1 = 161;
                }
              }
              if (sec1 < 0){
                min1 -= 1;
                sec1 = 59;
              }
              if (min1 < 0){
                h1 -= 1;
                min1 = 59;
              }

              if (sec2 > 60){
                min2 += 1;
                sec2 = sec2 - 60;
              }
              if (min2 > 60){
                h2 += 1;
                min2 = min2 - 60;
              }
            }

            else if (whiteMove==false){
              if (delay2 > 0){
                delay2 -= 45;
              }
              else{
                if (ms2 > 0){
                  ms2 -= 45;
                }
                else{
                  sec2 -= 1;
                  ms2 = 161;
                }
              }
              if (sec2 < 0){
                min2 -= 1;
                sec2 = 59;
              }
              if (min2 < 0){
                h2 -= 1;
                min2 = 59;
              }

              if (sec1 > 60){
                min1 += 1;
                sec1 = sec1 - 60;
              }
              if (min1 > 60){
                h1 += 1;
                min1 = min1 - 60;
              }
            }

            }
            //actual clock

            if (p1==true){
              if (whiteMove != true){
                sec2 = sec2 + fisher;
                delay2 = delayTime * 161;
              }
              whiteMove=true;
            }
            if (p3==true){
              if (whiteMove != false){
                sec1 = sec1 + fisher;
                delay1 = delayTime * 161;
              }
              whiteMove=false;
            }
            


          
          //winning by time
          if (h1 < 0){
            pause = true;
            LCD_Clear();
            LCD_putrs("   black won!");
          }
          else if (h2 < 0){
            pause = true;
            LCD_Clear();
            LCD_putrs("   white won!");
          }

            break;
          }
      
      }
      __delay_ms(40);
        
        
        LCD_Set_Cursor(1,0);
    }
        
}

