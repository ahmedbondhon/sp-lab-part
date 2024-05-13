#include <stdio.h>
#include <stdlib.h>

void Addplayers();
void Playerrecord();
void Searchplayers(); // Function prototype for Searchplayers
void Deleteplayers(); // Function prototype for Deleteplayers

struct Player {
    char first_name[200];
    char last_name[200];
    int jersey_no;
    char club_name[200];
    char nationality[200];
    float per;
};

int main() {
    int choice;
    while (choice != 5) {
        system("clear"); // Clearing the screen
        printf("                              ===== BARCELONA  PLAYERS DATABASE MANAGEMENT SYSTEM=====");
        printf("\n\n\n\t\t\t\t 1. Add players record\n");
        printf("\t\t\t\t 2. Player record\n");
        printf("\t\t\t\t 3. Search players\n");
        printf("\t\t\t\t 4. Delete players record\n");

        printf("\t\t\t\t ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                Addplayers();
                break;

            case 2:
                system("clear");
                Playerrecord();
                printf("\t\t\t\t Press any key to exit\n");
                getchar(); // getchar() to wait for user input
                system("clear");
                break;

            case 3:
                Searchplayers(); // Calling Searchplayers function
                printf("\n\t\t\t\t Press any key to exit\n");
                getchar();
                system("clear");
                break;

            case 4:
                Deleteplayers(); // Calling Deleteplayers function
                printf("\n\t\t\t\t Press any key to exit\n");
                getchar();
                system("clear");
                break;


        }
    }

}

void Addplayers() {
    char another;
    FILE *fp;
    struct Player info;
    do {
        system("clear"); // Clearing the screen
        printf("\t\t\t\t====== ADD PLAYERS INFO======\n\n\n");
        fp = fopen("Player_info.txt", "a");
        printf("\n\t\t\t Enter first name   : ");
        scanf("%s", info.first_name);
        printf("\n\t\t\t Enter last name    : ");
        scanf("%s", info.last_name);
        printf("\n\t\t\t Enter jersey no   : ");
        scanf("%d", &info.jersey_no);
        printf("\n\t\t\t Enter club name   : ");
        scanf("%s", info.club_name);
        printf("\n\t\t\t Enter nationality : ");
        scanf("%s", info.nationality);
        printf("\n\t\t\t Enter total G/A      : ");
        scanf("%f", &info.per);
        printf("\n\t\t\t____________________ \n");
        if (fp == NULL) {
            printf("\t\t\tCan't open file\n");
        }
        else {
            printf("\t\t\tRecord stored successfully\n");
        }
        fwrite(&info, sizeof(struct Player), 1, fp);
        fclose(fp);
        printf("\t\t\tDo you want to add another record? (y/n): ");
        scanf(" %c", &another);
    } while(another == 'y' || another == 'Y');
}

void Playerrecord(){
    FILE *fp;
    struct Player info;
    fp=fopen("Player_info.txt","r");
    printf("\t\t\t\t====== PLAYERS RECORD ======\n\n\n");

    if (fp == NULL){
        printf("\t\t\t\tCan't open file\n");
    }else {
        printf("\t\t\t\tRecord\n");
        printf("\t\t\t\t__/n/n");

    }
    while(fread(&info,sizeof(struct Player),1,fp)){
        printf("\n\t\t\t\tPlayer name    : %s %s",info.first_name, info.last_name);
        printf("\n\t\t\t\tJersey number : %d",info.jersey_no);
        printf("\n\t\t\t\tClub name    : %s",info.club_name);
        printf("\n\t\t\t\tNationality : %s",info.nationality);
        printf("\n\t\t\t\ttotal G/A       : %.2f",info.per);
        printf("\n\t\t\t\t__\n");
    }
    fclose(fp);
    getchar(); // getchar() to wait for user input
}

void Searchplayers (){
    FILE *fp;
    struct Player info;
    int jersey_no , found=0;
    fp=fopen("Player_info.txt","r");
    printf("\t\t\t\t====== PLAYERS RECORD ======\n\n\n");
    printf("\t\t\t jersey no :");
    scanf("%d",&jersey_no);

    while(fread(&info,sizeof(struct Player),1,fp)){
        if(info.jersey_no==jersey_no){
          found=1;

        printf("\n\t\t\t\tPlayer name    : %s %s",info.first_name, info.last_name);
        printf("\n\t\t\t\tJersey number : %d",info.jersey_no);
        printf("\n\t\t\t\tClub name    : %s",info.club_name);
        printf("\n\t\t\t\tNationality : %s",info.nationality);
        printf("\n\t\t\t\ttotal G/A      : %.2f",info.per);
        printf("\n\t\t\t\t__\n");
    }
    }

     if(!found){
         printf("\n\t\t\t record not found\n");
     }

    fclose(fp);
    getchar(); // getchar() to wait for user input
}

void Deleteplayers() {
    FILE *fp, *fp1;
    struct Player info;
    int jersey_no, found = 0;
    printf("\t\t\t\t====== PLAYERS RECORD ======\n\n\n");

    fp = fopen("Player_info.txt", "r");
    fp1 = fopen("temp.txt", "w");
    printf("\t\t\t Enter jersey no :");
    scanf("%d", &jersey_no);

    if (fp == NULL) {
        fprintf(stderr, "\t\t\t\t Can't open file :\n");
        printf("\t\t\t\t Can't open file :\n");
    } else {
        while (fread(&info, sizeof(struct Player), 1, fp)) {
            if (info.jersey_no == jersey_no) {
                found = 1;
            } else {
                fwrite(&info, sizeof(struct Player), 1, fp1);
            }
        }

        fclose(fp);
        fclose(fp1);

        if (found) {
            remove("Player_info.txt");
            rename("temp.txt", "Player_info.txt");
            printf("\n\t\t\t Record Delete successfully\n");
        }
        if (!found) {
            printf("\n\t\t\t Record not found\n");
        }
    }
} // Added closing brace here
