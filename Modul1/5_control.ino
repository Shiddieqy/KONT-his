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
int calc_pid(int sp, int feedback){
  prev_res = res;
//  if(sp == 0) return 0;
  int error = sp - feedback;
  // int error2 = sp - (100-feedback);
  // if(abs(error)>abs(error2)){
  //   error = error2;
  // }
  prop = error*kp;
  difference = constrain((error-prev_error)*kd/T,-MAX_PWM,MAX_PWM);
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
}
