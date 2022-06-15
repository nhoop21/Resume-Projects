#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct WeatherInfo
{
    int temperature; // 60-79 fahrenheit ** This won't affect race result. just added to look like real weather info. if it is rainy or cloudy the temperature is automatically under 70 degrees. If it is sunny the temp is between 60 - 79.
    int generalInfo; // 0. cloudy /1. sunny/ 2. rain ** this generates different track condition. "cloudy and sunny => dry", "rain =>wet" **
};

struct Horse
{
    char *name;
    float multiplier;
    char *strong_track;
    int past_winning_rate;
};

struct RaceResult
{
    int firstPlace;
    int secondPlace;
    int thirdPlace;
};
    
// Medina Spirit -> HORSE A
float GetMultiplier_HorseA (int weather_num) {
    float num_mult = 1.15; //the number after the decimal for this first var is the win% of that horse .
    if (weather_num > 1) { //strong track condition = dry
        num_mult = num_mult * 1.15;
    }
    else { //weak track condition
        num_mult = num_mult * 0.98;
    }
    return num_mult;
}

//Justify -> HORSE B
float GetMultiplier_HorseB (int weather_num) {
    float num_mult = 1.15; //the number after the decimal for this first var is the win% of that horse .
    if (weather_num < 2) { //strong track condition = wet
        num_mult = num_mult *1.1;
    }
    else { //weak track condition
        num_mult = num_mult * 0.95;
    }
    return num_mult;
}

//Nyquist -> HORSE C
float GetMultiplier_HorseC (int weather_num) {
    float num_mult = 1.10;
    if (weather_num > 1) {//strong track condition = dry
        num_mult = num_mult *1.15;
    }
    else {
        num_mult = num_mult * 0.96;
    }
    return num_mult;
}

//American Pharaoh -> HORSE D
float GetMultiplier_HorseD (int weather_num) {
    float num_mult = 1.10;
    if (weather_num < 2) {//strong track condition = wet
        num_mult = num_mult *1.11;
    }
    else {
        num_mult = num_mult * 0.95;
    }
    return num_mult;
}

//California Chrome -> HORSE E
float GetMultiplier_HorseE (int weather_num) {
    float num_mult = 1.08;
    if (weather_num > 1) {//strong track condition = dry
        num_mult = num_mult *1.15;
    }
    else { //weak track condition
        num_mult = num_mult * 0.93;
    }
    return num_mult;
}

//Authentic -> HORSE F
float GetMultiplier_HorseF (int weather_num) {
    float num_mult = 1.07;
    if (weather_num < 2) {//strong track condition = wet
        num_mult = num_mult *1.13;
    }
    else { //weak track condition
        num_mult = num_mult * 0.92;
    }
    return num_mult;
}

//Country House -> HORSE G
float GetMultiplier_HorseG (int weather_num) {
    float num_mult = 1.06;
    if (weather_num < 2) {//strong track condition = wet
        num_mult = num_mult * 1.14;
    }
    else {
        num_mult = num_mult * 0.99;
    }
    return num_mult;
}

//Always Dreaming -> HORSE H
float GetMultiplier_HorseH (int weather_num) {
    float num_mult = 1.05;
    if (weather_num < 2)  {//strong track condition = wet
        num_mult = num_mult *1.15;
    }
    else { //weak track condition
        num_mult = num_mult * 0.99;
    }
    return num_mult;
}
    
//Orb -> HORSE I
float GetMultiplier_HorseI (int weather_num) {
    float num_mult = 1.04;
    if (weather_num > 1) { //strong track condition = dry
        num_mult = num_mult *1.15;
    }
    else { //weak track condition
        num_mult = num_mult + 0.94;
    }
    return num_mult;
}

//Animal Kingdom -> HORSE J
float GetMultiplier_HorseJ (int weather_num) {
    float num_mult = 1.03;
    if (weather_num < 2) {//strong track condition = wet
        num_mult = num_mult *1.17;
    }
    else { //weak track condition
        num_mult = num_mult + 0.04;
    }
    return num_mult;
}

float HorseConditionRandomGenerator(float multiplier)
{
    float winning_rate = 0;
    int horse_condition;
    
    horse_condition = rand() % 4; //Variation not given to user
    switch (horse_condition)
    {
        case 0:// Excellent
            winning_rate = multiplier * 1.15;
            break;
            
        case 1:// Good
            winning_rate = multiplier * 1.05;
            break;
            
        case 2://Bad
            winning_rate = multiplier * 0.95;
            break;
            
        case 3:// Worst
            winning_rate = multiplier * 0.85;
            break;
    }
    return winning_rate;
}

//the sorting algorithm here was based off of Pankaj Prakash's ascending sort from codeforwin.com.
struct RaceResult GetRaceResult(float lane1_horse_multiplier,
                                float lane2_horse_multiplier,
                                float lane3_horse_multiplier,
                                float lane4_horse_multiplier,
                                float lane5_horse_multiplier) {
    
    struct RaceResult race_result = {0, 0, 0};
    
    float winning_rate_arr[5];
    winning_rate_arr[0] = HorseConditionRandomGenerator(lane1_horse_multiplier);
    winning_rate_arr[1] = HorseConditionRandomGenerator(lane2_horse_multiplier);
    winning_rate_arr[2] = HorseConditionRandomGenerator(lane3_horse_multiplier);
    winning_rate_arr[3] = HorseConditionRandomGenerator(lane4_horse_multiplier);
    winning_rate_arr[4] = HorseConditionRandomGenerator(lane5_horse_multiplier);
    
    float pre_sort_arr[5];
    int i;

    for (i=0; i<5; i++)
    {
        pre_sort_arr[i] = winning_rate_arr[i]; //copy the entire array
    }
    
    int j;
    float temp;
   
    
    for(i=0; i<5; i++) {
        /*
         * Place currently selected element array[i]
         * to its correct place.
         */
        for(j=i+1; j<5; j++) {
            /*
             * Swap if currently selected array element
             * is not at its correct position.
             */
            if(winning_rate_arr[i] > winning_rate_arr[j])
            {
                temp = winning_rate_arr[i];
                winning_rate_arr[i] = winning_rate_arr[j];
                winning_rate_arr[j] = temp;
            }
        }
    }

    
    //Now, sorted in ascending order. extract from the largest index
    for(i = 0; i < 5; i++)
    {
        if (winning_rate_arr[4] == pre_sort_arr[i]) //largest number
        {
            race_result.firstPlace = i + 1; // because lane number is 1 greater than index
        }
        else if (winning_rate_arr[3] == pre_sort_arr[i]) //second largest number
        {
            race_result.secondPlace = i + 1;
        }
        else if (winning_rate_arr[2] == pre_sort_arr[i]) //third largest number
        {
            race_result.thirdPlace = i + 1;
        }
    }
    return race_result;
}

int main()
{
    int SeedGold = 50; //starting amount of gold is 50 --> why it is initalized
    int TotalGold;
    int BettingType;
    int HorseSelectedforWIN;
    int HorseSelectedforPLACE;
    int HorseSelectedforSHOW;
    int BettingGold;
    int WinningGold;
    int firstwinner;
    int secondwinner;
    int thirdwinner;
    int a;
    char b;
    int repeat;
    int i, j;
    int randomNumber;
    int duplicate;
    
    int weatherRequest;
    struct WeatherInfo weatherToday;
    srand(time(NULL));
    
// horse information and winning rate
    struct Horse horse[10];
    horse[0].name = "Medina Spirit";
    horse[0].strong_track = "wet";
    horse[0].past_winning_rate = 15;
    
    horse[1].name = "Justify";
    horse[1].strong_track = "dry";
    horse[1].past_winning_rate = 15;
    
    horse[2].name = "Nyquist";
    horse[2].strong_track = "wet";
    horse[2].past_winning_rate = 10;
    
    horse[3].name = "American Pharaoh";
    horse[3].strong_track = "dry";
    horse[3].past_winning_rate =10;
    
    horse[4].name = "California Chrome";
    horse[4].strong_track = "wet";
    horse[4].past_winning_rate =8;
    
    horse[5].name = "Authentic";
    horse[5].strong_track = "dry";
    horse[5].past_winning_rate =7;
    
    horse[6].name = "Country House";
    horse[6].strong_track = "dry";
    horse[6].past_winning_rate =6;
    
    horse[7].name = "Always Dreaming";
    horse[7].strong_track = "dry";
    horse[7].past_winning_rate =5;
    
    horse[8].name = "Orb";
    horse[8].strong_track = "wet";
    horse[8].past_winning_rate =4;
    
    horse[9].name = "Animal Kingdom";
    horse[9].strong_track = "dry";
    horse[9].past_winning_rate =3;
    
    int racingHorseIndex[5] = {10, 10, 10, 10, 10}; //initialized to 10 because valid index is from 0 to 9 and to avoid garbage values...
    struct RaceResult result;
    
    printf("\n");
    printf("___________________________________________________________________________________________________________\n");
    printf("Welcome to the UofL 2022 spring Horse Racing Game!!!\n");
    printf("Here is 50 Gold as a jumpstart. Please enjoy the game!!!\n");
    printf("___________________________________________________________________________________________________________\n");
    printf("\n");
    printf("\n");
    //printf("\n");
    printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
    printf("YOU HAVE %d GOLD\n", SeedGold);
    printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
    printf("\n");
    
    TotalGold = SeedGold;
    
    while (1)
    {
    
        weatherToday.generalInfo = rand() % 3;
        if (weatherToday.generalInfo = 0) {
            weatherToday.temperature = (rand() % 10) + 60;
        }
        else if (weatherToday.generalInfo = 1) {
            weatherToday.temperature = (rand() % 20) + 60;
        }
        else {
            weatherToday.temperature = (rand() % 10) + 60;
        }
        printf("___________________________________________________________________________________________________________\n");
        printf("The weather will affect the track condition and race result.\n");
        printf("To view the weather information for today's race, you must pay 5 gold. \n");
        printf("If you would like to view the weather info, please enter '1'. If not, please enter any other number: ");
        scanf("%d", &weatherRequest);
        printf("___________________________________________________________________________________________________________\n");
        
        if (weatherRequest == 1) //user requested weather info
        {
            TotalGold  = TotalGold - 5;
            
            //printf("___________________________________________________________________________________________________________\n");
            printf("The temperature is %d degrees fahrenheit " ,weatherToday.temperature);
            
            if ( weatherToday.generalInfo == 0) //cloudy
            {
                printf("and it is cloudy. \n");
                printf("The racing track is dry.\n");
            }
            else if (weatherToday.generalInfo == 1) //sunny
            {
                printf("and it is sunny.\n");
                printf("The racing track is dry.\n");
            }
            else if (weatherToday.generalInfo == 2) // rainy
            {
                printf("and it is rainy.\n");
                printf("The racing track is wet.\n");
            }
            printf("___________________________________________________________________________________________________________\n");
            printf("\n");
            printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
            printf("YOU NOW HAVE %d GOLD\n", TotalGold);
            printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
            printf("\n");
            printf("___________________________________________________________________________________________________________\n");
        }
        
        horse[0].multiplier = GetMultiplier_HorseA(weatherToday.generalInfo);
        horse[1].multiplier = GetMultiplier_HorseB(weatherToday.generalInfo);
        horse[2].multiplier = GetMultiplier_HorseC(weatherToday.generalInfo);
        horse[3].multiplier = GetMultiplier_HorseD(weatherToday.generalInfo);
        horse[4].multiplier = GetMultiplier_HorseE(weatherToday.generalInfo);
        horse[5].multiplier = GetMultiplier_HorseF(weatherToday.generalInfo);
        horse[6].multiplier = GetMultiplier_HorseG(weatherToday.generalInfo);
        horse[7].multiplier = GetMultiplier_HorseH(weatherToday.generalInfo);
        horse[8].multiplier = GetMultiplier_HorseI(weatherToday.generalInfo);
        horse[9].multiplier = GetMultiplier_HorseJ(weatherToday.generalInfo);
        
        printf("Please enter any number to view the horse racing lineup & betting type: ");
        scanf("%s",&b);        //for pause purpose
        
        i = 0;
        while (i < 5)// randomly selecting 5 horses from the 10 horse pool.
        {
            randomNumber = rand() % 10;
            duplicate = 0;
            
            for (j=0; j<5; j++) {
                if (randomNumber == racingHorseIndex[j]) {
                    duplicate = 1;
                }
            }
            
            if (duplicate != 1) {
                racingHorseIndex[i] = randomNumber;
                i++;
            }
        }
        
        printf("\nHORSE LINEUP\n");
        printf("Lane 1: %s | Winning rate: %d percent | Strong track: %s\n", horse[racingHorseIndex[0]].name, horse[racingHorseIndex[0]].past_winning_rate, horse[racingHorseIndex[0]].strong_track);
        printf("Lane 2: %s | Winning rate: %d percent | Strong track: %s\n", horse[racingHorseIndex[1]].name, horse[racingHorseIndex[1]].past_winning_rate, horse[racingHorseIndex[1]].strong_track);
        printf("Lane 3: %s | Winning rate: %d percent | Strong track: %s\n", horse[racingHorseIndex[2]].name, horse[racingHorseIndex[2]].past_winning_rate, horse[racingHorseIndex[2]].strong_track);
        printf("Lane 4: %s | Winning rate: %d percent | Strong track: %s\n", horse[racingHorseIndex[3]].name, horse[racingHorseIndex[3]].past_winning_rate, horse[racingHorseIndex[3]].strong_track);
        printf("Lane 5: %s | Winning rate: %d percent | Strong track: %s\n", horse[racingHorseIndex[4]].name, horse[racingHorseIndex[4]].past_winning_rate, horse[racingHorseIndex[4]].strong_track);
        //printf("___________________________________________________________________________________________________________\n");
        
        printf("\nBETTING TYPE\n");
        printf("WIN: Your selected horse needs to win the race. This option quintuples your bet!\n");
        printf("PLACE: Your selected horse needs to finish in either 1st or 2nd place. This option triples your bet!\n");
        printf("SHOW: Your selected horse needs to finish in either 1st, 2nd, or 3rd place. This option doubles your bet!");
        printf("\n___________________________________________________________________________________________________________");
        printf("\n");
        
        printf("Please enter your desired betting type. Enter '1' for WIN, '2' for PLACE, or '3' for SHOW: ");
        scanf("%d", &BettingType);
        printf("\nPlease enter how much gold you want to bet (Minimum: 2 gold, Maximum: %d gold): ", TotalGold);
        scanf("%d", &BettingGold);
        TotalGold = TotalGold - BettingGold;
        //        printf("Now you have %d Gold\n", TotalGold);
        printf("\n");
        
        result = GetRaceResult(horse[racingHorseIndex[0]].multiplier, horse[racingHorseIndex[1]].multiplier, horse[racingHorseIndex[2]].multiplier, horse[racingHorseIndex[3]].multiplier, horse[racingHorseIndex[4]].multiplier);
        
        if(BettingType == 1) //WIN
        {
            printf("Please enter the lane number of your desired horse for WIN type betting (1~5): ");
            scanf("%d", &HorseSelectedforWIN);
            printf("\nTHE RACE HAS STARTED!!!\n");
            printf("\nPlease enter any number to see the result... "); //to delay
            scanf("%d", &a);
            scanf("%c", &b);
            firstwinner = result.firstPlace;
            printf("\n");
            printf("___________________________Race Result______________________________\n");
            printf("Horse number %d finished the race in 1st place.\n", firstwinner);
            printf("___________________________________________________________________________________________________________\n");
            printf("\n");
            if (HorseSelectedforWIN == firstwinner)
            {
                WinningGold = BettingGold * 5;
                TotalGold = WinningGold + TotalGold;
                printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
                printf("Congratulations!!! Your selected horse finished in 1st place. You won %d Gold...\n", WinningGold);
                printf("YOU NOW HAVE %d GOLD\n", TotalGold);
                printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
            }
            else
            {
                printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
                printf("Your selected horse did not finish in 1st place. You lost %d Gold...\n", BettingGold);
                printf("YOU NOW HAVE %d GOLD\n", TotalGold);
                printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
            }
            
        }
        else if(BettingType == 2) //PLACE
        {
            printf("Please enter the lane number of your desired horse for PLACE type betting (1~5): ");
            scanf("%d", &HorseSelectedforPLACE);
            printf("\nTHE RACE HAS STARTED!!!\n");
            printf("\nPlease enter any number to see the result... ");
            scanf("%d", &a);
            scanf("%c", &b);
            firstwinner = result.firstPlace;
            secondwinner = result.secondPlace;
            printf("\n");
            printf("___________________________Race Result______________________________\n");
            printf("Horse number %d finished the race in 1st place.\n", firstwinner);
            printf("Horse number %d finished the race in 2nd place.\n", secondwinner);
            printf("___________________________________________________________________________________________________________\n");
            printf("\n");
            
            if (HorseSelectedforPLACE == firstwinner || HorseSelectedforPLACE == secondwinner)
            {
                WinningGold = BettingGold * 3;
                TotalGold = WinningGold + TotalGold;
                printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
                printf("Congratulations!!! Your selected horse finished in 1st or 2nd place. You won %d Gold...\n", WinningGold);
                printf("YOU NOW HAVE %d GOLD\n", TotalGold);
                printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
            }
            else
            {
                printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
                printf("Your selected horse did not finish in 1st or 2nd place. You lost %d Gold...\n", BettingGold);
                printf("YOU NOW HAVE %d GOLD\n", TotalGold);
                printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
            }
        }
        else if(BettingType == 3) //SHOW
        {
            printf("Please enter the lane number of your desired horse for SHOW type betting (1~5): ");
            scanf("%d", &HorseSelectedforSHOW);
            printf("\nTHE RACE HAS STARTED!!!\n");
            printf("\nPlease enter any number to see the result... ");
            scanf("%d", &a);
            scanf("%c", &b);
            firstwinner = result.firstPlace;
            secondwinner = result.secondPlace;
            thirdwinner = result.thirdPlace;
            printf("\n");
            printf("___________________________Race Result______________________________\n");
            printf("Horse number %d finished the race in 1st place.\n", firstwinner);
            printf("Horse number %d finished the race in 2nd place.\n", secondwinner);
            printf("Horse number %d finished the race in 3rd place.\n", thirdwinner);
            printf("___________________________________________________________________________________________________________\n");
            printf("\n");
            if (HorseSelectedforSHOW == firstwinner || HorseSelectedforSHOW == secondwinner || HorseSelectedforSHOW == thirdwinner)
            {
                WinningGold = BettingGold * 2;
                TotalGold = WinningGold + TotalGold;
                printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
                printf("Congratulations!!! Your selected horse finished in 1st, 2nd, or 3rd place. You won %d Gold...\n", WinningGold);
                printf("YOU NOW HAVE %d GOLD\n", TotalGold);
                printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
            }
            else
            {
                printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
                printf("Your selected horse did not finish in 1st, 2nd, or 3rd place. You lost %d Gold...\n", BettingGold);
                printf("YOU NOW HAVE %d GOLD\n",TotalGold);
                printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
            }
        }
        
        printf("\nWould you like to play again? Enter '1' for yes or '2' for no: ");
        scanf("%d",&repeat);
        if (repeat == 1)
        {
            continue;
        }
        else
        {
            printf("\nThanks for playing the UofL 2022 spring Horse Racing Game!!!\n");
            break;
        }
    }
    return 0;
}
