# Types

## Every C++ variable is defined with a type, becasue C++ is a strongly typed language.

## There are two variance of types

- Fundamental Types (**primitives**)
  - These are built in types in the language like: int, float, ...etc.
  - STL also has additional types such as std::size_t and std::string.
  
- User-Defined Types
A type that can be built to aggregate and store data in way that suits the context of a program such as struct and class.

## Struct example

``` cpp
struct Date{
    int day;
    int month;
    int year;
};

// Create an instance of the Date structure
Date date;
// Initialize the attributes of Date
date.day = 1;
date.month = 10;
date.year = 2019;
```
