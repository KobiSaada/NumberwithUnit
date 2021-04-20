#include <iostream>
#include"NumberWithUnits.hpp"
#include <map>
#include <fstream>

using namespace std;


namespace ariel {

    static map<string, map<string, double> > UnitsMap;//datasructure to store the NumWithunits data 

    //read from the file and declare the proportion between the units
    void NumberWithUnits::read_units(ifstream& units_file){
        string unit1, unit2, k;
        double x, y;
        while(units_file >> x >> unit1 >> k >> y >> unit2){//while we have what to read k some string
            UnitsMap[unit1][unit2] = y;
            UnitsMap[unit2][unit1] = 1/y;
            DeepConvert(unit1,unit2);
            DeepConvert(unit2,unit1);

        }
    }
     void DeepConvert(const string unit1, const string unit2){//for deep convert for exam from "ton" to "g"
        for (auto map: UnitsMap[unit2]){
                double x = UnitsMap[unit1][unit2] * map.second;
                UnitsMap[unit1][map.first] = x;
                UnitsMap[map.first][unit1] = 1/x;
        }
    }  


//simple in&&out
    ostream& operator<<(ostream& out, const NumberWithUnits& unit){
        out << unit.number << "[" << unit.unit << "]";
        return out;
    }
    istream& operator>>(istream& in, NumberWithUnits& t){
        string s;
        in >> t.number >> s >> t.unit;
        return in;
    }
   //overloading arithmtic operators + ,+=,-=, -
    NumberWithUnits operator+(const NumberWithUnits &x){//onri
         return NumberWithUnits(x.number,x.unit); 
    }
    const NumberWithUnits operator+(const NumberWithUnits& x, const NumberWithUnits& y) {
        double t = Check_Convert_Func(y.number, y.unit, x.unit);
        return NumberWithUnits(x.number+t, x.unit);
    }
    const NumberWithUnits operator+(const NumberWithUnits& x, double a) {
        return NumberWithUnits(x.number+a, x.unit);
    }
    NumberWithUnits operator+=(NumberWithUnits& x, const NumberWithUnits& y) {
        x.number +=Check_Convert_Func(y.number, y.unit, x.unit);
        return x;
    }
    const NumberWithUnits operator-(const NumberWithUnits& x, const NumberWithUnits& y) {
        double t = Check_Convert_Func(y.number, y.unit, x.unit);
        return NumberWithUnits(x.number-t, x.unit);
    }
    const NumberWithUnits operator-(const NumberWithUnits& x) {
        return NumberWithUnits((-1)*x.number, x.unit);
    }
    NumberWithUnits operator-=(NumberWithUnits& x, const NumberWithUnits& y) {
        double t =Check_Convert_Func(y.number, y.unit, x.unit);
        x.number -=t;
        return x;
    }

     //overloading comprasion <,>,<=,>=,!=
    bool operator>(const NumberWithUnits& n1, const NumberWithUnits& n2){
        
            return n1.number >Check_Convert_Func(n2.number, n2.unit, n1.unit);
    
    }
    bool operator>=(const NumberWithUnits& x, const NumberWithUnits& y){
      
            return x.number >=Check_Convert_Func(y.number, y.unit, x.unit);
     
    }
    bool operator<(const NumberWithUnits& x, const NumberWithUnits& y){
        
            return x.number < Check_Convert_Func(y.number, y.unit, x.unit);
   
    }
    bool operator<=(const NumberWithUnits& x, const NumberWithUnits& y){
        
            return x.number <= Check_Convert_Func(y.number, y.unit, x.unit);
    
    }
    bool operator==(const NumberWithUnits& x, const NumberWithUnits& y){
        
            return x.number == Check_Convert_Func(y.number, y.unit, x.unit);
        
      
    }
    bool operator!=(const NumberWithUnits& x, const NumberWithUnits& y){
       
            return x.number != Check_Convert_Func(y.number, y.unit, x.unit);
        }

    //overload inc/dec operators ++,--
    NumberWithUnits operator++(NumberWithUnits& x) {
        NumberWithUnits t = x;
        t.number = ++x.number;
        return t;
   
 }

    NumberWithUnits operator++(NumberWithUnits& x, int) {
        NumberWithUnits t = x;
        t.number = x.number++;
        return t;
    }
    
   
    NumberWithUnits operator--(NumberWithUnits& x) {
        NumberWithUnits t = x;
        t.number = --x.number;
        return t;
    }
    
   
    NumberWithUnits operator--(NumberWithUnits& x, int) {
        NumberWithUnits t = x;
        t.number = x.number--;
        return t;
    }
    
     //overloading multipliction *,*=
    const NumberWithUnits operator*(NumberWithUnits& x, double n) {
        return NumberWithUnits(x.number*n, x.unit);
    }
    const NumberWithUnits operator*(double n ,NumberWithUnits& x) {
        return NumberWithUnits(x.number*n, x.unit);
    }
    NumberWithUnits operator*=(NumberWithUnits& x, double n) {
        x.number *= n;
        return x;
    }
    NumberWithUnits operator*=(double n, NumberWithUnits& x) {
        x.number *= n;
        return x;
    }

    double Check_Convert_Func(double x, const string Isrc ,const string Jdest){
        if(Isrc == Jdest) //if the same units return x and just do some operation
        {return x;}
        try {
            return x * UnitsMap[Isrc][Jdest];//mult by the proprtion
        }
        catch(const exception& ex) {
            throw invalid_argument{"Units not the same category the converted faild!" };
        }
    }
        
    
}