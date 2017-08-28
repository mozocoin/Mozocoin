#ifndef TOR_NTMAIN_H
#define TOR_NTMAIN_H

//#ifdef _WIN32
//#if !defined (WINCE)
//#define NT_SERVICE
//#endif
//#endif

#ifdef NT_SERVICE
int nt_service_parse_options(int argc, char **argv, int *should_exit);
int nt_service_is_stopping(void);
void nt_service_set_state(DWORD state);
#else
#define nt_service_is_stopping() 0
#endif

#endif

