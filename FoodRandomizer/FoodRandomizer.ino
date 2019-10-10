//------------------------------------------------------------------------
//                           Global Stuff
//------------------------------------------------------------------------
#define NELEMS(x)  (sizeof(x) / sizeof((x)[0])) //Determines number of elements
char des=0;//if decision is made, sets to 1,
char* option; //final destination
char* drvr; //final driver
struct food
{
  unsigned d : 1;  // delivery
  unsigned r : 1;  // restaraunt
  unsigned f : 1;  // fast food
  unsigned b : 1;  // breakfast
};


//------------------------------------------------------------------------
//                           List of Options
//------------------------------------------------------------------------
char brkfast[5][20]={"IHOP","Bob Evans","Sheetz","McDonalds","Shoney's"};
char bNum=NELEMS(brkfast);
//priority based?

char fast[11][20]={"McDonalds","Five Guys","Sheetz",
"Wendy's","Arby's","Panda Express","Subway","Popeyes",
"Long John Silvers","Taco Bell","Chipotle"}; //repeats Sheetz and McDonalds
char fNum=NELEMS(fast);

char rest[11][20]={"Applebee's","Chili's","Primanti's",
"Buffalo Wild Wings","Outback","Ogawa","No 1 Super Buffet",
"FRESH MINT","Ruby Tuesday","Black Bear","Fusion"};
char rNum=NELEMS(rest);

char deliv[7][20]={"China King","Pizza Hut","Papa Johns",
"Chaang", "D.P. Doughs","Casa D'Amici","Clutch Wing Shop"};
char dNum=NELEMS(deliv);

//------------------------------------------------------------------------
//                           Driver Options
//------------------------------------------------------------------------
char driver[3][10]={"Larry","Syd","Toast"};
char driv=NELEMS(driver);



//------------------------------------------------------------------------
//                           Setup
//------------------------------------------------------------------------
void setup() {
  pinMode(7,OUTPUT); //keeps Arduino on
  digitalWrite(7,HIGH);
  
  randomSeed(analogRead(0));//INCREASE THE RANDOMNESS
  
  pinMode(3, INPUT);//breakfast
  pinMode(4, INPUT);//fastfood
  pinMode(5, INPUT);//restaraunt
  pinMode(6, INPUT);//delivery
  pinMode(7,OUTPUT);
  digitalWrite(7,HIGH);
  pinMode(13,OUTPUT);//LED for error
}

//------------------------------------------------------------------------
//                           Loop
//------------------------------------------------------------------------
void loop() {
  int rando=-1; //random number to generate option
  struct food bitters;
  
  
//------------------------------------------------------------------------
//                           Decision Process
//------------------------------------------------------------------------
  
  if(!des){
    char maxPlace=-1; //number of places to choose from
    bitters=food{0,0,0,0};
    if(digitalRead(3)) bitters.b=1;
    if(digitalRead(4)) bitters.f=1;
    if(digitalRead(5)) bitters.r=1;
    if(digitalRead(6)) bitters.d=1;

    //Testing
      bitters.b=1;
      bitters.f=1;
      bitters.d=1;
      bitters.r=1;
    //Testing
    
    maxPlace=(bitters.b)+2*(bitters.f)+4*(bitters.r)+8*(bitters.d);
    if(maxPlace>0){
        rando=7;
        des=1;
    }
    else{ //parameters fail, reset and try again
        for(char i=0;i<10;i++){
          digitalWrite(13,HIGH);
          delay(1000);
          digitalWrite(13,LOW);
          delay(1000);
          exit(1);
        }
    }
  }
//------------------------------------------------------------------------
//                           Output Process
//------------------------------------------------------------------------
  if(des==1){
    option = optionList(rando,bitters);
    if(!((bitters.d)&&(rando>((bNum*bitters.b)+(fNum*bitters.f)+(rNum*bitters.r)))))
      drvr=*(driver+random(0,driv));
    outputVisual(option);
    outputAudio(option);
  }
  shutdownTimer();
}

//------------------------------------------------------------------------
//                           Randomizer
//------------------------------------------------------------------------
int randoThing(struct food &bitten){
  char var=(bNum*bitten.b)+(fNum*bitten.f)+(rNum*bitten.r)+(dNum*bitten.d); 
  if(bitten.b && bitten.f) var-2;
  return random(1,var);
}

//------------------------------------------------------------------------
//                           Picks Place
//------------------------------------------------------------------------
char* optionList(int rando, struct food &bitr)
{
  char rav=0;
  char var=(bNum*bitr.b)+(fNum*bitr.f)+(rNum*bitr.r)+(dNum*bitr.d); 
  char *place;
  if(bitr.b && bitr.f)
  {
    if(rando>7) rav+=2; //hardcoded McD skip FIX
    else if(rando>5) rav++; //hardcoded Sheetz skip FIX
  }
  
  if((bitr.d)&&(rando>(var-dNum*bitr.d)))
  {
    rav+=rando-((bNum*bitr.b)+(fNum*bitr.f)+(rNum*bitr.r))-1;  
    place=*(deliv+rav);
  }
  else if((bitr.r)&&(rando>(var-((rNum*bitr.r)+(dNum*bitr.d)))))
  {
    rav+=rando-((bNum*bitr.b)+(fNum*bitr.f))-1;
    place=*(rest+rav);
  }
  else if((bitr.f)&&(rando>(var-((fNum*bitr.f)+(rNum*bitr.r)+(dNum*bitr.d)))))
  {
    rav+=rando-(bNum*bitr.b)-1;
    place=*(fast+rav);
  }
  else 
  {
    rav+=rando-1;
    place=*(brkfast+rav);
  }
  
  return place;
}
//------------------------------------------------------------------------
//                           Outputs Visual
//------------------------------------------------------------------------
void outputVisual(char* ptr)
{
  //purchase components for a display module
}
//------------------------------------------------------------------------
//                           Outputs Audio
//------------------------------------------------------------------------
void outputAudio(char* ptr)
{
  //purchase speaker, and speaker components
  //purchase micro SD, SD, etc to store sound variables
}
//------------------------------------------------------------------------
//                           Shutdown Timer
//------------------------------------------------------------------------
void shutdownTimer()
{
  //purchase shutdown components
}
//------------------------------------------------------------------------
//                           Add Function
//------------------------------------------------------------------------

//communicate via serial
//switch must be set to access, if set, permanently rewrites function variables
//wait for feedback
//display current options
//allow user to input/edit/delete options freely
