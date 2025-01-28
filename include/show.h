#pragma once

#include "movie.h"
#include "theater.h"
#include "seat.h"
#include <string>
#include <vector>

/**
 * @brief Show class, contains Movie information and Theater where that Movie is played.
 * Also contains information about the time of the show and the id.
 * This class binds the information of a Movie with the information of a Theater.
 * One show is considered as one movie in one theater, like a unique specifier based on that. 
 * Theater could also have the information of all of the movies that are played in it.
 * Another solution is this one: bind one movie in one theater as one show, also for the specific time. 
 * This one makes it easier to maintain, since during a projection of a movie in one theater for a specific time
 * we can have all of the possible seats available only for that projection. 
 * Another option would be to have theater with all of the movies with all of the possible times/projections.
 */
class Show {
public:
    Show(const std::string& id, const Movie& movie, const Theater& theater, const std::string& time, const unsigned int num_seats = 20);

    std::string getId() const;
    Movie getMovie() const;
    Theater getTheater() const;
    std::string getTime() const;
    void addSeat(const Seat& seat);
    const std::vector<Seat>& getSeats() const;
    bool isSeatAvailable(const std::string& seatId) const;
    void bookSeat(const std::string& seatId);

private:
    // Store the data specific to one projection of a movie in one theater at one time
    std::string m_id;
    Movie m_movie;
    Theater m_theater;
    std::string m_time;
    std::vector<Seat> m_seats;
};
