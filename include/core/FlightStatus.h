//
// Created by HP on 05/11/2025.
//

#ifndef AIRPLANEMANAGER_FLIGHTSTATUS_H
#define AIRPLANEMANAGER_FLIGHTSTATUS_H

/**********************************************************
* @Description Enum biểu diễn trạng thái chuyến bay
* @attention
* CANCELLED : Chuyến bay đã hủy
* AVAILABLE : Chuyến bay còn vé
* SOLD_OUT  : Chuyến bay đã hết vé
* COMPLETED : Chuyến bay đã kết thúc
* @return  Không
**********************************************************/
enum class FlightStatus {
    CANCELLED = 0,
    AVAILABLE = 1,
    SOLD_OUT = 2,
    COMPLETED = 3
};


#endif //AIRPLANEMANAGER_FLIGHTSTATUS_H