/**
 * @file  music.c
 * @author Profesores EDAT
 * @date February 2026
 * @version 1.0
 * @brief Library to manage ADT Music
 *
 * @details 
 * 
 * @see
 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "music.h"
#include "types.h"


/* START [STR_LENGTH] */
#define STR_LENGTH 64
/* END [STR_LENGTH] */

/* Music declaration goes here */
struct _Music{
  long id;
  char title [STR_LENGTH];
  char artist [STR_LENGTH];
  unsigned short duration;
  State state;
  int index;
};

/*----------------------------------------------------------------------------------------*/
/*
Private function:
*/
Status music_setField (Music *m, char *key, char *value);

Status music_setField (Music *m, char *key, char *value) {
  if (!key || !value) return ERROR;

  if (strcmp(key, "id") == 0) {
    return music_setId(m, atol(value));
  } else if (strcmp(key, "title") == 0) {
    return music_setTitle(m, value);
  } else if (strcmp(key, "artist") == 0) {
    return music_setArtist(m, value);
  } else if (strcmp(key, "duration") == 0) {
    return music_setDuration(m, (unsigned short)atoi(value));
  } else if (strcmp(key, "state") == 0) {
    return music_setState(m, (State)atoi(value));
  }

  return ERROR;
}

/*----------------------------------------------------------------------------------------*/
Music *music_initFromString(char *descr) {
    Music *m = NULL;
    char *buffer = NULL;
    char *p, *key, *value;

    if (!descr) return NULL;

    buffer = (char *)malloc(strlen(descr) + 1);
    if (!buffer) return NULL;
    strcpy(buffer, descr);

    m = music_init();
    if (!m) {
        free(buffer);
        return NULL;
    }

    p = buffer;

    while (*p != '\0') {

        /* Skip whitespace */
        while (*p == ' ' || *p == '\t' || *p == '\n') {
            p++;
        }
        if (*p == '\0') break;

        /* Parse key */
        key = p;
        while (*p != '\0' && *p != ':') {
            p++;
        }
        if (*p == '\0') break;
        *p = '\0';
        p++;

        /* Expect opening quote */
        if (*p != '"') break;
        p++;

        /* Parse value */
        value = p;
        while (*p != '\0' && *p != '"') {
            p++;
        }
        if (*p == '\0') break;
        *p = '\0';
        p++;

        music_setField(m, key, value);
    }

    free(buffer);
    return m;
}



/**  Remaining functions of music.h to be implemented here **/

Music *music_init() {
  Music *m = NULL;

  /* Allocates memory for the Music struct */
  if (!(m = (Music *) calloc (1, sizeof(Music)))) {
    return NULL;
  }

  /* Initializes all the Music data */
    m->id = 0;
    m->title[0] = '\0';
    m->artist[0] = '\0';
    m->duration = 0;
    m->state = NOT_LISTENED;
    m->index = 0;

    return m;
}

void music_free(void *m) {
    if (!m) {
      return;
    }
    
    free(m);
}

Status music_setId(Music *m, const long id){
  if(!m || id<0){
    return ERROR;
  }

  m->id = id;

  return OK;
}

long music_getId(const Music *m){
  if(!m){
    return -1;
  }

  return m->id;
}

Status music_setTitle(Music *m, const char *title){
  if(!m || !title){
    return ERROR;
  }

  if(strlen(title) >= STR_LENGTH){
    return ERROR;
  }

  if(!strcpy(m->title, title)){
    return ERROR;
  }

  return OK;
}

const char* music_getTitle(const Music *m){
  if(!m){
    return NULL;
  }

  return m->title;
}

Status music_setArtist(Music *m, const char *artist){
  if(!m || !artist){
    return ERROR;
  }

  if(strlen(artist) >= STR_LENGTH){
    return ERROR;
  }

  if(!strcpy(m->artist, artist)){
    return ERROR;
  }

  return OK;
}

const char* music_getArtist(const Music *m){
  if(!m){
    return NULL;
  }

  return m->artist;
}

Status music_setDuration(Music *m, const unsigned short duration){
  if(!m){
    return ERROR;
  }

  m->duration = duration;

  return OK;
}

unsigned short music_getDuration(const Music *m){
  if(!m){
    return 0;
  }

  return m->duration;
}

Status music_setState(Music *m, const State state){
  if(!m || state == ERROR_MUSIC){
    return ERROR;
  }

  m->state = state;

  return OK;
}

State music_getState(const Music *m){
  if(!m){
    return ERROR_MUSIC;
  }

  return m->state;
}

int music_getIndex(const Music *m) {
  if (!m) {
    return -1;
  }

  return m->index;
}

Status music_setIndex(Music *m, int index) {
  if (!m || index < 0) {
    return ERROR;
  }

  m->index = index;

  return OK;
}

int music_cmp(const void *m1, const void *m2) {
  const Music *a = (const Music *)m1;
  const Music *b = (const Music *)m2;
  int title_cmp;

  /* Depending on what music is valid it returns different integers */
  if (!a && !b) {
    return 0;
  } else if (!a) {
    return -1;
  } else if (!b) {
    return 1;
  }

  if (a->id != b->id) {
    if (a->id < b->id) {
      return -1;
    } else {
      return 1;
    }
  }

  title_cmp = strcmp(a->title, b->title);

  if (title_cmp != 0) {
    return title_cmp;
  }

  return strcmp(a->artist, b->artist);
}

void *music_copy(const void *src) {
  const Music *original = (const Music *)src;
  Music *copy = NULL;

  if (!src) {
    return NULL;
  }

  /* Initializes the copy pointer */
  if (!(copy = music_init())) {
    return NULL;
  }

  /* Stores in the copy pointer the original data */
  copy->id = original->id;
  strcpy(copy->title, original->title);
  strcpy(copy->artist, original->artist);
  copy->duration = original->duration;
  copy->state = original->state;

  return copy;
}

int music_plain_print(FILE *pf, const void *m) {
  const Music *music = (const Music *)m;

  if (!pf || !m) {
    return -1;
  }

  return fprintf(pf, "[%ld, %s, %s, %hu, %d, %d]", music->id, music->title, music->artist, music->duration, music->state, music->index);
}

int music_formatted_print(FILE * pf, const void * m) {
	Music *aux = NULL;
	int counter = 0, minutes, secs;

	if (!pf || !m) {
    return -1;
  }

	aux = (Music*)m;
	
	if (!aux->duration || aux->duration <= 0) return -1;
	minutes = aux->duration / 60;
    secs = aux->duration % 60;
	
	counter = fprintf(pf, "\t ɴᴏᴡ ᴘʟᴀʏɪɴɢ: %s\n", aux->title);
	counter += fprintf(pf, "\t • Artist %s •\n", aux->artist);
	counter += fprintf(pf, "\t──────────⚪──────────\n");
	counter += fprintf(pf, "\t\t◄◄⠀▐▐ ⠀►►\n");
	counter += fprintf(pf, "\t 0:00 / %02d:%02d ───○ 🔊⠀\n\n", minutes, secs);
	
	return counter;
}

