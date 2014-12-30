#ifndef UQKBDHOOK_H
#define UQKBDHOOK_H

#include <Windows.h>

#if defined __cplusplus
extern "C" {
#endif

int KBDHook_Start(void (*callback)(BYTE, void*), void *cb_argument);
void KBDHook_Stop(void);

#if defined __cplusplus
}
#endif

#endif //UQKBDHOOK_H
