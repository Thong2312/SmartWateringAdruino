
 
int const SENSOR_MH_D_PIN = 4;
int const SENSOR_MH_A_PIN = A0;
int const T_RELAY_PIN = 2;

int const TIME_TO_GET_SAMPLE = 5000; //5s
int const SAMPLE_TIME = 500; //0.5 s


int const TREE_WATER_LEVEL_HIGH = 600;
int const TREE_WATER_LEVEL_LOW = 300;

int sensorMHValue = 0;//store sensor value

int bumpStatus = 0;
int waterStatus = 0;// -1: less water, 0: enough water,  +1 : more water

void setup() {
  //serial print
  Serial.begin(9600);

  pinMode(SENSOR_MH_D_PIN,INPUT);
  pinMode(T_RELAY_PIN, OUTPUT);
  
}

void loop() {
  // process and checking to watering
  wateringProcess();

  // Send information to serial port
  printToSerialPort();
  
}

void wateringProcess(){
  int sensorStatus = digitalRead(SENSOR_MH_D_PIN);
  int sensorValue = getSensorSampleValue();
  if(sensorStatus == 0){
    if(sensorValue > TREE_WATER_LEVEL_HIGH){
      digitalWrite(T_RELAY_PIN, HIGH);
      bumpStatus = 1;
      waterStatus = -1;
    }else if(sensorValue < TREE_WATER_LEVEL_LOW){
      digitalWrite(T_RELAY_PIN, LOW);
      bumpStatus = 0;
      waterStatus = +1;
    }else{
      digitalWrite(T_RELAY_PIN, LOW);
      bumpStatus = 0;
      waterStatus = 0;
    }
  }else{
    digitalWrite(T_RELAY_PIN, HIGH);
      bumpStatus = 1;
      waterStatus = -1;
  }
}

int getSensorSampleValue(){
  int value = 0;
  int t = TIME_TO_GET_SAMPLE/ SAMPLE_TIME;
  int total = 0;
  for(int i =0; i < t ; i++){
    total += analogRead(SENSOR_MH_A_PIN);
    delay(t);
  }
  return total / t;
}
void printToSerialPort(){
  Serial.print("Bumper enable: "); Serial.println(bumpStatus);
  Serial.print("Sensor value: "); Serial.println(sensorMHValue);
}
