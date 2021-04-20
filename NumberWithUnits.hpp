#include <iostream>
#include <string>
#include <map>
//using namespace std;

namespace ariel {
    class NumberWithUnits{

    
        double number;
        std::string unit;//std in H file  for the user

        friend std::ostream& operator<<(std::ostream& OSout, const NumberWithUnits& n);
        friend std::istream& operator>>(std::istream& OSin, NumberWithUnits& n);


    public:
        NumberWithUnits(double num, std::string unit){
            this->number = num;
            this->unit = unit;
        }
       

       
        static void read_units(std::ifstream& file);

         ~NumberWithUnits(){}//discructor

        
       
       
        // declare the Increment operators  //
        friend NumberWithUnits operator++(NumberWithUnits& n);
        friend  NumberWithUnits operator++(NumberWithUnits& n, int);
        friend NumberWithUnits operator--(NumberWithUnits& n);
        friend NumberWithUnits operator--(NumberWithUnits& n, int);
        friend const NumberWithUnits operator*(NumberWithUnits& n, double num);
        friend const NumberWithUnits operator*(double num, NumberWithUnits& n);
        friend  NumberWithUnits operator*=(NumberWithUnits& n, double num);
        friend  NumberWithUnits operator*=(double num, NumberWithUnits& n);

        // declare the comparison operators //
        friend bool operator>(const NumberWithUnits& n, const NumberWithUnits& n2);
        friend bool operator<(const NumberWithUnits& n, const NumberWithUnits& n2);
        friend bool operator>=(const NumberWithUnits& n, const NumberWithUnits& n2);
        friend bool operator<=(const NumberWithUnits& n, const NumberWithUnits& n2);
        friend bool operator!=(const NumberWithUnits& n, const NumberWithUnits& n2);
        friend bool operator==(const NumberWithUnits& n, const NumberWithUnits& n2);

        


         // declare the arithmetic operators //
        friend const NumberWithUnits operator+(const NumberWithUnits& n, const NumberWithUnits& n2);
        friend const NumberWithUnits operator+(const NumberWithUnits& n, double a);
        friend NumberWithUnits operator+=(NumberWithUnits& n, const NumberWithUnits& n2);
        friend const NumberWithUnits operator-(const NumberWithUnits& n, const NumberWithUnits& n2);
        friend const NumberWithUnits operator-(const NumberWithUnits& n);
        friend NumberWithUnits operator-=(NumberWithUnits& n, const NumberWithUnits& n2);

    };
}