#include "point.h"

#include <cmath>

response_code_t read_points_set_from_file(points_set_t &points_set, FILE *file)
{
    if (file == nullptr)
        return OPEN_FILE_FAILURE;

    response_code_t rc = read_points_count_from_file(points_set, file);

    if (rc == SUCCESS)
    {
        rc = allocate_points_set(points_set);
        if (rc == SUCCESS)
        {
            rc = read_points_data_from_file(points_set, file);
            if (rc != SUCCESS)
                points_free(points_set);
        }
    }

    return rc;
}

response_code_t read_points_count_from_file(points_set_t &points_set, FILE *file)
{
    if (file == nullptr)
        return OPEN_FILE_FAILURE;

    response_code_t rc = SUCCESS;

    if (fscanf(file, "%d", &points_set.count) != 1)
        rc = READ_FILE_FAILURE;
    else if (points_set.count <= 0)
        rc = WRONG_COUNT_OF_POINTS_FAILURE;

    return rc;
}

response_code_t allocate_points_set(points_set_t &points_set)
{
    if (points_set.count <= 0)
        return WRONG_COUNT_OF_POINTS_FAILURE;

    response_code_t rc = SUCCESS;

    point_t *data = (point_t*) malloc(points_set.count * sizeof(point_t));

    if (data == nullptr)
        rc = ALLOCATE_MEMORY_FAILURE;
    else
        points_set.data = data;

    return rc;
}

response_code_t read_points_data_from_file(points_set_t &points_set, FILE *file)
{
    if (file == nullptr)
        return OPEN_FILE_FAILURE;

    if (points_set.count <= 0)
        return WRONG_COUNT_OF_POINTS_FAILURE;
    if (points_set.data == nullptr)
        return ALLOCATE_MEMORY_FAILURE;

    response_code_t rc = SUCCESS;

    for (int i = 0; (i < points_set.count) && (rc == SUCCESS); i++)
        rc = read_point_from_file(points_set.data[i], file);

    return rc;
}

void points_free(points_set_t &points_set)
{
    points_set.count = 0;

    if (points_set.data != nullptr)
        free(points_set.data);
}

response_code_t read_point_from_file(point_t &point, FILE *file)
{
    if (file == nullptr)
        return OPEN_FILE_FAILURE;

    response_code_t rc = SUCCESS;

    if (fscanf(file, "%lf %lf %lf", &point.x, &point.y, &point.z) != 3)
        rc = READ_FILE_FAILURE;

    return rc;
}

response_code_t write_points_set_to_file(FILE *file, points_set_t points_set)
{
    if (file == nullptr)
        return OPEN_FILE_FAILURE;

    response_code_t rc = write_points_count_to_file(file, points_set);

    if (rc == SUCCESS)
        rc = write_points_data_to_file(file, points_set);

    return rc;
}

response_code_t write_points_count_to_file(FILE *file, points_set_t points_set)
{
    if (file == nullptr)
        return OPEN_FILE_FAILURE;

    if (points_set.count <= 0)
        return WRONG_COUNT_OF_POINTS_FAILURE;

    response_code_t rc = SUCCESS;

    if (fprintf(file, "%d\n", points_set.count) < 0)
        rc = WRITE_FILE_FAILURE;

    return rc;
}

response_code_t write_points_data_to_file(FILE *file, points_set_t points_set)
{
    if (file == nullptr)
        return OPEN_FILE_FAILURE;

    if (points_set.count <= 0)
        return WRONG_COUNT_OF_POINTS_FAILURE;
    if (points_set.data == nullptr)
        return NO_POINTS_FAILURE;

    response_code_t rc = SUCCESS;

    for (int i = 0; (i < points_set.count) && (rc == SUCCESS); i++)
        rc = write_point_to_file(file, points_set.data[i]);

    return rc;
}

response_code_t write_point_to_file(FILE *file, point_t point)
{
    if (file == nullptr)
        return OPEN_FILE_FAILURE;

    response_code_t rc = SUCCESS;

    if (fprintf(file, "%lf %lf %lf\n", point.x, point.y, point.z) < 3)
        rc = WRITE_FILE_FAILURE;

    return rc;
}

response_code_t all_points_move(points_set_t &points_set, move_data_t move_data)
{
    if (points_set.data == nullptr)
        return NO_POINTS_FAILURE;

    for (int i = 0; i < points_set.count; i++)
        point_move(points_set.data[i], move_data);

    return SUCCESS;
}

void point_move(point_t &point, move_data_t move_data)
{
    point.x += move_data.dx;
    point.y += move_data.dy;
    point.z += move_data.dz;
}

response_code_t all_points_scale(points_set_t &points_set, scale_data_t scale_data)
{
    if (points_set.data == nullptr)
        return NO_POINTS_FAILURE;

    for (int i = 0; i < points_set.count; i++)
        point_scale(points_set.data[i], scale_data);

    return SUCCESS;
}

void point_scale(point_t &point, scale_data_t scale_data)
{
    point.x *= scale_data.kx;
    point.y *= scale_data.ky;
    point.z *= scale_data.kz;
}

response_code_t all_points_turn(points_set_t &points_set, turn_data_t turn_data)
{
    if (points_set.data == nullptr)
        return NO_POINTS_FAILURE;

    turn_trig_data_t turn_trig_data;
    turn_data_to_trig(turn_trig_data, turn_data);

    for (int i = 0; i < points_set.count; i++)
        point_turn(points_set.data[i], turn_trig_data);

    return SUCCESS;
}

void turn_data_to_trig(turn_trig_data_t &turn_trig_data, turn_data_t turn_data)
{
    turn_coord_data_to_trig(turn_trig_data.ax, turn_data.ax);
    turn_coord_data_to_trig(turn_trig_data.ay, turn_data.ay);
    turn_coord_data_to_trig(turn_trig_data.az, turn_data.az);
}

void turn_coord_data_to_trig(turn_trig_coord_data_t &turn_trig_coord_data, double a)
{
    turn_trig_coord_data.cos_a = cos(get_radians_from_degrees(a));
    turn_trig_coord_data.sin_a = sin(get_radians_from_degrees(a));
}

double get_radians_from_degrees(double degrees)
{
    return M_PI * degrees / 180;
}

void point_turn(point_t &point, turn_trig_data_t turn_trig_data)
{

    point_x_turn(point, turn_trig_data.ax);
    point_y_turn(point, turn_trig_data.ay);
    point_z_turn(point, turn_trig_data.az);

}

void point_x_turn(point_t &point, turn_trig_coord_data_t ax)
{
    double y = point.y;
    point.y = point.y * ax.cos_a + point.z * ax.sin_a;
    point.z = -y * ax.sin_a + point.z * ax.cos_a;
}

void point_y_turn(point_t &point, turn_trig_coord_data_t ay)
{
    double x = point.x;
    point.x = point.x * ay.cos_a + point.z * ay.sin_a;
    point.z = -x * ay.sin_a + point.z * ay.cos_a;
}

void point_z_turn(point_t &point, turn_trig_coord_data_t az)
{
    double x = point.x;
    point.x = point.x * az.cos_a + point.y * az.sin_a;
    point.y = -x * az.sin_a + point.y * az.cos_a;
}


