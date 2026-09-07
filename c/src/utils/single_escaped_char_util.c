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

int unescape_single_char(char escaped_char, char *out_char)
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

int escape_single_char(char unescaped_char, char *out_char)
{
    size_t i;
    size_t map_size;

    map_size = sizeof(map) / sizeof(map[0]);
    i = 0;
    while (i < map_size)
    {
        if (map[i][1] == unescaped_char)
        {
            *out_char = map[i][0];
            return (0);
        }
        ++i;
    }
    return (-1);
}

