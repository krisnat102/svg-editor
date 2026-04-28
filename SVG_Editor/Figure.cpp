#include <string>
#include <iostream>
#include "Figure.h"

double getDistance(unsigned x1, unsigned y1, unsigned x2, unsigned y2) {
    double dx = (double)x1 - (double)x2; // so that it doesnt overflow as unsigned
    double dy = (double)y1 - (double)y2;
    return std::sqrt(std::pow(dx, 2) + std::pow(dy, 2));
}

#pragma region Rectangle

std::string Rectangle::toString() const {
    return "<rect x='" + std::to_string(x)
        + "' y='" + std::to_string(y) 
        + "' width='" + std::to_string(sizeX)
        + "' height='" + std::to_string(sizeY)
        + "' fill='" + fillColor
        + "' />";
}

std::string Rectangle::info() const {
    return "rectangle " + std::to_string(x) + " " + std::to_string(y) + " "
        + std::to_string(sizeX) + " " + std::to_string(sizeY) + " " + fillColor;
}

bool Rectangle::isWithinRectangle(unsigned rx, unsigned ry, unsigned rw, unsigned rh) const {
    return (x >= rx) && (y >= ry) && (x + sizeX <= rx + rw) && (y + sizeY <= ry + rh);
}

bool Rectangle::isWithinCircle(unsigned cx, unsigned cy, unsigned r) const {
    return getDistance(x, y, cx, cy) <= r &&
        getDistance(x + sizeX, y, cx, cy) <= r &&
        getDistance(x, y + sizeY, cx, cy) <= r &&
        getDistance(x + sizeX, y + sizeY, cx, cy) <= r;
}

#pragma endregion

#pragma region Ellipse

std::string Ellipse::toString() const {
    return "<ellipse cx='" + std::to_string(x)
        + "' cy='" + std::to_string(y)
        + "' rx='" + std::to_string(radiusX)
        + "' ry='" + std::to_string(radiusY)
        + "' fill='" + fillColor
        + "' />";
}

std::string Ellipse::info() const {
    return "ellipse " + std::to_string(x) + " " + std::to_string(y) + " "
        + std::to_string(radiusX) + " " + std::to_string(radiusY) + " " + fillColor;
}

bool Ellipse::isWithinRectangle(unsigned rx, unsigned ry, unsigned rw, unsigned rh) const {
    return (x >= rx + radiusX) && (y >= ry + radiusY) &&
        (x + radiusX <= rx + rw) && (y + radiusY <= ry + rh);
}

bool Ellipse::isWithinCircle(unsigned cx, unsigned cy, unsigned r) const {
    unsigned maxRadius = std::max(radiusX, radiusY);
    return getDistance(x, y, cx, cy) + maxRadius <= r;
}

#pragma endregion

#pragma region Line

std::string Line::toString() const {
    return "<line x1='" + std::to_string(x)
        + "' y1='" + std::to_string(y)
        + "' x2='" + std::to_string(x2)
        + "' y2='" + std::to_string(y2)
        + "' stroke-width='" + std::to_string(strokeWidth) 
        + "' />";
}

std::string Line::info() const {
    return "line " + std::to_string(x) + " " + std::to_string(y) + " "
        + std::to_string(x2) + " " + std::to_string(y2) + " stroke-width: "
        + std::to_string(strokeWidth);
}

bool Line::isWithinRectangle(unsigned rx, unsigned ry, unsigned rw, unsigned rh) const {
    return (x >= rx && x <= rx + rw && y >= ry && y <= ry + rh) &&
        (x2 >= rx && x2 <= rx + rw && y2 >= ry && y2 <= ry + rh);
}

bool Line::isWithinCircle(unsigned cx, unsigned cy, unsigned r) const {
    return getDistance(x, y, cx, cy) <= r &&
        getDistance(x2, y2, cx, cy) <= r;
}

#pragma endregion

void Figure::move(unsigned x, unsigned y)
{
    this->x += x;
    this->y += y;
}