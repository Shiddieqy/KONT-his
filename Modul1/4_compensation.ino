#define MINIMUM_POSITIF 24
#define MINIMUM_NEGATIF 24
float compensate(int input){
  if(input>1){
    return MINIMUM_POSITIF + input*(100-MINIMUM_POSITIF)/100;
  }
  if(input<-1){
    return -1*MINIMUM_NEGATIF + input*(100-MINIMUM_NEGATIF)/100;
  }
  return 0;
}

float compensation(float input){
  float a;
  if(input == 0){
    a = 0;
    return a;
  }
  else if(input > 0){
    a = ((input-1)*74/99) + 26;
    return a;
  }
  else if(input < 0){
    a = ((input+1)*76/99) - 24;
    return a;
  }
}