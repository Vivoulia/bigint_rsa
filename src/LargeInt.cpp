#include "LargeInt.h"
#include <string>
#include <sstream>
#include <algorithm>
#include "Rsa.h"

LargeInt:: LargeInt()
{

}

LargeInt::LargeInt(int taille)
{

    //NEW
    for (int i = 0; i < taille; i++)
    {
        this->m_value_vectorized.push_back(0);
    }

}

LargeInt::LargeInt(int taille, unsigned long int* value)
{
    //NEW
    for (int i = 0; i < taille; i++)
    {
        this->m_value_vectorized.push_back(value[i]);
    }
}


LargeInt::LargeInt(std::string number)
{
    unsigned long int round_number = 0;
    unsigned long long int power_ten = 1;
    bool finish = false;
    int i = 1;
    for (std::string::reverse_iterator it = number.rbegin(); it != number.rend(); ++it)
    {
        finish = false;
        int carac_to_int = 0;
        char carac = *it;
        std::stringstream ss;
        ss << carac;
        std::string conv = "";
        ss >> conv;
        std::istringstream ( conv ) >> carac_to_int;
        round_number += carac_to_int * power_ten;
        power_ten = power_ten * 10;
        if(i%9 == 0)
        {
            m_value_vectorized.push_back(round_number);
            power_ten = 1;
            round_number = 0;
            finish = true;
            i = 0;
        }
        i++;
    }
    if(!finish)
    {
        m_value_vectorized.push_back(round_number);
    }
}

LargeInt::LargeInt(const LargeInt& a)
{
    //NEW
    for (std::vector<unsigned long int>::const_iterator it = a.m_value_vectorized.begin() ; it != a.m_value_vectorized.end(); ++it)
    {
        m_value_vectorized.push_back(*it);
    }
}

void LargeInt::add_chunk(int n)
{
    for(int i = 0; i < n; i++)
    {
        m_value_vectorized.push_back(0);
    }
}

void LargeInt::remove_empty_chunk()
{
    int nb_empty_chunk = get_nb_empty_chunk();
    for(int i = 0; i < nb_empty_chunk; i++)
    {
        m_value_vectorized.pop_back();
    }
}

int LargeInt::get_nb_empty_chunk()
{
    int nb_empty_chunk = 0;
    for (std::vector<unsigned long int>::reverse_iterator it = m_value_vectorized.rbegin() ; it != m_value_vectorized.rend(); ++it)
    {
        if(*it != 0)
        {
            return nb_empty_chunk;
        }
        nb_empty_chunk++;
    }
    return nb_empty_chunk;
}

static LargeInt maximum(const LargeInt& a, const LargeInt& b)
{
    /*
    if(a >= b)
    {
        return a;
    }
    else
    {
        return b;
    }*/
}

static LargeInt minimum(const LargeInt& a, const LargeInt& b)
{
    /*
    if(a < b)
    {
        return a;
    }
    else
    {
        return b;
    }*/
}


LargeInt& LargeInt::operator=(const LargeInt& a)
{
    m_value_vectorized.clear();
    for (std::vector<unsigned long int>::const_iterator it = a.m_value_vectorized.begin() ; it != a.m_value_vectorized.end(); ++it)
    {
        m_value_vectorized.push_back(*it);
    }
}

LargeInt operator+(const LargeInt& a, const LargeInt& b)
{

    LargeInt result(std::max(a.getSize(), b.getSize()) + 1);
    const LargeInt* biggest;
    const LargeInt* lowest;
    if(a < b)
    {
        biggest = &b;
        lowest = &a;
    }
    else
    {
        lowest = &b;
        biggest = &a;
    }

    unsigned long long int round_result = 0;
    unsigned long long int carry = 0;

    for (int i = 0; i < biggest->getSize(); i++)
    {
        //On calcul le resultat de la somme dans une variable de taille 64 bits
        if(i < lowest->getSize())
            round_result = lowest->m_value_vectorized.at(i) + biggest->m_value_vectorized.at(i) + carry;
        else
            round_result = biggest->m_value_vectorized.at(i) + carry;

        //std::cout << biggest->m_value_vectorized.at(i) << " + " << lowest->m_value_vectorized.at(i) << " + " << carry << " = " << round_result<< std::endl;

        if( i != biggest->getSize() - 1)
        {
            if(round_result > 999999999L)
            {
                carry = round_result / LargeInt::PRIMITIVE_POW_TEN;
                round_result = round_result - carry * LargeInt::PRIMITIVE_POW_TEN;
            }
            else
            {
                carry = 0;
            }
        }
        result.m_value_vectorized.at(i) = round_result;
    }
    result.remove_empty_chunk();
    return result;
}

/*
* Réalise une soustraction entre a et b (Attention a doit être supérieur à b)
**/
LargeInt operator-(const LargeInt& a, const LargeInt& b)
{
    //On suppose que a est supérieur à b
    int taille = std::min(a.getSize(), b.getSize());
    LargeInt result(a);

    unsigned long long int round_result = 0;
    unsigned long long int carry = 0;
    unsigned long int biggest = 0;
    unsigned long int smallest = 0;

    //Pour chaque chunk
    for (int i = 0; i < taille; i++)
    {
        biggest = std::max(a.m_value_vectorized.at(i), b.m_value_vectorized.at(i));
        smallest = std::min(a.m_value_vectorized.at(i), b.m_value_vectorized.at(i));
        //Si le chunk le plus grand n'est pas a
        if(a.m_value_vectorized.at(i) < b.m_value_vectorized.at(i))
        {
            //On soustrait un chunk plus grand a un chunk plus petit (a[i] < b[i])
            //Si il reste une dizaine supérieur
            if(i < a.getSize() - 1)
            {
                result.m_value_vectorized.at(i) = LargeInt::PRIMITIVE_POW_TEN - (b.m_value_vectorized.at(i) -  a.m_value_vectorized.at(i)) - carry;
                carry = 1;
            }
            else
            {
                //Résultat négatif ...
            }
        }
        else
        {
            //On calcul le resultat de la soustraction dans une variable de taille 32 bits
            result.m_value_vectorized.at(i) = a.m_value_vectorized.at(i) - b.m_value_vectorized.at(i) - carry;
            carry = 0;
        }

    }
    result.m_value_vectorized.at(a.getSize()-1) = result.m_value_vectorized.at(a.getSize()-1) - carry;

    result.remove_empty_chunk();
    return result;
}

LargeInt operator*(const LargeInt& a, const LargeInt& b)
{
    LargeInt result(a.getSize()+b.getSize());
    unsigned long long int round_result = 0;
    for (int i = 0; i < a.getSize(); i++)
    {
        for(int j = 0; j < b.getSize(); j++)
        {
            unsigned long long int temp_a = a.m_value_vectorized.at(i);
            unsigned long long int temp_b = b.m_value_vectorized.at(j);
            unsigned long long int temp1 = result.m_value_vectorized.at(i+j);
            unsigned long long int temp2 = result.m_value_vectorized.at(i+j);
            round_result = temp_a * temp_b;
            //std::cout << round_result << " = " << temp_a << " * " << temp_b << std::endl;

            if(round_result > 999999999L)
            {
                //Partie Haute
                temp_a = result.m_value_vectorized.at(i+j+1) + (round_result / LargeInt::PRIMITIVE_POW_TEN);
                temp_b = result.m_value_vectorized.at(i+j) + (round_result % LargeInt::PRIMITIVE_POW_TEN);
                if(temp_a > 999999999L)
                {

                    bool overflow = true;
                    unsigned long long int* result_carry = new unsigned long long int[a.getSize() + b.getSize()];
                    for (int k = i+j+1; k < a.getSize() + b.getSize(); k++)
                    {
                        result_carry[k] = result.m_value_vectorized.at(k);
                    }
                    int shift = 0;
                    result_carry[i+j+1] = temp_a;
                    while(overflow)
                    {
                        unsigned long int carry = result_carry[i+j+1+shift] / LargeInt::PRIMITIVE_POW_TEN;
                        result_carry[i+j+shift+2] += carry;
                        result_carry[i+j+shift+1] = result_carry[i+j+shift+1] - carry * LargeInt::PRIMITIVE_POW_TEN;
                        if(result_carry[i+j+shift+2] > 999999999L)
                        {
                            overflow = true;
                        }
                        else
                        {
                            overflow = false;
                        }
                        shift++;
                    }
                    for (int k = i+j+1; k < i+j+2+shift; k++)
                    {
                        result.m_value_vectorized.at(k) = result_carry[k];

                    }
                    delete[] result_carry;

                }
                else
                {
                    result.m_value_vectorized.at(i+j+1) = temp_a;
                }

                //Partie basse

                if(temp_b > 999999999L)
                {
                    bool overflow = true;
                    unsigned long long int* result_carry = new unsigned long long int[a.getSize() + b.getSize()];
                    for (int k = i+j; k < a.getSize() + b.getSize(); k++)
                    {
                        result_carry[k] = result.m_value_vectorized.at(k);
                    }
                    int shift = 0;
                    result_carry[i+j] = temp_b;
                    while(overflow)
                    {
                        unsigned long int carry = result_carry[i+j+shift] / LargeInt::PRIMITIVE_POW_TEN;
                        result_carry[i+j+shift+1] += carry;
                        result_carry[i+j+shift] = result_carry[i+j+shift] - carry * LargeInt::PRIMITIVE_POW_TEN;
                        if(result_carry[i+j+shift+1] > 999999999L)
                        {
                            overflow = true;
                        }
                        else
                        {
                            overflow = false;
                        }
                        shift++;
                    }
                    for (int k = i+j; k < i+j+1+shift; k++)
                    {
                        result.m_value_vectorized.at(k) = result_carry[k];
                    }
                    delete[] result_carry;
                }
                else
                {
                    result.m_value_vectorized.at(i+j) = temp_b;
                }

            }
            else
            {
                result.m_value_vectorized.at(i+j) += round_result;
               //std::cout << "WEIRD:[" << i+j << "]"<< result.m_value_vectorized.at(i+j)<< std::endl;
            }
            //std::cout << "[chunk" << i+j << "]" << result.m_value_vectorized.at(i+j) << " = " << temp1 << " + " << (round_result % LargeInt::PRIMITIVE_POW_TEN) << std::endl;
            //std::cout << "[chunk" << i+j+1 << "]" << result.m_value_vectorized.at(i+j+1) << " = " << temp2 << " + " << (round_result / LargeInt::PRIMITIVE_POW_TEN) << std::endl;
        }
    }
    result.reformat();
    return result;
}


LargeInt operator/(const LargeInt& a, const LargeInt& b)
{
    LargeInt result();
}

 LargeInt LargeInt::add_modular(const LargeInt& a, const LargeInt& b, const LargeInt& n)
{
    LargeInt result = a + b;
    long int i = 0;
    while(result >= n)
    {
        result = result - n;
        i++;
    }
    return result;
}

LargeInt LargeInt::mult_modular(const LargeInt& A, const LargeInt& B, const LargeInt& N)
{
    LargeInt result = A*B;
    while(result >= N)
    {
        result = result - N;
    }
    return result;
}


/**
* Il faut A et B de taille 1024 bits et n impair < 2^1024
*/
LargeInt LargeInt::montgomery_modular(const LargeInt& a, const LargeInt& b, const Rsa& rsa_param)
{
    LargeInt A = LargeInt::montgomery_modular_operator(a, rsa_param.r2modn, rsa_param);
    LargeInt B = LargeInt::montgomery_modular_operator(b, rsa_param.r2modn, rsa_param);
    LargeInt C = LargeInt::montgomery_modular_operator(A, B, rsa_param);
    LargeInt one("1");
    LargeInt result = LargeInt::montgomery_modular_operator(C, one, rsa_param);
    return result;
}

LargeInt LargeInt::montgomery_modular_operator(const LargeInt& a, const LargeInt& b, const Rsa& rsa_param)
{
    LargeInt s = a * b;
    //std::cout << "s: " << s << std::endl;
    LargeInt temp = s * rsa_param.v;
    LargeInt t = LargeInt::mod10(temp, rsa_param.k);
    LargeInt m = s + t*rsa_param.n;
    //TODO: Division ...
    LargeInt u = LargeInt::div10(m, rsa_param.k);
    //std::cout << "u: " << u << std::endl;
    if(u >= rsa_param.n)
    {
        u = u-rsa_param.n;
        return u;
    }
    else
    {
        return u;
    }
}


/**
* Division de a par une puissance de 10 (keep k last digit)
*/
LargeInt LargeInt::div10(const LargeInt& a, int k)
{
    std::string chaine = a.to_str();
    std::string chaine_div10 = "";

    for (std::string::iterator it = chaine.begin(); it != chaine.end()-k; ++it)
    {
        chaine_div10 += *it;
    }
   //std::cout << chaine << std::endl;
    LargeInt result(chaine_div10);
    result.remove_empty_chunk();
    return result;

}

/**
* Modulo de a par une puissance de 10 (keep k first digit)
*/
LargeInt LargeInt::mod10(const LargeInt& a, int k)
{

    /*LargeInt r10("100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    if (a < r10)
    {
        return LargeInt(a);
    }
    else if(a == r10)
    {
        return LargeInt("0");
    }
    else
    {*/
        std::string chaine = a.to_str();
        std::string chaine_mod10 = "";
        int size_digit = 0;
        for (std::string::iterator it = chaine.begin() + (chaine.size() - k); it != chaine.end(); ++it)
        {
            chaine_mod10 += *it;
        }
        LargeInt result(chaine_mod10);
        result.remove_empty_chunk();
        return result;
   // }

}

LargeInt LargeInt::mod_pow(const LargeInt& a, const LargeInt& d, Rsa& rsa_param)
{
    LargeInt P = a;
    LargeInt i("1");
    while (i != d)
    {
        P = P * rsa_param.r_mod_n;
        P = LargeInt::montgomery_modular(P, a, rsa_param);
        i = i + LargeInt("1");
    }
    return P;
}

LargeInt LargeInt::mod_pow2(const LargeInt& a, Rsa& rsa_param)
{
    LargeInt A = LargeInt::montgomery_modular_operator(a, rsa_param.r2modn, rsa_param);
    LargeInt P("76589357365418471634473541044220529418037461887105220292626470396184988240451752769402340388625243480811166834628710552968372719651052333411047648183302021705726479102287368534937237887939766497242518826322159266539964765229384406905274434073328860586011781556159751324717651363731007612294415204338482030146992295639135007341127265029483575110972586648698321296249350526602640006371840995826451046454835532343487123319388599128917323306735881272489552994108461358317985274087337790304690569733035353928984234737793329799798234217931156896208521148231184399800538367614651270857807969081180698306730879157607118700113");
    int i = rsa_param.k_bit-1;
    while (i >= 0)
    {
        P = LargeInt::montgomery_modular_operator(P, P, rsa_param);
        if(rsa_param.d_bit[i] == 1)
        {
            P = LargeInt::montgomery_modular_operator(P, A, rsa_param);
        }
        i = i-1;

    }
    LargeInt one("1");
    P = montgomery_modular_operator(P, one, rsa_param);
    return P;

}

 bool LargeInt::operator==(const LargeInt& a) const
 {
     if(this->getSize() != a.getSize())
     {
         return false;
     }
     else
     {
         for(int i = 0; i < this->getSize(); i++)
         {
             if(this->m_value_vectorized.at(i) != a.m_value_vectorized.at(i))
             {
                 return false;
             }
         }
         return true;
     }
 }

bool LargeInt::operator<(const LargeInt& a) const
{

    if(this->getSize() < a.getSize())
    {
        //Si la taille est differente celui de plus petite taille est le plus petit
        return true;
    }
    else if (this->getSize() == a.getSize())
    {
        //Sinon on parcourt chaque bloc un par un en commençant par les blocs les plus hauts
        for (int i = this->getSize() - 1; i > -1; i--)
        {
            if(this->m_value_vectorized.at(i) < a.m_value_vectorized.at(i))
            {
                return true;
            }
            else if(this->m_value_vectorized.at(i) > a.m_value_vectorized.at(i))
            {
                return false;
            }
        }
        //Dans le cas ou ils sont égaux on retourne faux
        return false;
    }
    else
    {
        return false;
    }

}

bool LargeInt::operator>(const LargeInt& a) const
{
    if(!(*this == a) && !(*this < a))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool LargeInt::operator>=(const LargeInt& a) const
{
    if(*this == a || *this > a)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool LargeInt::operator<=(const LargeInt& a) const
{
    if(*this == a || *this < a)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool LargeInt::operator!=(const LargeInt& a) const
{
    if(*this == a)
    {
        return false;
    }
    else
    {
        return true;
    }
}

int LargeInt::count_digit_chunk(int chunk) const
{
    int nb_digit = 0;
    std::string chaine = std::to_string(m_value_vectorized.at(chunk));
    for (std::string::iterator it = chaine.begin(); it != chaine.end(); ++it)
    {
        nb_digit++;
    }
    return nb_digit;
}


static int count_digit_int(unsigned long int number)
{
    int nb_digit = 0;
    std::string chaine = std::to_string(number);
    for (std::string::iterator it = chaine.begin(); it != chaine.end(); ++it)
    {
        nb_digit++;
    }
    return nb_digit;
}


std::string LargeInt::to_str() const
{
    int i_chunk = this->m_value_vectorized.size() - 1;
    std::string largeInt_string = "";
    bool end_of_zero = true;
    for (std::vector<unsigned long int>::const_reverse_iterator it =  this->m_value_vectorized.rbegin(); it !=  this->m_value_vectorized.rend(); ++it)
    {
        if(it != m_value_vectorized.rbegin())
        {
            int nb_digit = this->count_digit_chunk(i_chunk);
            for(int i = 0; i < LargeInt::NB_DIGIT - nb_digit; i++)
            {
                largeInt_string += "0";
            }
        }

        i_chunk--;
        std::string chaine = std::to_string(*it);
        largeInt_string += chaine;
    }
    return largeInt_string;
}


/**
* Permet de reformater l'array de valeurs en array de 9 digits par case
*/
void LargeInt::reformat()
{
    this->remove_empty_chunk();
    int i = 0;
    for (std::vector<unsigned long int>::iterator it = m_value_vectorized.begin(); it != m_value_vectorized.end(); ++it)
    {
        if(this->count_digit_chunk(i) > LargeInt::NB_DIGIT)
        {
            unsigned long int carry = m_value_vectorized.at(i) / (LargeInt::PRIMITIVE_POW_TEN);
            if(i != m_value_vectorized.size() - 1)
            {
                //Si on est pas a la fin on ajoute la carry a l'élément de la dizaine supérieur
                m_value_vectorized.at(i+1) += carry;
                m_value_vectorized.at(i) -= carry*LargeInt::PRIMITIVE_POW_TEN;
            }
            else
            {
                //On rajoute une case pour la carry car il n'y a pas de dizaine supérieur
                m_value_vectorized.push_back(carry);
            }
        }
        i++;
    }
}

std::ostream& operator<<(std::ostream& os, const LargeInt& largeInt)
{
    /*
    int i_chunk = largeInt.m_value_vectorized.size() - 1;
    for (std::vector<unsigned long int>::const_reverse_iterator it = largeInt.m_value_vectorized.rbegin(); it != largeInt.m_value_vectorized.rend(); ++it)
    {

        std::string chaine = std::to_string(*it);
        int nb_digit = largeInt.count_digit_chunk(i_chunk);
        for(int i = 0; i < LargeInt::NB_DIGIT - nb_digit; i++)
        {
            os << "0";
        }
        i_chunk--;
        os << chaine << "|";
    }*/
    os << largeInt.to_str();
    return os;
}





LargeInt::~LargeInt()
{
    //dtor
}
