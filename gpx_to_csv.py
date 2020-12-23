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
            pt = [point.latitude, point.longitude]
            coords.append(pt)

coordinates = np.asarray(coords)
np.savetxt('coordinates.csv', coordinates, delimiter = ',')
