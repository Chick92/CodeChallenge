// A2DD.h
#ifndef A2DD_H
#define A2DD_H

class A2DD
{
  int gx;
  int gy;

public:
  A2DD(int x,int y);
  int getSum();

};

#endif

// A2DD.cpp
#include "A2DD.h"

A2DD::A2DD(int x,int y)
{
  gx = x;
  gy = y;
}

int A2DD::getSum()
{
  return gx + gy;
}


#include "csvparser.h"

float gps_coords::load_coordinates(){
	int i =  0;
	CsvParser *csvparser = CsvParser_new("coordinates.csv", ",", 0);
	CsvRow *row;

	while ((row = CsvParser_getRow(csvparser)) ) {
		printf("==NEW LINE==\n");
    	const char **rowFields = CsvParser_getFields(row);
    	for (i = 0 ; i < CsvParser_getNumFields(row) ; i++) {
        	printf("FIELD: %s\n", rowFields[i]);
        	printf("%i\n", i);
    	}
		printf("\n");
    	CsvParser_destroy_row(row);
	}
	CsvParser_destroy(csvparser);

    	return 0.0;
}



//g++ main.cpp -I CsvParser/include CsvParser/src/csvparser.c -o test