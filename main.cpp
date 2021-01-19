#include <iostream>
#include <string>
#include "LargeInt.h"
#include "Rsa.h"
#include <ctime>
#include <time.h>
#include <vector>
#include <fstream>



using namespace std;

void perform_benchmark(int n);
float benchmark_multiplication(int n);
float benchmark_addition(int n);
float benchmark_soustraction(int n);
float benchmark_div10(int n);
float benchmark_mod10(int n);
void save_log(string log);

LargeInt rand617();
LargeInt rand1000();
unsigned int nb_bits = 1024;


int main()
{
    /* initialize random seed: */
    srand (time(NULL));


    perform_benchmark(100);

    /*
    Rsa rsa_param = Rsa("key1.txt");
    LargeInt M("13");
    LargeInt d("7");
    LargeInt test = LargeInt::mod_pow(M, d, rsa_param);
    cout << test << endl;
    */

    return 0;

}

void perform_benchmark(int n)
{
    cout << "#Performance operations#" << endl;
    benchmark_addition(n);
    benchmark_soustraction(n);
    benchmark_multiplication(n);
    benchmark_div10(n);
    benchmark_mod10(n);
}

float benchmark_multiplication(int n)
{
    save_log("MULT");
    clock_t temps_initial;
    clock_t temps_final;
    vector<float> temps_cpu;
    float temps_cumule = 0.0;

    for (int i = 0; i < n; i++)
    {
        //Generer deux nombres A et B 1024 bits aleatoire
        LargeInt A = rand617();
        LargeInt B = rand617();
        //Start timer
        temps_initial = clock();
        //operation a mesurer
        LargeInt result = A * B;
        //End timer
        temps_final = clock ();
        //sauvegarde temps
        temps_cpu.push_back((temps_final - temps_initial)* 1e-3);
        temps_cumule += temps_cpu.at(i);
        save_log(result.to_str() + "," + A.to_str() + "," + B.to_str());
    }
    cout << "[" << n << " Multiplications]" << temps_cumule << " s" << endl;
    return temps_cumule;
}

float benchmark_addition(int n)
{
    save_log("ADD");
    clock_t temps_initial;
    clock_t temps_final;
    vector<float> temps_cpu;
    float temps_cumule = 0.0;

    for (int i = 0; i < n; i++)
    {
        //Generer deux nombres A et B 1024 bits aleatoire
        LargeInt A = rand617();
        LargeInt B = rand617();
        //Start timer
        temps_initial = clock();
        //operation a mesurer
        LargeInt result = A + B;
        //End timer
        temps_final = clock ();
        //sauvegarde temps
        temps_cpu.push_back((temps_final - temps_initial)* 1e-3);
        temps_cumule += temps_cpu.at(i);
        save_log(result.to_str() + "," + A.to_str() + "," + B.to_str());
    }
    cout << "[" << n << " Additions]" << temps_cumule << " s" << endl;
    return temps_cumule;
}

float benchmark_soustraction(int n)
{
    save_log("SOUS");
    clock_t temps_initial;
    clock_t temps_final;
    vector<float> temps_cpu;
    float temps_cumule = 0.0;

    for (int i = 0; i < n; i++)
    {
        //Generer deux nombres A et B 1024 bits aleatoire
        LargeInt A = rand617();
        LargeInt B = rand617();
        LargeInt biggest;
        LargeInt lowest;
        if( A < B )
        {
            biggest = B;
            lowest = A;
        }
        else
        {
            biggest = A;
            lowest = B;
        }

        //Start timer
        temps_initial = clock();
        //operation a mesurer
        LargeInt result = biggest - lowest;
        //End timer
        temps_final = clock ();
        //sauvegarde temps
        temps_cpu.push_back((temps_final - temps_initial)* 1e-3);
        temps_cumule += temps_cpu.at(i);
        save_log(result.to_str() + "," + biggest.to_str() + "," + lowest.to_str());
    }
    cout << "[" << n << " Soustractions]" << temps_cumule << " s" << endl;
    return temps_cumule;
}

float benchmark_div10(int n)
{
    clock_t temps_initial;
    clock_t temps_final;
    vector<float> temps_cpu;
    float temps_cumule = 0.0;

    for (int i = 0; i < n; i++)
    {
        //Generer deux nombres A et B 1024 bits aleatoire
        LargeInt A = rand1000();
        //Start timer
        temps_initial = clock();
        //operation a mesurer
        LargeInt result = LargeInt::div10(A, 617);
        //End timer
        temps_final = clock ();
        //sauvegarde temps
        temps_cpu.push_back((temps_final - temps_initial)* 1e-3);
        temps_cumule += temps_cpu.at(i);
    }
    cout << "[" << n << " div10]" << temps_cumule << " s" << endl;
    return temps_cumule;
}

float benchmark_mod10(int n)
{
    clock_t temps_initial;
    clock_t temps_final;
    vector<float> temps_cpu;
    float temps_cumule = 0.0;

    for (int i = 0; i < n; i++)
    {
        //Generer deux nombres A et B 1024 bits aleatoire
        LargeInt A = rand1000();
        //Start timer
        temps_initial = clock();
        //operation a mesurer
        LargeInt result = LargeInt::mod10(A, 617);
        //End timer
        temps_final = clock ();
        //sauvegarde temps
        temps_cpu.push_back((temps_final - temps_initial)* 1e-3);
        temps_cumule += temps_cpu.at(i);
    }
    cout << "[" << n << " mod10]" << temps_cumule << " s" << endl;
    return temps_cumule;
}

void save_log(string log)
{
    ofstream log_file("log.txt", ios::app);
    if(log_file)
    {
        log_file << log << endl;
        log_file.close();
    }

}

LargeInt rand617()
{
    string chaine = "";
    for(int i = 0; i < 617; i++)
    {
        chaine += to_string(rand() % 10);
    }
    return LargeInt(chaine);
}

LargeInt rand1000()
{
    string chaine = "";
    for(int i = 0; i < 1000; i++)
    {
        chaine += to_string(rand() % 10);
    }
    return LargeInt(chaine);
}

