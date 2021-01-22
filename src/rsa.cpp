#include "Rsa.h"
#include <fstream>

Rsa::Rsa()
{
    //ctor
}

Rsa::Rsa(std::string filename)
{
    std::string line;
    std::ifstream key_file;
    key_file.open(filename);

    if(key_file.is_open())
    {
        int i = 0;
        while(getline(key_file, line))
        {
            switch (i)
            {
                case 0:
                    //p
                    p = LargeInt(line);
                break;

                case 1:
                    //q
                    q = LargeInt(line);
                break;

                case 2:
                    //n
                    n = LargeInt(line);
                break;

                case 3:
                    //phi(n)
                    phi_n = LargeInt(line);
                break;

                case 4:
                    //R
                    r = LargeInt(line);
                break;

                case 5:
                    //modular_inv(R)
                    inv_r = LargeInt(line);
                break;
                case 6:
                    v = LargeInt(line);
                break;
                case 7:
                    d = LargeInt(line);
                break;
                case 8:
                    d_bit = std::bitset<2047>(line);
                    //std::cout << d_bit[1] << std::endl;
                break;
                case 9:
                    r2modn = LargeInt(line);
                    //std::cout << r2modn << std::endl;
                break;
                case 10:
                    e_bit = std::bitset<17>(line);
                    std::cout << e_bit << std::endl;
                break;
            }
            i++;
        }
        key_file.close();
    }
    else
    {
        std::cout << "Error while opening key file" << std::endl;
    }

    r_mod_n = LargeInt("6357429461673886537894164176882117672149847548420881170505881584739952961807011077609361554500973923244667338514842211873490878604209333644190592733208086822905916409149474139748951551759065988970075305288637066159859060917537627621097736293315442344047126224639005298870605454924030449177660817353928120587969182556540029364509060117934300443890346594793285184997402106410560025487363983305804185819342129373948493277554396515669293226943525089958211976433845433271941096349351161218762278932141415715936938951173319199192936871724627584834084592924737599202153470458605083431231876324722793226923516630428474800452");
}

LargeInt Rsa::chiffre(const LargeInt& M)
{
    LargeInt A = LargeInt::montgomery_modular_operator(M, this->r2modn, *this);
    LargeInt P("76589357365418471634473541044220529418037461887105220292626470396184988240451752769402340388625243480811166834628710552968372719651052333411047648183302021705726479102287368534937237887939766497242518826322159266539964765229384406905274434073328860586011781556159751324717651363731007612294415204338482030146992295639135007341127265029483575110972586648698321296249350526602640006371840995826451046454835532343487123319388599128917323306735881272489552994108461358317985274087337790304690569733035353928984234737793329799798234217931156896208521148231184399800538367614651270857807969081180698306730879157607118700113");
    int i = 17-1;
    while (i >= 0)
    {
        P = LargeInt::montgomery_modular_operator(P, P, *this);
        if(this->e_bit[i] == 1)
        {
            P = LargeInt::montgomery_modular_operator(P, A, *this);
        }
        i = i-1;

    }
    LargeInt one("1");
    P = LargeInt::montgomery_modular_operator(P, one, *this);
    return P;
}

LargeInt Rsa::dechiffre(const LargeInt& C)
{
    LargeInt A = LargeInt::montgomery_modular_operator(C, this->r2modn, *this);
    LargeInt P("76589357365418471634473541044220529418037461887105220292626470396184988240451752769402340388625243480811166834628710552968372719651052333411047648183302021705726479102287368534937237887939766497242518826322159266539964765229384406905274434073328860586011781556159751324717651363731007612294415204338482030146992295639135007341127265029483575110972586648698321296249350526602640006371840995826451046454835532343487123319388599128917323306735881272489552994108461358317985274087337790304690569733035353928984234737793329799798234217931156896208521148231184399800538367614651270857807969081180698306730879157607118700113");
    int i = this->k_bit - 1;
    while (i >= 0)
    {
        P = LargeInt::montgomery_modular_operator(P, P, *this);
        if(this->d_bit[i] == 1)
        {
            P = LargeInt::montgomery_modular_operator(P, A, *this);
        }
        i = i-1;

    }
    LargeInt one("1");
    P = LargeInt::montgomery_modular_operator(P, one, *this);
    return P;
}


Rsa::~Rsa()
{
    //dtor
}
