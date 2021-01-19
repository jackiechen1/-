#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string.h>
#include <vector>
#include <sstream>
#include <array>
#include <vector>

using namespace std;


double max_or_min(double array[], int end, int day, bool high_or_low);
void trends(double high, double low, double& cash, double open[], double& share, int day, string date[], bool& wait, bool& wait_change);
double raise_channel(double array[], int day, int start,int max_day,string date[],string price_type,int buyday,int sellday);
void quickSort(double arr[][3], int low, int high);
int main()
{
    int max = 2500; //max row

    fstream f;
    f.open("BTC.csv");
    string date[max], line, temp;
    double open[max], high[max], low[max], close[max];
    vector <string> row;
    int index = 0;
    getline(f, line); //get rid of first line 

    // read data 
    while (!f.eof())
    {
        row.clear();
        getline(f, line);
        stringstream s(line);
        while (s.good())
        {
            string substr;
            getline(s, substr, ',');
            row.push_back(substr);
        }
        date[index] = row[0];
        open[index] = stod(row[1]);
        high[index] = stod(row[2]);
        low[index] = stod(row[3]);
        close[index] = stod(row[4]);
        index++;
    }
    f.close();
    double final_dataset[3600][3];

    // btc 2315 row
    // eth 1991 row
    // try different trading stradgy
    // 1. buy and hold
    // 2. raise channel (trends)
    double ratio;
    ratio = raise_channel(open, 19, 0, 2314, date, " open price ", 19, 15);
    index = 0; // index for looping
    /*
    for (int i = 3; i < 60; i++) // buy backwards day
    {
        for (int j = 3; j < 60; j++) // sell backwards day
        {
            //cout << "Raise_channel method: Buy " << i << " Sell " << j <<" ";
            double ratio;
            ratio = raise_channel(open, 7,1852,2314, date, " open price ",i,j);
            // only use 80% data for training, rest of them for testing
            final_dataset[index][0] = ratio;
            final_dataset[index][1] = i;// buy date
            final_dataset[index][2] = j;// sell date
            index++;
        }
    }
    quickSort(final_dataset, 0, index);
    for (int i = index-1; i>index-101; i--)
    {
        //cout << final_dataset[i][0] <<" "<< final_dataset[i][1]<<" "<< final_dataset[i][2]<< endl;
    }*/
    /*
    for (int i = 0; i < index; i++)
    {
        if (final_dataset[i][1]==6 && final_dataset[i][2] == 3)
        {
            cout << final_dataset[i][0] << " " << final_dataset[i][1] << " " << final_dataset[i][2] << endl;
        }
        else if (final_dataset[i][1] == 6 && final_dataset[i][2] == 4)
        {
            cout << final_dataset[i][0] << " " << final_dataset[i][1] << " " << final_dataset[i][2] << endl;
        }
        else if (final_dataset[i][1] == 3 && final_dataset[i][2] == 4)
        {
            cout << final_dataset[i][0] << " " << final_dataset[i][1] << " " << final_dataset[i][2] << endl;
        }
        else if (final_dataset[i][1] == 6 && final_dataset[i][2] == 7)
        {
            cout << final_dataset[i][0] << " " << final_dataset[i][1] << " " << final_dataset[i][2] << endl;
        }
        else if (final_dataset[i][1] == 6 && final_dataset[i][2] == 6)
        {
            cout << final_dataset[i][0] << " " << final_dataset[i][1] << " " << final_dataset[i][2] << endl;
        }
        else if (final_dataset[i][1] == 6 && final_dataset[i][2] == 5)
        {
            cout << final_dataset[i][0] << " " << final_dataset[i][1] << " " << final_dataset[i][2] << endl;
        }
        else if (final_dataset[i][1] == 7 && final_dataset[i][2] == 3)
        {
            cout << final_dataset[i][0] << " " << final_dataset[i][1] << " " << final_dataset[i][2] << endl;
        }
        else if (final_dataset[i][1] == 18 && final_dataset[i][2] == 6)
        {
            cout << final_dataset[i][0] << " " << final_dataset[i][1] << " " << final_dataset[i][2] << endl;
        }
        else if (final_dataset[i][1] == 13 && final_dataset[i][2] == 6)
        {
            cout << final_dataset[i][0] << " " << final_dataset[i][1] << " " << final_dataset[i][2] << endl;
        }
        else if (final_dataset[i][1] == 18 && final_dataset[i][2] == 7)
        {
            cout << final_dataset[i][0] << " " << final_dataset[i][1] << " " << final_dataset[i][2] << endl;
        }
        else if (final_dataset[i][1] == 19 && final_dataset[i][2] == 15)
        {
            cout << final_dataset[i][0] << " " << final_dataset[i][1] << " " << final_dataset[i][2] << endl;
        }
        else if (final_dataset[i][1] == 19 && final_dataset[i][2] == 7)
        {
            cout << final_dataset[i][0] << " " << final_dataset[i][1] << " " << final_dataset[i][2] << endl;
        }
        else if (final_dataset[i][1] == 7 && final_dataset[i][2] == 4)
        {
            cout << final_dataset[i][0] << " " << final_dataset[i][1] << " " << final_dataset[i][2] << endl;
        }
        else if (final_dataset[i][1] == 13 && final_dataset[i][2] == 7)
        {
            cout << final_dataset[i][0] << " " << final_dataset[i][1] << " " << final_dataset[i][2] << endl;
        }
        else if (final_dataset[i][1] == 8 && final_dataset[i][2] == 3)
        {
            cout << final_dataset[i][0] << " " << final_dataset[i][1] << " " << final_dataset[i][2] << endl;
        }
        else if (final_dataset[i][1] == 19 && final_dataset[i][2] == 6)
        {
            cout << final_dataset[i][0] << " " << final_dataset[i][1] << " " << final_dataset[i][2] << endl;
        }
        else if (final_dataset[i][1] == 19 && final_dataset[i][2] == 9)
        {
            cout << final_dataset[i][0] << " " << final_dataset[i][1] << " " << final_dataset[i][2] << endl;
        }
        else if (final_dataset[i][1] == 16 && final_dataset[i][2] == 7)
        {
            cout << final_dataset[i][0] << " " << final_dataset[i][1] << " " << final_dataset[i][2] << endl;
        }
        else if (final_dataset[i][1] == 16 && final_dataset[i][2] == 6)
        {
            cout << final_dataset[i][0] << " " << final_dataset[i][1] << " " << final_dataset[i][2] << endl;
        }
        else if (final_dataset[i][1] == 19 && final_dataset[i][2] == 13)
        {
            cout << final_dataset[i][0] << " " << final_dataset[i][1] << " " << final_dataset[i][2] << endl;
        }
    }
    */

}
// array contains the price, end is the current day, day is the backwards days, high=true, low = false
double max_or_min(double array[], int end, int day, bool high_or_low)
{
    // find lowest or highest price in past x days.
    double result = array[end - day];
    for (int i = end - day; i < end; i++)
    {
        if (high_or_low) //seeking for high 
        {
            if (array[i] > result)
            {
                result = array[i];
            }
        }
        else
        {
            if (array[i] < result)
            {
                result = array[i];
            }
        }
    }
    return result;
}
void trends(double high, double low, double& cash, double open[], double& share, int day,string date[], bool &wait, bool &wait_change)
{
    if (open[day] > high && share==0)// buy
    {
        double num_to_buy = cash / (open[day]);
        share += num_to_buy;
        cash -= num_to_buy * open[day];
        wait = false;
        wait_change = true;
        cout << "Trend: Buy coin at a price of " << open[day] <<" "<<date[day]<<" Current value: "<<cash+share*open[day]<< endl;
    }
    else if (open[day] < low && share!=0) // sell
    {
        double num_to_sell = share;
        share =0;
        cash += num_to_sell * open[day];
        wait = true;
        wait_change = true;
        cout << "Trend: Sell coin at a price of " << open[day] <<" "<< date[day] << " Current value: " << cash + share * open[day] << endl;
    }
    else
    {
        wait_change = false;
    }
    
}
double raise_channel(double array[], int day,int start,int max_day,string date[],string price_type,int buyday,int sellday)
{
    // day: backwards time period
    // initialize some important parameter
    double high = 0;
    double low = 0;
    double cash = 10000.0;
    double share = 0;
    double maxmium = 10000;
    double minium = 1;
    int waiting_day = 0; // waiting for buying some shares 空仓时间
    vector<int> wait_array; // waiting day array, used for some stats
    int index = 0;
    bool wait_change = false; // change wait status
    bool wait = true;
    bool previous_trading_result = 1; //using Kelley formula trade.
    for (int i = buyday+start; i < max_day-1; i++)
    {
        high = max_or_min(array, i, buyday, true);
        low = max_or_min(array, i, sellday, false);
        trends(high, low, cash, array, share, i,date,wait,wait_change);
        double current = cash + share * array[i];
        if (current > maxmium)
        {
            maxmium = current;
        }
        if (current / maxmium < minium)
        {
            minium = current / maxmium;
        }
        //cout << cash + share * array[i] << endl;
        if (wait_change && !wait) // buy sign
        {
            wait_array.push_back(waiting_day);
        }
        if (wait) //waiting to buy
        {
            waiting_day++;
        }
        else // holding share
        {
            waiting_day = 0;
        }
        
    }
    //cout << minium << endl;
    double final_assest = share * array[max_day - 2] + cash;
    // divide 10000 to get the ratio
    // cout << fixed << "Based on "<<price_type<<". Value: " <<  final_assest/10000 << endl;
    for (int i=0;i< wait_array.size();i++)
    {
        //cout << wait_array[i] << endl;
    }
    return final_assest / 10000;
}

//these two functions are used for sorting.

/* This function takes last element as pivot, places
   the pivot element at its correct position in sorted
    array, and places all smaller (smaller than pivot)
   to left of pivot and all greater elements to right
   of pivot */
int partition(double arr[][3], int low, int high)
{
    int pivot = arr[high][0];    // pivot 
    int i = (low - 1);  // Index of smaller element 

    for (int j = low; j <= high - 1; j++)
    {
        // If current element is smaller than or 
        // equal to pivot 
        if (arr[j][0] <= pivot)
        {
            i++;    // increment index of smaller element 
            double temp1 = arr[i][0];
            double temp2 = arr[i][1];
            double temp3 = arr[i][2];
            arr[i][0] = arr[j][0];
            arr[i][1] = arr[j][1];
            arr[i][2] = arr[j][2];
            arr[j][0] = temp1;
            arr[j][1] = temp2;
            arr[j][2] = temp3;
        }
    }
    double temp1 = arr[i+1][0];
    double temp2 = arr[i+1][1];
    double temp3 = arr[i+1][2];
    arr[i+1][0] = arr[high][0];
    arr[i+1][1] = arr[high][1];
    arr[i+1][2] = arr[high][2];
    arr[high][0] = temp1;
    arr[high][1] = temp2;
    arr[high][2] = temp3;
    return (i + 1);
}

/* The main function that implements QuickSort
 arr[] --> Array to be sorted,
  low  --> Starting index,
  high  --> Ending index */
void quickSort(double arr[][3], int low, int high)
{
    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now
           at right place */
        int pi = partition(arr, low, high);

        // Separately sort elements before 
        // partition and after partition 
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}