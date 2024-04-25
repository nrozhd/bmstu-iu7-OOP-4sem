#include "link.h"

response_code_t read_links_set_from_file(links_set_t &links_set, FILE *file)
{
    if (file == nullptr)
        return OPEN_FILE_FAILURE;

    response_code_t rc  = read_links_count_from_file(links_set, file);
    if (rc == SUCCESS)
    {
        rc = allocate_links_set(links_set);
        if (rc == SUCCESS)
        {
            rc = read_links_data_from_file(links_set, file);
            if (rc != SUCCESS)
                links_free(links_set);
        }
    }

    return rc;
}

response_code_t read_links_count_from_file(links_set_t &links_set, FILE *file)
{
    if (file == nullptr)
        return OPEN_FILE_FAILURE;

    response_code_t rc = SUCCESS;

    if (fscanf(file, "%d", &links_set.count) != 1)
        rc = READ_FILE_FAILURE;
    else if (links_set.count <= 0)
        rc = WRONG_COUNT_OF_LINKS_FAILURE;

    return rc;
}

response_code_t allocate_links_set(links_set_t &links_set)
{
    if (links_set.count <= 0)
        return WRONG_COUNT_OF_LINKS_FAILURE;

    response_code_t rc = SUCCESS;

    link_t *data = (link_t*) malloc(links_set.count * sizeof(link_t));
    if (data == nullptr)
        rc = ALLOCATE_MEMORY_FAILURE;
    else
        links_set.data = data;

    return rc;
}

response_code_t read_links_data_from_file(links_set_t &links_set, FILE *file)
{
    if (file == nullptr)
        return OPEN_FILE_FAILURE;

    if (links_set.count <= 0)
        return WRONG_COUNT_OF_LINKS_FAILURE;
    if (links_set.data == nullptr)
        return ALLOCATE_MEMORY_FAILURE;

    response_code_t rc = SUCCESS;

    for (int i = 0; (i < links_set.count) && (rc == SUCCESS); i++)
        rc = read_link_from_file(links_set.data[i], file);

    return rc;
}

void links_free(links_set_t &links_set)
{
    links_set.count = 0;

    if (links_set.data != nullptr)
        free(links_set.data);
}

response_code_t read_link_from_file(link_t &link, FILE *file)
{
    if (file == nullptr)
        return OPEN_FILE_FAILURE;

    response_code_t rc = SUCCESS;

    if (fscanf(file, "%d %d", &link.p1, &link.p2) != 2)
        rc = READ_FILE_FAILURE;

    return rc;
}

response_code_t write_links_set_to_file(FILE *file, links_set_t links_set)
{
    if (file == nullptr)
        return OPEN_FILE_FAILURE;

    response_code_t rc = SUCCESS;

    rc = write_links_count_to_file(file, links_set);

    if (rc == SUCCESS)
        rc = write_links_data_to_file(file, links_set);

    return rc;
}

response_code_t write_links_count_to_file(FILE *file, links_set_t links_set)
{
    if (file == nullptr)
        return OPEN_FILE_FAILURE;

    if (links_set.count <= 0)
        return WRONG_COUNT_OF_LINKS_FAILURE;

    response_code_t rc = SUCCESS;

    if (fprintf(file, "%d\n", links_set.count) < 0)
        rc = READ_FILE_FAILURE;

    return rc;
}

response_code_t write_links_data_to_file(FILE *file, links_set_t links_set)
{
    if (file == nullptr)
        return OPEN_FILE_FAILURE;

    if (links_set.count <= 0)
        return WRONG_COUNT_OF_LINKS_FAILURE;
    if (links_set.data == nullptr)
        return ALLOCATE_MEMORY_FAILURE;

    response_code_t rc = SUCCESS;

    for (int i = 0; (i < links_set.count) && (rc == SUCCESS); i++)
        rc = write_link_to_file(file, links_set.data[i]);

    return rc;
}

response_code_t write_link_to_file(FILE *file, link_t link)
{
    if (file == nullptr)
        return OPEN_FILE_FAILURE;

    response_code_t rc = SUCCESS;

    if (fprintf(file, "%d %d\n", link.p1, link.p2) < 0)
        rc = READ_FILE_FAILURE;

    return rc;
}
