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
    Airplane(const string&, const vector<bool>&);
    ~Airplane();

    //  Getter
    [[nodiscard]] string getID() const;
    [[nodiscard]] int getSeatCount() const;
    vector<bool>& getSeatList();

    //  Setter
    void setSeatCount(int);
    void bookSeat(int);
    void cancelSeat(int);

    //  Logic
    [[nodiscard]] string toString() const;
    [[nodiscard]] bool isSeatAvailable(int) const;
    void printAirplaneInfo() const;
};

#endif //AIRPLANEMANAGER_AIRPLANE_H