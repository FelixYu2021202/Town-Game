As written in that blog, this blog is for putting `Game Maps Implementations (Centratown)`

[Back to `intro.md`](/blog/35/6464e26c426c19a595da2748)

This is the map of `Centratown`:

```txt
Centratown   ::   Map

       (To The North Volcanoes)
                    |
        Northern Woods   -- (To Northern Factories)
                    |                       |
                    |                       |
                  Town   --   Black Smith --
                    |             |
                    |             |
         Ponds -- Plains    (To The Rocks)
           |        |
           |        |
(To The Swamps)  (To The Woods)
```

And the map of the game:

```txt
Town Game   ::   Map

              The North Volcanoes
                 |             |
                 |             |
            Centratown  --  Northern Factories
           |      |  |__________            |
           |      |            |            |
   The Swamps -- The Woods -- The Rocks -- The East Waters
       |            |          |            |
       |            |          |            |
  The Southwest -- The South Lands -- The Southeast
```

The implementation for Centratown is:

```cpp
#include "tg.h"

// Game Maps implementations (Centratown)

extern GameBoard gb;

SGET_RET Town_1::operator()(string arg)
{
    for (int i = 1; i <= 3; i++)
    {
        System_Clear();
        cout << "Travelling to " << green << "town" << reset << string(".") * i << endc;
        Sleep(200);
    }
    System_Clear();
    cout << "You arrived at " << green << "town." << endc;
    Sleep(1000);
    System_Clear();
    cout << green << "       Town" << endc;
    if (MADE_MAP >= 3 && gb.level >= 1)
    {
        cout << green << "         To Northern Woods (U)";
    }
    cout << endc;
    cout << endc;
    cout << "Back to Main Page (L)";
    if (MADE_MAP >= 7 && gb.level >= 2)
    {
        cout << green << "     To Black Smith (R)";
    }
    cout << endc;
    cout << endc;
    cout << yellow << "   > The town carpenter (C)" << endc;
    cout << "   > The town mason (M)" << endc;
    cout << endc;
    if (MADE_MAP >= 2 && gb.level >= 1)
    {
        cout << green << "         To Plains (D)";
    }
    cout << endc;
    string input;
    while (getline(cin, input))
    {
        if (MADE_MAP >= 3 && input == "U" && gb.level >= 1)
        {
            return sget("northern_woods_3;town_1;exit;");
        }
        if (MADE_MAP >= 7 && input == "R" && gb.level >= 2)
        {
            return sget("black_smith_7;town_1;exit;");
        }
        if (MADE_MAP >= 2 && input == "D" && gb.level >= 1)
        {
            return sget("plains_2;town_1;exit;");
        }
        if (input == "L")
        {
            return sget(arg);
        }
        if (input == "C")
        {
            ull now = time(0);
            if (now - carpenter_lv_1 < 30)
            {
                System_Clear();
                cout << yellow << "The carpenter isn't rested! He needs to rest for " << red << "0.5 min" << yellow << "." << endc;
                Sleep(1000);
            }
            else
            {
                System_Clear();
                cout << yellow << "   Carpenter" << endc;
                cout << green << " - 10 * lv.0 wood -> 1 * lv.1 plank + 25 exp (1)" << endc;
                cout << green << " - 10 * lv.0 wood + 2 * lv.0 coin -> 5 * lv.1 wood + 25 exp (2)" << endc;
                cout << yellow << " - 1 * lv.1 plank -> 5 * lv.0 stick + 25 exp (3)" << endc;
                cout << yellow << " - 3 * lv.0 stick + 2 * lv.0 wood -> 1 * lv.1 ladder + 50 exp(4)" << endc;
                if (getline(cin, input))
                {
                    if (input == "1")
                    {
                        pii wood_ret = gb.purchase("Crafting 1 * lv.1 plank (with 25 exp)", "wood", 0, 10);
                        if (wood_ret.first != -1)
                        {
                            gb.invent_add("plank", 1, 1);
                            gb.get_exp(25);
                            cout << "Crafted." << endc;
                            carpenter_lv_1 = now;
                            Sleep(800);
                        }
                    }
                    elif (input == "2")
                    {
                        pii wood_ret = gb.purchase("Crafting 5 * lv.1 wood (with 25 exp)", "wood", 0, 10);
                        if (wood_ret.first != -1)
                        {
                            pii coin_ret = gb.purchase("Crafting 5 * lv.1 wood (with 25 exp)", "coin", 0, 2);
                            if (coin_ret.first != -1)
                            {
                                gb.invent_add("wood", 1, 5);
                                gb.get_exp(25);
                                cout << "Crafted." << endc;
                                carpenter_lv_1 = now;
                                Sleep(800);
                            }
                            else
                            {
                                gb.invent_add("wood", wood_ret.first, wood_ret.second);
                            }
                        }
                    }
                    elif (input == "3")
                    {
                        pii plank_ret = gb.purchase("Crafting 5 * lv.0 stick (with 25 exp)", "plank", 1, 1);
                        if (plank_ret.first != -1)
                        {
                            gb.invent_add("stick", 0, 5);
                            gb.get_exp(25);
                            cout << "Crafted." << endc;
                            carpenter_lv_1 = now;
                            Sleep(800);
                        }
                    }
                    elif (input == "4")
                    {
                        pii wood_ret = gb.purchase("Crafting 1 * lv.1 ladder (with 25 exp)", "wood", 0, 2);
                        if (wood_ret.first != -1)
                        {
                            pii coin_ret = gb.purchase("Crafting 1 * lv.1 ladder (with 25 exp)", "stick", 0, 3);
                            if (coin_ret.first != -1)
                            {
                                gb.invent_add("ladder", 1, 1);
                                gb.get_exp(50);
                                cout << "Crafted." << endc;
                                carpenter_lv_1 = now;
                                Sleep(800);
                            }
                            else
                            {
                                gb.invent_add("wood", wood_ret.first, wood_ret.second);
                            }
                        }
                    }
                }
            }
        }
        if (input == "M")
        {
            ull now = time(0);
            if (now - mason_lv_1 < 60)
            {
                System_Clear();
                cout << "The mason isn't rested! He needs to rest for " << red << "1 min" << reset << "." << endc;
                Sleep(1000);
            }
            else
            {
                System_Clear();
                cout << "   Mason" << endc;
                cout << green << " - 10 * lv.0 rock -> 1 * lv.1 stone + 25 exp (1)" << endc;
                cout << green << " - 10 * lv.0 rock + 1 * lv.0 coin -> 5 * lv.1 rock + 25 exp (2)" << endc;
                cout << yellow << " - 1 * lv.1 stone + 2 * lv.0 stick -> 1 * lv.1 hammer + 50 exp (3)" << endc;
                cout << yellow << " - 2 * lv.1 stone + 2 * lv.0 stick -> 1 * lv.1 axe + 75 exp(4)" << endc;
                if (getline(cin, input))
                {
                    if (input == "1")
                    {
                        pii rock_ret = gb.purchase("Crafting 1 * lv.1 stone (with 25 exp)", "rock", 0, 10);
                        if (rock_ret.first != -1)
                        {
                            gb.invent_add("stone", 1, 1);
                            gb.get_exp(25);
                            cout << "Crafted." << endc;
                            mason_lv_1 = now;
                            Sleep(800);
                        }
                    }
                    elif (input == "2")
                    {
                        pii rock_ret = gb.purchase("Crafting 5 * lv.1 rock (with 25 exp)", "rock", 0, 10);
                        if (rock_ret.first != -1)
                        {
                            pii coin_ret = gb.purchase("Crafting 5 * lv.1 rock (with 25 exp)", "coin", 0, 1);
                            if (coin_ret.first != -1)
                            {
                                gb.invent_add("rock", 1, 5);
                                gb.get_exp(25);
                                cout << "Crafted." << endc;
                                mason_lv_1 = now;
                                Sleep(800);
                            }
                            else
                            {
                                gb.invent_add("rock", rock_ret.first, rock_ret.second);
                            }
                        }
                    }
                    elif (input == "3")
                    {
                        pii stone_ret = gb.purchase("Crafting 1 * lv.1 hammer (with 50 exp)", "stone", 1, 1);
                        if (stone_ret.first != -1)
                        {
                            pii stick_ret = gb.purchase("Crafting 1 * lv.1 hammer (with 50 exp)", "stick", 0, 2);
                            if (stick_ret.first != -1)
                            {
                                gb.invent_add("hammer", 1, 1);
                                gb.get_exp(50);
                                cout << "Crafted." << endc;
                                mason_lv_1 = now;
                                Sleep(800);
                            }
                            else
                            {
                                gb.invent_add("stick", stick_ret.first, stick_ret.second);
                            }
                        }
                    }
                    elif (input == "4")
                    {
                        pii stone_ret = gb.purchase("Crafting 1 * lv.1 axe (with 75 exp)", "stone", 1, 2);
                        if (stone_ret.first != -1)
                        {
                            pii stick_ret = gb.purchase("Crafting 1 * lv.1 plank (with 25 exp)", "stick", 0, 2);
                            if (stick_ret.first != -1)
                            {
                                gb.invent_add("axe", 1, 1);
                                gb.get_exp(75);
                                cout << "Crafted." << endc;
                                mason_lv_1 = now;
                                Sleep(800);
                            }
                            else
                            {
                                gb.invent_add("stick", stone_ret.first, stone_ret.second);
                            }
                        }
                    }
                }
            }
        }
        System_Clear();
        cout << green << "       Town" << endc;
        if (MADE_MAP >= 3 && gb.level >= 1)
        {
            cout << green << "         To Northern Woods (U)";
        }
        cout << endc;
        cout << endc;
        cout << "Back to Main Page (L)";
        if (MADE_MAP >= 7 && gb.level >= 2)
        {
            cout << green << "     To Black Smith (R)";
        }
        cout << endc;
        cout << endc;
        cout << yellow << "   > The town carpenter (C)" << endc;
        cout << "   > The town mason (M)" << endc;
        cout << endc;
        if (MADE_MAP >= 2 && gb.level >= 1)
        {
            cout << green << "         To Plains (D)";
        }
        cout << endc;
    }
    return sget(arg);
}

string Town_1::save()
{
    return "mp01_cpt;" + to_string(carpenter_lv_1) + ";mp01_msn;" + to_string(mason_lv_1) + ";";
}

SGET_RET Town_1::load(SGET_RET tgm)
{
    next(tgm);
    while (tgm.curtsk.substr(0, 4) == "mp01")
    {
        if (tgm.curtsk == "mp01_cpt")
        {
            next(tgm);
            carpenter_lv_1 = stoi(tgm.curtsk);
            next(tgm);
        }
        else if (tgm.curtsk == "mp01_msn")
        {
            next(tgm);
            mason_lv_1 = stoi(tgm.curtsk);
            next(tgm);
        }
    }
    return tgm;
}

```
