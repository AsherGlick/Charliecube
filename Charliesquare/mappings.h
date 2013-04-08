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

// Color X Y Z
//      CXYZ 
#define b24 1,5
#define b44 1,6
#define b64 1,7
#define b84 1,8
#define r81 1,9
#define r61 1,10
#define r41 1,11
#define r21 1,12
#define g83 1,13
#define g43 1,14
#define g23 1,15
#define g63 1,16
#define b28 2,5
#define b48 2,6
#define b68 2,7
#define b88 2,8
#define r65 2,9
#define r85 2,10
#define r25 2,11
#define r45 2,12
#define g47 2,13
#define g87 2,14
#define g67 2,15
#define g27 2,16
#define b14 3,5
#define b34 3,6
#define b54 3,7
#define b74 3,8
#define r31 3,9
#define r11 3,10
#define r71 3,11
#define r51 3,12
#define g13 3,13
#define g53 3,14
#define g73 3,15
#define g33 3,16
#define b18 4,5
#define b38 4,6
#define b58 4,7
#define b78 4,8
#define r15 4,9
#define r35 4,10
#define r55 4,11
#define r75 4,12
#define g57 4,13
#define g17 4,14
#define g37 4,15
#define g77 4,16
#define b22 5,1
#define b26 5,2
#define b12 5,3
#define b26 5,4
#define g15 5,9
#define g11 5,10
#define g25 5,11
#define g21 5,12
#define r13 5,13
#define r17 5,14
#define r23 5,15
#define r27 5,16
#define b42 6,1
#define b46 6,2
#define b32 6,3
#define b36 6,4
#define g31 6,9
#define g35 6,10
#define g41 6,11
#define g45 6,12
#define r47 6,13
#define r43 6,14
#define r37 6,15
#define r33 6,16
#define b62 7,1
#define b66 7,2
#define b52 7,3
#define b56 7,4
#define g65 7,9
#define g61 7,10
#define g55 7,11
#define g51 7,13
#define r57 7,13
#define r53 7,14
#define r67 7,15
#define r63 7,16
#define b82 8,1
#define b86 8,2
#define b72 8,3
#define b76 8,4
#define g81 8,9
#define g85 8,10
#define g71 8,11
#define g75 8,12
#define r83 8,13
#define r87 8,14
#define r73 8,15
#define r77 8,16
#define g82 9,1
#define g66 9,2
#define g32 9,3
#define g16 9,4
#define r18 9,5
#define r34 9,6
#define r68 9,7
#define r84 9,8
#define b83 9,13
#define b17 9,14
#define b67 9,15
#define b33 9,16
#define g62 10,1
#define g86 10,2
#define g12 10,3
#define g36 10,4
#define r14 10,5
#define r38 10,6
#define r64 10,7
#define r88 10,8
#define b13 10,13
#define b87 10,14
#define b37 10,15
#define b63 10,16
#define g42 11,1
#define g26 11,2
#define g72 11,3
#define g56 11,4
#define r28 11,5
#define r44 11,6
#define r58 11,7
#define r74 11,8
#define b57 11,13
#define b43 11,14
#define b73 11,15
#define b27 11,16
#define g22 12,1
#define g46 12,2
#define g52 12,3
#define g76 12,4
#define r24 12,5
#define r48 12,6
#define r54 12,7
#define r78 12,8
#define b47 12,13
#define b53 12,14
#define b23 12,15
#define b77 12,16
#define r82 13,1
#define r46 13,2
#define r12 13,3
#define r56 13,4
#define g14 13,5
#define g48 13,6
#define g58 13,7
#define g84 13,8
#define b81 13,9
#define b11 13,10
#define b55 13,11
#define b45 13,12
#define r42 14,1
#define r86 14,2
#define r52 14,3
#define r16 14,4
#define g18 14,5
#define g44 14,6
#define g54 14,7
#define g88 14,8
#define b15 14,9
#define b85 14,10
#define b41 14,11
#define b51 14,12
#define r22 15,1
#define r66 15,2
#define r72 15,3
#define r36 15,4
#define g24 15,5
#define g38 15,6
#define g68 15,7
#define g74 15,8
#define b65 15,9
#define b35 15,10
#define b71 15,11
#define b21 15,12
#define r62 16,1
#define r26 16,2
#define r32 16,3
#define r76 16,4
#define g28 16,5
#define g34 16,6
#define g64 16,7
#define g78 16,8
#define b31 16,9
#define b61 16,10
#define b25 16,11
#define b75 16,12
#endif // _MAPPINGS_H_
