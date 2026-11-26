#ifndef DIMENSIONS_H
#define DIMENSIONS_H

#include <iosfwd>

class Dimensions {
private:
    double height_ = 0;
    double width_ = 0;
    double depth_ = 0;

public:
    Dimensions();
    explicit Dimensions(double height, double width = 0, double depth = 0);
    Dimensions(const Dimensions& other);
    ~Dimensions();

    Dimensions& operator=(const Dimensions& other) = default;

    double getHeight() const;
    double getWidth() const;
    double getDepth() const;

    void setHeight(double height);
    void setWidth(double width);
    void setDepth(double depth);

    friend Dimensions operator+(Dimensions dimensions, double number);
    Dimensions operator-(double number) const;
    Dimensions operator*(double number) const;
    Dimensions operator/(double number) const;

    friend Dimensions operator+(double number, const Dimensions& dimensions);
    friend Dimensions operator-(double number, const Dimensions& dimensions);
    friend Dimensions operator*(double number, const Dimensions& dimensions);
    friend Dimensions operator/(double number, const Dimensions& dimensions);

    Dimensions& operator+=(double number);
    Dimensions& operator-=(double number);
    Dimensions& operator*=(double number);
    Dimensions& operator/=(double number);

    friend std::ostream& operator<<(std::ostream& out, const Dimensions& dimensions);
};

#endif
