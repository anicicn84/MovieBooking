#include "booking_service.h"
#include "exceptions.h"
#include <algorithm>
#include <stdexcept>


void BookingService::setShows(const std::vector<Show>& shows){
    m_shows = shows;
}

void BookingService::setOneShow(Show show){
    m_shows.push_back(show);
}

std::vector<Movie> BookingService::getAllMovies() {
  std::vector<Movie> result;
  for (auto& show : m_shows){
    auto movie = show.getMovie();
    if (std::find(result.begin(), result.end(), movie) == result.end()) {
        result.push_back(movie);
    }
  }
  return result; 
}

/**
 * @brief Get all theaters showing a specific movie.
 * @return the list of theaters that are showing the movie with the given ID, but unique list.
 */
std::vector<Theater> BookingService::getTheatersForMovie(const std::string& movieId) {
/**
 * @brief A vector that holds a collection of Theater objects.
 */
  std::vector<Theater> result;

  // For all the shows find the theaters that are showing the movie with the given ID
  for (const auto& show : m_shows) {
    if (show.getMovie().getId() == movieId) {
      // Get the theater of the show that has the given movie
      result.push_back(show.getTheater());
    }
  }
  // Remove duplicates if a theater has multiple shows of the same movie
  //Also, could be done in a similar way as above, to check if it already exists before adding it, 
  // but I wanted to show something else how it could be done, too.
  result.erase(std::unique(result.begin(), result.end(),
                           [](const Theater& a, const Theater& b) {
                             return a.getId() == b.getId();
                           }),
               result.end());
  return result;
}

/**
 * @brief get the available shows for a movie in a specific theater that the user wants to go into.
 * @return the list of available shows, that have mapped the movie with the theater.
 */
std::vector<Show> BookingService::getAvailableShows(const std::string& movieId, const std::string& theaterId) {
    std::vector<Show> result;
    for (const auto& show : m_shows) {
        if (show.getMovie().getId() == movieId && show.getTheater().getId() == theaterId) {
            result.push_back(show);
        }
    }
    return result; // return the list of available shows for the specified movie and theater
}

/**
 * @brief get the available seats for a show that the user wants to go into.
 * 
 * @return the list of available seats for the show.
 */
std::vector<Seat> BookingService::getAvailableSeats(const std::string& showId) {
    std::lock_guard<std::mutex> lock(m_mutex); // Protect m_shows
    std::vector<Seat> availableSeats;
    auto showIt = std::find_if(m_shows.begin(), m_shows.end(),
        [&showId](const Show& s) { return s.getId() == showId; });

    if (showIt == m_shows.end()) {
        throw ShowNotFoundException("Show not found with ID: " + showId);
    }

    for (const auto& seat : showIt->getSeats()) {
        if (seat.getStatus() == Seat::Status::Available) {
            availableSeats.push_back(seat);
        }
    }
    return availableSeats;
}

/**
 * @brief  Book seats for a show that the user wants to go into.
 */
void BookingService::bookSeats(const std::string& showId, const std::vector<std::string>& seatIds) {
    std::lock_guard<std::mutex> lock(m_mutex); // Protect m_shows

    auto showIt = std::find_if(m_shows.begin(), m_shows.end(),
        [&showId](const Show& s) { return s.getId() == showId; });

    if (showIt == m_shows.end()) {
        throw ShowNotFoundException("Show not found with ID: " + showId);
    }

    // Book all of the seats from the given argument vector
    for (const auto& seatId : seatIds) {
        showIt->bookSeat(seatId);
    }
}
