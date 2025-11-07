#ifndef AIRPLANEMANAGER_AIRPLANE_H
#define AIRPLANEMANAGER_AIRPLANE_H
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Airplane {
    string m_strID;
    int m_iSeatCount;
    int m_iEmptySeatCount;
    vector<bool> m_seatList;
public:
    //  Constructor / Destructor
    Airplane();
    Airplane(const string&, int);
    ~Airplane();

    //  Getter
    string getID() const;
    int getSeatCount() const;
    vector<bool>& getSeatList();

    //  Setter
    void setSeatCount(int);

    //  Logic
    string toString() const;
    void printAirplaneInfo() const;
};

#endif //AIRPLANEMANAGER_AIRPLANE_H