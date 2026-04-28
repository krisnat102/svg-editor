#include <string>
#include <iostream>
#include "Figure.h"

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

#pragma endregion

void Figure::move(unsigned x, unsigned y)
{
    this->x += x;
    this->y += y;
}