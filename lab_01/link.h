#ifndef LINK_H
#define LINK_H

#include "responsecodes.h"

typedef struct{
    int p1;
    int p2;
} link_t;

typedef struct{
    link_t *data;
    int count;
} links_set_t;

response_code_t read_links_set_from_file(links_set_t &links_set, FILE *file);

response_code_t read_links_count_from_file(links_set_t &links_set, FILE *file);

response_code_t allocate_links_set(links_set_t &links_set);

response_code_t read_links_data_from_file(links_set_t &links_set, FILE *file);

void links_free(links_set_t &links_set);

response_code_t read_link_from_file(link_t &link, FILE *file);

response_code_t write_links_set_to_file(FILE *file, links_set_t links_set);

response_code_t write_links_count_to_file(FILE *file, links_set_t links_set);

response_code_t write_links_data_to_file(FILE *file, links_set_t links_set);

response_code_t write_link_to_file(FILE *file, link_t link);

#endif // LINK_H
