#include "other.h"
#include <iostream>

class Rectangle {
    int width, height;
  public:
    Rectangle (int,int);
    int area () {return (width*height);}
};

Rectangle::Rectangle (int a, int b) {
  width = a;
  height = b;
}


class LoadCSV{
    string filename;
public:
    load(string);
    
}

LoadCSV::load(string filename){
    trackBarFile.open("TrackBarSignal.csv");

    std::ofstream fout;
    fout.open("Output_ReadInCSV.txt");

    std::string line, line2, line3;
    int count;
    float tokenNum,lineFloat,line2Float,line3Float;

    while (getline(trackBarFile, line,',')&&getline(trackBarFile, line2,',')&&getline(trackBarFile, line3)) {

        lineFloat = (float)atof(line.c_str());
        line2Float = (float)atof(line2.c_str());
        line3Float = (float)atof(line3.c_str());

        std::cout<<line<<","<<lineFloat+2<<"   ,   "<<line2<<","<<line2Float+2<<"  ,  "<<line3<<","<<line3Float+2<<std::endl;
    }

    trackBarFile.close();
}
