#include "Dimensions.h"

#include <cmath>
#include <iostream>
#include <stdexcept>

namespace {
    double finiteValue(double value)
    {
        if (!std::isfinite(value)) {
            throw std::overflow_error("Значение выходит за диапазон типа double.");
        }
        return value;
    }
}

Dimensions::Dimensions()
{
    std::cout << "Dimensions: конструктор без параметров.\n";
}

Dimensions::Dimensions(double height, double width, double depth)
    : height_(finiteValue(height)), width_(finiteValue(width)), depth_(finiteValue(depth))
{
    std::cout << "Dimensions: конструктор с параметром.\n";
}

Dimensions::Dimensions(const Dimensions& other)
    : height_(other.height_), width_(other.width_), depth_(other.depth_)
{
    std::cout << "Dimensions: конструктор копирования.\n";
}

Dimensions::~Dimensions()
{
    std::cout << "Dimensions: деструктор.\n";
}

double Dimensions::getHeight() const { return height_; }
double Dimensions::getWidth() const { return width_; }
double Dimensions::getDepth() const { return depth_; }

void Dimensions::setHeight(double height) { height_ = finiteValue(height); }
void Dimensions::setWidth(double width) { width_ = finiteValue(width); }
void Dimensions::setDepth(double depth) { depth_ = finiteValue(depth); }

Dimensions operator+(Dimensions dimensions, double number)
{
    dimensions += number;
    return dimensions;
}

Dimensions Dimensions::operator-(double number) const
{
    return Dimensions(height_ - number, width_ - number, depth_ - number);
}

Dimensions Dimensions::operator*(double number) const
{
    return Dimensions(height_ * number, width_ * number, depth_ * number);
}

Dimensions Dimensions::operator/(double number) const
{
    if (number == 0) {
        throw std::domain_error("Нельзя делить габариты на ноль.");
    }
    return Dimensions(height_ / number, width_ / number, depth_ / number);
}

Dimensions operator+(double number, const Dimensions& dimensions)
{
    return dimensions + number;
}

Dimensions operator-(double number, const Dimensions& dimensions)
{
    return Dimensions(number - dimensions.height_, number - dimensions.width_,
        number - dimensions.depth_);
}

Dimensions operator*(double number, const Dimensions& dimensions)
{
    return dimensions * number;
}

Dimensions operator/(double number, const Dimensions& dimensions)
{
    if (dimensions.height_ == 0 || dimensions.width_ == 0 || dimensions.depth_ == 0) {
        throw std::domain_error("Нельзя делить число на нулевой компонент габаритов.");
    }
    return Dimensions(number / dimensions.height_, number / dimensions.width_,
        number / dimensions.depth_);
}

Dimensions& Dimensions::operator+=(double number)
{
    *this = Dimensions(height_ + number, width_ + number, depth_ + number);
    return *this;
}

Dimensions& Dimensions::operator-=(double number)
{
    *this = *this - number;
    return *this;
}

Dimensions& Dimensions::operator*=(double number)
{
    *this = *this * number;
    return *this;
}

Dimensions& Dimensions::operator/=(double number)
{
    *this = *this / number;
    return *this;
}

std::ostream& operator<<(std::ostream& out, const Dimensions& dimensions)
{
    return out << "(высота " << dimensions.getHeight()
        << ", ширина " << dimensions.getWidth()
        << ", глубина " << dimensions.getDepth() << ')';
}