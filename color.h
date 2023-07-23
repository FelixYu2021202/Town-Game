#ifndef TG_COLOR_LIB
#define TG_COLOR_LIB

// These are settings
#define USE_COLOR 1

#if (defined(__WINDOWS_) || defined(_WIN32))
#define SET_GNU_COLOR_IF_AVAILABLE 0
#else //(defined(__WINDOWS_) || defined(_WIN32))
#define SET_GNU_COLOR_IF_AVAILABLE 1
#endif //(defined(__WINDOWS_) || defined(_WIN32))

#define REVERSE_COLOR 1
#define USE_NAMESPACE 1

#include <iostream>
#include <functional>
#if (defined(__WINDOWS_) || defined(_WIN32))
#include <windows.h>
#endif // (defined(__WINDOWS_) || defined(_WIN32))

using namespace std;

class ColorWrapper
{
private:
    bool gnu()
    {
#if (defined(__WINDOWS_) || defined(_WIN32))
#if SET_GNU_COLOR_IF_AVAILABLE
        "To Do";
#else  // SET_GNU_COLOR_IF_AVAILABLE
        return false;
#endif // SET_GNU_COLOR_IF_AVAILABLE
#endif // (defined(__WINDOWS_) || defined(_WIN32))
        return true;
    }

private:
    template <int light, int fore, int back>
    class GnuWrapper
    {
    public:
        template <typename _CT, typename _T>
        static basic_ostream<_CT, _T> &sentry(basic_ostream<_CT, _T> &os)
        {
            os << string("\e[") + (light ? "1;" : "") + to_string(fore) + (back != 47 ? ";" + to_string(back) : "") + "m";
            return os;
        }
    };
    template <int light, int fore, int back>
    class WdsWrapper
    {
    public:
        template <typename _CT, typename _T>
        static basic_ostream<_CT, _T> &sentry(basic_ostream<_CT, _T> &os)
        {
#if (defined(__WINDOWS_) || defined(_WIN32))
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (fore - 30) | (light << 3) | ((back - 40) << 4));
#elif !SET_GNU_COLOR_IF_AVAILABLE // (defined(__WINDOWS_) || defined(_WIN32))
            assert(("Unable to use gnu color renderer or windows color renderer!", false));
#endif                            // (defined(__WINDOWS_) || defined(_WIN32))
            return os;
        }
    };
    template <int light, int fore, int back>
    class NullWrapper
    {
    public:
        template <typename _CT, typename _T>
        static basic_ostream<_CT, _T> &sentry(basic_ostream<_CT, _T> &os)
        {
            return os;
        }
    };
    template <int fore, int back, int light, typename _CT, typename _T>
    inline decltype(endl<_CT, _T>) &define_wrapper()
    {
        if (gnu())
        {
            return GnuWrapper<light, fore, back>::template sentry<_CT, _T>;
        }
        else
        {
            return WdsWrapper<light, fore, back>::template sentry<_CT, _T>;
        }
    }

public:
    template <int fore, int back, int light, typename _CT, typename _T>
    inline decltype(endl<_CT, _T>) &wrapper()
    {
        return define_wrapper<fore, back, light, _CT, _T>();
    }
    template <typename _CT, typename _T>
    inline decltype(endl<_CT, _T>) &null_wrapper()
    {
        return NullWrapper<0, 0, 0>::template sentry<_CT, _T>;
    }
};

static ColorWrapper color_wrapper;
#define DEFINE_COLOR(name, fore, back, light)                           \
    template <typename _CT, typename _T>                                \
    inline basic_ostream<_CT, _T> &name(basic_ostream<_CT, _T> &os)     \
    {                                                                   \
        return color_wrapper.wrapper<fore, back, light, _CT, _T>()(os); \
    }                                                                   \
    inline void set_##name()                                            \
    {                                                                   \
        cout << name;                                                   \
    }

#if USE_NAMESPACE
namespace color
{
#endif // USE_NAMESPACE

#if USE_COLOR

#if REVERSE_COLOR
    DEFINE_COLOR(black, 30, 47, 0)
    DEFINE_COLOR(red, 31, 47, 0)
    DEFINE_COLOR(green, 32, 47, 0)
    DEFINE_COLOR(yellow, 33, 47, 0)
    DEFINE_COLOR(blue, 34, 47, 0)
    DEFINE_COLOR(magenta, 35, 47, 0)
    DEFINE_COLOR(cyan, 36, 47, 0)
    DEFINE_COLOR(white, 37, 47, 0)
    DEFINE_COLOR(light_black, 30, 47, 1)
    DEFINE_COLOR(light_red, 31, 47, 1)
    DEFINE_COLOR(light_green, 32, 47, 1)
    DEFINE_COLOR(light_yellow, 33, 47, 1)
    DEFINE_COLOR(light_blue, 34, 47, 1)
    DEFINE_COLOR(light_magenta, 35, 47, 1)
    DEFINE_COLOR(light_cyan, 36, 47, 1)
    DEFINE_COLOR(light_white, 37, 47, 1)
#else  // REVERSE_COLOR
    DEFINE_COLOR(black, 30, 40, 0)
    DEFINE_COLOR(red, 31, 40, 0)
    DEFINE_COLOR(green, 32, 40, 0)
    DEFINE_COLOR(yellow, 33, 40, 0)
    DEFINE_COLOR(blue, 34, 40, 0)
    DEFINE_COLOR(magenta, 35, 40, 0)
    DEFINE_COLOR(cyan, 36, 40, 0)
    DEFINE_COLOR(white, 37, 40, 0)
    DEFINE_COLOR(light_black, 30, 40, 1)
    DEFINE_COLOR(light_red, 31, 40, 1)
    DEFINE_COLOR(light_green, 32, 40, 1)
    DEFINE_COLOR(light_yellow, 33, 40, 1)
    DEFINE_COLOR(light_blue, 34, 40, 1)
    DEFINE_COLOR(light_magenta, 35, 40, 1)
    DEFINE_COLOR(light_cyan, 36, 40, 1)
    DEFINE_COLOR(light_white, 37, 40, 1)
#endif // REVERSE_COLOR

#else // USE_COLOR

DEFINE_COLOR(black, 0, 0, 0)
DEFINE_COLOR(red, 0, 0, 0)
DEFINE_COLOR(green, 0, 0, 0)
DEFINE_COLOR(yellow, 0, 0, 0)
DEFINE_COLOR(blue, 0, 0, 0)
DEFINE_COLOR(magenta, 0, 0, 0)
DEFINE_COLOR(cyan, 0, 0, 0)
DEFINE_COLOR(white, 0, 0, 0)
DEFINE_COLOR(light_black, 0, 0, 0)
DEFINE_COLOR(light_red, 0, 0, 0)
DEFINE_COLOR(light_green, 0, 0, 0)
DEFINE_COLOR(light_yellow, 0, 0, 0)
DEFINE_COLOR(light_blue, 0, 0, 0)
DEFINE_COLOR(light_magenta, 0, 0, 0)
DEFINE_COLOR(light_cyan, 0, 0, 0)
DEFINE_COLOR(light_white, 0, 0, 0)

#endif // USE_COLOR

    DEFINE_COLOR(reset, 0, 0, 0)

    template <typename _CT, typename _T>
    inline basic_ostream<_CT, _T> &endc(basic_ostream<_CT, _T> &os)
    {
        return os << reset << endl;
    }

#if USE_NAMESPACE
}
#endif // USE_NAMESPACE

#undef SET_GNU_COLOR_IF_AVAILABLE
#undef REVERSE_COLOR
#undef USING_NAMESPACE

#endif // TG_COLOR_LIB
