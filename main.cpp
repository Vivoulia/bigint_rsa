#include <iostream>
#include <string>
#include "LargeInt.h"
#include "Rsa.h"
#include <ctime>
#include <time.h>
#include <vector>
#include <fstream>



using namespace std;

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


    benchmark_mod10(2000);

   // LargeInt a("4320439259280043854394384724185215749617014043121956053583069354910110521930087897686954214880699127781861079392681714927097809127646849818195762273579332978298089179502487838235347910285752692409785787478420483372749541044551245805611185128588941837082731512683451837605726025272724743514315790484732647013879");
   // LargeInt b("132324761283389341084194002215078975668519400256859157264982040334961059740939613021614698223379747222083756600079268157839569913528455569682736184083845992508723353976741692130256045632959847424355650571301381751510405049722072263914344963486309696781267160573814092959220315966655838299897980514271971826055673");

    Rsa rsa_param = Rsa("key1.txt");

    /*
    LargeInt a("966008234133913716653702755834755378997244229533702325699719845132374978987699464722020797129165890323420905929504496419663760646472726793015356519166298864743542408113970050091905204974200767779543992809641252662880707448223314511994018978494506060711544016170989442964250287186911506473385732504457752282699504143207326727395259840024275761024637792966106191172796997548370201308961491099679974990281574353882361393637063784355759000760414590164883131058633846892004736745957735980274564057683133439200898665323399824424091217911980623062836243054907794465202138015239170009761205810765774066273472805285303411112254998201218210946311421478931902135569926696223228");

    LargeInt b("65582663660316546066744262796676242108981270682397674300280154867625021012300535277979202870834109676579094070495503580336239353527273206984643480833701135256457591886029949908094795025799232220456007190358747337119292551776685488005981021505493939288455983829010557035749712813088493526614267495542247717300495856792673272604740159975724238975362207033893808827203002451629798691038508900320025009718425646117638606362936215644240999239585409835116868941366153107995263254042264019725435942316866560799101334676600175575908782088019376937163756945092205534797861984760829990238794189234225933726527194714696588887745001798781789053688578521068097864430073303776772");
    LargeInt r = a + b;
    cout << r << endl;*/


    LargeInt M("13");
    LargeInt d("7");
    LargeInt test = LargeInt::mod_pow(M, d, rsa_param);
    cout << test << endl;

    /*
    LargeInt result = LargeInt::montgomery_modular(a, b, rsa_param);
    cout << "Montgomery : " << result << endl;
    cout << rsa_param.v << endl;


    LargeInt verif("596935366287768639220946238504356709185746816694260997549482635475124124333632394244105383844437314966439056681556273724428345393357430111583832669049202356493648372719672534603184924421011056889341948237994744203132919242613628846456087221313975498029820161876663805738744987137564525374587313572664983769009644621276140019562881792400201382050163189286945671732825972129747905442526044709224819238314855961153038483034965031034928377441299097857017054731934616391830891088162294628329920765906000552275793232733213999849965081499421476193176601227377629075895324845402580353371238891594363295687640639630257685567");
   // LargeInt result = a * b;
   // bool bool_verif = verif == result;
   // cout << bool_verif << endl;
   // cout << result << endl;
   // cout << verif << endl;

   LargeInt c("23410642634581528365526458955779470581962538112894779707373529603815011759548247230597659611374756519188833165371289447031627280348947666588952351816697978294273520897712631465062762112060233502757481173677840733460035234770615593094725565926671139413988218443840248675282348636268992387705584795661517969853007704360864992658872734970516424889027413351301678703750649473397359993628159004173548953545164467656512876680611400871082676693264118727510447005891538641682014725912662209695309430266964646071015765262206670200201765782068843103791478851768815600199461632385348729142192030918819301693269120842392881299887");
   LargeInt d("17112009688362409015324849585788176445107069743463909148100483556526641051264104892259123023260660740287517259381843034691356249844258845621050831039730224830980728546512569810359402016821283680035892503510894842775952076135806787413104391306295158999219888591389744189964395439633347166274588877963238729047925092433010552778804702091802647696060959546081966617653389446392921951013760964005410712552429074157968867154783115990255193210865137135200985133594915355195882258334263286931631679238556497642424148749239131493807053987217084228643666183559971018789172958756079458360272865614821967008151695455078615937336");
   bool test2 = d >= c;
   cout << test2 << endl;

    LargeInt test("322453443240905945");
    LargeInt resul_test = LargeInt::mod10(test, 10);
    cout << resul_test << endl;*/
    return 0;

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
        temps_cpu.push_back((temps_final - temps_initial)* 1e-6);
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
        temps_cpu.push_back((temps_final - temps_initial)* 1e-6);
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
        temps_cpu.push_back((temps_final - temps_initial)* 1e-6);
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
        temps_cpu.push_back((temps_final - temps_initial)* 1e-6);
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
        temps_cpu.push_back((temps_final - temps_initial)* 1e-6);
        temps_cumule += temps_cpu.at(i);
    }
    cout << "[" << n << " div10]" << temps_cumule << " s" << endl;
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

