#ifndef NC2CSV_CFDIMS_H
#define NC2CSV_CFDIMS_H

#include <string>

struct DimValues {
    double time;
    double lat;
    double lon;
};

struct VariableMetadata {
    double missing_value;
    size_t length;
    std::string standard_name;
};

const std::vector<std::string> CF_DEFAULT_BASIC_DIMS{"time", "lat", "lon"};
const std::vector<std::string> CF_STANDARD_DIMS{"time", "lat", "lon", "crs", "time_bnds", "lat_bnds", "lon_bnds", "crs_bnds", "area", "msk_rgn"};

#endif //NC2CSV_CFDIMS_H
