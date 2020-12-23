#include "csvparser.h"
#include <iostream> 
#include <vector>

using namespace std; 


double load_coordinates(){
	int i =  0;
	vector<double> coords;
	



	CsvParser *csvparser = CsvParser_new("coordinates.csv", ",", 0);
	CsvRow *row;

	while ((row = CsvParser_getRow(csvparser)) ) {
    	const char **rowFields = CsvParser_getFields(row);
    	coords.push_back(std::stod(rowFields[0])); // It is significantly easier to use a 1D vector
    	coords.push_back(std::stod(rowFields[1])); // and just itterate over it as n = lattitude and n+1
    	CsvParser_destroy_row(row);	
    	i++;				// = longitude
	}
	CsvParser_destroy(csvparser);
	double coordinates[i][2];

	for(int j = 0; j<i;, j++){
		coordinates[j][0] = coords[j*2] // this maths is wrong
		coordinates[j][1] = coords[j*2+1]
	}

    //cout << "vector elements are: ";
    //for (int i = 0; i < lattitude.size(); ++i) {
    //    cout << lattitude[i] << ' ';
    //}
    //cout << endl;

    	return coordinates;
}



//std::string  s  = "0.6"
//std::wstring ws = "0.7"
//double d  = std::stod(s);
//double dw = std::stod(ws);



int main() {
	double a;
	a = load_coordinates();

  return 0;
}