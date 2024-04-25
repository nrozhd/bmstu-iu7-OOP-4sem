#include "responsecodes.h"

void failure_message(response_code_t error)
{
    switch(error)
    {
    case FILE_NAME_FAILURE:
        QMessageBox::critical(NULL, "Ошибка при выполнении программы.", "Неверное имя файла.");
        break;
    case OPEN_FILE_FAILURE:
        QMessageBox::critical(NULL, "Ошибка при выполнении программы.", "Ошибка при открытии файла.");
        break;
    case EMPTY_FILE_FAILURE:
        QMessageBox::critical(NULL, "Ошибка при выполнении программы.", "Ошибка. Файл пуст.");
        break;
    case CREATE_FILE_FAILURE:
        QMessageBox::critical(NULL, "Ошибка при выполнении программы.", "Ошибка при создании файла.");
        break;
    case READ_FILE_FAILURE:
        QMessageBox::critical(NULL, "Ошибка при выполнении программы.", "Ошибка при чтении файла.");
        break;
    case WRITE_FILE_FAILURE:
        QMessageBox::critical(NULL, "Ошибка при выполнении программы.", "Ошибка при записи в файл.");
        break;
    case WRONG_COUNT_OF_POINTS_FAILURE:
        QMessageBox::critical(NULL, "Ошибка при выполнении программы.", "Ошибка. Указано некоррекнтое количество точек.");
        break;
    case NO_POINTS_FAILURE:
        QMessageBox::critical(NULL, "Ошибка при выполнении программы.", "Ошибка. Не указаны коориданты точек.");
        break;
    case WRONG_POINTS_FAILURE:
        QMessageBox::critical(NULL, "Ошибка при выполнении программы.", "Ошибка. Указаны некоррекнтые координаты точек.");
        break;
    case WRONG_COUNT_OF_LINKS_FAILURE:
        QMessageBox::critical(NULL, "Ошибка при выполнении программы.", "Ошибка. Указано некоррекнтое количество соединений между точками.");
        break;
    case NO_LINKS_FAILURE:
        QMessageBox::critical(NULL, "Ошибка при выполнении программы.", "Ошибка. Не указаны соединения между точками.");
        break;
    case WRONG_LINKS_FAILURE:
        QMessageBox::critical(NULL, "Ошибка при выполнении программы.", "Ошибка. Указаны некоррекнтые соединения между точками.");
        break;
    case ALLOCATE_MEMORY_FAILURE:
        QMessageBox::critical(NULL, "Ошибка при выполнении программы.", "Ошибка при выделении памяти.");
        break;
    case WRONG_SCENE_FAILURE:
        QMessageBox::critical(NULL, "Ошибка при выполнении программы.", "Ошибка при формировании сцены.");
        break;
    case WRONG_MOVE_COEFFICIENTS:
        QMessageBox::critical(NULL, "Ошибка при выполнении программы.", "Введены некорректные коэффициенты переноса.");
        break;
    case WRONG_SCALE_COEFFICIENTS:
        QMessageBox::critical(NULL, "Ошибка при выполнении программы.", "Введены некорректные коэффициенты масштабирования.");
        break;
    case WRONG_TURN_COEFFICIENTS:
        QMessageBox::critical(NULL, "Ошибка при выполнении программы.", "Введены некорректные коэффициенты поворота.");
        break;
    case UNDEFINED_ACTION:
        QMessageBox::critical(NULL, "Ошибка при выполнении программы.", "Ошибка. Неизвестная команда.");
        break;
    default:
        QMessageBox::critical(NULL, "Ошибка при выполнении программы.", "Неизвестная ошибка.");
    }
}
