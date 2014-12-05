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
#include <string.h>

#include "../../utils/http.h"
#include "../mfconn.h"
#include "../apicalls.h"        // IWYU pragma: keep

int mfconn_api_folder_create(mfconn * conn, const char *parent,
                             const char *name)
{
    const char     *api_call;
    int             retval;
    mfhttp         *http;

    if (conn == NULL)
        return -1;

    if (name == NULL)
        return -1;
    if (strlen(name) < 1)
        return -1;

    // key must either be 13 chars or NULL
    if (parent != NULL && strlen(parent) != 13) {
        return -1;
    }

    if (parent != NULL) {
        api_call =
            mfconn_create_signed_get(conn, 0, "folder/create.php",
                                     "?parent_key=%s&foldername=%s"
                                     "&response_format=json", parent, name);
    } else {
        api_call =
            mfconn_create_signed_get(conn, 0, "folder/create.php",
                                     "?foldername=%s&response_format=json",
                                     name);
    }

    http = http_create();
    retval = http_get_buf(http, api_call, mfapi_decode_common,
                          "folder/create");
    http_destroy(http);
    mfconn_update_secret_key(conn);

    free((void *)api_call);

    return retval;
}
