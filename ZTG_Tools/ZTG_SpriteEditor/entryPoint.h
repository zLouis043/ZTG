#ifndef ZTG_SPRITEEDITOR_ENTRYPOINT_H
#define ZTG_SPRITEEDITOR_ENTRYPOINT_H

#include <ZTG/ZTG.h>

extern char ** save_file_name;
extern char ** load_file_name;

void Update(float elapsedTime);
void HandleInputs();

#endif //ZTG_SPRITEEDITOR_ENTRYPOINT_H
