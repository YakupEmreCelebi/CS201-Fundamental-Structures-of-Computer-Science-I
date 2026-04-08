
#include "BilkentTourism.h"
#include <iostream>

using namespace std;

BilkentTourism::BilkentTourism()
{
    headLines = nullptr;
    headAllStops = nullptr;
}

BilkentTourism::~BilkentTourism()
{
    LineNode *p = headLines;
    while (p != nullptr)
    {
        LineNode *tempLine = p->next;

        BusNode *b = p->lineBussesHead;
        while (b != nullptr)
        {
            BusNode *tempBus = b->next;
            delete b;
            b = tempBus;
        }

        StopNode *s = p->lineStopsHead;
        while (s != nullptr)
        {
            StopNode *tempStop = s->next;
            delete s;
            s = tempStop;
        }

        delete p;
        p = tempLine;
    }
    StopNode *g = headAllStops;
    while (g != nullptr)
    {
        StopNode *tempG = g->next;
        delete g;
        g = tempG;
    }

    headLines = nullptr;
    headAllStops = nullptr;
}

void BilkentTourism::addBusLine(const int lineId, const string lineName)
{

    bool exists = false;
    LineNode *check = headLines;
    while (check != nullptr)
    {
        if (check->lineId == lineId)
        {
            exists = true;
            break;
        }
        check = check->next;
    }

    if (exists)
    {
        cout << "Cannot add line. There is already a bus line with ID " << lineId << "." << endl;
        return;
    }

    LineNode *newNode = new LineNode(lineId, lineName);

    if (headLines == nullptr || lineId < headLines->lineId)
    {
        newNode->next = headLines;
        headLines = newNode;
    }
    else
    {
        LineNode *curr = headLines;
        while (curr->next != nullptr && curr->next->lineId < lineId)
        {
            curr = curr->next;
        }
        LineNode *tempNext = curr->next;
        curr->next = newNode;
        newNode->next = tempNext;
    }

    cout << "Added bus line " << lineId << "." << endl;
}

void BilkentTourism::removeBusLine(const int lineId)
{
    LineNode *curr = headLines;
    LineNode *prev = nullptr;
    bool found = false;

    while (curr != nullptr)
    {
        if (curr->lineId == lineId)
        {
            found = true;
            break;
        }
        prev = curr;
        curr = curr->next;
    }

    if (!found)
    {
        cout << "Cannot remove bus line. There is no bus line with ID " << lineId << "." << endl;
        return;
    }

    if (prev == nullptr)
    {
        headLines = curr->next;
    }
    else
    {
        prev->next = curr->next;
    }

    BusNode *bPtr = curr->lineBussesHead;
    while (bPtr != nullptr)
    {
        BusNode *delBus = bPtr;
        bPtr = bPtr->next;
        delete delBus;
    }

    StopNode *sPtr = curr->lineStopsHead;
    while (sPtr != nullptr)
    {
        StopNode *delStop = sPtr;
        sPtr = sPtr->next;
        delete delStop;
    }

    delete curr;

    cout << "Removed bus line " << lineId << "." << endl;
}

void BilkentTourism::printBusLines() const
{
    if (headLines == nullptr)
    {
        cout << "There are no bus lines to show." << endl;
        return;
    }

    cout << "Bus lines in the system:" << endl;

    LineNode *ptr = headLines;
    while (ptr != nullptr)
    {
        cout << "Line " << ptr->lineId << " : " << ptr->lineName << endl;
        ptr = ptr->next;
    }
}

void BilkentTourism::addStop(const int stopId, const string stopName)
{
    StopNode *temp = headAllStops;
    while (temp != nullptr)
    {
        if (temp->stopId == stopId)
        {
            cout << "Cannot add stop. BilkentTourism already contains stop " << stopId << "." << endl;
            return;
        }
        temp = temp->next;
    }

    StopNode *newNode = new StopNode(stopId, stopName);

    if (headAllStops == nullptr || stopId < headAllStops->stopId)
    {
        newNode->next = headAllStops;
        headAllStops = newNode;
    }
    else
    {
        StopNode *iter = headAllStops;
        while (iter->next != nullptr && iter->next->stopId < stopId)
        {
            iter = iter->next;
        }
        StopNode *nextNode = iter->next;
        iter->next = newNode;
        newNode->next = nextNode;
    }

    cout << "Added stop " << stopId << "." << endl;
}

void BilkentTourism::removeStop(const int stopId)
{
    StopNode *curr = headAllStops;
    StopNode *prev = nullptr;
    bool found = false;
    while (curr != nullptr)
    {
        if (curr->stopId == stopId)
        {
            found = true;
            break;
        }
        prev = curr;
        curr = curr->next;
    }
    if (!found)
    {
        cout << "Cannot remove stop " << stopId << ". There is no bus stop with ID " << stopId << "." << endl;
        found = false;
        return;
    }

    bool inUse = false;
    LineNode *lPtr = headLines;
    while (lPtr != nullptr)
    {
        StopNode *sPtr = lPtr->lineStopsHead;
        while (sPtr != nullptr)
        {
            if (sPtr->stopId == stopId)
            {
                inUse = true;
                break;
            }
            sPtr = sPtr->next;
        }
        if (inUse)
            break;
        lPtr = lPtr->next;
    }

    if (inUse)
    {
        cout << "Cannot remove stop " << stopId << ". The stop is currently in use." << endl;
        return;
    }

    if (prev == nullptr)
        headAllStops = curr->next;
    else
        prev->next = curr->next;

    delete curr;
    cout << "Removed stop " << stopId << "." << endl;
}

void BilkentTourism::addStopToLine(const int stopId, const int lineId)
{

    StopNode *foundStop = nullptr;
    StopNode *sIter = headAllStops;
    while (sIter != nullptr)
    {
        if (sIter->stopId == stopId)
        {
            foundStop = sIter;
            break;
        }
        sIter = sIter->next;
    }

    if (foundStop == nullptr)
    {
        cout << "Cannot add stop. There is no stop with ID " << stopId << "." << endl;
        return;
    }
    LineNode *foundLine = nullptr;
    LineNode *lIter = headLines;
    while (lIter != nullptr)
    {
        if (lIter->lineId == lineId)
        {
            foundLine = lIter;
            break;
        }
        lIter = lIter->next;
    }

    if (foundLine == nullptr)
    {
        cout << "Cannot add stop. There is no line with ID " << lineId << "." << endl;
        return;
    }
    StopNode *check = foundLine->lineStopsHead;
    while (check != nullptr)
    {
        if (check->stopId == stopId)
        {
            cout << "Cannot add stop. Line " << lineId << " already contains stop " << stopId << "." << endl;
            return;
        }
        check = check->next;
    }

    StopNode *newS = new StopNode(stopId, foundStop->stopName);

    if (foundLine->lineStopsHead == nullptr || stopId < foundLine->lineStopsHead->stopId)
    {
        newS->next = foundLine->lineStopsHead;
        foundLine->lineStopsHead = newS;
    }
    else
    {
        StopNode *tmp = foundLine->lineStopsHead;
        while (tmp->next != nullptr && tmp->next->stopId < stopId)
        {
            tmp = tmp->next;
        }
        StopNode *tempLink = tmp->next;
        tmp->next = newS;
        newS->next = tempLink;
    }

    cout << "Added stop " << stopId << " to line " << lineId << " (" << foundLine->lineName << ")." << endl;
}

void BilkentTourism::removeStopFromLine(const int stopId, const int lineId)
{

    LineNode *line = headLines;
    while (line != nullptr && line->lineId != lineId)
    {
        line = line->next;
    }

    if (line == nullptr)
    {
        cout << "Cannot remove stop. There is no line with ID " << lineId << "." << endl;
        return;
    }

    StopNode *curr = line->lineStopsHead;
    StopNode *prev = nullptr;
    bool found = false;

    while (curr != nullptr)
    {
        if (curr->stopId == stopId)
        {
            found = true;
            break;
        }
        prev = curr;
        curr = curr->next;
    }

    if (!found)
    {
        cout << "Cannot remove stop. Line " << lineId << " does not have stop " << stopId << "." << endl;
        return;
    }

    if (prev == nullptr)
    {
        line->lineStopsHead = curr->next;
    }
    else
    {
        prev->next = curr->next;
    }

    delete curr;
    cout << "Removed stop " << stopId << " from line " << lineId << "." << endl;
}

void BilkentTourism::printStops(const int lineId) const
{
    LineNode *theLine = headLines;
    while (theLine != nullptr)
    {
        if (theLine->lineId == lineId)
            break;
        theLine = theLine->next;
    }

    if (theLine == nullptr)
    {
        cout << "Cannot print stops. There is no line with ID " << lineId << "." << endl;
        return;
    }

    if (theLine->lineStopsHead == nullptr)
    {
        cout << "Cannot print stops. There is no stop to show." << endl;
        return;
    }

    cout << "Stops in bus line " << lineId << " (" << theLine->lineName << ") :" << endl;

    StopNode *s = theLine->lineStopsHead;
    while (s != nullptr)
    {
        cout << "Stop " << s->stopId << " : " << s->stopName << endl;
        s = s->next;
    }
}

// TODO
void BilkentTourism::assignBus(const int busId, const string driverName, const int lineId)
{
    LineNode *targetLine = nullptr;
    LineNode *ptr = headLines;
    while (ptr != nullptr)
    {
        if (ptr->lineId == lineId)
        {
            targetLine = ptr;
        }
        ptr = ptr->next;
    }

    if (targetLine == nullptr)
    {
        cout << "Cannot assign bus. There is no line with ID " << lineId << "." << endl;
        return;
    }

    bool assignedAlready = false;
    LineNode *search = headLines;
    while (search != nullptr)
    {
        BusNode *b = search->lineBussesHead;
        while (b != nullptr)
        {
            if (b->busId == busId)
            {
                assignedAlready = true;
                break;
            }
            b = b->next;
        }
        if (assignedAlready)
            break;
        search = search->next;
    }

    if (assignedAlready)
    {
        cout << "Cannot assign bus. Bus " << busId << " is already assigned to a line." << endl;
        return;
    }
    BusNode *newBus = new BusNode(busId, driverName);
    if (targetLine->lineBussesHead == nullptr || busId < targetLine->lineBussesHead->busId)
    {
        newBus->next = targetLine->lineBussesHead;
        targetLine->lineBussesHead = newBus;
    }
    else
    {
        BusNode *tmp = targetLine->lineBussesHead;
        while (tmp->next != nullptr && tmp->next->busId < busId)
        {
            tmp = tmp->next;
        }
        BusNode *holder = tmp->next;
        tmp->next = newBus;
        newBus->next = holder;
    }

    cout << "Bus " << busId << " with driver " << driverName << " is assigned to line " << lineId << " (" << targetLine->lineName << ")." << endl;
}

void BilkentTourism::unassignBus(const int busId)
{
    LineNode *lp = headLines;
    bool deleted = false;

    while (lp != nullptr)
    {
        BusNode *curr = lp->lineBussesHead;
        BusNode *prev = nullptr;

        while (curr != nullptr)
        {
            if (curr->busId == busId)
            {
                if (prev == nullptr)
                {
                    lp->lineBussesHead = curr->next;
                }
                else
                {
                    prev->next = curr->next;
                }
                delete curr;
                deleted = true;

                cout << "Bus " << busId << " is unassigned from line " << lp->lineId
                     << " (" << lp->lineName << ")." << endl;
                return;
            }
            prev = curr;
            curr = curr->next;
        }
        lp = lp->next;
    }

    if (!deleted)
    {
        cout << "Cannot unassign bus. There is no bus with ID " << busId << "." << endl;
    }
}

void BilkentTourism::printBussesInLine(const int lineId) const
{
    LineNode *target = nullptr;
    LineNode *p = headLines;

    while (p != nullptr)
    {
        if (p->lineId == lineId)
        {
            target = p;
            break;
        }
        p = p->next;
    }

    if (target == nullptr)
    {
        cout << "Cannot print busses. There is no line with ID " << lineId << "." << endl;
        return;
    }

    if (target->lineBussesHead == nullptr)
    {
        cout << "There are no bus to show in line " << lineId << " (" << target->lineName << ")." << endl;
        return;
    }

    cout << "Busses and their drivers assigned to the line " << lineId << " (" << target->lineName << "):" << endl;

    BusNode *b = target->lineBussesHead;
    while (b != nullptr)
    {
        cout << "Bus " << b->busId << " : " << b->driverName << endl;
        b = b->next;
    }
}

void BilkentTourism::printBussesPassingStop(const int stopId) const
{
    string sName = "";
    bool sExists = false;
    StopNode *g = headAllStops;

    while (g != nullptr)
    {
        if (g->stopId == stopId)
        {
            sExists = true;
            sName = g->stopName;
            break;
        }
        g = g->next;
    }

    if (!sExists)
    {
        cout << "Cannot print buses. There is no stop with ID " << stopId << "." << endl;
        return;
    }
    bool anyPass = false;
    LineNode *l = headLines;
    while (l != nullptr)
    {
        StopNode *st = l->lineStopsHead;
        while (st != nullptr)
        {
            if (st->stopId == stopId)
            {
                anyPass = true;
                break;
            }
            st = st->next;
        }
        if (anyPass)
        {
            break;
        }

        l = l->next;
    }

    if (!anyPass)
    {
        cout << "Cannot print buses. No lines pass through the stop." << endl;
        return;
    }

    cout << "Buses and their assigned lines passing the stop " << stopId << " (" << sName << "):" << endl;

    LineNode *ptr = headLines;
    while (ptr != nullptr)
    {
        bool passes = false;
        StopNode *sCheck = ptr->lineStopsHead;
        while (sCheck != nullptr)
        {
            if (sCheck->stopId == stopId)
            {
                passes = true;
                break;
            }
            sCheck = sCheck->next;
        }

        if (passes)
        {
            cout << "Line " << ptr->lineId << " (" << ptr->lineName << ") : ";
            BusNode *bPtr = ptr->lineBussesHead;

            if (bPtr == nullptr)
            {
                cout << "None";
            }
            else
            {
                cout << "[";
                while (bPtr != nullptr)
                {
                    cout << bPtr->busId;
                    if (bPtr->next != nullptr)
                        cout << ",";
                    bPtr = bPtr->next;
                }
                cout << "]";
            }
            cout << endl;
        }
        ptr = ptr->next;
    }
}

bool BilkentTourism::isLineExists(int id) const
{
    return false;
}

bool BilkentTourism::isStopExistsInLine(int stopId, int lineId) const
{

    LineNode *targetLine = headLines;
    while (targetLine != nullptr)
    {
        if (targetLine->lineId == lineId)
        {
            break;
        }
        targetLine = targetLine->next;
    }

    if (targetLine == nullptr)
    {
        return false;
    }

    StopNode *s = targetLine->lineStopsHead;
    while (s != nullptr)
    {
        if (s->stopId == stopId)
        {
            return true;
        }
        s = s->next;
    }

    return false;
}
