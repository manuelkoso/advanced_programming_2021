//two different ways
//1
//This work in all compiler
//#ifndef _MY_CLASS_H_  //if not defined => define it in your file
//#define _MY_CLASS_H_  //the name of the macro must be similar to the file name

//#endif

//2
#pragma once //pragma is a directive for compiler
            //the preprocessor take care that this file is included only once
class point {
double x,y;
public:
  void print(); //I want to implement it in another file (my_class.cpp)
};
