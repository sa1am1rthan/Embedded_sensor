

int maincount = 0;
int bpm = 120;
unsigned long remainingTime;
//int timerfinish =0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  init_stepcount();
  init_Display();
  init_GetHeartRate();
  
 // init_GetHeartRate();

  delay(2500);
 

}

void loop() {
  // put your main code here, to run repeatedly:
  
  display_init_timer("5-minute timer ready!");

  delay(5000);
  void clear_disp();
  
  timer_loop();
  while(remainingTime){
    timer_loop();
    getStepCount();
    // get_HeartRate();
    display_step(maincount);
    delay(20);
  }
  
  display_Data(bpm);
  delay(5000);
  
  vo2maxloop();

  delay(10000);
  
}
