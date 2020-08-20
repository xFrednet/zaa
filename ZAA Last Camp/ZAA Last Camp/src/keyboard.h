#pragma once


const int keycount = 256;
bool static keys[keycount] = {0};

void keyUp(unsigned char key, int x, int y);
void keyDown(unsigned char key, int x, int y);

bool isKeyDown(unsigned char key);
bool isKeyDown(int keyID);