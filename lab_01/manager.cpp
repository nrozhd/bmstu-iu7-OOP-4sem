#include "manager.h"
#include "scene.h"

response_code_t action_manager(request_t request)
{
    static model_t model = model_initialize();

    response_code_t rc = SUCCESS;

    switch(request.action)
    {
    case INIT:
        break;
    case DRAW:
        rc = scene_draw_model(model, request.scene);
        break;
    case LOAD:
        rc = model_load(model, request.filename);
        break;
    case SAVE:
        rc = model_save(request.filename, model);
        break;
    case MOVE:
        rc = model_move(model, request.move);
        break;
    case SCALE:
        rc = model_scale(model, request.scale);
        break;
    case TURN:
        rc = model_turn(model, request.turn);
        break;
    case QUIT:
        model_free(model);
        break;
    default:
        rc = UNDEFINED_ACTION;
    }

    return rc;
}
