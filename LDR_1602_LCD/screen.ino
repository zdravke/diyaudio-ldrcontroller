


/////////////////////////
/******* SCREEN  *******/
byte sinMap(unsigned long x, int xmin, int xmax, int offset) {
	float pw = (sin(map(x, xmin, xmax, 4712, 6283) / 1000.0) + 1) * (LCDBRI_MAX - offset) + offset;
	return byte(pw);
}

void startLCDFadeIn() {
	if (LCDBacklightMode == LCDSTATE_MIN || LCDBacklightMode == LCDSTATE_FADEOUT) {
		LCDBacklightMode = LCDSTATE_FADEIN;
		mil_onFadeIn = millis();
		LCDinitialPW = LCDcurrentPW;
	}
}

void startLCDFadeOut() {
	if (LCDBacklightMode == LCDSTATE_MAX || LCDBacklightMode == LCDSTATE_FADEIN) {
		LCDBacklightMode = LCDSTATE_FADEOUT;
		mil_onFadeOut = millis();
		LCDinitialPW = LCDcurrentPW;
	}
}

void setLCDMinLight() {
	LCDBacklightMode = LCDSTATE_MIN;
	analogWrite(PIN_LCDBRI, LCDBRI_MIN);
	LCDcurrentPW = LCDBRI_MIN;
}

void setLCDMaxLight() {
	LCDBacklightMode = LCDSTATE_MAX;
	analogWrite(PIN_LCDBRI, LCDBRI_MAX);
	LCDcurrentPW = LCDBRI_MAX;
}

// prints a text on the LCD, padding with " " up to size
void lcd_print(char* text, byte size) {
	bool eot = false;
	for (byte i = 0; i < size; i++) {
		if (text[i] == 0)
			eot = true;
		if (eot)
			lcd.write(32);
		else
			lcd.write(text[i]);
	}
}


// prints activity indicator
void printTick() {
	tick++;
	if (tick % 4 == 0) {
		lcd.setCursor(((LCDCOLUMNS - 3 - sizeof(msgCalib)) / 2) + sizeof(msgCalib), 0);
		lcd.print("   ");
	}
	else
	{
		lcd.setCursor(((LCDCOLUMNS - 3 - sizeof(msgCalib)) / 2) + sizeof(msgCalib) - 1 + tick % 4, 0);
		lcd.print(".");
	}
}


// prints progress bar
void printBar(byte p){
	if (p == 0) return;
	if (p > 100) p = 100;
	lcd.setCursor(int(((LCDCOLUMNS * 1.0) - 1.0)*p / 100.0), 1);
	lcd.write(255);
}




// 4x4 charset
byte cc0[8] = {    // Custom Character 0
	B00000,
	B00000,
	B00000,
	B00111,
	B01111,
	B11111,
	B11111,
	B11111
};

byte cc1[8] = {    // Custom Character 1
	B11100,
	B11110,
	B11111,
	B11111,
	B11111,
	B11111,
	B11111,
	B11111
};

byte cc2[8] = {    // Custom Character 2
	B11111,
	B11111,
	B11111,
	B11111,
	B11111,
	B00000,
	B00000,
	B00000
};

byte cc3[8] = {    // Custom Character 3
	B00000,
	B00000,
	B00000,
	B11111,
	B11111,
	B11111,
	B11111,
	B11111
};

byte cc4[8] = {    // Custom Character 4
	B11111,
	B11111,
	B11111,
	B11111,
	B11111,
	B11111,
	B01111,
	B00111
};

byte cc5[8] = {    // Custom Character 5
	B00111,
	B01111,
	B11111,
	B11111,
	B11111,
	B11111,
	B11111,
	B11111
};

byte cc6[8] = {    // Custom Character 6
	B00000,
	B00000,
	B00000,
	B11100,
	B11110,
	B11111,
	B11111,
	B11111
};

byte cc7[8] = {    // Custom Character 7
	B11111,
	B11111,
	B11111,
	B11111,
	B11111,
	B11111,
	B11110,
	B11100
};



//             0            1            2            3            4            5            6            7            8            9
char bn1[] = { 5, 2, 2, 1,  0, 5, B, A,  5, 2, 2, 1,  2, 2, 2, 1,  5, A, A, B,  B, 2, 2, 2,  5, 2, 2, 2,  2, 2, 2, B,  5, 2, 2, 1,  5, 2, 2, 1 };
char bn2[] = { B, A, A, B,  A, A, B, A,  A, A, A, B,  A, 3, 3, B,  B, 3, 3, B,  B, 3, 3, 6,  B, 3, 3, 6,  A, A, 0, 7,  B, 3, 3, B,  4, 3, 3, B };
char bn3[] = { B, A, A, B,  A, A, B, A,  5, 2, 2, 2,  A, A, A, B,  A, A, A, B,  A, A, A, B,  B, A, A, B,  A, A, B, A,  B, A, A, B,  A, A, A, B };
char bn4[] = { 4, 3, 3, 7,  3, 3, B, 3,  B, 3, 3, 3,  4, 3, 3, 7,  A, A, A, B,  4, 3, 3, 7,  4, 3, 3, 7,  A, A, B, A,  4, 3, 3, 7,  4, 3, 3, 7 };



// 3x2 charset
byte LT[8] = 
{
 B00111,
 B01111,
 B11111,
 B11111,
 B11111,
 B11111,
 B11111,
 B11111
};
byte UB[8] =
{
 B11111,
 B11111,
 B11111,
 B00000,
 B00000,
 B00000,
 B00000,
 B00000
};
byte RT[8] =
{
 B11100,
 B11110,
 B11111,
 B11111,
 B11111,
 B11111,
 B11111,
 B11111
};
byte LL[8] =
{
 B11111,
 B11111,
 B11111,
 B11111,
 B11111,
 B11111,
 B01111,
 B00111
};
byte LB[8] =
{
 B00000,
 B00000,
 B00000,
 B00000,
 B00000,
 B11111,
 B11111,
 B11111
};
byte LR[8] =
{
 B11111,
 B11111,
 B11111,
 B11111,
 B11111,
 B11111,
 B11110,
 B11100
};
byte MB[8] =
{
 B11111,
 B11111,
 B11111,
 B00000,
 B00000,
 B00000,
 B11111,
 B11111
};
byte block[8] =
{
 B11111,
 B11111,
 B11111,
 B11111,
 B11111,
 B11111,
 B11111,
 B11111
};

byte blank[8] =
{
 B00000,
 B00000,
 B00000,
 B00000,
 B00000,
 B00000,
 B00000,
 B00000
};


// 32 = blank
//             0         1          2         3         4          5          6         7           8         9
char bn5[] = { 0, 1, 2,  1, 2, 32,  6, 6, 2,  6, 6, 2,  3, 4, 7,    3, 6, 6,  0, 6, 6,  1, 1, 2,    0, 6, 2,  0, 6, 2 };
char bn6[] = { 3, 4, 5,  4, 7, 4,   3, 4, 4,  4, 4, 5,  32, 32, 7,  4, 4, 5,  3, 4, 5,  32, 32, 7,  3, 4, 5,  32, 32, 7 };



// Functions for printing two 4x4 digits. Works from 00-99
void printTwoNumber(byte column, byte number) {
  if (LCDCOLUMNS == 20) {
	lcd.setCursor(column, 0); 
	lcd.write(bn1[(number / 10) * 4]);
	lcd.write(bn1[(number / 10) * 4 + 1]);
	lcd.write(bn1[(number / 10) * 4 + 2]);
	lcd.write(bn1[(number / 10) * 4 + 3]);
	lcd.write(A); // Blank
	lcd.write(bn1[(number % 10) * 4]);
	lcd.write(bn1[(number % 10) * 4 + 1]);
	lcd.write(bn1[(number % 10) * 4 + 2]);
	lcd.write(bn1[(number % 10) * 4 + 3]);

	lcd.setCursor(column, 1); 
	lcd.write(bn2[(number / 10) * 4]);
	lcd.write(bn2[(number / 10) * 4 + 1]);
	lcd.write(bn2[(number / 10) * 4 + 2]);
	lcd.write(bn2[(number / 10) * 4 + 3]);
	lcd.write(A); // Blank
	lcd.write(bn2[(number % 10) * 4]);
	lcd.write(bn2[(number % 10) * 4 + 1]);
	lcd.write(bn2[(number % 10) * 4 + 2]);
	lcd.write(bn2[(number % 10) * 4 + 3]);

	lcd.setCursor(column, 2); 
	lcd.write(bn3[(number / 10) * 4]);
	lcd.write(bn3[(number / 10) * 4 + 1]);
	lcd.write(bn3[(number / 10) * 4 + 2]);
	lcd.write(bn3[(number / 10) * 4 + 3]);
	lcd.write(A); // Blank
	lcd.write(bn3[(number % 10) * 4]);
	lcd.write(bn3[(number % 10) * 4 + 1]);
	lcd.write(bn3[(number % 10) * 4 + 2]);
	lcd.write(bn3[(number % 10) * 4 + 3]);

	lcd.setCursor(column, 3); 
	lcd.write(bn4[(number / 10) * 4]);
	lcd.write(bn4[(number / 10) * 4 + 1]);
	lcd.write(bn4[(number / 10) * 4 + 2]);
	lcd.write(bn4[(number / 10) * 4 + 3]);
	lcd.write(A); // Blank
	lcd.write(bn4[(number % 10) * 4]);
	lcd.write(bn4[(number % 10) * 4 + 1]);
	lcd.write(bn4[(number % 10) * 4 + 2]);
	lcd.write(bn4[(number % 10) * 4 + 3]);
    };
    
  if (LCDCOLUMNS == 16) {
  	lcd.setCursor(column, 0); 
	lcd.write(bn5[(number / 10) * 3]);
	lcd.write(bn5[(number / 10) * 3 + 1]);
	lcd.write(bn5[(number / 10) * 3 + 2]);
	lcd.write(A); // Blank
	lcd.write(bn5[(number % 10) * 3]);
	lcd.write(bn5[(number % 10) * 3 + 1]);
	lcd.write(bn5[(number % 10) * 3 + 2]);

	lcd.setCursor(column, 1); 
	lcd.write(bn6[(number / 10) * 3]);
	lcd.write(bn6[(number / 10) * 3 + 1]);
	lcd.write(bn6[(number / 10) * 3 + 2]);
	lcd.write(A); // Blank
	lcd.write(bn6[(number % 10) * 3]);
	lcd.write(bn6[(number % 10) * 3 + 1]);
	lcd.write(bn6[(number % 10) * 3 + 2]);
    };
}



void defineCustomChar() {
  if (LCDCOLUMNS == 16) {
     lcd.createChar(0,LT);
     lcd.createChar(1,UB);
     lcd.createChar(2,RT);
     lcd.createChar(3,LL);
     lcd.createChar(4,LB);
     lcd.createChar(5,LR);
     lcd.createChar(6,MB);
     lcd.createChar(7,block);  
    };
   
  if (LCDCOLUMNS == 20) {
    lcd.createChar(0, cc0);  
    lcd.createChar(1, cc1);  
    lcd.createChar(2, cc2);  
    lcd.createChar(3, cc3);  
    lcd.createChar(4, cc4);  
    lcd.createChar(5, cc5);  
    lcd.createChar(6, cc6);  
    lcd.createChar(7, cc7);  
    };
}



