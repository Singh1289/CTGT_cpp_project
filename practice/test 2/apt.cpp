// The angle of elevation of a ladder leaning against a wall is 60° and the foot of the ladder is 4.6 m away from the wall. The length of the ladder is:

#include <stdio.h>
#include <math.h>

int main() {
    double angle_of_elevation = 60.0;
    double foot_of_ladder = 4.6;
    double length_of_ladder;

    length_of_ladder = foot_of_ladder * cos(angle_of_elevation * M_PI / 180.0);

    printf("The length of the ladder is %.2f meters.\n", length_of_ladder);

    return 0;
}