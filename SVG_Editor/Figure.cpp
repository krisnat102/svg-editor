#include <string>
#include <iostream>

class Figure {
public:
    Figure(int x, int y)
        :x(x),
        y(y)
    {
    }

    virtual ~Figure() {}

    virtual std::string toString() const = 0;
    virtual std::string info() const = 0;

protected:
    int x, y;
};

class Rectangle : public Figure {
public:
    Rectangle(int x, int y, int sizeX, int sizeY, std::string fillColor)
        :Figure(x, y),
        sizeX(sizeX),
        sizeY(sizeY),
        fillColor(fillColor)
    {
    }

    virtual std::string toString() const override;
    virtual std::string info() const override;

private:
    int sizeX, sizeY;
    std::string fillColor;
};

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

class Ellipse : public Figure {
public:
    Ellipse(int x, int y, int rx, int ry, std::string fillColor)
        :Figure(x, y),
        radiusX(rx),
        radiusY(ry),
        fillColor(fillColor)
    {
    }

    virtual std::string toString() const override;
    virtual std::string info() const override;

private:
    int radiusX, radiusY;
    std::string fillColor;
};

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

class Line : public Figure {
public:
    Line(int x1, int y1, int x2, int y2, int strokeWidth)
        :Figure(x1, y1),
        x2(x2),
        y2(y2),
        strokeWidth(strokeWidth)
    {
    }

    virtual std::string toString() const override;
    virtual std::string info() const override;

private:
    int x2, y2, strokeWidth;
};

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

int main() {
    Ellipse el = Ellipse(1, 2, 2, 2, "blue");
    std::cout << el.toString();
}