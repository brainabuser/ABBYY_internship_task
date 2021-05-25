#include <iostream>
#include <vector>
#include <cmath>

template<class T>
class Vector;

template<class T>
class Point {
  public:
    Point() = default;
    Point(const T &x, const T &y) : x_(x), y_(y) {}
  private:
    T x_, y_;
    template<class P>
    friend P getDistance(const Point<P> &lhs, const Point<P> &rhs);

    friend class Vector<T>;
};

template<class T>
class Vector {
  public:
    Vector() = default;
    explicit Vector(const Point<T> &begin, const Point<T> &end) :
            begin_(begin), end_(end), x_(end_.x_ - begin_.x_), y_(end_.y_ - begin_.y_) {}

  private:
    Point<T> begin_, end_;
    T x_, y_;
    template<class P>
    friend P scalarProduct(const Vector<P> &lhs, const Vector<P> &rhs);
    template<class P>
    friend P vectorProduct(const Vector<P> &lhs, const Vector<P> &rhs);
};

template<class T>
class Figure {
  public:
    virtual T getArea() const = 0;
};

template<class T>
class Circle : public Figure<T> {
  public:
    Circle() = default;
    explicit Circle(const std::vector<Point<T>> &points) {
        if (points.size() != 2) {
            throw std::invalid_argument("For circle it should be 2 arguments");
        }
        center_ = points.front();
        auto circle_point = *next(points.begin(), 1);
        radius_ = getDistance(center_, circle_point);
    }
    T getArea() const override;
  private:
    T radius_;
    Point<T> center_;
};

template<class T>
class Triangle : public Figure<T> {
  public:
    Triangle() = default;
    explicit Triangle(const std::vector<Point<T>> points) {
        if (points.size() != 3) {
            throw std::invalid_argument("For triangle it should be 3 arguments");
        }
        a_ = points.front();
        b_ = *next(points.begin(), 1);
        c_ = *next(points.begin(), 2);
    }
    T getArea() const override;
  private:
    Point<T> a_, b_, c_;
};

template<class T>
class Rectangle : public Figure<T> {
  public:
    Rectangle() = default;
    explicit Rectangle(const std::vector<Point<T>> &points) {
        if (points.size() != 4) {
            throw std::invalid_argument("For Rectangle it should be 4 arguments");
        }
        a_ = points.front();
        b_ = *next(points.begin(), 1);
        c_ = *next(points.begin(), 2);
        d_ = *next(points.begin(), 3);
    }
    T getArea() const override;
  private:
    Point<T> a_, b_, c_, d_;
};

template<class T>
T getArea(const Figure<T> &figure) {
    return figure.getArea();
}

int main() {
    //Circle, Rectangle, Triangle tests
    std::vector<Point<long double>> circle_points({{0., 0.},
                                                   {1., 0.}});
    std::vector<Point<long double>> rectangle_points({{0., 0.},
                                                      {0., 7.},
                                                      {6., 7.},
                                                      {6., 0.}});
    std::vector<Point<long double>> triangle_points({{3., 4.},
                                                     {0., 4.},
                                                     {3., 0.}});
    try {
        auto area = getArea(Circle<long double>(circle_points));
        std::cout << "Circle area = " << area << std::endl;
    } catch (std::invalid_argument &e) {
        std::cout << e.what() << std::endl;
    }
    try {
        auto area = getArea(Rectangle<long double>(rectangle_points));
        std::cout << "Rectangle area = " << area << std::endl;
    } catch (std::invalid_argument &e) {
        std::cout << e.what() << std::endl;
    }
    try {
        auto area = getArea(Triangle<long double>(triangle_points));
        std::cout << "Triangle area = " << area << std::endl;
    } catch (std::invalid_argument &e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}

template<class T>
T getDistance(const Point<T> &lhs, const Point<T> &rhs) {
    return sqrt(pow(lhs.x_ - rhs.x_, 2) + pow(lhs.y_ - rhs.y_, 2));
}

template<class T>
T scalarProduct(const Vector<T> &lhs, const Vector<T> &rhs) {
    return lhs.x_ * rhs.x_ + lhs.y_ * rhs.y_;
}

template<class T>
T getLength(const Vector<T> &v) {
    return sqrt(scalarProduct(v, v));
}

template<class T>
T vectorProduct(const Vector<T> &lhs, const Vector<T> &rhs) {
    return lhs.x_ * rhs.y_ - lhs.y_ * rhs.x_;
}

template<class T>
T Circle<T>::getArea() const {
    return M_PI * radius_ * radius_;
}

template<class T>
T Triangle<T>::getArea() const {
    Vector<T> lhs(a_, b_), rhs(a_, c_);
    return 1. / 2 * fabsl(vectorProduct(lhs, rhs));
}

template<class T>
T Rectangle<T>::getArea() const {
    Vector lhs(a_, b_), rhs(b_, c_);
    auto lhs_len = getLength(lhs);
    auto rhs_len = getLength(rhs);
    return lhs_len * rhs_len;
}