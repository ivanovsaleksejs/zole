#include <libwebsockets.h>

#include "websockets.h"

static int callbackWebsocket(struct lws *wsi, enum lws_callback_reasons reason, void *user, void *in, size_t len) {
    switch (reason) {
        case LWS_CALLBACK_ESTABLISHED:
            lwsl_user("Client connected\n");
            break;
        case LWS_CALLBACK_RECEIVE:
            lwsl_user("Received message: %s\n", (char *)in);
            lws_write(wsi, (unsigned char *)in, len, LWS_WRITE_TEXT);
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
