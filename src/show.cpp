#include "show.h"
#include "exceptions.h"

Show::Show(const std::string& id, const Movie& movie, const Theater& theater, const std::string& time, const unsigned int num_seats)
    : m_id(id), m_movie(movie), m_theater(theater), m_time(time)
    {
        m_seats.reserve(num_seats);
        std::generate_n(std::back_inserter(m_seats), num_seats, [n = 1]() mutable {
            return Seat("S" + std::to_string(n++));
        });

    }

std::string Show::getId() const {
    return m_id;
}

Movie Show::getMovie() const {
    return m_movie;
}

Theater Show::getTheater() const {
    return m_theater;
}

std::string Show::getTime() const {
    return m_time;
}

void Show::addSeat(const Seat& seat) {
    m_seats.push_back(seat);
}

const std::vector<Seat>& Show::getSeats() const {
    return m_seats;
}

bool Show::isSeatAvailable(const std::string& seatId) const {
    for (const auto& seat : m_seats) {
        if (seat.getSeatNumber() == seatId && seat.getStatus() == Seat::Status::Available) {
            return true;
        }
    }
    return false;
}

void Show::bookSeat(const std::string& seatId) {
    for (auto& seat : m_seats) {
        if (seat.getSeatNumber() == seatId) {
            if (seat.getStatus() == Seat::Status::Available) {
                seat.setStatus(Seat::Status::Reserved);
                return;
            } else {
                throw SeatNotAvailableException("Seat already booked: " + seatId);
            }
        }
    }
    throw SeatNotFoundException("Seat not found with ID: " + seatId);
}