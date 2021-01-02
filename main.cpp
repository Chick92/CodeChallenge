#include "csvparser.h"
#include "Journey.h"
#include <iostream> 
#include <vector>
#include <cstdio>
#include <string>


//top left lat/lon: 53.491721 -2.359734 UTM: 57.733086 65.345893 
//top right lat/lon: 53.491721 -2.357919 UTM: 57.733676 65.345893
//bottom left lat/lon: 53.490108 -2.359734 UTM: 57.733086 65.346774
//bottom right lat/lon: 53.490108 -2.357919 UTM: 57.733676 65.346774 
// Map width/height pixel: 828x1228 width/height m: 117.0x172.8
// map width in UTM 0.00059
// map height in UTM 0.000881
// pixel width = 0.00000071
// pixel height = 0.00000071

//g++ main.cpp Journey.cpp -I CsvParser/include CsvParser/src/csvparser.c -o MapJourney `pkg-config --cflags --libs opencv`
//you must use g++ version => 8


std::vector<double> load_coordinates_vector(){
	std::vector<double> coords;
	CsvParser *csvparser = CsvParser_new("coordinates.csv", ",", 0);
	CsvRow *row;

	while ((row = CsvParser_getRow(csvparser)) ) {
    	const char **rowFields = CsvParser_getFields(row);
    	coords.push_back(std::stod(rowFields[0])); // It is significantly easier to use a 1D vector
    	coords.push_back(std::stod(rowFields[1])); // and just itterate over it as n = lattitude and n+1
        coords.push_back(std::stod(rowFields[2]));
    	CsvParser_destroy_row(row);	
	}
	CsvParser_destroy(csvparser);
    
    return coords;
}

int main() {
    double distance;
    
    std::vector<double> coordinates = load_coordinates_vector();
    std::string name = "MapBase.jpeg";
    
    
    Journey j1(coordinates, name);
    j1.PrintCoordinates();
    distance = j1.CalculateTotalDistanceTravelled();
    j1.DrawMap();^
    return 0; 
}



