#include "seat.h"

Seat::Seat(const std::string& seatNumber) : m_seatNumber(seatNumber), m_status(Status::Available) {}

Seat::Seat(const std::string& seatNumber, const std::string& showId)
    : m_seatNumber(seatNumber), m_showId(showId), m_status(Status::Available) {}

std::string Seat::getSeatNumber() const {
    return m_seatNumber;
}

std::string Seat::getShowId() const {
    return m_showId;
}

Seat::Status Seat::getStatus() const {
    return m_status;
}

void Seat::book() {
    m_status = Status::Reserved;
}

void Seat::setStatus(Status status) {
    m_status = status;
}

std::string Seat::getId() const {
    return m_seatNumber;
}