#include "MammalSightings.h"

int main() {
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
            printf("File doesn't exist try again!");
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
    fclose(file);//

    // Locations ------------------------------------------
    //Create an array of mammals equal to one mammal per sighting
    struct aMammal mammals[fileLength];

    calculateAllTheMammals(mammals, sightings, observers, fileLength);

    //Take in the file name and open that file for writing
    char outputFileName[FILE_NAME_MAX], outputFileNamePostCat[FILE_NAME_MAX + 4] = "../";
    printf("What file do you want to print the data to?\n");
    scanf("%s", outputFileName);

    strcat(outputFileNamePostCat, outputFileName);

    file = fopen(outputFileNamePostCat, "w");

    //Write all the data to the file
    printMammalsToFile(mammals, file, fileLength);

    fclose(file);

    // Locations within the border ---------------------------
    //Take file name and open for write
    char output2FileName[FILE_NAME_MAX], output2FileNamePostCat[FILE_NAME_MAX + 4] = "../";
    printf("What file do you want to print the data to for within the sea area?\n");
    scanf("%s", output2FileName);

    strcat(output2FileNamePostCat, output2FileName);

    file = fopen(output2FileNamePostCat, "w");

    //Then write all the data to file if it is within the sea area.
    printMammalsToFileIfInBorder(mammals, file, fileLength);

    fclose(file);

    //Exit with success
    return EXIT_SUCCESS;
};