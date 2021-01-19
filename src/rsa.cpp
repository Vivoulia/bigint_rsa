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


Rsa::~Rsa()
{
    //dtor
}
