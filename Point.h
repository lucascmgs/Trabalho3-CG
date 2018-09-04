#ifndef POINT_H
#define POINT_H
#include <iostream>
#include <cmath>

using namespace std;

class Point {
    public:
        double x;
        double y;
        bool in;
        float Color[3] = {0.0, 0.0, 1.0};
    friend ostream& operator<<(ostream& os, const Point& givenPoint);  


    Point(){
        this->x = 0;
        this->y = 0;
        this->Color[2] = 1.0;
    }

    Point(double givenX, double givenY){
        this->x = givenX;
        this->y = givenY;
    }

    void SetColor(float red, float green, float blue){
        this->Color[0] = red;
        this->Color[1] = green;
        this->Color[2] = blue;
    }

    double Scalar (const Point& operated){
        return this->x * operated.x + this->y * operated.y;
    }

    double ZProdVec (const Point& operated){
        return(this->x * operated.y - this->y * operated.x);
    }

    double GetLength (){
        return sqrt(pow(this->x, 2) + pow(this->y, 2));
    }

    double GetAngle(Point& operated){
        return acos((this->Scalar(operated))/(this->GetLength() * operated.GetLength()));
    }

    double GetOrientedAngle(Point& operated){
        
        double angle = this->GetAngle(operated);
        if(this->ZProdVec(operated) > 0){
            return angle;
        } else {
            return -angle;
        }
    }

    Point MiddlePoint(const Point& operated){
        return Point((this->x + operated.x)/2., (this->y + operated.y)/2.);
    }

    double Distance(const Point& operated){
        double resultX = operated.x - this->x;
        double resultY = operated.y - this->y;
        return sqrt(pow(resultX, 2) + pow(resultY, 2));
    }

    Point operator+ (const Point& operated){
        return Point(this->x + operated.x, this->y + operated.y);
    }

    bool operator== (const Point& operated){
        return this->x == operated.x && this->y == operated.y;
    }


    bool operator!= (const Point& operated){
        return this->x != operated.x && this->y != operated.y;
    }


    Point operator- (const Point& operated){
        return Point(this->x - operated.x, this->y - operated.y);
    }

    Point operator* (const double k){
        return Point(this->x * k, this->y * k);
    }

    Point& operator+= (const Point& operated){
        this->x += operated.x;
        this->y += operated.y;

        return *this;
    }

    Point& operator*= (const double escalar){
        this->x *= escalar;
        this->y *= escalar;

        return *this;
    }
};

ostream& operator<< (ostream& os, const Point& givenPoint){  
        os << "X: " << givenPoint.x << " Y: " << givenPoint.y;  
        return os;  
}  

#endif