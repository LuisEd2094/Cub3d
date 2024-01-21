#include <stdio.h>
#include <math.h>

#define MAP_SIZE_X 10
#define MAP_SIZE_Y 10

int map[MAP_SIZE_X][MAP_SIZE_Y] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
    {0, 1, 1, 1, 1, 1, 1, 0, 1, 0},
    {0, 1, 0, 0, 0, 0, 0, 0, 1, 0},
    {0, 1, 0, 1, 1, 1, 1, 0, 1, 0},
    {0, 1, 0, 1, 0, 0, 0, 0, 1, 0},
    {0, 1, 0, 1, 1, 1, 1, 0, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 0}
};

typedef struct {
    int x;
    int y;
} Point;

typedef struct {
    Point start;
    Point direction;
} Ray;

typedef struct {
    Point point;
    float distance;
} HitInfo;

// Function to check if a given point is within the map bounds
int isInsideMap(int x, int y) {
    return x >= 0 && x < MAP_SIZE_X && y >= 0 && y < MAP_SIZE_Y;
}

// Function to perform ray casting
HitInfo castRay(Ray ray) {
    Point currentPoint = ray.start;
    
    while (isInsideMap(currentPoint.x, currentPoint.y) &&
           map[currentPoint.x][currentPoint.y] != 1) {
        currentPoint.x += ray.direction.x;
        currentPoint.y += ray.direction.y;
    }

    HitInfo hitInfo;
    hitInfo.point = currentPoint;
    hitInfo.distance = sqrt(pow(currentPoint.x - ray.start.x, 2) + pow(currentPoint.y - ray.start.y, 2));

    return hitInfo;
}

// Function to draw the line from the player to the wall
void drawLine(Point start, Point end) {
    // For simplicity, let's assume the player is represented by 'P' and the wall by 'W'
    char screen[MAP_SIZE_X][MAP_SIZE_Y];

    // Initialize screen with empty spaces
    for (int i = 0; i < MAP_SIZE_X; i++) {
        for (int j = 0; j < MAP_SIZE_Y; j++) {
            screen[i][j] = ' ';
        }
    }

    // Mark the player and wall positions
    screen[start.x][start.y] = 'P';
    screen[end.x][end.y] = 'W';

    // Draw the screen
    for (int i = 0; i < MAP_SIZE_X; i++) {
        for (int j = 0; j < MAP_SIZE_Y; j++) {
            printf("%c ", screen[i][j]);
        }
        printf("\n");
    }
}

int main() {
    // Player position
    Point player = {6, 4};

    // Ray direction (assuming a unit vector for simplicity)
    Point direction = {1, 1};

    // Create a ray from the player position and direction
    Ray ray = {player, direction};

    // Cast the ray and get the hit information
    HitInfo hitInfo = castRay(ray);

    // Print the hit information
    printf("Hit Point: (%d, %d)\n", hitInfo.point.x, hitInfo.point.y);
    printf("Distance: %.2f\n", hitInfo.distance);

    // Draw the line from the player to the wall
    drawLine(player, hitInfo.point);

    return 0;
}