#include<iostream>
#include <stdio.h>
#include<stdlib.h>
#include<dlfcn.h>
using namespace std;

int main(){
    void* adres = NULL;//адресс для доступа к библиотеке
    //указатели на функции 1 и 2
    int (*PrimeCount)(int A, int B);
    float (*Derivative)(float A, float deltaX);
    
    const char* libeary_mas[]={"libd1.so", "libd2.so"};
    int curlib;
    int statl;
    cout<<"Enter the start library:"<<endl;
    cout << '\t' << "1 for first library" <<endl;
    cout << '\t' << "2 for second library" <<endl;
    cin>>statl;
    bool flag = 1;
    while(flag){
        if (statl==1){
            curlib = 0;
            flag = 0;
        }
        else if(statl==2){
            curlib=1;
            flag=0;
        }
        else{
            cout<<"Please, enter again!"<<endl;
            cin>>statl;
        }
    }
    adres = dlopen(libeary_mas[curlib],RTLD_LAZY);//RTLD_LAZY выполняется поиск только тех символов, на которые есть ссылки из кода
    if (!adres){
        cout<<"Error";
        exit(EXIT_FAILURE);
    }
    PrimeCount = (int(*)(int , int))dlsym(adres,"PrimeCount");//возвращаем адрес функции из памяти библиотеки /dlsym присваивает указателю на функцию, объявленному в начале, ее адрес в библиотеке
    Derivative = (float(*)(float, float))dlsym(adres, "Derivative");
    int command;
    cout<<"Please read the nexst ruls? before you enter the command";
    cout << '\t' << "0 for changing the contract;" << std:: endl;
    cout << '\t' << "1 for calculating Derivative; " << std:: endl;
    cout << '\t' << "2 for calculating PrimeCount; " << std:: endl;
    while(printf("Please enter your command: ") && (scanf("%d", &command)) != EOF){
        if (command==0){
            dlclose(adres);//освобождает указатель на библиотеку и программа перестает ей пользоваться
            if (curlib==0){
                curlib=1;
                adres=dlopen(libeary_mas[curlib],RTLD_LAZY);
                if(!adres){
                    cout<<"Error";
                    exit(EXIT_FAILURE);
                }
                PrimeCount = (int(*)(int , int))dlsym(adres,"PrimeCount");//возвращаем адрес функции из памяти библиотеки /dlsym присваивает указателю на функцию, объявленному в начале, ее адрес в библиотеке
                Derivative = (float(*)(float, float))dlsym(adres, "Derivative");
   
            }
            else if(curlib==1){
                curlib=0;
                adres = dlopen(libeary_mas[curlib],RTLD_LAZY);
                if(!adres){
                    cout<<"Error";
                    exit(EXIT_FAILURE);
                }
                PrimeCount = (int(*)(int, int))dlsym(adres,"PrimeCount");//возвращаем адрес функции из памяти библиотеки /dlsym присваивает указателю на функцию, объявленному в начале, ее адрес в библиотеке
                Derivative = (float(*)(float, float))dlsym(adres, "Derivative");
 
            }
            cout << "You have changed contracts!" << std:: endl;
        }
        else if (command==2){
            int A, B;
            cin>>A>>B;
            int  primeCount =PrimeCount(A,B);
            if (primeCount==-1){
                cout<<"please enter again\n";
            }
            else{
                cout<<"PrimeCount("<< A<<","<<B<<")="<<PrimeCount(A, B)<< endl; 
            }
        }
        else if (command==1){
            float A, deltaX;
            cin>>A>>deltaX;
            float  derivative =Derivative(A, deltaX);
            if (derivative==-1){
                cout<<"please enter again\n";
            }
            else{
                cout<< "Derivative("<<A<<","<<deltaX<<")="<<Derivative(A,deltaX)<<endl;
            }
        }
        else{
            cout<<"You had to enter only 0, 1 or 2!" << std:: endl;
        }
    }
    dlclose(adres);
    return 0;
}