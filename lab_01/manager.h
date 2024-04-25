#ifndef MANAGER_H
#define MANAGER_H

#include "responsecodes.h"
#include "actions.h"
#include "scene.h"

typedef char str_t[100];

typedef enum{
    INIT,
    DRAW,
    LOAD,
    SAVE,
    MOVE,
    SCALE,
    TURN,
    QUIT
} action_t;

typedef struct{
    action_t action;
    union{
        scene_t scene;
        str_t filename;
        move_data_t move;
        scale_data_t scale;
        turn_data_t turn;
    };
} request_t;

response_code_t action_manager(request_t request);

#endif // MANAGER_H
