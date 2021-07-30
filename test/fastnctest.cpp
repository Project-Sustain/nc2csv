#include "doctest.h"
#include "../src/fastnc.h"
#include "../src/write.h"
#include <sstream>

TEST_CASE("Can open a one-var netCDF file with default settings") {
    FastNcFile f("../resources/tos_example.nc");

    REQUIRE(f.basic_dims[0] == "time");
    REQUIRE(f.basic_dims[1] == "lat");
    REQUIRE(f.basic_dims[2] == "lon");

    REQUIRE(f.wanted_variables == std::set<std::string>{ "tos" });
}

TEST_CASE("Can write a one-var netCDF file with default settings") {
    FastNcFile f("../resources/tos_example.nc");

    std::stringstream ss;
    write_header(f, ss);

    ss.flush();
    REQUIRE(ss.str() == "time,lat,lon,sea_surface_temperature,\n");

    std::function<std::string(double)> dummy_mapper = [](double) { return "dummy_time"; };
    write_data(f, ss, dummy_mapper);

    // Very superficial tests - the full dataset is over 700 records.
    std::string line;
    std::getline(ss, line);
    std::getline(ss, line);
    REQUIRE(line == "dummy_time,-78.5000,181.0000,275.8637");
    std::getline(ss, line);
    REQUIRE(line == "dummy_time,-77.5000,165.0000,275.6657");
}

TEST_CASE("File with inconsistent variable sizes cannot open") {
    REQUIRE_THROWS_AS(FastNcFile("../resources/ncar_example.nc"), std::runtime_error);
    REQUIRE_THROWS_AS(FastNcFile("../resources/ncar_example.nc", { "plev", "pr" }), std::runtime_error);
    REQUIRE_THROWS_AS(FastNcFile("../resources/ncar_example.nc", { "ua", "plev" }), std::runtime_error);
    REQUIRE_THROWS_AS(FastNcFile("../resources/ncar_example.nc", { "plev", "pr", "ua" }), std::runtime_error);
}

TEST_CASE("Can open file with inconsistent variable sizes given consistent variable list") {
    FastNcFile f("../resources/ncar_example.nc", { "pr", "tas" });
}
