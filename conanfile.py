from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout

class MovieBookingServiceConan(ConanFile):
    name = "movie-booking-service"
    version = "0.1"
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {"shared": False, "fPIC": True}
    exports_sources = "CMakeLists.txt", "include/*", "src/*", "tests/*"
    requires = "catch2/3.5.2"  # Add Catch2 dependency, since it also exists as a public conan package

    def layout(self):
        cmake_layout(self)

    def generate(self):
        tc = CMakeToolchain(self)
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()