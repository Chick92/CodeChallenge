#ifndef JOURNEY_H
#define JOURNEY_H
 
#include <vector>
#include <string>

class Journey
{
private:
    std::vector<double> journey_coordinates;
    std::string journey_name;
    std::vector<double> utm_coords_vec; 
    double distance = 0.0;
    double min_speed = 100000.0;
    double max_speed = 1.0;
public:
    //double distance = 0.0;
    Journey(std::vector<double> coordinates, std::string name);
    void SetCoordinates(std::vector<double> coordinates, std::string name);
    void PrintCoordinates();
 
    std::vector<double> returnCoordinates(){ 
        return journey_coordinates;
    }
    
    double CalculateTotalDistanceTravelled();
    double ReturnDistanceBetweenPoints(double lat1, double lon1, double lat2, double lon2);
    double MercatorGetX(double lon, int width);
    double MercatorGetY(double lat, int height, int width);
    void DrawMap();
};
 
#endif