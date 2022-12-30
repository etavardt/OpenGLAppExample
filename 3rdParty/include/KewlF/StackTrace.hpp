#pragma once

#include "String.hpp"

#if defined DEBUG && defined BACKTRACE
#include <backtrace.h>

#include "App.hpp"

typedef struct backtrace_state BackTraceState;

class StackTrace {
    static const int MAX_LINES = 20;

    /* Used to collect backtrace info.  */
    struct info {
        char *filename;
        int lineno;
        char *function;
    };

    /* Passed to backtrace callback function.  */
    struct bdata {
        struct info *all;
        size_t index;
        size_t max;
        int failed;
    };

    /* Passed to backtrace_simple callback function.  */
    struct sdata {
        uintptr_t *addrs;
        size_t index;
        size_t max;
        int failed;
    };

    /* Passed to backtrace_syminfo callback function.  */
    struct symdata {
        const char *name;
        uintptr_t val, size;
        int failed;
    };

    /* The number of failures.  */
    int failures;

  public:
    static struct info all[MAX_LINES];
    struct bdata data;

    static StackTrace &getInstance();
    String getStackTrace();

  protected:
  private:
    char *appFileName = App::getApp().getAppFileName();
    BackTraceState *backTraceState;
    static void backTraceErrorCallback(void *data, const char *msg, int errnum);
    static int backtraceFullCallback(void *vdata, uintptr_t pc, const char *filename, int lineno, const char *function);
    String demangle(const char *mangled_name);

    StackTrace();
    ~StackTrace();
};
#else
class StackTrace {
  public:
    static StackTrace &getInstance();
    String getStackTrace() { return ""; }
  private:
    StackTrace() = default;
    ~StackTrace() = default;
};
#endif
