This repositiory contains my work on a c++ coding challenge set by Horiba Mirra.

The bulk of the development work was done on an Ipad Pro / Raspberry pi 4 combo, as i received the challenge whilst i was already travelling down to my parents for the Christmas / New years break.

OpenCV was installed on the pi using pre compiled binaries from the comunity, as it was a lot simpler than installing from source. The binaries can be found at https://solarianprogrammer.com/2019/09/17/install-opencv-raspberry-pi-raspbian-cpp-python-development/

The C++ program utilises a C library to parse CSV files, CSVParser, which can be found at https://sourceforge.net/projects/cccsvparser/ - This was used purely because i'd used it before on other projects, and it's relatively easy to work with. 

The command to compile everything is:
$ g++ main.cpp Journey.cpp -I CsvParser/include CsvParser/src/csvparser.c -o MapJourney `pkg-config --cflags --libs opencv`

It is vitally important that you use a verion of g++ => 8

If you're host system is Ubuntu 16, you'll need to install g++ 8 and force it to use that version.

$ g++-8 main.cpp Journey.cpp -I CsvParser/include CsvParser/src/csvparser.c -o MapJourney `pkg-config --cflags --libs opencv`

Also, if you're going to copy and paste the above command, do so from a text file, not githubs visualisation of said file, as it uses the " ` " as syntax and hence doesn't display it. 

A Docker image is provided for your convenience, with openCV and G++ >= 8 installed, and the required files stored in the CodeChallenge directory.   