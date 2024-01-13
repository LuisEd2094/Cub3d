#include <stdio.h>
#include <math.h>

// Structure to represent a 2D vector
typedef struct {
    double x;
    double y;
} Vector2D;

// Function to perform 2D rotation
Vector2D rotate2D(Vector2D v, double angle) {
    Vector2D result;
    
    // Convert angle to radians
    double theta = angle * M_PI / 180.0;
    
    // Rotation matrix
    double cosTheta = cos(theta);
    double sinTheta = sin(theta);
    
    // Apply rotation matrix
    result.x = v.x * cosTheta - v.y * sinTheta;
    result.y = v.x * sinTheta + v.y * cosTheta;
    
    return result;
}

int main() {
    // Example usage
    Vector2D originalVector = {1.0, 0.0};  // [1, 0]
    double rotationAngle = 90.0;  // 45 degrees
    
    // Perform rotation
    Vector2D rotatedVector = rotate2D(originalVector, rotationAngle);
    
    // Display the result
    printf("Rotated Vector:  [%f, %f]\n", rotatedVector.x, rotatedVector.y);
    rotatedVector = rotate2D(rotatedVector, rotationAngle);
    
    // Display the result
    printf("Rotated Vector:  [%f, %f]\n", rotatedVector.x, rotatedVector.y);

    rotatedVector = rotate2D(rotatedVector, rotationAngle);
    
    // Display the result
    printf("Rotated Vector:  [%f, %f]\n", rotatedVector.x, rotatedVector.y);

    rotatedVector = rotate2D(rotatedVector, rotationAngle);
    
    // Display the result
    printf("Rotated Vector:  [%f, %f]\n", rotatedVector.x, rotatedVector.y);
    
    return 0;
}