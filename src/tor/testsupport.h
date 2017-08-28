#ifndef TOR_TESTSUPPORT_H
#define TOR_TESTSUPPORT_H

#ifdef TOR_UNIT_TESTS
#define STATIC
#else
#define STATIC static
#endif

#ifdef TOR_UNIT_TESTS
#define MOCK_DECL(rv, funcname, arglist)     \
  rv funcname ##__real arglist;              \
  extern rv(*funcname) arglist
#define MOCK_IMPL(rv, funcname, arglist)     \
  rv(*funcname) arglist = funcname ##__real; \
  rv funcname ##__real arglist
#define MOCK(func, replacement)                 \
  do {                                          \
    (func) = (replacement);                     \
  } while (0)
#define UNMOCK(func)                            \
  do {                                          \
    func = func ##__real;                       \
  } while (0)
#else
#define MOCK_DECL(rv, funcname, arglist) \
  rv funcname arglist
#define MOCK_IMPL(rv, funcname, arglist) \
  rv funcname arglist
#endif

#endif

