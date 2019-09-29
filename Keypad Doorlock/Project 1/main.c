//Abdullah Aljandali
//EE 380
//Project 1	

#define GPIOA_PUPDR (*((volatile unsigned long *) 0x4800000C))  //GPIOA pullup pulldown Register
#define GPIOA_MODER (*((volatile unsigned long *) 0x48000000))  //GPIOB Mode Register
#define GPIOA_OTYPER (*((volatile unsigned long *) 0x48000004))  //GPIOB Mode Register
#define GPIOA_ODR (*((volatile unsigned long *) 0x48000014))  //GPIOB Mode Register
#define GPIOA_IDR (*((volatile unsigned long *) 0x48000010))  //GPIOB Mode Register
#define RCC_AHB2ENR (*((volatile unsigned long *) 0x4002104C))  //GPIO Enable Register


void GPIO_Initialize(void);       //initialize inputs & outputs
unsigned char keypad_scan(void);  //scan one key input
void openLock (void);             //turn on soindexoid and green light
void wrongCode(void);							//wrong code entered
void delay_msec(void);						//a delay of 1 msec
void redLight(void);							//blink red light
void greenLight(void);						//blink green light
void yellowLight(void);						//blink yellow light	
void blueLight(void);						//blink blue light	

void new_passcode(void);					//allow user to input a new password

char passcode[6] = {'#', '#' , '#', '#', '#' , '#'};  //initial password
 
unsigned char key_map [4][3] = {
	{'1', '2' , '3'},
	{'4', '5' , '6'},
	{'7', '8' , '9'},
	{'*', '0' , '#'},
};


int main(){
	 unsigned int i, k, test = 0,
		delayUnpressing =0,
		unpressed = 1, num_stars = 0;
	 
	unsigned char key, index = 0; 
	char input[7];

	GPIO_Initialize();
	while(1){
		
		key = keypad_scan();
		
		if( key == '.'){
			delayUnpressing++;
			if(delayUnpressing>100){	//puts a delay so that the same key doesn't isn't read twice
				unpressed = 1;					//finger up
				delayUnpressing = 0;
			}
		}
		else //add key pressed to inputing
		{			
			if(unpressed == 1){ //if finger was up
				blueLight();
				input[index] = key;
				index++;
				unpressed = 0; //finger down
			}

			if(index == 6){
				index =0; //avoiod buffer overflow
				test = 1;
				num_stars = 0;
				for(k =0; k<6; k++){
					if(input[k] != passcode[k])
						test = 0;
					if(input[k] == '*') //if user enters 6 stars, allow them to change the password
						num_stars++;
					input[k] = '.';
				}
				if (num_stars == 6)
						test = 2;
						
				if (test == 0){	
					wrongCode();
				}
				else if(test == 1) {
					openLock();
				}
				else if(test==2)
					new_passcode();
			}
		}
	}
}

void GPIO_Initialize(void){
	
	RCC_AHB2ENR |= (1<<0); //GPIO A clock enable

	//set pins 0-6 to 00
	GPIOA_MODER &= ~(0x3FFF);
	
	//set pin 4,5,6 to input
	//already set as we cleared it to 0 earlier
	
	//set to no pull up no pull down
	//set by default
	
	//set pin 0,1,2,3 to output
	GPIOA_MODER |= (1<< 2*0);    //pin 0
	GPIOA_MODER |= (1<< 2*1);	   //pin 1	
	GPIOA_MODER |= (1<< 2*2);    //pin 2
	GPIOA_MODER |= (1<< 2*3);    //pin 3

	//configure row pins as open drain to prevent potential circuit shortage
	
	GPIOA_OTYPER |= (1 << 0);
	GPIOA_OTYPER |= (1 << 1);
	GPIOA_OTYPER |= (1 << 2);
	GPIOA_OTYPER |= (1 << 3);
	
	
	//set up PA7 for output for blue LED
	GPIOA_MODER &= ~(3<<2*7);
	GPIOA_MODER |= (1<<2*7);

	//set up PA8  output for red LED
	GPIOA_MODER &= ~(0xFF<<2*8);
  GPIOA_MODER |= (1<< 2*8);    //pin 8

	//set up PA9  output for Green LED
	GPIOA_MODER |= (1<< 2*9);    //pin 9

	//set up PA10 output for yellow LED
	GPIOA_MODER |= (1<< 2*10);    //pin 10
	
	//set up PA11 output for soindexoied
	GPIOA_MODER |= (1<< 2*11);    //pin 11

 }
void new_passcode(void){
	
	int delayUnpressing = 0;
	unsigned int i, test =0, k, unpressed = 1;
	unsigned char key, index = 0; 
	char passcode1[7];
	char passcode2[7];
	char input[7];
	int passcode1_done = 0;
	int passcode2_done = 0;


	for(i = 0; i<3; i++)
		yellowLight();
	greenLight();
	
	while(1){
		
		key = keypad_scan();
		if( key == '.'){
			delayUnpressing++;
			if(delayUnpressing>100){	
				unpressed = 1;
				delayUnpressing = 0;
			}
		}
		
		else //add key pressed to inputing
		{
			if(unpressed == 1){
				if(key == '*')
					redLight();
				else{
					input[index] = key;
					index++;
					unpressed = 0;
					blueLight();
				}
			}

			if(index == 6){
				index =0; //avoiod buffer overflow
				test = 1;
				for(k =0; k<6; k++){
					if(passcode1_done == 0)
						passcode1[k] = input[k];
					else{
						if (input[k] != passcode1[k])
							test = 0;
					}
					input[k] = '.';
				}
				if(passcode1_done ==0){
						passcode1_done =1;
						for(i=0; i<3; i++) yellowLight(); greenLight();
						
				}
				else
					passcode2_done = 1;

				if ((passcode2_done == 1 )&& (test == 1)){	//passwords equal
					for(i=0; i<3; i++) greenLight();
					for(k =0; k<6; k++)
						passcode[k] = passcode1[k];
					break;
				}
				else if((passcode2_done == 1 )&& (test == 0)) { // passwords not equal
					redLight();
					passcode1_done = 0;
					passcode2_done = 0;
					for(k =0; k<6; k++){
						passcode1[k] = '.';
						
					}	
				}
			}
		}
	}
}

unsigned char keypad_scan(void){

	unsigned char row, col, ColumnPressed;
	unsigned char key = 0xFF;
	ColumnPressed = 3;
	//check wether any key has been pressed
	// 1.output zeroes on all row pins
	// 2.delay shortly and read inputs of column pins
	// 3.if inputs are 1 for all columns, then no key has been pressed
	
	
	for(col =0; col < 3; col++){
		if((GPIOA_IDR&(1<<(4+col))) == 0)
			ColumnPressed = col;
	}
	if(ColumnPressed == 3) //if no key pressed,
		return '.';
	
	//identifty the row of the column pressed
	for(row =0; row<4; row++){
		
		//set up the row outputs
		GPIOA_ODR |=0xF;
		//read the column inputs after a short delay
		GPIOA_ODR &= ~(1<<row);
		//check the column inputs
		if((GPIOA_IDR & (1<<(4+ColumnPressed))) == 0) //if the input from the column pi9n ColumnPressed is zero
			key = key_map[row][ColumnPressed];
	}
	GPIOA_ODR &= ~(0xF);

return key;
}


void delay_msec(){
	unsigned int i;
	for( i =0; i < 2050; i++);
}

void delay_sec(){
	unsigned int i;	
	for(i=0; i<1000; i++){delay_msec();}
}

void delay_5sec(){
	unsigned int i;	
	for(i=0; i<5; i++){delay_sec();}
}

void delay_10sec(){
	unsigned int i;	
	for(i=0; i<10; i++){delay_sec();}
}
void yellowLight(){
	
	unsigned int j;
	GPIOA_ODR |= 1<<10;//turn on yellow LED
	for(j = 0;j<100;j++){ delay_msec();}
	GPIOA_ODR &= ~(1<<10);//turn off yellow LED
	for(j = 0;j<100;j++){ delay_msec();}
}
void blueLight(){
	unsigned int j;
	GPIOA_ODR |= 1<<7;//turn on yellow LED
	for(j = 0;j<30;j++){ delay_msec();}
	GPIOA_ODR &= ~(1<<7);//turn off yellow LED
	for(j = 0;j<30;j++){ delay_msec();}
}

void redLight(){
	unsigned int j;
	GPIOA_ODR |= 1<<8;//turn on red LED
	for(j = 0;j<100;j++){ delay_msec();}
	GPIOA_ODR &= ~(1<<8);//turn off red LED
	for(j = 0;j<100;j++){ delay_msec();}

}
void greenLight(){
	unsigned int i,j;
	GPIOA_ODR |= 1<<9;//turn on green LED
	for(j = 0;j<100;j++){ delay_msec();}
	GPIOA_ODR &= ~(1<<9);//turn off green LED
	for(j = 0;j<100;j++){ delay_msec();}

}
void openLock(){
	unsigned int i,j;
	GPIOA_ODR |= 1<<11;//turn on soindexoid port
	for(i =0;i <5; i++) greenLight();
	for(i=0;i <10; i++) yellowLight();
	GPIOA_ODR &= ~(1<<11);//turn off soindexoid port
}

void wrongCode(){
	unsigned int j;
	for(j=0; j<5; j++)redLight();
}