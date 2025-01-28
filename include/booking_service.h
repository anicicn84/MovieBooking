#pragma once

#include "movie.h"
#include "theater.h"
#include "show.h"
#include "seat.h"
#include <string>
#include <vector>
#include <mutex> 
#include <unordered_map>

class BookingService {
public:
  BookingService() = default;

  // Make a setter for shows
  void setShows(const std::vector<Show>& shows);

  // Set just one show
  void setOneShow(Show show);

  // Get all playing movies
  std::vector<Movie> getAllMovies();

  // Get theaters showing a specific movie
  std::vector<Theater> getTheatersForMovie(const std::string& movieId);

  // Get available shows for a movie in a specific theater
  std::vector<Show> getAvailableShows(const std::string& movieId, const std::string& theaterId);

  // Get available seats for a show
  std::vector<Seat> getAvailableSeats(const std::string& showId);

  // Book seats for a show
  void bookSeats(const std::string& showId, const std::vector<std::string>& seatIds);

private:
  std::vector<Show> m_shows;
  std::mutex m_mutex;
};