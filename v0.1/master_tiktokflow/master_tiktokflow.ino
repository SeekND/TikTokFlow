// user can change

int fulltime = 15; // in seconds for the whole sequence to last
int flashtime = 3; // in seconds for the last seconds of the sequence where you want it to flash
int nrofsequences = 5; // you need to have the sequences coded at the end of this script if you want to add more


// leave the rest alone unless you know what you are doing
int prewhosit = 0;
int timetoflash = ( fulltime - flashtime ) * 1000;

void setup() {
  Serial.begin(9600);
  delay(2000);
}

void loop() {


  int whosit = random(1, nrofsequences);

  if ( whosit == prewhosit ) {
    if ( whosit == nrofsequences )
    {
      whosit -= 1;
    }
    else if ( whosit == 1 )
    {
      whosit += 1;
    }
    else
    {
      int randi = random(0, 1);
      if (randi == 0)
        whosit += 1;
      else
        whosit -= 1;
    }
  }
  prewhosit = whosit;

  //Serial.println(whosit);

  
  if (whosit == 1) {
    leftlane(0); // 0 means no flash
  }
  else if (whosit == 2) {
    middlelane(0);
  }
  else if (whosit == 3) {
    rightlane(0);
  }
  else if (whosit == 4) {
    gotoright(0);
  }
  else if (whosit == 5) {
    gotoleft(0);
  }

  delay(timetoflash * 1000);

  if (whosit == 1) {
    leftlane(1);  // 1 means flash
  }
  else if (whosit == 2) {
    middlelane(1);
  }
  else if (whosit == 3) {
    rightlane(1);
  }
  else if (whosit == 4) {
    gotoright(1);
  }
  else if (whosit == 5) {
    gotoleft(1);
  }

  delay(flashtime * 1000);
}


/////////////////////////// below are the sequences you can create. explanation on the serial print you need to send on the comments
/////////////////////////// remember to increase the maximum nr of sequences at the start of the script if you add more below


void leftlane(int flash) {

  if (flash == 0 ) {
    Serial.print("T1_1|");   // turns on led 1 (_1) on TickTok 1 array (T1) 
    delay(100);
    Serial.print("T2_1|");   // turns on led 1 (_1) on TickTok 2 array (T2)
    delay(100);
    Serial.print("T3_1|");   // turns on led 1 (_1) on TickTok 3 array (T3)
    delay(100);
  }
  else
  {

    Serial.print("T1_1F|");   // flashes (F) led 1 (_1) on TickTok 1 array (T1) 
    delay(100);
    Serial.print("T2_1F|");   // flashes (F) led 1 (_1) on TickTok 1 array (T1) 
    delay(100);
    Serial.print("T3_1F|");   // flashes (F) led 1 (_1) on TickTok 1 array (T1) 
    delay(100);
  }
}

void middlelane(int flash) {

  if (flash == 0 ) {
    Serial.print("T1_2|");
    delay(100);
    Serial.print("T2_2|");
    delay(100);
    Serial.print("T3_2|");
    delay(100);
  }
  else
  {
    Serial.print("T1_2F|");
    delay(100);
    Serial.print("T2_2F|");
    delay(100);
    Serial.print("T3_2F|");
    delay(100);
  }
}


void rightlane(int flash) {

  if (flash == 0 ) {
    Serial.print("T1_3|");
    delay(100);
    Serial.print("T2_3|");
    delay(100);
    Serial.print("T3_3|");
    delay(100);
  }
  else
  {
    Serial.print("T1_3F|");
    delay(100);
    Serial.print("T2_3F|");
    delay(100);
    Serial.print("T3_3F|");
    delay(100);

  }
}

void gotoright(int flash) {

  if (flash == 0 ) {
    Serial.print("T1_1|");
    delay(100);
    Serial.print("T2_2|");
    delay(100);
    Serial.print("T3_3|");
    delay(100);
  }
  else
  {
    Serial.print("T1_1F|");
    delay(100);
    Serial.print("T2_2F|");
    delay(100);
    Serial.print("T3_3F|");
    delay(100);

  }
}

void gotoleft(int flash) {
  if (flash == 0 ) {
    Serial.print("T1_3|");
    delay(100);
    Serial.print("T2_2|");
    delay(100);
    Serial.print("T3_1|");
    delay(100);
  }
  else
  {
    Serial.print("T1_3F|");
    delay(100);
    Serial.print("T2_2F|");
    delay(100);
    Serial.print("T3_1F|");
    delay(100);

  }
}
