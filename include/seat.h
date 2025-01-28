#pragma once

#include <string>

/**
 * @brief Seat class, contains the information of the seat number and the status of the seat.
 * Also, via this class you can book and unbook the seat.
 * Could be called from some outside api of the booking service.
 */
class Seat {
public:
    enum class Status {
        Available,
        Reserved
    };

    Seat(const std::string& seatNumber);
    Seat(const std::string& seatNumber, const std::string& showId); 

    std::string getSeatNumber() const;
    std::string getShowId() const;
    Status getStatus() const;
    void book();
    void setStatus(Status status);
    std::string getId() const;

private:
    std::string m_seatNumber;
    std::string m_showId;
    Status m_status;
};