import numpy as np
import gpxpy
import gpxpy.gpx

'''
Python script to parse gpx file from my Fenix 6X Pro, to the required CSV file
'''

coords = []
gpx_file = open('walk.gpx', 'r')

gpx = gpxpy.parse(gpx_file)

for track in gpx.tracks:
    for segment in track.segments:
        for point in segment.points:
            #print point.time.hour, point.time.minute, point.time.second
            seconds_since_midnight = (point.time.hour * 60 * 60) + (point.time.minute * 60) + point.time.second
            #print seconds_since_midnight
            pt = [point.latitude, point.longitude, seconds_since_midnight]
            coords.append(pt)

coordinates = np.asarray(coords)
np.savetxt('coordinates.csv', coordinates, delimiter = ',')
