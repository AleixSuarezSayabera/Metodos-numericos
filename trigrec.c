#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>
#define PI 3.1415926535897932384

void trigrec0(int k, double x, double* c, double* s) {
    c[0] = 1;
    s[0] = 0;
    for (int j = 1; j <= k; j++) {
        s[j] = sin(x * j);
        c[j] = cos(x * j);
    }
}

void trigrec1(int k, double x, double* c, double* s) {
    c[0] = 1;
    s[0] = 0;
    c[1] = cos(x);
    s[1] = sin(x);
    for (int j = 1; j <= k - 1; j++) {
        c[j + 1] = 2 * c[1] * c[j] - c[j - 1];
        s[j + 1] = 2 * c[1] * s[j] - s[j - 1];
    }
}

void trigrec2(int k, double x, double* c, double* s) {
    c[0] = 1;
    s[0] = 0;
    c[1] = cos(x);
    s[1] = sin(x);
    for (int j = 1; j <= k - 1; j++) {
        c[j + 1] = c[1] * c[j] - s[1] * s[j];
        s[j + 1] = s[1] * c[j] + c[1] * s[j];
    }
}

void trigrec3(int k, double x, double* c, double* s) {
    double dc;
    double ds;
    dc = sin(x/2);
    dc = -2*dc*dc;
    ds = (((int)floor(x / PI))%2==0 ? 1:-1)*sqrt(-dc * (2 + dc));
    double t = 2 * dc;
    c[0] = 1;
    s[0] = 0;
    for (int j = 1; j <= k; j++) {
        c[j] = c[j - 1] + dc;
        dc = t * c[j] + dc;
        s[j] = s[j - 1] + ds;
        ds = t * s[j] + ds;
    }
}