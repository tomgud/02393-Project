//
//  main.cpp
//  Exercises
//
//  Created by Elvar Örn Unnþórsson on 3/12/2011.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include <math.h>

using namespace std;


class Vector2d 
{
    private:
        double x; // X Coordinate
        double y; // Y Coordinate
        
    public:
        Vector2d(double _x, double _y) {
            this->x = _x;
            this->y = _y;
        }
        
        ~Vector2d() {
        }
    
        double getX() {
            return this->x;
        }
        
        double getY() {
            return this->y;
        }
    
        void addition( double xAdd, double yAdd ) {
            this->x += xAdd;
            this->y += yAdd;
        }
        
        void scalar( double scalar ) {
            this->x *= scalar;
            this->y *= scalar;
        }
        
        double product( double xOther, double yOther ) {
            return this->x * xOther + this->y * yOther;
        }
    
        double product( Vector2d other ) {
            return this->x * other.getX() + this->y * other.getY();
        }
        
        double length( ) {
            return sqrt( this->x + this->y );
        }
};


template <typename T>
class VectorNd
{
    private:
    T *array;
    int capacity;
    
    public:
    VectorNd( int capacity = 1 ) {
        this->capacity = capacity;
        array = new T[capacity];
    }
    
    
};

int main (int argc, const char * argv[])
{
    Vector2d myVector = Vector2d( 1, 1 );
    
    cout << "Vector created with x: " << myVector.getX() << " y: " << myVector.getY() << endl;
    
    
    cout << "Testing addition" << endl;
    myVector.addition(1, 1);
    cout << "Should see x=2 and y=2. Results => x: " << myVector.getX() << " y: " << myVector.getY() << endl << endl;
    
    
    cout << "Testing scalar" << endl;
    myVector.scalar( 2 );
    cout << "Should see x=4 and y=4. Results => x: " << myVector.getX() << " y: " << myVector.getY() << endl << endl;
    
    
    cout << "Testing product" << endl;
    cout << "Should see 32. Results => " << myVector.product( 4, 4 ) << endl;
    cout << "Should see 32. Results => " << myVector.product( Vector2d( 4, 4 ) ) << endl << endl;
    
    
    cout << "Testing length" << endl;
    cout << "Should see 2.82 Results => " << myVector.length() << endl << endl;
    
    
    //VectorNd<Vector2d> myVectorStorage;
    
    return 0;
}

