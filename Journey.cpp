#include "Journey.h"
#include <iostream> 
#include <vector>
#include <cstdio>
#include <math.h>
#include <opencv2/opencv.hpp> //Include file for every supported OpenCV function. Hint: Slow to compile.
#include <string>

using namespace cv;  // optional 
//using namespace std; 

 
// Journey constructor
Journey::Journey(std::vector<double> coordinates, std::string name)
{
    SetCoordinates(coordinates, name);
    
}


void Journey::SetCoordinates(std::vector<double> coordinates, std::string name)
{
    journey_coordinates = coordinates;
    journey_name = name;
}


void Journey::PrintCoordinates(){
    int size = journey_coordinates.size();
    printf("size of array %i\n", size);
    for(int i = 0; i < size; i=i+3){
        printf("Coordinate # %i - Latitude %f, Longitude %f, Time since midnight %f\n",i, journey_coordinates[i], journey_coordinates[i+1], journey_coordinates[i+2]);
    }
}

double Journey::CalculateTotalDistanceTravelled(){
    
    double width = 117.0;
    double height = 172.8;
    double lat1,lon1,lat2,lon2,time1,time2,speed;
    int size = journey_coordinates.size();
    double coordinates[size/2][3];
    
    for(int i = 0; i< (size/3); i++){ // puts lat and long into a 2d array to make manipulating it a bit easier
        coordinates[i][0] = journey_coordinates[i*3];
        coordinates[i][1] = journey_coordinates[i*3+1];
        coordinates[i][2] = journey_coordinates[i*3+2];
    }   
    for(int i = 0; i< (size/3)-3; i++){    
        
        lat1 = coordinates[i][0];
        lon1 = coordinates[i][1];
        lat2 = coordinates[i+1][0];
        lon2 = coordinates[i+1][1];
        time1 = coordinates[i][2];
        time2 = coordinates[i+1][2];
        //printf("i, lat1, lon1, lat2, lon2, %i %f %f %f %f \n", i, lat1, lon1, lat2, lon2);

        speed = ReturnDistanceBetweenPoints(lat1,lon1,lat2,lon2) / (time2 - time1);
        distance = distance + ReturnDistanceBetweenPoints(lat1,lon1,lat2,lon2);
        printf("speed = %f mercator X/Y = %f %f \n ", speed, MercatorGetX(lon1, width), MercatorGetY(lat1, height, width));
        //cna't index an array of unknown size as a class member - so using vector instead
        utm_coords_vec.push_back(MercatorGetX(lon1, width));
        utm_coords_vec.push_back(MercatorGetY(lat1, height, width));
        utm_coords_vec.push_back(speed);
        if (speed < min_speed){
            min_speed = speed;
        }
        if (speed > max_speed){
            max_speed = speed;
        }
        
    }
    utm_coords_vec.push_back(MercatorGetX(lon2, width));
    utm_coords_vec.push_back(MercatorGetY(lat2, height, width));
    utm_coords_vec.push_back(speed);
    
    printf("total distance travelled = %f\n ", distance);
    //printf("Top left %f %f \n", MercatorGetX(-2.359734, width), MercatorGetY(53.491721, height,width));
    //printf("Top right %f %f \n", MercatorGetX(-2.357919, width), MercatorGetY(53.491721, height, width));
    //printf("Bottom left %f %f \n", MercatorGetX(-2.359734, width), MercatorGetY(53.490108, height, width));
    //printf("Bottom right %f %f \n", MercatorGetX(-2.357919, width), MercatorGetY(53.490108, height, width));
    return distance;
}

double Journey::ReturnDistanceBetweenPoints(double lat1, double lon1, double lat2, double lon2){
    
    int R = 6371000; // metres
    double lattitude1 = lat1 * M_PI/180; // φ, λ in radians
    double lattitude2 = lat2 * M_PI/180;
    double delta_lat = (lat2-lat1) * M_PI/180;
    double delta_lon = (lon2-lon1) * M_PI/180;

    double a = sin(delta_lat/2) * sin(delta_lat/2) + cos(lattitude1) * cos(lattitude2) * sin(delta_lon/2) * sin(delta_lon/2);
    double c = 2 * atan2(sqrt(a),sqrt(1-a));

    double d = R * c; // in metres
    return d;
}

//https://mathworld.wolfram.com/MercatorProjection.html
//https://stackoverflow.com/questions/16080225/convert-lat-long-to-x-y-coordinates-c
double Journey::MercatorGetX(double lon, int width){
    // width is map width
    double x = fmod((width*(180+lon)/360), (width +(width/2)));

    return x;
}

double Journey::MercatorGetY(double lat, int height, int width){
    // height and width are map height and width
    double latRad = lat*M_PI/180;

    // get y value
    double mercN = log(tan((M_PI/4)+(latRad/2)));
    double y = (height/2)-(width*mercN/(2*M_PI));
    return y;
}

void Journey::DrawMap(){
    cv::Mat image;
    int x=0, y=0;
    int X,Y;
    int size = (journey_coordinates.size()/3); 
    int colour;
    // place an image in the working folder
    image = cv::imread(journey_name, IMREAD_COLOR);
    
    double originX = 57.733086;
    double originY = 65.345893;
    
    
    //for (int i = 0: i < size; i++){
      //  utm_coords[i][0] = utm_coords_vec[i*3];   
        //utm_coords[i][1] = utm_coords_vec[i*3+1];
       // utm_coords[i][2] = utm_coords_vec[i*3+2];      
    //}


    for (int i = 0; i < (size-3); i++){ // use journey coordinates size as utm_coords doesnt have defined size - gives compiler error
        X = int((utm_coords_vec[i*3] - originX) / 0.00000071);
        Y = int((utm_coords_vec[i*3+1] - originY) / 0.00000071);   
        colour = int( (utm_coords_vec[i*3+2] - min_speed)*(255/(max_speed-min_speed)) );
        printf("size, i, X and Y %i %i %i %i\n", size, i, X,Y);
        for (x=X; x<X+7; x++) { //x=190, y = 170 for start
            for (y=Y; y<Y+7; y++ ){
                cv::Vec3b color = image.at<Vec3b>(Point(x,y)); // get the pixel
                color[0]=0;
                color[1]=colour;
                color[2] =(255-colour);
                // set a pixel back to the image
                image.at<Vec3b>(Point(x,y)) = color;
 
            }
        }
    }
    cv::imwrite("new_map.jpg", image);
    cv::imshow("Changed a part of the image", image);
    waitKey(0);
     
}