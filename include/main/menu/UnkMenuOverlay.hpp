#pragma once
#include <globaldefs.h>
#include "main/dss/UnkOverlaySlot.hpp"

extern UnkOverlaySlot data_020a29f4;            // materiel menu overlay
extern UnkOverlaySlot data_020a29ec;            // town/battle menu overlay

void loadMaterielMenuOverlay(int menu);                // load the overlay of a materiel menu
void loadWindowOverlay(int menu);                // load the overlay of the town (1), battle (2) or ov020 (3) menus
void unloadWindowOverlay();                        // unload the menu overlay
