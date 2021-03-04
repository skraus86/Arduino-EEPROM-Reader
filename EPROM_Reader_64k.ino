/*
ROM Reader. Quick Arduino program to read a parallel-accessed ROM and dump it to the serial
port in hex.

Oddbloke. 16th Feb 2014.
 */
 
// How I've wired the digital pins on my Arduino to the address and data pins on
// the ROM.
static const int kPin_A0  = 53;
static const int kPin_A1  = 51;
static const int kPin_A2  = 49;
static const int kPin_A3  = 47;
static const int kPin_A4  = 45;
static const int kPin_A5  = 43;
static const int kPin_A6  = 41;
static const int kPin_A7  = 39;
static const int kPin_A8  = 46;
static const int kPin_A9  = 48;
static const int kPin_A10 = 52;
static const int kPin_A11 = 50;
static const int kPin_A12 = 37;
static const int kPin_A13 = 44;

static const int kPin_D0 = 28;
static const int kPin_D1 = 30;
static const int kPin_D2 = 32;
static const int kPin_D3 = 33;
static const int kPin_D4 = 31;
static const int kPin_D5 = 29;
static const int kPin_D6 = 27;
static const int kPin_D7 = 25;

boolean done = false;

const char hex[] = {'0', '1', '2', '3', '4', '5', '6', '7',
              '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
              

void setup()
{
  // set the address lines as outputs ...
  pinMode(kPin_A0, OUTPUT);     
  pinMode(kPin_A1, OUTPUT);     
  pinMode(kPin_A2, OUTPUT);     
  pinMode(kPin_A3, OUTPUT);     
  pinMode(kPin_A4, OUTPUT);     
  pinMode(kPin_A5, OUTPUT);     
  pinMode(kPin_A6, OUTPUT);     
  pinMode(kPin_A7, OUTPUT);     
  pinMode(kPin_A8, OUTPUT);     
  pinMode(kPin_A9, OUTPUT);     
  pinMode(kPin_A10, OUTPUT);     
  pinMode(kPin_A11, OUTPUT);     
  pinMode(kPin_A12, OUTPUT);     
  //pinMode(kPin_A13, OUTPUT);
 
  // set the data lines as inputs ...
  pinMode(kPin_D0, INPUT); 
  pinMode(kPin_D1, INPUT); 
  pinMode(kPin_D2, INPUT); 
  pinMode(kPin_D3, INPUT); 
  pinMode(kPin_D4, INPUT); 
  pinMode(kPin_D5, INPUT); 
  pinMode(kPin_D6, INPUT); 
  pinMode(kPin_D7, INPUT); 
  
  Serial.begin(9600);
}

void SetAddress(int addr)
{
  // update the address lines to reflect the address we want ...
  digitalWrite(kPin_A0, (addr & 1)?HIGH:LOW);
  digitalWrite(kPin_A1, (addr & 2)?HIGH:LOW);
  digitalWrite(kPin_A2, (addr & 4)?HIGH:LOW);
  digitalWrite(kPin_A3, (addr & 8)?HIGH:LOW);
  digitalWrite(kPin_A4, (addr & 16)?HIGH:LOW);
  digitalWrite(kPin_A5, (addr & 32)?HIGH:LOW);
  digitalWrite(kPin_A6, (addr & 64)?HIGH:LOW);
  digitalWrite(kPin_A7, (addr & 128)?HIGH:LOW);
  digitalWrite(kPin_A8, (addr & 256)?HIGH:LOW);
  digitalWrite(kPin_A9, (addr & 512)?HIGH:LOW);
  digitalWrite(kPin_A10, (addr & 1024)?HIGH:LOW);
  digitalWrite(kPin_A11, (addr & 2048)?HIGH:LOW);
  digitalWrite(kPin_A12, (addr & 4096)?HIGH:LOW);
  //digitalWrite(kPin_A13, (addr & 8192)?HIGH:LOW);
}

byte ReadByte()
{
  // read the current eight-bit byte being output by the ROM ...
  byte b = 0;
  if (digitalRead(kPin_D0)) b |= 1;
  if (digitalRead(kPin_D1)) b |= 2;
  if (digitalRead(kPin_D2)) b |= 4;
  if (digitalRead(kPin_D3)) b |= 8;
  if (digitalRead(kPin_D4)) b |= 16;
  if (digitalRead(kPin_D5)) b |= 32;
  if (digitalRead(kPin_D6)) b |= 64;
  if (digitalRead(kPin_D7)) b |= 128;
  
  return(b);
}

void loop()
{
  byte d[16];
  unsigned int x, y, addr;
  
  // The only reason I'm choosing to read in blocks of 16 bytes
  // is to keep the hex-dump code simple. You could just as easily
  // read a single byte at a time if that's all you needed.
  
  Serial.println("Reading ROM ...\n");
{
 while (!done){
  for (addr = 0; addr < 8192; addr += 16)
  {
    // read 16 bytes of data from the ROM ...
    for (x = 0; x < 16; x++)
    {
      SetAddress(addr + x); // tells the ROM the byte we want ...
      d[x] = ReadByte(); // reads the byte back from the ROM
    }
  
    // now we'll print each byte in hex ...
    for (y = 0; y < 16; y++)
    {
      Serial.print(hex[ (d[y] & 0xF0) >> 4  ]);
      Serial.print(hex[ (d[y] & 0x0F)       ]);
    }
          
    // and print an ASCII dump too ...
    
   // Serial.print(" ");
    //for (y = 0; y < 16; y++)
   // {
   //  char c = '.';
   //   if (d[y] > 32 && d[y]<127) c = d[y];
   //   Serial.print(c);
   // }
      
    Serial.println("");
  }
  
  // All done, so lockup ...
  while (true) {delay(10000);}
  done = true;
  }
 }
}
