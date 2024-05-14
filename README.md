# Shape Management System

This project is a console-based Shape Management System implemented in C++. It allows users to manage a list of geometric shapes, including rectangles, squares, circles, and triangles.

## Features

The Shape Management System provides the following features:

- Add a shape to the list
- Remove a shape from the list by its position
- Get information about a shape by its position
- Display the area and perimeter of a shape by its position
- Display information of all the shapes in the list
- Translate all the shapes in the list
- Scale all the shapes in the list

## Usage

To run the Shape Management System, compile and run the `main.cpp` file. The main menu of the system will be displayed, where you can choose the operation you want to perform.

## Classes

The system is implemented using several classes:

- `Coordinate`: Represents a 2D point with x and y coordinates.
- `Shape`: An abstract base class for all shapes.
- `Rectangle`, `Square`, `Circle`, `Triangle`: Derived classes from `Shape`, each representing a specific type of shape.
- `ShapeList`: Manages a list of shapes.
- `ShapeManagement`: Provides the main menu and handles user input to perform operations on the `ShapeList`.

## Contributing

Contributions are welcome. Please open an issue to discuss your idea or submit a Pull Request.

## License

This project is open source and available under the [MIT License](LICENSE).