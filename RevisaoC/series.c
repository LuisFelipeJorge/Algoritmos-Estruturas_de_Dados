#include <stdio.h>

int power(int base, int e);
int factorial(int n);
float calculate_serie(int x, int n);

int main(int argc, char const *argv[]){
  int n, x;
  scanf("%d %d", &x, &n);
  printf("%f\n", calculate_serie(x, n));
  return 0;
}

int power(int base, int e){
  int result = 1;
  int i;
  for ( i = 0; i < e; i++){
    result = result*base;
  }
  
  return result;
}

int factorial(int n){
  int result = 1;
  int i;
  if (n == 0) return 1;

  for ( i = 1; i <= n; i++){
    result = result*i;
  }
  
  return result;
}

float calculate_serie(int x, int n){
  float result = x;
  int i;
  for ( i = 1; i <= n; i++){
    if (i%2 == 0){
      result += power(x, 2*i)/(float)factorial(2*i+1);
    }else{
      result -= power(x, 2*i)/(float)factorial(2*i+1);
    }
  }
  return result;
}