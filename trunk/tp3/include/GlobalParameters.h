#ifndef _GLOBALPARAMETERS_H_
#define _GLOBALPARAMETERS_H_

#define SPEED 4

#define BELT_STEP        100
#define BOTTLE_ROTATIONS 10
#define BOTTLE_STEP      100

const float beltControlPoints[][3] = {{-11.75, -1.25, 0}, 
                                      {-10.25, -3.75, 0}, 
                                      {-5.75,  -4.25, 0}, 
                                      {-3.75,  -2.25, 0},
                                      {-4.25,   2.25, 0},
                                      {-2.25,   4.25, 0},
                                      { 2.25,   3.75, 0},
                                      { 4.75,   4.25, 0},
                                      { 7.75,   7.75, 0},
                                      {NAN, NAN, NAN}};

const float bottleControlPoints[][3] = {{0,   0,  0.8},
                                       {1.3, 0,  0.8},
                                       {2.5, 0, -0.5},
                                       {3,   0,  0.3},
                                       {6,   0,  3},
                                       {.5,  0,  2},
                                       {4,   0,  11},
                                       {4.8, 0,  20},
                                       {1.5, 0,  18},
                                       {1,   0,  24},
                                       {1.5, 0,  24.5},
                                       {1.3, 0,  25},
                                       {1.3, 0,  26.5},
                                       {NAN, NAN, NAN}};

#endif /* _GLOBALPARAMETERS_H_ */
