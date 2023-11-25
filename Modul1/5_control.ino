#define MAX_INCREMENT 10
#define MAX_PWM 35

float Ti = 0.072917;
float Td = 0.0138153;//0.021265;
float kp = 0.382;
float ki = 0;
float kd = 0.004966;//kp*Td;//kp*Td;
int prev_error = 0;
float integral = 0;
int res;
int sign = 1;

int prop;
int difference;
float T = 0.01;
int prev_res = 0;

float prevR, sum, sumt, prevT;
float integrate(float r){
  sum = sum + (prevR + r)*(T/2);
  prevR = r;
  return sum; 
}

float integratetacho(float r){
  sumt = sumt + (prevR + r)*(T/2);
  prevT = r;
  return sumt; 
}

float k[2] = {1, 0.6077};
float calc_fsf(float thet, float vel, float r){
  if (r == 0) return 0;
  // Serial.print(k[0]*sum-k[0]*sumt);
  // Serial.println("\t");
  // return constrain(k[0]*integrate(r)+k[1]*r-k[0]*integratetacho(vel)-k[1]*vel,-70,70);
  return constrain(integrate(r)-k[0]*integratetacho(vel)-k[1]*vel,-100,100);
}

int calc_pid(int sp, int feedback){
  int error = sp - feedback;
  prop = error*kp;
  difference = constrain((error-prev_error)*kd/T,-255,255);
  prev_error = error;

  sign = 1;
  
  if (prop < 0){
    sign = -1;
  }
  if (abs(prop) >= MAX_PWM){
    return MAX_PWM*sign;
  }
  int leftover = MAX_PWM*sign - prop;
  integral += error*ki*T;
  if (integral*sign > leftover*sign){
    integral = leftover;
  }
  integral = constrain(integral,-MAX_PWM,MAX_PWM);
  res = prop + integral + difference;
  res = constrain(res, prev_res-MAX_INCREMENT, prev_res+MAX_INCREMENT);
  return constrain(res, -MAX_PWM,MAX_PWM);
  prev_res = res;
}
