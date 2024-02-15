#ifndef ZTG_SPRITEEDITOR_ENTRYPOINT_H
#define ZTG_SPRITEEDITOR_ENTRYPOINT_H

#include <ZTG/ZTG.h>

extern char ** save_file_name;
extern char ** load_file_name;

void Start();
void Update(float elapsedTime);
void HandleInputs();
void load_sprite_from_memory(char *filename);
void set_save_name_from_file(char *filename);

#endif //ZTG_SPRITEEDITOR_ENTRYPOINT_H
