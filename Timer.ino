const unsigned long timerDuration = 60000;  // 5 minutes in milliseconds
unsigned long startTime;
bool timerRunning = false;



void timer_loop() {
  if (!timerRunning) {
    // Start the timer
    startTime = millis();
    timerRunning = true;
    display_Data_txt("Timer started!");
  }

  // Calculate the remaining time and print it every second
  unsigned long elapsedTime = millis() - startTime;
  remainingTime = timerDuration - elapsedTime;

  if (timerRunning && remainingTime > 0) {
    // Show the countdown in seconds
    unsigned long remainingSeconds = remainingTime / 1000;
    Serial.print("Time remaining: ");
    Serial.print(remainingSeconds);
    display_Data_txt(" seconds");
    delay(1000);  // Update every second
  }

  // Check if the timer has elapsed
  if (timerRunning && elapsedTime >= timerDuration) {
    display_Data_txt("Time's up!");
    remainingTime = 0;
    delay(5000);  // Stop the program, no need to refresh anymore
    
  }
}
