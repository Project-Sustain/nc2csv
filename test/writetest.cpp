#include "doctest.h"
#include "../src/fastnc.h"
#include "../src/write.h"
#include "../src/args.h"
#include <functional>
#include <sstream>
#include <algorithm>

TEST_CASE("Can write a one-var netCDF file with default settings") {
    FastNcFile f("../resources/tos_example.nc");

    std::stringstream ss;
    write_header(f, ss);

    ss.flush();
    REQUIRE(ss.str() == "time,lat,lon,sea_surface_temperature\n");

    std::function<std::string(double)> dummy_mapper = [](double) { return "dummy_time"; };
    write_data(f, ss, dummy_mapper, parse_args({ "" }));

    // Very superficial tests - the full dataset is over 700 records.
    std::string line;
    std::getline(ss, line);
    std::getline(ss, line);
    REQUIRE(line == "dummy_time,-78.5000,-179.0000,275.8637");
    std::getline(ss, line);
    REQUIRE(line == "dummy_time,-77.5000,165.0000,275.6657");
}

/*
TEST_CASE("Can write with scale and offset") {
    FastNcFile f("../resources/gridmet_temp_example.nc", {"day", "lat", "lon"}, {});

    const MetadataMap &metadata = f.get_metadata_view();
    REQUIRE(metadata.at("air_temperature").scale_factor == 0.1);
    REQUIRE(metadata.at("air_temperature").add_offset == 220);
}
 */

TEST_CASE("Can write only dimensions") {
    FastNcFile f("../resources/tos_example.nc");

    std::stringstream ss;
    write_dimensions(f, { "lat", "lon" }, ss);

    ss.flush();
    std::string all_lines = ss.str();
    REQUIRE(170 * 180 + 1 == std::count(all_lines.begin(), all_lines.end(), '\n'));

    std::string line;
    std::getline(ss, line);
    REQUIRE(line == "lat,lon");
    std::getline(ss, line);
    REQUIRE(line == "-79.5000,1.0000");
    std::getline(ss, line);
    REQUIRE(line == "-79.5000,3.0000");
}

TEST_CASE("Can write only specific timestamps") {
    FastNcFile f("../resources/tos_example.nc");

    std::stringstream ss;
    std::function<std::string(double)> dummy_mapper = [] (double time) -> std::string {
        if (time == 345.0) {
            return "2020-01-01T00:00:00";
        } else if (time == 135.0) {
            return "2020-01-03T00:00:00";
        } else {
            return "2020-01-05T00:00:00";
        }
    };

    write_variable(f, "tos", ss, dummy_mapper, parse_args({ "-s", "2020-01-01,2020-01-03", "" }));

    std::string line;
    std::getline(ss, line);
    REQUIRE(line == "2020-01-03T00:00:00,-78.5000,-179.0000,271.9052");
}
