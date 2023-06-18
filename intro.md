## Town Game -- Intro

This is a text game(unfinished) by cosf. Players can explore the world in this game.

You can see this text in the `Introduction` page.

## Source Code

The code is too long, so it is separated into several files and parts:

- `main.cpp`, which is given below.
- `tg.h`

  - ```cpp
    #ifndef TG_LIB
    #define TG_LIB "TG_LIB;Town Game by cosf;header-version;v0.6.2"
    ```

  - [Utilities](/blog/35/64731bf78710066d92d29796 "tg")
  - [Map Declaration](/blog/35/64731bf78710066d92d29796 "tg")
  - Game Board, which is given below.

  - ```cpp
    #endif
    ```

- `centratown.cpp`

  - [Game Map Implementations](/blog/35/646cb7b28710066d92d00a77#1684846514151 "centratown.cpp")
- Several other maps will be added soon.

If you are unable to compile, you can try the command below. Remember to put these three files in the same folder!

```powershell
g++ -g main.cpp -g centratown.cpp -o tg.exe -std=c++17
```

**Or** if you are using dev-c++ or other IDE with project features, you can put all three files in a project and use the built-in project compiler to compile it.

The recommended ISO standard is `C++ 17(ISO/IEC 14882:2017)`.

## Update log

### v0.6.2 (23.6.18)

- Updated map.
- Added bonus for new archives.

### v0.6.1 (23.6.3)

- Updated purchase system.

### v0.6.0 (23.5.29)

- Separated files of the game system.

### v0.5.0 (23.5.28)

- Updated the way of running the game.

### v0.4.0 (23.5.24)

- Added one map.
- Fixed Page.

### v0.3.0 (23.5.23)

- Added store.
  Hopefully the next upgrade will be the maps.
  The map codes may be too long, so you can download it in other blogs maybe.

### v0.2.2 (23.5.22)

- Added hourly reward.
- Added more information.

### v0.2.1 (23.5.21)

- Changed level formula.
- Salvage some of the stuff as exp when crafting failed.

### v0.2.0 (23.5.20)

- Added level.
- Update logs will no longer be put in game.
  See hfoj blog (here) for update logs.

### v0.1.1 (23.5.19)

- Added crafting.

### v0.1.0 (23.5.18)

- Added inventory page.

### v0.0.4 (23.5.17)

- Updated inventory system.

### v0.0.3 (23.5.16)

- Added file(progress) system.
  Now players can save there progress through the main page.
  Yet this feature isn't tested on big data.

### v0.0.2 (23.5.15)

- Updated update log.

### v0.0.1 (23.5.15)

- Added update log.

### v0.0.0 (23.5.15)

- Added main page.
- Added quit.
- First update.

## Code Implementations

The `main.cpp` code is

```cpp
// Game by cosf
// v0.6.2
// build 2023.6.18
// unf
// for more details please go to http://ac.hfoj.net/blog/35/6464e26c426c19a595da2748#1684333164277

// Utilities

#include "tg.h"

// Game Board

GameBoard gb;

// Game Start
int main()
{
    if (gb.game_start())
    {
        cout << "Game did not exit normally." << endl;
        return -1;
    }
    return 0;
}

```

The Game Board code is (note that it is in `tg.h`):

```cpp
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

    pii purchase_light(string sn, string in, int sc, int c)
    {
        vector<int> able;
        vector<ull> nd(10, 0);
        int c0 = c;
        for (int i = sc; i; i--)
        {
            c0 *= cvsld[i];
        }
        for (int i = 0; i <= sc; i++)
        {
            if (check_purchase(in, i, c0))
            {
                able.push_back(i);
                nd[i] = c0;
            }
            c0 /= cvsld[i + 1];
        }
        for (int i = sc + 1; i < 10; i++)
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
            cout << "   Purchase" << endl;
            cout << endl;
            cout << "You don't have enough to buy it!" << endl;
            cout << "Enter to be back." << endl;
            string input;
            getline(cin, input);
            return {-1, -1};
        }
        int slen = max(8UL, 2 + in.length());
        cout << "   Purchase" << endl;
        cout << sn << endl;
        cout << endl;
        cout << "These are the options you can choose(only one):" << endl;
        cout << "|" << string("-") * slen << "|" << string("-------|") * able.size() << endl;
        cout << "| " << left << setw(slen - 1) << "level"
             << "|";
        for (int i : able)
        {
            cout << "  " << left << setw(4) << i << " |";
        }
        cout << endl;
        cout << "|" << string("-") * slen << "|" << string("-------|") * able.size() << endl;
        cout << "| " << left << setw(slen - 1) << in
             << "|";
        for (int i : able)
        {
            cout << "  " << left << setw(4) << itos(invent[in][i]) << " |";
        }
        cout << endl;
        cout << "|" << string("-") * slen << "|" << string("-------|") * able.size() << endl;
        cout << "|" << string(" ") * slen << "|";
        for (int i : able)
        {
            cout << " -" << left << setw(4) << itos(nd[i]) << " |";
        }
        cout << endl;
        cout << "|" << string("-") * slen << "|" << string("-------|") * able.size() << endl;
        cout << "| " << left << setw(slen - 1) << "result"
             << "|";
        for (int i : able)
        {
            cout << "  " << left << setw(4) << itos(invent[in][i] - nd[i]) << " |";
        }
        cout << endl;
        cout << "|" << string("-") * slen << "|" << string("-------|") * able.size() << endl;
        cout << "Please enter the choice(0 ~ 9) or abort(any other)." << endl;
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
        cout << "          Main page" << endl;
        cout << "> Inventory(C) > Level(E)" << endl;
        cout << "> Store(P)" << endl;
        cout << "> Explore(F)" << endl;
        cout << "> Load(L)      > Save(S)" << endl;
        cout << "> Quit(Q)      > Save & Quit(A)" << endl;
        cout << "> Introduction(I)" << endl;
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
            cout << "          Main page" << endl;
            cout << "> Inventory(C) > Level(E)" << endl;
            cout << "> Store(P)" << endl;
            cout << "> Explore(F)" << endl;
            cout << "> Load(L)      > Save(S)" << endl;
            cout << "> Quit(Q)      > Save & Quit(A)" << endl;
            cout << "> Introduction(I)" << endl;
        }
        return sget("exit;exit;");
    }

    SGET_RET introduction(string arg)
    {
        cout << "    Introduction" << endl;
        cout << "This is a text game(unfinished) by cosf. Players can explore the world in this game." << endl;
        cout << endl;
        cout << "> Exit(Q)" << endl;
        string input;
        while (getline(cin, input))
        {
            System_Clear();
            if (input == "Q")
            {
                return sget("main_page;exit;");
            }
            cout << "    Update Log" << endl;
            cout << "This is a text game(unfinished) by cosf. Players can explore the world in this game." << endl;
            cout << endl;
            cout << "> Exit(Q)" << endl;
        }
        return sget("exit;exit;");
    }

    SGET_RET load_invent(string arg)
    {
        SGET_RET par = sget(arg);
        if (par.curtsk == "save")
        {
            cout << "   Save Game Progress" << endl;
            cout << "Which file do you want to save to?" << endl;
            string fin;
            cin >> fin;
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
            cout << "   Load Game Progress" << endl;
            cout << "Which file do you want to load?" << endl;
            string fin;
            cin >> fin;
            ifstream file(fin);
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
        cout << "    Inventory" << endl;
        cout << endl;
        cout << craft_line << endl;
        cout << endl;
        cout << "|--------------------|------|------|------|------|------|------|------|------|------|------|" << endl;
        cout << "| Name of Stuff      | lv.0 | lv.1 | lv.2 | lv.3 | lv.4 | lv.5 | lv.6 | lv.7 | lv.8 | lv.9 |" << endl;
        for (string in : invent_names)
        {
            cout << "|--------------------|------|------|------|------|------|------|------|------|------|------|" << endl;
            cout << "| " << left << setw(18) << in << " |";
            for (int i = 0; i < 10; i++)
            {
                cout << " " << left << setw(4) << itos(invent[in][i]) << " |";
            }
            cout << endl;
        }
        cout << "|--------------------|------|------|------|------|------|------|------|------|------|------|" << endl;
        cout << endl;
        cout << "> Exit(Q)" << endl;
        cout << "> Craft(C): the form is \"C;type;level;number;\", for example, \"C;wood;0;2\"" << endl;
        cout << "tips: Make sure you really want to craft it, since it's not undo-able." << endl;
        cout << "The success rates are:" << endl;
        cout << "|--------|--------|--------|--------|--------|--------|--------|--------|--------|" << endl;
        cout << "| lv0=>1 | lv1=>2 | lv2=>3 | lv3=>4 | lv4=>5 | lv5=>6 | lv6=>7 | lv7=>8 | lv8=>9 |" << endl;
        cout << "| 25%    | 5%     | 3%     | 2%     | 1%     | 0.4%   | 0.1%   | 0.025% | 0.005% |" << endl;
        cout << "|--------|--------|--------|--------|--------|--------|--------|--------|--------|" << endl;
        cout << endl;
        cout << "> Hourly Reward(D): if the last time you get this reward is over 1h, you will get 10 lv.0(1 for lv. 6+, 2 for lv. 9+) coins." << endl;
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
                if (now - lstr >= 3600000)
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
            cout << "    Inventory" << endl;
            cout << endl;
            cout << craft_line << endl;
            cout << endl;
            cout << "|--------------------|------|------|------|------|------|------|------|------|------|------|" << endl;
            cout << "| Name of Stuff      | lv.0 | lv.1 | lv.2 | lv.3 | lv.4 | lv.5 | lv.6 | lv.7 | lv.8 | lv.9 |" << endl;
            for (string in : invent_names)
            {
                cout << "|--------------------|------|------|------|------|------|------|------|------|------|------|" << endl;
                cout << "| " << left << setw(18) << in << " |";
                for (int i = 0; i < 10; i++)
                {
                    cout << " " << left << setw(4) << itos(invent[in][i]) << " |";
                }
                cout << endl;
            }
            cout << "|--------------------|------|------|------|------|------|------|------|------|------|------|" << endl;
            cout << endl;
            cout << "> Exit(Q)" << endl;
            cout << "> Craft(C): the form is \"C;type;level;number;\", for example, \"C;wood;0;2\"" << endl;
            cout << "tips: Make sure you really want to craft it, since it's not undo-able." << endl;
            cout << "The success rates are:" << endl;
            cout << "|--------|--------|--------|--------|--------|--------|--------|--------|--------|" << endl;
            cout << "| lv0=>1 | lv1=>2 | lv2=>3 | lv3=>4 | lv4=>5 | lv5=>6 | lv6=>7 | lv7=>8 | lv8=>9 |" << endl;
            cout << "| 25%    | 5%     | 3%     | 2%     | 1%     | 0.4%   | 0.1%   | 0.025% | 0.005% |" << endl;
            cout << "|--------|--------|--------|--------|--------|--------|--------|--------|--------|" << endl;
            cout << endl;
            cout << "> Hourly Reward(D): if the last time you get this reward is over 1h, you will get 10 lv.0(1 for lv. 6+, 2 for lv. 9+) coins." << endl;
        }
        return sget(arg);
    }

    SGET_RET level_page(string arg)
    {
        update_level();
        cout << "    Level" << endl;
        cout << "Currently your level is lv." << level << '.' << endl;
        cout << right << setw(15) << exp << " / " << left << setw(15) << lne[level] << endl;
        int sw = exp * 31 / lne[level];
        int rt = 31 - sw;
        cout << "["
             << string("*") * sw << string(".") * rt << "]" << endl;
        cout << endl;
        cout << "> Exit(Q)" << endl;
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
        cout << "   Version's Offer" << endl;
        cout << endl;
        cout << "> lv.0 wood * 10 (5 * lv.0 coins) (1)" << endl;
        cout << "> lv.0 rock * 10 (6 * lv.0 coins) (2)" << endl;
        cout << "> lv.1 wood * 5 (15 * lv.0 coins) (3)" << endl;
        cout << endl;
        cout << "> Exit(Q)" << endl;
        string input;
        while (getline(cin, input))
        {
            if (input == "Q")
            {
                return sget(arg);
            }
            elif (input == "1")
            {
                if (purchase_light("lv.0 wood * 10", "coin", 0, 5).first != -1)
                {
                    invent_add("wood", 0, 10);
                }
            }
            elif (input == "2")
            {
                if (purchase_light("lv.0 rock * 10", "coin", 0, 6).first != -1)
                {
                    invent_add("rock", 0, 10);
                }
            }
            elif (input == "3")
            {
                if (purchase_light("lv.1 wood * 5", "coin", 0, 10).first != -1)
                {
                    invent_add("wood", 1, 5);
                }
            }
            System_Clear();
            cout << "   Version's Offer" << endl;
            cout << endl;
            cout << "> lv.0 wood * 10 (5 * lv.0 coins) (1)" << endl;
            cout << "> lv.0 rock * 10 (6 * lv.0 coins) (2)" << endl;
            cout << "> lv.1 wood * 5 (15 * lv.0 coins) (3)" << endl;
            cout << endl;
            cout << "> Exit(Q)" << endl;
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
```
