#include "booking_service.h"
#include "exceptions.h"
#include <catch2/catch_test_macros.hpp>
#include <thread>
#include <vector>
#include <iostream>
#include <atomic>

TEST_CASE("Booking Service Tests") {
    // Use a shared pointer to ensure the BookingService instance is properly managed
    // across threads.
    std::shared_ptr<BookingService> service = std::make_shared<BookingService>();
    std::vector<Show> shows;
    shows.push_back(Show("S1", Movie("M1", "Movie A"), Theater("T1", "Theater X"), "10:00 AM"));
    shows.push_back(Show("S2", Movie("M1", "Movie A"), Theater("T1", "Theater X"), "12:00 AM")); // another projection of the same movie
    shows.push_back(Show("S3", Movie("M2", "Movie B"), Theater("T1", "Theater X"), "11:00 AM")); // another movie in the same theater
    shows.push_back(Show("S4", Movie("M2", "Movie B"), Theater("T2", "Theater Y"), "10:00 AM")); // 2nd movie in another theater
    shows.push_back(Show("S5", Movie("M1", "Movie A"), Theater("T2", "Theater Y"), "10:00 PM")); // another projection of the movie A in the same 2nd theater
    service->setShows(shows);

    SECTION("Get All Movies") {
        std::vector<Movie> movies = service->getAllMovies();
        REQUIRE(movies.size() == 2);
        REQUIRE(movies[0].getTitle() == "Movie A");
        REQUIRE(movies[1].getTitle() == "Movie B");
    }

    SECTION("Get Theaters for Movie") {
        std::vector<Theater> theaters = service->getTheatersForMovie("M1");
        REQUIRE(theaters.size() == 2);
        REQUIRE(theaters[0].getName() == "Theater X");
        REQUIRE(theaters[1].getName() == "Theater Y");
    }

    SECTION("Get Available Shows") {
        std::vector<Show> shows = service->getAvailableShows("M1", "T1");
        REQUIRE(shows.size() == 2);
        REQUIRE(shows[0].getMovie().getTitle() == "Movie A");
        REQUIRE(shows[0].getTheater().getName() == "Theater X");
        REQUIRE(shows[0].getTime() == "10:00 AM");
    }

    SECTION("Get Available Seats") {
        std::vector<Seat> seats = service->getAvailableSeats("S1");
        REQUIRE(seats.size() == 20);
        REQUIRE(seats[0].getStatus() == Seat::Status::Available);
    }

    SECTION("Book Seats") {
      std::vector<std::string> seatIds = {"S1", "S2", "S3"};
      service->bookSeats("S1", seatIds);

      std::vector<Seat> seats = service->getAvailableSeats("S1");
      REQUIRE(seats.size() == 17); // 20 seats - 3 booked seats, 17 available seats

      // Get the Show object to check the status of all seats in the show
      std::vector shows = service->getAvailableShows("M1", "T1");
      REQUIRE(shows.size() == 2);
      Show show = service->getAvailableShows("M1", "T1")[0]; // the first show would suffice 

      REQUIRE(show.getId() == "S1");
      bool s1Found = false;
      bool s2Found = false;
      bool s3Found = false;
      for (const auto& seat : show.getSeats()) {
          if (seat.getSeatNumber() == "S1") {
              s1Found = true;
              REQUIRE(seat.getStatus() == Seat::Status::Reserved);
          }
          if (seat.getSeatNumber() == "S2") {
              s2Found = true;
              REQUIRE(seat.getStatus() == Seat::Status::Reserved);
          }
          if (seat.getSeatNumber() == "S3") {
              s3Found = true;
              REQUIRE(seat.getStatus() == Seat::Status::Reserved);
          }
      }
      REQUIRE(s1Found);
      REQUIRE(s2Found);
      REQUIRE(s3Found);
    }

    SECTION("Book Already Booked Seat") {
        std::vector<std::string> seatIds = {"S1"};
        service->bookSeats("S1", seatIds);

        REQUIRE_THROWS_AS(service->bookSeats("S1", seatIds), SeatNotAvailableException);
    }

    SECTION("Book Non-Existent Seat") {
        std::vector<std::string> seatIds = {"Z99"}; // Invalid seat ID
        REQUIRE_THROWS_AS(service->bookSeats("S1", seatIds), SeatNotFoundException);
    }

    SECTION("Book Seat for Non-Existent Show") {
        std::vector<std::string> seatIds = {"S1"};
        REQUIRE_THROWS_AS(service->bookSeats("S99", seatIds), ShowNotFoundException); // Invalid show ID
    }

    SECTION("Concurrent Booking - Multiple Threads Booking Different Seats") {
        std::shared_ptr<BookingService> sharedService = std::make_shared<BookingService>();

        auto bookSeatsThread = [&](const std::string& showId, const std::vector<std::string>& seatIds) {
            try {
                sharedService->bookSeats(showId, seatIds);
            } catch (const std::exception& e) {
                std::cout << "Thread " << std::this_thread::get_id() << " Error: " << e.what() << std::endl;
            }
        };
        Show show_test = Show("Sh1", Movie("M1", "Movie A"), Theater("T1", "Theater X"), "10:00 AM");
        sharedService->setOneShow(show_test);
        std::thread t1(bookSeatsThread, "Sh1", std::vector<std::string>{"S4"});
        std::thread t2(bookSeatsThread, "Sh1", std::vector<std::string>{"S5"});
        std::thread t3(bookSeatsThread, "Sh1", std::vector<std::string>{"S6"});

        t1.join();
        t2.join();
        t3.join();

        std::vector<Seat> seats = sharedService->getAvailableSeats("Sh1");
        REQUIRE(seats.size() == 17);

        for (const auto& seat : seats) {
            if (seat.getSeatNumber() == "S4" || seat.getSeatNumber() == "S5" || seat.getSeatNumber() == "S6") {
                REQUIRE(seat.getStatus() == Seat::Status::Reserved);
            }
        }
    }

    SECTION("Concurrent Booking - Multiple Threads Trying to Book the Same Seat") {
        std::shared_ptr<BookingService> sharedService = std::make_shared<BookingService>();

        std::atomic<int> successfulBookings(0);

        auto bookSeatsThread = [&](const std::string& showId, const std::string& seatId) {
            try {
                sharedService->bookSeats(showId, {seatId});
                successfulBookings++;
            } catch (const SeatNotAvailableException& e) {
                std::cout << "Thread " << std::this_thread::get_id() << " Expected Error: " << e.what() << std::endl;
            } catch (const std::exception& e) {
                std::cout << "Thread " << std::this_thread::get_id() << " Unexpected Error: " << e.what() << std::endl;
            }
        };

        Show show_test = Show("Sh1", Movie("M1", "Movie A"), Theater("T1", "Theater X"), "10:00 AM");
        sharedService->setOneShow(show_test);

        std::thread t1(bookSeatsThread, "Sh1", "S7");
        std::thread t2(bookSeatsThread, "Sh1", "S7");
        std::thread t3(bookSeatsThread, "Sh1", "S7");

        t1.join();
        t2.join();
        t3.join();

        REQUIRE(successfulBookings == 1);

        std::vector<Seat> seats = sharedService->getAvailableSeats("Sh1");
        for (const auto& seat : seats) {
            if (seat.getSeatNumber() == "S7") {
                REQUIRE(seat.getStatus() == Seat::Status::Reserved);
            }
        }
    }
}