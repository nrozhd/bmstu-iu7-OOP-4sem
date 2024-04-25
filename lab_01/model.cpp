#include "model.h"

model_t model_initialize(void)
{
    model_t model;

    model.points.data = nullptr;
    model.points.count = 0;
    model.links.data = nullptr;
    model.links.count = 0;

    return model;
}

response_code_t model_load(model_t &model, str_t filename)
{
    if (filename == nullptr)
        return FILE_NAME_FAILURE;

    response_code_t rc = SUCCESS;

    FILE *file = nullptr;
    file = fopen(filename, "r");

    if (file == nullptr)
        rc = OPEN_FILE_FAILURE;
    else
    {
        model_t curr_model = model_initialize();
        rc = read_model_from_file(curr_model, file);
        fclose(file);
        if (rc == SUCCESS)
        {
            model_free(model);
            model = curr_model;
        }
    }

    return rc;
}

response_code_t read_model_from_file(model_t &model, FILE *file)
{
    if (file == nullptr)
        return OPEN_FILE_FAILURE;

    response_code_t rc = read_points_set_from_file(model.points, file);

    if (rc == SUCCESS)
        rc = read_links_set_from_file(model.links, file);
    else
        model_free(model);

    return rc;
}

response_code_t model_save(str_t filename, model_t model)
{
    if (filename == nullptr)
        return FILE_NAME_FAILURE;

    response_code_t rc = SUCCESS;

    FILE *file = nullptr;
    file = fopen(filename, "w");

    if (file == nullptr)
        rc = CREATE_FILE_FAILURE;
    else
    {
        rc = write_model_to_file(file, model);
        fclose(file);
    }

    return rc;
}

response_code_t write_model_to_file(FILE *file, model_t model)
{
    if (file == nullptr)
        return OPEN_FILE_FAILURE;

    response_code_t rc = write_points_set_to_file(file, model.points);

    if (rc == SUCCESS)
        rc = write_links_set_to_file(file, model.links);

    return rc;
}

response_code_t model_move(model_t &model, move_data_t move_data)
{
    return all_points_move(model.points, move_data);
}

response_code_t model_scale(model_t &model, scale_data_t scale_data)
{
    return all_points_scale(model.points, scale_data);
}

response_code_t model_turn(model_t &model, turn_data_t turn_data)
{
    return all_points_turn(model.points, turn_data);
}

void model_free(model_t &model)
{
    points_free(model.points);
    links_free(model.links);
}
