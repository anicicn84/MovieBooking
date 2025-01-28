FROM ubuntu:latest

# Install dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git

# Install Conan if needed
# RUN pip install conan

# Clone the repository here if this was on the git repo
WORKDIR /app
COPY . .

# Conan install
# RUN conan install . -s build_type=Release

# Build the project
RUN mkdir build && cd build && \
    cmake .. && \
    cmake --build .

# Run unit tests (optional)
# RUN ./booking_service_tests

# Define the entry point for the standalone service
# CMD ["./booking_service"]