
int pins[] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, A0, A1, A2, A3};

void setup() {
  Serial.begin(9600);
}

void loop() {
  for (int i = 0; i < 16; i++) {
    for (int j = 0; j < 16; j++) {
      if (i!=j && 
        !(( i==0 || i==1 || i==2 || i==3) && ( j==0 || j==1 || j==2 || j==3))&&
        !(( i==4 || i==5 || i==6 || i==7) && ( j==4 || j==5 || j==6 || j==7)) &&
        !(( i==8 || i==9 || i==10 || i==11) && ( j==8 || j==9 || j==10 || j==11))&&
        !(( i==12 || i==13 || i==14 || i==15) && ( j==12 || j==13 || j==14 || j==15))
        ) {
          
        turnOnLed2(i,j);
        
        /*
        Serial.print(i+1);
        Serial.print(":");
        Serial.print(j+1);
        Serial.println("");
        
        while(true) {
          if (Serial.available() > 0) {
            Serial.read();
            break;
          }
        }
        //*/ delay(50);
      }
    }
  }
}

void turnOnLed(int pin1, int pin2) {
  for (int i = 0; i < 16; i++) {
    pinMode(pins[i], INPUT);
  }
        
  pinMode(pins[pin1],OUTPUT);
  pinMode(pins[pin2],OUTPUT);
        
  digitalWrite(pins[pin1], HIGH);
  digitalWrite(pins[pin2], LOW);
}



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
    
byte pinsB[] = {0x00,WIRE_1_PORT_B,WIRE_2_PORT_B,WIRE_3_PORT_B,WIRE_4_PORT_B,WIRE_5_PORT_B,WIRE_6_PORT_B,WIRE_7_PORT_B,WIRE_8_PORT_B,WIRE_9_PORT_B,WIRE_10_PORT_B,WIRE_11_PORT_B,WIRE_12_PORT_B,WIRE_13_PORT_B,WIRE_14_PORT_B,WIRE_15_PORT_B,WIRE_16_PORT_B};
byte pinsC[] = {0x00,WIRE_1_PORT_C,WIRE_2_PORT_C,WIRE_3_PORT_C,WIRE_4_PORT_C,WIRE_5_PORT_C,WIRE_6_PORT_C,WIRE_7_PORT_C,WIRE_8_PORT_C,WIRE_9_PORT_C,WIRE_10_PORT_C,WIRE_11_PORT_C,WIRE_12_PORT_C,WIRE_13_PORT_C,WIRE_14_PORT_C,WIRE_15_PORT_C,WIRE_16_PORT_C};
byte pinsD[] = {0x00,WIRE_1_PORT_D,WIRE_2_PORT_D,WIRE_3_PORT_D,WIRE_4_PORT_D,WIRE_5_PORT_D,WIRE_6_PORT_D,WIRE_7_PORT_D,WIRE_8_PORT_D,WIRE_9_PORT_D,WIRE_10_PORT_D,WIRE_11_PORT_D,WIRE_12_PORT_D,WIRE_13_PORT_D,WIRE_14_PORT_D,WIRE_15_PORT_D,WIRE_16_PORT_D};
byte pinsE[] = {0x00,WIRE_1_PORT_E,WIRE_2_PORT_E,WIRE_3_PORT_E,WIRE_4_PORT_E,WIRE_5_PORT_E,WIRE_6_PORT_E,WIRE_7_PORT_E,WIRE_8_PORT_E,WIRE_9_PORT_E,WIRE_10_PORT_E,WIRE_11_PORT_E,WIRE_12_PORT_E,WIRE_13_PORT_E,WIRE_14_PORT_E,WIRE_15_PORT_E,WIRE_16_PORT_E};
byte pinsF[] = {0x00,WIRE_1_PORT_F,WIRE_2_PORT_F,WIRE_3_PORT_F,WIRE_4_PORT_F,WIRE_5_PORT_F,WIRE_6_PORT_F,WIRE_7_PORT_F,WIRE_8_PORT_F,WIRE_9_PORT_F,WIRE_10_PORT_F,WIRE_11_PORT_F,WIRE_12_PORT_F,WIRE_13_PORT_F,WIRE_14_PORT_F,WIRE_15_PORT_F,WIRE_16_PORT_F};    

void turnOnLed2(int pin1, int pin2) {
  pin1++;
  pin2++;
  byte portBClear = 0x00;
  byte portCClear = 0x00;
  byte portDClear = 0x00;
  byte portEClear = 0x00;
  byte portFClear = 0x00;
  
  /*for (int i = 1; i < 17; i++) {
    portBClear = portBClear | pinsB[i];
    portCClear = portCClear | pinsC[i];
    portDClear = portDClear | pinsD[i];
    portEClear = portEClear | pinsE[i];
    portFClear = portFClear | pinsF[i];
  }
  
  portBClear = ~portBClear;
  portCClear = ~portCClear;
  portDClear = ~portDClear;
  portEClear = ~portEClear;
  portFClear = ~portFClear;*/
  
  PORTB &= portBClear;
  PORTC &= portCClear;
  PORTD &= portDClear;
  PORTE &= portEClear;
  PORTF &= portFClear;
  
  DDRB &= portBClear;
  DDRC &= portCClear;
  DDRD &= portDClear;
  DDRE &= portEClear;
  DDRF &= portFClear;
  
  DDRB |= pinsB[pin1] | pinsB[pin2];
  DDRC |= pinsC[pin1] | pinsC[pin2];
  DDRD |= pinsD[pin1] | pinsD[pin2];
  DDRE |= pinsE[pin1] | pinsE[pin2];
  DDRF |= pinsF[pin1] | pinsF[pin2];
  
  PORTB |= pinsB[pin1];
  PORTC |= pinsC[pin1];
  PORTD |= pinsD[pin1];
  PORTE |= pinsE[pin1];
  PORTF |= pinsF[pin1];
}
