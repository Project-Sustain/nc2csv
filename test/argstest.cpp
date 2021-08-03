#include "doctest.h"
#include "../src/args.h"

TEST_CASE("Fail on empty or no-files arguments") {
    REQUIRE(parse_args({}).abort);
    REQUIRE(parse_args({"-c", "10"}).abort);
    REQUIRE(parse_args({"-c", "10", "-a", "latitude"}).abort);
}

TEST_CASE("Parse single-file argument") {
    Args a = parse_args({ "some_file.nc" });

    REQUIRE(a.abort == false);
    REQUIRE(a.files == std::vector<std::string>{ "some_file.nc" });
}

TEST_CASE("Parse many files") {
    Args a = parse_args({ "some_file.nc", "some_other_file.nc", "another_file.nc", "fourth_file.nc" });

    REQUIRE(a.abort == false);
    REQUIRE(a.files == std::vector<std::string>{ "some_file.nc", "some_other_file.nc", "another_file.nc", "fourth_file.nc" });
}

TEST_CASE("Parse many files and options") {
    Args a = parse_args({ "-c", "7", "-g", "lng", "some_file.nc", "some_other_file.nc", "another_file.nc", "fourth_file.nc" });

    REQUIRE(a.abort == false);
    REQUIRE(a.files == std::vector<std::string>{ "some_file.nc", "some_other_file.nc", "another_file.nc", "fourth_file.nc" });
    REQUIRE(a.concurrency == 7);
    REQUIRE(a.lon_property == "lng");
}

TEST_CASE("Parse dimension list") {
    Args a = parse_args({"-d", "time", "some_file.nc"});

    CHECK(a.dimension_mode == true);
    CHECK(a.standalone_dimensions == std::set<std::string>{"time"});

    a = parse_args({"-d", "lat,lon", "some_file.nc"});

    CHECK(a.dimension_mode == true);
    CHECK(a.standalone_dimensions == std::set<std::string>{"lat", "lon"});

    a = parse_args({"-d", "lat,lon,time", "some_file.nc"});

    CHECK(a.dimension_mode == true);
    CHECK(a.standalone_dimensions == std::set<std::string>{"lat", "lon", "time"});
}

TEST_CASE("Provides defaults") {
    Args a = parse_args({ "one_file.nc" });

    REQUIRE(a.abort == false);
    REQUIRE(a.concurrency == 3);
    REQUIRE(a.time_property == "time");
    REQUIRE(a.lat_property == "lat");
    REQUIRE(a.lon_property == "lon");
    REQUIRE(a.dimension_mode == false);
    REQUIRE(a.standalone_dimensions == std::set<std::string>{});
}

