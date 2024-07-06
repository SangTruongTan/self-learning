#include <stdio.h>
#include "hello-tp.h"

int main(int argc, char *argv[])
{
    unsigned int i;

    puts("Hello, World!\nPress Enter to continue...");

    /*
     * The following getchar() call only exists for the purpose of this
     * demonstration, to pause the application in order for you to have
     * time to list its tracepoints. You don't need it otherwise.
     */
    getchar();

    /*
     * An lttng_ust_tracepoint() call.
     *
     * Arguments, as defined in `hello-tp.h`:
     *
     * 1. Tracepoint provider name (required)
     * 2. Tracepoint name (required)
     * 3. `my_integer_arg` (first user-defined argument)
     * 4. `my_string_arg` (second user-defined argument)
     *
     * Notice the tracepoint provider and tracepoint names are
     * C identifiers, NOT strings: they're in fact parts of variables
     * that the macros in `hello-tp.h` create.
     */
    lttng_ust_tracepoint(hello_world, my_first_tracepoint, 23,
                         "hi there!");

    for (i = 0; i < argc; i++) {
        lttng_ust_tracepoint(hello_world, my_first_tracepoint,
                             i, argv[i]);
    }

    puts("Quitting now!");
    lttng_ust_tracepoint(hello_world, my_first_tracepoint,
                         i * i, "i^2");
    return 0;
}
