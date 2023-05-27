/*ROSY BUDHTAHOKI*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXLENGTH 20
#define TOTALALPHABETS 26
#define MappingLength 52
#define MAXMAPPING 150
#define WORDSPERLINE 4

void Encrypt(char word[MAXLENGTH], char fileMode[MappingLength]);
void Decrypt(char word[MAXLENGTH], char fileMode[MappingLength]);
int checkMapping(char file[MAXMAPPING]);

/* This is the main function. It handles the error checking part of the program and exits the program with suitable exit code if errors occur 
while providing arguments. It then called either the Encrypt or Decrypt functions as per user's choice. */
int main(int argc, char *argv[]){
    
    FILE *mappingfile;
    FILE *inputfile;
    int mode =0;

   for(int i = 1; i < 7 ; i= i+2){
        if((strcmp(argv[i],"-i") != 0) && (strcmp(argv[i],"-t") != 0) && (strcmp(argv[i],"-m") != 0)){
            fprintf(stderr,"Usage: ./encrypt -t <mappingfile> -m <encryption mode> -i <inputfile>");
            exit(7);
        }
    }

    if(argc != 7){
            fprintf(stderr,"Usage: ./encrypt -t <mappingfile> -m <encryption mode> -i <inputfile>");
            exit(7);
        }

    /*Checks for -t and uses the file following it as the mapping file, prints an error if can't open the file */
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i],"-t") ==0){
            mappingfile = fopen(argv[i+1],"r");
            if (mappingfile == NULL){            
                fprintf(stderr,"Error: Mapping file %s does not exist", argv[i+1]);
                exit(3);
            }
        }

    /*Checks for -i and uses the file following it as the input file, prints an error if can't open the file */
        if (strcmp(argv[i],"-i")==0){
            inputfile = fopen(argv[i+1],"r");
            if (inputfile == NULL){            
                fprintf(stderr,"Error: Input word file %s does not exist", argv[i+1]);
                exit(5);
            }
        }

    /*Checks for -m and uses the file following it as the input file, prints an error if can't open the file */
        if (strcmp(argv[i],"-m")==0){
            mode = atoi(argv[i+1]);
            if (mode != 2 && mode != 1){    
                fprintf(stderr,"You entered %d. Sorry, your mode must be 1 for encryption or 2 for decryption", mode);
                exit(6);
                
            }
        }
    }

    char wordsToGet[WORDSPERLINE];
    char mappingAlpha[MAXMAPPING]="";

    while (fgets(wordsToGet, WORDSPERLINE, mappingfile)){
        strcat(mappingAlpha,wordsToGet);
    }
    
    /* Calls the checkMapping function to verify that the mapping file has no repetations and is of correct length and format. */
    checkMapping(mappingAlpha);
    fclose(mappingfile);


    /* Removes any comma or newline character from the mapping file*/
    int j=0;
    char temp[MAXMAPPING];
    for(int i=0; i < strlen(mappingAlpha) ; i++){
        if(mappingAlpha[i] != ',' && mappingAlpha[i] != '\n') {
            temp[j] = mappingAlpha[i];
            j++;
        }
    }
    strcpy(mappingAlpha, temp);

    /*Removes any newline character and prints output for encyption or decryption for mode 1 or 2 respectively*/
    char word[MAXLENGTH+1];
    char *removeNullCharacter;
    while ((fgets(word,MAXLENGTH+1,inputfile)) != NULL){
        removeNullCharacter = strtok(word,"\n");
        if(mode == 1){
            Encrypt(removeNullCharacter,mappingAlpha);
            printf("\n");
        }

        if(mode == 2){
            Decrypt(removeNullCharacter, mappingAlpha);
            printf("\n");
        }
    }

    fclose(inputfile);
    return 0;
}


/*This function will take the word to encrypt and the mapping file as arguments and print the encrypted word in a reverse order*/
void Encrypt(char word[MAXLENGTH], char fileMode[MappingLength]){
    for (int i = 0; i < strlen(word); i++) {
        for (int j = 0; j < strlen(fileMode); j++) {
            if ((word[i] == fileMode[j]) && (j%2 == 0)) {
                word[i] = fileMode[j+1];
                break;
            }
        }
    }
    for(int k = strlen(word)-1; k >= 0 ; k--){
      printf("%c",word[k]);
    }
}

/*This function will take the word to decrypt and the mapping file as arguments and print the decrypted word in a reverse order*/
void Decrypt(char word[MAXLENGTH], char fileMode[MappingLength]){
    for (int i = 0; i <= strlen(word); i++) {
        for (int j = 0; j <= strlen(fileMode); j++) {
            if ((word[i] == fileMode[j]) && (j%2 != 0)) {
                word[i] = fileMode[j-1];
                break;
            }
        }
    }
    for(int k = strlen(word)-1; k >= 0 ; k--){
      printf("%c",word[k]);
    }
}

/*This function takes mapping file as argument and checks it for repetation, correct length and correct format. It returns exit code 4 if errors found*/
int checkMapping(char myfile[MAXMAPPING]){
    int j=0;
    char temp[MAXMAPPING];
    for(int i=0; i < strlen(myfile) ; i++){
        if(myfile[i] != '\n') {
            temp[j] = myfile[i];
            j++;
        }
    }
    strcpy(myfile, temp);  /*Copies the temp file to myfile after the newline character is removed*/

    char comma = ',';
    int count=0;
    int plainCount;
    int plainAlpha;
    int cypherAlpha;
    int cypherCount;
    char plainText[TOTALALPHABETS] ={0};
    char cypherText[TOTALALPHABETS]={0};


    /*checks if the mapping file only has the small alphabets or comma in it. Then counts if all 26 albhabets are there
    Then checks if both the right side alphabets and left side alphabets are distinct.*/
    for(int i=0; i<strlen(myfile); i++){
        if(myfile[i] < 'a' && myfile[i]> 'z' && myfile[i] != comma){
        fprintf(stderr,  "Error: The format of mapping file <Name of mapping file> is incorrect");
        exit(4);
        }

        if(i%3 == 0){
            plainAlpha = myfile[i] - 'a';
            plainCount++;
            if (plainText[plainAlpha] == 0)
                plainText[plainAlpha] = 'T';
            else plainText[plainAlpha] = 'F';
        }
        if(i%3 != 0 && myfile[i] != comma){
            cypherCount++;
            cypherAlpha = myfile[i] - 'a';
            if (cypherText[cypherAlpha] == 0)
                cypherText[cypherAlpha] = 'T';
            else cypherText[cypherAlpha] = 'F';
        }
    }

    /*Returns exit code 4 if any repetation of alphabets occur */
    for(int i=0; i<TOTALALPHABETS;i++){
        if(plainText[i] != 'T' || cypherText[i] != 'T')
        {
            fprintf(stderr,  "Error: The format of mapping file <Name of mapping file> is incorrect");
            exit(4);
        }
    }

    /*Checks if the alphabets are spereated by a comma. The format should be "distinct_left_alphabet Comma distinct_right_alphabet" */
    for(int i=1; i<strlen(myfile); i = i+3){
        if(myfile[i] != comma){
            fprintf(stderr,  "Error: The format of mapping file <Name of mapping file> is incorrect");
            exit(4);
        }
        count++;
    }
    /*Return 4 if there are more than 26 lines in the mapping file*/
    if(count != TOTALALPHABETS && plainCount != TOTALALPHABETS && cypherCount !=0){
        fprintf(stderr, "INVALID count");
        exit(4);
    }
    return 0;
}
