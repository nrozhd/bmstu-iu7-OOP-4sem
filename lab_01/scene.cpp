#include "scene.h"

response_code_t scene_draw_model(model_t &model, scene_t scene)
{   
    scene_clear(scene);

    return scene_add_lines(scene, model.points, model.links);
}

response_code_t scene_add_lines(scene_t &scene, points_set_t points_set, links_set_t links_set)
{
    if ((scene.data == nullptr) || (scene.height <= 0) || (scene.width <= 0))
        return WRONG_SCENE_FAILURE;

    if ((points_set.count <= 0) || (points_set.data == nullptr))
        return NO_POINTS_FAILURE;
    if ((links_set.count <= 0) || (links_set.data == nullptr))
        return  NO_LINKS_FAILURE;

    response_code_t rc = SUCCESS;

    for (int i = 0; (i < links_set.count) && (rc == SUCCESS); i++)
        rc = scene_add_line(scene, points_set.data, links_set.data[i]);

    return rc;
}

response_code_t scene_add_line(scene_t scene, point_t *points_set, link_t link)
{
    if (points_set == nullptr)
        return NO_POINTS_FAILURE;
    if ((link.p1 < 0) || (link.p2 < 0))
        return WRONG_LINKS_FAILURE;

    scene_line_t line;

    response_code_t rc = scene_line_points_identify(line, scene, points_set[link.p1], points_set[link.p2]);

    if (rc == SUCCESS)
        rc = scene_draw_line(scene, line);

    return rc;
}

response_code_t scene_line_points_identify(scene_line_t &line, scene_t scene, point_t p1, point_t p2)
{
    scene_point_t sp1, sp2;

    response_code_t rc = scene_point_modification(sp1, scene, p1);

    if (rc == SUCCESS)
    {
        rc = scene_point_modification(sp2, scene, p2);
        if (rc == SUCCESS)
        {
            line.p1 = sp1;
            line.p2 = sp2;
        }
    }

    return rc;
}

response_code_t scene_point_modification(scene_point_t &scene_point, scene_t scene, point_t point)
{
    if ((scene.height <= 0) || (scene.width <= 0))
        return WRONG_SCENE_FAILURE;

    scene_point.x = point.x + scene.width / 2;
    scene_point.y = point.y + scene.height / 2;

    return SUCCESS;
}

response_code_t scene_draw_line(scene_t &scene, scene_line_t line)
{
    if (scene.data == nullptr)
        return WRONG_SCENE_FAILURE;

    scene.data->addLine(line.p1.x, line.p1.y, line.p2.x, line.p2.y);

    return SUCCESS;
}

void scene_clear(scene_t &scene)
{
    if (scene.data != nullptr)
        scene.data->clear();
}
