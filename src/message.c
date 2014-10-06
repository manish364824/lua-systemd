#include "lua.h"
#include "lauxlib.h"

#include <systemd/sd-journal.h>
#include <stdlib.h>
#include <errno.h>

#include "util.c"
#include "message.h"
#include "id128.h"

int journal_get_catalog_for_message_id (lua_State *L) {
	sd_id128_t *id = (sd_id128_t*)luaL_checkudata(L, 1, ID128_METATABLE);
	char *ret;
	int err = sd_journal_get_catalog_for_message_id(*id, &ret);
	if (err == -ENOENT) {
		lua_pushboolean(L, 0);
		return 1;
	} else if (err != 0) {
		return handle_error(L, -err);
	} else {
		lua_pushstring(L, ret);
		free(ret);
		return 1;
	}
}
