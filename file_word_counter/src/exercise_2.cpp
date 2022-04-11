
/*
11 players:

2 forward
0 mid-fielders
8 defender

1 goalkeeper

min 2 f_players max 9
min 1 d_players max 8
min 1 g_players max 1 

*/
// int count = combinations;
// min 2 f_players min 1 d_player
// mid_fielder ( min value possible to reach 11 )
// loop f_players >
//  

for (int i = 2; f_players > 9; i++ ) {
    nr_players = 1
// fplayers = 3
    for (int i = 1; d_players > 8; i++) {
        nr_players++;
        combinations++;

        while  ( combinations++ < 11 ) {
            combinations++;
            nr_players++;
        }

    }
}

/*

bill_Arr = {2,5,10,20,50}

input = price 

min bill combination

O(n) 

User input:
billsArr = {20,10,5,50}

std::orderedmap ( O(n) )

billPrice = 35€



if 1st ele is smaller than bill price
    if last ele is smaller than bill price
        Loop 




*/




