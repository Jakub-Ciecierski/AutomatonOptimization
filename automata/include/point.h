//
// Created by jakub on 11/10/15.
//

#ifndef AC_POINT_H
#define AC_POINT_H

#include <vector>

/**
 * Class template for Point
 *
 */
template <class T>
class Point {
private:
    //-----------------------------------------------------------//
    //  PRIVATE FIELDS
    //-----------------------------------------------------------//

    // Stores the elements of the point
    std::vector<T> elements;

public:
    //-----------------------------------------------------------//
    //  CONSTRUCTORS
    //-----------------------------------------------------------//

    /*
     * Creates empty point. No dimensions
     */
    Point();

    /*
     * Creates point with size dimensions
     */
    Point(int size);

    /*
     * Creates a point from data.
     */
    Point(T* data, int count);

    //-----------------------------------------------------------//
    //  PUBLIC METHODS
    //-----------------------------------------------------------//

    /*
     * Adds another dimension to the point.
     */
    void addDimension();

    /*
     * Adds another dimension with element value
     */
    void addDimension(T element);

    /*
     * Returns the size (number of dimensions)
     */
    int size();

    //-----------------------------------------------------------//
    //  OPERATORS
    //-----------------------------------------------------------//

    T &operator[](int i);

    Point<T> operator+(const Point<T>& p);

    Point<T> operator-(const Point<T>& p);
};


#endif //AC_POINT_H
