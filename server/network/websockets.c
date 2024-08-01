#include <libwebsockets.h>
#include <cjson/cJSON.h>

#include "websockets.h"

#define MAX_MESSAGE_LEN 512

char username[MAX_MESSAGE_LEN];

static int callbackWebsocket(struct lws *wsi, enum lws_callback_reasons reason, void *user, void *in, size_t len) {
    switch (reason) {
        case LWS_CALLBACK_ESTABLISHED:
            lwsl_user("Client connected\n");
            break;
        case LWS_CALLBACK_RECEIVE:
            char received_msg[MAX_MESSAGE_LEN];
            if (len < MAX_MESSAGE_LEN) {
                memcpy(received_msg, in, len);
                received_msg[len] = '\0';
            } else {
                memcpy(received_msg, in, MAX_MESSAGE_LEN - 1);
                received_msg[MAX_MESSAGE_LEN - 1] = '\0';
            }

            lwsl_user("Received message: %s\n", (char *)received_msg);
            cJSON *receivedJSON = cJSON_Parse(received_msg);

            char reply[MAX_MESSAGE_LEN];
            const cJSON *json_cmd = NULL;
            const cJSON *json_name = NULL;

            json_cmd = cJSON_GetObjectItemCaseSensitive(receivedJSON, "cmd");

            if (strcmp(json_cmd->valuestring, "GETUSERNAME") == 0) {
                snprintf(reply, sizeof(reply), "{\"username\": \"%s\"}", (char *)username);
            } else if (strcmp(json_cmd->valuestring, "SETUSERNAME") == 0) {
                json_name = cJSON_GetObjectItemCaseSensitive(receivedJSON, "name");
                snprintf(reply, sizeof(reply), "{\"username\": \"%s\"}", (char *)(json_name->valuestring));
                memcpy(username, json_name, strlen(json_name->valuestring));
            }

            lws_write(wsi, (unsigned char *)reply, strlen(reply), LWS_WRITE_TEXT);
            break;
        case LWS_CALLBACK_CLOSED:
            lwsl_user("Client disconnected\n");
            break;
        default:
            break;
    }
    return 0;
}

static struct lws_protocols protocols[] = {
    { "chat-protocol", callbackWebsocket, 0, 1024 },
    { NULL, NULL, 0, 0 } // Terminator
};

void *start_websocket_server(void *arg) {
    struct lws_context_creation_info info;
    struct lws_context *context;

    memset(&info, 0, sizeof(info));
    info.port = 9001;
    info.protocols = protocols;

    context = lws_create_context(&info);
    if (context == NULL) {
        lwsl_err("lws init failed\n");
        return NULL;
    }

    lwsl_user("Starting WebSocket server on port 9001...\n");
    while (1) {
        lws_service(context, 1000);
    }

    lws_context_destroy(context);
    return NULL;
}
