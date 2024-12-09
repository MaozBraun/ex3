/******************
Name:Maoz Braun
ID:324978428
Assignment: ex3
*******************/

#include <stdio.h>

#define NUM_OF_BRANDS 5
#define BRANDS_NAMES 15
#define NUM_OF_TYPES 4
#define TYPES_NAMES 10
#define DAYS_IN_YEAR 365
#define addOne 1
#define addAll 2
#define stats 3
#define print 4
#define insights 5
#define deltas 6
#define done 7

char brands[NUM_OF_BRANDS][BRANDS_NAMES] = {"Toyoga", "HyunNight", "Mazduh", "FolksVegan", "Key-Yuh"};
char types[NUM_OF_TYPES][TYPES_NAMES] = {"SUV", "Sedan", "Coupe", "GT"};
// difine a array of 5 number that equales 0
int days[NUM_OF_BRANDS] = {0};
int complete[NUM_OF_BRANDS] = {0};
int Checkday[DAYS_IN_YEAR] = {0};
// difine the function InitializeArray.
void InitializeArray(int arr[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]);
void printMenu();
void PrintArr(int arr[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]);
void populate(int arr[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int brand, int SUV_sales, int Sedan_sales, int Coupe_sales, int GT_sales, int day);
void Numcheck(int brand, int SUV_sales, int Sedan_sales, int Coupe_sales, int GT_sales);
void sales_sum(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int day);
void sold_brand(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int day);
void sold_types(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int day);
void show_arr(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int day);
// int sales_sum_helper(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int day, int brand);
void sold_brand_helper(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int day);
void sold_types_helper(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int day);
void profitable_day(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int day);
void Average(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int days[NUM_OF_BRANDS]);
int main()
{
    int day = 0;
    int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES];
    int choice;
    printMenu();
    InitializeArray(cube);
    scanf("%d", &choice);
    while (choice != done)
    {
        int brand, SUV_sales, Sedan_sales, Coupe_sales, GT_sales;
        switch (choice)
        {
        case addOne:
        {
            printf("please enter a car brand index (between 0-4) followed by a series of 4 integers\n");
            scanf("%d %d %d %d %d", &brand, &SUV_sales, &Sedan_sales, &Coupe_sales, &GT_sales);
            while (brand < 0 || brand > NUM_OF_BRANDS || SUV_sales < 0 || Sedan_sales < 0 || Coupe_sales < 0 || GT_sales < 0)
            {
                printf("This brand is not valid");
                scanf("%d %d %d %d %d", &brand, &SUV_sales, &Sedan_sales, &Coupe_sales, &GT_sales);
            }
            populate(cube, brand, SUV_sales, Sedan_sales, Coupe_sales, GT_sales, day);
            PrintArr(cube);
            break;
        }
        case addAll:
        {
            int check = NUM_OF_BRANDS;
            printf("No data for brands Toyoga HyunNight Mazduh FolksVegan Key-Yuh Please complete the data\n");
            while (check > 0)
            {
                scanf("%d ", &brand);
                scanf("%d %d %d %d", &SUV_sales, &Sedan_sales, &Coupe_sales, &GT_sales);
                Numcheck(brand, SUV_sales, Sedan_sales, Coupe_sales, GT_sales);
                //  printf(" if (complete[brand] == 1) ==  %d\n", (complete[brand] == 1));
                while (complete[brand] == 1)
                {
                    printf("Data for this brand is already entered!\n");
                    scanf("%d %d %d %d %d", &brand, &SUV_sales, &Sedan_sales, &Coupe_sales, &GT_sales);
                }
                Numcheck(brand, SUV_sales, Sedan_sales, Coupe_sales, GT_sales);
                populate(cube, brand, SUV_sales, Sedan_sales, Coupe_sales, GT_sales, day);
                check--;
                // printf("CHECK: %d", check);

                //  printf("check valiue:  %d", check);

                if (check > 0)
                {
                    printf("No data for brands ");

                    for (int i = 0; i < NUM_OF_BRANDS; i++)
                    {
                        if (complete[i] == 0)
                        {
                            printf("%s ", brands[i]);
                        }
                    }
                }
                if (check > 0)
                {
                    printf("\nPlease complete the data.\n");
                }
            }
            // PrintArr(cube);
            Checkday[day - 1] = 1;
            day++;
            //printf("day: %d\n", day);
            for (int i = 0; i < NUM_OF_BRANDS; i++)
            {
                complete[i] = 0;
            }

            break;
        }
        case stats:
        {
            int usersDay;
            printf("What day would you like to analyze?:\n");
            scanf("%d", &usersDay);
            while (usersDay > DAYS_IN_YEAR || usersDay < 1 || usersDay > day)
            { //Checkday[usersDay - 1] == 0
                printf("Please enter a valid day.\n Which day would you like to analyze?\n");
                scanf(" %d", &usersDay);
            }
            printf("In day number %d:\n", usersDay);
            sales_sum(cube, (usersDay - 1));
            sold_brand(cube, (usersDay - 1));
            sold_types(cube, (usersDay - 1));
            break;
        }
        case print:
        {
            printf("*****************************************\n\n");
             //printf("days: %d\n", day);
            show_arr(cube, day);
            printf("\n");
            printf("*****************************************\n");
            break;
        }
        case insights:
        {
            sold_brand_helper(cube, day);
            sold_types_helper(cube, day);
            profitable_day(cube, day);
            break;
        }
        case deltas:
        {
            //printf("fuck");
            Average(cube, days);

            break;
        }
        default:
            printf("Invalid input\n");
        }
        printMenu();
        scanf("%d", &choice);
    }
    printf("Goodbye!\n");
    return 0;
}

void printMenu()
{
    printf("Welcome to the Cars Data Cube! What would you like to do?\n"
           "1.Enter Daily Data For A Brand\n"
           "2.Populate A Day Of Sales For All Brands\n"
           "3.Provide Daily Stats\n"
           "4.Print All Data\n"
           "5.Provide Overall (simple) Insights\n"
           "6.Provide Average Delta Metrics\n"
           "7.exit\n");
}

void InitializeArray(int arr[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES])
{
    for (int i = 0; i < DAYS_IN_YEAR; i++)
    {
        for (int j = 0; j < NUM_OF_BRANDS; j++)
        {
            for (int k = 0; k < NUM_OF_TYPES; k++)
            {
                arr[i][j][k] = -1;
            }
        }
    }
}
void PrintArr(int arr[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES])
{
    printf("Sales Data:\n");
    for (int i = 0; i < DAYS_IN_YEAR; i++)
    {
        for (int j = 0; j < NUM_OF_BRANDS; j++)
        {
            printf("Day: %d, Brand: %d: ", i, j);
            for (int k = 0; k < NUM_OF_TYPES; k++)
                printf("%d ", arr[i][j][k]);
            printf("\n");
        }
    }
}
void populate(int arr[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int brand, int SUV_sales, int Sedan_sales, int Coupe_sales, int GT_sales, int day)
{
    arr[day][brand][0] = SUV_sales;
    arr[day][brand][1] = Sedan_sales;
    arr[day][brand][2] = Coupe_sales;
    arr[day][brand][3] = GT_sales;
    days[brand]++;
    complete[brand] = 1;
}
void Numcheck(int brand, int SUV_sales, int Sedan_sales, int Coupe_sales, int GT_sales)
{
    while (brand < 0 || brand > NUM_OF_BRANDS)
    {
        printf("This brand is not valid\n");
        scanf("%d %d %d %d %d", &brand, &SUV_sales, &Sedan_sales, &Coupe_sales, &GT_sales);
    }
    while (SUV_sales < 0 || Sedan_sales < 0 || Coupe_sales < 0 || GT_sales < 0)
    {
        printf("Please enter a valid num for sales.\n");
        scanf("%d %d %d %d %d", &brand, &SUV_sales, &Sedan_sales, &Coupe_sales, &GT_sales);
    }
}

void sales_sum(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int usersDay)
{
    int sum = 0;
    for (int i = 0; i < NUM_OF_BRANDS; i++)
    {
        for (int j = 0; j < NUM_OF_TYPES; j++)
        {
            sum += cube[usersDay][i][j];
        }
    }
    printf("The sales total was %d\n", sum);
}
void sold_brand(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int usersDay)
{
    int max_sales = 0;
    int best_brand = -1;
    for (int i = 0; i < NUM_OF_BRANDS; i++)
    {
        int total_sales = 0;
        for (int j = 0; j < NUM_OF_TYPES; j++)
        {
            total_sales += cube[usersDay][i][j];
        }
        if (total_sales > max_sales)
        {
            max_sales = total_sales;
            best_brand = i;
        }
    }
    if (best_brand != -1)
    {
        printf("The best sold brand with %d sales was %s\n", max_sales, brands[best_brand]);
    }
}
void sold_types(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int usersDay)
{
    int max_type = 0;
    int best_type = 0;
    for (int j = 0; j < NUM_OF_TYPES; j++)
    {
        int type_sales = 0;
        for (int i = 0; i < NUM_OF_BRANDS; i++)
        {
            type_sales += cube[usersDay][i][j];
        }
        if (type_sales > max_type)
        {
            max_type = type_sales;
            best_type = j;
        }
    }
    printf("The best sold type with %d sales was %s\n", max_type, types[best_type]);
}
void show_arr(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int day)
{
    printf("daysygyh: %d\n", day);
    for (int i = 0; i < NUM_OF_BRANDS; i++)
    {
        printf("Sales for %s:\n", brands[i]);
        for (int j = 0; j < day; j++)
        {
            printf("Day %d-", j + 1);
            for (int k = 0; k < NUM_OF_TYPES; k++)
            {
                printf("%s: %d ", types[k], cube[j][i][k]);
            }
            printf("\n");
        }
    }
}
// int sales_sum_helper(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int day, int brand)
//{
//   int sum = 0, brand_sales = 0;
// for (int i = 0; i < NUM_OF_TYPES; i++)
//{
//   brand_sales += cube[day][brand][i];
//}
// sum += brand_sales;

// return brand_sales;
//}
void sold_brand_helper(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int day)
{
    int max_sales = 0, best_brand = -1, total_sales = 0;
    for (int i = 0; i < NUM_OF_BRANDS; i++)
    {
        for (int j = 0; j < NUM_OF_TYPES; j++)
        {
            for (int k = 0; k < day; k++)
            {
                total_sales += cube[k][i][j];
            }
        }
        if (total_sales > max_sales)
        {
            max_sales = total_sales;
            best_brand = i;
        }
        total_sales = 0;
    }
    printf("The best-selling brand overall is %s:%d$\n", brands[best_brand], max_sales);
}

void sold_types_helper(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int day)
{
    int max_sales = 0, best_type = -1, total_sales = 0;
    for (int i = 0; i < NUM_OF_TYPES; i++)
    {
        for (int j = 0; j < NUM_OF_BRANDS; j++)
        {
            for (int k = 0; k < day; k++)
            {
                total_sales += cube[k][j][i];
            }
        }
        if (total_sales > max_sales)
        {
            max_sales = total_sales;
            best_type = i;
        }
        total_sales = 0;
    }
    printf("The best-selling type overall is %s:%d$\n", types[best_type], max_sales);
}

void profitable_day(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int day)
{
    //printf("days: %d\n", day);
    int max_sales = 0, best_day = -1, total_sales = 0;
    for (int i = 0; i < day; i++)
    {
        for (int j = 0; j < NUM_OF_BRANDS; j++)
        {
            for (int k = 0; k < NUM_OF_TYPES; k++)
            {
                total_sales += cube[i][j][k];
            }
        }
        if (total_sales > max_sales)
        {
            max_sales = total_sales;
            best_day = i;
        }
        total_sales = 0;
    }
    int profit_day = best_day + 1;
    printf("The most profitable day was day number %d:%d$\n", profit_day, max_sales);
}

void Average(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int days[NUM_OF_BRANDS])
{
    float average = 0;
    for (int i = 0; i < NUM_OF_BRANDS; i++)
    {
        float delta = 0;
        for (int j = 0; j < NUM_OF_TYPES; j++)
        {
            for (int k = 0; k < days[i] - 1; k++)
            {
                delta += cube[k + 1][i][j] - cube[k][i][j];
            }
        }
        average = delta / (days[i] - 1);
        printf("Brand: %s, Average Delta: %.6f\n", brands[i], average);
    }
}