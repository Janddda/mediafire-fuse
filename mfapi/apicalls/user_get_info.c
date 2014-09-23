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

#include <jansson.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../utils/http.h"
#include "../../utils/json.h"
#include "../mfconn.h"
#include "../apicalls.h"        // IWYU pragma: keep

static int      _decode_user_get_info(mfhttp * conn, void *data);

int mfconn_api_user_get_info(mfconn * conn)
{
    const char     *api_call;
    int             retval;
    mfhttp         *http;

    // char        *rx_buffer;

    if (conn == NULL)
        return -1;

    api_call = mfconn_create_signed_get(conn, 0, "user/get_info.php",
                                        "&response_format=json");

    http = http_create();
    retval = http_get_buf(http, api_call, _decode_user_get_info, NULL);
    http_destroy(http);

    free((void *)api_call);

    return retval;
}

static int _decode_user_get_info(mfhttp * conn, void *data)
{
    json_error_t    error;
    json_t         *root;
    json_t         *node;
    json_t         *email;
    json_t         *first_name;
    json_t         *last_name;

    if (data != NULL)
        return -1;

    root = http_parse_buf_json(conn, 0, &error);

    node = json_object_by_path(root, "response/user_info");

    email = json_object_get(node, "email");
    if (email != NULL)
        printf("Email: %s\n\r", json_string_value(email));

    first_name = json_object_get(node, "first_name");
    if (first_name != NULL)
        printf("Name: %s ", json_string_value(first_name));

    last_name = json_object_get(node, "last_name");
    if (node != NULL)
        printf("%s", json_string_value(last_name));

    printf("\n\r");

    if (root != NULL)
        json_decref(root);

    return 0;
}

// sample user callback
/*
static void
_mycallback(char *data,size_t sz,cmffile *cfile)
{
    double  bytes_read;
    double  bytes_total;

    bytes_read = cfile_get_rx_count(cfile);
    bytes_total = cfile_get_rx_length(cfile);

    printf("bytes read: %.0f\n\r",bytes_read);

    if(bytes_read == bytes_total)
    {
        printf("transfer complete!\n\r");
    }

    return;
}
*/
