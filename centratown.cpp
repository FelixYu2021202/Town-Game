#include "tg.h"

// Game Maps implementations (Centratown)

extern GameBoard gb;

// Town

SGET_RET Town_1::operator()(string arg)
{
    for (int i = 1; i <= 3; i++)
    {
        System_Clear();
        cout << "Travelling to " << green << "town" << reset << string(".") * i << endc;
        Sleep(200);
    }
    System_Clear();
    cout << "You arrived at " << green << "town" << reset << "." << endc;
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
    cout << green << "   > The town merchant (P)" << endc;
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
            return sget("main_page;town_1;exit;");
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
                cout << yellow << " - 3 * lv.0 stick + 2 * lv.0 wood -> 1 * lv.1 ladder + 50 exp (4)" << endc;
                cout << blue << " - 2 * lv.0 stick + 2 * lv.0 wood -> 1 * lv.1 shovel + 50 exp (5)" << endc;
                if (getline(cin, input))
                {
                    if (input == "1")
                    {
                        now = time(0);
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
                        now = time(0);
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
                        now = time(0);
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
                        now = time(0);
                        pii wood_ret = gb.purchase("Crafting 1 * lv.1 ladder (with 50 exp)", "wood", 0, 2);
                        if (wood_ret.first != -1)
                        {
                            pii stick_ret = gb.purchase("Crafting 1 * lv.1 ladder (with 50 exp)", "stick", 0, 3);
                            if (stick_ret.first != -1)
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
                    elif (input == "5")
                    {
                        now = time(0);
                        pii wood_ret = gb.purchase("Crafting 1 * lv.1 shovel (with 50 exp)", "wood", 0, 2);
                        if (wood_ret.first != -1)
                        {
                            pii stick_ret = gb.purchase("Crafting 1 * lv.1 shovel (with 50 exp)", "stick", 0, 2);
                            if (stick_ret.first != -1)
                            {
                                gb.invent_add("shovel", 1, 1);
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
                        now = time(0);
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
                        now = time(0);
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
                        now = time(0);
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
                        now = time(0);
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
        if (input == "P")
        {
            ull now = time(0);
            if (now - merchant_lv_1 < 75)
            {
                System_Clear();
                cout << "The merchant isn't rested! He needs to rest for " << red << "1.25 min" << reset << "." << endc;
                Sleep(1000);
            }
            else
            {
                System_Clear();
                cout << green << "    Merchant" << endc;
                cout << green << " - 5 * lv.0 coin -> 3 * lv.1 wood + 25 exp (1)" << endc;
                cout << green << " - 6 * lv.0 coin -> 3 * lv.1 rock + 25 exp (2)" << endc;
                cout << yellow << " - 10 * lv.0 wood -> 5 * lv.0 coin + 25 exp (3)" << endc;
                cout << yellow << " - 10 * lv.0 rock -> 6 * lv.0 coin + 25 exp (4)" << endc;
                cout << blue << " - 10 * lv.0 coin -> 3 * lv.1 coin + 50 exp (5)" << endc;
                if (getline(cin, input))
                {
                    if (input == "1")
                    {
                        now = time(0);
                        pii coin_ret = gb.purchase("Crafting 3 * lv.1 wood (with 25 exp)", "coin", 0, 5);
                        if (coin_ret.first != -1)
                        {
                            gb.invent_add("wood", 1, 3);
                            gb.get_exp(25);
                            cout << "Crafted." << endc;
                            merchant_lv_1 = now;
                            Sleep(800);
                        }
                    }
                    elif (input == "2")
                    {
                        now = time(0);
                        pii coin_ret = gb.purchase("Crafting 3 * lv.1 rock (with 25 exp)", "coin", 0, 6);
                        if (coin_ret.first != -1)
                        {
                            gb.invent_add("rock", 1, 3);
                            gb.get_exp(25);
                            cout << "Crafted." << endc;
                            merchant_lv_1 = now;
                        }
                    }
                    elif (input == "3")
                    {
                        now = time(0);
                        pii wood_ret = gb.purchase("Crafting 5 * lv.0 coin (with 25 exp)", "wood", 0, 10);
                        if (wood_ret.first != -1)
                        {
                            gb.invent_add("coin", 0, 5);
                            gb.get_exp(25);
                            cout << "Crafted." << endc;
                            merchant_lv_1 = now;
                        }
                    }
                    elif (input == "4")
                    {
                        now = time(0);
                        pii rock_ret = gb.purchase("Crafting 6 * lv.0 coin (with 25 exp)", "rock", 0, 10);
                        if (rock_ret.first != -1)
                        {
                            gb.invent_add("coin", 0, 6);
                            gb.get_exp(25);
                            cout << "Crafted." << endc;
                            merchant_lv_1 = now;
                        }
                    }
                    elif (input == "5")
                    {
                        now = time(0);
                        pii coin_ret = gb.purchase("Crafting 3 * lv.1 coin (with 50 exp)", "coin", 0, 10);
                        if (coin_ret.first != -1)
                        {
                            gb.invent_add("coin", 1, 3);
                            gb.get_exp(50);
                            cout << "Crafted." << endc;
                            merchant_lv_1 = now;
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
        cout << green << "   > The town merchant (P)" << endc;
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
    return "mp01_cpt;" + to_string(carpenter_lv_1) + ";mp01_msn;" + to_string(mason_lv_1) + ";mp01_mct;" + to_string(merchant_lv_1) + ";";
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
        if (tgm.curtsk == "mp01_msn")
        {
            next(tgm);
            mason_lv_1 = stoi(tgm.curtsk);
            next(tgm);
        }
        if (tgm.curtsk == "mp01_mct")
        {
            next(tgm);
            merchant_lv_1 = stoi(tgm.curtsk);
            next(tgm);
        }
    }
    return tgm;
}

// Plains

SGET_RET Plains_2::operator()(string arg)
{
    for (int i = 1; i <= 3; i++)
    {
        System_Clear();
        cout << "Travelling to " << green << "plains" << reset << string(".") * i << endc;
        Sleep(200);
    }
    System_Clear();
    cout << "You arrived at " << green << "plains" << reset << "." << endc;
    Sleep(1000);
    System_Clear();
    cout << green << "       Plains" << endc;
    if (MADE_MAP >= 1 && gb.level >= 1)
    {
        cout << green << "         To Town (U)";
    }
    cout << endc;
    cout << endc;
    if (MADE_MAP >= 4 && gb.level >= 2 && explore_stage >= 9)
    {
        cout << green << "To Ponds (L)";
    }
    cout << endc;
    cout << endc;
    gb.lvc[abs(explore_stage)]();
    cout << "   > Explore (F)" << endc;
    if (explore_stage >= 1)
    {
        cout << yellow << "   > Craft House (C)" << endc;
    }
    if (explore_stage >= 7)
    {
        cout << "   > Mine (M)" << endc;
    }
    cout << endc;
    if (MADE_MAP >= 5 && gb.level >= 2 && explore_stage >= 8)
    {
        cout << green << "         To Woods (D)";
    }
    cout << endc;
    string input;
    while (getline(cin, input))
    {
        if (MADE_MAP >= 1 && gb.level >= 1 && input == "U")
        {
            return sget("town_1;plains_2;exit;");
        }
        if (MADE_MAP >= 4 && gb.level >= 2 && input == "L" && explore_stage >= 9)
        {
            return sget("ponds_4;plains_2;exit;");
        }
        if (MADE_MAP >= 5 && gb.level >= 2 && input == "D" && explore_stage >= 8)
        {
            return sget("woods_5;plains_2;exit;");
        }
        if (input == "F")
        {
            if (explore_stage >= 9)
            {
                System_Clear();
                cout << green << "Congratulations! You explorered every corner of this map!" << endc;
                Sleep(2500);
            }
            else
            {
                ull now = time(0);
                if (now - explore_lv_1 <= 90)
                {
                    System_Clear();
                    gb.lvc[abs(explore_stage)]();
                    cout << "You cannot explore so often! The lap should be at least " << red << "1.5 min";
                    gb.lvc[abs(explore_stage)]();
                    cout << "." << endc;
                    Sleep(1000);
                }
                else
                {
                    System_Clear();
                    cout << explore_message[++explore_stage] << endc;
                    cout << endc;
                    gb.lvc[explore_stage]();
                    if (explore_stage == 0)
                    {
                        cout << "You received 10 exp." << endc;
                        gb.get_exp(10);
                    }
                    else if (explore_stage == 1)
                    {
                        cout << "Craft House unlocked. You received 15 exp." << endc;
                        gb.get_exp(15);
                    }
                    else if (explore_stage == 2)
                    {
                        cout << "Unlocked some recipes. You received 10 exp." << endc;
                        gb.get_exp(10);
                    }
                    else if (explore_stage == 3)
                    {
                        cout << "Unlocked another recipe. You received 10 exp." << endc;
                        gb.get_exp(10);
                    }
                    else if (explore_stage == 4)
                    {
                        cout << "You received 25 exp." << endc;
                        gb.get_exp(25);
                    }
                    else if (explore_stage == 5)
                    {
                        cout << "Unlocked a recipe. You received 20 exp." << endc;
                        gb.get_exp(20);
                    }
                    else if (explore_stage == 6)
                    {
                        cout << "You received 20 exp." << endc;
                        gb.get_exp(20);
                    }
                    else if (explore_stage == 7)
                    {
                        cout << "Unlocked a recipe and a place. You received 10 exp." << endc;
                        gb.get_exp(10);
                    }
                    else if (explore_stage >= 8)
                    {
                        cout << "Unlocked a map. You received 15 exp." << endc;
                        gb.get_exp(15);
                    }
                    explore_lv_1 = now;
                    Sleep(5000);
                }
            }
        }
        if (input == "C" && explore_stage >= 1)
        {
            ull now = time(0);
            if (now - craft_house_lv_1 < 15)
            {
                System_Clear();
                cout << yellow << "You cannot craft so often! The lap should be at least " << red << "0.25 min" << yellow << "." << endc;
                Sleep(1000);
            }
            else
            {
                System_Clear();
                cout << yellow << "   Craft House" << endc;
                cout << green << " - 15 * lv.0 wood -> 5 * lv.0 plank + 25 exp (1)" << endc;
                if (explore_stage >= 2)
                {
                    cout << green << " - 15 * lv.0 stick -> 1 * lv.1 rope + 50 exp (2)" << endc;
                }
                if (explore_stage >= 3)
                {
                    cout << yellow << " - 1 * lv.1 plank + 2 * lv.0 stick -> 1 * lv.1 paddle + 25 exp (3)" << endc;
                    cout << yellow << " - 2 * lv.1 paddle + 5 * lv.1 plank + 2 * lv.1 rope -> 1 * lv.2 boat + 50 exp (4)" << endc;
                }
                if (explore_stage >= 5)
                {
                    cout << blue << " - 2 * lv.0 plank -> 1 * lv.0 shield + 10 exp (5)" << endc;
                    cout << magenta << " - 2 * lv.0 stick + 1 * lv.1 stone -> 1 * lv.1 sword + 20 exp (6)" << endc;
                }
                if (explore_stage >= 7)
                {
                    cout << red << " - 2 * lv.0 stick + 1 * lv.1 stone -> 1 * lv.1 pickaxe + 20 exp (7)" << endc;
                }
                if (getline(cin, input))
                {
                    if (input == "1")
                    {
                        now = time(0);
                        pii wood_ret = gb.purchase("Crafting 5 * lv.0 plank (with 25 exp)", "wood", 0, 15);
                        if (wood_ret.first != -1)
                        {
                            gb.invent_add("plank", 0, 5);
                            gb.get_exp(25);
                            cout << "Crafted." << endc;
                            craft_house_lv_1 = now;
                            Sleep(800);
                        }
                    }
                    elif (input == "2" && explore_stage >= 2)
                    {
                        now = time(0);
                        pii stick_ret = gb.purchase("Crafting 1 * lv.1 rope (with 50 exp)", "stick", 0, 15);
                        if (stick_ret.first != -1)
                        {
                            gb.invent_add("rope", 1, 1);
                            gb.get_exp(50);
                            cout << "Crafted." << endc;
                            craft_house_lv_1 = now;
                            Sleep(800);
                        }
                    }
                    elif (input == "3" && explore_stage >= 3)
                    {
                        now = time(0);
                        pii plank_ret = gb.purchase("Crafting 1 * lv.1 paddle (with 25 exp)", "plank", 1, 1);
                        if (plank_ret.first != -1)
                        {
                            pii stick_ret = gb.purchase("Crafting 1 * lv.1 paddle (with 25 exp)", "stick", 0, 2);
                            if (stick_ret.first != -1)
                            {
                                gb.invent_add("paddle", 1, 1);
                                gb.get_exp(25);
                                cout << "Crafted." << endc;
                                craft_house_lv_1 = now;
                                Sleep(800);
                            }
                            else
                            {
                                gb.invent_add("plank", plank_ret.first, plank_ret.second);
                            }
                        }
                    }
                    elif (input == "4" && explore_stage >= 3)
                    {
                        now = time(0);
                        pii paddle_ret = gb.purchase("Crafting 1 * lv.2 boat (with 50 exp)", "paddle", 1, 2);
                        if (paddle_ret.first != -1)
                        {
                            pii plank_ret = gb.purchase("Crafting 1 * lv.2 boat (with 50 exp)", "plank", 1, 5);
                            if (plank_ret.first != -1)
                            {
                                pii rope_ret = gb.purchase("Crafting 1 * lv.2 boat (with 50 exp)", "rope", 1, 2);
                                if (rope_ret.first != -1)
                                {
                                    gb.invent_add("boat", 2, 1);
                                    gb.get_exp(50);
                                    cout << "Crafted." << endc;
                                    craft_house_lv_1 = now;
                                    Sleep(800);
                                }
                                else
                                {
                                    gb.invent_add("plank", plank_ret.first, plank_ret.second);
                                    gb.invent_add("paddle", paddle_ret.first, paddle_ret.second);
                                }
                            }
                            else
                            {
                                gb.invent_add("paddle", paddle_ret.first, paddle_ret.second);
                            }
                        }
                    }
                    elif (input == "5" && explore_stage >= 5)
                    {
                        now = time(0);
                        pii plank_ret = gb.purchase("Crafting 1 * lv.0 shield (with 10 exp)", "plank", 0, 2);
                        if (plank_ret.first != -1)
                        {
                            gb.invent_add("shield", 0, 1);
                            gb.get_exp(10);
                            cout << "Crafted." << endc;
                            craft_house_lv_1 = now;
                            Sleep(800);
                        }
                    }
                    elif (input == "6" && explore_stage >= 5)
                    {
                        now = time(0);
                        pii stick_ret = gb.purchase("Crafting 1 * lv.1 sword (with 20 exp)", "stick", 0, 2);
                        if (stick_ret.first != -1)
                        {
                            pii stone_ret = gb.purchase("Crafting 1 * lv.1 sword (with 20 exp)", "stone", 1, 1);
                            if (stone_ret.first != -1)
                            {
                                gb.invent_add("sword", 1, 1);
                                gb.get_exp(20);
                                cout << "Crafted." << endc;
                                craft_house_lv_1 = now;
                                Sleep(800);
                            }
                            else
                            {
                                gb.invent_add("stick", stick_ret.first, stick_ret.second);
                            }
                        }
                    }
                    elif (input == "7" && explore_stage >= 7)
                    {
                        now = time(0);
                        pii stick_ret = gb.purchase("Crafting 1 * lv.1 pickaxe (with 20 exp)", "stick", 0, 2);
                        if (stick_ret.first != -1)
                        {
                            pii stone_ret = gb.purchase("Crafting 1 * lv.1 pickaxe (with 20 exp)", "stone", 1, 1);
                            if (stone_ret.first != -1)
                            {
                                gb.invent_add("pickaxe", 1, 1);
                                gb.get_exp(20);
                                cout << "Crafted." << endc;
                                craft_house_lv_1 = now;
                                Sleep(800);
                            }
                            else
                            {
                                gb.invent_add("stick", stick_ret.first, stick_ret.second);
                            }
                        }
                    }
                }
            }
        }
        if (input == "M" && explore_stage >= 7)
        {
            ull now = time(0);
            if (now - mining_lv_1 < 60)
            {
                System_Clear();
                cout << "You cannot mine so often! The lap should be at least " << red << "1 min" << reset << "." << endc;
                Sleep(1000);
            }
            else
            {
                System_Clear();
                cout << "   Mine" << endc;
                // 18% rock, 2% ferrum
                int sd = gb.tst() % 50;
                if (sd < 1) // ferrum
                {
                    cout << endc << "You found a ferrum ore! 1 * lv.1 pickaxe to mine it." << endc;
                    pii ret = gb.consume("", "pickaxe", 1, 5, 4, 35, 36);
                    if (ret.first != -1)
                    {
                        cout << green << "You get it (1 * lv.1 ferrum)!" << endc << endc;
                        gb.invent_add("ferrum", 1, 1);
                        if (ret.second)
                        {
                            cout << red << "Your pickaxe is broken." << endc;
                        }
                    }
                    cout << "You left and you never saw it again." << endc;
                    Sleep(3000);
                }
                elif (sd < 10)
                {
                    cout << "You found a rock! 1 * lv.1 pickaxe to mine it." << endc;
                    pii ret = gb.consume("", "pickaxe", 1, 10, 9, 30, 31);
                    if (ret.first != -1)
                    {
                        cout << green << "You get it (2 * lv.1 rock)!" << endc << endc;
                        gb.invent_add("rock", 1, 2);
                        if (ret.second)
                        {
                            cout << red << "You pickaxe is broken." << endc;
                        }
                    }
                    cout << "You left and you never saw it again." << endc;
                    Sleep(2500);
                }
                else
                {
                    cout << "You found nothing." << endc;
                    Sleep(2000);
                }
                mining_lv_1 = now;
            }
        }
        System_Clear();
        cout << green << "       Plains" << endc;
        if (MADE_MAP >= 1 && gb.level >= 1)
        {
            cout << green << "         To Town (U)";
        }
        cout << endc;
        cout << endc;
        if (MADE_MAP >= 4 && gb.level >= 2 && explore_stage >= 9)
        {
            cout << green << "To Ponds (L)";
        }
        cout << endc;
        cout << endc;
        gb.lvc[abs(explore_stage)]();
        cout << "   > Explore (F)" << endc;
        if (explore_stage >= 1)
        {
            cout << yellow << "   > Craft House (C)" << endc;
        }
        if (explore_stage >= 7)
        {
            cout << "   > Mine (M)" << endc;
        }
        cout << endc;
        if (MADE_MAP >= 5 && gb.level >= 2 && explore_stage >= 8)
        {
            cout << green << "         To Woods (D)";
        }
        cout << endc;
    }
    return sget(arg);
}

string Plains_2::save()
{
    return "mp02_cfh;" + to_string(craft_house_lv_1) + ";mp02_mng;" + to_string(mining_lv_1) + ";mp02_exp;" + to_string(explore_lv_1) + ";mp02_exs;" + to_string(explore_stage) + ";";
}

SGET_RET Plains_2::load(SGET_RET tgm)
{
    next(tgm);
    while (tgm.curtsk.substr(0, 4) == "mp02")
    {
        if (tgm.curtsk == "mp02_cfh")
        {
            next(tgm);
            craft_house_lv_1 = stoi(tgm.curtsk);
            next(tgm);
        }
        if (tgm.curtsk == "mp02_mng")
        {
            next(tgm);
            mining_lv_1 = stoi(tgm.curtsk);
            next(tgm);
        }
        if (tgm.curtsk == "mp02_exp")
        {
            next(tgm);
            explore_lv_1 = stoi(tgm.curtsk);
            next(tgm);
        }
        if (tgm.curtsk == "mp02_exs")
        {
            next(tgm);
            explore_stage = stoi(tgm.curtsk);
            next(tgm);
        }
    }
    return tgm;
}
