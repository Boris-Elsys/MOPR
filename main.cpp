#include <iostream>
#include <valarray>

using namespace std;

class Point {

    int x;
    int y;

public:

    Point() : x(0), y(0) {}
    Point(int x, int y) : x(x), y(y) {}

    int getX() const { return x; }
    int getY() const { return y; }

    void setX(int x) { this->x = x; }
    void setY(int y) { this->y = y; }

    friend std::ostream& operator<<(std::ostream& os, const Point& p){
        os << "(" << p.x << ", " << p.y << ")";
        return os;

    }

    friend std::istream& operator>>(std::istream& is, Point& p) {
        is >> p.x;
        is >> p.y;

        return is;

    }

};

class Vector {

    int x;
    int y;

public:

    Vector() : x(0), y(0) {}
    Vector(int x, int y) : x(x), y(y) {}

    Vector(const Point p1, const Point p2) {

        this->x = p2.getX() - p1.getX();
        this->y = p2.getY() - p1.getY();
    }

    int getX() const { return x; }

    int getY() const { return y; }

    friend std::ostream& operator<<(std::ostream& os, const Vector& v) {
        os << "(" << v.x << ", " << v.y << ")";
        return os;}
    friend std::istream& operator>>(std::istream& is, Vector& v) {
        is >> v.x;
        is >> v.y;
        return is; }

    Vector sum(const Vector& other) const {

        Vector vector(other.x + this->x, other.y + this->y);

        return vector;
    }

    Vector times_num(int num) const {

        Vector vector(this->x * num, this->y * num);

        return vector;
    }

    bool is_colinear(const Vector& other) const {

        //За да бъдат два вектора колинеарни трябва съотношението между x-овете и съотношението между y-ците им да е равно
        //За избягване на проблеми при деление с нулеви вектори уравнението се умножава на кръст
        int isColinear = 0;
        if(this->x * other.y == this->y * other.x){ isColinear++; }

        return isColinear;
    }

    double length() const {

        double len = sqrt(pow(this->x, 2) + pow(this->y, 2));

        return len;
    }

    int dot_product(const Vector& other) const {

        int product = (this->x * other.x) + (this->y * other.y);

        return product;
    }

    int area(const Vector v1, const Vector v2) {

        //Намира се дължината на двата дадени вектора
        double a = v1.length();
        double b = v2.length();
        //Намира се дължината на третата страна на триъгълника която е равна на дължината на сбора на двата вектора
        double c = (v1.sum(v2)).length();
        //Пресмята се полупериметъра на триъгълника
        double p = (a + b + c) / 2.0;
        //Имайки полупериметъра и страните на триъгълника чрез хероновата формула се пресмята лицето на триъгълника
        double S = sqrt(p * (p - a) * (p - b) * (p - c));

        return S;
    }
};

class Line {
    int A, B, C;

public:
    Line(int A = 0, int B = 0, int C = 0) : A(A), B(B), C(C) {}
    Line(const Point p, const Vector& v) {

        this->A = v.getY();
        this->B = -v.getX();
        this->C = -(A * p.getX() + B * p.getY());
    }
    Line(const Point p1, const Point p2) {

        //Чрез дадените 2 точки инстанцирам вектор като с него и първата ми дадена точка мога да и използвам метода за конструиране на права имплементиран горе

        Vector v1(p1, p2);

        this->A = v1.getY();
        this->B = -v1.getX();
        this->C = -(A * p1.getX() + B * p1.getY());
    }

    int getA() const { return A; }
    int getB() const { return B; }
    int getC() const { return C; }

    friend std::ostream& operator<<(std::ostream& os, const Line& l){
        os << l.A << "x + "<< l.B << "y + "<< l.C << " = 0 ";
        return os;
    }
    friend std::istream& operator>>(std::istream& is, Line& l){
        is >> l.A;
        is >> l.B;
        is >> l.C;
        return is;
    }


    bool are_parallel(const Line& other) const {

        //За да бъдат две прави паралелни трябва съотношението между A-тата и съотношението между B-тата им да е равно, наклоните им да са равни
        //За избягване на проблеми при деление на нула уравнението се умножава на кръст

        int areParallel = 0;
        if(this->A * other.B == this->B * other.A){ areParallel++; }

        return areParallel;
    }

    bool is_orthogonal(const Line& other) const {

        //За да бъдат две прави ортогонални трябва те да са перпендикулярни в точката на пресичане
        //От формулата ((A1 / B1) * (A2 / B2) + 1) / (A2 / B2) - (A1 / B1) = 0 извеждаме (А1 / В1) * (A2 / B2) = -1
        //А него представяме като A1 / B1 = -(B2 / A2) което след умножение на кръст става A1 * B1 + B2 * A2 = 0

        int isOrthogonal = 0;
        if(((this->A * other.A) + (this->B * other.B)) == 0){ isOrthogonal++; }

        return isOrthogonal;
    }

    Vector colinear() const {

        return Vector(-(this->B), this->A);
    }

    Vector orthogonal() const {

        return Vector(this->A, this->B);
    }

    Line parallel(const Point p) const {

        return Line(p, this->colinear());
    }

    Line orthogonal(const Point p) const {

        return Line(p, this->orthogonal());
    }

};

class Ball {

    Point center;
    double diameter;

public:

    Ball(const Point& center, double diameter) : center(center), diameter(diameter) {}
    Ball() : center(0, 0), diameter(0) {}
    Ball(Ball const& other) : center(other.center), diameter(other.diameter) {}

    Point getCenter() const { return center; }
    double getDiameter() const { return diameter; }
    double getRadius() const { return diameter / 2.0; }
    void setCenter(const Point& center) { this->center = center; }
    void setCenter(int x, int y) { this->center = Point(x, y); }
    void setDiameter(double diameter) { this->diameter = diameter; }

    friend std::ostream& operator<<(std::ostream& os, const Ball& b) {

        os << "Center: " << b.center << " Diameter: " << b.diameter;
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Ball& b) {

        is >> b.center;
        is >> b.diameter;
        return is;
    }

    void moveBall(Point point, int power) {

            //Преместваме топката със силата power в посоката на вектора от центъра на топката до точката p

            Vector v(this->getCenter(), point);
            v.times_num(power);
            this->setCenter(v.getX() + this->getCenter().getX(), v.getY() + this->getCenter().getY());

    }


};

class Board {

    Point p1;
    Point p2;
    Point p3;
    Point p4;

public:

    Board(Point p1, Point p3) : p1(p1), p2(p1.getX(), p3.getY()), p3(p3), p4(p3.getX(), p1.getY()) {}

    Board(Point p1, Point p2, Point p3, Point p4) : p1(p1), p2(p2), p3(p3), p4(p4) {}

    friend std::ostream& operator<<(std::ostream& os, const Board& b) {

        os << "P1: " << b.p1 << " P2: " << b.p2 << " P3: " << b.p3 << " P4: " << b.p4;
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Board& b){

        is >> b.p1;
        is >> b.p2;
        is >> b.p3;
        is >> b.p4;
        return is;
    }


    bool isInside(const Ball& ball) const{
        if(ball.getCenter().getX() <= p3.getX() && ball.getCenter().getX() >= p1.getX()
        && ball.getCenter().getY() <= p3.getY() && ball.getCenter().getY() >= p1.getY()){
            return true;
        }
        return false;

    }

    Point getSimmetrical(Ball ball) const{

        int x = ball.getCenter().getX();
        int y = ball.getCenter().getY();

        if(x < p1.getX()){
            ball.setCenter(p1.getX() + abs(p1.getX() - x), y);

        }else if(x > p3.getX()){
            ball.setCenter(p3.getX() - abs(p3.getX() - x), y);
        }

        if(y < p1.getY()){
            ball.setCenter(x, p1.getY() + abs(p1.getY() - y));
        }else if(y > p3.getY()){
            ball.setCenter(x, p3.getY() - abs(p3.getY() - y));
        }

    }

    int hitBall(Ball& ball, Point& point, unsigned int power){

        p1.setX(p1.getX() + ball.getRadius());
        p1.setY(p1.getY() + ball.getRadius());

        p3.setX(p3.getX() - ball.getRadius());
        p3.setY(p3.getY() - ball.getRadius());

        Board board(p1, p3);

        Ball tempBall(ball);
        tempBall.moveBall(point, power);

        while(!board.isInside(tempBall)){
            tempBall.setCenter(getSimmetrical(tempBall));

        }

        ball = tempBall;

    }

};

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
