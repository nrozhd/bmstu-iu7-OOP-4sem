#ifndef POINT_H
#define POINT_H

#include "responsecodes.h"
#include "actions.h"

typedef struct{
    double x;
    double y;
    double z;
} point_t;

typedef struct{
    point_t *data;
    int count;
} points_set_t;

response_code_t read_points_set_from_file(points_set_t &points_set, FILE *file);

response_code_t read_points_count_from_file(points_set_t &points_set, FILE *file);

response_code_t allocate_points_set(points_set_t &points_set);

response_code_t read_points_data_from_file(points_set_t &points_set, FILE *file);

void points_free(points_set_t &points_set);

response_code_t read_point_from_file(point_t &point, FILE *file);

response_code_t write_points_set_to_file(FILE *file, points_set_t points_set);

response_code_t write_points_count_to_file(FILE *file, points_set_t points_set);

response_code_t write_points_data_to_file(FILE *file, points_set_t points_set);

response_code_t write_point_to_file(FILE *file, point_t point);

response_code_t all_points_move(points_set_t &points_set, move_data_t move_data);

response_code_t all_points_move(points_set_t &points_set, move_data_t move_data);

void point_move(point_t &point, move_data_t move_data);

response_code_t all_points_scale(points_set_t &points_set, scale_data_t scale_data);

void point_scale(point_t &point, scale_data_t scale_data);

response_code_t all_points_turn(points_set_t &points_set, turn_data_t turn_data);

void turn_data_to_trig(turn_trig_data_t &turn_trig_data, turn_data_t turn_data);

void turn_coord_data_to_trig(turn_trig_coord_data_t &turn_trig_coord_data, double a);

double get_radians_from_degrees(double degrees);

void point_turn(point_t &point, turn_trig_data_t turn_trig_data);

void point_x_turn(point_t &point, turn_trig_coord_data_t ax);

void point_y_turn(point_t &point, turn_trig_coord_data_t ay);

void point_z_turn(point_t &point, turn_trig_coord_data_t az);

#endif // POINT_H
