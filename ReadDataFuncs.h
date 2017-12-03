//
// Created by Pasarus on 03/12/2017.
//

#ifndef LOCALASSIGNMENTC_READDATAFUNCS_H
#define LOCALASSIGNMENTC_READDATAFUNCS_H

int findFileLength(FILE*, const fpos_t*);
void readInTheDataObserver(FILE*, struct anObserver*);
void readInTheDataSighting(FILE*, struct aSighting*);

typedef struct anObserver{
    char ID[4]; float latitude; float longitude;
};

typedef struct aSighting{
    char ID[4]; char mammalType; float trueNorthBearing; float range;
};

typedef struct observerDate{
    int day; int month; int year; int hour; int minute; int seconds;
};

#endif //LOCALASSIGNMENTC_READDATAFUNCS_H
