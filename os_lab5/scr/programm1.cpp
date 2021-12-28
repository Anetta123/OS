#include <iostream>
using namespace std;

//extern "C" для использования float в работе с С++

extern "C" float Derivative(float A, float deltaX);
extern "C" int PrimeCount(int A, int B);

int main()
{
    int flag;
    cout << "Please enter the flag:\n";
    while (scanf("%d",&flag) > 0 ){
        if (flag == 2){
            cout<<"Please enter your dates:\n";
            int A, B;
            cin>>A>>B;
            cout<<"PrimeCount("<< A<<","<<B<<")="<<PrimeCount(A, B)<< endl;
        }
        else if (flag == 1){
            cout<<"Please enter your dates:\n";
            float A, deltaX;
            cin>>A>>deltaX;
            cout<< "Derivative("<<A<<","<<deltaX<<")="<<Derivative(A,deltaX)<<endl;
        }
    }
    return 0;
}