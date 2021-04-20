#include "doctest.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "NumberWithUnits.hpp"



using namespace ariel;
using namespace std;

ifstream units_file{"units.txt"};


TEST_CASE("Adding units"){// NumberWithUnits+NumberWithUnits
    NumberWithUnits::read_units(units_file);

    NumberWithUnits Unita{5, "km"};
    NumberWithUnits Unitb{7, "m"};
    NumberWithUnits Unitc{2, "hour"};
    NumberWithUnits Unitd{1, "g"};
    NumberWithUnits Unite{1, "ton"};
    CHECK_EQ(Unitd+Unite , NumberWithUnits{1000001,"g"});
    CHECK_EQ(Unita+Unitb , NumberWithUnits{5.007, "km"});
    CHECK_EQ(Unitb+Unita , NumberWithUnits{5007, "m"});
    CHECK_THROWS(Unita+Unitc);
    CHECK_THROWS_MESSAGE(Unitc+Unite,"error to covert ");
    CHECK_THROWS(Unitc+Unita);
}


TEST_CASE("increase"){//x++,++x
    NumberWithUnits::read_units(units_file);
    NumberWithUnits Unita{4, "km"};
     CHECK(Unita++ == NumberWithUnits{4, "km"});
     CHECK(Unita == NumberWithUnits{5, "km"});
     CHECK(++Unita == NumberWithUnits{6, "km"});
     CHECK(Unita == NumberWithUnits{6, "km"});

}


TEST_CASE("decrease"){//--x,x--
    NumberWithUnits::read_units(units_file);
    NumberWithUnits Unita{4, "km"};
    NumberWithUnits Unitb{61, "min"};
    CHECK(Unitb-- == NumberWithUnits{61, "min"});
    CHECK(Unita-- == NumberWithUnits{4, "km"});
    CHECK(Unita == NumberWithUnits{3, "km"});
    CHECK(--Unita == NumberWithUnits{1, "km"});
    CHECK(Unita == NumberWithUnits{1, "km"});
}

TEST_CASE("comparision increase operators"){//x+=y,y+=x
      NumberWithUnits::read_units(units_file);
      NumberWithUnits Unita{5, "km"};
      NumberWithUnits Unitb{4000, "m"};
       NumberWithUnits Unitc{2000, "kg"};
      NumberWithUnits Unitd{1, "g"};
       CHECK((Unitc+=Unitd) == NumberWithUnits{20001, "kg"});
      CHECK((Unita+=Unitb) == NumberWithUnits{9, "km"});
    CHECK(Unita == NumberWithUnits{9, "km"});
    CHECK((Unitb+=Unita) == NumberWithUnits{13000, "m"});
    CHECK(Unitb== NumberWithUnits{13000, "m"});
}
TEST_CASE("comparision decrease operators"){//x-=y,y-=x
      NumberWithUnits::read_units(units_file);
      NumberWithUnits Unita{5, "km"};
      NumberWithUnits Unitb{2000, "m"};
      NumberWithUnits Unitc{2000, "kg"};
      NumberWithUnits Unitd{1, "g"};
    CHECK((Unitc-=Unitd) == NumberWithUnits{1999, "kg"});
    CHECK((Unita-=Unitb) == NumberWithUnits{3, "km"});
    CHECK(Unita == NumberWithUnits{3, "km"});
    CHECK((Unitb-=Unita) == NumberWithUnits{-28000, "m"});
    CHECK(Unitb== NumberWithUnits{-28000, "m"});
}




TEST_CASE("Multiplication"){ //double*x, x*double, x*=double, double*=x
    NumberWithUnits::read_units(units_file);
    NumberWithUnits Unita{4, "km"};

    CHECK((Unita*0.5) == NumberWithUnits{2, "km"});
    CHECK((3*Unita) == NumberWithUnits{12, "km"});
    CHECK((Unita*=6.5) == NumberWithUnits{26, "km"});
    CHECK((Unita*=3.2) == NumberWithUnits{12.8, "km"});
    CHECK(Unita== NumberWithUnits{12.8, "km"});
   // CHECK_FALSE(Unita>=NumberWithUnits(12.9,"km"));
}

TEST_CASE("Comparison operators"){//{>, <, >=, <=, ==, !=}
    NumberWithUnits::read_units(units_file);

    
    CHECK_GT(NumberWithUnits{7000, "m"}, NumberWithUnits{6, "km"});
    CHECK_GT(NumberWithUnits{7000, "ton"}, NumberWithUnits{6, "k"});
    CHECK_NE(NumberWithUnits{2, "km"}  , NumberWithUnits{2500, "m"});
    CHECK_NE(NumberWithUnits{21, "ton"}  , NumberWithUnits{2500, "m"});
    CHECK_NE(NumberWithUnits{2500, "m"}, NumberWithUnits{2, "km"});
    CHECK_LT(NumberWithUnits{1, "km"}  , NumberWithUnits{7000, "m"});
    CHECK_LT(NumberWithUnits{2, "k"}  , NumberWithUnits{70, "ton"});
    CHECK_GT(NumberWithUnits{3200, "m"}, NumberWithUnits{10, "cm"});
    CHECK_NE(NumberWithUnits{20, "cm"} , NumberWithUnits{3200, "m"});
    CHECK_LT(NumberWithUnits{20, "cm"} , NumberWithUnits{3200, "km"});
    CHECK_NE(NumberWithUnits{3100, "m"}, NumberWithUnits{50, "cm"});

    CHECK_FALSE(NumberWithUnits(2,"hour")>=NumberWithUnits(130,"min"));
    CHECK_FALSE(NumberWithUnits(2,"km")>=NumberWithUnits(13000,"m"));


    CHECK_EQ(NumberWithUnits{300, "cm"}, NumberWithUnits{3, "m"});
    CHECK_EQ(NumberWithUnits{3, "m"}, NumberWithUnits{300, "cm"});
    CHECK_EQ(NumberWithUnits{3, "km"}, NumberWithUnits{3000, "m"});
}