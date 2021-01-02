This repositiory contains my work on a c++ coding challenge set by Horiba Mirra.

The bulk of the development work was done on an Ipad Pro / Raspberry pi 4 combo, as i received the challenge whilst i was already travelling down to my parents for the Christmas / New years break.

OpenCV was installed on the pi using pre compiled binaries from the comunity, as it was a lot simpler than installing from source. The binaries can be found at https://solarianprogrammer.com/2019/09/17/install-opencv-raspberry-pi-raspbian-cpp-python-development/

The C++ program utilises a C library to parse CSV files, CSVParser, which can be found at https://sourceforge.net/projects/cccsvparser/ - This was used purely because i'd used it before on other projects, and it's relatively easy to work with. 

The command to compile everything is:
g++ main.cpp Journey.cpp -I CsvParser/include CsvParser/src/csvparser.c -o MapJourney `pkg-config --cflags --libs opencv`