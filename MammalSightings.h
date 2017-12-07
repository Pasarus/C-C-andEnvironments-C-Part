//
// Created by Pasarus on 07/12/2017.
//

#ifndef LOCALASSIGNMENTC_MAMMALSIGHTINGS_H
#define LOCALASSIGNMENTC_MAMMALSIGHTINGS_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>

#define FILE_NAME_MAX 40
#define UPPER_BORDER 53.833
#define LOWER_BORDER 52.000
#define EASTERN_BORDER -4.000
#define WESTERN_BORDER -5.500

//The various structs
typedef struct anObserver{
    char ID[5]; double latitude; double longitude;
} obs;

typedef struct aSighting{
    char ID[5]; char mammalType; double trueNorthBearing; double range;
} sight;

typedef struct observerDate{
    int day; int month; int year; int hour; int minute; int seconds;
} date;

typedef struct aLocation{
    double latitude; double longitude;
} location;

typedef struct aMammal{
    char mammalType; struct aLocation location;
} mammal;

//The various functions used in the main.c file
int findFileLength(FILE*, const fpos_t*);
void readInTheDataObserver(FILE*, struct anObserver*);
void readInTheDataSighting(FILE*, struct aSighting*);
void calculateAllTheMammals(struct aMammal*,struct aSighting*, struct anObserver*, int);
void printMammalsToFile(struct aMammal*, FILE*, int);
void printMammalsToFileIfInBorder(struct aMammal*, FILE*, int);

#endif //LOCALASSIGNMENTC_MAMMALSIGHTINGS_H
