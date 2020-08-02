#include "TM4C123_RTOS_BSP.h"
#include "TM4C123.h"                    // Device header

//-----------------Start of ADC APIs***************************//

void ADC0_Init(void)
{
  /* enable clocks */
    SYSCTL->RCGCGPIO |= 0x10;   /* enable clock to GPIOE (AIN0 is on PE3) */
    SYSCTL->RCGCADC |= 1;       /* enable clock to ADC0 */
    
    /* initialize PE3 for AIN0 input  */
    GPIOE->AFSEL |= 8;       /* enable alternate function */
    GPIOE->DEN &= ~8;        /* disable digital function */
    GPIOE->AMSEL |= 8;       /* enable analog function */
   
    /* initialize ADC0 */
    ADC0->ACTSS &= ~8;        /* disable SS3 during configuration */
    ADC0->EMUX &= ~0xF000;    /* software trigger conversion */
    ADC0->SSMUX3 = 0;         /* get input from channel 0 */
    ADC0->SSCTL3 |= 6;        /* take one sample at a time, set flag at 1st sample */
    ADC0->ACTSS |= 8;       /* enable ADC0 sequencer 3 */
}

	volatile uint32_t _result;

 uint32_t ADC0_getResult(void)
{

	 ADC0->PSSI |= 8;        /* start a conversion sequence 3 */
   while((ADC0->RIS & 8) == 0){} ;   /* wait for conversion complete */
   _result = ADC0->SSFIFO3; /* read conversion result */
   ADC0->ISC = 8;          /* clear completion flag */
	
	 return _result;
}


//-----------------End of ADC APIs***************************//


//-----------------Start of Probe APIs***************************//
void Probe_Init(void)
{
   SYSCTL->RCGCGPIO =(1U<<1);
	 GPIOB->DIR |=(CH0|CH1|CH2|CH3);
	GPIOB->DEN |=(CH0|CH1|CH2|CH3);


}

void Probe_CH0(void)
{
	GPIOB->DATA ^= CH0;
}

void Probe_CH1(void)
{
		GPIOB->DATA ^= CH1;

}
void Probe_CH2(void)
{
	GPIOB->DATA ^= CH2;

}
void Probe_CH3(void)
{
		GPIOB->DATA ^= CH3;

}
//---------------End of Probe APIs*******************************/


//*******************Start of SystemClockConfig APIs******************/
void SystemClock_Config80Mhz(void)
{

  SYSCTL->RCC2 |= SYSCTL_RCC2_USERCC2;
  SYSCTL->RCC2|= SYSCTL_RCC2_BYPASS2;

  SYSCTL->RCC &= ~SYSCTL_RCC_XTAL_M;  
	DelayMs(1);          //Very important

  SYSCTL->RCC += SYSCTL_RCC_XTAL_16MHZ;

  SYSCTL->RCC2 &= ~SYSCTL_RCC2_OSCSRC2_M;

  SYSCTL->RCC2 += SYSCTL_RCC2_OSCSRC2_MO;

  SYSCTL->RCC2 &= ~SYSCTL_RCC2_PWRDN2;
	
  SYSCTL->RCC2|= SYSCTL_RCC2_DIV400;  
  SYSCTL->RCC2 = (SYSCTL->RCC2&~0x1FC00000)  + (4<<22);      
  while((SYSCTL->RIS &SYSCTL_RIS_PLLLRIS)==0){};
  SYSCTL->RCC2 &= ~SYSCTL_RCC2_BYPASS2;
	
}
//*******************************End of SystemClockConfig APIs**************/



//*******************************Start  of Timer APIs**************/

void DelayMs(uint32_t ttime)
{
	 	int i;

		SYSCTL->RCGCTIMER |=2;
	  TIMER1->CTL = 0;
   	TIMER1->CFG = 0x04;    //16-bits mode
	  TIMER1->TAMR = 0x02;        /* periodic mode and down-counter */
    TIMER1->TAILR = 120000 - 1; 
    TIMER1->ICR = 0x1;          /* clear the TimerA timeout flag*/
    TIMER1->CTL |= 0x01;        /* enable Timer A after initialization */
   
	   for(i = 0; i < ttime; i++)
    {
        while ((TIMER1->RIS & 0x1) == 0) ;      /* wait for TimerA timeout flag */
        TIMER1->ICR = 0x1;      /* clear the TimerA timeout flag */
    }
}
/* Setup Timer2A to create 10 Hz interrupt */
void Timer2A_Init(void)
{
    SYSCTL->RCGCTIMER |= 4;     /* enable clock to Timer Block 2   */
    TIMER2->CTL = 0;            /* disable Timer2 before initialization */
    TIMER2->CFG = 0x04;         /* 16-bit option */
    TIMER2->TAMR = 0x02;        /* periodic mode and down-counter */
    TIMER2->TAPR = 250;         /* 16000000 Hz / 250 = 64000 Hz */
    TIMER2->TAILR = 6400;       /* 64000 Hz / 6400 = 10 Hz */
    TIMER2->ICR = 0x1;          /* clear the Timer2A timeout flag */
    TIMER2->IMR |= 0x01;        /* enable Timer2A timeout interrupt */
    TIMER2->CTL |= 0x01;        /* enable Timer2A after initialization */
    NVIC->ISER[0] |= 0x00800000;  /* enable IRQ23 (D23 of ISER[0]) */
}

void TIMER2A_Handler(void)
{
    volatile int readback;
    if (TIMER2->MIS & 0x1)     /* Timer2A timeout flag */
    {            
      /*******Task****/
  			TIMER2->ICR = 0x1;     /* clear the Timer2A timeout flag */
        readback = TIMER2->ICR;   /* a read to force clearing of interrupt flag */
    }
    else
    {   /* should not get here, but if we do */
        TIMER2->ICR = TIMER2->MIS;  /* clear all flags */
        readback = TIMER2->ICR;      /* a read to force clearing of interrupt flag */
    }
}

void Timer3A_Init500HzInt(void){
	     volatile uint32_t delay;

                                // activate timer3
  SYSCTL->RCGCTIMER|= (1U<<3);
                                   // allow time for clock to stabilize
  delay = SYSCTL->RCGCTIMER;          // allow time to finish activating
  TIMER3->CTL =0 ; // disable timer2A during setup
  TIMER3->CFG = 0; // configure for 32-bit timer mode
  TIMER3->TAMR = 0x02;
  TIMER3->TAPR = 0;             // No Prescaler

	TIMER3->TAILR = 32000;          // start value for 500 Hz interrupts
  
	TIMER3->IMR |= 0x01;// enable timeout (rollover) interrupt
  TIMER3->ICR = 0x01;
  TIMER3->CTL|= 0x01;  
                                   // Timer3A=priority 4
	NVIC->IP[35] = 2<<5;  //set to priority level 4
	NVIC_EnableIRQ(35);
}

void TIMER3A_Handler(void)
{
    volatile int readback;
    if (TIMER3->MIS & 0x1)     /* Timer3A timeout flag */
    {            
      /*******Task****/
  			TIMER3->ICR = 0x1;     /* clear the Timer3A timeout flag */
        readback = TIMER3->ICR;   /* a read to force clearing of interrupt flag */
    }
    else
    {   /* should not get here, but if we do */
        TIMER3->ICR = TIMER3->MIS;  /* clear all flags */
        readback = TIMER3->ICR;      /* a read to force clearing of interrupt flag */
    }
}


void WTimer5_Init(void){
	
  SYSCTL->RCGCWTIMER|= 0x20;     // activate clock for Wide Timer5
  while((SYSCTL->PRWTIMER&0x20) == 0){};// allow time for clock to stabilize
  WTIMER5->CTL &= ~0x100;// disable Wide Timer5B during setup
  WTIMER5->CFG = 0x04;// configure for 32-bit timer mode
                                   // configure for periodic mode, default down-count settings
  WTIMER5->TBMR = 0x02;
  WTIMER5->TBILR= 0xFFFFFFFF;    // reload value
  WTIMER5->TBPR = 79;             // 1 MHz resolution
  WTIMER5->ICR = 0x100;// clear WTIMER5B timeout flag
  WTIMER5->IMR &= ~0x100;// disarm timeout interrupt
  WTIMER5->CTL |= 0x100; // enable Wide Timer0B 32-b
}

uint32_t getMicro(void){
  return (0xFFFFFFFF - WTIMER5->TBV);
}

//*******************************End  of Timer APIs**************/


//*******************Start of ST7735 Driver and  APIs******************/

static uint8_t ColStart, RowStart; // some displays need this changed

static int16_t _width = ST7735_TFTWIDTH;
static int16_t _height = ST7735_TFTHEIGHT;
uint32_t StX=0; 
uint32_t StY=0; 
uint16_t StTextColor = YELLOW;
static uint8_t ColStart, RowStart; 
void static writedata(uint8_t d);
void static setAddrWindow(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
void static writecommand(uint8_t c) ;


#define DELAY 0x80
   
void static commandList(const uint8_t *addr) {

  uint8_t numCommands, numArgs;
  uint16_t ms;

  numCommands = *(addr++);               
  while(numCommands--) {                
    writecommand(*(addr++));             
    numArgs  = *(addr++);                
    ms       = numArgs & DELAY;          
    numArgs &= ~DELAY;                   
    while(numArgs--) {                  
      writedata(*(addr++));             
    }

    if(ms) {
      ms = *(addr++);             
      if(ms == 255) ms = 500;    
      DelayMs(ms);
    }
  }
}
void standard_Init_Cmd(void);


void SSI0_Init(void)
{
	 volatile uint32_t delay;
  ColStart  = RowStart = 0; 

  SYSCTL->RCGCSSI|= 0x01; 
  SYSCTL->RCGCGPIO |= 0x01; 
  while((SYSCTL->PRGPIO&0x01)==0){}; 

  GPIOA->DIR |= 0xC8;             
  GPIOA->AFSEL &= ~0xC8;          
  GPIOA->DEN |= 0xC8;             
  GPIOA->PCTL = (GPIOA->PCTL&0x00FF0FFF)+0x00000000;
  GPIOA->AMSEL&= ~0xC8;          
  LCD_CS0;
  LCD_RS1;
  DelayMs(500);
  LCD_RS0;
  DelayMs(500);
  LCD_RS1;
  DelayMs(500);

  // initialize SSI0
  GPIOA->AFSEL |= 0x2C;           
  GPIOA->DEN |= 0x2C;             
                                        
  GPIOA->PCTL = (GPIOA->PCTL&0xFF0F00FF)+0x00202200;
  GPIOA->AMSEL &= ~0x2C;          // disable analog functionality on PA2,3,5
  SSI0->CR1 &= ~SSI_CR1_SSE;           // disable SSI
  SSI0->CR1 &= ~SSI_CR1_MS;            // master mode
                                        // configure for system clock/PLL baud clock source
  SSI0->CC = (SSI0->CC&~SSI_CC_CS_M)+SSI_CC_CS_SYSPLL;
  SSI0->CPSR = (SSI0->CPSR&~SSI_CPSR_CPSDVSR_M)+16;
                                        
  SSI0->CPSR = (SSI0->CPSR&~SSI_CPSR_CPSDVSR_M)+10; 
  SSI0->CR0 &= ~(SSI_CR0_SCR_M |       
                  SSI_CR0_SPH |         
                  SSI_CR0_SPO);         
                                       
  SSI0->CR0 = (SSI0->CR0&~SSI_CR0_FRF_M)+SSI_CR0_FRF_MOTO;
  SSI0->CR0 = (SSI0->CR0&~SSI_CR0_DSS_M)+SSI_CR0_DSS_8;
  SSI0->CR1 |= SSI_CR1_SSE;            // enable SSI

standard_Init_Cmd();

}

void 	 ST7735_Init(void )
{
	SSI0_Init();
	 ST7735_SetCursor(0,0);
  StTextColor = YELLOW;
 ST7735_FillScreen(BLACK);                 // set screen to black

}

void ST7735_SetCursor(uint32_t newX, uint32_t newY){
  if((newX > 20) || (newY > 15)){       
    return;                           
  }
  StX = newX;
  StY = newY;
}


void ST7735_FillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
  uint8_t hi = color >> 8, lo = color;

  if((x >= _width) || (y >= _height)) return;
  if((x + w - 1) >= _width)  w = _width  - x;
  if((y + h - 1) >= _height) h = _height - y;

  setAddrWindow(x, y, x+w-1, y+h-1);

  for(y=h; y>0; y--) {
    for(x=w; x>0; x--) {
      writedata(hi);
      writedata(lo);
    }
  }
}

void ST7735_FillScreen(uint16_t color) {
  ST7735_FillRect(0, 0, _width, _height, color);  
}

void static writecommand(uint8_t c) {
  while((SSI0->SR&SSI_SR_BSY)==SSI_SR_BSY){};
   DC = DC_COMMAND;
  SSI0->DR = c;                        
                                        
  while((SSI0->SR&SSI_SR_BSY)==SSI_SR_BSY){};
}


void static writedata(uint8_t c) {
  while((SSI0->SR&SSI_SR_TNF)==0){};   
  DC = DC_DATA;
  SSI0->DR = c;                        
}

void static setAddrWindow(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1) {

  writecommand(ST7735_CASET); // Column addr set
  writedata(0x00);
  writedata(x0+ColStart);     // XSTART
  writedata(0x00);
  writedata(x1+ColStart);     // XEND

  writecommand(ST7735_RASET); // Row addr set
  writedata(0x00);
  writedata(y0+RowStart);     // YSTART
  writedata(0x00);
  writedata(y1+RowStart);     // YEND

  writecommand(ST7735_RAMWR); // write to RAM
}


void standard_Init_Cmd(void)
{
	LCD_CS0;           // CS=0   
  LCD_RS0;           // RST=0 

  DelayMs(10);      

  LCD_RS1;           // RST=1
  DelayMs(10);      

   
   writecommand(0x11); 

   DelayMs(120);      

   writecommand (0x3A); //Set Color mode
   writedata(0x05); //16 bits
	 writecommand (0x36);
	 writedata(0x14);
	 writecommand (0x29);//Display on
}

void static pushColor(uint16_t color) {
  writedata((uint8_t)(color >> 8));
  writedata((uint8_t)color);
}

void ST7735_DrawPixel(int16_t x, int16_t y, uint16_t color) {

  if((x < 0) || (x >= _width) || (y < 0) || (y >= _height)) return;

  setAddrWindow(x,y,x,y);

  pushColor(color);
}

void ST7735_DrawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color) {
  uint8_t hi = color >> 8, lo = color;

  if((x >= _width) || (y >= _height)) return;
  if((y+h-1) >= _height) h = _height-y;
  setAddrWindow(x, y, x, y+h-1);

  while (h--) {
    writedata(hi);
    writedata(lo);
  }
}

void ST7735_DrawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color) {
  uint8_t hi = color >> 8, lo = color;

  if((x >= _width) || (y >= _height)) return;
  if((x+w-1) >= _width)  w = _width-x;
  setAddrWindow(x, y, x+w-1, y);

  while (w--) {
    writedata(hi);
    writedata(lo);
  }
}

void ST7735_DrawBitmap(int16_t x, int16_t y, const uint16_t *image, int16_t w, int16_t h){
  int16_t skipC = 0;                      
  int16_t originalWidth = w;              
  int i = w*(h - 1);

  if((x >= _width) || ((y - h + 1) >= _height) || ((x + w) <= 0) || (y < 0)){
    return;                             
  }
  if((w > _width) || (h > _height)){    
   
    return;
  }
  if((x + w - 1) >= _width){            
    skipC = (x + w) - _width;           
    w = _width - x;
  }
  if((y - h + 1) < 0){                  
    i = i - (h - y - 1)*originalWidth;  
    h = y + 1;
  }
  if(x < 0){                            
    w = w + x;
    skipC = -1*x;                       
    i = i - x;                          
    x = 0;
  }
  if(y >= _height){                     
    h = h - (y - _height + 1);
    y = _height - 1;
  }

  setAddrWindow(x, y-h+1, x+w-1, y);

  for(y=0; y<h; y=y+1){
    for(x=0; x<w; x=x+1){
                                        
      writedata((uint8_t)(image[i] >> 8));
                                        
      writedata((uint8_t)image[i]);
      i = i + 1;                       
    }
    i = i + skipC;
    i = i - 2*originalWidth;
  }
}

void ST7735_DrawCharS(int16_t x, int16_t y, char c, int16_t textColor, int16_t bgColor, uint8_t size){
  uint8_t line; 
  int32_t i, j;
  if((x >= _width)            || 
     (y >= _height)           || 
     ((x + 5 * size - 1) < 0) || 
     ((y + 8 * size - 1) < 0))   
    return;

  for (i=0; i<6; i++ ) {
    if (i == 5)
      line = 0x0;
    else
      line = Font[(c*5)+i];
    for (j = 0; j<8; j++) {
      if (line & 0x1) {
        if (size == 1) 
          ST7735_DrawPixel(x+i, y+j, textColor);
        else {  
          ST7735_FillRect(x+(i*size), y+(j*size), size, size, textColor);
        }
      } else if (bgColor != textColor) {
        if (size == 1) 
          ST7735_DrawPixel(x+i, y+j, bgColor);
        else {  
          ST7735_FillRect(x+i*size, y+j*size, size, size, bgColor);
        }
      }
      line >>= 1;
    }
  }
}

void ST7735_DrawChar(int16_t x, int16_t y, char c, int16_t textColor, int16_t bgColor, uint8_t size){
  uint8_t line; 
  int32_t col, row, i, j;
  if(((x + 5*size - 1) >= _width)  || 
     ((y + 8*size - 1) >= _height) || 
     ((x + 5*size - 1) < 0)        || 
     ((y + 8*size - 1) < 0)){        
    return;
  }

  setAddrWindow(x, y, x+6*size-1, y+8*size-1);

  line = 0x01;        
  for(row=0; row<8; row=row+1){
    for(i=0; i<size; i=i+1){
      for(col=0; col<5; col=col+1){
        if(Font[(c*5)+col]&line){
          for(j=0; j<size; j=j+1){
            pushColor(textColor);
          }
        } else{
          for(j=0; j<size; j=j+1){
            pushColor(bgColor);
          }
        }
      }
      for(j=0; j<size; j=j+1){
        pushColor(bgColor);
      }
    }
    line = line<<1;   // move up to the next row
  }
}
uint16_t ST7735_Color565(uint8_t r, uint8_t g, uint8_t b) {
  return ((b & 0xF8) << 8) | ((g & 0xFC) << 3) | (r >> 3);
}

uint32_t ST7735_DrawString(uint16_t x, uint16_t y, char *pt, int16_t textColor){
  uint32_t count = 0;
  if(y>15) return 0;
  while(*pt){
    ST7735_DrawCharS(x*6, y*10, *pt, textColor, BLACK, 1);
    pt++;
    x = x+1;
    if(x>20) return count;  
    count++;
  }
  return count;  
}

int32_t Ymax,Ymin,X;        
int32_t Yrange; 


void ST7735_PlotClear(int32_t ymin, int32_t ymax){
  ST7735_FillRect(0, 32, 128, 128, ST7735_Color565(228,228,228));
  if(ymax>ymin){
    Ymax = ymax;
    Ymin = ymin;
    Yrange = ymax-ymin;
  } else{
    Ymax = ymin;
    Ymin = ymax;
    Yrange = ymax-ymin;
  }
  X = 0;
}
int TimeIndex;               
int32_t Ymax, Ymin, Yrange;  
uint16_t PlotBGColor; 

void ST7735_SimplePlotPoint(int32_t y)
{
		int32_t j;
  if(y<Ymin) y=Ymin;
  if(y>Ymax) y=Ymax;
  j = 32+(127*(Ymax-y))/Yrange;
  if(j<32) j = 32;
  if(j>159) j = 159;
  ST7735_DrawPixel(X,   j,  BLUE);
  ST7735_DrawPixel(X+1, j,  BLUE);
  ST7735_DrawPixel(X,   j+1,BLUE);
  ST7735_DrawPixel(X+1, j+1,BLUE);
}

void ST7735_PlotPoint(int32_t data1, uint16_t color1){
  data1 = ((data1 - Ymin)*100)/Yrange;
  if(data1 > 98){
    data1 = 98;
    color1 = RED;
  }
  if(data1 < 0){
    data1 = 0;
    color1 = RED;
  }
  ST7735_DrawPixel(TimeIndex + 11, 116 - data1, color1);
  ST7735_DrawPixel(TimeIndex + 11, 115 - data1, color1);
}
void ST7735_PlotIncrement(void){
  TimeIndex = TimeIndex + 1;
  if(TimeIndex > 99){
    TimeIndex = 0;
  }
  ST7735_DrawFastVLine(TimeIndex + 11, 17, 100, PlotBGColor);
}

int32_t lastj=0;

void ST7735_PlotLine(int32_t y)
{
	int32_t i,j;
  if(y<Ymin) y=Ymin;
  if(y>Ymax) y=Ymax;
 
  j = 32+(127*(Ymax-y))/Yrange;
  if(j < 32) j = 32;
  if(j > 159) j = 159;
  if(lastj < 32) lastj = j;
  if(lastj > 159) lastj = j;
  if(lastj < j){
    for(i = lastj+1; i<=j ; i++){
      ST7735_DrawPixel(X,   i,   BLUE) ;
      ST7735_DrawPixel(X+1, i,   BLUE) ;
    }
  }else if(lastj > j){
    for(i = j; i<lastj ; i++){
      ST7735_DrawPixel(X,   i,   BLUE) ;
      ST7735_DrawPixel(X+1, i,   BLUE) ;
    }
  }else{
    ST7735_DrawPixel(X,   j,   BLUE) ;
    ST7735_DrawPixel(X+1, j,   BLUE) ;
  }
  lastj = j;
}

void ST7735_PlotBar(int32_t y){
int32_t j;
  if(y<Ymin) y=Ymin;
  if(y>Ymax) y=Ymax;

  j = 32+(127*(Ymax-y))/Yrange;
  ST7735_DrawFastVLine(X, j, 159-j,BLACK);

}

void ST7735_PlotNext(void){
  if(X==127){
    X = 0;
  } else{
    X++;
  }
}



void ST7735_Drawaxes(uint16_t axisColor, uint16_t bgColor, char *xLabel,char *yLabel1, uint16_t label1Color, char *yLabel2, uint16_t label2Color,int32_t ymax, int32_t ymin)
	{
  int i;

  Ymax = ymax;
  Ymin = ymin;
  Yrange = Ymax - Ymin;
  TimeIndex = 0;
  PlotBGColor = bgColor;
  ST7735_FillRect(0, 0, 128, 160, bgColor);
  ST7735_DrawFastHLine(10, 140, 101, axisColor);
  ST7735_DrawFastVLine(10, 17, 124, axisColor);
  for(i=20; i<=110; i=i+10){
    ST7735_DrawPixel(i, 141, axisColor);
  }
  for(i=17; i<120; i=i+10){
    ST7735_DrawPixel(9, i, axisColor);
  }
  i = 50;
  while((*xLabel) && (i < 100)){
    ST7735_DrawChar(i, 145, *xLabel, axisColor, bgColor, 1);
    i = i + 6;
    xLabel++;
  }
  if(*yLabel2){ // two labels
    i = 26;
    while((*yLabel2) && (i < 50)){
      ST7735_DrawChar(0, i, *yLabel2, label2Color, bgColor, 1);
      i = i + 8;
      yLabel2++;
    }
    i = 82;
  }else{ // one label
    i = 42;
  }
  while((*yLabel1) && (i < 120)){
   ST7735_DrawChar(0, i, *yLabel1, label1Color, bgColor, 1);
    i = i + 8;
    yLabel1++;
  }
}

//*******************End of ST7735 Driver and  APIs******************/



