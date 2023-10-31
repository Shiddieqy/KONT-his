unsigned long Time, StartTime, LastTime;
unsigned int TimeSampling = 10, DeltaTime;
int InputSerial = 0;
float Motor = 0.0;
float Poten1, Poten2, Tacho1, Tacho2;
unsigned long TotalTime = 0;
int set_poins[5] = {50,20,50,90,20};
bool isrun =0;

void setup() {
  general_setup();
  sensor_setup();
  actuator_setup();
  print_header();
  StartTime = millis();
  LastTime = StartTime;
  InputSerial = 0;
  unsigned long TotalTime = 0;
}
float compensated = 0;
int  counter = 0;
int  increment = 1;
int pidval = 0;
float potn2 = 0;
float seq = 0;
void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()){
    InputSerial = serial(InputSerial);
  }
  Time = millis();
  if (Time - LastTime >= TimeSampling) {
    DeltaTime = Time - LastTime;
    LastTime = Time;
    potn2 = Poten2;
    Poten1 = sample_position_percentage();
    Poten2 = smooth_position_percentage() + 100*seq;
    Tacho1 = sample_velocity_percentage();
    Tacho2 = smooth_velocity_percentage();
    if(Poten2 < potn2-70 ){
      seq+=1;
      Poten2 = smooth_position_percentage() + 100*seq;
    }
    else if(Poten2>potn2+70 ){
      seq-=1;
      Poten2 = smooth_position_percentage() + 100*seq;
    }
//    TotalTime = TimeSampling + TotalTime;
//    if (TotalTime >= 5000) {
//      if (InputSerial == 1){
//         isrun = 1;
//      }
//      InputSerial = set_poins[counter];
//      counter++;
//      if(counter>4){
//        counter =0;
//      }
//      TotalTime = 0;
//    }
    if (Motor<0){
      Tacho2 = -1*Tacho2;
    }
    // compensated = compensate(InputSerial);
    // Motor = run_motor(compensated);
    pidval = calc_pid(InputSerial, Poten2);
    compensated = compensate(pidval);
    Motor = run_motor((float) compensated);
//    Serial.print(Time - StartTime - TimeSampling);
//    Serial.print("\t");
//    Serial.print(DeltaTime);
//    Serial.print("\t");
    Serial.print(InputSerial);
    Serial.print("\t");
    Serial.print(Motor);
    Serial.print("\t");
    Serial.print(Poten1);
    Serial.print("\t");
    Serial.print(Poten2);
    Serial.println("\t");
    // Serial.print(Tacho1);
//    Serial.print(Tacho2);
//    Serial.print("\t");
////    Serial.print(prop);
////    Serial.print("\t");
////        Serial.print(integral);
////    Serial.print("\t");
////        Serial.print(difference);
////    Serial.print("\t");
//      Serial.println(res);
    // Serial.print("\t");
//    counter++;
//    if (counter>=40){
//      counter = 0;
////      Motor = run_motor(0);
//      delay(500);
//      InputSerial+= increment;
//      if(abs(InputSerial)>100){
//        increment = -1*increment;
//        InputSerial =0;
//      }
//    }
//    }
  }
}

void print_header() {
  Serial.println("Time\tDelta\tInput\tMotor\tPos 1\tPos 2\tKec 1\tKec 2");
}
