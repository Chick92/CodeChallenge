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


I used a .GPX file from my garmin watch to generate some lat / lon coordinates, of a walk around my parents estate. .gpx does not give speed, but rather a year, month, day, hour, minute, second time stamp. So, I wrote a python script to convert this to a CSV file and (lat / lon) and add a third data field for time since midnight (seconds) as we only care about time difference between points, not absolute time.

The C++ code loads this file and does the following -


When run, the code will load the coordinates and time stamp from the CSV file, it will then print each coordinate lat / lon and time stamp out to the terminal. It will then calculate the speed between each successive coordinate and translate the lat / lon coordinates to Mercator coordinates, and then printing those via the terminal too. Finally, the code will load a map jpeg taken from apple maps (with scale) and overlay the coordinates onto that map, witht he colour of the overlay being dictated by the speed. Red for the slowest point, transitioning to green for the fastest point. 

I determined the distance between points assuming the earth was a perfect sphere. At this scale, the difference between assumed and real world will probably be a few orders of magnitude less than a rounding error. I also used a mercator projection to overlay the points onto a 2D map. Again at this scale the dofference is trivial, and since as though apple maps use a mercator projection anyway, it's cancelled out. 

There are a few comments in the code disucssing why i opted to do things a certain way, i won't repeat them here. 