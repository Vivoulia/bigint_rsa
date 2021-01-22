#ifndef LARGEINT_H
#define LARGEINT_H


#include <iostream>
#include <vector>

class Rsa;

class LargeInt
{
    public:
        LargeInt();
        LargeInt(int taille);
        LargeInt(int taille, unsigned long int* value);
        LargeInt(std::string number);
        LargeInt(const LargeInt& a);

        //Usefull function

        /**
            Add n chunk of 32 bits initialized to 0 to the LargeInt
        */
        void add_chunk(int n);

        /**
            Delete null chunk starting from the higher values until one is not 0
        */
        void remove_empty_chunk();
        int  get_nb_empty_chunk();
        int count_digit_chunk(int chunk) const;
        std::string to_str() const;
        //Reformat to create array of 9 digit
        void reformat();

        static LargeInt maximum(const LargeInt& a, const LargeInt& b);
        static LargeInt minimum(const LargeInt& a, const LargeInt& b);
        static int count_digit_int(unsigned long int number);

        unsigned int getSize() const {return m_value_vectorized.size();}

        //Surcharge opérateur

        LargeInt& operator=(const LargeInt& a);
        bool operator<(const LargeInt& a) const;
        bool operator>(const LargeInt& a) const;
        bool operator==(const LargeInt& a) const;
        bool operator!=(const LargeInt& a) const;
        bool operator>=(const LargeInt& a) const;
        bool operator<=(const LargeInt& a) const;

        friend LargeInt operator+(const LargeInt& a, const LargeInt& b);
        friend LargeInt operator-(const LargeInt& a, const LargeInt& b);
        friend LargeInt operator*(const LargeInt& a, const LargeInt& b);
        friend LargeInt operator/(const LargeInt& a, const LargeInt& b);
        friend std::ostream& operator<<(std::ostream& os, const LargeInt& largeInt);
        static LargeInt add_modular(const LargeInt& a, const LargeInt& b, const LargeInt& n);
        static LargeInt mult_modular(const LargeInt& a, const LargeInt& b, const LargeInt& n);
        static LargeInt montgomery_modular(const LargeInt& a, const LargeInt& b, const Rsa& rsa_param);
        static LargeInt montgomery_modular_operator(const LargeInt& a, const LargeInt& b, const Rsa& rsa_param);
        static LargeInt div10(const LargeInt& a, int k);
        static LargeInt mod10(const LargeInt& a, int k);
        static LargeInt mod_pow(const LargeInt& a, const LargeInt& d, Rsa& rsa_param);
        static LargeInt mod_pow2(const LargeInt& a, Rsa& rsa_param);
        virtual ~LargeInt();

        //Valeur max pour un unsigned long int: 4 294 967 295
        static const unsigned long  int MAX_VALUE = 0xFFFFFFFFL;
        static const int NB_DIGIT = 9;
        //Pre-computed 10^9
        static const unsigned long int PRIMITIVE_POW_TEN = 1000000000L;
        //Pre-computed R
        static const unsigned long long int UPPER_BITS = 0xFFFFFFFF00000000LL;
        static const unsigned long long int LOWER_BITS = 0XFFFFFFFFL;

    protected:
        //Chunks of 32 bits
        std::vector<unsigned long int> m_value_vectorized;



    private:
};

#endif // LARGEINT_H
