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

TEST_CASE("Provides defaults") {
    Args a = parse_args({ "one_file.nc" });

    REQUIRE(a.abort == false);
    REQUIRE(a.concurrency == 3);
    REQUIRE(a.time_property == "time");
    REQUIRE(a.lat_property == "lat");
    REQUIRE(a.lon_property == "lon");
}

