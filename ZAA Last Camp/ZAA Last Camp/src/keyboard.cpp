#include "keyboard.h"

#include <ctype.h>
#include <iostream>

void keyUp(unsigned char key, int x, int y) {
	key = tolower(key);
	if (key >= keycount) return;
	keys[key] = false;
}
void keyDown(unsigned char key, int x, int y) {
	key = tolower(key);
	if (key >= keycount) return;
	keys[key] = true;
}

bool isKeyDown(unsigned char key) {
	key = tolower(key);
	if (key >= keycount) return false;
	return keys[key];
}

bool isKeyDown(int keyID) {
	if (keyID >= keycount) return false;
	return keys[keyID];
}