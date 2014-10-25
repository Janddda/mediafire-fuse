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
#include <string.h>

#include "../../mfapi/apicalls.h"
#include "../mfshell.h"
#include "../../mfapi/mfconn.h"
#include "../commands.h"        // IWYU pragma: keep

int mfshell_cmd_rmdir(mfshell * mfshell, int argc, char *const argv[])
{
    int             retval;
    const char     *folderkey;

    if (mfshell == NULL)
        return -1;

    if (mfshell->conn == NULL) {
        fprintf(stderr, "conn is NULL\n");
        return -1;
    }

    if (argc != 2) {
        fprintf(stderr, "Invalid number of arguments\n");
        return -1;
    }

    folderkey = argv[1];
    if (folderkey == NULL)
        return -1;

    // check the lenght of the key
    if (strlen(folderkey) != 13) {
        return -1;
    }

    retval = mfconn_api_folder_delete(mfshell->conn, folderkey);
    mfconn_update_secret_key(mfshell->conn);

    return retval;
}
