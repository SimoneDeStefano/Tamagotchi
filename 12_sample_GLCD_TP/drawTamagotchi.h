#ifndef __TAMAGOTCHI_H
#define __TAMAGOTCHI_H

#include "LPC17xx.h"
#include "GLCD/GLCD.h" 
#include "TouchPanel/TouchPanel.h"
#include "timer/timer.h"
#include "RIT/RIT.h"
#include "joystick/joystick.h"
#include <stdio.h>

extern void bodyTamagotchi(void);
extern void bodyTamagotchi1(void);
extern void clearTamagotchi(void);
extern void selectl(void);
extern void selectr(void);
extern void draw_meal(void);
extern void draw_snack(void);
extern void animation_food(int center_x , int center_y);
extern void animation_fuga(int center_x);
extern void animation_coccole(void);
extern void clear_coccole(void);
extern void setVolume(int volume);
extern void Tamagotchi_Initialization(void);

#endif /* end __TAMAGOTCHI_H */

