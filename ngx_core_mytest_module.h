#ifndef _NGX_CORE_MYTEST_MODULE_H_INCLUDED_
#define _NGX_CORE_MYTEST_MODULE_H_INCLUDED_

typedef char *(*Func)(char *);

typedef struct {
    ngx_int_t                 a;
    ngx_int_t                 b;
    char *error;
    void *handle;
    void (*Hello)();
    Func myFunc;
    int (*Add)(int, int);

} ngx_core_test_conf_t;

extern ngx_module_t           ngx_core_mytest_module;

#endif


