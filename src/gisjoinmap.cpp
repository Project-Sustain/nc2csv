//
// Created by breadcrumbs on 8/16/21.
//

#include "gisjoinmap.h"

#include <utility>

Point::Point(double _lat, double _lng)
        : lat(_lat), lng(_lng) { }

bool Point::operator==(const Point &other) const {
    return lat == other.lat && lng == other.lng;
}

GISJOINMapper::GISJOINMapper(const std::string &host, int port, std::function<void(GISJOINMap)> _flush_function)
    : redis("tcp://" + host + ":" + std::to_string(port)),
      pipe(redis.pipeline()),
      flush_function(std::move(_flush_function)) { }

void GISJOINMapper::queue(const Point &p) {
    if (requested_points.find(p) != requested_points.end()) {
        return;
    }
    requested_points.emplace(p);

    pipe.exists()
}

void GISJOINMapper::flush() {
    for (const Point &p : requested_points) {
        std::unordered_set<std::string> GISJOINs;
    }
}
