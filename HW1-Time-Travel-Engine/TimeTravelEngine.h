// Name: Yakup Emre Çelebi, Department: Computer Science
#ifndef TIMETRAVELENGINE_H
#define TIMETRAVELENGINE_H

#include <string>

#include <iostream>
#include "TimeBranch.h"

using namespace std;
class TimeTravelEngine
{
private:
    TimeBranch **branches;

    int numberOfBranches;

    int findBranchIndex(int branchId) const;

public:
    TimeTravelEngine();
    ~TimeTravelEngine();

    int createTimeBranch(const int pastCapacity, const int futureCapacity, const string startLocation, const int branchId);

    void deleteTimeBranch(const int branchId);

    void printAllBranches() const;

    void travelTo(const int branchId, const string newLocation);
    void fastForward(const int branchId, const int k);

    void rewind(const int branchId, const int k);

    void placeTimeStone(const int branchId);

    void activateTimeStone(const int branchId);

    void printTimeBranch(const int branchId) const;

    int mergeBranches(const int branchId1, const int branchId2, const int newBranchId);
};

#endif
