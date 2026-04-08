
#ifndef BILKENTTOURISM_H
#define BILKENTTOURISM_H

#include <string>
using namespace std;

class BilkentTourism
{
public:
    BilkentTourism();
    ~BilkentTourism();

    void addBusLine(const int lineId, const string lineName);
    void removeBusLine(const int lineId);
    void printBusLines() const;

    void addStop(const int stopId, const string stopName);
    void removeStop(const int stopId);
    void addStopToLine(const int stopId, const int lineId);
    void removeStopFromLine(const int stopId, const int lineId);
    void printStops(const int lineId) const;

    void assignBus(const int busId, const string driverName, const int lineId);
    void unassignBus(const int busId);
    void printBussesInLine(const int lineId) const;
    void printBussesPassingStop(const int stopId) const;

private:
    struct BusNode
    {
        int busId;
        string driverName;
        BusNode *next;

        BusNode(int id, string name, BusNode *n = nullptr)
        {
            this->busId = id;
            this->driverName = name;
            this->next = n;
        }
    };

    struct StopNode
    {
        int stopId;
        string stopName;
        StopNode *next;

        StopNode(int id, string name, StopNode *n = nullptr)
        {
            this->stopId = id;
            this->stopName = name;
            this->next = n;
        }
    };

    struct LineNode
    {
        int lineId;
        string lineName;
        LineNode *next;

        StopNode *lineStopsHead;
        BusNode *lineBussesHead;

        LineNode(int id, string name, LineNode *n = nullptr)
        {
            this->lineId = id;
            this->lineName = name;
            this->next = n;

            this->lineStopsHead = nullptr;
            this->lineBussesHead = nullptr;
        }
    };

    LineNode *headLines;
    StopNode *headAllStops;

    bool isLineExists(int id) const;
    bool isStopExistsInLine(int stopId, int lineId) const;
};

#endif
