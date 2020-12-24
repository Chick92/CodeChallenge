#include "csvparser.h"
#include "Num.h"
#include <iostream> 
#include <vector>
#include <cstdio>

using namespace std; 


vector<double> load_coordinates_vector(){
	vector<double> coords;
	CsvParser *csvparser = CsvParser_new("coordinates.csv", ",", 0);
	CsvRow *row;

	while ((row = CsvParser_getRow(csvparser)) ) {
    	const char **rowFields = CsvParser_getFields(row);
    	coords.push_back(std::stod(rowFields[0])); // It is significantly easier to use a 1D vector
    	coords.push_back(std::stod(rowFields[1])); // and just itterate over it as n = lattitude and n+1
    	CsvParser_destroy_row(row);	
	}
	CsvParser_destroy(csvparser);
    
    return coords;
}

int main() {
    std::vector<double> coordinates = load_coordinates_vector();
    int size = coordinates.size();
    for(int i = 0; i < size/2; i=i+2){
        printf("Coordinate %i - Latitude / Longitude %f %f\n",i, coordinates[i], coordinates[i+1]);
    }
    
    Num n(4);
    Num n2(5);
    
    printf("number n = %i\n ", n.getNum());
    printf("number n2 = %i\n", n2.getNum());

    //printf("size of the vector is %i\n", size);
    
    //for (auto i = coordinates.begin(); i != coordinates.end(); ++i)
    //std::cout << *i << ' ';
    //Journey t1(10, 50, 59);
    //t1.print();   // 10:50:59
    //Journey t2;
    //t2.print(); // 06:39:09
    //t2.setTime(6, 39, 9);
    //t2.print();  // 06:39:09
   
    //if(t1.equals(t2))
      //  cout << "Two objects are equal\n";
    //else
      //  cout << "Two objects are not equal\n";	

    //return 0;
}