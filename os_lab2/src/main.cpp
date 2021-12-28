#include "unistd.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;
 
int main()
{
    cout << "Enter file name:" << endl; 
    string fileName;
    cin >> fileName; 
    int fd[2]; int fd1[2];
    pipe(fd); //канал, связывающий процессы, к концам привязаны два дескриптора (0и1)
    pipe(fd1);
    int id = fork(); //создает дочерний процесс
    if (id == -1)
    {
        perror("fork error");
        return -1;
    }
    else if (id == 0) 
    {
       
        float res;
	    int n = 1; 
        int flag = 0;
        ofstream out(fileName); 
        while (read(fd[0], &n, sizeof(int)) && n != 0) { //цикл считывания размера массива
            float *p = new float[n]; 
            read(fd[0], p, sizeof(float[n]));// читаем массив из пайпа
            res = p[0]; 
            for (int i = 1; i < n; i++){
                if (p[i] == 0) {
                    flag = 1;
                    write(fd1[1], &flag, sizeof(int));
                    exit(-1);
                }
                res = res / p[i]; 
            }
            cout << "res: " << res << endl; 
            out << res << endl; 
            delete [] p; 
            write(fd1[1], &flag,  sizeof(int));
        }
        out.close(); 
        close(fd1[0]);
        close(fd1[1]);
        close(fd[0]); 
        close(fd[1]);
    }
    else
    {
    
        printf("[%d] It's parent. Child id: %d\n", getpid(), id);
        float num;
        string line; 
        int flag = 0;
        vector<float> vec;
        cout << "Enter numbers:" << endl;
        cin.ignore(); 
        while(cin.good() && getline(cin, line)){ 
        stringstream inp(line);  // преобразует строку в отдельные числа
	    while (inp >> num) {
		    vec.push_back(num); // заполняет вектор
            }
        int n = vec.size(); // задает размер будующего массива
        float *p = new float[n]; 
        for (int i = 0; i < vec.size(); i++){
            p[i] = vec[i]; // заполняем массив из вектора
            }
        write(fd[1], &n, sizeof(int)); 
        write(fd[1], p, sizeof(float[n]));
        vector<float>().swap(vec); // очищаем вектор
        delete [] p; 
        read(fd1[0], &flag, sizeof(float[n]));
        if (flag == 1) {
            exit(-1);
	        }
        }
        close(fd1[0]); 
        close(fd1[1]);
        close(fd[0]); 
        close(fd[1]);
    }
    return 0;
}
