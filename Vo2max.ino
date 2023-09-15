#define AGE 24
#define GRADE 1.0
float Vo2max;
float Vo2;
int speed;

void vo2maxloop()
{

  speed=maincount*0.413/60; //stride length of average human 0.413
  Vo2 = 0.2 * speed + 0.9 * speed * GRADE + 3.5;

  // Calculate Vo2max
  Vo2max = Vo2 * (220 - AGE) / bpm;
  display_Data(Vo2max);
}