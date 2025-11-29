#ifndef AIRPLANEMANAGER_FLIGHTMANAGER_H
#define AIRPLANEMANAGER_FLIGHTMANAGER_H

#include "../repository/AirplaneRepository.h"
#include "../repository/FlightRepository.h"
#include "../repository/TicketRepository.h"
#include "../core/FlightStatus.h"
#include "../repository/CustomerRepository.h"


using namespace std;
class FlightManager {
    FlightRepository* m_flightRepository; /**< Repository chứa chuyến bay */
    TicketRepository* m_ticketRepository; /**< Repository chứa vé */
    AirplaneRepository* m_airplaneRepository; /**< Repository chứa máy bay */
    CustomerRepository* m_customerRepository; /**< Repository chứa khách hàng */

    /**********************************************************
    * @Description Lưu toàn bộ dữ liệu hiện có của hệ thống
    * @return  Không
    **********************************************************/
    void saveData() const;

    /**********************************************************
    * @Description Load toàn bộ dữ liệu hiện có của hệ thống
    * @return  Không
    **********************************************************/
    void loadData() const;
public:
    /**********************************************************
    * @Description Constructor mặc định
    * @return  Pointer trỏ đến FlightManager vừa tạo
    **********************************************************/
    FlightManager();

    /**********************************************************
    * @Description Constructor với repository có sẵn
    * @param FlightRepository*, TicketRepository*, AirplaneRepository*, CustomerRepository*
    * @return  Pointer trỏ đến FlightManager vừa tạo
    **********************************************************/
    FlightManager(FlightRepository*, TicketRepository*, AirplaneRepository*, CustomerRepository*);

    /**********************************************************
    * @Description Destructor
    * @return  Không
    **********************************************************/
    ~FlightManager();

    /**********************************************************
    * @Description Lấy FlightRepository
    * @return  Tham chiếu đến FlightRepository
    **********************************************************/
    [[nodiscard]] FlightRepository& getFlightRepository() const;

    /**********************************************************
    * @Description Lấy TicketRepository
    * @return  Tham chiếu đến TicketRepository
    **********************************************************/
    [[nodiscard]] TicketRepository& getTicketRepository() const;

    /**********************************************************
    * @Description Lấy AirplaneRepository
    * @return  Tham chiếu đến AirplaneRepository
    **********************************************************/
    [[nodiscard]] AirplaneRepository& getAirplaneRepository() const;

    /**********************************************************
    * @Description Lấy CustomerRepository
    * @return  Tham chiếu đến CustomerRepository
    **********************************************************/
    [[nodiscard]] CustomerRepository& getCustomerRepository() const;

    /**********************************************************
    * @Description Thêm chuyến bay mới vào hệ thống
    * @param Flight& flight
    * @return  Không
    **********************************************************/
    void addFlight(const Flight&) const;

    /**********************************************************
    * @Description Hủy chuyến bay theo ID
    * @param string& flightID
    * @return  Không
    **********************************************************/
    void cancelFlight(const string&) const;

    /**********************************************************
    * @Description Cập nhật trạng thái chuyến bay
    * @param string& flightID, FlightStatus& status
    * @return  Không
    **********************************************************/
    void updateFlightStatus(const string&, const FlightStatus&) const;

    /**********************************************************
    * @Description Tìm chuyến bay theo ID
    * @param string& flightID
    * @return  Pointer trỏ đến Flight object hoặc undefineFlight() nếu không tồn tại
    **********************************************************/
    Flight** findFlightByID(const string&) const;

    /**********************************************************
    * @Description Tìm chuyến bay theo ngày khởi hành
    * @param string& date
    * @return  List<Flight*> chuyến bay theo ngày
    **********************************************************/
    List<Flight*> findFlightByDate(const string&) const;

    /**********************************************************
    * @Description Tìm chuyến bay theo điểm đến
    * @param string& destination
    * @return  List<Flight*> chuyến bay theo điểm đến
    **********************************************************/
    List<Flight*> findFlightByDestination(const string&) const;

    /**********************************************************
    * @Description Lấy danh sách ghế trống của chuyến bay
    * @param string& flightID
    * @return  List<int> danh sách ghế trống
    **********************************************************/
    List<int> getAvailableSeat(const string&) const;

    /**********************************************************
    * @Description Lấy tất cả chuyến bay sử dụng một máy bay
    * @param string& airplaneID
    * @return  List<Flight*> chuyến bay sử dụng máy bay
    **********************************************************/
    List<Flight*> findFlightQuantityOfAirplane(const string&) const;

    /**********************************************************
    * @Description Đếm số chuyến bay sử dụng một máy bay
    * @param string& airplaneID
    * @return  int số lượng chuyến bay
    **********************************************************/
    int countFlightOfOneAirplane(const string&) const;

    /**********************************************************
    * @Description Lấy danh sách ghế của chuyến bay
    * @param string& flightID
    * @return  List<int> danh sách ghế: 0 = trống, 1 = đã đặt
    **********************************************************/
    List<int> getSeats(const string&) const;

    /**********************************************************
    * @Description Lấy toàn bộ chuyến bay hiện có trong hệ thống
    * @return  Tham chiếu đến List<Flight*>
    **********************************************************/
    List<Flight*>& getAllFlight() const;
};

#endif //AIRPLANEMANAGER_FLIGHTMANAGER_H