/* the username and password are given by user when they run the code for the first time , after the username
and password is saved in login.txt , the program will shutdown and will tell the user to open the program for the 2nd time
 then they can login via the username and password they given and make use of the program */

#include <stdio.h>
#include <string.h>

#define MAX_PLAYERS 100

typedef struct playerinfo
{
    char playername[100];
    char playerposition[4];
    int playerjerseynumber;
    int contractduration;
    int playerage;
    int playerhealth;
} playerinfo;

typedef struct logininfo
{
    char loginname[11];
    char loginpass[11];
} logininfo;



void savelogin(logininfo credentials)
{
    FILE *file2;
    file2 = fopen("login.txt", "w");
    fprintf(file2, "%s,%s\n", credentials.loginname, credentials.loginpass);
    fclose(file2);
}

int read_login(logininfo credentials)
{
    FILE *file2;
    file2 = fopen("login.txt", "r");
    int log =0;
    if (file2 == NULL)
    {
        char newloginname[12], newloginpass[12];
        printf("First time opening program.\n");

        for (;;)
        {
            printf("Enter new username to save (max 10 characters and minimum 4 characters): ");
            fflush(stdin);
            gets(newloginname);
            if (strlen(newloginname) <= 10 && strlen(newloginname) > 3)
            {
                strcpy(credentials.loginname, newloginname);
                break;
            }
        }

        for (;;)
        {
            printf("Enter new password to save (max 10 characters and minimum 4 characters): ");
            fflush(stdin);
            gets(newloginpass);
            if (strlen(newloginpass) <= 10 && strlen(newloginpass) > 3)
            {
                strcpy(credentials.loginpass, newloginpass);
                break;
            }
        }

        savelogin(credentials);
        fclose(file2);
        return 2;

    }
    else
    {
        fscanf(file2, "%[^,],%[^\n]", credentials.loginname, credentials.loginpass);
        fclose(file2);

        char username[12];
        char password[12];

        printf("Enter Username: ");
        fflush(stdin);
        gets(username);

        printf("Enter Password: ");
        fflush(stdin);
        gets(password);

        if (strcmp(username, credentials.loginname) == 0 && strcmp(password, credentials.loginpass) == 0)
            log = 1;
        else
            log = 0;
    }
    return log;
}


int read_playerinfo(playerinfo players[])
{
    int numplayers = 0;
    FILE *file;
    file = fopen("team.txt","r");
    if (file == NULL)
    {
        printf("Error opening team data file or first time running this program without saving teamdata file before.\nAdd player info to create teamdata file.\n");
    }

    while (fscanf(file, "%[^,],%[^,],%d,%d,%d,%d\n", players[numplayers].playername, players[numplayers].playerposition,
                  &players[numplayers].playerjerseynumber,&players[numplayers].contractduration,&players[numplayers].playerage,
                  &players[numplayers].playerhealth)==6)

    {
        numplayers++;
    }

    fclose(file);
    return numplayers;
}

void saveplayers(playerinfo players[], int numplayers)
{
    FILE *file;
    file = fopen("team.txt","w");

    for (int i = 0; i < numplayers; i++)
    {
        fprintf(file, "%s,%s,%d,%d,%d,%d\n", players[i].playername, players[i].playerposition, players[i].playerjerseynumber,
                players[i].contractduration, players[i].playerage,  players[i].playerhealth);

    }

    fclose(file);
}

void addplayer(playerinfo players[], int *numplayers);
void editinfo(playerinfo players[], int numplayers);
void checkplayerinfo(playerinfo players[], int numplayers);
void viewplayers(playerinfo players[], int numplayers);
void deleteplayers(playerinfo players[], int *numplayers);
void teamanalysis(playerinfo players[], int numplayers);


void main()
{
    logininfo credentials;
    int result = read_login(credentials);

    if(result==1)
    {
        printf("Login successful!\n");


    playerinfo players[MAX_PLAYERS];
    int numplayers = read_playerinfo(players);
    int choice;

            printf("Welcome to the Football Club Management System.\n");

          for(;;)
            {
                printf("\n******************************\n");
                printf("   FOOTBALL CLUB MANAGEMENT   \n");
                printf("******************************\n");
                printf("1. Add Player\n");
                printf("2. Edit Player Info\n");
                printf("3. Check Player Info\n");
                printf("4. View Players\n");
                printf("5. Delete Player Info\n");
                printf("6. Team Analysis.\n");
                printf("0. Exit\n");
                printf("Enter your choice to proceed: ");
                scanf("%d", &choice);

                switch (choice)
                {
                case 1:
                    addplayer(players, &numplayers);
                    saveplayers(players, numplayers);
                    break;
                case 2:
                    editinfo(players, numplayers);
                    saveplayers(players, numplayers);
                    break;
                case 3:
                    checkplayerinfo(players, numplayers);
                    break;
                case 4:
                    viewplayers(players, numplayers);
                    break;
                case 5:
                    deleteplayers(players, &numplayers);
                    saveplayers(players, numplayers);
                    break;
                case 6:
                    teamanalysis(players, numplayers);
                    break;
                case 0:
                    printf("Exiting the program. Thank you.\n");
                    getch();
                    return;
                default:
                    printf("Invalid choice. Please try again.\n");
                    getch();
                    return;
                }
            }


        }

        else if(result==2)
        {
            printf("New login detected. Open the program again to start adding info of player.");

        }

        else
        {
            printf("Login failed because of invalid username or password.");

        }

    getch();

}







void addplayer(playerinfo players[], int *numplayers)
{
    if (*numplayers >= MAX_PLAYERS)
    {
        printf("Maximum number of players reached.\n");
        return;
    }

    playerinfo newplayer;

    printf("\nEnter new player name: ");
    fflush(stdin);
    gets(newplayer.playername);

    for(; ;)
    {

        printf("Enter new player position(write atk or mid or def or gk only) : ");
        fflush(stdin);
        scanf("%s",newplayer.playerposition);

        if(strcmp(newplayer.playerposition,"atk")==0 ||strcmp(newplayer.playerposition,"mid")==0 ||strcmp(newplayer.playerposition,"def")==0 ||
                strcmp(newplayer.playerposition,"gk")==0)
            break;
        else
            printf("Invaild input. Try again\n");
    }


    printf("Enter new player jersey number : ");
    fflush(stdin);
    scanf("%d",&newplayer.playerjerseynumber);

    for (int i = 0; i < *numplayers; i++)
    {

        if (players[i].playerjerseynumber == newplayer.playerjerseynumber)
        {
            printf("This jersey number already exists. Try again.\n");
            return;
        }

    }

    for(;;)

    {
        printf("Enter new player contract duration (months) : ");
        fflush(stdin);
        scanf("%d",&newplayer.contractduration);

        if(newplayer.contractduration > 0)
            break;
        else
            printf("Contract duration cannot be less or equal 0. Try again.\n");

    }
    for(;;)

    {
        printf("Enter new player age : ");
        fflush(stdin);
        scanf("%d",&newplayer.playerage);

        if(newplayer.playerage > 0 && newplayer.playerage <80)
            break;
        else
            printf("Age cannot be less or equal 0. Try again.\n");

    }

    for(;;)
    {
        printf("Enter new player health status (0=injured and 1=healthy) : ");
        fflush(stdin);
        scanf("%d",&newplayer.playerhealth);

        if(newplayer.playerhealth==0 || newplayer.playerhealth==1)
            break;
        else
            printf("invaild input. Try again\n");

    }

    players[*numplayers] = newplayer;
    (*numplayers)++;


    printf("new player added successfully.\n");


}

void editinfo(playerinfo players[], int numplayers)
{
    if(numplayers>0)

    {

        char splayername[100];

        printf("Enter player full name: ");
        fflush(stdin);
        gets(splayername);

        int playerindex = -1;
        for (int i = 0; i < numplayers; i++)
        {
            if (strcmp(splayername,players[i].playername)==0)
            {
                playerindex = i;
                break;
            }
        }

        if (playerindex == -1)
        {
            printf("Player not found.\n");
            return;

        }
        int choiceofedit;
        for(;;)
        {
            printf("1. Change player jersey number\n");
            printf("2. Change player contract duration\n");
            printf("3. change player age\n");
            printf("4. change player health\n");
            printf("0. Exit this menu\n");
            printf("Enter your choice to proceed: ");
            fflush(stdin);
            scanf("%d",&choiceofedit);

            if(choiceofedit==1)
            {
                int newjersey;
                printf("Enter new player jersey number : ");
                fflush(stdin);
                scanf("%d",&newjersey);

                for (int j = 0; j < numplayers; j++)
                {

                    if (players[j].playerjerseynumber == newjersey)
                    {
                        printf("This jersey number already exists. Try again.\n");
                        return;
                    }

                }
                players[playerindex].playerjerseynumber = newjersey;
                printf("New info edited successfully\n");
                return;

            }
            else if(choiceofedit==2)
            {
                int newcontractduration;

                for(;;)
                {
                    printf("Enter new contract duration : ");
                    fflush(stdin);
                    scanf("%d",&newcontractduration);

                    if(newcontractduration>0)
                        break;

                    else if(newcontractduration==0)
                    {
                        printf("New contract duration is set to 0. To delete player info use DELETE PLAYER INFO function\n");
                        break;
                    }
                    else
                        printf("Invalid input. Try again.\n");

                }
                players[playerindex].contractduration = newcontractduration;
                printf("New info edited successfully\n");

                return;

            }
            else if(choiceofedit==3)
            {
                int newplayerage;

                for(;;)
                {
                    printf("Enter new age : ");
                    fflush(stdin);
                    scanf("%d",&newplayerage);

                    if(newplayerage>0 && newplayerage<80)
                        break;
                    else
                        printf("Player age cannot be less or equal 0. Try again\n");


                }

                players[playerindex].playerage = newplayerage;
                printf("New info edited successfully\n");
                return;

            }
            else if(choiceofedit==4)
            {
                int newhealth;
                printf("Enter health status(0 for injured and 1 for healthy) : ");
                fflush(stdin);
                scanf("%d",&newhealth);
                if(newhealth==0 || newhealth==1)
                {
                    players[playerindex].playerhealth = newhealth;
                    printf("New info edited successfully\n");
                    break;
                }
                else
                    printf("invaild input. Try again\n");
                return;
            }


            else if(choiceofedit==0)
            {
                return;
            }
            else
            {
                printf("invalid choice");
                return;
            }

        }
    }
    else
        printf("No players found.\n");
    return;

}


void checkplayerinfo(playerinfo players[], int numplayers)
{

    if(numplayers>0)
    {

        char splayername[100];

        printf("Enter player name: ");
        fflush(stdin);
        gets(splayername);

        int playerindex = -1;
        for (int i = 0; i < numplayers; i++)
        {
            if (strcmp(splayername,players[i].playername)==0)
            {
                playerindex = i;
                break;
            }
        }

        if (playerindex == -1)
        {
            printf("Player not found.\n");
            return;

        }
        if( players[playerindex].playerhealth==1)
        {
            printf("player name : %s, position :%s, jersey number :%d%, contract duration :%d%, age :%d%, healthy.\n",
                   players[playerindex].playername, players[playerindex].playerposition,
                   players[playerindex].playerjerseynumber,
                   players[playerindex].contractduration, players[playerindex].playerage);
        }
        else
        {
            printf("player name : %s, position :%s, jersey number :%d%, contract duration :%d%, age :%d%, injured.\n",
                   players[playerindex].playername, players[playerindex].playerposition,
                   players[playerindex].playerjerseynumber,
                   players[playerindex].contractduration, players[playerindex].playerage);
        }
        return;
    }

    else
        printf("No player found.\n");
    return;
}

void viewplayers(playerinfo players[], int numplayers)
{
    if(numplayers>0)
    {

        char splayerposition[4];
        int viewofchoice;

        printf("1. View players according position\n");
        printf("2. View all players\n");
        printf("0. Leave menu\n");
        printf("Enter your choice to proceed: ");
        fflush(stdin);
        scanf("%d",&viewofchoice);


        if(viewofchoice==1)

        {

            for(;;)
            {

                printf("Enter player position(write atk or mid or def or gk only) : ");
                fflush(stdin);
                scanf("%s",splayerposition);

                if(strcmp(splayerposition,"atk")==0 ||strcmp(splayerposition,"mid")==0 ||strcmp(splayerposition,"def")==0 ||
                        strcmp(splayerposition,"gk")==0)
                    break;
                else
                {
                    printf("Invaild input. Try again\n");
                    return;
                }
            }


            for(int i=0 ; i< numplayers ; i++)
            {

                if(strcmp(players[i].playerposition,splayerposition)==0)
                {
                    if(players[i].playerhealth==1)
                        printf("player name : %s, position :%s, jersey number :%d%, contract duration :%d%, age :%d%, healthy.\n",
                               players[i].playername, players[i].playerposition,
                               players[i].playerjerseynumber,
                               players[i].contractduration, players[i].playerage);

                    else
                        printf("player name : %s, position :%s, jersey number :%d%, contract duration :%d%, age :%d%, injured.\n",
                               players[i].playername, players[i].playerposition,
                               players[i].playerjerseynumber,
                               players[i].contractduration, players[i].playerage);


                }

                else if( strcmp(players[i].playerposition,splayerposition)==0)
                {
                    if(players[i].playerhealth==1)
                        printf("player name : %s, position :%s, jersey number :%d%, contract duration :%d%, age :%d%, healthy.\n",
                               players[i].playername, players[i].playerposition,
                               players[i].playerjerseynumber,
                               players[i].contractduration, players[i].playerage);
                    else
                        printf("player name : %s, position :%s, jersey number :%d%, contract duration :%d%, age :%d%, injured.\n",
                               players[i].playername, players[i].playerposition,
                               players[i].playerjerseynumber,
                               players[i].contractduration, players[i].playerage);

                }

                else if( strcmp(players[i].playerposition,splayerposition)==0)
                {
                    if(players[i].playerhealth==1)
                        printf("player name : %s, position :%s, jersey number :%d%, contract duration :%d%, age :%d%, healthy.\n",
                               players[i].playername, players[i].playerposition,
                               players[i].playerjerseynumber,
                               players[i].contractduration, players[i].playerage);

                    else
                        printf("player name : %s, position :%s, jersey number :%d%, contract duration :%d%, age :%d%, injured.\n",
                               players[i].playername, players[i].playerposition,
                               players[i].playerjerseynumber,
                               players[i].contractduration, players[i].playerage);


                }

                else if(strcmp(players[i].playerposition,splayerposition)==0)
                {
                    if(players[i].playerhealth==1)
                        printf("player name : %s, position :%s, jersey number :%d%, contract duration :%d%, age :%d%, healthy.\n",
                               players[i].playername, players[i].playerposition,
                               players[i].playerjerseynumber,
                               players[i].contractduration, players[i].playerage);

                    else
                        printf("player name : %s, position :%s, jersey number :%d%, contract duration :%d%, age :%d%, injured.\n",
                               players[i].playername, players[i].playerposition,
                               players[i].playerjerseynumber,
                               players[i].contractduration, players[i].playerage);
                }

            }
            return;


        }




        else if(viewofchoice==2)
        {
            for(int j=0 ; j < numplayers ; j++ )
            {
                if( players[j].playerhealth==1)
                {
                    printf("player name : %s, position :%s, jersey number :%d%, contract duration :%d%, age :%d%, healthy.\n",
                           players[j].playername, players[j].playerposition,
                           players[j].playerjerseynumber,
                           players[j].contractduration, players[j].playerage);
                }
                else if( players[j].playerhealth==0)
                {
                    printf("player name : %s, position :%s, jersey number :%d%, contract duration :%d%, age :%d%, injured.\n",
                           players[j].playername, players[j].playerposition,
                           players[j].playerjerseynumber,
                           players[j].contractduration, players[j].playerage);
                }
            }
            return;

        }

        else
        {

            printf("Invaild input. Try again\n");
            return;

        }

    }

    else
        printf("No players found\n");
    return;
}






void deleteplayers(playerinfo players[], int *numplayers)
{
    int choice;
    printf("1. Delete 1 player info.\n");
    printf("2. Delete all player info.\n");
    printf("3. Return to main menu.\n");
    printf("Enter your choice ");
    fflush(stdin);
    scanf("%d",&choice);

    if(choice==1)
    {

        char splayername[100];
        printf("Enter player name: ");
        fflush(stdin);
        gets(splayername);

        int playerindex = -1;
        for (int i = 0; i < *numplayers; i++)
        {
            if (strcmp(splayername,players[i].playername)==0)
            {
                playerindex = i;
                break;
            }
        }

        if (playerindex == -1)
        {
            printf("Player not found.\n");
            return;
        }

        for (int i = playerindex; i < *numplayers - 1; i++)
        {
            players[i] = players[i + 1];
        }

        (*numplayers)--;
        printf("Player info deleted successfully.\n");
        return;
    }

    else if (choice==2)
    {
        (*numplayers)=0;
        printf("All player info deleted successfully.\n");
        return;
    }

    else if(choice==3)
        return;

    else
        printf("Invalid choice. Try again\n");
    return;

}

void teamanalysis(playerinfo players[], int numplayers)
{
    if(numplayers>0)

    {


        int minatk=5, minmid=9, mindef=8, mingk=3 ;
        int acatk=0,acmid=0,acdef=0,acgk=0;
        int icatk=0,icmid=0,icdef=0,icgk=0;
        int choice;

        printf("1. Analyze attackers count.\n");
        printf("2. Analyze midfielders count.\n");
        printf("3. Analyze defenders count.\n");
        printf("4. Analyze goalkeepers count.\n");
        printf("0. Exit.\n");
        printf("Enter choice :");
        fflush(stdin);
        scanf("%d",&choice);


        if(choice==1)
        {
            for(int i=0 ; i< numplayers ; i++)
            {
                if(strcmp(players[i].playerposition,"atk")==0)
                {
                    if(players[i].playerhealth==1)
                        acatk++;

                    else
                        icatk++;

                }
            }

            int totalatk= acatk + icatk;
            int signatk= minatk - acatk;

            if (signatk>0)
            {
                printf("The minimum strikers required 5, active strikers %d, injured strikers %d, striker/strikers to sign-up %d.\n",acatk,icatk,signatk);
            }
            else
            {
                printf("The minimum strikers required 5, active strikers %d, injured strikers %d, no need to sign-up more strikers.\n",acatk,icatk);
            }
            return;

        }

        else if(choice==2)
        {
            for(int i=0 ; i< numplayers ; i++)
            {
                if(strcmp(players[i].playerposition,"mid")==0)
                {
                    if(players[i].playerhealth==1)
                        acmid++;

                    else
                        icmid++;

                }
            }

            int totalmid= acmid + icmid;
            int signmid= minmid - acmid;

            if (signmid>0)
            {
                printf("The minimum midfielders required 9, active midfielders %d, injured midfielders %d, midfielder/midfielders to sign-up %d.\n",acmid,icmid,signmid);
            }
            else
            {
                printf("The minimum midfielders required 9, active midfielders %d, injured midfielders %d, no need to sign-up more midfielders.\n",acmid,icmid);
            }
            return;

        }

        else if(choice==3)
        {
            for(int i=0 ; i< numplayers ; i++)
            {
                if(strcmp(players[i].playerposition,"def")==0)
                {
                    if(players[i].playerhealth==1)
                        acdef++;

                    else
                        icdef++;

                }
            }

            int totaldef= acdef + icdef;
            int signdef= mindef - acdef;

            if (signdef>0)
            {
                printf("The minimum defenders required 8, active defenders %d, injured defenders  %d, defender/defenders to sign-up %d.\n",acdef,icdef,signdef);
            }
            else
            {
                printf("The minimum defenders required 8, active defenders %d, injured defenders %d, no need to sign-up more defenders.\n",acdef,icdef);
            }
            return;

        }

        else if(choice==4)
        {
            for(int i=0 ; i< numplayers ; i++)
            {
                if(strcmp(players[i].playerposition,"gk")==0)
                {
                    if(players[i].playerhealth==1)
                        acgk++;

                    else
                        icgk++;

                }
            }

            int totalgk= acgk + icgk;
            int signgk= mingk - acgk;

            if (signgk>0)
            {
                printf("The minimum goalkeepers required 3, active goalkeepers %d, injured goalkeepers %d, goalkeeper/goalkeepers to sign-up %d.\n",acgk,icgk,signgk);
            }
            else
            {
                printf("The minimum goalkeepers required 3, active goalkeepers %d, injured goalkeepers %d, no need to sign-up more goalkeepers.\n",acgk,icgk);
            }
            return;

        }
        else if(choice==0)
            return;

        else
            printf("Invalid choice. Try again.");
        return;

    }

    else
        printf("No players found to analyze. Save player info first then try again.");
    return;

}



