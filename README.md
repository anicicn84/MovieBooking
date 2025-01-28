# Movie Ticket Booking Service

This project implements a backend service for a movie ticket booking system in C++. It allows users to view movies, theaters, showtimes, available seats, and book tickets.

## Features

*   View all playing movies.
*   Select a movie and view theaters showing it.
*   Select a theater and see available showtimes.
*   View available seats for a selected show.
*   Book one or more available seats concurrently (basic concurrency handling implemented).
*   In-memory data storage (no external database).
*   Unit tests using Catch2.
*   (Bonus) Conan package management.
*   (Bonus) Docker support.
*   (Bonus) Doxygen documentation (Only instructions are here).

## Prerequisites

*   **C++ Compiler:** A C++ compiler supporting C++17 or later (e.g., GCC, Clang, MSVC).
*   **CMake:** Version 3.10 or later.
*   **(Optional) Conan:** For dependency management (if you want to use the Conan feature).
*   **(Optional) Docker:** For building and running the service in a container.
*   **(Optional) Doxygen:** For generating API documentation.

## Project Structure

```
movie-booking-service/
├── include/          # Header files for the service and data models
├── src/              # Source files for the implementation
├── tests/            # Unit tests using Catch2
├── CMakeLists.txt    # CMake build configuration
├── conanfile.py      # (Bonus) Conan package definition
├── Dockerfile        # (Bonus) Dockerfile for containerization
└── README.md         # This file
```

## Building and Running

### 1. Build Options

#### **a) Manual Build (without Conan)**

1. **Install Catch2:**

    *   **Using a package manager:** If you have a package manager like `vcpkg` or `apt-get`, you can install Catch2 using it (e.g., `vcpkg install catch2`, `sudo apt-get install catch2`).
    *   **Manual installation:** Download Catch2 from [https://github.com/catchorg/Catch2](https://github.com/catchorg/Catch2) and follow its installation instructions. Make sure CMake can find it.

2. **Build with CMake:**

    ```bash
    mkdir build
    cd build
    cmake ..
    cmake --build .
    ```

#### **b) Build with Conan (Bonus)**

1. **Install Conan:**

    ```bash
    pip install conan
    ```

2. **Build using Conan:**

    ```bash
    mkdir build
    cd build
    conan install .. --build=missing # Install dependencies and build missing packages
    cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake
    cmake --build .
    ```

### 2. Run Unit Tests

After a successful build (either manual or with Conan), run the unit tests:

```bash
cd build
./booking_service_tests
```

### 3. Run the Service (Standalone/CLI - Not Implemented in Code)

```bash
./booking_service
```
if there would be some main.cpp as the main app and if it was compiled to an executable named `booking_service`, otherwise use the arbitrary name for compiling and running, this was just an example of how it might be called. 

### 4. Docker Build and Run (Bonus)

1. **Build the Docker image:**

    ```bash
    docker build -t movie-booking-service .
    ```

2. **Run the Docker container:**

    ```bash
    docker run -it movie-booking-service
    ```

## API Documentation (Bonus - Doxygen)

Generate the API documentation as follows:

1. **Install Doxygen:**
    ```bash
    sudo apt-get install doxygen 
    ```
2. **Generate documentation:**
    ```bash
    doxygen Doxyfile # Assuming there is a Doxyfile configuration in the project root with all of the necessary flags ON/OFF, like dot graphs
    ```
    This will typically create an `html` folder containing the generated documentation.

## Data Persistence

The current implementation uses in-memory data storage. For a more robust solution,  the idea would be to implement data persistence using:

*   **File Storage:** Store data in a file (e.g., JSON, XML, or a custom format) and load/save it on service startup/shutdown.
*   **Database:** Integrate with a lightweight database like SQLite.
