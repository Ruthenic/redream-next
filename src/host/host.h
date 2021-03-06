#ifndef HOST_H
#define HOST_H

#include "keycode.h"

typedef void (*video_resized_cb)(void *);
typedef void (*video_context_reset_cb)(void *);
typedef void (*video_context_destroyed_cb)(void *);
typedef void (*input_keydown_cb)(void *, int, enum keycode, int16_t);
typedef void (*input_mousemove_cb)(void *, int, int, int);

struct host {
  /* supplied by user to hook into host events */
  void *userdata;
  video_resized_cb video_resized;
  video_context_reset_cb video_context_reset;
  video_context_destroyed_cb video_context_destroyed;
  input_keydown_cb input_keydown;
  input_mousemove_cb input_mousemove;
};

/* audio */
void audio_push(struct host *host, const int16_t *data, int frames);

/* video */
int video_width(struct host *host);
int video_height(struct host *host);

int video_supports_multiple_threads(struct host *host);

struct render_backend *video_create_renderer(struct host *host);
void video_destroy_renderer(struct host *host, struct render_backend *r);

void video_bind_context(struct host *host, struct render_backend *r);
void video_unbind_context(struct host *host);

/* input */
void input_poll(struct host *host);
int16_t input_get(struct host *host, int port, int button);

#endif
