This blog is for putting the implement of `Utilities` and `Map Declaration` of this game.

[Back to `intro.md`](/blog/35/6464e26c426c19a595da2748)

This is the Utilities code:

```cpp

// Utilities

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cstring>
#include <random>
#include <vector>
#include <ctime>
#include <cmath>
#include <set>
#include <map>

#if !(defined(__WINDOWS_) || defined(_WIN32))
#include <sys/select.h>
#include <unistd.h>
#else
#include <windows.h>
#endif

using namespace std;

using ull = unsigned long long;
#define MADE_MAP 1

struct SGET_RET
{
    string curarg;
    string curtsk;
};

#define elif else if
#define pii pair<int, ull>
#define sstream stringstream
#define next(i) i = sget(i.curarg)

#if !(defined(__WINDOWS_) || defined(_WIN32))
static void Sleep(unsigned int ms)
{
    timeval tval;
    tval.tv_sec = ms / 1000;
    tval.tv_usec = ms % 1000 * 1000;
    select(0, NULL, NULL, NULL, &tval);
}
#endif

static void System_Clear()
{
    system(
#if !(defined(__WINDOWS_) || defined(_WIN32))
        "clear"
#else
        "cls"
#endif
    );
}

static string operator*(string a, int b)
{
    string res;
    while (b)
    {
        if (b & 1)
        {
            res += a;
        }
        b >>= 1;
        a += a;
    }
    return res;
}

static SGET_RET sget(string tsk)
{
    return SGET_RET{tsk.substr(tsk.find(';') + 1), tsk.substr(0, tsk.find(';'))};
}

static string itos(ull i)
{
    sstream sst;
    if (i < 10000)
    {
        sst.clear();
        sst << i;
        string res;
        sst >> res;
        return res;
    }
    else
    {
        ull rmd, ts = 0;
        while (i >= 1000)
        {
            ts++;
            rmd = i % 1000;
            i /= 1000;
        }
        string res, tmp;
        sst.clear();
        sst << i;
        sst >> res;
        if (res.length() > 1)
        {
            return res + " kmbtq"[ts];
        }
        else
        {
            sst.clear();
            sst << rmd / 100;
            sst >> tmp;
            return res + "." + tmp + " kmbtq"[ts];
        }
    }
}

```

and the Map Declaration code is:

```cpp

// Map Declarations
class ExploreMap
{
public:
    SGET_RET operator()(string);
    string save();
    SGET_RET load(SGET_RET);
};

class Town_1 : public ExploreMap
{
public:
    ull carpenter_lv_1 = 0;
    ull mason_lv_1 = 0;
    SGET_RET operator()(string);
    string save();
    SGET_RET load(SGET_RET);
};

```
