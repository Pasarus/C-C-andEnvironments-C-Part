//
// Created by Pasarus on 07/12/2017.
//

#include "MammalSightings.h"

int findFileLength(FILE *file, const fpos_t *currentPosition){
    //Will be unable to read in more than 20 characters from a line but it shouldn't be more than roughly 12 anyway
    char buffer[20];
    int fileLength = 0;
    while(fgets(buffer, sizeof(buffer), file)!= NULL){
        fileLength+=1;
    }
    fsetpos(file, currentPosition);
    return fileLength;
}

void readInTheDataObserver(FILE *file, struct anObserver *observers){
    char tempID[5];
    double tempLong, tempLat;
    int i = 0;
    //While not at the end of file scan details
    while(fscanf(file, "%s %lf %lf", tempID, &tempLat, &tempLong) != EOF){
        i++;

        //Set current data at pointer to the data in the temps
        observers->latitude = tempLat;
        observers->longitude = tempLong;
        strcpy(observers->ID, tempID);

        //Assign null terminator to the end of the string
        observers->ID[4] = '\0';

        //Increment the pointer to the next sets of data.
        observers++;
    }
}

void readInTheDataSighting(FILE *file, struct aSighting *sightings){
    char tempID[5], tempType;
    double tempBearing, tempDistance;
    int i = 0;
    //While not at the end of file scan details
    while(fscanf(file, "%s %c %lf %lf", tempID, &tempType, &tempBearing, &tempDistance) != EOF){
        i++;

        //Set current data at pointer to the data in the temps
        sightings->trueNorthBearing = tempBearing;
        sightings->range = tempDistance;
        strcpy(sightings->ID, tempID);
        sightings->mammalType = tempType;

        //Assign null terminator to the end of the string
        sightings->ID[4] = '\0';
        //Increment the pointer to the next sets of data.
        sightings++;
    }
}