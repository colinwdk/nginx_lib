#include <ngx_config.h>
#include <ngx_core.h>
#include "ngx_core_mytest_module.h"


static void *ngx_test_module_create_conf(ngx_cycle_t *cycle);
char * ngx_test(ngx_conf_t *cf, ngx_command_t *cmd, void *conf);

static ngx_command_t ngx_test_commands[] = {
     {   
     ngx_string("commands"),
         NGX_MAIN_CONF|NGX_DIRECT_CONF|NGX_CONF_NOARGS,
         ngx_test,      
         0,
         0,
         NULL
      },
      ngx_null_command
};

static ngx_core_module_t ngx_test_module_ctx = {
    ngx_string("test"),
    ngx_test_module_create_conf,
    NULL
};

ngx_module_t ngx_core_mytest_module = {
    NGX_MODULE_V1,
    &ngx_test_module_ctx,
    ngx_test_commands,
    NGX_CORE_MODULE,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NGX_MODULE_V1_PADDING
};

char * ngx_test(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    //FILE *fp = fopen("test", "w");
    //fprintf(fp,"call ngx_test\n");
    //fclose(fp);
    printf("1111call ngx_test_module_create_conf\n");

    return NGX_CONF_OK;

}

ngx_core_test_conf_t  *ctcf = NULL;
static void *ngx_test_module_create_conf(ngx_cycle_t *cycle){
    printf("call ngx_test_module_create_conf\n");

   if(ctcf != NULL)
    dlclose(ctcf->handle);
    //if (NULL == ctcf){
        ctcf = ngx_pcalloc(cycle->pool, sizeof(ngx_core_test_conf_t));
        if (ctcf == NULL) {
            return NULL;
        }
    //    printf("ctcf == NULL|%p\n", ctcf);
    //} else {
    //   printf("ctcf != NULL|%p\n", ctcf);
    //    dlclose(ctcf->handle);
    //}
    ctcf->a = 22;
    ctcf->b = 33;
    
    ctcf->handle = dlopen("/root/c/myso.so", RTLD_LAZY|RTLD_GLOBAL);
    ctcf->error =  dlerror();
    if ( ctcf->error != NULL )
    {
      printf("Fail to load so file.\n[%s]\n", ctcf->error);
      return NGX_CONF_ERROR;
    }
    
    ctcf->Hello = (void(*)())dlsym(ctcf->handle, "Hello");
    ctcf->error =  dlerror();
    if ( ctcf->error != NULL )
    {
      printf("Fail to get function address.\n[%s]\n", ctcf->error);
      return NGX_CONF_ERROR;
    }

     ctcf->myFunc = (Func)dlsym(ctcf->handle, "Func");
     ctcf->error =  dlerror();
     if ( ctcf->error != NULL )
     {
         printf("Fail to get function address.\n[%s]\n", ctcf->error);
         return NGX_CONF_ERROR;
     }
     ctcf->Add = (int(*)(int, int))dlsym(ctcf->handle, "Add");
     ctcf->error =  dlerror();
     if ( ctcf->error != NULL )
     {
         printf("Fail to get function address.\n[%s]\n", ctcf->error);
         return NGX_CONF_ERROR;
     }

    printf("call ngx_test_module_create_conf--end%i\n", ctcf->Add(1,2));
    return ctcf;//NULL;
}

