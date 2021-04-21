#include <iostream>
#include <string>
#include <map>
#include <fstream>
//using namespace std;

namespace ariel {
    class NumberWithUnits{
        private:
        double number;
        std::string unit;//std in H file for the user
        //in&&out
        friend std::ostream& operator<<(std::ostream& OSout, const NumberWithUnits& n);
        friend std::istream& operator>>(std::istream& OSin, NumberWithUnits& n);


    public:
        NumberWithUnits(double num, std::string unit){
            this->number = num;
            this->unit = unit;


        }
       

       
        static void read_units(std::ifstream& file);

         ~NumberWithUnits(){}//discructor

        double Check_Convert_Func(double x, const std::string Isrc ,const std::string Jdest);
        void DeepConvert(const std::string &unit1,const  std::string &unit2);
        
        // declare the Increment operators ++,--//
        friend NumberWithUnits operator++(NumberWithUnits& x);
        friend  NumberWithUnits operator++(NumberWithUnits& x, int);
        friend NumberWithUnits operator--(NumberWithUnits& x);
        friend NumberWithUnits operator--(NumberWithUnits& n, int);
        friend const NumberWithUnits operator*(NumberWithUnits& x, double n);
        friend const NumberWithUnits operator*(double n, NumberWithUnits& x);
        friend  NumberWithUnits operator*=(NumberWithUnits& x, double n);
        friend  NumberWithUnits operator*=(double n, NumberWithUnits& x);

        // declare the comparison operators >,<,!=,<=,>=//
        friend bool operator>(const NumberWithUnits& x, const NumberWithUnits& y);
        friend bool operator<(const NumberWithUnits& x, const NumberWithUnits& y);
        friend bool operator>=(const NumberWithUnits& x, const NumberWithUnits& y);
        friend bool operator<=(const NumberWithUnits& x, const NumberWithUnits& y);
        friend bool operator!=(const NumberWithUnits& x, const NumberWithUnits& y);
        friend bool operator==(const NumberWithUnits& x, const NumberWithUnits& y);

        


         // declare the arithmetic operators +,-,+=,-=//
        friend const NumberWithUnits operator+(const NumberWithUnits& x, const NumberWithUnits& y);
        friend const NumberWithUnits operator+(const NumberWithUnits& x, double b);
        friend NumberWithUnits operator+(const NumberWithUnits &x);
        friend NumberWithUnits operator+=(NumberWithUnits& x, const NumberWithUnits& y);
        friend const NumberWithUnits operator-(const NumberWithUnits& x, const NumberWithUnits& y);
        friend const NumberWithUnits operator-(const NumberWithUnits& x);
        friend NumberWithUnits operator-=(NumberWithUnits& x, const NumberWithUnits& y);

    };
}