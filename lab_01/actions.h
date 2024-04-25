#ifndef ACTIONS_H
#define ACTIONS_H

typedef struct{
    double dx;
    double dy;
    double dz;
} move_data_t;

typedef struct{
    double kx;
    double ky;
    double kz;
} scale_data_t;

typedef struct{
    double ax;
    double ay;
    double az;
} turn_data_t;

typedef struct{
    double cos_a;
    double sin_a;
} turn_trig_coord_data_t;

typedef struct{
    turn_trig_coord_data_t ax;
    turn_trig_coord_data_t ay;
    turn_trig_coord_data_t az;
} turn_trig_data_t;

#endif // ACTIONS_H
