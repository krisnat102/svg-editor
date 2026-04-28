#pragma once

class Figure {
public:
    Figure(unsigned x, unsigned y)
        :x(x),
        y(y)
    {
    }

    virtual ~Figure() {}

    virtual std::string toString() const = 0;
    virtual std::string info() const = 0;
    virtual void move(unsigned x, unsigned y);
    virtual bool isWithinRectangle(unsigned rx, unsigned ry, unsigned rw, unsigned rh) const = 0;
    virtual bool isWithinCircle(unsigned cx, unsigned cy, unsigned r) const = 0;

protected:
    unsigned x, y;
};

class Rectangle : public Figure {
public:
    Rectangle(unsigned x, unsigned y, unsigned sizeX, unsigned sizeY, std::string fillColor)
        :Figure(x, y),
        sizeX(sizeX),
        sizeY(sizeY),
        fillColor(fillColor)
    {
    }

    virtual std::string toString() const override;
    virtual std::string info() const override;
    virtual bool isWithinRectangle(unsigned rx, unsigned ry, unsigned rw, unsigned rh) const override;
    virtual bool isWithinCircle(unsigned cx, unsigned cy, unsigned r) const override;

private:
    unsigned sizeX, sizeY;
    std::string fillColor;
};

class Ellipse : public Figure {
public:
    Ellipse(unsigned x, unsigned y, unsigned rx, unsigned ry, std::string fillColor)
        :Figure(x, y),
        radiusX(rx),
        radiusY(ry),
        fillColor(fillColor)
    {
    }

    virtual std::string toString() const override;
    virtual std::string info() const override;
    virtual bool isWithinRectangle(unsigned rx, unsigned ry, unsigned rw, unsigned rh) const override;
    virtual bool isWithinCircle(unsigned cx, unsigned cy, unsigned r) const override;

private:
    unsigned radiusX, radiusY;
    std::string fillColor;
};

class Line : public Figure {
public:
    Line(unsigned x1, unsigned y1, unsigned x2, unsigned y2, unsigned strokeWidth)
        :Figure(x1, y1),
        x2(x2),
        y2(y2),
        strokeWidth(strokeWidth)
    {
    }

    virtual std::string toString() const override;
    virtual std::string info() const override;
    virtual bool isWithinRectangle(unsigned rx, unsigned ry, unsigned rw, unsigned rh) const override;
    virtual bool isWithinCircle(unsigned cx, unsigned cy, unsigned r) const override;

private:
    unsigned x2, y2, strokeWidth;
};