//
// Created by Pasarus on 07/12/2017.
//

#include "MammalSightings.h"

void calculateAllTheMammals(struct aMammal *mammals,struct aSighting *sightings, struct anObserver *observers, int sizeOfMammals){
    //Declare the functions I'll need in this functions
    struct anObserver findTheObserver(struct aSighting*, struct anObserver*, int);
    struct aLocation findTheLocation(struct aSighting*, struct anObserver*);
    //Assign the values for mammal type to each of the mammal structs
    for (int i = 0; i<sizeOfMammals; i++){
        mammals->mammalType = sightings->mammalType;
        struct anObserver theObserver = findTheObserver(sightings, observers, sizeOfMammals);
        mammals->location = findTheLocation(sightings, &theObserver);
        mammals++;
        sightings++;
    }
}

struct anObserver findTheObserver (struct aSighting *theSighting, struct anObserver *observers, int sizeOfMammals){
    struct anObserver theObserver;
    theObserver.longitude = 0;
    theObserver.latitude = 0;
    strcat(theObserver.ID, "0000");
    for (int i = 0; i<sizeOfMammals; i++){
        if((strcmp(theSighting->ID, observers->ID) == 0)){
            strcpy(theObserver.ID, observers->ID);
            theObserver.latitude = observers->latitude;
            theObserver.longitude = observers->longitude;
            break;
        }
        observers++;
    }
    return theObserver;
}

struct aLocation findTheLocation(struct aSighting *theSighting, struct anObserver *theObserver){
    double olat, olatR, olong,bg, bgr, range, cmLat, cmLong;
    struct aLocation newLocation;

    //Find the variable values needed ---------------------
    olat = theObserver->latitude;
    olong = theObserver->longitude;
    bg = theSighting->trueNorthBearing;
    range = theSighting->range;

    //Calculate the rest of the needed variables ----------
    olatR = olat * M_PI / 180.0;
    bgr = bg * M_PI / 180.0;

    //Perform the main calculations -----------------------
    cmLat = olat + (range * cos(bgr)) / 60.0;
    cmLong = (olong + (range * sin(bgr) / cos(olatR)) / 60.0);

    //finish the struct -----------------------------------
    newLocation.latitude = cmLat;
    newLocation.longitude = cmLong;

    return newLocation;
}