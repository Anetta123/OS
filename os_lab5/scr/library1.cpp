#include <cmath>
extern "C" float Derivative(float A, float deltaX);
extern "C" int PrimeCount(int A, int B);


float Derivative(float A, float deltaX){
    return (cosf (A + deltaX) - cosf(A))/deltaX;
}
 
int PrimeCount(int A, int B){
    bool mod = false;
    int quality = 0;
    for (int i = A+1; i < B+1; i++){
        for (int j = i-1; j > 0; j--){
            if (i % j == 0){
                mod = true;
                break;
            }
        } 
        if (mod == true){
            mod = false;
            quality += 1;
        }
    }
    return quality;
}