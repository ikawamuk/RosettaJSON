#include <stddef.h>

static const char map[8][2] = {
    {'"', '"'},
    {'\\', '\\'},
    {'/', '/'},
    {'b', '\b'},
    {'f', '\f'},
    {'n', '\n'},
    {'t', '\t'},
    {'r', '\r'}
};

int parse_single_escape_char(char escaped_char, char *out_char)
{
    size_t i;
    size_t map_size;

    map_size = sizeof(map) / sizeof(map[0]);
    i = 0;
    while (i < map_size)
    {
        if (map[i][0] == escaped_char)
        {
            *out_char = map[i][1];
            return (0);
        }
        ++i;
    }
    return (-1);
}
