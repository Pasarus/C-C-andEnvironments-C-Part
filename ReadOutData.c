//
// Created by Pasarus on 07/12/2017.
//

#include "MammalSightings.h"

void printMammalsToFile(struct aMammal *mammals, FILE * file , int mammalFileSize){
    for(int i = 0; i<mammalFileSize; i++){
        fprintf(file, "%c %.6f %.6f\n", mammals->mammalType, mammals->location.latitude, mammals->location.longitude);
        mammals++;
    }
}

void printMammalsToFileIfInBorder(struct aMammal *mammals, FILE * file, int mammalFileSize){
    for(int i = 0; i<mammalFileSize; i++){
        if(mammals->location.latitude >= LOWER_BORDER &&
           mammals->location.latitude <= UPPER_BORDER &&
           mammals->location.longitude >= WESTERN_BORDER &&
           mammals->location.longitude <= EASTERN_BORDER){
            fprintf(file, "%c %.6f %.6f\n", mammals->mammalType, mammals->location.latitude, mammals->location.longitude);
        }
        mammals++;
    }
}