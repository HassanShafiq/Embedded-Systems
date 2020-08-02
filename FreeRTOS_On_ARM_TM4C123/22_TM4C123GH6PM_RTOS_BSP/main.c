#include "TM4C123_RTOS_BSP.h"

void drawaxes(void);
void drawInfoBar(void);
#define YMAX 5000
#define YMIN 0

void plotData(void);

volatile uint32_t  sensorValue;
int main(void)
{
		
	Probe_Init();
  ST7735_Init();
	ADC0_Init();
	drawaxes();
  drawInfoBar();

	while(1)
	{
		sensorValue = ADC0_getResult();
 plotData();
	}
}

void drawaxes(void){
    ST7735_Drawaxes(AXISCOLOR, BGCOLOR, "Time", "ADC", LIGHTCOLOR, "", 0, YMAX, YMIN);
}

void drawInfoBar(void)
{
    ST7735_DrawString(1, 0, "CPU =", GREEN);

	    ST7735_DrawString(7, 0, "85%", BLUE );
    ST7735_DrawString(11, 0, "Temp =", GREEN);
   	    ST7735_DrawString(18, 0, "30", BLUE );



}


void plotData(void)
{
	ST7735_PlotPoint(sensorValue,GREEN);
	ST7735_PlotIncrement();
	
	
}
