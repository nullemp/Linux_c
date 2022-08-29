#include <stdio.h>
#include <stdlib.h>

#define unconstify(underlying_type, expr) \
	(StaticAssertExpr(__builtin_types_compatible_p(__typeof(expr), const underlying_type), \
					  "wrong cast"), \
	 (underlying_type) (expr))
#define StaticAssertStmt(condition, errmessage) \
	do { _Static_assert(condition, errmessage); } while(0)
#define StaticAssertExpr(condition, errmessage) \
	((void) ({ StaticAssertStmt(condition, errmessage); true; }))


        typedef struct PQExpBufferData
{
        char       *data;
        size_t          len;
        size_t          maxlen;
} PQExpBufferData;

         typedef PQExpBufferData *PQExpBuffer;

int main()
{
	PQExBufferData s;
        PQExpBuffer str = &s;
        	if (str->data != oom_buffer)
		free(str->data);

	/*
 * 	 * Casting away const here is a bit ugly, but it seems preferable to not
 * 	 	 * marking oom_buffer const.  We want to do that to encourage the compiler
 * 	 	 	 * to put oom_buffer in read-only storage, so that anyone who tries to
 * 	 	 	 	 * scribble on a broken PQExpBuffer will get a failure.
 * 	 	 	 	 	 */
	str->data = unconstify(char *, oom_buffer_ptr);
	str->len = 0;
	str->maxlen = 0;
	return 0;
}
