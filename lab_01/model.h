#ifndef MODEL_H
#define MODEL_H

#include "responsecodes.h"
#include "point.h"
#include "link.h"

typedef char str_t[100];

typedef struct{
    points_set_t points;
    links_set_t links;
} model_t;

model_t model_initialize(void);

response_code_t model_load(model_t &model, str_t filename);

response_code_t read_model_from_file(model_t &model, FILE *file);

response_code_t model_save(str_t filename, model_t model);

response_code_t write_model_to_file(FILE *file, model_t model);

response_code_t model_move(model_t &model, move_data_t move_data);

response_code_t model_scale(model_t &model, scale_data_t scale_data);

response_code_t model_turn(model_t &model, turn_data_t turn_data);

void model_free(model_t &model);

#endif // MODEL_H
