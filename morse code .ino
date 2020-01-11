

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
Adafruit_SSD1306 display(128, 64,7, 6, 4, 3, 5);

void menu_from_mors();
void menu2_from_mors();
void menu_to_mors();
void menu2_to_mors();
void to_morse(char *message, int *morsecode, int message_len, int * count_pointer);
void beap(int beap);
char from_morse(int x);


int menu=0;
int d_menu=0;
int d_menu2=0;
char alphabet[27]={'.','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
char message[20]; 

char led_or_buzzer='b';

int order=0; int morsecode[20]; int count=0; int *count_pointer=&count;


int letter=0;
int chosen_letter=0;
int cursorx=0;
int cursory=0;
int a=0;

int pushed=2;
int wait_count=0;
int listen_count=0;
int listen_mode=0;
int code=3;


void setup() {
  Serial.begin(9600);

  /*if(!display.begin(SSD1306_SWITCHCAPVCC)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
    
  }*/

  pinMode(12, INPUT_PULLUP);
  pinMode(13, OUTPUT);
  pinMode(11, INPUT_PULLUP);
  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  menu_to_mors();
}

void loop() {
    delay(1);
  if (listen_mode==1){
     if (digitalRead(12)==HIGH){


              if (pushed==0){
                            if (wait_count>400){
                                Serial.print(2);
                                Serial.print("\n");
                                
                                
                                display.setTextSize(2);
                                display.setTextColor(WHITE);
                                display.setCursor(cursorx,20);
                                display.println(from_morse(code));
                                cursorx+=20;
                                

                                display.display();
                                
                                
                                
                                code=3;   
                                
                                }
                        }
                        tone(10, 1000);
                        pushed=1;
                        wait_count=0;
                        
                }else{
                      if (pushed==1){
                            if(listen_count>100){
                                Serial.print(1);
                                code*=10;
                                code++;
                                //Serial.print("\n");
                            }else{
                                Serial.print(0);
                                code*=10;
                                //Serial.print("\n");
                                }
                        }
                      listen_count=0;
                      noTone(10);
                      if (pushed==1)
                          pushed=0;}
                if (pushed==1)
                    listen_count++;
                if (pushed==0)
                    wait_count++;
   }else{
//----------------------------------------------------------------------------
       if (digitalRead(12)==HIGH){
        if(d_menu==0){
          switch (menu){
            case 0:
                display.clearDisplay();
                menu_from_mors();
                menu=1;
               
                break;
            case 1:
                display.clearDisplay();
                menu_to_mors();
                menu=0;
                break;
            case 2:
                letter=letter%27;
                
                display.clearDisplay();
                cursorx=0;
                menu2_to_mors();
                
               if (chosen_letter!=0){
                for (int i=0;i<chosen_letter;i++){
                  display.setTextSize(2);
                  display.setTextColor(WHITE);
                  display.setCursor(cursorx,16);
                  display.println(message[i]);
                  
                  display.display();
                  cursorx+=15;
                  
                }}
                display.setTextSize(2);
                display.setTextColor(WHITE);
                display.setCursor(cursorx,16);
                display.println(alphabet[letter]);
                display.display();
                menu=2;                
                letter+=1;       
                
                break;
     }
        }
        d_menu=1;}
     else  d_menu=0;}

     if (digitalRead(11)==HIGH){
      if(d_menu2==0){
        switch(menu){
          case 0:
              menu2_to_mors();
              menu=2;
              break;
          case 1:             
              menu2_from_mors();
              listen_mode=1;
              menu=3;
              break;
          case 2:
              if(letter==1){
                to_morse(message, morsecode, chosen_letter, count_pointer);
                
                
                
                for(order=0;order < count-1;order++){
                    beap(morsecode[order]);
                    Serial.print(morsecode[order]);
                }
                
              }else{
              message[chosen_letter]=alphabet[letter-1];  
              chosen_letter+=1;  
              cursorx+=15;
              menu=2;             
              letter=0; }      
              break;}
          
        }
        d_menu2=1;}
     else{  d_menu2=0;}
      
     
   
}

void menu_to_mors(){
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println(">To Mors");
  display.setCursor(0,25);
  display.println(" From Mors");
  display.display();
  
}
void menu_from_mors(){
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println(" To Mors");
  display.setCursor(0,25);
  display.println(">From Mors");
  display.display();
}
void menu2_to_mors(){
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("To Mors:");
  display.display();

  
}
void menu2_from_mors(){
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("From Mors:");
  display.display();}


  void to_morse(char *message, int *morsecode, int message_len, int * count_pointer){
  
      int A[2]={0,1};     int B[4]={1,0,0,0}; int C[4]={1,0,1,0}; int D[3]={1,0,0};   int E[1]={0};             int F[4]={0,0,1,0};
      int G[3]={1,1,0};   int H[4]={0,0,0,0}; int I[2]={0,0};     int J[4]={0,1,1,1}; int K[3]={1,0,1};         int L[4]={0,1,0,0};
      int M[2]={1,1};     int N[2]={1,0};     int O[3]={1,1,1};   int P[4]={0,1,1,0}; int Q[4]={1,1,0,1};       int R[3]={0,1,0};         int S[3]={0,0,0};   
      int T[1]={1};       int U[3]={0,0,1};   int V[4]={0,0,0,1}; int W[3]={0,1,1};   int X[4]={1,0,0,1};       int Y[4]={1,0,1,1};       int Z[4]={1,1,0,0};
      int PERIOD[6]={0,1,0,1,0,1}; int COMMA[5]={1,1,0,0,1}; int ONE[5]={0,1,1,1,1};  int TWO[5]={0,0,1,1,1};   int THREE[5]={0,0,0,1,1}; int FOUR[5]={0,0,0,0,1};  
      int FIVE[5]={0,0,0,0,0};     int SIX[5]={1,0,0,0,0};   int SEVEN[5]={1,1,0,0,0};int EIGHT[5]={1,1,1,0,0}; int NINE[5]={1,1,1,1,0};  int ZERO[5]={1,1,1,1,1};
      int *temp,lenght;       int count=0;  int space=0;
      for (int i=0; i < message_len; i++){switch(message[i]){ 
            case 'a':   temp= A;      lenght=2;   break;  case 'b':   temp= B;      lenght=4;   break;
            case 'c':   temp= C;      lenght=4;   break;  case 'd':   temp= D;      lenght=3;   break;
            case 'e':   temp= E;      lenght=1;   break;  case 'f':   temp= F;      lenght=4;   break;
            case 'g':   temp= G;      lenght=3;   break;  case 'h':   temp= H;      lenght=4;   break;
            case 'i':   temp= I;      lenght=2;   break;  case 'j':   temp= J;      lenght=4;   break;
            case 'k':   temp= K;      lenght=3;   break;  case 'l':   temp= L;      lenght=4;   break;
            case 'm':   temp= M;      lenght=2;   break;  case 'n':   temp= N;      lenght=2;   break;
            case 'o':   temp= O;      lenght=3;   break;  case 'p':   temp= P;      lenght=4;   break;
            case 'q':   temp= Q;      lenght=4;   break;  case 'r':   temp= R;      lenght=3;   break;
            case 's':   temp= S;      lenght=3;   break;  case 't':   temp= T;      lenght=1;   break;
            case 'u':   temp= U;      lenght=3;   break;  case 'v':   temp= V;      lenght=4;   break;
            case 'w':   temp= W;      lenght=3;   break;  case 'x':   temp= X;      lenght=4;   break;
            case 'y':   temp= Y;      lenght=4;   break;  case 'z':   temp= Z;      lenght=4;   break;
            case '.':   temp= PERIOD; lenght=5;   break;  case ',':   temp= COMMA;  lenght=5;   break;
            case '1':   temp= ONE;    lenght=5;   break;  case '2':   temp= TWO;    lenght=5;   break;
            case '3':   temp= THREE;  lenght=5;   break;  case '4':   temp= FOUR;   lenght=5;   break;
            case '5':   temp= FIVE;   lenght=5;   break;  case '6':   temp= SIX;    lenght=5;   break;
            case '7':   temp= SEVEN;  lenght=5;   break;  case '8':   temp= EIGHT;  lenght=5;   break;
            case '9':   temp= NINE;   lenght=5;   break;  case '0':   temp= ZERO;   lenght=5;   break;
            case ' ':   space=1;   break;}
            if (space==0){
            for (int j=0; j<lenght; j++){
                 morsecode[count]=temp[j];
                 count++;}}
            morsecode[count]=2;
            count++;
            space=0;} 
      *count_pointer = count;};
   
void beap(int beap){
  
      if (led_or_buzzer =='l'){
           switch (beap){
              case 2:delay(1000); break;   
              case 1:digitalWrite(10,HIGH);delay(200);digitalWrite(10,LOW);delay(400);break;
              case 0:digitalWrite(10,HIGH);delay(50); digitalWrite(10,LOW);delay(400);break;};}
      else{switch (beap){
              case 2:delay(500); break;   
              case 1:tone(10,1000);delay(200);noTone(10);delay(200);break;
              case 0:tone(10,1000);delay(50); noTone(10);delay(200);break;}}};


char from_morse(int x){
      int A=301;     int B=31000; int C=31010; int D=3100;   int E=30;             int F=30010;
      int G=3110;   int H=30000; int I=300;     int J=30111; int K=3101;         int L=30100;
      int M=311;     int N=310;     int O=3111;   int P=30110; int Q=31101;       int R=3010;         int S=3000;   
      int T=31;       int U=3001;   int V=30001; int W=3011;   int X=31001;       int Y=31011;       int Z=31100;
      if (x==A) return 'a';if (x==B) return 'b';if (x==C) return 'c';if (x==D) return 'd';if (x==E) return 'e';if (x==F) return 'f';
      if (x==G) return 'g';if (x==H) return 'h';if (x==I) return 'i';if (x==J) return 'j';if (x==K) return 'k';if (x==L) return 'l';
      if (x==M) return 'm';if (x==N) return 'n';if (x==O) return 'o';if (x==P) return 'p';if (x==Q) return 'q';if (x==R) return 'r';if (x==S) return 's';
      if (x==T) return 't';if (x==U) return 'u';if (x==V) return 'v';if (x==W) return 'w';if (x==X) return 'x';if (x==Y) return 'y';if (x==Z) return 'z';
   
  
}
