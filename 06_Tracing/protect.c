#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdio.h>
#include <unistd.h>

typedef int (*unlink_type)(const char *pathname);

int unlink(const char *pathname) {
    if (strstr(pathname, "PROTECT") != NULL) {
        printf("Prevented deletion of: %s\n", pathname);
        return 0; // Успешное "удаление" (на самом деле просто предотвращение)
    }

    unlink_type original_unlink = (unlink_type)dlsym(RTLD_NEXT, "unlink");
    return original_unlink(pathname);
}
