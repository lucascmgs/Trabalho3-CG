#ifndef SEGMENT_H
#define SEGMENT_H

#include "Point.h"

using namespace std;

class Segment {
    public:
    Point From;
    Point To;

    Segment(const Point givenFrom, const Point givenTo){
        this->From = givenFrom;
        this->To = givenTo;
    }

    Point Vectorialize(){
        return this->To - this->From;
    }

    bool Intercepts (Segment& operated){

        Point tFrom = this->From;
        Point tTo = this->To;
        Point oFrom = operated.From;
        Point oTo = operated.To;

        cout<< "First segment:" << endl;
        cout << "From point (" << this->From.x << "," << this->From.y << ")" << 
            " to point (" << this->To.x << "," << this->To.y << ")" << endl;  
        cout<< "Second segment:" << endl;
        cout << "From point (" << operated.From.x << "," << operated.From.y << ")" << 
            " to point (" << operated.To.x << "," << operated.To.y << ")" << endl;  

        Point AB = oTo - oFrom;
        Point AD = tTo - oFrom;
        Point AC = tFrom - oFrom;

        Point CD = tTo - tFrom;
        Point CA = oFrom - tFrom;
        Point CB = oTo - tFrom;

        double ABAD = AB.ZProdVec(AD);
        double ABAC = AB.ZProdVec(AC);

        double CDCA = CD.ZProdVec(CA);
        double CDCB = CD.ZProdVec(CB);

        cout << ABAD << " " << ABAC << endl << CDCA << " " << CDCB << endl << "-----------" << endl ; 

        double firstRes = ABAD * ABAC ;
        double secondRes = CDCA * CDCB ;

        //cout << firstRes << " " << secondRes << endl;
        return (firstRes < 0 && secondRes < 0);
    }
};

#endif