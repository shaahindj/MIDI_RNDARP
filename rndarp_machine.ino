
/**
  DEFINISCO LE COSTANTI PER LE LETTURE DEGLI INPUT
*/
const int PIN_SEED = -1;     
const int PIN_TEMPO_INC = -1;     
const int PIN_TEMPO_DEC = -1;

//FUNZIONI DI MENU
int sensorMin = 0;
int sensorMax = 1024;

int battute = 8;
int tempo = 120;
int vels[] = {127,127,127,127,127,127,127,127};
int tones[] = {60,60,60,60,60,60,60,60};
int currentNotes[8];
int midi_ch=1;
int *ptones;
boolean play = false;

int currentMenu = 0;

String currentMode = "TEMPO";

String scale = "C";
int maggiore[] = {2,2,1,2,2,2,1};
int dorico[] = {2,1,2,2,2,1,2};
int frigio[] = {1,2,2,2,1,2,2};
int lidio[] = {2,2,2,1,2,2,1};
int misolidio[] = {2,2,1,2,2,1,2};
int minore[] = {2,1,2,2,1,2,2};
int locrio[] = {1,2,2,1,2,2,2};
int pentatonic[] = {1,2,3,2,2,3,1};


int ret[8];

float bps = tempo/60;
float tickDuration = 1/bps;
int del_tick = tickDuration*1000;
int arp_tick = del_tick / (battute/4);


void scala(int initNote,int modo[], int range)
{
  int modoRange[]={};
  //octave 3
  //initNote = C
  //60
  //modo maggiore [2,2,1,2,2,2,1]
  //int modoRange[4];
  //modoRange = modo;
  //for (r=1;r<sizeOf(range);r++){
  //  for (n=0;n<sizeOf(modo);n++){
  //    modoRange[r*7+n] = modo[n];
  //  }


  ret[0] = initNote;
  
  int i;
  for (i = 0; i < 8; i=i+1){
     ret[i+1] = initNote+modoRange[i];
  }
  
  
}

/*
//Restituisce una rray di battute Randomizza gli array nelle battute (8)
void randomize(int generator[],int  *pdata )
{
  int ret[8];
  int i;
  for(i=0;i<battute;i++){
    int rnd = random(sizeOf(generator));
    ret[i] = generator[rnd];
  }
}
*/

void setup() {
  //currentMode = pentatonic
  //range = 1
  //scala = scala(60,currentMode,range);
  play=true;
  // set up the LCD's number of columns and rows:
  //lcd.begin(16, 2);
  // Print a message to the LCD.
  //lcd.print("RNDARP MACHINE");
  Serial.begin(9600);
}

///play the rnd arp
void play(){
  for (int i=0;i<8;i=i+1){
    String space = " ";
    Serial.println(tones[0] + space + vels[i] + space + ch);
  }
}

String menuLabel = "";
int lastMenu = 0;


int menuReading;
int changeReading;

void inputReading(){
    menuReading = analogRead(A0);
    changeReading = analogRead(A1);
    seed = digitalRead(PIN_SEED);
}

void seed(){
  menuLabel = "SEEDS";
  for(int i=0;i<battute;i++){
    tones[i] = random(255);
  }
}

void loop() {
  
  // map the sensor range to a range of four options:
  int range = map(menuReading, sensorMin, sensorMax, 0, 6);
  currentMenu=range;
  switch (currentMenu) {
    case 0:    // TEMPO
      menuLabel = "TEMPO";
      //int tempoReading = changeReading;    
      tempo = map(changeReading, sensorMin, sensorMax, 70, 230); 
      //Serial.print(tempo);
      bps = tempo/60;
      tickDuration = 1/bps;
      del_tick = tickDuration*1000;
      //se 8 del_tick = 4 battute; 8/4=2
      arp_tick = del_tick / (battute/4);
      break;
    case 1:    // VELOCITY
      menuLabel = "VELOCITY";
      break;
    case 2:    // TONE
      menuLabel = "TONE";
      break;
    case 3:    // SCALE
      menuLabel = "SCALE";
      break;  
    case 4: //RANGE
      menuLabel = "RANGE";
      break;
    case 5: //OCTAVE
      menuLabel = "OCTAVE";
      break;
  }
  
  if (lastMenu != currentMenu){
    Serial.println(menuLabel);
    lastMenu = currentMenu;
  }
  
  Serial.println(tempo);
  //Serial.println(del_tick);
  if (play==true){
  for (int b=0;b<battute;b++){
    inputReading();
    Serial.print(String(tones[b],HEX)+"|" );
    delay(arp_tick);
  }
  Serial.println();
  }
  
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  //lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  //lcd.print(millis() / 1000);
}
