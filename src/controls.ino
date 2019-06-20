
#define PWMA 9
#define DIRA 8

#define PWMB 6
#define DIRB 7

#define CH1_PIN 2
#define P_TIMEOUT 40000

#define CH_MIN 980
#define CH_MAX 1940
#define DEADZONE_LOW 1450
#define DEADZONE_HIGH 1550

#define LOOP_DELAY 20 //how much delay add to one loop

int v1;

void setup() {
  Serial.begin(9600);

  
  //Setup Channel A
  pinMode(PWMA, OUTPUT); //Initiates Motor Channel A pin
  pinMode(DIRA, OUTPUT); //Initiates Brake Channel A pin
  //pinMode(LED, OUTPUT);

  pinMode(CH1_PIN, INPUT);
}

int readAndGetOutput(int pin) {
  int ch = pulseIn(pin, HIGH, P_TIMEOUT);
  //Serial.println(ch);
  int v1 = map(ch, CH_MIN, CH_MAX, -255, 255);
  if (v1 < -255 || v1 > 255) {
    v1 = 0;
  }
  if (ch >= DEADZONE_LOW && ch < DEADZONE_HIGH) {
    v1 = 0;
  }
  //v1 = constrain(v1, -255, 255);
  Serial.println(v1);
  return v1;
}

void runMotor(int PWMThrottlePin, int ReversePin, int value) {
  int valueFinal;
  if (value >= 0) {
    digitalWrite(ReversePin, HIGH); //Establishes forward direction
    valueFinal = value;
  } else {
    digitalWrite(ReversePin, LOW);
    valueFinal = -value;
  }
  analogWrite(PWMThrottlePin, valueFinal);   //Spins the motor
}

void loop(){
   
  runMotor(PWMA, DIRA, readAndGetOutput(CH1_PIN));

  
  
  //Serial.println(v1);
  
  
  
  delay(LOOP_DELAY);
}
