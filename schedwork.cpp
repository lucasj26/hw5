#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here

bool helper(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    vector<int>& counter,
    int row,
    int col
);


// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below

    for (size_t i = 0; i < avail.size(); ++i) {
        vector<Worker_T> row;
        for (size_t j = 0; j < dailyNeed; ++j) {
            row.push_back(INVALID_ID);
        }
        sched.push_back(row); 
    }

    vector<int> shiftCounter(avail[0].size(), 0);
    return helper(avail,dailyNeed,maxShifts,sched,shiftCounter,0,0);



}



bool helper(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    vector<int>& counter,
    int row,
    int col
)
{
    if(row==avail.size()){
        return true;
    }
    if(col==dailyNeed){
        return helper(avail,dailyNeed,maxShifts,sched,counter,row+1,0);
    }
    for(int worker=0;worker<avail[0].size();worker++){
        bool shiftsLeft = counter[worker] < maxShifts;
        if(shiftsLeft && avail[row][worker]
            && find(sched[row].begin(), sched[row].end(), worker) == sched[row].end()){
            sched[row][col] = worker;
            counter[worker]++;
            if(helper(avail,dailyNeed,maxShifts,sched,counter,row,col+1)){
                return true;
            }
            counter[worker]--;
            sched[row][col] = INVALID_ID;
        }   
        

    }
    return false;

}