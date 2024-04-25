#ifndef SCENE_H
#define SCENE_H

#include "QGraphicsScene"
#include "responsecodes.h"
#include "point.h"
#include "link.h"
#include "model.h"

typedef struct{
    QGraphicsScene *data;
    double height;
    double width;
} scene_t;

typedef struct{
    double x;
    double y;
} scene_point_t;

typedef struct{
    scene_point_t p1;
    scene_point_t p2;
} scene_line_t;

response_code_t scene_draw_model(model_t &model, scene_t scene);

response_code_t scene_add_lines(scene_t &scene, points_set_t points_set, links_set_t links_set);

response_code_t scene_add_line(scene_t scene, point_t *points_set, link_t link);

response_code_t scene_line_points_identify(scene_line_t &line, scene_t scene, point_t p1, point_t p2);

response_code_t scene_point_modification(scene_point_t &scene_point, scene_t scene, point_t point);

response_code_t scene_draw_line(scene_t &scene, scene_line_t line);

void scene_clear(scene_t &scene);

#endif // SCENE_H
