#ifndef LPOSIX_H
#define LPOSIX_H

#include <rpm/rpmutil.h>


#ifdef __cplusplus
extern "C" {
#endif

RPM_GNUC_INTERNAL
void check_deprecated(lua_State *L, const char *func, const char *deprecated_in);

RPM_GNUC_INTERNAL
int luaopen_posix (lua_State *L);

#ifdef __cplusplus
}
#endif

#endif
