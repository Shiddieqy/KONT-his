#define MINIMUM_POSITIF 23
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
