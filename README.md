
#DriveData Analyze

This repository holds tools for analysis of data captured by my DriveData Android app.
----

The following executables are currently in the repository:

+ align: Attempts to calculate an homography transform using the ECC method to relate a present image and a past image. (CURRENTLY BROKEN)
+ analyze: Calls all the nessecary executeables to take a DriveData folder and retrieve all nessecary Street View Imagery
+ correctSV: Calls the methods nessecary to correc the orientation of SV images (Currently calls the manual rotation code)
+ executeSV: Retrieves all StreetView imagry using request strings generated earlier.
+ featureMatcher: Does ORB and FLANN matching between two given images.
+ genImgList: Given a directory, generates a list of all images in that directory.
+ genSnapRequest: Given the file of unique poses, generates a request for the Roads API to snap them to a road.
+ genSVRequest: Given the file of snapped poses, generate requests for Street View imagery at each location.
+ genUniquePose: Generate a file of unique poses from a DriveData location log.
+ matchAll: Attempts to match all SV images with the real-time images which correspond to the unique poses.
+ parseResponse: Parses the JSON response from the SnapToRoads request
+ rotateSV: Rotates a single StreetView image.
+ vdmaker: Makes a video from the images of a DriveData capture (I believe this is currently broken)

----
Usage notes: to use the SnapToRoads and StreetView API's, you MUST have a key stored in:
$BUILD-DIR/config/key.txt  Please use your own Google Developer key.

To generate an analysis file (SV Images, and all associated files), call 
"./analyze/path/to/data/capture ". Make sure that you call the correct path and do not 
include a / at the end of the path.
