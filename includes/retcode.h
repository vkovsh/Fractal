#ifndef RETCODE_H
# define RETCODE_H

typedef enum    e_retcode
{
    RC_SUCSESS = 0,
    RC_ERR = 1,
    RC_ERR_BAD_FRACTAL_IMAGE_SIZE = 2,
    RC_ERR_BAD_MEMALLOC = 3,
    RC_ERR_TOTAL = 4,
}               t_retcode;

#endif