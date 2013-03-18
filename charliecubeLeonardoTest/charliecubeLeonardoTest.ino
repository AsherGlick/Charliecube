
int pins[] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, A0, A1, A2, A3};

void setup() {
  for (int i = 0; i < 26; i++) {
    pinMode(i, INPUT);
  }
  Serial.begin(9600);
}

void loop() {
   for (int i = 0; i < 16; i++) {
     for (int j = 0; j < 16; j++) {
       if (i!=j && !(( i==0 || i==1 || i==2 || i==3) && ( j==0 || j==1 || j==2 || j==3)) ) {
         pinMode(pins[i],OUTPUT);
         pinMode(pins[j],OUTPUT);
         
         digitalWrite(pins[i], HIGH);
         digitalWrite(pins[j], LOW);
         
         /*
         Serial.println(A0);
         Serial.println(A1);
         Serial.println(A2);
         Serial.println(A3);
         Serial.print(pins[i]);
         Serial.print(":");
         Serial.print(pins[j]);
         Serial.println("");
         
         while(true) {
           if (Serial.available() > 0) {
             Serial.read();
             break;
           }
         }
         //*/ delay(100);
         
         
         pinMode(pins[i],INPUT);
         pinMode(pins[j],INPUT);
       }
     }
   }
}
