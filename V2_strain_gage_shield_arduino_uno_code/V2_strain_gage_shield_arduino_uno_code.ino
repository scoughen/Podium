// SGS Calibration by linear interpolation for Strain 1 and Strain 2

// Put two known loads on the Strain Gauge sensor and write obtained values below :  (You can use Strain 1 or Strain 2 or the two Strains) 

float ReadingA_Strain1 = 866.0;
float LoadA_Strain1 = 0.0; //  (g) 
float ReadingB_Strain1 = 947.0;
float LoadB_Strain1 = 2.9; //  (g) 
float sum;
float newReading_Strain1;


int time_step = 0 ; // reading every 0.75s
long time = 0;

void setup() {
  Serial.begin(9600); //  setup serial baudrate
  analogReference(INTERNAL1V1);
}

void loop() {

  sum = 0;
  
  for (int i = 0; i<=1250; i++) {
    newReading_Strain1 = analogRead(0);  // analog in 0 for Strain 1
    sum = sum + newReading_Strain1;
    delay(1);
  }
  
  newReading_Strain1 = sum/1250;

  // Calculate load by interpolation 
  float load_Strain1 = ((LoadB_Strain1 - LoadA_Strain1)/(ReadingB_Strain1 - ReadingA_Strain1)) * (newReading_Strain1 - ReadingA_Strain1) + LoadA_Strain1;
  
  // millis returns the number of milliseconds since the board started the current program
  if(millis() > time_step+time) {
    Serial.print("Reading_Strain1 : ");
    Serial.print(newReading_Strain1);     // display strain 1 reading
    Serial.print("  Load_Strain1 : ");
    Serial.println(load_Strain1,4);     // display strain 1 load
    Serial.println('\n'); 
    time = millis();
  }
}
