/* 
  IR Breakbeam sensors and solenoids
*/
#define SENSORPIN_1 4
#define SENSORPIN_2 2


#define MOSFETPIN_1 7
#define MOSFETPIN_2 8

// variables will change:
int sensorState_1 = 0, lastState_1=0;         // variable for reading the breakbeam 1 status
int sensorState_2 = 0, lastState_2=0;         // variable for reading the breakbeam 2 status

int post_delay = 100;
int pre_delay = 0;

void setup() {
 
  // initialize the MOSFET pins as outputs:
  pinMode(MOSFETPIN_1, OUTPUT);  
  pinMode(MOSFETPIN_2, OUTPUT); 
       
  // initialize the sensor pins as inputs:
  pinMode(SENSORPIN_1, INPUT);  
  pinMode(SENSORPIN_2, INPUT);   

  // turn on the pullup
  digitalWrite(SENSORPIN_1, HIGH); 
  digitalWrite(SENSORPIN_2, HIGH); 
  
  
  Serial.begin(9600);
}

void loop(){
  // read the state of the pushbutton value:
  sensorState_1 = digitalRead(SENSORPIN_1);
  sensorState_2 = digitalRead(SENSORPIN_2);

  // check if the sensor beam 1 is broken
  // if it is, the sensorState is LOW:
  if (sensorState_1 == LOW) {     
    //turn MOSFET on
    delay(pre_delay);
    digitalWrite(MOSFETPIN_1, HIGH); 
    delay(post_delay);       
  } 
  else {
    //turn MOSFET off
    digitalWrite(MOSFETPIN_1, LOW); 
  }
  
  if (sensorState_1 && !lastState_1) {
    Serial.println("Beam 1 Unbroken");
  } 
  if (!sensorState_1 && lastState_1) {
    Serial.println("Beam 1 Broken");
  }
  lastState_1 = sensorState_1;


  //repeating the same but for breakbeam 2
  if (sensorState_2 == LOW) {     
    //turn MOSFET on
    delay(pre_delay);
    digitalWrite(MOSFETPIN_2, HIGH);
    delay(post_delay);         
  } 
  else {
    //turn MOSFET off
    digitalWrite(MOSFETPIN_2, LOW); 
  }
  
  if (sensorState_2 && !lastState_2) {
    Serial.println("Beam 2 Unbroken");
  } 
  if (!sensorState_2 && lastState_2) {
    Serial.println("Beam 2 Broken");
  }
  lastState_2 = sensorState_2;
}
