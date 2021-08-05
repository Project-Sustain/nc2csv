#include "doctest.h"
#include "../src/cftime.h"

TEST_CASE("Can generate time maps") {
    TimeMapLock lock;

    TimeMap map = get_time_map("../resources/tos_example.nc", "time");
    REQUIRE(map.size() == 24);
    REQUIRE(map[15.0] == "2001-01-16T00:00:00");
    REQUIRE(map[45.0] == "2001-02-16T00:00:00");
    REQUIRE(map[75.0] == "2001-03-16T00:00:00");
    REQUIRE(map[675.0] == "2002-11-16T00:00:00");
    REQUIRE(map[705.0] == "2002-12-16T00:00:00");

    map = get_time_map("../resources/gridmet_example.nc", "day");
    REQUIRE(map.size() == 365);
    REQUIRE(map[33968.0] == "1993-01-01T00:00:00");
    REQUIRE(map[33969.0] == "1993-01-02T00:00:00");
    REQUIRE(map[33970.0] == "1993-01-03T00:00:00");
    REQUIRE(map[34331.0] == "1993-12-30T00:00:00");
    REQUIRE(map[34332.0] == "1993-12-31T00:00:00");
}
