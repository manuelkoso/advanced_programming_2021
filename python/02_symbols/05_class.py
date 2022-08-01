'''
class
=================

* self
'''

# each class is derived by object (like Java)
class Point:  # if python 2 ---> class Point(object): 
    # self must be in the first place by convention
    def __init__(self, x, y):  # not a real ctor. why? => because we can add a class member even in other functions
        self.x = x
        self.y = y

    def method_with_no_arg(self):  # if you remove self --> error
        print("no args!")

    def update(self, x, y):  # do I really need this? => we can do p.x, p.y = 2, 3 
        self.x = x
        self.y = y

    def print(self):  # is this pythonic?
        print("Point", self.x, self.y)

    def equal(self, other):  # is this pythonic?
        return (self.x, self.y) == (other.x, other.y)

# python doesn't need destructors beacuse it has a garbage collector
# in python everything is public, we cannot have private members



class Point2D:
    """Documention 
    of class Point"""

    def __init__(self, x, y):
        self.x = x
        self.y = y

    def __repr__(self): # for function print(): a string representation of object
        return f"{self.__class__.__name__}({self.x!r}, {self.y!r})" # !r representation formatting

    def __eq__(self, other):
        # return self.x == other.x and self.y == other.y
        return (self.x, self.y) == (other.x, other.y)

    def __abs__(self):
        """return absolute value"""
        import math

        return math.hypot(self.x, self.y)
