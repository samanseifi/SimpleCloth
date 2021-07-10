//
// Created by saman on 6/21/21.
//

#ifndef BASICROPE_VEC3_H
#define BASICROPE_VEC3_H

#include <iostream>
#include <vector>

#include <cmath>

using namespace std;

/* Simple 2D cartesian vector object for simple mass/spring calculations */
class Vec3 {
public:
    Vec3() {
        this->x = 0.0;
        this->y = 0.0;
        this->z = 0.0;
    };

    Vec3(double x1, double y1, double z1) {
        this->x = x1;
        this->y = y1;
        this->z = z1;
    };

    // Because implicitly-declaration is deprecated
    Vec3(const Vec3 &obj) {
        this->x = obj.x;
        this->y = obj.y;
        this->z = obj.z;
    };


    inline Vec3& operator=(Vec3 const& v) {
        if (this != &v){
            x = v.x;
            y = v.y;
            z = v.z;
        }
        return *this;
    };

    inline Vec3& operator=(double const &val) {
        this->x = val;
        this->y = val;
        this->z = val;

        return *this;
    };

    inline Vec3 operator+(const Vec3& v) const {
        return Vec3(x + v.x, y + v.y, z + v.z);
    };

    inline Vec3& operator*(const double& val) {
        this->x = val*x;
        this->y = val*y;
        this->z = val*z;

        return *this;
    };

    inline Vec3& operator+=(Vec3 &v) {
        this->x = x + v.x;
        this->y = y + v.y;
        this->z = z + v.z;

        return *this;
    };

    inline Vec3& operator*=(double const& scale) {
        this->x = x*scale;
        this->y = y*scale;
        this->z = z*scale;

        return *this;
    };

    inline Vec3 operator-(const Vec3& v) const {
        return Vec3(x - v.x, y - v.y, z - v.z);
    };

    double Magnitude() const {
        return sqrt(x*x + y*y + z*z);
    };

    Vec3 UnitVec() const {
        return Vec3(x/Magnitude(), y/Magnitude(), z/Magnitude());
    };

    void PrintVec() const{
        std::cout << x << " " << y << " " << z  << std::endl;
    };

    double Dot(const Vec3& v) const {
        return x*v.x + y*v.y + z*v.z;
    };

    ~Vec3() = default;

    double y;
    double x;
    double z;
};


#endif //BASICROPE_VEC3_H
