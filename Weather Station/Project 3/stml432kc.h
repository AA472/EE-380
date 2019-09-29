#define GPIOA_MODER  (*((volatile unsigned long *) 0x48000000))  //GPIOA Mode Register
#define GPIOA_OTYPER (*((volatile unsigned long *) 0x48000004))  //GPIOA Mode Register
#define GPIOA_PUPDR  (*((volatile unsigned long *) 0x4800000C))  //GPIOA pullup pulldown Register
#define GPIOA_AFRL   (*((volatile unsigned long *) 0x48000020))  //GPIOA Mode Register
#define GPIOA_AFRH   (*((volatile unsigned long *) 0x48000024))  //GPIOA Mode Register
#define GPIOA_ODR (*((volatile unsigned long *) 0x48000014))    //GPIOA Input Data Register
#define GPIOA_IDR (*((volatile unsigned long *) 0x48000010))    //GPIOA Input Data Register

#define RCC_AHB2ENR (*((volatile unsigned long *) 0x4002104C))  //GPIO Enable Register
#define RCC_AHB1ENR (*((volatile unsigned long *) 0x40021048))  //GPIO Enable Register

#define RCC_APB1ENR (*((volatile unsigned long *) 0x40021058))  //Peripheral Clock Enable Register
#define RCC_APB2ENR (*((volatile unsigned long *) 0x40021060))  //Peripheral Clock Enable Register
	
#define GPIOB_MODER (*((volatile unsigned long *) 0x48000400))  //GPIOB Mode Register
#define GPIOB_OTYPER (*((volatile unsigned long *) 0x48000404))  //GPIOB Mode Register
#define GPIOB_OSPEEDR (*((volatile unsigned long *) 0x48000408))  //GPIOB speed Register=
#define GPIOB_BSRR (*((volatile unsigned long *) 0x48000418))   //GPIOB Output Bit set/reset Register
#define GPIOB_IDR (*((volatile unsigned long *) 0x48000410))    //GPIOB Input Data Register
#define GPIOB_ODR (*((volatile unsigned long *) 0x48000414))    //GPIOB Input Data Register
#define GPIOB_AFRL (*((volatile unsigned long *) 0x48000420))    //GPIOB Alt Function
#define GPIOB_AFRH   (*((volatile unsigned long *) 0x48000424))  //GPIOB Mode Register
#define GPIOB_PUPDR  (*((volatile unsigned long *) 0x4800040C))  //GPIOB pullup pulldown Register

#define ADC_ISR (*((volatile unsigned long *) 0x50040000))      //ADC Interrupt and Status Register
#define ADC_IER (*((volatile unsigned long *) 0x50040004))      //ADC Interrupt Enable Register
#define ADC_CR (*((volatile unsigned long *) 0x50040008))       //ADC Control Register
#define ADC_SQR1 (*((volatile unsigned long *) 0x50040030))     //ADC Regular Sequence Register
#define ADC_DR (*((volatile unsigned long *) 0x50040040))       //ADC Data Register
#define ADC_CCR (*((volatile unsigned long *) 0x50040308))      //ADC Common Control Register
#define ADC_CFGR (*((volatile unsigned long *) 0x5004000C))      //ADC configuration register

#define TIM2_PSC (*((volatile unsigned long *) 0x40000028))     //Timer 2 Prescaler??
#define TIM2_ARR (*((volatile unsigned long *) 0x4000002c))     //this is for the value to be reloaded into timer 2 that we count to every time
#define TIM2_CCMR1 (*((volatile unsigned long *) 0x40000018))
#define TIM2_CCR1 (*((volatile unsigned long *) 0x40000034))
#define TIM2_CCR2 (*((volatile unsigned long *) 0x40000038)) 
#define TIM2_CR1 (*((volatile unsigned long *) 0x40000000)) //auto reload register
#define TIM2_CCER (*((volatile unsigned long *) 0x40000020)) //TIMx capture/compare enable register
#define TIM2_EGR (*((volatile unsigned long *) 0x40000014)) //event generation register
	
#define NVIC_ISER0 (*((volatile unsigned long *) 0xE000E100)) //event generation register
#define NVIC_ISER1 (*((volatile unsigned long *) 0xE000E104)) //event generation register
#define NVIC_ISER2 (*((volatile unsigned long *) 0xE000E108)) //event generation register

#define SYSCFG_EXTICR1 (*((volatile unsigned long *) 0x40010008)) //event generation register
#define EXTI_IMR1 (*((volatile unsigned long *) 0x40010400)) //event generation register
#define EXTI_RTSR1 (*((volatile unsigned long *) 0x40010408)) //event generation register
#define EXTI_FTSR1 (*((volatile unsigned long *) 0x4001040C)) //event generation register

#define TIM3_DIER (*((volatile unsigned long *) 0x4000040C))     
#define TIM3_CNT (*((volatile unsigned long *) 0x40000424))     
#define TIM3_CCMR1 (*((volatile unsigned long *) 0x40000418))     
#define TIM3_CCER (*((volatile unsigned long *) 0x40000420))     
#define TIM3_PSC (*((volatile unsigned long *) 0x40000428))    
#define TIM3_ARR (*((volatile unsigned long *) 0x4000042c)) 
#define TIM3_EGR (*((volatile unsigned long *) 0x40000414)) //event generation register
#define TIM3_CR1 (*((volatile unsigned long *) 0x40000400)) //auto reload register
#define TIM3_CCR1 (*((volatile unsigned long *) 0x40000434))
#define TIM3_CCR2 (*((volatile unsigned long *) 0x40000438)) 
	

#define I2C1_CR1 (*((volatile unsigned long *) 0x40005400)) 
#define I2C1_CR2 (*((volatile unsigned long *) 0x40005404)) 
#define I2C1_OAR1 (*((volatile unsigned long *) 0x40005408)) 
#define I2C1_OAR2 (*((volatile unsigned long *) 0x4000540C)) 
#define I2C1_TIMINGR (*((volatile unsigned long *) 0x40005410)) 
#define I2C1_TIMEOUTR (*((volatile unsigned long *) 0x40005414)) 
#define I2C1_ISR (*((volatile unsigned long *) 0x40005418)) 
#define I2C1_ICR (*((volatile unsigned long *) 0x4000541C))
#define I2C1_PECR (*((volatile unsigned long *) 0x40005420))
#define I2C1_RXDR (*((volatile unsigned long *) 0x40005424)) 
#define I2C1_TXDR (*((volatile unsigned long *) 0x40005428)) 

#define I2C3_CR1 (*((volatile unsigned long *) 0x40005C00)) 
#define I2C3_CR2 (*((volatile unsigned long *) 0x40005C04)) 
#define I2C3_OAR1 (*((volatile unsigned long *) 0x40005C08)) 
#define I2C3_OAR2 (*((volatile unsigned long *) 0x40005C0C)) 
#define I2C3_TIMINGR (*((volatile unsigned long *) 0x40005C10)) 
#define I2C3_TIMEOUTR (*((volatile unsigned long *) 0x40005C14)) 
#define I2C3_ISR (*((volatile unsigned long *) 0x40005C18)) 
#define I2C3_ICR (*((volatile unsigned long *) 0x40005C1C)) 
#define I2C3_ICR (*((volatile unsigned long *) 0x40005C1C)) 
#define I2C3_PECR (*((volatile unsigned long *) 0x40005C20)) 
#define I2C3_RXDR (*((volatile unsigned long *) 0x40005C24)) 
#define I2C3_TXDR (*((volatile unsigned long *) 0x40005C28)) 


#define USART1_CR1 (*((volatile unsigned long *) 0x40013800)) 
#define USART1_CR2 (*((volatile unsigned long *) 0x40013804)) 
#define USART1_CR3 (*((volatile unsigned long *) 0x40013808)) 
#define USART1_BRR (*((volatile unsigned long *) 0x4001380C)) 
#define USART1_GTPR (*((volatile unsigned long *) 0x40013810)) 
#define USART1_RTOR (*((volatile unsigned long *) 0x40013814)) 
#define USART1_RQR (*((volatile unsigned long *) 0x40013818)) 
#define USART1_ISR (*((volatile unsigned long *) 0x4001381C)) 
#define USART1_ICR (*((volatile unsigned long *) 0x40013820)) 
#define USART1_RDR (*((volatile unsigned long *) 0x40013824)) 
#define USART1_TDR (*((volatile unsigned long *) 0x40013828)) 

#define USART2_CR1 (*((volatile unsigned long *) 0x40004400)) 
#define USART2_CR2 (*((volatile unsigned long *) 0x40004404)) 
#define USART2_CR3 (*((volatile unsigned long *) 0x40004408)) 
#define USART2_BRR (*((volatile unsigned long *) 0x4000440C)) 
#define USART2_GTPR (*((volatile unsigned long *) 0x40004410)) 
#define USART2_RTOR (*((volatile unsigned long *) 0x40004414)) 
#define USART2_RQR (*((volatile unsigned long *) 0x40004418)) 
#define USART2_ISR (*((volatile unsigned long *) 0x4000441C)) 
#define USART2_ICR (*((volatile unsigned long *) 0x40004420)) 
#define USART2_RDR (*((volatile unsigned long *) 0x40004424)) 
#define USART2_TDR (*((volatile unsigned long *) 0x40004428)) 
	


#define DMA2_ISR (*((volatile unsigned long *) 0x40020400))  
#define DMA2_IFCR (*((volatile unsigned long *) 0x40020404))  
#define DMA2_CCR3 (*((volatile unsigned long *) 0x40020430))  
#define DMA2_CNDTR3 (*((volatile unsigned long *) 0x40020434)) 
#define DMA2_CPAR3 (*((volatile unsigned long *) 0x40020438)) 
#define DMA2_CMAR3 (*((volatile unsigned long *) 0x4002043C)) 
#define DMA2_CSELR (*((volatile unsigned long *) 0x400204A8)) 

#define I2C_CR2_ADD10	1<<11          
#define I2C_CR2_NACK	1<<15 
#define I2C_CR2_SADD    0x3FF << 0            
#define I2C_CR2_NBYTES  0xFF<<16         
#define I2C_CR2_RELOAD  1<<24                          
#define I2C_CR2_AUTOEND  1<<25                         
#define I2C_CR2_RD_WRN   1<<10           
#define I2C_CR2_START   1<<13           						 
#define I2C_CR2_STOP    1<<14           
#define I2C_ISR_STOPF   1<<5         
#define I2C_ISR_BUSY   1<<15           
#define I2C_ICR_STOPCF  1<<5           
#define I2C_TIMINGER_PRESC 0xF<<28;
#define I2C_ISR_TXE	1<<0
#define I2C_ISR_TXIS	1<<1  
#define I2C_ISR_ADDCODE	0xFF<<17           
#define I2C_ISR_TC	1<<6          
#define I2C_ISR_NACKF	1<<4          
#define I2C_ISR_ADDR	1<<3           
#define I2C_ISR_DIR	1<<16
#define I2C_ISR_RXNE 1 << 2
#define I2C_RXDR_RXDATA 0xFF 
#define I2C_TXDR_TXDATA	0x7f         
#define I2C_CR1_PE  1 << 0
#define I2C_CR1_TXIE  1 << 1
#define I2C_CR1_RXIE  1 << 2
#define I2C_CR1_ADDRIE  1 << 3
#define I2C_CR1_TCIE  1 << 6
#define I2C_CR1_ANOFF 1<<12
#define I2C_CR1_DNF 0xF<<8
#define I2C_CR1_ERRIE	1<<7       
#define I2C_CR1_SMBUS
#define I2C_CR1_NOSTRETCH	1<<17  
#define I2C_OAR1_OA1EN	1<<15  
#define I2C_OAR2_OA2EN	1<<15 
#define READ_FROM_SLAVE 1
#define WRITE_TO_SLAVE 0
#define LED_ON (1 << 3) 
#define LED_OFF (1 << (3+16))


#define USART_CR1_UE 1 << 0
#define USART_CR1_UESM 1 << 1
#define USART_CR1_RE 1 << 2
#define USART_CR1_TE 1 << 3
#define USART_CR1_PCE 1 << 10
#define USART_CR1_OVER8 1 << 15
#define USART_CR1_M0 1 << 12
#define USART_CR1_M1 1 << 28
#define USART_CR2_STOP 3 << 12
#define USART_ISR_RXNE 1 << 5
#define USART_ISR_TC 1 << 6
#define USART_ISR_TXE 1 << 7
#define USART_ISR_TEACK 1 << 21
#define USART_ISR_REACK 1 << 22
#define USART_ICR_TTCF 1 << 6