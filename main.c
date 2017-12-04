#include <stdio.h>
#include <string.h>
#include <unistd.h>
//#include <ntdef.h>
#include <math.h>

#define FILE_NAME_MAX 40

typedef struct anObserver{
    char ID[4]; double latitude; double longitude;
};

typedef struct aSighting{
    char ID[4]; char mammalType; double trueNorthBearing; double range;
};

typedef struct observerDate{
    int day; int month; int year; int hour; int minute; int seconds;
};

typedef struct aLocation{
    double latitude; double longitude;
};

typedef struct aMammal{
    char mammalType; struct aLocation location;
};


int main() {
    //Function Declarations ---------------------------------------
    int findFileLength(FILE*, const fpos_t*);
    void readInTheDataObserver(FILE*, struct anObserver*);
    void readInTheDataSighting(FILE*, struct aSighting*);
    void calculateAllTheMammals(struct aMammal*,struct aSighting*, struct anObserver*, int sizeOfMammals);

    //Variable declarations ---------------------------------------
    struct observerDate date;
    char observerFileName[FILE_NAME_MAX], observersFileNamePostCat[FILE_NAME_MAX + 4];
    FILE* file;

    //Get the file name for observer and check whether or not it exists
    int fileExists;
    do{
        printf("Give file name for observers\n");
        scanf("%s",observerFileName);
        strcpy(observersFileNamePostCat, "../");
        strcat(observersFileNamePostCat, observerFileName);
        //If file exists or not
        if(access(observersFileNamePostCat, F_OK) != -1) {
            //The file exists
            fileExists = 1;
        } else {
            //The file doesn't exist
            fileExists = 0;
        }
    } while (!fileExists);

    //Open the file
    file = fopen(observersFileNamePostCat, "r");

    //Read in the date
    fscanf(file, "%d %d %d %d %d %d", &date.day, &date.month, &date.year, &date.hour, &date.minute, &date.seconds);

    //Find current file position
    const fpos_t observerFilePosition = ftell(file);

    //Find file length and take one away to account for the date and time
    int fileLength = findFileLength(file, &observerFilePosition)-1;

    //Create the array of data
    struct anObserver observers[fileLength];

    //Read in all the data from the file
    readInTheDataObserver(file , observers);

    // Sightings ------------------------------------------------------
    char sightingFileName[FILE_NAME_MAX], sightingFileNamePostCat[FILE_NAME_MAX + 4];
    do{
        printf("Give file name for sightings\n");
        scanf("%s",sightingFileName);
        strcpy(sightingFileNamePostCat, "../");
        strcat(sightingFileNamePostCat, sightingFileName);
        //If file exists or not
        if(access(sightingFileNamePostCat, F_OK) != -1) {
            //The file exists
            fileExists = 1;
        } else {
            //The file doesn't exist
            fileExists = 0;
        }
    } while (!fileExists);

    //Open sightings
    file = fopen(sightingFileNamePostCat, "r");

    //declare and redefine the necessary variables
    const fpos_t sightingFilePosition = ftell(file);
    fileLength = findFileLength(file, &sightingFilePosition);
    struct aSighting sightings[fileLength];

    //Read in the data from sightings
    readInTheDataSighting(file, sightings);

    //Close the file
    fclose(file);

    // Locations ------------------------------------------
    //Create an array of mammals equal to one mammal per sighting
    struct aMammal mammals[fileLength];




    return 1;
};

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
    char tempID[4];
    double tempLong, tempLat;
    int i = 0;
    //While not at the end of file scan details
    while(fscanf(file, "%s %lf %lf", tempID, &tempLong, &tempLat) != EOF){
        i++;

        //Set current data at pointer to the data in the temps
        observers->latitude = tempLat;
        observers->longitude = tempLong;
        strcpy(observers->ID, tempID);

        //Increment the pointer to the next sets of data.
        observers++;
    }
}

void readInTheDataSighting(FILE *file, struct aSighting *sightings){
    char tempID[4], tempType;
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

        //Increment the pointer to the next sets of data.
        sightings++;
    }
}

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
        if(theSighting->ID == observers->ID){
            strcat(theObserver.ID, observers->ID);
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
    cmLong = olong + (range * sin(bgr) / cos(olatR)) / 60.0;

    //finish the struct -----------------------------------
    newLocation.latitude = cmLat;
    newLocation.longitude = cmLong;

    return newLocation;
}