#include "doctest.h"
#include "../src/fastnc.h"
#include <sstream>

TEST_CASE("Can open a one-var netCDF file with default settings") {
    FastNcFile f("../resources/tos_example.nc");

    REQUIRE(f.basic_dims[0] == "time");
    REQUIRE(f.basic_dims[1] == "lat");
    REQUIRE(f.basic_dims[2] == "lon");

    REQUIRE(f.wanted_variables == std::set<std::string>{ "tos" });
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

TEST_CASE("Can get arbitrary attributes") {
    netCDF::NcFile f("../resources/gridmet_temp_example.nc", netCDF::NcFile::read);
    netCDF::NcVar var = f.getVar("air_temperature");

    REQUIRE(FastNcFile::get_attribute<double>(var, "scale_factor") == doctest::Approx(0.1));
    REQUIRE(FastNcFile::get_attribute<int>(var, "add_offset") == 220);
    REQUIRE(FastNcFile::get_attribute<std::string>(var, "long_name") == "tmmx");
}