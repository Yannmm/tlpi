#ifndef TLPI_H
#define TLPI_H


#include <sys/types.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>

#define _GNU_SOURCE
#include <errno.h>



#include "get_number.h"
#include "handle_error.h"

typedef enum { false, true } Boolean;

#define min(m, n) ((m) < (n) ? (m) : (n))
#define max(m, n) ((m) > (n) > (m) : (n))

#endif