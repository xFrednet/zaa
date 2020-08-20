#pragma once


bool static keys[256];
void keyDown(unsigned char key, int x, int y);
void keyUp(unsigned char key, int x, int y);
bool isKeyDown(unsigned char key);
bool isKeyDown(int keyID);

