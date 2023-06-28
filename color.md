This blog is for putting `Color Implementations` of this game.

[Back to `intro.md`](/blog/35/6464e26c426c19a595da2748)

This is the Color Implementations code:

```cpp
#ifndef TG_COLOR_LIB
#define TG_COLOR_LIB

#define USE_COLOR 0
#define SET_GNU_COLOR_IF_AVAILABLE 1
#define REVERSE_COLOR 1

#include <iostream>
#include <functional>
#if (defined(__WINDOWS_) || defined(_WIN32))
#include <windows.h>
#endif // (defined(__WINDOWS_) || defined(_WIN32))
using namespace std;

class Color
{
private:
    bool gnu = SET_GNU_COLOR_IF_AVAILABLE;
    void check_gnu_color()
    {
#if (defined(__WINDOWS_) || defined(_WIN32))
        string vname;
        using NTPROC = void(__stdcall *)(DWORD *, DWORD *, DWORD *);
        using HINSTANCE hinst = LoadLibrary(_T("ntdll.dll"));
        DWORD dwMajor, dwMinor, dwBuildNumber;
        NTPROC proc = (NTPROC)GetProcAddress(hinst, "RtlGetNtVersionNumbers");
        proc(&dwMajor, &dwMinor, &dwBuildNumber);
        if (dwMajor < 10)
        {
            gnu = false;
        }
#endif // (defined(__WINDOWS_) || defined(_WIN32))
    }

    class Color_8
    {
    public:
        int fore, back;
        int light = 0;
        Color_8(int fore, int back, int light) : fore(fore), back(back), light(light) {}
        Color_8(int fore, int back) : fore(fore), back(back) {}
        Color_8() : fore(37), back(40) {}
    };

public:
    typedef void __cpf(ostream &os);

private:
    template <int light, int fore, int back>
    class GnuWrapper
    {
    public:
        static void sentry(ostream &os)
        {
            os << string("\e[") + (light ? "1;" : "") + to_string(fore) + (back != 47 ? "m\e[" + to_string(back) : "") + "m";
        }
    };
    template <int light, int fore, int back>
    class WdsWrapper
    {
    public:
        static void sentry(ostream &os)
        {
#if (defined(__WINDOWS_) || defined(_WIN32))
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (fore - 30) | (light << 3) | ((back - 40) << 4));
#else  // (defined(__WINDOWS_) || defined(_WIN32))
            assert(("Unable to use gnu color renderer or windows color renderer!", false));
#endif // (defined(__WINDOWS_) || defined(_WIN32))
        }
    };
    template <int light, int fore, int back>
    class NullWrapper
    {
    public:
        static void sentry(ostream &os)
        {
            return;
        }
    };
    template <int fore, int back, int light>
    inline Color::__cpf &define_wrapper()
    {
        if (gnu)
        {
            return GnuWrapper<light, fore, back>::sentry;
        }
        else
        {
            return WdsWrapper<light, fore, back>::sentry;
        }
    }

public:
    template <int fore, int back, int light>
    inline __cpf &wrapper()
    {
        return define_wrapper<fore, back, light>();
    }
    inline __cpf &null_wrapper()
    {
        return NullWrapper<0, 0, 0>::sentry;
    }
} color_wrapper;

#define DC(name, fore, back, light) inline function<void(basic_ostream<char> &)> name = color_wrapper.wrapper<fore, back, light>();
#define DN(name) inline function<void(basic_ostream<char> &)> name = color_wrapper.null_wrapper();

#if USE_COLOR

#if REVERSE_COLOR

DC(black, 30, 47, 0);
DC(red, 31, 47, 0);
DC(green, 32, 47, 0);
DC(yellow, 33, 47, 0);
DC(blue, 34, 47, 0);
DC(magenta, 35, 47, 0);
DC(cyan, 36, 47, 0);
DC(white, 37, 47, 0);
DC(light_black, 30, 47, 1);
DC(light_red, 31, 47, 1);
DC(light_green, 32, 47, 1);
DC(light_yellow, 33, 47, 1);
DC(light_blue, 34, 47, 1);
DC(light_magenta, 35, 47, 1);
DC(light_cyan, 36, 47, 1);
DC(light_white, 37, 47, 1);

#else // REVERSE_COLOR

DC(black, 30, 40, 0);
DC(red, 31, 40, 0);
DC(green, 32, 40, 0);
DC(yellow, 33, 40, 0);
DC(blue, 34, 40, 0);
DC(magenta, 35, 40, 0);
DC(cyan, 36, 40, 0);
DC(white, 37, 40, 0);
DC(light_black, 30, 40, 1);
DC(light_red, 31, 40, 1);
DC(light_green, 32, 40, 1);
DC(light_yellow, 33, 40, 1);
DC(light_blue, 34, 40, 1);
DC(light_magenta, 35, 40, 1);
DC(light_cyan, 36, 40, 1);
DC(light_white, 37, 40, 1);

#endif // REVERSE_COLOR

#else // USE_COLOR

DN(black);
DN(red);
DN(green);
DN(yellow);
DN(blue);
DN(magenta);
DN(cyan);
DN(white);
DN(light_black);
DN(light_red);
DN(light_green);
DN(light_yellow);
DN(light_blue);
DN(light_magenta);
DN(light_cyan);
DN(light_white);

#endif // USE_COLOR

ostream &operator<<(ostream &os, function<void(basic_ostream<char> &)> pf)
{
    return pf(os), os;
}

#undef SET_GNU_COLOR_IF_AVAILABLE
#undef REVERSE_COLOR
#undef USING_NAMESPACE

#endif // TG_COLOR_LIB

```
