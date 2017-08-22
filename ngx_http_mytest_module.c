#include <ngx_config.h>  
#include <ngx_core.h>  
#include <ngx_http.h> 
#include <dlfcn.h> 
#include "ngx_core_mytest_module.h"
  
static ngx_int_t ngx_http_mytest_handler(ngx_http_request_t *r);  
static char *   
ngx_http_mytest(ngx_conf_t *cf, ngx_command_t *cmd, void *conf);  

static ngx_command_t ngx_http_mytest_commands[] = {  
    {  
        ngx_string("mytest"),  
        NGX_HTTP_MAIN_CONF|NGX_HTTP_SRV_CONF|NGX_HTTP_LOC_CONF|NGX_HTTP_LMT_CONF|NGX_CONF_NOARGS,  
        ngx_http_mytest,  
        NGX_HTTP_LOC_CONF_OFFSET,  
        0,  
        NULL  
    },  
    ngx_null_command  
};  

static ngx_http_module_t ngx_http_mytest_module_ctx = {  
    NULL,  
    NULL,  
    NULL,  
    NULL,  
    NULL,  
    NULL,  
    NULL,  
    NULL  
};  

ngx_module_t ngx_http_mytest_module = {  
    NGX_MODULE_V1,  
    &ngx_http_mytest_module_ctx,  
    ngx_http_mytest_commands,  
    NGX_HTTP_MODULE,  
    NULL,  
    NULL,  
    NULL,  
    NULL,  
    NULL,  
    NULL,  
    NULL,  
    NGX_MODULE_V1_PADDING  
};


ngx_core_test_conf_t  *ctcf;

char *error = NULL;
void *handle = NULL;
void (*Hello)();
typedef char *(*Func)(char *);
int (*add)(int, int);
 
int aa = 0;
 
static char *   
ngx_http_mytest(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)  
{  
    ngx_http_core_loc_conf_t *clcf;  
  
    clcf = ngx_http_conf_get_module_loc_conf(cf, ngx_http_core_module);
    clcf->handler = ngx_http_mytest_handler;

    ctcf = (ngx_core_test_conf_t *) ngx_get_conf(cf->cycle->conf_ctx, ngx_core_mytest_module);
    ngx_log_error(NGX_LOG_EMERG, cf->log, 0, "aa111aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa!type:;byte----begin3333|%p", ctcf);
    if (ctcf != NULL){
    ctcf->Hello();
    int c = ctcf->Add(1,2);
    char cstr_name[100] = "hjchen";
    //ngx_cpystrn((u_char *)cstr_name, (u_char *)r->args.data, 100);
    char *cstr_return_name = ctcf->myFunc(cstr_name);
    aa = ctcf->a+1;
    //ngx_log_debug2(NGX_LOG_DEBUG_HTTP, cf->log, 0, "aa111aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa!type:;bytes:%ui;%s", 0, 0);    
    ngx_log_error(NGX_LOG_EMERG, cf->log, 0, "aa111aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa!type:;bytes a=%i|%s|%p|a+b=%i", ctcf->a, cstr_return_name,ctcf->Add, c);
}
/*    
    handle = dlopen("/root/c/myso.so", RTLD_LAZY);
    error =  dlerror();
    if ( error != NULL )
    {
      printf("Fail to load so file.\n[%s]\n", error);
      return NGX_CONF_ERROR;
    }
   
    Hello = (void(*)())dlsym(handle, "Hello");
    error =  dlerror();
    if ( error != NULL )
    {
      printf("Fail to get function address.\n[%s]\n", error);
      return NGX_CONF_ERROR;
    }
*/   
    //Hello();
    //dlclose(handle);
  
    return NGX_CONF_OK;  
}  
  
static ngx_int_t ngx_http_mytest_handler(ngx_http_request_t *r)  
{  
    ngx_log_error(NGX_LOG_EMERG, r->connection->log, 0, "aa222aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa!type:;bytes|%i", aa);
    if (!(r->method & (NGX_HTTP_GET | NGX_HTTP_HEAD))) {  
        return NGX_HTTP_NOT_ALLOWED;  
    }  
  
    ngx_int_t rc = ngx_http_discard_request_body(r);  
    if (rc != NGX_OK) {  
        return rc;  
    }

    /*
    handle = dlopen("/root/c/myso.so", RTLD_LAZY);
    error =  dlerror();
    if ( error != NULL )
    {
      printf("Fail to load so file.\n[%s]\n", error);
      return NGX_ERROR;
    }
    Hello = (void(*)())dlsym(handle, "Hello");
    error =  dlerror();
    if ( error != NULL )
    {
      printf("Fail to get function address.\n[%s]\n", error);
      return NGX_ERROR;
    }*/

    //Hello();
  	//**********************************************************
    /*Func myFunc = (Func)dlsym(ctcf->handle, "Func");
    error =  dlerror();
    if ( error != NULL )
    {
      printf("Fail to get function address.\n[%s]\n", error);
      return -1;
    }*/

    add = (int(*)(int, int))dlsym(ctcf->handle, "Add");
    error =  dlerror();
    if (error != NULL )
    {
        printf("Fail to get function address.\n[%s]\n", error);
        return -1;
    }

    ngx_log_error(NGX_LOG_EMERG, r->connection->log, 0, "aa2222233333aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa!|%p|%i", ctcf->Add, r->args.len);

    char cstr_name[200] = "no data!";
    /* add
    //ngx_cpystrn((u_char *)cstr_name, (u_char *)r->args.data, r->args.len+1);
    int a = -1, bb = -1;
    unsigned int i = 0;
    char *p_cstr_name = (char *)r->args.data;
    while (i < r->args.len) {
        if (*p_cstr_name++ == '=') {
            if (a == -1) {
                a = atoi(p_cstr_name);
            } else {
                bb = atoi(p_cstr_name);    
            }
        }
        i++;
    }
    ngx_sprintf((u_char *)cstr_name, "%i", add(a, bb));
    */
    char *cstr_return_name = ctcf->myFunc(cstr_name);
    //ngx_log_error(NGX_LOG_EMERG, r->connection->log, 0, "a=%i,b=%i,c=%i; aa33333aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa%i!%s", a, bb, cc, ngx_strlen(cstr_return_name), cstr_return_name);
  
    ngx_log_error(NGX_LOG_EMERG, r->connection->log, 0, "aa44444444aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa!|%p|%s|", cstr_return_name, cstr_name);
    ngx_str_t response = ngx_string("no data!");//= ngx_string(cstr_return_name);//ngx_string("Hello World1");
    if (ngx_strlen(cstr_name) > 0) {
        response.data = (u_char *)cstr_return_name;
        response.len = ngx_strlen(cstr_return_name);
    }
    //response.data = (u_char *)cstr_name;
    //response.len = ngx_strlen(cstr_name);
    //ngx_str_t response  = ngx_string("Hello World1");
  	//**********************************************************

    //dlclose(handle);  
  
    ngx_str_t type = ngx_string("text/plain");  
    r->headers_out.status = NGX_HTTP_OK;  
    r->headers_out.content_length_n = response.len;  
    r->headers_out.content_type = type;  
  
    rc = ngx_http_send_header(r);  
    if (rc == NGX_ERROR || rc > NGX_OK || r->header_only) {  
        return rc;  
    }  
  
    ngx_buf_t *b;  
    b = ngx_create_temp_buf(r->pool, response.len);  
    if (b == NULL) {  
        return NGX_HTTP_INTERNAL_SERVER_ERROR;  
    }  
  
    ngx_memcpy(b->pos, response.data, response.len);  
    b->last = b->pos + response.len;  
    b->last = b->pos + response.len;  
    b->last_buf = 1;  
  
    ngx_chain_t out;  
    out.buf = b;  
    out.next = NULL;  
  
    return ngx_http_output_filter(r, &out);  
}  
