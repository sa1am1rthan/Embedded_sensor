#include <Arduino_LSM9DS1.h>  

// Constants
const int sampleRate = 100;    
float threshold1 = 12;       

// Gyroscope Data Variables
float filt1 = 0;               
float prevFilt1 = 0;           

float in[7] = {0, 0, 0, 0, 0, 0, 0};
float Ou[7] = {0, 0, 0, 0, 0, 0, 0};
int counter1 = 0;
int counter2 = 0;
int var_k = 0;
int i = 0;
float gyro_up_peak = 0;
float gyro_down_peak = 0;

int gyro_count_enable = 1;

// Butterworth filter coefficients (2 Hz)
const float b[4] = {0.000000000853160, 0.000000005118957, 0.000000012797393, 0.000000017063191};
const float a[7] = {-0.7844171769, 4.8969248914, -12.7416173292, 17.6873761799, 12.7416173292, -13.8155108061, 5.7572441862};



void init_stepcount(){

  Serial.begin(9600);


  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }
  Serial.println("IMU initialized.");

}

void getStepCount() {
  if (IMU.gyroscopeAvailable()) {
    float gx, gy, gz;
    IMU.readGyroscope(gx, gy, gz);


    for (int j = 0; j < 6; j++) {
      in[j] = in[j + 1];
      Ou[j] = Ou[j + 1];
    }

    // if(gx < 0 ){
    //   gx = gx + (-5);
    // }else if (gx > 0 ){
    //   gx = gx + (5);
    // }



    in[6] = gx; 

    
    filt1 = (0.000000000853160 * (in[0] + in[6]) + 0.000000005118957 * (in[1] + in[5]) +  0.000000012797393* (in[2] + in[4]) +  0.000000017063191* in[3]
            + -0.7844171769 * Ou[0] + 4.8969248914 * Ou[1] + -12.7416173292 * Ou[2] + 17.6873761799 * Ou[3] + -13.8155108061 * Ou[4] + 5.7572441862 * Ou[5]);


    


    Ou[6] = filt1;

    

    
    detectZeroCross();

    
    Serial.print("Filtered Gyro-X: ");

    // Serial.println(gx);
    

    Serial.print(filt1);
    Serial.print(" | Steps: ");
    Serial.println(maincount);

   
    delay(1000 / sampleRate);
  }
}


void detectZeroCross() {
  
  if (Ou[6] < 0 && Ou[5] > 0 && gyro_count_enable == 1) {
    counter1 = 1;
    counter2 = 0;
    var_k = i;
    if (gyro_up_peak > threshold1) {
      maincount++;  
    }
  }

  
  if (Ou[6] > 0 && Ou[5] < 0 && gyro_count_enable == 1) {
    counter2 = 1;
    counter1 = 0;
    var_k = i;
    if (gyro_down_peak < -threshold1) {
      maincount++; 
    }
  }

  
  if (Ou[6] < Ou[5] && Ou[5] > Ou[4] && counter2 == 1) {
    gyro_up_peak = prevFilt1;
  }

  
  if (Ou[6] > Ou[5] && Ou[5] < Ou[4] && counter1 == 1) {
    gyro_down_peak = prevFilt1;
  }

  
  prevFilt1 = filt1;

}