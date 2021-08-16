#ifndef NC2CSV_GISJOINMAP_H
#define NC2CSV_GISJOINMAP_H

#include <string>
#include <sw/redis++/redis++.h>
#include <functional>
#include <unordered_map>
#include <unordered_set>

struct Point {
    Point(double _lat, double _lng);
    Point(const Point &other) = default;
    Point &operator=(const Point &other) = default;

    bool operator==(const Point &other) const;

    double lat;
    double lng;
};

template<>
struct std::hash<Point> {
public:
    size_t operator()(const Point &point) const {
        std::hash<double> hasher;
        return hasher(point.lat) ^ hasher(point.lng);
    }

    std::string to_string(size_t precision) const {

    }
};

class GISJOINMapper {
public:
    using GISJOINMap = std::unordered_map<Point, std::string>;

    const size_t PIPE_MAX_SIZE = 10000;

    GISJOINMapper(const std::string& host, int port, std::function<void(GISJOINMap)> _flush_function);
    void queue(const Point &p);
    void flush();
private:
    sw::redis::Redis redis;
    sw::redis::Pipeline pipe;
    std::function<void(GISJOINMap)> flush_function;
    std::unordered_set<Point> requested_points{};
};

#endif //NC2CSV_GISJOINMAP_H
