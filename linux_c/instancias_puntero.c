#include <stdio.h>
#include <math.h>
#include <string.h>
#include <uchar.h>
#include <stdlib.h>

/**
 * Define Shape class
 */
typedef struct Shape Shape;
struct Shape {
    /**
     * Variables header...
     */
    double width, height;

    /**
     * Functions header...
     */
    double (*area)(Shape *shape);
};

/**
 * Functions
 */
double calc(Shape *shape) {
        return shape->width * shape->height;
}

/**
 * Constructor
 */
Shape _Shape() {
    Shape s;

    s.width = 1;
    s.height = 1;

    s.area = calc;

    return s;
}

/********************************************/

int main(void) {

    Shape *s1 = malloc(sizeof(Shape));
    *s1 = _Shape();

    s1->width = 5.35;
    s1->height = 12.5462;

    Shape *s2 = malloc(sizeof(Shape));
    *s2 = _Shape();

    //Shape s1 = _Shape();
    s2->width = 2;
    s2->height = 1;


    printf("Hello World\n\n");

    printf("User.width = %f\n", s1->width);
    printf("User.height = %f\n", s1->height);
    printf("User.area = %f\n\n", s1->area(s1));

    free(s1);

    printf("User.width = %f\n", s2->width);
    printf("User.height = %f\n", s2->height);
    printf("User.area = %f\n\n", s2->area(s2));

    printf("Made with \xe2\x99\xa5 \n");
    printf("User.width = %f\n", s1->width);
    printf("User.height = %f\n", s1->height);
    printf("User.area = %f\n\n", s1->area(s1));

    return 0;
};
