#include <ctype.h>
#include <freeglut.h>

#include "keyboard.h"

void keyDown(unsigned char key, int x, int y) {
	key = tolower(key);
	keys[key] = true;
}
void keyUp(unsigned char key, int x, int y) {
	key = tolower(key);
	keys[key] = false;
}

bool isKeyDown(unsigned char key) {
	key = tolower(key);
	return keys[key];
}

bool isKeyDown(int keyID) {
	return keys[keyID];
}