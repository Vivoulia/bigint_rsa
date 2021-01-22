#ifndef RSA_H
#define RSA_H

#include "LargeInt.h"
#include <string>
#include <bitset>

class Rsa
{
    public:
        Rsa();
        Rsa(std::string filename);
        virtual ~Rsa();

        LargeInt p;
        LargeInt q;
        LargeInt n;
        LargeInt phi_n;
        LargeInt r;
        LargeInt inv_r;
        LargeInt v;
        LargeInt d;
        LargeInt r_mod_n;
        LargeInt r2modn;
        int k = 617;
        int e = 65537;


        int k_bit = 2047;
        std::bitset<2047> d_bit;

        std::bitset<17> e_bit;

        LargeInt chiffre(const LargeInt& M);
        LargeInt dechiffre(const LargeInt& C);

    protected:

    private:
};

#endif // RSA_H
