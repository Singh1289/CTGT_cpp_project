// The angle of elevation of a ladder leaning against a wall is 60° and the foot of the ladder is 4.6 m away from the wall. The length of the ladder is:


#include <stdio.h>

int main() {
    double angle_of_elevation = 60.0;
    double foot_distance_from_wall = 4.6;
    double ladder_length;

    // Using the sine function to find the length of the ladder
    ladder_length = foot_distance_from_wall / sin(angle_of_elevation * M_PI / 180.0);

    printf("The length of the ladder is %.2f meters.\n", ladder_length);

    return 0;
}