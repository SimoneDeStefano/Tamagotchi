/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_RIT.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    RIT.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "lpc17xx.h"
#include "RIT.h"
#include "../drawTamagotchi.h"
#include "../timer/timer.h"
#include "../adc/adc.h"
//#include "../led/led.h"

/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

volatile int f = 0;
int food=2;
extern int flag,dead;
volatile int count1 = 0,coccole = 0;
extern int happines;
extern int freqs[8];
volatile int sound = 0;
extern int number_of_note;
void RIT_IRQHandler (void)
{				
	
	static int select = 0 ; //pin 25
	static int left = 0 ; //pin 27
	static int right = 0 ; //pin 28
	
	//joystick select
	if((LPC_GPIO1->FIOPIN & (1<<25)) == 0){	
	  // Joytick Select pressed 
		select++;
		switch(select){
			case 1:
				disable_timer(0);
				reset_timer(0);    
				init_timer(0,freqs[7]); 
				enable_timer(0);
				if(food == 0 & flag==0){//mangiando meal incrementare satiety
					draw_meal();
					disable_timer(2);
					disable_RIT();
					enable_timer(3);
					number_of_note=4;
				}
				else if(food==1 & flag==0){       //incrementare happines
					draw_snack();
					disable_timer(2);
					
					disable_RIT();
					enable_timer(3);
					number_of_note=4;
					
				}
				else if(flag==1){
					GUI_Text(100 , 292 , (uint8_t*)"Reset" , Red , White);
					Tamagotchi_Initialization();
					}
				break;
			default:
				break;
		}
	}
	else{
			select=0;
			
	}
	

	if((LPC_GPIO1->FIOPIN & (1<<27)) == 0 & flag==0){	
		/* Joytick left pressed */
		left++;
		switch(left){
			case 1:
				selectl();
				food=0;
				break;
			default:
				break;
		}
	}
	else{
			left=0;
	}
	
	if((LPC_GPIO1->FIOPIN & (1<<28)) == 0 & flag==0){	
		/* Joytick Right pressed */
		right++;
		switch(right){
			case 1:
				selectr();
				food = 1;
				break;
			default:
				break;
		}
	}
	else{
			right=0;
	}
	
if(coccole != 2){
	//gestione touch
	//char time_in_char[5] = "";
  if(getDisplayPoint(&display, Read_Ads7846(), &matrix )){
		if(display.y > 120 & display.y < 240 & display.x > 60 & display.x < 180){
			//qua voglio mettere la mia animazione coccole
			coccole = 1;
			count1 = 0;
			number_of_note = 11;
		  enable_timer(1);
		}
	}				
	if(coccole ==1){
	count1++;
	animation_coccole();
		if(count1 == 40){ 
					//animazione coccole
					switch(happines){
				case 0:{ LCD_DrawRectangle(88,59,10,24,Black); happines++; break;}
				case 1:  LCD_DrawRectangle(88,59,10,24,Black); break;
				case 2:  LCD_DrawRectangle(77,59,10,24,Black);  break;
				case 3:	 LCD_DrawRectangle(66,59,10,24,Black); break;
				case 4:	 LCD_DrawRectangle(55,59,10,24,Black); break;
				case 5:	 LCD_DrawRectangle(44,59,10,24,Black); break;
				//case 6:	 LCD_DrawRectangle(33,59,10,24,Black);	break;
			}
			happines--;
			clear_coccole();
			coccole=0;
			disable_timer(1);
			reset_timer(1);
				}
				
			}
				
		}
	


	
	ADC_start_conversion();	
	
	LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
