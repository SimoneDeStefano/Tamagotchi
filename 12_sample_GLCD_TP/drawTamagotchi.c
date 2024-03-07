#include "drawTamagotchi.h"
//int first = 0;
extern int hr , min , sec;
extern int happines,satiety, space,fuga,flag,dead;
extern int factor,coccole;
extern int freqs[8];
void Tamagotchi_Initialization(void){
	
	
	char time_in_char[20] = " ";
	int space = 0 , i ;
	hr =0, min =0, sec = 0,flag=0,satiety=0,happines=0;
	coccole = 0;
	dead = 0;
	LCD_Clear(White);
	//meal();
	LCD_DrawLine(0,280 , 240 , 280 , Black);
	LCD_DrawLine(120,280 , 120 , 320 , Black);
	GUI_Text(45 , 292 , (uint8_t*)"Meal" , Black , White);
	//snack();
	GUI_Text(165 , 292 , (uint8_t*)"Snack" , Black , White);
	//Draw_Happiness_Satiety();
	GUI_Text(30 , 30 ,(uint8_t*)"Happiness" , Black , White);
	GUI_Text(160 , 30 ,(uint8_t*)"Satiety" , Black , White);
	//happines
	LCD_DrawRectangle(30,56,71,30,Black);
	LCD_DrawRectangle(32,58,67,26,White);
	LCD_DrawRectangle(102,62,4,16,Black);
	//satiety
	LCD_DrawRectangle(150,56,71,30,Black);
	LCD_DrawRectangle(152,58,67,26,White);
	LCD_DrawRectangle(222,62,4,16,Black);
	//barre_happines() and satiety;
	for(i = 0 ; i < 6 ; i++){
		LCD_DrawRectangle(33+space,59,10,24,Black);
		LCD_DrawRectangle(153+space,59,10,24,Black);
		space =space + 11;
	}
	bodyTamagotchi1();
	sprintf(time_in_char , "Age: %02u:%02u:%02u " , hr , min , sec);
	GUI_Text(65, 10 , (uint8_t *) time_in_char , Black , White);	
	
	//disegno icona audio
	LCD_DrawRectangle(18,2,2,2,Black);
	LCD_DrawRectangle(16,4,4,2,Black);
	LCD_DrawRectangle(14,6,6,2,Black);
	LCD_DrawRectangle(12,8,8,2,Black);
	LCD_DrawRectangle(2,10,18,2,Black);
	LCD_DrawRectangle(2,12,18,2,Black);
	LCD_DrawRectangle(2,14,18,2,Black);
	LCD_DrawRectangle(2,16,18,2,Black);
	LCD_DrawRectangle(2,18,18,2,Black);
	LCD_DrawRectangle(2,20,18,2,Black);
	LCD_DrawRectangle(12,22,8,2,Black);
	LCD_DrawRectangle(14,24,6,2,Black);
	LCD_DrawRectangle(16,26,4,2,Black);
	LCD_DrawRectangle(18,28,2,2,Black);
	
	//ondine audio
	LCD_DrawRectangle(22,10,2,2,Black);
	LCD_DrawRectangle(24,12,2,6,Black);
	LCD_DrawRectangle(22,18,2,2,Black);
	
	LCD_DrawRectangle(25,6,2,2,Black);
	LCD_DrawRectangle(27,8,2,2,Black);
	LCD_DrawRectangle(28,10,2,10,Black);
	LCD_DrawRectangle(27,20,2,2,Black);
	LCD_DrawRectangle(25,22,2,2,Black);
	
	LCD_DrawRectangle(29,4,2,2,Black);
	LCD_DrawRectangle(31,6,2,4,Black);
	LCD_DrawRectangle(32,10,2,10,Black);
	LCD_DrawRectangle(31,20,2,4,Black);
	LCD_DrawRectangle(29,24,2,2,Black);
	
	//init_timer(0, 0xC8); 				//volume	    /* K(counter) = T * Fre = 1s * 25MHz = 17D7840(1 s) */
	//init_timer(0, 0x02FAF080); 									  //imposto a 2 secondi e uso MR0 e MR1 in modo da generare un interrupt ogni secondo e chimare funzione diverse
	init_timer(1 , 0x004C4B4F);                      //inizializzo il timer per la musica
	init_timer(2 ,0x02FAF080);											//animazione base
	init_timer(3 ,0x000FAF08);											//animazione cibo
	
	//enable_timer(0);
	//enable_timer(1);
	enable_timer(2);
	
	joystick_init();											/* Joystick Initialization            */
	init_RIT(0x004C4B40);									/* RIT Initialization 50 msec    001312D0   	*/
	enable_RIT();	
	
}



void bodyTamagotchi(void){  //queste cordinate le vorrei usare per spostare il disegno
	
	LCD_DrawRectangle(82 , 120  , 30 , 15 , White);  

  LCD_DrawRectangle(142 , 120  , 30 , 15 , White); //165	
	
  //corpo del personaggio
	LCD_DrawRectangle(82  , 135   , 90 , 7 , White);  //linea orizzontale sotto le orecchie
	LCD_DrawRectangle(82  , 142    , 15 , 15 , White);   //parte interna al quadrato sx
	LCD_DrawRectangle(157  , 142    , 15 , 15 , White);  //dx
	
	//guanciotte
	LCD_DrawRectangle(76 , 157  , 7 , 15 , White);
	LCD_DrawRectangle(172 , 157  , 7 , 15 , White);
	//occhi 
	LCD_DrawRectangle(104 , 149  , 8 , 8 , White);
	LCD_DrawRectangle(142 , 149  , 8 , 8 , White);
	//bocca
	LCD_DrawRectangle(112 , 166  , 30 , 7 , White);
	//pezzi del quadrato disegnati ad hoc per velocizzare il disegno
	LCD_DrawRectangle(82 , 172  , 7 , 31 , White); // sx
	LCD_DrawRectangle(165 , 172  , 7 , 8 , White);    // dx
	LCD_DrawRectangle(172 , 180  , 7 , 8 , White);    // dx
	LCD_DrawRectangle(165 , 187  , 7 , 16 , White);    // dx
	LCD_DrawRectangle(89 , 187  , 16 , 7 , White); //braccio sx ok
	LCD_DrawRectangle(98 , 180  , 7 , 7 , White); //mano sx ok
	LCD_DrawRectangle(147 , 180  , 7 , 7 , White); //mano dx  ok 
	LCD_DrawRectangle(154 , 187  , 13 , 7 , White); //braccio dx ok
	//gambe (sono da animare)
	LCD_DrawRectangle(89 , 203  , 7 , 8 , White); // sx  //1 quadro della gamba
	LCD_DrawRectangle(158 , 203  , 7 , 8 , White); // dx	
	LCD_DrawRectangle(96 , 211  , 7 , 8 , White);  // sx   //2 quadro della gamba
	LCD_DrawRectangle(151 , 211  , 7 , 16 , White); // dx	
	LCD_DrawRectangle(110 , 212  , 35 , 7 , White); // dx  //pezzo centrale gamba
	LCD_DrawRectangle(144 , 227  , 7 , 8 , White); // dx
	LCD_DrawRectangle(103 , 219  , 7 , 8 , White);  // sx   //pezzo all'inizio del pezzo centrale
	LCD_DrawRectangle(138 , 219  , 7 , 8 , White); // dx  //piedi
	
	//clearBody1(7,40);//0 ,40
	//orecchie
	LCD_DrawRectangle(75 , 120  , 30 , 15 , Black);  
	LCD_DrawRectangle(75 , 120  , 7 , 7 , White);   //orecchio sx
	LCD_DrawRectangle(98 , 120  , 7 , 7 , White);			//orecchio dx
  LCD_DrawRectangle(135 , 120  , 30 , 15 , Black); //165	
	LCD_DrawRectangle(135 , 120  , 7 , 7 , White);    //orecchie sx
	LCD_DrawRectangle(158 , 120  , 7 , 7 , White);    //orecchie dx
  //corpo del personaggio
	LCD_DrawRectangle(75  , 135   , 90 , 7 , Black);  //linea orizzontale sotto le orecchie
	LCD_DrawRectangle(75  , 142    , 15 , 15 , Black);   //parte interna al quadrato sx
	LCD_DrawRectangle(150  , 142    , 15 , 15 , Black);  //dx
	LCD_DrawRectangle(83  , 150    , 7 , 7 , White);
	LCD_DrawRectangle(150  , 150    , 7 , 7 , White);
	//guanciotte
	LCD_DrawRectangle(69 , 157  , 7 , 15 , Black);
	LCD_DrawRectangle(165 , 157  , 7 , 15 , Black);
	//occhi 
	LCD_DrawRectangle(97 , 149  , 8 , 8 , Black);
	LCD_DrawRectangle(135 , 149  , 8 , 8 , Black);
	//bocca
	LCD_DrawRectangle(105 , 166  , 30 , 7 , Black);	
	//mani (sono da animare)
	LCD_DrawRectangle(75 , 172  , 7 , 8 , Black);  
	LCD_DrawRectangle(69 , 180  , 7 , 8 , Black);
	LCD_DrawRectangle(95 , 180  , 7 , 7 , Black); //mano sx
	LCD_DrawRectangle(142 , 180  , 7 , 7 , Black); //mano dx
	LCD_DrawRectangle(82 , 187  , 13 , 7 , Black); //braccio sx
	LCD_DrawRectangle(142 , 187  , 16 , 7 , Black); //braccio dx
	//pezzi del quadrato disegnati ad hoc per velocizzare il disegno mani
	LCD_DrawRectangle(75 , 187  , 7 , 16 , Black); // sx
	LCD_DrawRectangle(158 , 172  , 7 , 31 , Black); // dx
	//gambe (sono da animare)
	LCD_DrawRectangle(82 , 203  , 7 , 8 , Black); // sx  //1 quadro della gamba
	LCD_DrawRectangle(151 , 203  , 7 , 8 , Black); // dx
	LCD_DrawRectangle(89 , 211  , 7 , 16 , Black);  // sx   //2 quadro della gamba
	LCD_DrawRectangle(144 , 211  , 7 , 8 , Black); // dx
	LCD_DrawRectangle(103 , 212  , 35 , 7 , Black); // dx  //pezzo centrale gamba 
	LCD_DrawRectangle(137 , 219  , 7 , 8 , Black); // dx
	LCD_DrawRectangle(96 , 227  , 7 , 8 , Black);  // sx   //pezzo all'inizio del pezzo centrale
	LCD_DrawRectangle(103 , 219  , 7 , 8 , Black); // dx  //piedi
	

}


void bodyTamagotchi1(void){  //queste cordinate le vorrei usare per spostare il disegno


	
	//orecchie
	LCD_DrawRectangle(75 , 120  , 30 , 15 , White);  
  LCD_DrawRectangle(135 , 120  , 30 , 15 , White); //165	
  //corpo del personaggio
	LCD_DrawRectangle(75  , 135   , 90 , 7 , White);  //linea orizzontale sotto le orecchie
	LCD_DrawRectangle(75  , 142    , 15 , 15 , White);   //parte interna al quadrato sx
	LCD_DrawRectangle(150  , 142    , 15 , 15 , White);  //dx
	//guanciotte
	LCD_DrawRectangle(69 , 157  , 7 , 15 , White);
	LCD_DrawRectangle(165 , 157  , 7 , 15 , White);
	//occhi 
	LCD_DrawRectangle(97 , 149  , 8 , 8 , White);
	LCD_DrawRectangle(135 , 149  , 8 , 8 , White);
	//bocca
	LCD_DrawRectangle(105 , 166  , 30 , 7 , White);	
	//mani (sono da animare)
	LCD_DrawRectangle(75 , 172  , 7 , 8 , White);  
	LCD_DrawRectangle(69 , 180  , 7 , 8 , White);
	LCD_DrawRectangle(95 , 180  , 7 , 7 , White); //mano sx
	LCD_DrawRectangle(142 , 180  , 7 , 7 , White); //mano dx
	LCD_DrawRectangle(82 , 187  , 13 , 7 , White); //braccio sx
	LCD_DrawRectangle(142 , 187  , 16 , 7 , White); //braccio dx
	//pezzi del quadrato disegnati ad hoc per velocizzare il disegno mani
	LCD_DrawRectangle(75 , 187  , 7 , 16 , White); // sx
	LCD_DrawRectangle(158 , 172  , 7 , 31 , White); // dx
	//gambe (sono da animare)
	LCD_DrawRectangle(82 , 203  , 7 , 8 , White); // sx  //1 quadro della gamba
	LCD_DrawRectangle(151 , 203  , 7 , 8 , White); // dx
	LCD_DrawRectangle(89 , 211  , 7 , 16 , White);  // sx   //2 quadro della gamba
	LCD_DrawRectangle(144 , 211  , 7 , 8 , White); // dx
	LCD_DrawRectangle(103 , 212  , 35 , 7 , White); // dx  //pezzo centrale gamba 
	LCD_DrawRectangle(137 , 219  , 7 , 8 , White); // dx
	LCD_DrawRectangle(96 , 227  , 7 , 8 , White);  // sx   //pezzo all'inizio del pezzo centrale
	LCD_DrawRectangle(103 , 219  , 7 , 8 , White); // dx  //piedi
	

  //clearBody(0,40);//7,40
	//orecchie
	LCD_DrawRectangle(82 , 120  , 30 , 15 , Black);  
	LCD_DrawRectangle(82 , 120  , 7 , 7 , White);   //orecchio sx
	LCD_DrawRectangle(105 , 120  , 7 , 7 , White);			//orecchio dx
  LCD_DrawRectangle(142 , 120  , 30 , 15 , Black); //165	
	LCD_DrawRectangle(142 , 120  , 7 , 7 , White);    //orecchie sx
	LCD_DrawRectangle(165 , 120  , 7 , 7 , White);    //orecchie dx
  //corpo del personaggio
	LCD_DrawRectangle(82  , 135   , 90 , 7 , Black);  //linea orizzontale sotto le orecchie
	LCD_DrawRectangle(82  , 142    , 15 , 15 , Black);   //parte interna al quadrato sx
	LCD_DrawRectangle(157  , 142    , 15 , 15 , Black);  //dx
	LCD_DrawRectangle(90  , 150    , 7 , 7 , White);
	LCD_DrawRectangle(157  , 150    , 7 , 7 , White);
	//guanciotte
	LCD_DrawRectangle(76 , 157  , 7 , 15 , Black);
	LCD_DrawRectangle(172 , 157  , 7 , 15 , Black);
	//occhi 
	LCD_DrawRectangle(104 , 149  , 8 , 8 , Black);
	LCD_DrawRectangle(142 , 149  , 8 , 8 , Black);
	//bocca
	LCD_DrawRectangle(112 , 166  , 30 , 7 , Black);
	//pezzi del quadrato disegnati ad hoc per velocizzare il disegno
	LCD_DrawRectangle(82 , 172  , 7 , 31 , Black); // sx
	LCD_DrawRectangle(165 , 172  , 7 , 8 , Black);    // dx
	LCD_DrawRectangle(172 , 180  , 7 , 8 , Black);    // dx
	LCD_DrawRectangle(165 , 187  , 7 , 16 , Black);    // dx
	LCD_DrawRectangle(89 , 187  , 16 , 7 , Black); //braccio sx ok
	LCD_DrawRectangle(98 , 180  , 7 , 7 , Black); //mano sx ok
	LCD_DrawRectangle(147 , 180  , 7 , 7 , Black); //mano dx  ok 
	LCD_DrawRectangle(154 , 187  , 13 , 7 , Black); //braccio dx ok
	//gambe (sono da animare)
	LCD_DrawRectangle(89 , 203  , 7 , 8 , Black); // sx  //1 quadro della gamba
	LCD_DrawRectangle(158 , 203  , 7 , 8 , Black); // dx	
	LCD_DrawRectangle(96 , 211  , 7 , 8 , Black);  // sx   //2 quadro della gamba
	LCD_DrawRectangle(151 , 211  , 7 , 16 , Black); // dx	
	LCD_DrawRectangle(110 , 212  , 35 , 7 , Black); // dx  //pezzo centrale gamba
	LCD_DrawRectangle(144 , 227  , 7 , 8 , Black); // dx
	LCD_DrawRectangle(103 , 219  , 7 , 8 , Black);  // sx   //pezzo all'inizio del pezzo centrale
	LCD_DrawRectangle(138 , 219  , 7 , 8 , Black); // dx  //piedi
}

void selectl(){
	
		LCD_DrawLine(120,280 , 240 , 280 , Black);
		LCD_DrawLine(120,280 , 120 , 320 , Black);
	  LCD_DrawLine(120,320 , 240 , 320 , Black);
		LCD_DrawLine(320,280 , 320 , 320 , Black);
		//GUI_Text(165 , 292 , (uint8_t*)"Snack" , Black , White);
		LCD_DrawLine(0,280 , 120 , 280 , Red);
		LCD_DrawLine(120,280 , 120 , 320 , Red);
	  LCD_DrawLine(0,320 , 120 , 320 , Red);
		LCD_DrawLine(0,280 , 0 , 320 , Red);
	  //GUI_Text(45 , 292 , (uint8_t*)"Meal" , Red , White);
		
}




void selectr(){
		LCD_DrawLine(0,280 , 120 , 280 , Black);
		LCD_DrawLine(120,280 , 120 , 320 , Black);
	  LCD_DrawLine(0,320 , 120 , 320 , Black);
		LCD_DrawLine(0,280 , 0 , 320 , Black);
		//GUI_Text(45 , 292 , (uint8_t*)"Meal" , Black , White);
		LCD_DrawLine(120,280 , 240 , 280 , Red);
		LCD_DrawLine(120,280 , 120 , 320 , Red);
	  LCD_DrawLine(120,320 , 240 , 320 , Red);
		LCD_DrawLine(320,280 , 320 , 320 , Red);
		//GUI_Text(165 , 292 , (uint8_t*)"Snack" , Red , White);
}




void draw_meal(void){
	
	LCD_DrawRectangle(5,166,25,11,White);
	LCD_DrawCircle(20,166 , 5,Black);
	LCD_DrawCircle(30 , 166 , 5 ,Black);
	LCD_DrawCircle(10 , 166 , 5 ,Black);
	LCD_DrawCircle(20,156 , 5,Black);
	LCD_DrawCircle(20,176 , 5,Black);
}

void draw_snack(void){
	
	LCD_DrawRectangle(5,166,25,11,White);
	LCD_DrawRectangle(9,166,25,11,Black);
	LCD_DrawRectangle(5,169,3,5,Black);
	LCD_DrawRectangle(35,169,3,5,Black);
}




void animation_food(int center_x , int center_y){
	LCD_DrawRectangle(38,100,160,160,White);   //anche questo si puo modificare per una pulizia migliore
	/*-------------------------------------------------------------------------*/
	//orecchie
	LCD_DrawRectangle(75 +center_x, 80+center_y  , 30 , 15 , Black);  
	LCD_DrawRectangle(75+center_x , 80+center_y  , 7 , 7 , White);   //orecchio sx
	LCD_DrawRectangle(98+center_x , 80+center_y  , 7 , 7 , White);			//orecchio dx
  LCD_DrawRectangle(135+center_x , 80+center_y  , 30 , 15 , Black); //165	
	LCD_DrawRectangle(135+center_x , 80+center_y  , 7 , 7 , White);    //orecchie sx
	LCD_DrawRectangle(158+center_x , 80+center_y  , 7 , 7 , White);    //orecchie dx
	
  //corpo del personaggio
	LCD_DrawRectangle(75+center_x  , 95+center_y   , 90 , 7 , Black);  //linea orizzontale sotto le orecchie
	LCD_DrawRectangle(75+center_x  , 102+center_y    , 15 , 15 , Black);   //parte interna al quadrato sx
	LCD_DrawRectangle(150+center_x  , 102 +center_y   , 15 , 15 , Black);  //dx
	LCD_DrawRectangle(83 +center_x , 110 +center_y   , 7 , 7 , White);
	LCD_DrawRectangle(150+center_x  , 110+center_y    , 7 , 7 , White);
	//guanciotte
	LCD_DrawRectangle(69+center_x , 117+center_y  , 7 , 15 , Black);
	LCD_DrawRectangle(165+center_x , 117+center_y  , 7 , 15 , Black);
	//occhi 
	LCD_DrawRectangle(97+center_x , 109+center_y  , 8 , 8 , Black);
	LCD_DrawRectangle(135+center_x , 109+center_y  , 8 , 8 , Black);
	//bocca
	LCD_DrawRectangle(105+center_x , 126+center_y  , 30 , 7 , Black);	
	
	//mani (sono da animare)
	LCD_DrawRectangle(75+center_x , 132+center_y  , 7 , 8 , Black);  
	LCD_DrawRectangle(69+center_x , 140+center_y  , 7 , 8 , Black);
	LCD_DrawRectangle(95+center_x , 140+center_y  , 7 , 7 , Black); //mano sx
	LCD_DrawRectangle(142+center_x , 140+center_y  , 7 , 7 , Black); //mano dx
	LCD_DrawRectangle(82 +center_x, 147+center_y  , 13 , 7 , Black); //braccio sx
	LCD_DrawRectangle(142 +center_x, 147+center_y  , 16 , 7 , Black); //braccio dx
	//pezzi del quadrato disegnati ad hoc per velocizzare il disegno mani
	LCD_DrawRectangle(75 +center_x, 147+center_y  , 7 , 16 , Black); // sx
	LCD_DrawRectangle(158+center_x , 132 +center_y , 7 , 31 , Black); // dx
	
	//gambe (sono da animare)
	LCD_DrawRectangle(82 +center_x, 163+center_y  , 7 , 8 , Black); // sx  //1 quadro della gamba
	LCD_DrawRectangle(151 +center_x, 163+center_y  , 7 , 8 , Black); // dx
	LCD_DrawRectangle(89 +center_x, 171+center_y  , 7 , 8 , Black);  // sx   //2 quadro della gamba
	LCD_DrawRectangle(144 +center_x, 171+center_y  , 7 , 8 , Black); // dx
	LCD_DrawRectangle(103 +center_x, 172+center_y  , 35 , 7 , Black); // dx  //pezzo centrale gamba 
	LCD_DrawRectangle(137+center_x , 179+center_y  , 7 , 8 , Black); // dx
	LCD_DrawRectangle(96+center_x , 179+center_y  , 7 , 8 , Black);  // sx   //pezzo all'inizio del pezzo centrale
	
}

void animation_fuga(int center_x){
	LCD_DrawRectangle(0,100,200,160,White);
	//orecchie
	LCD_DrawRectangle(75 +center_x, 120  , 30 , 15 , Black);  
	LCD_DrawRectangle(75+center_x , 120 , 7 , 7 , White);   //orecchio sx
	LCD_DrawRectangle(98+center_x , 120  , 7 , 7 , White);			//orecchio dx
  LCD_DrawRectangle(135+center_x , 120  , 30 , 15 , Black); //165	
	LCD_DrawRectangle(135+center_x , 120  , 7 , 7 , White);    //orecchie sx
	LCD_DrawRectangle(158+center_x , 120  , 7 , 7 , White);    //orecchie dx
	
  //corpo del personaggio
	LCD_DrawRectangle(75+center_x  , 135   , 90 , 7 , Black);  //linea orizzontale sotto le orecchie
	LCD_DrawRectangle(75+center_x  , 142    , 15 , 15 , Black);   //parte interna al quadrato sx
	LCD_DrawRectangle(150+center_x  , 142    , 15 , 15 , Black);  //dx
	LCD_DrawRectangle(83 +center_x , 150    , 7 , 7 , White);
	LCD_DrawRectangle(150+center_x  , 150    , 7 , 7 , White);
	//guanciotte
	LCD_DrawRectangle(69+center_x , 157  , 7 , 15 , Black);
	LCD_DrawRectangle(165+center_x , 157  , 7 , 15 , Black);
	//occhi 
	LCD_DrawRectangle(97+center_x , 149  , 8 , 8 , Black);
	LCD_DrawRectangle(135+center_x , 149  , 8 , 8 , Black);
	//bocca sad
	LCD_DrawRectangle(105+center_x , 171  , 5 , 5 , Black);	
	LCD_DrawRectangle(130+center_x , 171  , 5 , 5 , Black);	
	LCD_DrawRectangle(110+center_x , 169  , 5 , 5 , Black);	
	LCD_DrawRectangle(125+center_x , 169  , 5 , 5 , Black);	
	LCD_DrawRectangle(115+center_x , 167  , 5 , 5 , Black);	
	LCD_DrawRectangle(120+center_x , 167  , 5 , 5 , Black);
	
	//mani (sono da animare)
	LCD_DrawRectangle(75+center_x , 172  , 7 , 8 , Black);  
	LCD_DrawRectangle(69+center_x , 180  , 7 , 8 , Black);
	LCD_DrawRectangle(95+center_x , 180  , 7 , 7 , Black); //mano sx
	LCD_DrawRectangle(142+center_x , 180  , 7 , 7 , Black); //mano dx
	LCD_DrawRectangle(82 +center_x, 187  , 13 , 7 , Black); //braccio sx
	LCD_DrawRectangle(142 +center_x, 187  , 16 , 7 , Black); //braccio dx
	//pezzi del quadrato disegnati ad hoc per velocizzare il disegno mani
	LCD_DrawRectangle(75 +center_x, 187  , 7 , 16 , Black); // sx
	LCD_DrawRectangle(158+center_x , 172  , 7 , 31 , Black); // dx
	
	//gambe (sono da animare)
	LCD_DrawRectangle(82 +center_x, 203  , 7 , 8 , Black); // sx  //1 quadro della gamba
	LCD_DrawRectangle(151 +center_x, 203  , 7 , 8 , Black); // dx
	LCD_DrawRectangle(89 +center_x, 211  , 7 , 16 , Black);  // sx   //2 quadro della gamba
	LCD_DrawRectangle(144 +center_x, 211  , 7 , 16 , Black); // dx
	LCD_DrawRectangle(103 +center_x, 212  , 35 , 7 , Black); // dx  //pezzo centrale gamba 
	LCD_DrawRectangle(137+center_x , 219  , 7 , 8 , Black); // dx
	LCD_DrawRectangle(96+center_x , 219  , 7 , 8 , Black);  // sx   //pezzo all'inizio del pezzo centrale
	
	
}

void animation_coccole(){
	LCD_DrawRectangle(52 , 110  , 6 , 2 , Red); 
	LCD_DrawRectangle(64 , 110  , 6 , 2 , Red); 
	LCD_DrawRectangle(50 , 112  , 10 , 2 , Red); 
	LCD_DrawRectangle(62 , 112  , 10 , 2 , Red);
	LCD_DrawRectangle(48 , 114  , 26 , 2 , Red); 
	LCD_DrawRectangle(46 , 116  , 30 , 2 , Red); 
	LCD_DrawRectangle(46 , 118  , 30 , 2 , Red);
	LCD_DrawRectangle(46 , 120  , 30 , 2 , Red);
	LCD_DrawRectangle(46 , 122  , 30 , 2 , Red);
	LCD_DrawRectangle(46 , 124  , 30 , 2 , Red);	
	LCD_DrawRectangle(48 , 126  , 26 , 2 , Red);
	LCD_DrawRectangle(50 , 128  , 22 , 2 , Red);
	LCD_DrawRectangle(52 , 130  , 18 , 2 , Red);
	LCD_DrawRectangle(54 , 132  , 14 , 2 , Red);
	LCD_DrawRectangle(56 , 134  , 10 , 2 , Red);
	LCD_DrawRectangle(58 , 136  , 6 , 2 , Red);
	LCD_DrawRectangle(60 , 138  , 2 , 2 , Red);
	
	LCD_DrawRectangle(190 , 120  , 6 , 2 , Red); 
	LCD_DrawRectangle(202 , 120  , 6 , 2 , Red); 
	LCD_DrawRectangle(188 , 122  , 10 , 2 , Red); 
	LCD_DrawRectangle(200 , 122  , 10 , 2 , Red);
	LCD_DrawRectangle(186 , 124  , 26 , 2 , Red); 
	LCD_DrawRectangle(184 , 126  , 30 , 2 , Red); 
	LCD_DrawRectangle(184 , 128  , 30 , 2 , Red);
	LCD_DrawRectangle(184 , 130  , 30 , 2 , Red);
	LCD_DrawRectangle(184 , 132  , 30 , 2 , Red);
	LCD_DrawRectangle(184 , 134  , 30 , 2 , Red);	
	LCD_DrawRectangle(186 , 136  , 26 , 2 , Red);
	LCD_DrawRectangle(188 , 138  , 22 , 2 , Red);
	LCD_DrawRectangle(190 , 140  , 18 , 2 , Red);
	LCD_DrawRectangle(192 , 142  , 14 , 2 , Red);
	LCD_DrawRectangle(194 , 144  , 10 , 2 , Red);
	LCD_DrawRectangle(196 , 146  , 6 , 2 , Red);
	LCD_DrawRectangle(198 , 148  , 2 , 2 , Red);
	
	
}


void clear_coccole(){
	LCD_DrawRectangle(52 , 110  , 6 , 2 , White); 
	LCD_DrawRectangle(64 , 110  , 6 , 2 , White); 
	LCD_DrawRectangle(50 , 112  , 10 , 2 , White); 
	LCD_DrawRectangle(62 , 112  , 10 , 2 , White);
	LCD_DrawRectangle(48 , 114  , 26 , 2 , White); 
	LCD_DrawRectangle(46 , 116  , 30 , 2 , White); 
	LCD_DrawRectangle(46 , 118  , 30 , 2 , White);
	LCD_DrawRectangle(46 , 120  , 30 , 2 , White);
	LCD_DrawRectangle(46 , 122  , 30 , 2 , White);
	LCD_DrawRectangle(46 , 124  , 30 , 2 , White);	
	LCD_DrawRectangle(48 , 126  , 26 , 2 , White);
	LCD_DrawRectangle(50 , 128  , 22 , 2 , White);
	LCD_DrawRectangle(52 , 130  , 18 , 2 , White);
	LCD_DrawRectangle(54 , 132  , 14 , 2 , White);
	LCD_DrawRectangle(56 , 134  , 10 , 2 , White);
	LCD_DrawRectangle(58 , 136  , 6 , 2 , White);
	LCD_DrawRectangle(60 , 138  , 2 , 2 , White);
	
	
	LCD_DrawRectangle(190 , 120  , 6 , 2 , White); 
	LCD_DrawRectangle(202 , 120  , 6 , 2 , White); 
	LCD_DrawRectangle(188 , 122  , 10 , 2 , White); 
	LCD_DrawRectangle(200 , 122  , 10 , 2 , White);
	LCD_DrawRectangle(186 , 124  , 26 , 2 , White); 
	LCD_DrawRectangle(184 , 126  , 30 , 2 , White); 
	LCD_DrawRectangle(184 , 128  , 30 , 2 , White);
	LCD_DrawRectangle(184 , 130  , 30 , 2 , White);
	LCD_DrawRectangle(184 , 132  , 30 , 2 , White);
	LCD_DrawRectangle(184 , 134  , 30 , 2 , White);	
	LCD_DrawRectangle(186 , 136  , 26 , 2 , White);
	LCD_DrawRectangle(188 , 138  , 22 , 2 , White);
	LCD_DrawRectangle(190 , 140  , 18 , 2 , White);
	LCD_DrawRectangle(192 , 142  , 14 , 2 , White);
	LCD_DrawRectangle(194 , 144  , 10 , 2 , White);
	LCD_DrawRectangle(196 , 146  , 6 , 2 , White);
	LCD_DrawRectangle(198 , 148  , 2 , 2 , White);
	
	
}

void setVolume(int volume){
	//disegno icona audio
	LCD_DrawRectangle(18,2,2,2,Black);
	LCD_DrawRectangle(16,4,4,2,Black);
	LCD_DrawRectangle(14,6,6,2,Black);
	LCD_DrawRectangle(12,8,8,2,Black);
	LCD_DrawRectangle(2,10,18,2,Black);
	LCD_DrawRectangle(2,12,18,2,Black);
	LCD_DrawRectangle(2,14,18,2,Black);
	LCD_DrawRectangle(2,16,18,2,Black);
	LCD_DrawRectangle(2,18,18,2,Black);
	LCD_DrawRectangle(2,20,18,2,Black);
	LCD_DrawRectangle(12,22,8,2,Black);
	LCD_DrawRectangle(14,24,6,2,Black);
	LCD_DrawRectangle(16,26,4,2,Black);
	LCD_DrawRectangle(18,28,2,2,Black);
	
	if(volume < 500){
	//cancello le ondine audio
	//ondine audio
	LCD_DrawRectangle(22,10,2,2,White);
	LCD_DrawRectangle(24,12,2,6,White);
	LCD_DrawRectangle(22,18,2,2,White);
	
	LCD_DrawRectangle(25,6,2,2,White);
	LCD_DrawRectangle(27,8,2,2,White);
	LCD_DrawRectangle(28,10,2,10,White);
	LCD_DrawRectangle(27,20,2,2,White);
	LCD_DrawRectangle(25,22,2,2,White);
	
	LCD_DrawRectangle(29,4,2,2,White);
	LCD_DrawRectangle(31,6,2,4,White);
	LCD_DrawRectangle(32,10,2,10,White);
	LCD_DrawRectangle(31,20,2,4,White);
	LCD_DrawRectangle(29,24,2,2,White);
	factor=800;
  }
	else if(volume >= 500 && volume <2000){   //volume 1 tacca
	//ondine audio
	LCD_DrawRectangle(22,10,2,2,Black);
	LCD_DrawRectangle(24,12,2,6,Black);
	LCD_DrawRectangle(22,18,2,2,Black);
	
	LCD_DrawRectangle(25,6,2,2,White);
	LCD_DrawRectangle(27,8,2,2,White);
	LCD_DrawRectangle(28,10,2,10,White);
	LCD_DrawRectangle(27,20,2,2,White);
	LCD_DrawRectangle(25,22,2,2,White);
	
	LCD_DrawRectangle(29,4,2,2,White);
	LCD_DrawRectangle(31,6,2,4,White);
	LCD_DrawRectangle(32,10,2,10,White);
	LCD_DrawRectangle(31,20,2,4,White);
	LCD_DrawRectangle(29,24,2,2,White);
	factor=3;
	}
	else if(volume >= 2000 && volume <3000){  //volume 2 tacche
		LCD_DrawRectangle(22,10,2,2,Black);
	LCD_DrawRectangle(24,12,2,6,Black);
	LCD_DrawRectangle(22,18,2,2,Black);
	
	LCD_DrawRectangle(25,6,2,2,Black);
	LCD_DrawRectangle(27,8,2,2,Black);
	LCD_DrawRectangle(28,10,2,10,Black);
	LCD_DrawRectangle(27,20,2,2,Black);
	LCD_DrawRectangle(25,22,2,2,Black);
		
		LCD_DrawRectangle(29,4,2,2,White);
	LCD_DrawRectangle(31,6,2,4,White);
	LCD_DrawRectangle(32,10,2,10,White);
	LCD_DrawRectangle(31,20,2,4,White);
	LCD_DrawRectangle(29,24,2,2,White);
	factor=2;
		
	}
	else if(volume >= 3000){
	
	
	//ondine audio
	LCD_DrawRectangle(22,10,2,2,Black);
	LCD_DrawRectangle(24,12,2,6,Black);
	LCD_DrawRectangle(22,18,2,2,Black);
	
	LCD_DrawRectangle(25,6,2,2,Black);
	LCD_DrawRectangle(27,8,2,2,Black);
	LCD_DrawRectangle(28,10,2,10,Black);
	LCD_DrawRectangle(27,20,2,2,Black);
	LCD_DrawRectangle(25,22,2,2,Black);
	
	LCD_DrawRectangle(29,4,2,2,Black);
	LCD_DrawRectangle(31,6,2,4,Black);
	LCD_DrawRectangle(32,10,2,10,Black);
	LCD_DrawRectangle(31,20,2,4,Black);
	LCD_DrawRectangle(29,24,2,2,Black);
	factor=1;
	}
}


