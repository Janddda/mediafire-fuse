/*
 * Copyright (C) 2013 Bryan Christ <bryan.christ@mediafire.com>
 *               2014 Johannes Schauer <j.schauer@email.de>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2, as published by
 * the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc., 51
 * Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

#include "command.h"
#include "mfshell.h"
#include "private.h"

int
mfshell_cmd_lpwd(mfshell_t *mfshell, int argc, char **argv)
{
    extern int  term_width;
    int         trim_size;

    if(mfshell == NULL) return -1;

    if (argc != 1) {
        fprintf(stderr, "Invalid number of argumens\n");
        return -1;
    }

    if(mfshell->local_working_dir == NULL)
    {
        mfshell->local_working_dir = (char*)calloc(PATH_MAX + 1,sizeof(char));
        getcwd(mfshell->local_working_dir,PATH_MAX);
    }

    trim_size = term_width - 1;

    printf("%-*.*s\n\r",
        trim_size,trim_size,
        mfshell->local_working_dir);

    return 0;
}

