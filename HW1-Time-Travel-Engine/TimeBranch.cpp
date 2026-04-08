// Name: Yakup Emre Çelebi, Department: Computer Science
#include "TimeBranch.h"

TimeBranch::TimeBranch(int id, string startLoc, int pastCap, int futureCap)
{
    branchId = id;

    currentLocation = startLoc;
    pastStack = new StringStack(pastCap);
    futureStack = new StringStack(futureCap);

    stoneStack = new StringStack(2);
}

TimeBranch::~TimeBranch()
{
    delete pastStack;

    delete futureStack;
    delete stoneStack;
}

void TimeBranch::travelTo(string newLocation)
{
    if (currentLocation == newLocation)
    {

        futureStack->clear();
        cout << "Traveled to " << newLocation << " in branch " << branchId << "." << endl;
        return;
    }

    if (pastStack->isFull())
    {
        cout << "Cannot travel to " << newLocation << " in branch " << branchId << ". Past stack capacity exceeded." << endl;
        return;
    }

    pastStack->push(currentLocation);
    currentLocation = newLocation;

    futureStack->clear();

    cout << "Traveled to " << newLocation << " in branch " << branchId << "." << endl;
}

void TimeBranch::fastForward(int k)
{
    int steps = k;
    if (steps > futureStack->size())
    {
        steps = futureStack->size();
    }

    if (pastStack->size() + steps > pastStack->getCapacity())
    {
        cout << "Cannot fast forward " << steps << " steps in branch " << branchId << ". Past stack capacity exceeded." << endl;
        return;
    }

    for (int i = 0; i < steps; i++)
    {
        pastStack->push(currentLocation);
        currentLocation = futureStack->pop();
    }

    cout << "Fast forwarded " << steps << " steps in branch " << branchId << "." << endl;
}

void TimeBranch::rewind(int k)
{
    int steps = k;
    if (steps > pastStack->size())
    {
        steps = pastStack->size();
    }

    if (futureStack->size() + steps > futureStack->getCapacity())
    {
        cout << "Cannot rewind " << steps << " steps in branch " << branchId << ". Future stack capacity exceeded." << "\n";
        return;
    }

    for (int i = 0; i < steps; i++)
    {
        futureStack->push(currentLocation);
        currentLocation = pastStack->pop();
    }

    cout << "Rewound " << steps << " steps in branch " << branchId << "." << endl;
}

void TimeBranch::placeTimeStone()
{
    if (stoneStack->isFull())
    {
        stoneStack->expand();
    }

    stoneStack->push(currentLocation);
    cout << "Time stone placed at " << currentLocation << "." << "\n";
}

// todo, not empty control
void TimeBranch::activateTimeStone()
{
    if (stoneStack->isEmpty())
    {
        cout << "Cannot activate time stone. No time stones available." << endl;
        return;
    }
    string L = stoneStack->pop();

    if (currentLocation == L)
    {

        futureStack->clear();
        cout << "Time stone activated. The traveler is now at " << L << "." << endl;
        return;
    }
    int idxPast = -1;
    for (int i = pastStack->size() - 1; i >= 0; --i)
    {

        if (pastStack->getElementAt(i) == L)
        {
            idxPast = i;
            break;
        }
    }

    if (idxPast != -1)
    {
        int steps = pastStack->size() - idxPast;

        if (futureStack->size() + steps > futureStack->getCapacity())
        {
            cout << "Time stone discarded. Future stack capacity exceeded." << endl;
            return;
        }

        while (currentLocation != L)
        {
            futureStack->push(currentLocation);
            currentLocation = pastStack->pop();
        }

        futureStack->clear();

        cout << "Time stone activated. The traveler is now at " << L << "." << endl;
        return;
    }

    int idxFuture = -1;
    for (int i = futureStack->size() - 1; i >= 0; --i)
    {
        if (futureStack->getElementAt(i) == L)
        {
            idxFuture = i;
            break;
        }
    }

    if (idxFuture != -1)
    {

        int steps = futureStack->size() - idxFuture;

        if (pastStack->size() + steps > pastStack->getCapacity())
        {

            cout << "Time stone discarded. Past stack capacity exceeded." << endl;
            return;
        }

        while (currentLocation != L)
        {
            pastStack->push(currentLocation);
            currentLocation = futureStack->pop();
        }
        futureStack->clear();

        cout << "Time stone activated. The traveler is now at " << L << "." << endl;

        return;
    }

    cout << "Time stone discarded. The recorded moment is no longer reachable." << endl;
}

void TimeBranch::printBranchState() const
{
    int pSize = pastStack->size();
    cout << "Past   : [ ";
    for (int i = 0; i < pSize; i++)
    {
        cout << pastStack->getElementAt(i);
        if (i < pastStack->size() - 1)
        {
            cout << ", ";
        }
    }
    cout << " ]" << endl;

    cout << "Current: ( " << currentLocation << " )" << endl;

    cout << "Future : [ ";

    int futureSize = futureStack->size();
    for (int i = 0; i < futureSize; i++)
    {
        cout << futureStack->getElementAt(i);
        if (i < futureStack->size() - 1)
        {
            cout << ", ";
        }
    }
    cout << " ]" << endl;

    cout << "Stones : [ ";
    for (int i = 0; i < stoneStack->size(); i++)
    {
        cout << stoneStack->getElementAt(i);
        if (i < stoneStack->size() - 1)
        {
            cout << ", ";
        }
    }
    cout << " ]" << endl;
}

int TimeBranch::getId() const { return branchId; }

string TimeBranch::getCurrentLocation() const { return currentLocation; }
StringStack *TimeBranch::getPastStack() const { return pastStack; }
StringStack *TimeBranch::getFutureStack() const { return futureStack; }
StringStack *TimeBranch::getStoneStack() const { return stoneStack; }

int TimeBranch::getPastCapacity() const { return pastStack->getCapacity(); }

int TimeBranch::getFutureCapacity() const { return futureStack->getCapacity(); }
