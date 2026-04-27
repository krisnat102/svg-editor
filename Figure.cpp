#include <string>
#include <iostream>

class Figure {
public:
    Figure(int x, int y, std::string color)
        :x(x),
        y(y),
        fillColor(color)
    {
    }

    virtual std::string toString() const = 0;

protected:
    int x, y;
    std::string fillColor;
};

class Rectangle : public Figure {
public:
    Rectangle(int x, int y, int sizeX, int sizeY, std::string fillColor)
        :Figure(x, y, fillColor),
        sizeX(sizeX),
        sizeY(sizeY)
    {
    }

    virtual std::string toString() const override;

private:
    int sizeX, sizeY;
};

std::string Rectangle::toString() const {
    return "<rect x='" + std::to_string(x)
        + "' y='" + std::to_string(y) 
        + "' width='" + std::to_string(sizeX) 
        + "' height='" + std::to_string(sizeY)
        + "' fill='" + fillColor +"' />";
}

class Ellipse : public Figure {
public:
    Ellipse(int x, int y, int rx, int ry, std::string fillColor)
        :Figure(x, y, fillColor),
        radiusX(rx),
        radiusY(ry)
    {
    }

    virtual std::string toString() const override;

private:
    int radiusX, radiusY;
};

std::string Ellipse::toString() const {
    return "<ellipse cx='" + std::to_string(x)
        + "' cy='" + std::to_string(y)
        + "' rx='" + std::to_string(radiusX)
        + "' ry='" + std::to_string(radiusY)
        + "' fill='" + fillColor + "' />";
}

class Ellipse : public Figure {
public:
    Ellipse(int x, int y, int rx, int ry, std::string fillColor)
        :Figure(x, y, fillColor),
        radiusX(rx),
        radiusY(ry)
    {
    }

    virtual std::string toString() const override;

private:
    int radiusX, radiusY;
};

std::string Ellipse::toString() const {
    return "<ellipse cx='" + std::to_string(x)
        + "' cy='" + std::to_string(y)
        + "' rx='" + std::to_string(radiusX)
        + "' ry='" + std::to_string(radiusY)
        + "' fill='" + fillColor + "' />";
}

// add line

int main() {
    Ellipse el = Ellipse(1, 2, 2, 2, "blue");
    std::cout << el.toString();
}