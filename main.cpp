#include "csvparser.h"
#include <iostream> 
#include <vector>
#include <cstdio>
using namespace std; 


double** load_coordinates(){
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
    
    double** array2D = 0;
    array2D = new double*[i];
    for (int h = 0; h < i; h++){
        array2D[h] = new double[2];
        for (int w = 0; w < 2; w++){
            array2D[h][w] = coords[w + 2 * h];
        }
    }
    return array2D;
}





int main() {
	double** a = load_coordinates();
    int height = 81;
    int width = 2;
    
    for (int h = 0; h < height; h++){
        for (int w = 0; w < width; w++){
            printf("%f,", a[h][w]);
        }
            printf("\n");
    }

          // important: clean up memory
          printf("\n");
          printf("Cleaning up memory...\n");
          for (int h = 0; h < height; h++)
          {
            delete [] a[h];
          }
          delete [] a;
          a = 0;
          printf("Ready.\n");

  return 0;
}