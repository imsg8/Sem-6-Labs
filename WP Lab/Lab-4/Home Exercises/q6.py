import math

class Circle:
    def __init__(self, radius):
        self.radius = radius
    
    def area(self) -> float:
        return math.pi * self.radius ** 2
    
    def perimeter(self) -> float:
        return 2 * math.pi * self.radius

circle = Circle(5)
print("Circle radius:", circle.radius)
print("Area:", circle.area())
print("Perimeter:", circle.perimeter())
