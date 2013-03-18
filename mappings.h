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
/*
__AVR_ATtiny24__
__AVR_ATtiny44__
__AVR_ATtiny84__
__AVR_ATtiny25__
__AVR_ATtiny45__
__AVR_ATtiny85__

__AVR_ATmega1280__
__AVR_ATmega2560__
__AVR_ATmega1284P__
__AVR_ATmega644P__

__AVR_ATmega328P__
__AVR_ATmega32U4__
*/
#ifndef _MAPPINGS_H_
  #define _MAPPINGS_H_

  
  #ifdef __AVR_ATmega328P__
    /*********************** ATMEGA328 PIN TO PORT MAPPINGS ***********************\
    | These are the pin to port mappings for an ATMEGA328                          |
    \******************************************************************************/
    #define WIRE_1_PORT_B 0x00
    #define WIRE_1_PORT_C 0x00
    #define WIRE_1_PORT_D 0x04
    
    #define WIRE_2_PORT_B 0x00
    #define WIRE_2_PORT_C 0x00
    #define WIRE_2_PORT_D 0x08
    
    #define WIRE_3_PORT_B 0x00
    #define WIRE_3_PORT_C 0x00
    #define WIRE_3_PORT_D 0x10
    
    #define WIRE_4_PORT_B 0x00
    #define WIRE_4_PORT_C 0x00
    #define WIRE_4_PORT_D 0x20
    
    #define WIRE_5_PORT_B 0x00
    #define WIRE_5_PORT_C 0x00
    #define WIRE_5_PORT_D 0x40
    
    #define WIRE_6_PORT_B 0x00
    #define WIRE_6_PORT_C 0x00
    #define WIRE_6_PORT_D 0x80
    
    #define WIRE_7_PORT_B 0x01
    #define WIRE_7_PORT_C 0x00
    #define WIRE_7_PORT_D 0x00
    
    #define WIRE_8_PORT_B 0x02
    #define WIRE_8_PORT_C 0x00
    #define WIRE_8_PORT_D 0x00
    
    #define WIRE_9_PORT_B 0x04
    #define WIRE_9_PORT_C 0x00
    #define WIRE_9_PORT_D 0x00
    
    #define WIRE_10_PORT_B 0x08
    #define WIRE_10_PORT_C 0x00
    #define WIRE_10_PORT_D 0x00
    
    #define WIRE_11_PORT_B 0x10
    #define WIRE_11_PORT_C 0x00
    #define WIRE_11_PORT_D 0x00
    
    #define WIRE_12_PORT_B 0x20
    #define WIRE_12_PORT_C 0x00
    #define WIRE_12_PORT_D 0x00
    
    #define WIRE_13_PORT_B 0x00
    #define WIRE_13_PORT_C 0x01
    #define WIRE_13_PORT_D 0x00
    
    #define WIRE_14_PORT_B 0x00
    #define WIRE_14_PORT_C 0x02
    #define WIRE_14_PORT_D 0x00
    
    #define WIRE_15_PORT_B 0x00
    #define WIRE_15_PORT_C 0x04
    #define WIRE_15_PORT_D 0x00
    
    #define WIRE_16_PORT_B 0x00
    #define WIRE_16_PORT_C 0x08
    #define WIRE_16_PORT_D 0x00
  #endif // __AVR_ATmega328P__
    
  // ARDUINO LEONARDO (ATMEGA32U4)
  #ifdef __AVR_ATmega32U4__
    #define WIRE_1_PORT_B 0x00
    #define WIRE_1_PORT_C 0x00
    #define WIRE_1_PORT_D 0x02
    #define WIRE_1_PORT_E 0x00
    #define WIRE_1_PORT_F 0x00
    
    #define WIRE_2_PORT_B 0x00
    #define WIRE_2_PORT_C 0x00
    #define WIRE_2_PORT_D 0x01
    #define WIRE_2_PORT_E 0x00
    #define WIRE_2_PORT_F 0x00
    
    #define WIRE_3_PORT_B 0x00
    #define WIRE_3_PORT_C 0x00
    #define WIRE_3_PORT_D 0x10
    #define WIRE_3_PORT_E 0x00
    #define WIRE_3_PORT_F 0x00
    
    #define WIRE_4_PORT_B 0x00
    #define WIRE_4_PORT_C 0x40
    #define WIRE_4_PORT_D 0x00
    #define WIRE_4_PORT_E 0x00
    #define WIRE_4_PORT_F 0x00
    
    #define WIRE_5_PORT_B 0x00
    #define WIRE_5_PORT_C 0x00
    #define WIRE_5_PORT_D 0x80
    #define WIRE_5_PORT_E 0x00
    #define WIRE_5_PORT_F 0x00
    
    #define WIRE_6_PORT_B 0x00
    #define WIRE_6_PORT_C 0x00
    #define WIRE_6_PORT_D 0x00
    #define WIRE_6_PORT_E 0x40
    #define WIRE_6_PORT_F 0x00
    
    #define WIRE_7_PORT_B 0x10
    #define WIRE_7_PORT_C 0x00
    #define WIRE_7_PORT_D 0x00
    #define WIRE_7_PORT_E 0x00
    #define WIRE_7_PORT_F 0x00
    
    #define WIRE_8_PORT_B 0x20
    #define WIRE_8_PORT_C 0x00
    #define WIRE_8_PORT_D 0x00
    #define WIRE_8_PORT_E 0x00
    #define WIRE_8_PORT_F 0x00
    
    #define WIRE_9_PORT_B 0x40
    #define WIRE_9_PORT_C 0x00
    #define WIRE_9_PORT_D 0x00
    #define WIRE_9_PORT_E 0x00
    #define WIRE_9_PORT_F 0x00
    
    #define WIRE_10_PORT_B 0x80
    #define WIRE_10_PORT_C 0x00
    #define WIRE_10_PORT_D 0x00
    #define WIRE_10_PORT_E 0x00
    #define WIRE_10_PORT_F 0x00
    
    #define WIRE_11_PORT_B 0x00
    #define WIRE_11_PORT_C 0x00
    #define WIRE_11_PORT_D 0x40
    #define WIRE_11_PORT_E 0x00
    #define WIRE_11_PORT_F 0x00
    
    #define WIRE_12_PORT_B 0x00
    #define WIRE_12_PORT_C 0x80
    #define WIRE_12_PORT_D 0x00
    #define WIRE_12_PORT_E 0x00
    #define WIRE_12_PORT_F 0x00
    
    #define WIRE_13_PORT_B 0x00
    #define WIRE_13_PORT_C 0x00
    #define WIRE_13_PORT_D 0x00
    #define WIRE_13_PORT_E 0x00
    #define WIRE_13_PORT_F 0x80
    
    #define WIRE_14_PORT_B 0x00
    #define WIRE_14_PORT_C 0x00
    #define WIRE_14_PORT_D 0x00
    #define WIRE_14_PORT_E 0x00
    #define WIRE_14_PORT_F 0x40
    
    #define WIRE_15_PORT_B 0x00
    #define WIRE_15_PORT_C 0x00
    #define WIRE_15_PORT_D 0x00
    #define WIRE_15_PORT_E 0x00
    #define WIRE_15_PORT_F 0x20
    
    #define WIRE_16_PORT_B 0x00
    #define WIRE_16_PORT_C 0x00
    #define WIRE_16_PORT_D 0x00
    #define WIRE_16_PORT_E 0x00
    #define WIRE_16_PORT_F 0x10

  #endif // END __AVR_ATmega32U4__
#endif // _MAPPINGS_H_
