#include <stdio.h>
#include "core/log.h"


int main(void) {

    log_set_level(LOG_LEVEL_TRACE);
    LOG_TRACE("Test");
    LOG_DEBUG("Test");
    LOG_INFO("Test");
    LOG_WARN("Test");
    LOG_ERROR("Test");
    //LOG_FATAL("Test");
    return 0;
}
