#ifndef TG_LIB
#define TG_LIB "TG_LIB;Town Game by cosf;header-version;v0.7.1"

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

#include "color.h"

using namespace std;
using namespace color;

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

// Game Board

class GameBoard
{
public:
    // Game Data Analysing (Inventory)

    map<string, vector<ull>> invent;
    set<string> invent_names;
    mt19937 tst;

    void invent_cleanup()
    {
        set<string> res_in;
        for (string in : invent_names)
        {
            int ii = 0;
            for (int i = 0; i < 10; i++)
            {
                if (invent[in][i] != 0)
                {
                    res_in.insert(in);
                    ii = 1;
                    break;
                }
            }
            if (!ii && invent[in].size())
            {
                invent.erase(in);
            }
        }
        invent_names = res_in;
    }

    void invent_add(string type, int lv, ull num)
    {
        if (!invent_names.count(type))
        {
            invent_names.insert(type);
            invent[type] = vector<ull>(10);
        }
        invent[type][lv] += num;
    }

    bool check_purchase(string type, int lv, ull num)
    {
        if (!invent_names.count(type))
        {
            return false;
        }
        return invent[type][lv] >= num;
    }

    void invent_purchase(string type, int lv, ull num) // Must be run after checking check_purchase.
    {
        invent[type][lv] -= num;
    }

    ull sucde[9] = {4, 20, 100, 50, 100, 250, 1000, 4000, 20000};
    ull sucnu[9] = {1, 1, 3, 1, 1, 1, 1, 1, 1};
    ull cvslu[9] = {3, 15, 20, 30, 50, 100, 200, 500, 1000};
    ull cvsld[10] = {0, 5, 25, 45, 70, 150, 400, 1500, 7000, 35000};
    ull craft(ull num, ull de, ull nu)
    {
        ull res = 0;
        for (int i = 1; i <= num; i++)
        {
            res += (tst() % de) < nu;
        }
        return res;
    }

    string scr[10] = {"25%   ", "5%    ", "3%    ", "2%    ", "1%    ", "0.4%  ", "0.1%  ", "0.025%", "0.005%"};
    vector<void (*)()> lvc;

    // Game Data Analysing (Level)

    int level = 1;
    ull lne[100] = {0, 100, 250, 1250, 5000, 25000, 125000, 500000, 2500000, 12500000, 50000000, 250000000, 1250000000, 5000000000};
    ull expr[10] = {0, 0, 0, 1, 1, 2, 4, 7, 14};
    ull exp = 0;
    vector<pii> ulb{{0, 0}, {0, 10}, {1, 10}, {2, 9}, {3, 6}, {3, 35}, {4, 8}, {5, 1}, {5, 6}, {5, 16}, {6, 1}, {6, 5}, {6, 15}, {7, 1}};

    void update_level()
    {
        while (exp >= lne[level])
        {
            exp -= lne[level];
            invent_add("coin", ulb[level].first, ulb[level].second);
            level++;
        }
    }

    void get_exp(ull num)
    {
        exp += num;
        update_level();
    }

    /// Daily Reward & Store

    ull lstr = 0;

    pii purchase(string sn, string in, int sc, int c)
    {
        vector<int> able;
        vector<ull> nd(10, 0);
        int c0 = c;
        for (int i = sc; i; i--)
        {
            c0 *= cvsld[i];
        }
        for (int i = 0; i < sc; i++)
        {
            if (check_purchase(in, i, c0))
            {
                able.push_back(i);
                nd[i] = c0;
            }
            c0 /= cvsld[i + 1];
        }
        for (int i = sc; i < 10; i++)
        {
            if (check_purchase(in, i, c))
            {
                able.push_back(i);
                nd[i] = c;
            }
            c = ceil(c * 1.0L / cvslu[i]);
        }
        if (!able.size())
        {
            lvc[sc]();
            cout << "   Purchase" << endc;
            cout << endc;
            cout << red << "You don't have enough to buy it!" << endc;
            cout << "Enter to be back." << endc;
            string input;
            getline(cin, input);
            return {-1, -1};
        }
        int slen = max(8UL, 2 + in.length());
        lvc[sc]();
        cout << "   Purchase" << endc;
        cout << sn << endc;
        cout << endc;
        cout << "These are the options you can choose(only one):" << endc;
        cout << yellow << "|" << string("-") * slen << "|" << string("-------|") * able.size() << endc;
        cout << yellow << "| " << left << setw(slen - 1) << "level"
             << "|";
        for (int i : able)
        {
            lvc[i]();
            cout << "  " << left << setw(4) << i << yellow << " |";
        }
        cout << endc;
        cout << yellow << "|" << string("-") * slen << "|" << string("-------|") * able.size() << endc;
        cout << yellow << "| " << left << setw(slen - 1) << in
             << "|";
        for (int i : able)
        {
            lvc[i]();
            cout << "  " << left << setw(4) << itos(invent[in][i]) << yellow << " |";
        }
        cout << endc;
        cout << yellow << "|" << string("-") * slen << "|" << string("-------|") * able.size() << endc;
        cout << yellow << "|" << string(" ") * slen << "|";
        for (int i : able)
        {
            cout << red << " -" << left << setw(4) << itos(nd[i]) << yellow << " |";
        }
        cout << endc;
        cout << yellow << "|" << string("-") * slen << "|" << string("-------|") * able.size() << endc;
        cout << yellow << "| " << left << setw(slen - 1) << "result"
             << "|";
        for (int i : able)
        {
            lvc[i]();
            cout << "  " << left << setw(4) << itos(invent[in][i] - nd[i]) << yellow << " |";
        }
        cout << endc;
        cout << yellow << "|" << string("-") * slen << "|" << string("-------|") * able.size() << endc;
        cout << "Please enter the choice(" << green << "0" << reset << " ~ " << white << "9" << reset << ") or abort(any other)." << endc;
        string input;
        getline(cin, input);
        if (isdigit(input[0]))
        {
            if (nd[input[0] ^ '0'])
            {
                invent_purchase(in, input[0] ^ '0', nd[input[0] ^ '0']);
                return {input[0] ^ '0', nd[input[0] ^ '0']};
            }
        }
        return {-1, 0};
    }

    // Game Maps (Basics)

    SGET_RET main_page(string arg)
    {
        cout << "          Main page" << endc;
        cout << magenta << "> Inventory(C) > Level(E)" << endc;
        cout << green << "> Store(P)" << endc;
        cout << blue << "> Explore(F)" << endc;
        cout << green << "> Load(L)      > Save(S)" << endc;
        cout << red << "> Quit(Q)      > Save & Quit(A)" << endc;
        cout << "> Introduction(I)" << endc;
        string input;
        while (getline(cin, input))
        {
            System_Clear();
            if (input == "Q")
            {
                return sget("exit;exit;");
            }
            elif (input == "I")
            {
                return sget("introduction;exit;");
            }
            elif (input == "L")
            {
                return sget("load_invent;load;");
            }
            elif (input == "S")
            {
                return sget("load_invent;save;main_page;");
            }
            elif (input == "A")
            {
                return sget("load_invent;save;exit;");
            }
            elif (input == "C")
            {
                return sget("invent_page;main_page;exit;");
            }
            elif (input == "E")
            {
                return sget("level_page;main_page;exit;");
            }
            elif (input == "P")
            {
                return sget("store_page;main_page;exit;");
            }
            elif (input == "F")
            {
                return sget("town_1;main_page;exit;");
            }
            cout << "          Main page" << endc;
            cout << magenta << "> Inventory(C) > Level(E)" << endc;
            cout << green << "> Store(P)" << endc;
            cout << blue << "> Explore(F)" << endc;
            cout << green << "> Load(L)      > Save(S)" << endc;
            cout << red << "> Quit(Q)      > Save & Quit(A)" << endc;
            cout << "> Introduction(I)" << endc;
        }
        return sget("exit;exit;");
    }

    SGET_RET introduction(string arg)
    {
        cout << "    Introduction" << endc;
        cout << "This is a text game(unfinished) by " << blue << "cosf" << reset << ". Players can explore the world in this game." << endc;
        cout << endc;
        cout << red << "> Exit(Q)" << endc;
        string input;
        while (getline(cin, input))
        {
            System_Clear();
            if (input == "Q")
            {
                return sget("main_page;exit;");
            }
            cout << "    Introduction" << endc;
            cout << "This is a text game(unfinished) by " << blue << "cosf" << reset << ". Players can explore the world in this game." << endc;
            cout << endc;
            cout << red << "> Exit(Q)" << endc;
        }
        return sget("exit;exit;");
    }

    SGET_RET load_invent(string arg)
    {
        SGET_RET par = sget(arg);
        if (par.curtsk == "save")
        {
            cout << green << "   Save Game Progress" << endc;
            cout << "Which file do you want to save to?" << endc << green;
            string fin;
            cin >> fin;
            cout << reset;
            invent_cleanup();
            update_level();
            ofstream file(fin);
            file << "comment;saved - " << time(0) << ", load saved;";
            file << "invent;" << invent.size() << ";";
            for (pair<string, vector<ull>> iter : invent)
            {
                file << iter.first << ";";
                for (int i = 0; i < 10; i++)
                {
                    file << iter.second[i] << ";";
                }
            }
            file << "level;" << level << ";" << exp << ";";
            file << "reward;" << lstr << ";";
            file << "maps;";

            // For Explore Maps

            file << "town_1;" << town_1.save();

            //
            return sget(par.curarg + "exit;");
        }
        elif (par.curtsk == "load")
        {
            cout << green << "   Load Game Progress" << endc;
            cout << "Which file do you want to load?" << endc << green;
            string fin;
            cin >> fin;
            cout << reset;
            ifstream file(fin);
            invent.clear();
            invent_names.clear();
            string dat;
            getline(file, dat);
            SGET_RET tgm = sget(dat);
            while (tgm.curtsk.size())
            {
                if (tgm.curtsk == "comment")
                {
                    next(tgm);
                    next(tgm);
                }
                elif (tgm.curtsk == "invent")
                {
                    next(tgm);
                    int nos = stoi(tgm.curtsk);
                    next(tgm);
                    for (int i = 0; i < nos; i++)
                    {
                        string stfn = tgm.curtsk;
                        next(tgm);
                        for (int j = 0; j < 10; j++)
                        {
                            invent_add(stfn, j, stoi(tgm.curtsk));
                            next(tgm);
                        }
                    }
                }
                elif (tgm.curtsk == "level")
                {
                    next(tgm);
                    level = stoi(tgm.curtsk);
                    next(tgm);
                    exp = stoi(tgm.curtsk);
                    next(tgm);
                }
                elif (tgm.curtsk == "reward")
                {
                    next(tgm);
                    lstr = stoi(tgm.curtsk);
                    next(tgm);
                }
                elif (tgm.curtsk == "maps")
                {
                    next(tgm);
                    // For Explore Maps
                    if (tgm.curtsk == "town_1")
                    {
                        tgm = town_1.load(tgm);
                    }
                    //
                }
            }
            invent_cleanup();
            update_level();
            return sget("main_page;exit;");
        }
        return sget("exit;exit;");
    }

    SGET_RET invent_page(string arg)
    {
        invent_cleanup();
        string craft_line = "(Place for crafting)";
        cout << magenta << "    Inventory" << endc;
        cout << endc;
        cout << red << craft_line << endc;
        cout << endc;
        cout << yellow << "|--------------------|------|------|------|------|------|------|------|------|------|------|" << endc;
        cout << yellow << "| Name of Stuff      |";
        for (int i = 0; i < 10; i++)
        {
            lvc[i]();
            cout << " lv." << i << " " << yellow << "|";
        }
        cout << endc;
        for (string in : invent_names)
        {
            cout << yellow << "|--------------------|------|------|------|------|------|------|------|------|------|------|" << endc;
            cout << "| " << left << setw(18) << in << " |";
            for (int i = 0; i < 10; i++)
            {
                lvc[i]();
                cout << " " << left << setw(4) << itos(invent[in][i]) << " " << yellow << "|";
            }
            cout << endc;
        }
        cout << yellow << "|--------------------|------|------|------|------|------|------|------|------|------|------|" << endc;
        cout << endc;
        cout << red << "> Exit(Q)" << endc;
        cout << magenta << "> Craft(C): " << reset << "the form is \"" << magenta << "C" << reset << ";type;" << yellow << "level" << reset << ";number;\", for example, \"" << magenta << "C" << reset << ";wood;" << green << "0" << reset << ";2\"" << endc;
        cout << red << "tips: Make sure you really want to craft it, since it's not undo-able." << endc;
        cout << "The success rates are:" << endc;
        cout << yellow << "|--------|--------|--------|--------|--------|--------|--------|--------|--------|" << endc;
        cout << yellow << "|";
        for (int i = 0; i < 9; i++)
        {
            cout << " " << reset << "lv";
            lvc[i]();
            cout << i << reset << "=>";
            lvc[i + 1]();
            cout << i + 1 << yellow << " |";
        }
        cout << endc;
        cout << yellow << "|";
        for (int i = 0; i < 9; i++)
        {
            lvc[i + 1]();
            cout << " " << scr[i] << " " << yellow << "|";
        }
        cout << endc;
        cout << yellow << "|--------|--------|--------|--------|--------|--------|--------|--------|--------|" << endc;
        cout << endc;
        cout << green << "> Hourly Reward(D): if the last time you get this reward is over 1h, you will get 10 lv.0(1 for lv. 6+, 2 for lv. 9+) coins." << endc;
        string input;
        while (getline(cin, input))
        {
            if (input == "Q")
            {
                return sget(arg);
            }
            elif (input == "D")
            {
                ull now = time(0);
                if (now - lstr >= 3600)
                {
                    lstr = now;
                    if (level < 6)
                    {
                        invent_add("coin", 0, 10);
                    }
                    elif (level < 9)
                    {
                        invent_add("coin", 1, 10);
                    }
                    else
                    {
                        invent_add("coin", 2, 10);
                    }
                }
            }
            else
            {
                SGET_RET intask = sget(input);
                if (intask.curtsk == "C")
                {
                    next(intask);
                    string in = intask.curtsk;
                    next(intask);
                    int lv = stoi(intask.curtsk);
                    next(intask);
                    ull nb = stoi(intask.curtsk);
                    if (invent_names.count(in) && 0 <= lv && lv < 9 && invent[in][lv] >= nb)
                    {
                        ull suc = craft(nb, sucde[lv], sucnu[lv]);
                        ull fld = nb - suc;
                        get_exp(fld * expr[lv]);
                        craft_line = " lv." + itos(lv) + " " + in + " * " + itos(nb) + " ==> lv." + itos(lv + 1) + " " + in + " * " + itos(suc);
                        invent_add(in, lv + 1, suc);
                        invent_purchase(in, lv, nb);
                    }
                }
            }
            System_Clear();
            cout << magenta << "    Inventory" << endc;
            cout << endc;
            cout << red << craft_line << endc;
            cout << endc;
            cout << yellow << "|--------------------|------|------|------|------|------|------|------|------|------|------|" << endc;
            cout << yellow << "| Name of Stuff      |";
            for (int i = 0; i < 10; i++)
            {
                lvc[i]();
                cout << " lv." << i << " " << yellow << "|";
            }
            cout << endc;
            for (string in : invent_names)
            {
                cout << yellow << "|--------------------|------|------|------|------|------|------|------|------|------|------|" << endc;
                cout << "| " << left << setw(18) << in << " |";
                for (int i = 0; i < 10; i++)
                {
                    lvc[i]();
                    cout << " " << left << setw(4) << itos(invent[in][i]) << " " << yellow << "|";
                }
                cout << endc;
            }
            cout << yellow << "|--------------------|------|------|------|------|------|------|------|------|------|------|" << endc;
            cout << endc;
            cout << red << "> Exit(Q)" << endc;
            cout << magenta << "> Craft(C): " << reset << "the form is \"" << magenta << "C" << reset << ";type;" << yellow << "level" << reset << ";number;\", for example, \"" << magenta << "C" << reset << ";wood;" << green << "0" << reset << ";2\"" << endc;
            cout << red << "tips: Make sure you really want to craft it, since it's not undo-able." << endc;
            cout << "The success rates are:" << endc;
            cout << yellow << "|--------|--------|--------|--------|--------|--------|--------|--------|--------|" << endc;
            cout << yellow << "|";
            for (int i = 0; i < 9; i++)
            {
                cout << " " << reset << "lv";
                lvc[i]();
                cout << i << reset << "=>";
                lvc[i + 1]();
                cout << i + 1 << yellow << " |";
            }
            cout << endc;
            cout << yellow << "|";
            for (int i = 0; i < 9; i++)
            {
                lvc[i + 1]();
                cout << " " << scr[i] << " " << yellow << "|";
            }
            cout << endc;
            cout << yellow << "|--------|--------|--------|--------|--------|--------|--------|--------|--------|" << endc;
            cout << endc;
            cout << green << "> Hourly Reward(D): if the last time you get this reward is over 1h, you will get 10 lv.0(1 for lv. 6+, 2 for lv. 9+) coins." << endc;
        }
        return sget(arg);
    }

    SGET_RET level_page(string arg)
    {
        update_level();
        cout << magenta << "    Level" << endc;
        cout << "Currently your level is lv.";
        lvc[level - 1]();
        cout << level << '.' << endc;
        lvc[level - 1]();
        cout << right << setw(15) << exp << reset << " / ";
        lvc[level - 1]();
        cout << left << setw(15) << lne[level] << endc;
        int sw = exp * 31 / lne[level];
        int rt = 31 - sw;
        cout << "[";
        lvc[level - 1]();
        cout << string("*") * sw << reset << string(" ") * rt << "]" << endc;
        cout << endc;
        cout << "> Exit(Q)" << endc;
        string input;
        while (getline(cin, input))
        {
            if (input == "Q")
            {
                return sget(arg);
            }
        }
        return sget(arg);
    }

    SGET_RET store_page(string arg)
    {
        cout << "   Version's Offer" << endc;
        cout << endc;
        cout << green << "> lv.0 wood * 10 (5 * lv.0 coins) (1)" << endc;
        cout << green << "> lv.0 rock * 10 (6 * lv.0 coins) (2)" << endc;
        cout << green << "> lv.1 stone * 1 (3 * lv.1 coins) (3)" << endc;
        cout << green << "> lv.1 plank * 1 (2 * lv.0 coins) (4)" << endc;
        cout << endc;
        cout << "> Exit(Q)" << endc;
        string input;
        while (getline(cin, input))
        {
            if (input == "Q")
            {
                return sget(arg);
            }
            elif (input == "1")
            {
                if (purchase("lv.0 wood * 10", "coin", 0, 5).first != -1)
                {
                    invent_add("wood", 0, 10);
                }
            }
            elif (input == "2")
            {
                if (purchase("lv.0 rock * 10", "coin", 0, 6).first != -1)
                {
                    invent_add("rock", 0, 10);
                }
            }
            elif (input == "3")
            {
                if (purchase("lv.1 stone * 1", "coin", 1, 3).first != -1)
                {
                    invent_add("stone", 1, 1);
                }
            }
            elif (input == "4")
            {
                if (purchase("lv.1 plank * 1", "coin", 1, 2).first != -1)
                {
                    invent_add("plank", 1, 1);
                }
            }
            System_Clear();
            cout << "   Version's Offer" << endc;
            cout << endc;
            cout << green << "> lv.0 wood * 10 (5 * lv.0 coins) (1)" << endc;
            cout << green << "> lv.0 rock * 10 (6 * lv.0 coins) (2)" << endc;
            cout << green << "> lv.1 stone * 1 (3 * lv.1 coins) (3)" << endc;
            cout << green << "> lv.1 plank * 1 (2 * lv.0 coins) (4)" << endc;
            cout << endc;
            cout << "> Exit(Q)" << endc;
        }
        return sget(arg);
    }

    // Game Maps (Explore)

    Town_1 town_1;

    // Game Launching
    GameBoard()
    {
        tst = mt19937(time(0));
        invent_add("coin", 0, 50);
        lvc.push_back(set_green);
        lvc.push_back(set_green);
        lvc.push_back(set_yellow);
        lvc.push_back(set_yellow);
        lvc.push_back(set_blue);
        lvc.push_back(set_magenta);
        lvc.push_back(set_red);
        lvc.push_back(set_cyan);
        lvc.push_back(set_black);
        lvc.push_back(set_white);
    }
    int game_start()
    {
        // load data
        string start_task = "main_page;exit;";
        SGET_RET task = sget(start_task);
        while (task.curtsk.size())
        {
            System_Clear();
            if (task.curtsk == "main_page")
            {
                task = main_page(task.curarg);
            }
            elif (task.curtsk == "exit")
            {
                return 0;
            }
            elif (task.curtsk == "introduction")
            {
                task = introduction(task.curarg);
            }
            elif (task.curtsk == "load_invent")
            {
                task = load_invent(task.curarg);
            }
            elif (task.curtsk == "invent_page")
            {
                task = invent_page(task.curarg);
            }
            elif (task.curtsk == "level_page")
            {
                task = level_page(task.curarg);
            }
            elif (task.curtsk == "store_page")
            {
                task = store_page(task.curarg);
            }
            elif (task.curtsk == "town_1")
            {
                task = town_1(task.curarg);
            }
            else
            {
                task = SGET_RET{};
            }
        }
        return -1;
    }
};

#endif
