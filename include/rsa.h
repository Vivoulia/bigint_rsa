#ifndef RSA_H
#define RSA_H

#include "LargeInt.h"
#include <string>

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
        int k = 617;
        int e = 7;

        LargeInt chiffre(int m);
        int dechiffre(LargeInt& c);

    protected:

    private:
};

#endif // RSA_H
