//
// Created by jakub on 11/10/15.
//

#include "point.h"

template <class T>
Point<T>::Point(){

}


template <class T>
T &Point<T>::operator[](int i){
    return this->elements[i];
}