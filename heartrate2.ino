// Constants for signal processing
const int BUFFER_SIZE = 10;
const int MIN_BPM = 30;
const int MAX_BPM = 200;
const unsigned long MIN_INTERVAL = 60000 / MAX_BPM;
const unsigned long MAX_INTERVAL = 60000 / MIN_BPM;

// Variables for timing and calculations
unsigned long previousMillis = 0;
unsigned long currentMillis = 0;


// Variables for signal processing
int samples[BUFFER_SIZE];
int sampleIndex = 0;
float avgThreshold = 650;  
float alpha = 1;  // Smoothing factor for dynamic threshold

// Variables for serial output timing
unsigned long lastSerialOutput = 0;
const unsigned long SERIAL_INTERVAL = 20;  // Output every 20ms to not overwhelm 9600 baud

void init_GetHeartRate() {
  pinMode(10, INPUT);
  pinMode(11, INPUT);
 
  // Initialize sample buffer
  for(int i = 0; i < BUFFER_SIZE; i++) {
    samples[i] = 0;
  }
}

// Calculate moving average of the signal
int calculateMovingAverage() {
  long sum = 0;
  for(int i = 0; i < BUFFER_SIZE; i++) {
    sum += samples[i];
  }
  return sum / BUFFER_SIZE;
}

// Update sample buffer with new reading
void updateSamples(int newSample) {
  samples[sampleIndex] = newSample;
  sampleIndex = (sampleIndex + 1) % BUFFER_SIZE;
}

// Check if the current value is a valid R peak
bool isValidPeak(int currentValue, int avgValue) {
  // Must be above threshold and local maximum
  if (currentValue < avgThreshold) return false;
 
  // Check if it's a local maximum
  for(int i = 0; i < BUFFER_SIZE; i++) {
    if (samples[i] > currentValue) return false;
  }
 
  // Verify the peak timing
  currentMillis = millis();
  unsigned long interval = currentMillis - previousMillis;
 
  // Check if the interval is physiologically possible
  if (interval < MIN_INTERVAL || interval > MAX_INTERVAL) {
    return false;
  }
 
  return true;
}

void get_HeartRate() {
  int ecgValue = analogRead(A0);
 
  // Apply basic noise filtering
  ecgValue = constrain(ecgValue, 0, 1023);  // Limit to ADC range
 
  // Update sample buffer
  updateSamples(ecgValue);
 
  // Calculate moving average
  int avgValue = calculateMovingAverage();
 
  // Dynamically adjust threshold
  avgThreshold = (alpha * ecgValue) + ((1 - alpha) * avgThreshold);
 
  // Check for valid R peak
  if (isValidPeak(ecgValue, avgValue)) {
    currentMillis = millis();
    unsigned long interval = currentMillis - previousMillis;
   
    // Calculate BPM
    // bpm = 60000 / interval;
   
    // Update timing
    previousMillis = currentMillis;
   
    // Output BPM when detected
   // Serial.print("Heart Rate: ");
    Serial.print(bpm);
   // Serial.println(" BPM");
  }
 
  // Output raw signal and threshold less frequently to accommodate 9600 baud
  if (millis() - lastSerialOutput >= SERIAL_INTERVAL) {
    //Serial.print("Signal:");
   // Serial.print(ecgValue);
   // Serial.print(",Threshold:");
    //Serial.println(avgThreshold);
    lastSerialOutput = millis();
  }
  Serial.println("HEart rate");
 
  delay(2);  // Slightly longer delay for 9600 baud
 // return bpm;
}


  


