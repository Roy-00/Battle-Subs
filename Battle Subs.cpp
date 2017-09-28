//Brandon Roy Comp Sci I 12/1/16
/*
Example: Input depth charger location: 3 4
*/

#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cstring>
#include <vector>
using namespace std;

bool DEBUG = false;

const int r = 10, c = 10;
char ocean[r][c];
int Max_Drops = 76, drop_count = 0;
const int MAX_SUBS = 5;
bool INVOKE_WIN = false;
int shortest = 10;
int input_r = 0, input_c = 0;
int dist;

struct Location
{
    int row;
    int column;
};

vector<Location> subs_list(MAX_SUBS);
vector<Location> drop_list(Max_Drops);

void No_Win_Game_Over(); //Prototype
void Good_Win_Game_Over();
bool Depth_Charger(int input_r, int input_c);
int List_of_Drops();
int Sonar();

//*************************************************************************************************************************
void Initialize_Ocean()
{
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            ocean[i][j] = '.';
        }
    }
}
//*************************************************************************************************************************
void Show_Game_Board()
{
    cout << "  ";
    for (int i = 0; i < c; i++)
    {
        cout << i << " ";
    }
    cout << endl;

    for (int i = 0; i < r; i++)
    {
        cout << i << " ";
        for (int j = 0; j < c; j++)
        {
            if (DEBUG == true)
                cout << ocean[i][j] << " ";
            if (DEBUG == false)
                cout << '.' << " ";
        }
        cout << i << endl;
    }

    cout << "  ";
    for (int i = 0; i < c; i++)
    {
        cout << i << " ";
    }
    cout << endl;
}
//*************************************************************************************************************************
void Update_Game_Board()
{
    cout << "  ";
    for (int i = 0; i < c; i++)
    {
        cout << i << " ";
    }
    cout << endl;

    if (Depth_Charger(input_r, input_c) == false && ocean[input_r][input_c] != '#')
    {
        char c = '0'+ shortest;
        ocean[input_r][input_c] = c;
    }

    for (int i = 0; i < r; i++)
    {
        cout << i << " ";
        for (int j = 0; j < c; j++)
        {
            if (DEBUG == true)
            {
                cout << ocean[i][j] << " ";
            }
            if (DEBUG == false)
            {
                if (ocean[i][j] == 'S')
                    cout << '.' << " ";
                else
                    cout << ocean[i][j] << " ";
            }
        }
        cout << i << endl;
    }

    cout << "  ";
    for (int i = 0; i < c; i++)
    {
        cout << i << " ";
    }
    cout << endl;
}
//*************************************************************************************************************************
int Total_Subs_Remaining()
{
    int tracking_total_subs = 0;
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            if (ocean[i][j] == 'S')
                tracking_total_subs++;
        }
    }
    if (tracking_total_subs == 0)
        INVOKE_WIN = true;

    return tracking_total_subs;
}
//*************************************************************************************************************************
int Insert_Sub_Locations()
{
    srand(time(0));
    int subs_spawned = 0;
    while (subs_spawned < MAX_SUBS)
    {
        subs_list.at(subs_spawned).row = rand() % r;
        subs_list.at(subs_spawned).column = rand() % c;
        if (ocean[r][c] != 'S')
        {
            ocean[subs_list.at(subs_spawned).row][subs_list.at(subs_spawned).column] = 'S';
            subs_spawned++;
        }
    }
}
//*************************************************************************************************************************
bool Depth_Charger(int input_r, int input_c)
{
    if (ocean[input_r][input_c] == 'S')
    {
        ocean[input_r][input_c] = '#';
        return true;
    }
    else
        return false;
}
//*************************************************************************************************************************
int List_of_Drops()
{
    drop_list.at(drop_count).row = input_r;
    drop_list.at(drop_count).column = input_c;
    drop_count++;

}
//*************************************************************************************************************************
int Sonar()
{
    int sr, sc; // submarine coordinates
    if (subs_list.size() == 0)
        return 0;
    for (unsigned i = 0; i < subs_list.size(); i++)
        {
            sr = subs_list.at(i).row;
            sc = subs_list.at(i).column;
            dist = abs(abs(input_r - sr)+ abs(input_c - sc));
            if (dist < shortest)
                shortest = dist;
        }
}
//*************************************************************************************************************************
int main()
{
    cout << "MISSION: SEARCH AND DESTROY. DROP DEPTH CHARGERS AND SINK" << endl
         << "ALL ENEMY SUBMARINES IN YOUR SECTOR. GODSPEED." << endl << endl;

    Initialize_Ocean();
    Insert_Sub_Locations();
    Show_Game_Board();

    int x = 0;
    char surrender = 'N';
    while(surrender == 'N' || surrender == 'n')
    {
        cout << "Captain, enter location to drop depth charger: ";
        cin >> input_r >> input_c;
        while (input_r > r || input_c > c || input_r < 0 || input_c < 0)
        {
            cout << "Invalid Input. Captain, enter a valid location to drop depth charger: ";
            cin >> input_r >> input_c;
        }
        if (Depth_Charger(input_r, input_c) == true)
        {
            cout << "Executing Firing Point Procedures..." << endl;
            cout << "HIT! Enemy sub sunk!" << endl;
        }
        else
        {
            cout << "Executing Firing Point Procedures..." << endl;
            cout << "MISS. Reloading..." << endl;
            List_of_Drops();
        }
        cout << "Total Remaining Submarines: " << Total_Subs_Remaining() << endl;
        if (INVOKE_WIN == true)
            break;
        if (DEBUG == false)
        {
            cout << "Surrender? Y/N: ";
            cin >> surrender;
            while (surrender != 'Y' && surrender != 'N' && surrender != 'y' && surrender != 'n')
            {
                cout << "Invalid Input. Try Again: ";
                cin >> surrender;
            }
            if (surrender == 'y' || surrender == 'Y')
                break;
        }
        if (surrender == 'y' || surrender == 'Y')
            break;

        cout << endl;

        if (Depth_Charger(input_r, input_c) == false && ocean[input_r][input_c] != '#')
        {
            Sonar();
            cout << "SONAR detects an object " << shortest << " kilometers away." << endl;
        }
        if (Depth_Charger(input_r, input_c) == true && ocean[input_r][input_c] == '#')
            cout << " " << endl;

        Update_Game_Board();

        if (Depth_Charger(input_r, input_c) == false && ocean[input_r][input_c] != '#')
            ocean[input_r][input_c] = '.';

        shortest = 10; //So Sonar won't show same dist every time
    }
    if (INVOKE_WIN == true)
        Good_Win_Game_Over();
    if (surrender == 'y' || surrender == 'Y')
        No_Win_Game_Over();

    return 0;
}
//*************************************************************************************************************************
void No_Win_Game_Over()
{
    cout << endl;
    cout << "We have been sunk!" << endl;
    cout << "    GAME OVER     " << endl;
}
//*************************************************************************************************************************
void Good_Win_Game_Over()
{
    cout << endl;
    cout << "All enemy submarines eliminated!" << endl;
    cout << "            VICTORY             " << endl;
}
//*************************************************************************************************************************

//*************************************************************************************************************************

//*************************************************************************************************************************

//*************************************************************************************************************************

//*************************************************************************************************************************

//*************************************************************************************************************************

//*************************************************************************************************************************

//*************************************************************************************************************************

//*************************************************************************************************************************
