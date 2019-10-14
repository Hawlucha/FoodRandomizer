//------------------------------------------------------------------------
//                           Global Stuff
//------------------------------------------------------------------------
#define NELEMS(x)  (sizeof(x) / sizeof((x)[0])) //Determines number of elements
char des=-1;//if decision is made, sets to 1,
char Incoming_value=0; //BT set
  
char* option; //final destination
char* drvr; //final driver

struct foodPlace
{
  char pName[20];
  unsigned incl : 1;
  unsigned type : 5;  //5 types: deliv, sit-in, carry-out,fast food, breakfast
  struct foodPlace *next;
  struct foodPlace *prev;
};

struct driver
{
  char dName[20];
};

struct queue
{
  struct foodPlace *head; //head of the queue
  int count; //number of elements
};

//reads in data initially below
//stores info in queue
//uploads queue info to app.
//app sets incl to 0 if unwanted

const byte intPin=3;
//------------------------------------------------------------------------
//                           PROGRMEM Variables
//------------------------------------------------------------------------
const char string_0[] PROGMEM = "IHOP";
const char string_1[] PROGMEM = "Bob Evans";
const char string_2[] PROGMEM = "Sheetz";
const char string_3[] PROGMEM = "McDonalds";
const char string_4[] PROGMEM = "Shoney's";
const char string_5[] PROGMEM = "Five Guys";
const char string_6[] PROGMEM = "Wendy's";
const char string_7[] PROGMEM = "Arby's";
const char string_8[] PROGMEM = "Panda Express";
const char string_9[] PROGMEM = "Subway";
const char string_10[] PROGMEM = "Popeyes";
const char string_11[] PROGMEM = "Long John Silvers";
const char string_12[] PROGMEM = "Taco Bell";
const char string_13[] PROGMEM = "Chipotle";
const char string_14[] PROGMEM = "Applebee's";
const char string_15[] PROGMEM = "Chili's";
const char string_16[] PROGMEM = "Primanti's";
const char string_17[] PROGMEM = "Buffalo Wild Wings";
const char string_18[] PROGMEM = "Outback";
const char string_19[] PROGMEM = "Ogawa";
const char string_20[] PROGMEM = "No 1 Super Buffet";
const char string_21[] PROGMEM = "FRESH MINT";
const char string_22[] PROGMEM = "Ruby Tuesday";
const char string_23[] PROGMEM = "Black Bear";
const char string_24[] PROGMEM = "Fusion";
const char string_25[] PROGMEM = "China King";
const char string_26[] PROGMEM = "Pizza Hut";
const char string_27[] PROGMEM = "Papa Johns";
const char string_28[] PROGMEM = "Chaang";
const char string_29[] PROGMEM =  "D.P. Doughs";
const char string_30[] PROGMEM = "Casa D'Amici";
const char string_31[] PROGMEM = "Clutch Wing Shop";
const char *const string_table[] PROGMEM = {string_0, string_1, string_2, 
string_3, string_4, string_5, string_6, string_7, string_8, string_9, string_10,
string_11, string_12, string_13,string_14, string_15, string_16, string_17,
string_18, string_19, string_21, string_22, string_23,string_24, string_25,
string_26, string_27, string_28, string_29, string_30, string_31};
const uint16_t btype[] PROGMEM={0b00001,0b00001,0b00011,0b00011,0b00001,0b00010,
0b00010,0b00010,0b00110,0b00010,0b0010,0b0010,0b0110,0b0110,0b01000,
0b01000,0b01000,0b11100,0b01100,0b01000,0b01000,0b01000,0b01000,0b01000,
0b01000,0b10100,0b10100,0b10100,0b11100,0b10100,0b10100,0b11100};

//------------------------------------------------------------------------
//                           begins
//------------------------------------------------------------------------
void begins(){
  des=0;
}

//------------------------------------------------------------------------
//                           Setup
//------------------------------------------------------------------------
void setup() {
  pinMode(7,OUTPUT); //keeps Arduino on
  digitalWrite(7,HIGH);
  Serial.begin(9600);
  pinMode(intPin, INPUT_PULLUP); //interruptPin
  attachInterrupt(digitalPinToInterrupt(intPin),begins,CHANGE);
  pinMode(13,OUTPUT);//LED for error

  randomSeed(analogRead(0));//Random Setup
}

//------------------------------------------------------------------------
//                           Loop
//------------------------------------------------------------------------
struct queue *items=NULL;
void loop() {
  int rando=-1; //random number to generate option
  if(isEmpty(items))
    items=createQueue();
  while(des<0)
  {
    poll();
  }
//------------------------------------------------------------------------
//                           Randomize Process
//------------------------------------------------------------------------
  
  if(!des){
    
    des++;
  }
//------------------------------------------------------------------------
//                           Output Process
//------------------------------------------------------------------------
  if(des==1){
    outputVisual(option);
    outputAudio(option);
  }
  shutdownTimer();
}
//------------------------------------------------------------------------
//                           poll
//------------------------------------------------------------------------
void poll(){
  if(Serial.available() > 0)
  {
    Incoming_value = Serial.read();      //Read the incoming data and store it into variable Incoming_value
    Serial.println(Incoming_value);
  }     
}
//------------------------------------------------------------------------
//                           isEmpty
//------------------------------------------------------------------------
int isEmpty(struct queue *items){ //returns 1 if empty
  if(items==NULL)
    return 1;
  if(items->count==0)
    return 1;
  return 0;
}
//------------------------------------------------------------------------
//                           createQueue
//------------------------------------------------------------------------
struct queue* createQueue(){
  struct queue *items=(struct queue*)malloc(sizeof(struct queue));
  items->head=NULL;
  items->count=0;
  return items;
}
//------------------------------------------------------------------------
//                           addPlace
//------------------------------------------------------------------------
//desc will be between 1 and 15,
//n will be a name of a restaraunt
int addPlace(char n[20],int desc){ //returns 0 if failure
  struct foodPlace *place=(struct foodPlace*)malloc(sizeof(struct foodPlace));
  if(place)
  {
    return 0;
  }
  if(items->head==NULL){
    items->head=place;
    items->count++;
  }
  else{
    struct foodPlace *temp= items->head;
    while(temp->next) temp=temp->next;
    temp->next=place;
    items->count++;
  }
  return 1;
}
//------------------------------------------------------------------------
//                           removePlace
//------------------------------------------------------------------------
int removePlace(struct foodPlace *place){ //returns 0 if failure
  if(place)
  {
    return 0;
  }
  if(items->head==NULL){
    items->head=place;
    items->count++;
  }
  else{
    struct foodPlace *temp= items->head;
    while(temp->next) temp=temp->next;
    temp->next=place;
    items->count++;
  }
  return 1;
}
//------------------------------------------------------------------------
//                           Randomizer
//------------------------------------------------------------------------
int randoThing(){
  return random(1,(items->count)+1);
}
//------------------------------------------------------------------------
//                           Picks Place
//------------------------------------------------------------------------
char* optionList(int rando, struct food &bitr)
{
  
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
