#include <cmath>
#include <vector>
using namespace std;
extern "C" float Derivative(float A, float deltaX);
extern "C" int PrimeCount(int A, int B);


float Derivative(float A, float deltaX) {
  return (cosf(A + deltaX) - cosf(A - deltaX)) / (2 * deltaX);
}

int PrimeCount(int A, int B){
     vector<bool> numbers(B, true);
     int quality = 0;
     for (int i = 2; i*i <= B; i++){
         if (numbers[i] == true){
             for (int j = i*i; j < B; j+=i){
                 numbers[j] = false;
             }
        }
    }
    for (int i = A; i<B; i++){
        if (numbers[i] == true){
            quality +=1; 
        }
    }
    return quality;
}