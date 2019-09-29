// EE380 Project3
//Team 3
//Abdullah Austin Quentin Sayed Zenawi

#include "stml432kc.h" 
#include "string.h"

#define MAX_MESSAGE_SIZE 10

//procedures
void USART1_Init();
void USART1_Read(unsigned char* buffer, unsigned long nBytes);
void USART1_Write(unsigned char* buffer, unsigned long nBytes);
void GPIOA_Init();
void print_integer(int a_value);
void ADC_Init();
void write_sensor_reading(int sensor, float value);
void delay_msec();
void delay_sec();
void delay_min();
void delay_15min();
void send_message(float value);
float get_humidity();
float get_light();
float get_temperature();
float get_moisture();
void I2C1_Init(); 
void I2C1_Stop();
void I2C1_WaitLineIdle();
void I2C1_Start (unsigned long SlaveAddress, char size, char direction);
void GPIOA_Initialize(void);
void setup_table();
void ChangeChannel();
void Timer2Init(void);

//global variables
char sentData[15];
char receivedData[15];
int receiver, transmitter, flag;
float value;
unsigned long k;
unsigned char temp[1];
unsigned long sample =0;
unsigned char zero[1];
unsigned char newLine[2];
unsigned char tab[1];
	
int main(){
	unsigned long int i,j;
	float temperature =23, humidity =50, moisture =80, light =2,moistureHex=0;
	int ADC_value =0;
	GPIOA_Init();
	USART1_Init(); 
	ADC_Init();
	I2C1_Init(); 
  Timer2Init();
	sentData[0] = 0;
	newLine[0] = 13;
	newLine[1] = 10;
	tab[0] = 9;
	zero[0] = '0';
	
	setup_table();

	while(1){
		
		TIM2_CR1 |= (1 << 0);
		while((TIM2_CR1 & 1) != 0);
		
		receiver = 0;
		temperature = get_temperature();
		for(i=0; i<50000; i++);
		humidity = get_humidity();
		
		ADC_CR |= (1 << 2); //Start ADC
		k=0;
		while( ((ADC_ISR &4) ==0) && k < 100000)
			k++;
		ADC_value = ADC_DR; //Read in val from sensor
		light = ADC_value;
		ChangeChannel(); // function call
		ADC_CR |= (1 << 2); //Start ADC
		k=0;
		while( ((ADC_ISR &4) ==0) && k < 100000)
			k++;
		ADC_value = ADC_DR; //Read in val from sensor
		moisture = 100 - (ADC_value - 0x705) * 100/(0xD55 -0x705);
		moistureHex = ADC_value;
		ChangeChannel(); //function call
				
	if(sample ==0)
		USART1_Write(zero, 1);
	else
		send_message(sample);
	
		USART1_Write(tab, 1);
		write_sensor_reading(1, temperature);
		USART1_Write(tab, 1);
		write_sensor_reading(2, humidity);
		USART1_Write(tab, 1);
		write_sensor_reading(3, moisture);
		USART1_Write(tab, 1);
		write_sensor_reading(4, light);
		USART1_Write(tab, 1);
		write_sensor_reading(3, moistureHex);

		USART1_Write(newLine, 2);
		sample++;
		
	}
	return 0;
}
void setup_table(){
	
	unsigned char ready[5];
	unsigned char SampleStr[7] = "Sample#";
	unsigned char sensor1[4] = "Temp";
	unsigned char sensor2[4] = "AirH";
	unsigned char sensor3[7] = "GroundH";
	unsigned char sensor4[5] = "Light";
	unsigned char sensorBackup[10] = "GroundHHex";
	unsigned char value[5] = "Value";
	
	//USART1_Read(ready, 3); 	//wait until openlog is ready
	for( k=0; k<60000; k++);
	
	k=0;
	USART1_Write(SampleStr, 7);
	
	USART1_Write(tab, 1);
	USART1_Write(sensor1, 4);
	
	USART1_Write(tab, 1);
	USART1_Write(sensor2, 4);
	
	USART1_Write(tab, 1);
	USART1_Write(sensor3, 7);
	
	USART1_Write(tab, 1);
	USART1_Write(sensor4, 5);

	USART1_Write(tab, 1);
	USART1_Write(sensorBackup, 10);
	
	USART1_Write(newLine, 2);
	USART1_Write(newLine, 2);
}
float get_humidity(){
	int i;	
	float humidityValue =0;
	sentData[0] = 0xE5; // triggers the humidity sensor
	
	I2C1_Start(((0x40 << 1)), 1, 0); 
  for(i=0; i<=500000;i++); 		
	I2C1_Start(((0x40 << 1)), 2, 1);
		
  for(i=0; i<=500000;i++); // delay
	humidityValue = 256.0 * (receivedData[0])+ receivedData[1];
	humidityValue = -6 + 125*(humidityValue/(65536));
	return humidityValue;
}
float get_temperature(){
	int i;	
	float temperatureValue = 0;
	sentData[0] = 0xE3; // triggers the humidity sensor
	
	I2C1_Start(((0x40 << 1)), 1, 0); 
  for(i=0; i<=500000;i++); 		
	I2C1_Start(((0x40 << 1)), 2, 1);
		
  for(i=0; i<=500000;i++); // delay
	temperatureValue = 256.0 * (receivedData[0])+ receivedData[1];
	temperatureValue = -46.85 + 168.5*(temperatureValue/(65536));
	return temperatureValue;
}
void write_sensor_reading(int sensor, float value){
	if(value ==0)
		USART1_Write(zero, 1);
	else
		send_message(value);
}
void GPIOA_Init(){
	
	// enable GPIO clock and configure the TX pin  and the RX pin as:
	// alternate function, high speed, push-pull, pull-up
	
	//GPIOA initialization for USART1
	//PB.6 = AF7 (USART1_TX), PB.7 = AF7(USART1_RX), see appendix I
	RCC_AHB2ENR |= 1 << 1; // enable GPIO port B clock
	
	//00 = input, 01 = output, 10 = alternate function, 11 = analog
	GPIOB_MODER &= ~(0xF << (2*6)); // clear mode bits for pin 6 and 7
	GPIOB_MODER |= 0xA << (2*6); //select alternate function mode
	
	//alternative function 7 = USART 1
	//Appendix I shows all alternate functions
	GPIOB_AFRL |= 0x77 << (4*6); // set pin 6 and 7 to AF7
	
	//GPIOA speed: 00 = low speed, 01 = medium speed,
  //								 10 = fast speed,11 = high speed
	GPIOB_OSPEEDR |= 0xF << (2*6);
	
	//GPIO push-pull 00 = no pull-up/pull-down, 01 - pull-up (01)
	//							 10 = pull down, 11 = reserved
	GPIOB_PUPDR &= ~(0xF<<(2*6));
	GPIOB_PUPDR |= 0x5 << (2*6); // select pullup
	
	//GPIO output type: 0 = push-pull, 1 = open drain
	GPIOB_OTYPER &= ~(0x3<<6);
	

	// GPIOA Initialization for sensors	
	RCC_AHB2ENR |= 1; // enable port A clock
	GPIOA_MODER &= ~(3<<(2*9)); // clear PA9
	GPIOA_MODER &= ~(3<<(2*10)); // clear PA10
	GPIOA_MODER |= 2<<(2*9); // PA9 alt function
	GPIOA_MODER |= 2<<(2*10); // PA10 alt function
	GPIOA_AFRH |= 4 << (4* (9-8)); // PA9 I2C1_SCL
	GPIOA_AFRH |= 4 << (4* (10-8)); // PA10 I2C1_SDA
	GPIOA_OTYPER |= 1<<9; //PA9 open drain
	GPIOA_OTYPER |= 1<<10; //PA10 open drain
	NVIC_ISER0 |= (1<<31); //I2C1 interrupt initialize
	
}
void USART1_Init(){
	int i;
	
	RCC_APB2ENR |= 1 << 14; // USART clock enable
	
	//disable USART
	USART1_CR1 &= ~USART_CR1_UE;
	
	//set data length to 8bits
	// 00 = 8 data bits, 01 = 9 data bits, 10 = 7 data bits
	
	USART1_CR1 &= ~USART_CR1_M0;
	USART1_CR1 &= ~USART_CR1_M1;

	//select 1 stop bit
	//00 = 1 stop bit	   01 = 0.5 stop bit
	//10 = 2 stop bits   11 = 1.5 stop bit
	
	USART1_CR2 &= ~USART_CR2_STOP;
	
	// set parity control as a no parity
	// 0 = no parity,
	// 1 = parity enabled (then, program PS bit to select Even or Odd parity)
	USART1_CR1 &= USART_CR1_PCE;
	
	// Oversample by 16
	// 0 = oversampling by 16, 1 = oversampling by 8
	USART1_CR1 &= ~USART_CR1_OVER8;
	
	// set Baud rate to 9600 using APB frequency (4MHz)
	// see example 1 in section 22.1.1
	USART1_BRR = 0x1A1;
	
	// enable transmission and reception 
	USART1_CR1 |= (USART_CR1_TE | USART_CR1_RE);
	
	// enable USART
	USART1_CR1 |= USART_CR1_UE;
	
	// verify that USART is ready for transmission
	// TEACK: tramsmit enable acknowledge flag. HArdware sets or resets iot.
	k=0;
	while( ((USART1_ISR & USART_ISR_TEACK) == 0) && k <1000000 )
		k++;
	// verify that USART is ready for reception
	// REACK: Receive enable acknowledge flag. HArdware sets or resets it.
	k =0;
	while(((USART1_ISR &USART_ISR_REACK) ==0) && k <1000000)
		k++;
	for(i =0; i<50000; i++);
}

void USART1_Read(unsigned char* buffer, unsigned long nBytes){
	int i;
	
	for(i =0; i< nBytes; i++){
		k=0;
		while( (!(USART1_ISR & USART_ISR_RXNE)) && k <1000000) // wait until hardware sets RXNE
			k++;
		buffer[i] = USART1_RDR;								 // Reading RDR clears RXNE
	}
}
void USART1_Write(unsigned char* buffer, unsigned long nBytes){
	int i;
	
	for(i=0; i< nBytes; i++){
		k=0;
		while( (!(USART1_ISR & USART_ISR_TXE)) && k <1000000) // wait until hardware sets TXE
			k++;
		USART1_TDR = buffer[i] & 0xFF;       // writing to TDR clears TXE flag
	}
	
	// wait until TX bit is set. TC is set by hardware and cleared by software.
	k=0;
	while( (!(USART1_ISR & USART_ISR_TC)) && k <1000000)	// TC: Transmission complete flag
		k++;
	k=0;
	
	// writing 1 to the TCCF bit in ICR clears the TC bit in ISR
	USART1_ICR |= USART_ICR_TTCF; //TCCF: Transmission complete clear flag
}

void ADC_Init(void){
	int i;
	RCC_AHB2ENR |= (1 << 13); //ADC clk enable 
	//mode defaults to analog, so no need to set this up (PA1 Analog)
	GPIOA_PUPDR &= ~(0xF); //PA0/1 no pull up or down
	ADC_CR &= ~(1 << 29); //clr deep pwr down 
	ADC_CR |= (1 << 28); //enable voltage regulator
	for(i=0;i<10000;i++); //delay loop
	ADC_CCR |= (1 << 22); //Enables Vref channel
	ADC_CCR |= (1 << 16); //ADC clk mode
	ADC_ISR |= 1; //ADC ready to start conversion
	ADC_CR |= 1; //Enable ADC
	while((ADC_ISR & 0x1) == 0); //Wait for ready flag
	ADC_SQR1 |= 0x180; //Sets channel 6 as 1st conversion
	
}

void ChangeChannel(){
	int i;
	ADC_CR |= (1 << 4); //Stops conversion
	if(flag == 0){ //Checks for flag var
		ADC_SQR1 &= ~(0x180); //clears channel
		ADC_SQR1 |= 5 << 6; //Sets channel 5 as 1st conversion
		flag = 1; //Set to 1 so channel will be switched to 6 next
	}else if(flag == 1){ 
		ADC_SQR1 &= ~(5<<6); //clears channel
		ADC_SQR1 |= 0x180; //Sets channel 6 as 1st conversion
		flag = 0; //Set to 0 so channel will be switched to 7 next
	}
	ADC_CR |= (1 << 2); //Start ADC
	for(i=0;i<1000;i++); //delay
}

void send_message(float value){
	int i;
	char message[MAX_MESSAGE_SIZE];
	for(i=0; i<10; i++)
		message[i] = 0;
	
	sprintf(message, "%.2f", value);
	USART1_Write(message, strlen(message));
	
}
void I2C1_Init(){
	int OwnAddress = 0xC2;
	
	//enable the I2C clock and select SYSCLK as the Source
	RCC_APB1ENR |= 1 << 21; //I2C1 clock enable 
	
	//I2C CR1 Configuration
	//when the I2C is disabled (PE = 0), the I2C performs a software reset
	I2C1_CR1 &=~ I2C_CR1_PE; // Disable I2C
	I2C1_CR1 &= ~I2C_CR1_ANOFF;  // 0: Analog noise filter enabled
	I2C1_CR1 &= ~I2C_CR1_DNF; //0000: Digital filter disabled
	I2C1_CR1 |= I2C_CR1_ERRIE; //Errors interrupt enable
	I2C1_CR1 &= ~I2C_CR1_NOSTRETCH; // Enable clock stretching
	I2C1_CR1 |= I2C_CR1_ADDRIE; //ADDR interrupt enable
	I2C1_CR1 |= I2C_CR1_TXIE; //TX interrupt enable
	I2C1_CR1 |= I2C_CR1_RXIE; //RX interrupt enable
	I2C1_CR1 |= I2C_CR1_TCIE; //TC interrupt enable

	//I2C TIMINGR Configuration
	I2C1_TIMINGR = 0;
	//sysTimer = 80MHz, presc = 7, 800MHz/1+7 = 10 MHz
	I2C1_TIMINGR &= ~ I2C_TIMINGER_PRESC // clear the prescaler
	I2C1_TIMINGR |= 7<<28; // set clock prescaler to 7
	I2C1_TIMINGR |= 49; // SCLL: SCL Low Period(master mode) > 4.7us
	I2C1_TIMINGR |= 49<<8; //SCLH: SCL high period(master mode) > 4.0us
	I2C1_TIMINGR |= 14<<20; //SCLDEL: Data setup time >100us
	I2C1_TIMINGR |= 15<<16; //SDADEL: Data hold time > 1.25 us
	
	//I2C Own address 1 register (I2C_OAR1)
	I2C1_OAR1 &= ~I2C_OAR1_OA1EN;
	I2C1_OAR1 = I2C_OAR1_OA1EN | OwnAddress; // 7bit own address
	I2C1_OAR2 &= ~I2C_OAR2_OA2EN; //Disable own address 2
	
	//I2C CR2 Configuration
	I2C1_CR2 &= ~I2C_CR2_ADD10; // 0 = 7-bit mode, 1 = 10-bit mode
	I2C1_CR2 |= I2C_CR2_AUTOEND;// Enable the auto end
	I2C1_CR2 |= I2C_CR2_NACK; // for slave mode: set NACK
	I2C1_CR1 |= I2C_CR1_PE; // peripheral enable
}

void I2C1_Start (unsigned long SlaveAddress, char size, char direction){
	//direction = 0: master requests a write transfer
	//direction = 1: master requests a read transfer
			
	unsigned long tmpreg = I2C1_CR2;
	tmpreg &= (unsigned long) ~ ((unsigned long)		(I2C_CR2_SADD | I2C_CR2_NBYTES |
																									 I2C_CR2_RELOAD| I2C_CR2_AUTOEND|
																									 I2C_CR2_RD_WRN| I2C_CR2_START  |
																									 I2C_CR2_STOP));
	if(direction == READ_FROM_SLAVE)
		tmpreg |= I2C_CR2_RD_WRN; //Read from slave
	else
		tmpreg &= ~I2C_CR2_RD_WRN; //write to slave
			
	tmpreg |= (unsigned long)(((unsigned long) SlaveAddress & I2C_CR2_SADD) |
															 (((unsigned long) size << 16) & I2C_CR2_NBYTES));
			
	tmpreg |= I2C_CR2_START;
	I2C1_CR2 = tmpreg;
	//I2C1_TXDR = 0x09;
}
		
void I2C1_Stop(){
	//master: generate stop bit after the current byte has been transferred
	I2C1_CR2 |= I2C_CR2_STOP;
			
	//wait until STOPF flag is reset
	k=0;
	while( ((I2C1_ISR & I2C_ISR_STOPF) == 0) && k<100000) 
		k++;
			
	I2C1_ICR |= I2C_ICR_STOPCF; //write 1 to clear stopf flag
}
		
void I2C1_WaitLineIdle(){
	//wait until I2C bus is ready
	k=0;
	while( ((I2C1_ISR & I2C_ISR_BUSY) == I2C_ISR_BUSY) && k < 100000) //if busy, wait
		k++;
	k=0;
}
void I2C1_EV_IRQHandler(){
	//why am i in here
	
	char direction; // read or write?
	char Recieved_Address; 
	
	if (I2C1_ISR & I2C_ISR_ADDR) // check to see if slave is called
	{			
		 
		I2C1_ICR|=I2C_ISR_ADDR; 
		Recieved_Address = ((I2C1_ISR & I2C_ISR_ADDCODE) >> 17);
		direction = ((I2C1_ISR & I2C_ISR_DIR) >> 16);  // means either read or write
		
		if (direction == 1) // read
		{
			//slave writes to master
			//that is I2C1 to I2C3
			//the interrupt will turn off automatically when the data is read out of the TXDR
			I2C1_TXDR = I2C1_TXDR - (I2C1_TXDR & 0xFF) + sentData[0];
	  }
	
	}
	else if (I2C1_ISR & I2C_ISR_TXIS) {
		//TXDR is empty and needs to be reloaded
		
			I2C1_TXDR = I2C1_TXDR - (I2C1_TXDR & 0xFF) + sentData[0];
	}
	else if (I2C1_ISR & I2C_ISR_TC){
		//if transfer is complete, send stop bit
		I2C1_Stop();
	}
	else if (I2C1_ISR & I2C_ISR_RXNE) {
		//This bit is set by hardware when the received data is copied into the I2C_RXDR register, and is
		//ready to be read. It is cleared when I2C_RXDR is read.
		
		//	receivedData[receiver] = I2C1_RXDR;
		//receiver = (receiver+1)%10;
		  receivedData[receiver]  = I2C1_RXDR;
		receiver++;
			//blink_yellow(sentData[0]);
	}
}
void Timer2Init(){
	
	
	RCC_APB1ENR |= (1 << 0);   
	TIM2_CR1 &= ~(1 << 0);
	TIM2_PSC = 59702; 
	TIM2_ARR = 60000; 
	TIM2_CR1 |= ( 1 << 4); 
	TIM2_CR1 |= ( 1 << 3); 
	TIM2_CR1 |= (1 << 0); 
}