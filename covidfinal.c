#include <stdio.h>
#include <stdlib.h> // atoi, malloc, free
#include <ctype.h> // isdigit

// variables declaration
// yesterday
const int day9NewCase = 9;
const int day9TotalCase = 100;
const int day9TotalDeaths = 2;
const int day9TotalDischarged = 10;
const int day9TotalUnderTreatment = 88;
const float day9DeathPercentage = (float)2 / 100 * 100;
const float day9DischargedPercentage = (float)10 / 100 * 100;
const float day9TreatmentPercentage = (float)88 / 100 * 100;

struct dailyData
{
    int newCase;
    int totalCase;
    int totalDeaths;
    int totalDischarged;
    int totalUnderTreatment;
    float deathPercentage;
    float dischargedPercentage;
    float treatmentPercentage;
};

// constants for error handling
const char* ERRCHK_NUMBER = "number";
const char* ERRCHK_MENU = "menu";

// constant for string buffer
const int BUFFER_SIZE = 256;

// new data
int numOfNewLocalCases;
int numOfNewImportedCases;
int numOfDeaths;
int numOfDischarged;

//daliy comparative
int currentDay = 10;

int highestCase = 9; //day 9
int highestCaseDay = 9; // no. of cases in day 9
int lowestCase = 9;
int lowestCaseDay = 9;

// function declaration
struct dailyData calculation(struct dailyData);
void printDailySummaryReport(struct dailyData);
void printDailyComparativeReport(struct dailyData, struct dailyData);
void readInput(struct dailyData);
void printYesterdayTotal(int, struct dailyData);
void validateInput(char* type, char* input);

int main()
{
    struct dailyData  prevDay = { day9NewCase,day9TotalCase,day9TotalDeaths,day9TotalDischarged,day9TotalUnderTreatment,day9DeathPercentage,day9DischargedPercentage,day9TreatmentPercentage };
    struct dailyData newTotalData;
    char* choice = malloc(BUFFER_SIZE);

    int hasData = 0;
    do
    { //Menu
        printf("\nPlease select which one you want to show:\n");
        printf("1. Enter current day data.\n");
        printf("2. Daily Summary Report\n");
        printf("3. Daily Comparative Report\n");
        printf("4. Yesterday Data\n");
        printf("5. Highest and Lowest cases\n");
        printf("6. Enter next day data\n");
        printf("7. Exit program\n");
        printf("Please enter your choice (1-7):");
        fgets(choice, BUFFER_SIZE, stdin);
        validateInput(ERRCHK_MENU, choice);
        if (strcmp(choice, "1") == 0)
        {
            // used only for day 10
            if (hasData == 1)
            {
                printf("Data for current day has been entered.\n");
                continue;
            }

            readInput(prevDay);
            hasData = 1;
            newTotalData = calculation(prevDay);
        }
        else if (strcmp(choice, "2") == 0)
        {
            if (hasData == 0) // user has not entered data
            {
                printf("Please enter data first.\n");
                continue;
            }

            printDailySummaryReport(newTotalData);
        }
        else if (strcmp(choice, "3") == 0)
        {
            if (hasData == 0) // user has not entered data
            {
                printf("Please enter data first.\n");
                continue;
            }

            printDailyComparativeReport(prevDay, newTotalData);
        }
        else if (strcmp(choice, "4") == 0)
        {
            printYesterdayTotal(currentDay, prevDay);
        }
        else if (strcmp(choice, "5") == 0)
        {
            if (hasData == 0)
                printf("\nTOTAL Days recorded\t= 1 day (Day 9)\n");
            else
                printf("\nTOTAL Days recorded\t= %d days (Day 9 to Day %d)\n", currentDay - 9 + 1, currentDay);

            printf("HIGHEST number of cases\t= %d, occuring on Day %d\n", highestCase, highestCaseDay);
            printf("LOWEST number of cases \t= %d, occuring on Day %d\n\n", lowestCase, lowestCaseDay);
        }
        else if (strcmp(choice, "6") == 0)
        {
            if (hasData != 1)
            {
                printf("Please enter data first.\n");
                continue;
            }

            currentDay++;
            prevDay = newTotalData; // update yesterday's data
            readInput(prevDay);
            hasData = 1;
            newTotalData = calculation(prevDay);
        }
        else if (strcmp(choice, "7") == 0)
            printf("\nThank you for using the program!\n");

    } while (strcmp(choice, "7") != 0);

    free(choice);
    choice = NULL;
    return 0;
}

void readInput(struct dailyData prevDay) {
    char* usrInput = malloc(BUFFER_SIZE); // holds user input to check for errors

    printf("Day %d\n", currentDay);
    printf("=======\n");
    printf("Key in Today's data: , \n");

    printf("\tNumber of New Local Cases :");
    fgets(usrInput, BUFFER_SIZE, stdin);
    validateInput(ERRCHK_NUMBER, usrInput);
    numOfNewLocalCases = atoi(usrInput);

    printf("\tNumber of New Imported Cases:");
    fgets(usrInput, BUFFER_SIZE, stdin);
    validateInput(ERRCHK_NUMBER, usrInput);
    numOfNewImportedCases = atoi(usrInput);

    //difference from yesterday
    int todayTotalNewCases = numOfNewLocalCases + numOfNewImportedCases;
    if (todayTotalNewCases < prevDay.newCase)
        printf("Total number of new cases = %i\t(Decrease by %i from yesterday.)", todayTotalNewCases, prevDay.newCase - todayTotalNewCases);
    else if (todayTotalNewCases > prevDay.newCase)
        printf("Total number of new cases = %i\t(Increase by %i from yesterday.)", todayTotalNewCases, todayTotalNewCases - prevDay.newCase);
    else
        printf("Total number of new cases = %i\t(Remain the same.)", todayTotalNewCases);

    if (todayTotalNewCases >= highestCase)
    {
        highestCase = todayTotalNewCases;
        highestCaseDay = currentDay;
    }
    if (todayTotalNewCases <= lowestCase)
    {
        lowestCase = todayTotalNewCases;
        lowestCaseDay = currentDay;
    }

    printf("\nNo. of deaths  = ");
    fgets(usrInput, BUFFER_SIZE, stdin);
    validateInput(ERRCHK_NUMBER, usrInput);
    numOfDeaths = atoi(usrInput);

    printf("No. recovered = ");
    fgets(usrInput, BUFFER_SIZE, stdin);
    validateInput(ERRCHK_NUMBER, usrInput);
    numOfDischarged = atoi(usrInput);

    free(usrInput);
    usrInput = NULL;
}

struct dailyData calculation(struct dailyData prevTotal) {
    struct dailyData retVal;
    retVal.newCase = numOfNewImportedCases + numOfNewLocalCases;
    retVal.totalCase = numOfNewImportedCases + numOfNewLocalCases + prevTotal.totalCase;
    retVal.totalDeaths = numOfDeaths + prevTotal.totalDeaths;
    retVal.totalDischarged = numOfDischarged + prevTotal.totalDischarged;
    retVal.totalUnderTreatment = retVal.totalCase - retVal.totalDeaths - retVal.totalDischarged;
    retVal.deathPercentage = (float)retVal.totalDeaths / retVal.totalCase * 100;
    retVal.dischargedPercentage = (float)retVal.totalDischarged / retVal.totalCase * 100;
    retVal.treatmentPercentage = (float)retVal.totalUnderTreatment / retVal.totalCase * 100;
    return retVal;
}

void printYesterdayTotal(int currentDay, struct dailyData prevDay) {
    printf("-------------------------COVID-19 CASES Tracking System-------------------------\n");
    printf("                    Yesterday's Total - (Day %d):\n", currentDay - 1);
    printf("+---------------+---------------++---------------+---------------+---------------+\n");
    printf("|%-15s|%-15s||%-15s|%-15s|%-15s|\n", "Yesterday's", "Total", "Total", "Total", "Under");
    printf("|%-15s|%-15s||%-15s|%-15s|%-15s|\n", "Cases", "Cases", "Deaths", "Recovered", "Treatment");
    printf("+---------------+---------------++---------------+---------------+---------------+\n");
    printf("|%15d|%15d||%15d|%15d|%15d|\n", prevDay.newCase, prevDay.totalCase, prevDay.totalDeaths, prevDay.totalDischarged, prevDay.totalUnderTreatment);
    printf("+---------------+---------------++---------------+---------------+---------------+\n");
    printf("%32s||%14.1f%%|%14.1f%%|%14.1f%%|\n", " ", prevDay.deathPercentage, prevDay.dischargedPercentage, prevDay.treatmentPercentage);
    printf("                                ++---------------+---------------+---------------+\n\n");
}

void printDailySummaryReport(struct dailyData newData) {
    printf("\nDay %i                     DAILY SUMMARY REPORT\n", currentDay);
    printf("+---------------+---------------++---------------+---------------+---------------+\n");
    printf("|%15s|%-15s||%-15s|%-15s|%-15s|\n", "Today's", "Total", "Total", "Total", "Under");
    printf("|%15s|%-15s||%-15s|%-15s|%-15s|\n", "Cases", "Cases", "Deaths", "Recovered", "Treatment");
    printf("+---------------+---------------++---------------+---------------+---------------+\n");
    printf("|%-8s%7d|%15s||%15s|%15s|%15s|\n", "Local", numOfNewLocalCases, " ", " ", " ", " ");
    printf("|%-8s%7d|%15s||%15s|%15s|%15s|\n", "Imported", numOfNewImportedCases, " ", " ", " ", " ");
    printf("|%15d|%15d||%15d|%15d|%15d|\n", (numOfNewLocalCases + numOfNewImportedCases), newData.totalCase, newData.totalDeaths, newData.totalDischarged, newData.totalUnderTreatment);
    printf("+---------------+---------------++---------------+---------------+---------------+\n");
    printf("%32s||%14.1f%%|%14.1f%%|%14.1f%%|\n", " ", newData.deathPercentage, newData.dischargedPercentage, newData.treatmentPercentage);
    printf("                                ++---------------+---------------+---------------+\n\n");
}

void printDailyComparativeReport(struct dailyData prevDay, struct dailyData newData) {
    printf("                            DAILY COMPARATIVE REPORT\n");
    printf("                            +---------------+---------------++----------+");
    printf("\n %27s|%15s|%15s||%10s|\n", " ", "YESTERDAY", "TODAY", "DIFFRENCE");
    printf("%28s|%9sDay  %i|", " ", " ", currentDay - 1);
    printf("%8sDay  %i||", " ", currentDay);
    printf("%10s|\n", " ");
    int diff = (numOfNewLocalCases + numOfNewImportedCases) - prevDay.newCase;
    printf("+---------------------------+---------------+---------------++----------+\n");
    printf("|%27s|%8s%7d|%8s%7d||\t[%d]\t|\n", "New Cases", " ", prevDay.newCase, " ", (numOfNewLocalCases + numOfNewImportedCases), diff);
    printf("+---------------------------+---------------+---------------++----------+\n");
    printf("|%27s|%8s%7d|%8s%7d||\t[%d]\t|\n", "Total Cases", " ", prevDay.totalCase, " ", newData.totalCase, (newData.totalCase - prevDay.totalCase));
    printf("+---------------------------+---------------+---------------++----------+\n");
    printf("|%27s|%14.1f%%|%14.1f%%||\t[%.1f%%]\t|\n", "Death Rate", prevDay.deathPercentage, newData.deathPercentage, (newData.deathPercentage - prevDay.deathPercentage));
    printf("+---------------------------+---------------+---------------++----------+\n");
    printf("|%27s|%14.1f%%|%14.1f%%||\t[%.1f%%]\t|\n", "Recovery Rate", prevDay.dischargedPercentage, newData.dischargedPercentage, (newData.dischargedPercentage - prevDay.dischargedPercentage));
    printf("+---------------------------+---------------+---------------++----------+\n\n");
}

//validate input
void validateInput(char* type, char* input)
{
    if (strlen(input) >= 1 && input[strlen(input) - 1] == '\n')
        input[strlen(input) - 1] = '\0';

    if (strcmp(type, ERRCHK_MENU) == 0)
        while (input[0] < 49 || input[0] > 55 || strlen(input) != 1)
        {
            printf("Incorrect input, please try again!");
            fgets(input, 256, stdin);
            if (strlen(input) >= 1 && input[strlen(input) - 1] == '\n')
                input[strlen(input) - 1] = '\0';
        }
    else if (strcmp(type, ERRCHK_NUMBER) == 0)
    {
        int hasError = 0;
        do
        {
            for (int i = 0; i < strlen(input); i++)
            {
                if (!isdigit(input[i]))
                {
                    hasError = 1;
                    break;
                }
                hasError = 0;
            }

            if (hasError)
            {
                printf("Incorrect input, please try again!");
                fgets(input, 256, stdin);
                if (strlen(input) >= 1 && input[strlen(input) - 1] == '\n')
                    input[strlen(input) - 1] = '\0';
            }
        } while (hasError);
    }

}