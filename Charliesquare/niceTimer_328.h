/********************************** SIGNATURE *********************************\
|                                      ,,                                      |
|                     db             `7MM                                      |
|                    ;MM:              MM                                      |
|                   ,V^MM.    ,pP"Ybd  MMpMMMb.  .gP"Ya `7Mb,od8               |
|                  ,M  `MM    8I   `"  MM    MM ,M'   Yb  MM' "'               |
|                  AbmmmqMA   `YMMMa.  MM    MM 8M""""""  MM                   |
|                 A'     VML  L.   I8  MM    MM YM.    ,  MM                   |
|               .AMA.   .AMMA.M9mmmP'.JMML  JMML.`Mbmmd'.JMML.                 |
|                                                                              |
|                                                                              |
|                                  ,,    ,,                                    |
|                      .g8"""bgd `7MM    db        `7MM                        |
|                    .dP'     `M   MM                MM                        |
|                    dM'       `   MM  `7MM  ,p6"bo  MM  ,MP'                  |
|                    MM            MM    MM 6M'  OO  MM ;Y                     |
|                    MM.    `7MMF' MM    MM 8M       MM;Mm                     |
|                    `Mb.     MM   MM    MM YM.    , MM `Mb.                   |
|                      `"bmmmdPY .JMML..JMML.YMbmd'.JMML. YA.                  |
|                                                                              |
\******************************************************************************/
/*********************************** LICENCE **********************************\
| Copyright (c) 2012, Asher Glick                                              |
| All rights reserved.                                                         |
|                                                                              |
| Redistribution and use in source and binary forms, with or without           |
| modification, are permitted provided that the following conditions are met:  |
|                                                                              |
| * Redistributions of source code must retain the above copyright notice,     |
|   this list of conditions and the following disclaimer.                      |
| * Redistributions in binary form must reproduce the above copyright notice,  |
|   this list of conditions and the following disclaimer in the documentation  |
|   and/or other materials provided with the distribution.                     |
|                                                                              |
| THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"  |
| AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE    |
| IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE   |
| ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE    |
| LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR          |
| CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF         |
| SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS     |
| INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN      |
| CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)      |
| ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE   |
| POSSIBILITY OF SUCH DAMAGE.                                                  |
\******************************************************************************/
/******************************************************************************\
| The purpose of nice timer is to have easy access to the timers on an atmel   |
| ATmega328. This project is not being actively developed and will only be     |
| updated when another aspect of the ATmega328's timers are required for my    |
| projects. Besides that all of the code is under a BSD-like licence so feel   |
| free to take it an use it for whatever you want. At some point I will make   |
| documentation for it maybe (dont wait for it :P )                            |
\******************************************************************************/
#ifndef _NICE_TIMER_H_
#define _NICE_TIMER_H_

  //////////////////////////////////////////////////////////////////////////////
 ////////////////////////////// TIMER FUNCTIONS /////////////////////////////// 
//////////////////////////////////////////////////////////////////////////////

// Timer 0 Functions (8 bit)
void Timer0_setMode (int mode);
void Timer0_setTimer0Prescaler(int prescaler);
void Timer0_setTimer0Value(byte value);
byte Timer0_getTimer0Value();
void Timer0_setTimer0OutputCompareA(byte value);
void Timer0_setTimer0OutputCompareB(byte value);
void Timer0_enableTimer0CompareAInterrupt();
void Timer0_disableTimer0CompareAInterrupt();
void Timer0_enableTimer0CompareBInterrupt();
void Timer0_disableTimer0CompareBInterrupt();
void Timer0_enableTimer0OverflowInterrupt();
void Timer0_disableTimer0OverflowInterrupt();

// Timer 1 Functions (16 bit)
void Timer1_setMode (int mode);
void Timer1_setPrescaler(int prescaler);
void Timer1_setValue(unsigned int value);
unsigned int Timer1_getValue();
void Timer1_setOutputCompareA(unsigned int value);
void Timer1_setOutputCompareB(unsigned int value);
void Timer1_enableCompareAInterrupt();
void Timer1_disableCompareAInterrupt();
void Timer1_enableCompareBInterrupt();
void Timer1_disableCompareBInterrupt();
void Timer1_enableOverflowInterrupt();
void Timer1_disableOverflowInterrupt();

// Timer 2 Functions (8 bit)
void Timer2_setMode (int mode);
void Timer2_setPrescaler(int prescaler);
void Timer2_setValue(byte value);
byte Timer2_getValue();
void Timer2_setOutputCompareA(byte value);
void Timer2_setOutputCompareB(byte value);
void Timer2_enableCompareAInterrupt();
void Timer2_disableCompareAInterrupt();
void Timer2_enableCompareBInterrupt();
void Timer2_disableCompareBInterrupt();
void Timer2_enableOverflowInterrupt();
void Timer2_disableOverflowInterrupt();

  //////////////////////////////////////////////////////////////////////////////
 ////////////////////////////// Timer 0 Functions /////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/****************************** SET TIMER 0 MODE ******************************\
| This function still needs some more work because i dont understand compleetly|
| what each mode does                                                          |
| Waveform Generation Mode Bit Description                                     |
|                                                                              |
| Mode|WGM2|WGM1|WGM0|Mode of Operation |TOP |Update OCRx at|TOV Flag set on   |
| 0    0    0    0   |Normal            |0xFF| Immediate    |MAX               |
| 1    0    0    1   |PWM, Phase Correct|0xFF| TOP          |BOTTOM            |
| 2    0    1    0   |CTC               |OCRA| Immediate    |MAX               |
| 3    0    1    1   |Fast PWM          |0xFF|BOTTOM        |MAX               |
| 4    1    0    0   |Reserved          | –  | –            |–                 |
| 5    1    0    1   |PWM, Phase Correct|OCRA| TOP          |BOTTOM            |
| 6    1    1    0   |Reserved          |–   | –            | –                |
| 7    1    1    1   |Fast PWM          |OCRA| BOTTOM       |TOP               |
\******************************************************************************/
#define TIMER0_NORMAL 0
void Timer0_setMode (int mode) {
  if (mode == 0) {
    TCCR0A &= ~((1<<WGM01) | (1<<WGM00));
    TCCR0B &= ~(1<<WGM02);
  }
}
/**************************** SET TIMER 0 PRESCALER ***************************\
| The timer 0 prescaler determines when the timer is incremented. If the       |
| prescaler is 1 then the timer is incremented each time the clock ticks, if   |
| the prescaler is 8 then the timer is incremented every 8 cycles. You use     |
| this is you are trying to get small accurate numbers or large less acurate   |
| numbers from a timer                                                         |
\******************************************************************************/
void Timer0_setPrescaler(int prescaler) {
  TCCR0B &= B11111000; 
  if (prescaler == 0)         TCCR0B |= (0<<CS02) | (0<<CS01) | (0<<CS00);
  else if (prescaler == 1)    TCCR0B |= (0<<CS02) | (0<<CS01) | (1<<CS00);
  else if (prescaler == 8)    TCCR0B |= (0<<CS02) | (1<<CS01) | (0<<CS00);
  else if (prescaler == 32)   TCCR0B |= (0<<CS02) | (1<<CS01) | (1<<CS00);
  else if (prescaler == 64)   TCCR0B |= (1<<CS02) | (0<<CS01) | (0<<CS00);
  else if (prescaler == 128)  TCCR0B |= (1<<CS02) | (0<<CS01) | (1<<CS00);
  else if (prescaler == 256)  TCCR0B |= (1<<CS02) | (1<<CS01) | (0<<CS00);
  else if (prescaler == 1024) TCCR0B |= (1<<CS02) | (1<<CS01) | (1<<CS00);
}
/**************************** TIMER 0 DIRECT ACCESS ***************************\
| Set or get the current value for timer0                                      |
\******************************************************************************/
void Timer0_setValue(byte value) {TCNT0 = value;}
byte Timer0_getValue()           {return TCNT0; }

/************************ SET TIMER 0 OUTPUT COMPARE A ************************\
| The Output Compare Register A contains an 8-bit value that is continuously   |
| compared with the counter value (TCNT0). A match can be used to generate an  |
| Output Compare interrupt, or to generate a waveform output on the OC0A pin.  |
\******************************************************************************/
void Timer0_setOutputCompareA(byte value) { OCR0A = value; }

/************************ SET TIMER 0 OUTPUT COMPARE B ************************\
| The Output Compare Register B contains an 8-bit value that is continuously   |
| compared with the counter value (TCNT0). A match can be used to generate an  |
| Output Compare interrupt, or to generate a waveform output on the OC0B pin.  |
\******************************************************************************/
void Timer0_setOutputCompareB(byte value) { OCR0B = value; }



  //////////////////////////////////////////////////////////////////////////////
 ////////////////////////// ENABLE TIMER 0 INTERRUPTS /////////////////////////
//////////////////////////////////////////////////////////////////////////////

/***************** ENABLE/DISABLE TIMER 0 COMPARE A INTERRUPT *****************\
| These two functions will enable or disable the timer 0 compare A interrupt.  |
| Overflow Compare Interrupt Enable 0 A  is register (OCIE0A)                  |
\******************************************************************************/
void Timer0_enableCompareAInterrupt()  { TIMSK0 |=  (1<<OCIE0A); }
void Timer0_disableCompareAInterrupt() { TIMSK0 &= ~(1<<OCIE0A);}

/***************** ENABLE/DISABLE TIMER 0 COMPARE B INTERRUPT *****************\
| These two functions will enable or disable the timer 0 compare B interrupt.  |
| Overflow Compare Interrupt Enable 0 B is register (OCIE0B)                   |
\******************************************************************************/
void Timer0_enableCompareBInterrupt()  { TIMSK0 |=  (1<<OCIE0B); }
void Timer0_disableCompareBInterrupt() { TIMSK0 &= !(1<<OCIE0B); }

/****************** ENABLE/DISABLE TIMER 0 OVERFLOW INTERRUPT *****************\
| These two functions will enable or disable the timer 0 overflow interrupt    |
| Timer Overflow Interrupt Enable 0  is register (TOIE0)                       |
\******************************************************************************/
void Timer0_enableOverflowInterrupt()  { TIMSK0 |=  (1<<TOIE0); }
void Timer0_disableOverflowInterrupt() { TIMSK0 &= ~(1<<TOIE0); }

  //////////////////////////////////////////////////////////////////////////////
 ////////////////////////////// Timer 1 Functions /////////////////////////////
//////////////////////////////////////////////////////////////////////////////


/****************************** SET TIMER 1 MODE ******************************\
| This function still needs some more work because i dont understand compleetly|
| what each mode does                                                          |
| 
\******************************************************************************/
#define TIMER1_NORMAL 0
void Timer1_setMode (int mode) {
  if (mode == 0) {
    TCCR1A &= ~((1<<WGM11) | (1<<WGM10));
    TCCR1B &= ~((1<<WGM12) | (1<<WGM13));
  }
}
/**************************** SET TIMER 1 PRESCALER ***************************\
| The timer 1 prescaler determines when the timer is incremented. If the       |
| prescaler is 1 then the timer is incremented each time the clock ticks, if   |
| the prescaler is 8 then the timer is incremented every 8 cycles. You use     |
| this is you are trying to get small accurate numbers or large less acurate   |
| numbers from a timer                                                         |
\******************************************************************************/
void Timer1_setPrescaler(int prescaler) {
  TCCR1B &= B11111000; 
  if (prescaler == 0)          TCCR1B |= (0<<CS12) | (0<<CS11) | (0<<CS10);
  else if (prescaler == 1)     TCCR1B |= (0<<CS12) | (0<<CS11) | (1<<CS10);
  else if (prescaler == 8)     TCCR1B |= (0<<CS12) | (1<<CS11) | (0<<CS10);
  else if (prescaler == 64)    TCCR1B |= (0<<CS12) | (1<<CS11) | (1<<CS10);
  else if (prescaler == 256)   TCCR1B |= (1<<CS12) | (0<<CS11) | (0<<CS10);
  else if (prescaler == 1024)  TCCR1B |= (1<<CS12) | (0<<CS11) | (1<<CS10);
  else if (prescaler == -1)    TCCR1B |= (1<<CS12) | (1<<CS11) | (0<<CS10);
  else if (prescaler == -2)    TCCR1B |= (1<<CS12) | (1<<CS11) | (1<<CS10);
}
/**************************** TIMER 1 DIRECT ACCESS ***************************\
| Set or get the current value for timer1                                      |
\******************************************************************************/
void Timer1_setValue(unsigned int value) {TCNT1 = value;}
unsigned int Timer1_getValue()           {return TCNT1; }

/************************ SET TIMER 1 OUTPUT COMPARE A ************************\
| The Output Compare Register A contains an 8-bit value that is continuously   |
| compared with the counter value (TCNT1). A match can be used to generate an  |
| Output Compare interrupt, or to generate a waveform output on the OC0A pin.  |
\******************************************************************************/
void Timer1_setOutputCompareA(unsigned int value) { OCR1A = value; }

/************************ SET TIMER 1 OUTPUT COMPARE B ************************\
| The Output Compare Register B contains an 8-bit value that is continuously   |
| compared with the counter value (TCNT1). A match can be used to generate an  |
| Output Compare interrupt, or to generate a waveform output on the OC0B pin.  |
\******************************************************************************/
void Timer1_setOutputCompareB(unsigned int value) { OCR1B = value; }


  //////////////////////////////////////////////////////////////////////////////
 ////////////////////////// ENABLE TIMER 1 INTERRUPTS /////////////////////////
//////////////////////////////////////////////////////////////////////////////



/***************** ENABLE/DISABLE TIMER 1 COMPARE A INTERRUPT *****************\
| These two functions will enable or disable the timer 1 compare A interrupt.  |
| Overflow Compare Interrupt Enable 1 A  is register (OCIE0A)                  |
\******************************************************************************/
void Timer1_enableCompareAInterrupt()  { TIMSK1 |=  (1<<OCIE1A); }
void Timer1_disableCompareAInterrupt() { TIMSK1 &= ~(1<<OCIE1A);}

/***************** ENABLE/DISABLE TIMER 1 COMPARE B INTERRUPT *****************\
| These two functions will enable or disable the timer 0 compare B interrupt.  |
| Overflow Compare Interrupt Enable 1 B is register (OCIE1B)                   |
\******************************************************************************/
void Timer1_enableCompareBInterrupt()  { TIMSK1 |=  (1<<OCIE1B); }
void Timer1_disableCompareBInterrupt() { TIMSK1 &= !(1<<OCIE1B); }

/****************** ENABLE/DISABLE TIMER 1 OVERFLOW INTERRUPT *****************\
| These two functions will enable or disable the timer 1 overflow interrupt    |
| Timer Overflow Interrupt Enable 1  is register (TOIE1)                       |
\******************************************************************************/
void Timer1_enableOverflowInterrupt()  { TIMSK1 |=  (1<<TOIE1); }
void Timer1_disableOverflowInterrupt() { TIMSK1 &= ~(1<<TOIE1); }

  //////////////////////////////////////////////////////////////////////////////
 ////////////////////////////// Timer 2 Functions /////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/****************************** SET TIMER 2 MODE ******************************\
| This function still needs some more work because i dont understand compleetly|
| what each mode does                                                          |
| Waveform Generation Mode Bit Description                                     |
| Timer/Counter TOP Update of TOV Flag                                         |
| Mode of OCRx at Set on(1)(2)                                                 |
| Operation                                                                    |
| Mode WGM2 WGM1 WGM0                                                          |
| 0    0    0    0    Normal 0xFF Immediate MAX                                |
| 1    0    0    1    PWM, Phase 0xFF TOP BOTTOM                               |
|        Correct                                                               |
| 2    0    1    0    CTC OCRA Immediate MAX                                   |
| 3    0    1    1    Fast PWM 0xFF BOTTOM MAX                                 |
| 4    1    0    0    Reserved – – –                                           |
| 5    1    0    1    PWM, Phase OCRA TOP BOTTOM                               |
|        Correct                                                               |
| 6    1    1    0    Reserved – – –                                           |
| 7    1    1    1    Fast PWM OCRA BOTTOM TOP                                 |
\******************************************************************************/
#define TIMER2_NORMAL 0
void Timer2_setMode (int mode) {
  if (mode == 0) { // Normal Top=0xFF update of OCRz at
    TCCR2A &= ~((1<<WGM21) | (1<<WGM20));
    TCCR2B &= ~(1<<WGM22);
  }
}

/**************************** SET TIMER 2 PRESCALER ***************************\
| The timer 2 prescaler determines when the timer is incremented. If the       |
| prescaler is 1 then the timer is incremented each time the clock ticks, if   |
| the prescaler is 8 then the timer is incremented every 8 cycles. You use     |
| this is you are trying to get small accurate numbers or large less acurate   |
| numbers from a timer                                                         |
\******************************************************************************/
void Timer2_setPrescaler(int prescaler) {
  TCCR2B &= B11111000; 
  if (prescaler == 0)         TCCR2B |= (0<<CS22) | (0<<CS21) | (0<<CS20);
  else if (prescaler == 1)    TCCR2B |= (0<<CS22) | (0<<CS21) | (1<<CS20);
  else if (prescaler == 8)    TCCR2B |= (0<<CS22) | (1<<CS21) | (0<<CS20);
  else if (prescaler == 32)   TCCR2B |= (0<<CS22) | (1<<CS21) | (1<<CS20);
  else if (prescaler == 64)   TCCR2B |= (1<<CS22) | (0<<CS21) | (0<<CS20);
  else if (prescaler == 128)  TCCR2B |= (1<<CS22) | (0<<CS21) | (1<<CS20);
  else if (prescaler == 256)  TCCR2B |= (1<<CS22) | (1<<CS21) | (0<<CS20);
  else if (prescaler == 1024) TCCR2B |= (1<<CS22) | (1<<CS21) | (1<<CS20);
}

/**************************** TIMER 2 DIRECT ACCESS ***************************\
| Set or get the current value for timer2                                      |
\******************************************************************************/
void Timer2_setValue(byte value) {TCNT2 = value;}
byte Timer2_getValue() {return TCNT2; }

/************************ SET TIMER 2 OUTPUT COMPARE A ************************\
| The Output Compare Register A contains an 8-bit value that is continuously   |
| compared with the counter value (TCNT2). A match can be used to generate an  |
| Output Compare interrupt, or to generate a waveform output on the OC2A pin.  |
\******************************************************************************/
void Timer2_setOutputCompareA(byte value) { OCR2A = value; }

/************************ SET TIMER 2 OUTPUT COMPARE B ************************\
| The Output Compare Register B contains an 8-bit value that is continuously   |
| compared with the counter value (TCNT2). A match can be used to generate an  |
| Output Compare interrupt, or to generate a waveform output on the OC2B pin.  |
\******************************************************************************/
void Timer2_setOutputCompareB(byte value) { OCR2B = value; }



  //////////////////////////////////////////////////////////////////////////////
 ////////////////////////// ENABLE TIMER 2 INTERRUPTS /////////////////////////
//////////////////////////////////////////////////////////////////////////////

/***************** ENABLE/DISABLE TIMER 2 COMPARE A INTERRUPT *****************\
| These two functions will enable or disable the timer 2 compare A interrupt.  |
| Overflow Compare Interrupt Enable 2 A  is register (OCIE2A)                  |
\******************************************************************************/
void Timer2_enableCompareAInterrupt()  { TIMSK2 |=  (1<<OCIE2A); }
void Timer2_disableCompareAInterrupt() { TIMSK2 &= ~(1<<OCIE2A);}

/***************** ENABLE/DISABLE TIMER 2 COMPARE B INTERRUPT *****************\
| These two functions will enable or disable the timer 2 compare B interrupt.  |
| Overflow Compare Interrupt Enable 2 B is register (OCIE2B)                   |
\******************************************************************************/
void Timer2_enableCompareBInterrupt()  { TIMSK2 |=  (1<<OCIE2B); }
void Timer2_disableCompareBInterrupt() { TIMSK2 &= !(1<<OCIE2B); }

/****************** ENABLE/DISABLE TIMER 2 OVERFLOW INTERRUPT *****************\
| These two functions will enable or disable the timer 2 overflow interrupt    |
| Timer Overflow Interrupt Enable 2  is register (TOIE2)                       |
\******************************************************************************/
void Timer2_enableOverflowInterrupt()  { TIMSK2 |=  (1<<TOIE2); }
void Timer2_disableOverflowInterrupt() { TIMSK2 &= ~(1<<TOIE2); }

// interrupt functions
#define TIMER2_OVERFLOW_INTERRUPT TIMER2_OVF_vect
/*
#define RESET_INTERRUPT RESET_vect //External Pin, Power-on Reset, Brown-out Reset and Watchdog System Reset
#define EXTERNAL_INTERRUPT_0 INT0_vect // External interrupt request 0
#define EXTERNAL_INTERRUPT_1 INT1_vect // External interrupt request 1
#define PCINT0_vect // Pin change interrupt request 0
#define PCINT1_vect // Pin change interrupt request 1
#define PCINT2_vect // Pin change interrupt request 2
#define WDT_vect // Watchdog time-out interrupt
#define TIMER2_COMPA_vect // Timer/Counter2 Compare Match A
#define TIMER2_COMPB_vect // Timer/Counter2 Compare Match B
#define TIMER2_OVF_vect // Timer2 Overflow

TIMER1_CAPT_vect // Timer/Counter1 Capture Event
TIMER1_COMPA_vect // Timer/Counter1 Compare Match A
TIMER1_COMPB_vect // Timer/Counter1 Compare Match B 
TIMER1_OVF_vect // Timer/Counter1 Overflow

TIMER0_COMPA_vect // Timer/Counter0 Compare Match A
TIMER0_COMPB_vect // Timer/Counter0 Compare Match B
TIMER0_OVF_vect // Timer/Counter0 Overflow

// these next ones i am not sure about but this is my best analysis
SPI_STC_vect // SPI Serial Transfer Conplete
USART_RX_vect // USART Rx Complete
USART_UDRE_vect // USART, Data regester empty
USART_TX_vect // USART, Tx Complete
ADC_vect // ADC Conversion Complete
EE_READY_vect // EEPROM Ready
ANALOG_COMP_vect // Analog Comparator (i am not sure what this does)
TWI_vect // 2 wire Serial Interface (again not sure)
SPM_READY_vect // Store Program Memory Ready (pretty sure used for bootloaders like arduino)
*/

//TODO ASSR register (asynchronous status register)
//TODO GTCCR register (General timer/counter control register)
#endif
