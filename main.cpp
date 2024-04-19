#include <iostream>
#include <cmath>
#include <vector>
#include <string>
using namespace std;

class Coordinate
{
private:
    int x, y;

public:
    // constructor
    Coordinate(int x, int y) : x(x), y(y) {}

    int getX() const { return x; }
    int getY() const { return y; }

    double distance(const Coordinate &p) const
    {
        return sqrt(pow(p.x - x, 2) + pow(p.y - y, 2));
    }

    void translate(int dx, int dy)
    {
        x += dx;
        y += dy;
    }

    void scale(int factor, bool sign)
    {
        if (sign)
        {
            x *= factor;
            y *= factor;
        }
        else
        {
            x /= factor;
            y /= factor;
        }
    }

    string display() const
    {
        return "X = " + to_string(x) + " Y = " + to_string(y);
    }
};

class Shape
{
protected:
    Coordinate position;
    int sides;

public:
    Shape(int noOfSides, Coordinate coord) : position(coord), sides(noOfSides) {}

    Coordinate getCoordinates() const { return position; }
    void setCoordinates(const Coordinate &coord) { position = coord; }

    virtual double getArea() const = 0;
    virtual double getPerimeter() const = 0;
    virtual void translate(int dx, int dy) { position.translate(dx, dy); }
    virtual void scale(int factor, bool sign) = 0;
    virtual string display() const = 0;
};

class Rectangle : public Shape
{
private:
    int width, length;

public:
    Rectangle(Coordinate coord, int width, int length)
        : Shape(4, coord), width(width), length(length) {}

    double getArea() const override
    {
        return width * length;
    }

    virtual void translate(int dx, int dy)
    {
        position.translate(dx, dy);
    }

    double getPerimeter() const override
    {
        return 2 * (width + length);
    }

    void scale(int factor, bool sign) override
    {
        if (sign)
        {
            width *= factor;
            length *= factor;
        }
        else
        {
            width /= factor;
            length /= factor;
        }
    }

    string display() const override
    {
        return "Rectangle at " + position.display() + " with width " + to_string(width) +
               " and length " + to_string(length) + ", Area: " + to_string(getArea()) + ", Perimeter: " + to_string(getPerimeter());
    }
};

class Square : public Shape
{
private:
    int side;

public:
    Square(Coordinate coord, int side) : Shape(4, coord), side(side) {}

    double getArea() const override
    {
        return side * side;
    }

    double getPerimeter() const override
    {
        return 4 * side;
    }

    void scale(int factor, bool sign) override
    {
        if (sign)
        {
            side *= factor;
        }
        else
        {
            side /= factor;
        }
    }

    string display() const override
    {
        return "Square at " + position.display() + " with side" + to_string(side) + ", Area: " + to_string(getArea()) + ", Perimeter: " + to_string(getPerimeter());
    }
};

class Circle : public Shape
{
private:
    int radius;

public:
    Circle(Coordinate coord, int radius) : Shape(0, coord), radius(radius) {}

    double getArea() const override
    {
        return M_PI * radius * radius;
    }

    double getPerimeter() const override
    {
        return 2 * M_PI * radius;
    }

    void scale(int factor, bool sign) override
    {
        if (sign)
        {
            radius *= factor;
        }
        else
        {
            radius /= factor;
        }
    }

    string display() const override
    {
        return "Circle at " + position.display() + " with radius " + to_string(radius) +
               ", Area: " + to_string(getArea()) + ", Perimeter: " + to_string(getPerimeter());
    }
};

class Triangle : public Shape
{
private:
    Coordinate vertex1, vertex2, vertex3;

public:
    Triangle(Coordinate v1, Coordinate v2, Coordinate v3) : Shape(3, v1), vertex1(v1), vertex2(v2), vertex3(v3) {}

    double getArea() const override
    {
        double a = vertex1.distance(vertex2);
        double b = vertex2.distance(vertex3);
        double c = vertex3.distance(vertex1);
        double s = (a + b + c) / 2;
        return sqrt(s * (s - a) * (s - b) * (s - c));
    }

    double getPerimeter() const override
    {
        return vertex1.distance(vertex2) + vertex2.distance(vertex3) + vertex3.distance(vertex1);
    }

    void translate(int dx, int dy) override
    { // Correct the function name here
        vertex1.translate(dx, dy);
        vertex2.translate(dx, dy);
        vertex3.translate(dx, dy);
    }

    void scale(int factor, bool sign) override
    {
        vertex1 = scalePointFrom(vertex1, factor, sign); // Correct the function name here
        vertex2 = scalePointFrom(vertex2, factor, sign); // Correct the function name here
        vertex3 = scalePointFrom(vertex3, factor, sign); // Correct the function name here
    }

    string display() const override
    {
        return "Triangle with vertices " + vertex1.display() + ", " + vertex2.display() + ", " + vertex3.display() +
               ", Area: " + to_string(getArea()) + ", Perimeter: " + to_string(getPerimeter());
    }

private:
    Coordinate scalePointFrom(Coordinate point, int factor, bool sign)
    {                                            // Correct the function name here
        int dx = point.getX() - position.getX(); // Use the position as center
        int dy = point.getY() - position.getY();

        if (sign)
        {
            dx *= factor;
            dy *= factor;
        }
        else
        {
            dx /= factor; // Correct the divide by zero possibility
            dy /= factor; // Correct the divide by zero possibility
        }
        return Coordinate(position.getX() + dx, position.getY() + dy);
    }
};

class ShapeList
{
private:
    vector<Shape *> shapes;

public:
    ~ShapeList()
    {
        for (auto shape : shapes)
        {
            delete shape;
        }
    }

    void addShape(Shape *shape)
    {
        shapes.push_back(shape);
    }

    Shape *getShape(int index)
    {
        if (index < 0 || index >= shapes.size())
            throw out_of_range("Index out of range");
        return shapes[index];
    }

    void removeShape(int index)
    {
        if (index < 0 || index >= shapes.size())
            throw out_of_range("Index out of range");
        delete shapes[index];
        shapes.erase(shapes.begin() + index);
    }

    void display() const
    {
        for (const auto *shape : shapes)
        {
            cout << shape->display() << endl;
        }
    }

    void translateShapes(int dx, int dy)
    {
        for (Shape *shape : shapes)
        {
            shape->translate(dx, dy); // This should work if translate is correctly defined in Shape
        }
    }
    void scaleShapes(int factor, bool sign)
    {
        for (Shape *shape : shapes)
        {
            shape->scale(factor, sign);
        }
    }
};

class ShapeManagement
{
private:
    ShapeList shapeList;

public:
    void mainMenu()
    {
        int choice = 0;
        do
        {
            cout << "Shape Management System:" << endl;
            cout << "1: Add a shape" << endl;
            cout << "2: Remove a shape by position" << endl;
            cout << "3: Get information about a shape by position" << endl;
            cout << "4: Display area and perimeter of a shape by position" << endl;
            cout << "5: Display information of all the shapes" << endl;
            cout << "6: Translate all the shapes" << endl;
            cout << "7: Scale all the shapes" << endl;
            cout << "0: Quit program" << endl;
            cout << "Enter your choice: ";
            cin >> choice;
            switch (choice)
            {
            case 1:
                addShape();
                break;
            case 2:
                removeShape();
                break;
            case 3:
                displayShapeInfo();
                break;
            case 4:
                displayShapeAreaAndPerimeter();
                break;
            case 5:
                shapeList.display();
                break;
            case 6:
                translateAllShapes();
                break;
            case 7:
                scaleAllShapes();
                break;
            case 0:
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid option, please try again." << endl;
            }
        } while (choice != 0);
    }

    void addShape() {
        int shapeType;

        cout << "Select the type of shape to add:" << endl;
        cout << "1. Rectangle" << endl;
        cout << "2. Square" << endl;
        cout << "3. Circle" << endl;
        cout << "4. Triangle" << endl;
        cout << "Enter your choice: ";
        cin >> shapeType;


        int x, y;
        cout << "Enter the x and y coordinates of the shape's position: ";
        cin >> x >> y;
        Coordinate position(x, y);

        switch (shapeType) {
            case 1: {
                int width, length;
                cout << "Enter the width and length of the rectangle: ";
                cin >> width >> length;
                Shape* rectangle = new Rectangle(position, width, length);
                shapeList.addShape(rectangle);
                break;
            }
            case 2: {
                int side;
                cout << "Enter the side length of the square: ";
                cin >> side;
                Shape* square = new Square(position, side);
                shapeList.addShape(square);
                break;
            }

            case 3: {
                int radius;
                cout << "Enter the radius of the circle: ";
                cin >> radius;
                Shape* circle = new Circle(position, radius);
                shapeList.addShape(circle);
                break;
            }

            case 4: {
                cout << "Enter the coordinates for the three verticies of the trieangle:" << endl;
                int x1, y1, x2, y2, x3, y3;
                cout << "Vertex 1 - X: "; cin >> x1;
                cout << "Vertex 1 - Y: "; cin >> y1;
                cout << "Vertex 2 - X: "; cin >> x2;
                cout << "Vertex 2 - Y: "; cin >> y2;
                cout << "Vertex 3 - X: "; cin >> x3;
                cout << "Vertex 3 - Y: "; cin >> y3;
                Coordinate v1(x1, y1), v2(x2, y2), v3(x3, y3);
                Shape* triangle = new Triangle(v1, v2, v3);
                shapeList.addShape(triangle);
                break;
            }
            default:
                cout << "Invalid shape type." << endl;
        }
        cout << "Shape added." << endl;
    }

    void removeShape()
    {
        int index;
        cout << "Enter the position of the shape to remove: ";
        cin >> index;
        try
        {
            shapeList.removeShape(index);
            cout << "Shape at position " << index << " removed." << endl;
        }
        catch (const std::out_of_range &e)
        {
            cout << "Error: " << e.what() << endl;
        }
    }

    void displayShapeInfo()
    {
        int index;
        cout << "Enter the position of the shape to get information: ";
        cin >> index;
        try
        {
            Shape *shape = shapeList.getShape(index);
            cout << shape->display() << endl;
        }
        catch (const std::out_of_range &e)
        {
            cout << "Error: " << e.what() << endl;
        }
    }

    void displayShapeAreaAndPerimeter()
    {
        int index;
        cout << "Enter the position of the shape to display area and perimeter: ";
        cin >> index;
        try
        {
            Shape *shape = shapeList.getShape(index);
            cout << "Area: " << shape->getArea() << endl;
            cout << "Perimeter: " << shape->getPerimeter() << endl;
        }
        catch (const std::out_of_range &e)
        {
            cout << "Error: " << e.what() << endl;
        }
    }

    void translateAllShapes()
    {
        int dx, dy;
        cout << "Enter the x distance to translate: ";
        cin >> dx;
        cout << "Enter the y distance to translate: ";
        cin >> dy;
        shapeList.translateShapes(dx, dy);
        cout << "All shapes have been translated." << endl;
    }

    void scaleAllShapes()
    {
        int factor;
        bool sign;
        cout << "Enter the scaling factor: ";
        cin >> factor;
        cout << "Should the shapes be enlarged (1 for yes, 0 for no): ";
        cin >> sign;
        shapeList.scaleShapes(factor, sign);
        cout << "All shapes have been scaled." << endl;
    }
};

int main()
{
    ShapeManagement manager;
    manager.mainMenu();
    return 0;
}
