#include <iostream>
#include"NumberWithUnits.hpp"
#include <map>
#include <fstream>




using namespace std;

namespace ariel {

    static map<string, map<string, double> > table;

    /**
     * @brief convert val of unit1 to unit2
     *        For Example:
     *              convert from 3[km] to 3000[m],
     *              convert from 30[sec] to 0.5[min],
     *              convert from 3.7[ton] to 3700[kg]. etc.
     * 
     * @param val   A given value of unit1 to be converted to unit2.
     * @param from  source unit
     * @param to    destination unit
     * @return      double The converted value
     */
    double convertFromTo(double val, const string from, const string to){
        if(from == to) {return val;}
        try {
            return val * table.at(from).at(to);
        }
        catch(const exception& e) {
            throw invalid_argument{"Units do not match - ["+from+"] cannot be converted to ["+to+"]"};
        }
    }

    /**
     * @brief Read a text file with each line in the format:
     *          "1 <unit1> = <ratio> <unit2>"
     *        For example:
     *          "1 km = 1000 m"
     *        And build a table of units ratios.
     * 
     * @param units_file A file stream contains the units as described above.
     */
    void NumberWithUnits::read_units(ifstream& units_file){
        string buf, u1, u2, t;
        double n1, n2;
        while(units_file >> n1 >> u1 >> t >> n2 >> u2){
            table[u1][u2] = n2/n1;
            table[u2][u1] = n1/n2;
        }
    }

    //=============================================================================================
    /* Overloading the in\out stream operators: {<<, >>} */
    //=============================================================================================
    ostream& operator<<(ostream& out, const NumberWithUnits& t){
        out << t.number << "[" << t.unit << "]";
        return out;
    }
    istream& operator>>(istream& in, NumberWithUnits& t){
        string s;
        in >> t.number >> s >> t.unit;
        return in;
    }
    //=============================================================================================
    /* Overloading the arithmetic operators: {+, +=, -, -=} */
    //=============================================================================================
    const NumberWithUnits operator+(const NumberWithUnits& n1, const NumberWithUnits& n2) {
        double temp = convertFromTo(n2.number, n2.unit, n1.unit);
        return NumberWithUnits(n1.number+temp, n1.unit);
    }
    const NumberWithUnits operator+(const NumberWithUnits& n, double a) {
        return NumberWithUnits(n.number+a, n.unit);
    }
    NumberWithUnits operator+=(NumberWithUnits& n1, const NumberWithUnits& n2) {
        n1.number += convertFromTo(n2.number, n2.unit, n1.unit);
        return n1;
    }
    const NumberWithUnits operator-(const NumberWithUnits& n1, const NumberWithUnits& n2) {
        double temp = convertFromTo(n2.number, n2.unit, n1.unit);
        return NumberWithUnits(n1.number-temp, n1.unit);
    }
    const NumberWithUnits operator-(const NumberWithUnits& n) {
        return NumberWithUnits(-n.number, n.unit);
    }
    NumberWithUnits operator-=(NumberWithUnits& n1, const NumberWithUnits& n2) {
        n1.number -= convertFromTo(n2.number, n2.unit, n1.unit);
        return n1;
    }

    //=============================================================================================
    /* Overloading the Increament\Decreament operators: {++x, x++, --x, x--} */
    //=============================================================================================
    NumberWithUnits operator++(NumberWithUnits& n) {
        NumberWithUnits temp = n;
        temp.number = ++n.number;
        return temp;
    }
    NumberWithUnits operator++(NumberWithUnits& n, int) {
        NumberWithUnits temp = n;
        temp.number = n.number++;
        return temp;
    }
    NumberWithUnits operator--(NumberWithUnits& n) {
        NumberWithUnits temp = n;
        temp.number = --n.number;
        return temp;
    }
    NumberWithUnits operator--(NumberWithUnits& n, int) {
        NumberWithUnits temp = n;
        temp.number = n.number--;
        return temp;
    }
    //=============================================================================================
    /* Overloading the Multiplication operator: {number*x, x*number, x*=number, number*=x} */
    //=============================================================================================
    const NumberWithUnits operator*(NumberWithUnits& n, double num) {
        return NumberWithUnits(n.number*num, n.unit);
    }
    const NumberWithUnits operator*(double num, NumberWithUnits& n) {
        return NumberWithUnits(n.number*num, n.unit);
    }
    NumberWithUnits operator*=(NumberWithUnits& n, double num) {
        n.number *= num;
        return n;
    }
    NumberWithUnits operator*=(double num, NumberWithUnits& n) {
        n.number *= num;
        return n;
    }
    //=============================================================================================
    /* Overloading the comparison operators: {>, >=, <, <=, ==, !=} */
    //=============================================================================================
    bool operator>(const NumberWithUnits& n1, const NumberWithUnits& n2){
        try{
            return n1.number > convertFromTo(n2.number, n2.unit, n1.unit);
        }
        catch(const exception& e){
            return false;
        }
    }
    bool operator>=(const NumberWithUnits& n1, const NumberWithUnits& n2){
        try{
            return n1.number >= convertFromTo(n2.number, n2.unit, n1.unit);
        }
        catch(const exception& e){
            return false;
        }
    }
    bool operator<(const NumberWithUnits& n1, const NumberWithUnits& n2){
        try{
            return n1.number < convertFromTo(n2.number, n2.unit, n1.unit);
        }
        catch(const exception& e){
            return false;
        }
    }
    bool operator<=(const NumberWithUnits& n1, const NumberWithUnits& n2){
        try{
            return n1.number <= convertFromTo(n2.number, n2.unit, n1.unit);
        }
        catch(const exception& e){
            return false;
        }
    }
    bool operator==(const NumberWithUnits& n1, const NumberWithUnits& n2){
        try{
            return n1.number == convertFromTo(n2.number, n2.unit, n1.unit);
        }
        catch(const exception& e){
            return false;
        }
    }
    bool operator!=(const NumberWithUnits& n1, const NumberWithUnits& n2){
        try{
            return n1.number != convertFromTo(n2.number, n2.unit, n1.unit);
        }
        catch(const exception& e){
            return false;
        }
    }
}