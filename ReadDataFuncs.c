//
// Created by Pasarus on 03/12/2017.
//

#include <mem.h>
#include <stdio.h>
#include "ReadDataFuncs.h"

int findFileLength(FILE *file, const fpos_t *currentPosition){
    //Will be unable to read in more than 200 charecters from a line but it shouldn't matter
    char buffer[200];
    int fileLength = 0;
    while(fgets(buffer, sizeof(buffer), file)!= NULL){
        fileLength+=1;
    }
    fsetpos(file, currentPosition);
    return fileLength;
}

void readInTheDataObserver(FILE *file, struct anObserver *observers){
    char tempID[4];
    float tempLong, tempLat;
    int i = 0;
    //While not at the end of file scan details
    while(fscanf(file, "%s %f %f", tempID, &tempLong, &tempLat) != EOF){
        i++;

        //Set current data at pointer to the data in the temps
        observers->latitude = tempLat;
        observers->longitude = tempLong;
        strcpy(observers->ID, tempID);

        //Increment the pointer to the next sets of data.
        observers++;
    }
}