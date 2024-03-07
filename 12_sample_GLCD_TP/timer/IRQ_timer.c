/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_timer.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    timer.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include <string.h>
#include "lpc17xx.h"
#include "timer.h"
#include "../GLCD/GLCD.h" 
#include "../TouchPanel/TouchPanel.h"
#include "../drawTamagotchi.h"
int hr=0 , min=0 , sec=0;
volatile int happines = 0,satiety=0, space = 0,fuga=0;
volatile int x = 0, i = 8 ,flag=0;//flag mi serve a capire che ho perso
extern int food;
volatile int count = 0;
extern int freqs[8];
extern int factor;
int duration = 2500;
int number_of_note=1;
extern int coccole;
int dead = 0;
int barre=0;
/******************************************************************************
** Function name:		Timer0_IRQHandler
**
** Descriptions:		Timer/Counter 0 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
uint16_t SinTable[45] =                                       /* ÕýÏÒ±í                       */
{
    410, 467, 523, 576, 627, 673, 714, 749, 778,
    799, 813, 819, 817, 807, 789, 764, 732, 694, 
    650, 602, 550, 495, 438, 381, 324, 270, 217,
    169, 125, 87 , 55 , 30 , 12 , 2  , 0  , 6  ,   
    20 , 41 , 70 , 105, 146, 193, 243, 297, 353
};
void TIMER0_IRQHandler (void)        
{
	
	static int ticks=0;
	if(duration > 0){
	duration--;
	/* DAC management */	
	LPC_DAC->DACR = (SinTable[ticks]<<6)/factor;
	ticks++;
	if(ticks==45) ticks=0;
	}
	else{
		reset_timer(0);
		disable_timer(0);
		duration = 2500;
	}

	LPC_TIM0->IR |= 1; /* clear interrupt flag */			
	return;
}

void TIMER1_IRQHandler (void)    //timer per il conteggio delle barre
{
	if(coccole==1){
      if(number_of_note == 11 ){
					init_timer(0,freqs[0]); 
					enable_timer(0);
					number_of_note--;
				}else if(number_of_note == 10  ){
					init_timer(0,freqs[1]); 
					enable_timer(0);
					number_of_note--;
				}else if(number_of_note == 9  ){
					init_timer(0,freqs[2]); 
					enable_timer(0);
					number_of_note--;
				}else if(number_of_note == 8  ){
					init_timer(0,freqs[0]); 
					enable_timer(0);
					number_of_note--;
				}else if(number_of_note == 7  ){
					init_timer(0,freqs[0]); 
					enable_timer(0);
					number_of_note--;
				}else if(number_of_note == 6   ){
					init_timer(0,freqs[1]); 
					enable_timer(0);
					number_of_note--;
				}else if(number_of_note == 5   ){
					init_timer(0,freqs[2]); 
					enable_timer(0);
					number_of_note--;
				}else if(number_of_note == 4   ){
					init_timer(0,freqs[0]); 
					enable_timer(0);
					number_of_note--;
				}else if(number_of_note == 3  ){
					init_timer(0,freqs[2]); 
					enable_timer(0);
					number_of_note--;
				}else if(number_of_note == 2  ){
					init_timer(0,freqs[3]); 
					enable_timer(0);
					number_of_note--;
				}else if(number_of_note == 1 ){
					init_timer(0,freqs[4]); 
					enable_timer(0);
					number_of_note=12;
				}
			}
	
				if(dead==1){
					if(number_of_note == 5){
						init_timer(0,freqs[7]); 
						enable_timer(0);
						number_of_note--;
						LCD_DrawRectangle(152,58,68,26,White);
						animation_fuga(-fuga);
						fuga=fuga+10; 
						coccole = 2;
					}else if(number_of_note == 4){
						init_timer(0,freqs[6]); 
						enable_timer(0);
						number_of_note--;
						LCD_DrawRectangle(152,58,68,26,White);
						animation_fuga(-fuga);
						fuga=fuga+10;
					}else if(number_of_note == 3){
						init_timer(0,freqs[5]); 
						enable_timer(0);
						number_of_note--;
						LCD_DrawRectangle(152,58,68,26,White);
						animation_fuga(-fuga);
						fuga=fuga+10;
					}else if(number_of_note == 2){
						init_timer(0,freqs[4]); 
						enable_timer(0);
						number_of_note--;
						LCD_DrawRectangle(152,58,68,26,White);
						animation_fuga(-fuga);
						fuga=fuga+10;
					}else if(number_of_note == 1){
						LCD_DrawRectangle(0,100,240,220,White);
						LCD_DrawCircle(120,160,50,Black);
						GUI_Text(30 , 130 , (uint8_t*)"The tamagotchi ran away" , Black , White);
						GUI_Text(85 , 145 , (uint8_t*)"Game Over" , Black , White);
						LCD_DrawLine(0,280 , 240 , 280 , Black);
						GUI_Text(100 , 292 , (uint8_t*)"Reset" , Black , White);
						init_timer(0,freqs[3]); 
						enable_timer(0);
						disable_timer(1);
						number_of_note=5;
					}
				}
  LPC_TIM1->IR = 1;/* clear interrupt flag */	
  return;
}
	

void TIMER2_IRQHandler (void)//timer per l'animazione base
{
 char time_in_char[20] = " ";
 if(LPC_TIM2->IR == 1 & flag==0)			
	{
		if(sec <= 59){
			sec++;
			sprintf(time_in_char , "Age: %02u:%02u:%02u " , hr , min , sec);
			GUI_Text(65, 10 , (uint8_t *) time_in_char , Black , White);	
		}
		else if(sec > 59 & min <= 59){
				min++;
				sec = 0;
				sprintf(time_in_char , "Age: %02u:%02u:%02u " , hr , min , sec);
				GUI_Text(65, 10 , (uint8_t *) time_in_char , Black , White);	
			sec++;
		}
		else if(min > 59){
				hr++;
				min = 0;
				sec = 0;
				sprintf(time_in_char , "Age: %02u:%02u:%02u " , hr , min , sec);
				GUI_Text(65, 10 , (uint8_t *) time_in_char , Black , White);	
		}
		bodyTamagotchi();
		barre++;
		LPC_TIM2->IR = 1; /* clear interrupt flag */
	}		
	else if(LPC_TIM2->IR == 2 & flag==0)
	{
		if(sec <= 59){
			sec++;
			sprintf(time_in_char , "Age: %02u:%02u:%02u " , hr , min , sec);
			GUI_Text(65, 10 , (uint8_t *) time_in_char , Black , White);	
		}
		else if(sec > 59 & min <= 59){
				min++;
				sec = 0;
				sprintf(time_in_char , "Age: %02u:%02u:%02u " , hr , min , sec);
				GUI_Text(65, 10 , (uint8_t *) time_in_char , Black , White);	
			sec++;
		}
		else if(min > 59){
				hr++;
				min = 0;
				sec = 0;
				sprintf(time_in_char , "Age: %02u:%02u:%02u " , hr , min , sec);
				GUI_Text(65, 10 , (uint8_t *) time_in_char , Black , White);	
		}
		barre++;
		bodyTamagotchi1();			
		LPC_TIM2->IR = 2;			/* clear interrupt flag MR1*/	
	
}

if(barre == 5){
		barre = 0;
		if(flag==0){
			switch(happines){
				case 0:  LCD_DrawRectangle(88,59,10,24,White); break;
				case 1:  LCD_DrawRectangle(77,59,10,24,White); break;
				case 2:	 LCD_DrawRectangle(66,59,10,24,White); break;
				case 3:	 LCD_DrawRectangle(55,59,10,24,White); break;
				case 4:	 LCD_DrawRectangle(44,59,10,24,White); break;
				case 5:{ LCD_DrawRectangle(33,59,10,24,White);            //qua ho perso
								 dead = 1;
								 enable_timer(1);
								 number_of_note = 5;
								 disable_timer(2);
								 reset_timer(2);
								 disable_RIT();
								 flag=1;
								 enable_RIT();
								 break;
								}
			}
	}
	if(flag==0){
			switch(satiety){
				case 0:  LCD_DrawRectangle(208,59,10,24,White); break;
				case 1:  LCD_DrawRectangle(197,59,10,24,White); break;
				case 2:	 LCD_DrawRectangle(186,59,10,24,White); break;
				case 3:	 LCD_DrawRectangle(175,59,10,24,White); break;
				case 4:	 LCD_DrawRectangle(164,59,10,24,White); break;
				case 5:{ LCD_DrawRectangle(153,59,10,24,White);      //qua ho perso
								 dead = 1;		 
								 enable_timer(1);
								 number_of_note = 5;
								 disable_timer(2);		
								 reset_timer(2);					
								 disable_RIT();
								 flag=1;
								 enable_RIT();
								 break;
								}
			}
	}
	happines++;   //parto da 0 e incremento
	satiety++;
	LPC_TIM2->IR = 3;			/* clear interrupt flag MR1*/
	}
	return;
}

void TIMER3_IRQHandler (void)
{	
	
	if(number_of_note == 4){
		init_timer(0,freqs[5]); 
		enable_timer(0);
		number_of_note--;
	}else if(number_of_note == 3){
		init_timer(0,freqs[2]); 
		enable_timer(0);
		number_of_note--;
	}else if(number_of_note == 2){
		init_timer(0,freqs[1]); 
		enable_timer(0);
		number_of_note--;
	}else if(number_of_note == 1){
		init_timer(0,freqs[2]); 
		enable_timer(0);
		number_of_note=4;
	}
	
	
	//animazione del pet che salto verso il cibo
		if(i%2 == 0){	
			animation_food(x,40);
			x = x - 5;
			i--;
		}
		else if(i%2==1){
			animation_food(x,20);
			x = x - 5;
			i--;
		}
	/*-----------------------------------*/
		if(i==1 & food==0){     //incrementando la satiety
			switch(satiety){
				case 0:{  LCD_DrawRectangle(208,59,10,24,Black); satiety++; break;}
				case 1:  LCD_DrawRectangle(208,59,10,24,Black); break;
				case 2:  LCD_DrawRectangle(197,59,10,24,Black);  break;
				case 3:	 LCD_DrawRectangle(186,59,10,24,Black); break;
				case 4:	 LCD_DrawRectangle(175,59,10,24,Black); break;
				case 5:	 LCD_DrawRectangle(164,59,10,24,Black); break;
				//case 6:	 LCD_DrawRectangle(153,59,10,24,Black);	break;
			}
			satiety--;
			i = 8;
			food=2;
			x=0; //posizione
      LCD_DrawRectangle(0,100,200,170,White);
			//meal();
			LCD_DrawLine(0,280 , 240 , 280 , Black);
			LCD_DrawLine(120,280 , 120 , 320 , Black);
			LCD_DrawLine(0,280 , 0 , 320 , Black);
			GUI_Text(45 , 292 , (uint8_t*)"Meal" , Black , White);
			//snack();
			GUI_Text(165 , 292 , (uint8_t*)"Snack" , Black , White);
			
			reset_timer(3);
			disable_timer(3);
			reset_timer(2);
			enable_timer(2);
			//reset_timer(1);
			//enable_timer(1);
			enable_RIT();
		}
		else if(i==1 & food== 1){  //incremento happines
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
			i = 8;
			food=2;
			x=0; //posizione
			LCD_DrawRectangle(0,100,200,170,White);
			//meal();
			LCD_DrawLine(0,280 , 240 , 280 , Black);
			LCD_DrawLine(120,280 , 120 , 320 , Black);
			LCD_DrawLine(0,280 , 0 , 320 , Black);
			GUI_Text(45 , 292 , (uint8_t*)"Meal" , Black , White);
			//snack();
			GUI_Text(165 , 292 , (uint8_t*)"Snack" , Black , White);
			reset_timer(3);
			disable_timer(3);
			reset_timer(2);
			enable_timer(2);
			//reset_timer(1);
			//enable_timer(1);
			enable_RIT();
		}
  LPC_TIM3->IR = 1;			/* clear interrupt flag */
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
