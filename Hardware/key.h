#ifndef __KEY_H
#define __KEY_H
typedef enum{
	KEY_NONE = 0,
	KEY_OK,
	KEY_BACK
} KeyEvent;

void KeyInit(void);
KeyEvent Key_GetEvent(void);

#endif 
