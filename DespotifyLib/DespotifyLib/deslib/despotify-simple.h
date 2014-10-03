#ifndef LIBDESPOTIFY_SIMPLE_H
#define LIBDESPOTIFY_SIMPLE_H

#include "despotify.h"
#include "session.h"

bool despotify_play(SESSION *session, playlist *playlist, int initial_song);

bool despotify_skip_song(SESSION *session);
bool despotify_previous_song(SESSION *session); 

bool despotify_queue_song(SESSION *session, track *song);
bool despotify_dequeue_song(SESSION *session, track*song);

bool despotify_set_shuffle(SESSION *session, int new_state);
bool despotify_get_shuffle(SESSION *session);

bool despotify_set_repeat(SESSION *session, int new_state);
bool despotify_get_repeat(SESSION *session);

bool despotify_set_volume(SESSION *session, int new_volume);
bool despotify_get_volume(SESSION *session);

#endif
