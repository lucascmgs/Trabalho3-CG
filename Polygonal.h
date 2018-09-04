#ifndef POLYGONAL_H
#define POLYGONAL_H
#include <iostream>
#include <GL/gl.h>
#include <GL/freeglut.h>
#include "Point.h"
#include "Segment.h"
#include <list> 

using namespace std;

class Polygonal {
    public:
    bool isPolygon = false;
    list<Point> Points;

    void Reset(){
        isPolygon = false;
        Points.clear();
    }

    void Add(Point p){
        if(!this->isPolygon){
            this->Points.push_back(p);
        }
    }

    bool IsPolygon(){
        return this->isPolygon;
    }

    bool CheckInside(Point p){
        if(this->isPolygon){
            int interceptCount = 0;
            Point outerPoint = Point(1.1, 1.1);
            Segment testSegment = Segment(p, outerPoint);
            for (list<Point>::iterator it = this->Points.begin(); it != this->Points.end(); ++it){      
                list<Point>::iterator second;
                second = it;
                second++;
                if(second == this->Points.end()){
                    break;
                }
                
                Segment currentSegment = Segment(*it, *second);

                if(testSegment.Intercepts(currentSegment)){
                    interceptCount++;
                }
            }
            if(interceptCount % 2 == 0) {
                return false;
            } else {
                return true;
            }
        }
        return false;
    }


    void Close (){
        this->isPolygon = true;
    }

    void PlotLines(){
        glBegin(GL_LINE_STRIP);
        for (list<Point>::iterator it = this->Points.begin(); it != this->Points.end(); ++it){   
            Point p = *it;   
            glColor3f(p.Color[0], p.Color[1], p.Color[2]);
            double px = it->x;
            double py = it->y;
            //cout << "X: " << px << " Y: " << py << endl; 
            glVertex2f(px,py);
        }
        glEnd();
    }

    void PlotPoints(){
        glBegin(GL_POINTS);
        for (list<Point>::iterator it = this->Points.begin(); it != this->Points.end(); ++it){      
            Point p = *it;
            glColor3f(p.Color[0], p.Color[1], p.Color[2]);
            double px = it->x;
            double py = it->y;
            //cout << "X: " << px << " Y: " << py << endl; 
            glVertex2f(px,py);
        }
        glEnd();
    }

    list<Point> GetPoints(){
        return this->Points;
    }

    long unsigned int GetSize(){
        return this->Points.size();
    }
    
    Polygonal GetConvexHull(){
        Polygonal result = Polygonal();
        Point base = Point();
        for (list<Point>::iterator it = this->Points.begin(); it != this->Points.end(); ++it){      
            if(it->y < base.y){
                base = *it;
            }
        }
        Point axis = Point(10, 0);
        Point originalBase = base;
        base.SetColor(1, 0, 0);
        result.Add(base);

        int k = 0;
        for (Point newPoint = Point(); newPoint != originalBase;){
            newPoint = Point(); 
            double newAngle = 10;
            cout << "Axis: " << axis << " Base: " << base << endl;     
            for (list<Point>::iterator jt = this->Points.begin(); jt != this->Points.end(); ++jt){ 
                Point comparison = *jt - base;     
                double angle = axis.GetOrientedAngle(comparison); 
                if( *jt != base && angle >= 0 && angle <= newAngle){
                    newAngle = angle;
                    newPoint = *jt;
                }
                cout << "Iteration: " << k << " Point: " << *jt << " Angle with base: " << angle << endl;

            }
            axis = newPoint - base;
            base = newPoint;
            newPoint.SetColor(1, 0, 0);
            result.Add(newPoint);
            k++;
        } 
        int i = 0;
        for(list<Point>::iterator it = result.Points.begin(); it != result.Points.end(); it++){
            cout << "Ponto " << i << ": " <<*it << endl;
            i++;
        }
        result.Close();
        return result;
    }
};

#endif