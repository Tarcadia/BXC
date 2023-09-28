
#ifndef __BX_CODE_ENV_DEBUG_H__
#define __BX_CODE_ENV_DEBUG_H__

#include <stdio.h>


#define __BX_CODE_ENV_DBG_PRINT__(info, ...) {\
    printf(\
        "[%s:%d] " info "\n",\
        __FILE__, __LINE__, ##__VA_ARGS__\
    );\
}


#endif /* __BX_CODE_ENV_DEBUG_H__ */
