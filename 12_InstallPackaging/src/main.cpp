#include <iostream>
#include <libintl.h>
#include "hello.h"

#define _(STRING) gettext(STRING)

int main() {
    setlocale(LC_ALL, "");
    bindtextdomain("hello_world_project", "po");
    textdomain("hello_world_project");

    std::cout << _("Hello, World!") << std::endl;
    return 0;
}