#include "acss/acss.h"
#include <cstdio>
#include <string>

static void AddClasses(Element *e, const char *cls) {
    std::string s(cls);
    size_t start = 0;
    while (start < s.size()) {
        size_t sp = s.find(' ', start);
        std::string one = (sp == std::string::npos) ? s.substr(start) : s.substr(start, sp - start);
        if (!one.empty()) ElementAddClass(e, one);
        if (sp == std::string::npos) break;
        start = sp + 1;
    }
}
static Element *Div(Document *doc, Element *parent, const char *cls) {
    Element *e = ElementCreate(doc, ELEMENT_DIV, "");
    if (cls[0]) AddClasses(e, cls);
    ElementAppendChild(parent, e);
    return e;
}
static Element *Text(Document *doc, Element *parent, const char *cls, const char *text) {
    Element *e = ElementCreate(doc, ELEMENT_TEXT, "");
    if (cls[0]) AddClasses(e, cls);
    ElementSetText(e, text);
    ElementAppendChild(parent, e);
    return e;
}
static Element *Btn(Document *doc, Element *parent, const char *cls, const char *text) {
    Element *e = ElementCreate(doc, ELEMENT_BUTTON, "");
    if (cls[0]) AddClasses(e, cls);
    ElementSetText(e, text);
    ElementAppendChild(parent, e);
    return e;
}

static const char *CSS =
    "Root { background-color: #05070a; font-family: sans-serif; }"
    ""
    "#backdrop { position: absolute; left: 0px; top: 0px; width: 1400px; height: 800px;"
    "            background-image: linear-gradient(160deg, #0c1420, #05070a 60%); }"
    "#vignette { position: absolute; left: 0px; top: 0px; width: 1400px; height: 800px;"
    "            background-image: radial-gradient(circle, rgba(20,30,45,0.6), rgba(0,0,0,0.85)); }"
    ""
    "#left-panel { position: absolute; left: 60px; top: 460px; width: 420px; }"
    "#game-title { color: #dfe3e8; font-size: 46px; font-weight: bold; letter-spacing: 4px; }"
    "#game-subtitle { color: #b8bec7; font-size: 26px; letter-spacing: 8px; margin-top: 4px; }"
    "#title-rule { width: 340px; height: 1px; background-color: #4a5261; margin-top: 14px; margin-bottom: 18px; }"
    ".menu-item { color: #e7e9ec; font-size: 19px; letter-spacing: 1px; padding: 7px 0; }"
    ".menu-item.hot { color: #f0a030; }"
    ""
    ".panel { position: absolute; background-color: #3a3f47; border: 1px solid #1a1d21; }"
    ".panel-titlebar { display: flex; flex-direction: row; justify-content: space-between; align-items: center;"
    "                  background-color: #24272c; padding: 8px 12px; }"
    ".panel-title { color: #d7dae0; font-size: 13px; font-weight: bold; letter-spacing: 1px; }"
    ".panel-close { color: #aab0b8; font-size: 15px; width: 20px; height: 20px; background-color: transparent;"
    "               display: flex; align-items: center; justify-content: center; }"
    ".panel-body { padding: 16px; }"
    ""
    "#newgame-panel { left: 660px; top: 380px; width: 600px; }"
    ".chapter-row { display: flex; flex-direction: row; gap: 16px; }"
    ".chapter-col { display: flex; flex-direction: column; width: 176px; }"
    ".chapter-label { color: #9099a3; font-size: 10px; letter-spacing: 1px; }"
    ".chapter-label.active { color: #f0a030; }"
    ".chapter-title { color: #d7dae0; font-size: 11px; font-weight: bold; margin-bottom: 6px; }"
    ".chapter-thumb { width: 176px; height: 100px; background-color: #23303d; }"
    ".chapter-thumb.active { border: 3px solid #f0a030; width: 170px; height: 94px; }"
    ".more-row { display: flex; flex-direction: row; justify-content: flex-end; margin-top: 10px; }"
    ".hairline { width: 568px; height: 1px; background-color: #2a2d32; margin-top: 16px; margin-bottom: 14px; }"
    ".commentary-row { display: flex; flex-direction: row; align-items: center; gap: 10px; }"
    ".commentary-label { color: #c7ccd2; font-size: 13px; }"
    ".newgame-actions { display: flex; flex-direction: row; justify-content: flex-end; gap: 10px; margin-top: 18px; }"
    ""
    "Button { background-color: #4a505a; color: #d7dae0; font-size: 12px; padding: 7px 16px; border: 1px solid #22252a; }"
    "Button.primary { background-color: #b97316; color: #ffffff; }"
    ""
    "#options-panel { left: 900px; top: 60px; width: 500px; }"
    ".acss-tab-bar { display: flex; flex-direction: row; background-color: #2c2f34; }"
    ".acss-tab { color: #9099a3; font-size: 11px; padding: 8px 14px; background-color: transparent; }"
    ".acss-tab.active { color: #f0a030; background-color: #3a3f47; }"
    ".acss-tab-panels { padding: 16px; }"
    ".diff-label { color: #c7ccd2; font-size: 13px; margin-bottom: 12px; }"
    ".radio-row { display: flex; flex-direction: row; align-items: flex-start; gap: 8px; margin-bottom: 14px; }"
    ".radio-text { display: flex; flex-direction: column; }"
    ".radio-title { color: #e7e9ec; font-size: 13px; font-weight: bold; }"
    ".radio-desc { color: #9099a3; font-size: 11px; margin-top: 2px; }"
    ".options-actions { display: flex; flex-direction: row; justify-content: flex-end; gap: 10px; margin-top: 6px; }"
    ""
    "#ach-panel { left: 900px; top: 470px; width: 500px; }"
    ".ach-progress-row { display: flex; flex-direction: row; justify-content: space-between; margin-bottom: 6px; }"
    ".ach-progress-label { color: #9099a3; font-size: 11px; }"
    ".ach-bar-track { width: 468px; height: 10px; background-color: #24272c; margin-bottom: 12px; }"
    ".ach-bar-fill { width: 52px; height: 10px; background-color: #6fae2e; }"
    ".ach-list { display: flex; flex-direction: column; height: 210px; overflow: scroll; gap: 2px; }"
    ".ach-row { display: flex; flex-direction: row; gap: 10px; background-color: #33373d; padding: 8px; align-items: center; }"
    ".ach-icon { width: 36px; height: 36px; background-color: #23303d; }"
    ".ach-icon.gold { background-color: #8a6414; }"
    ".ach-text { display: flex; flex-direction: column; }"
    ".ach-title { color: #e7e9ec; font-size: 12px; font-weight: bold; }"
    ".ach-desc { color: #9099a3; font-size: 10px; margin-top: 2px; }"
    ".ach-footer { display: flex; flex-direction: row; justify-content: space-between; align-items: center; margin-top: 10px; }"
    ".hide-row { display: flex; flex-direction: row; align-items: center; gap: 8px; }"
    ".hide-label { color: #c7ccd2; font-size: 12px; }";

int main(void) {
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(1400, 800, "acss game-ui demo 1 -- Half-Life 2: Episode Two menu layout recreation");
    SetTargetFPS(60);

    Document *doc = DocumentCreate();

    Div(doc, doc->root, "")->id = "backdrop";
    Div(doc, doc->root, "")->id = "vignette";

    Element *left = Div(doc, doc->root, "");
    left->id = "left-panel";
    Text(doc, left, "", "");
    Element *title = ElementCreate(doc, ELEMENT_TEXT, "game-title");
    ElementSetText(title, "HALF-LIFE 2");
    ElementAppendChild(left, title);
    Element *subtitle = ElementCreate(doc, ELEMENT_TEXT, "game-subtitle");
    ElementSetText(subtitle, "EPISODE TWO");
    ElementAppendChild(left, subtitle);
    Div(doc, left, "")->id = "title-rule";
    const char *menuItems[] = { "NEW GAME", "LOAD GAME", "ACHIEVEMENTS", "OPTIONS", "BACK" };
    for (int i = 0; i < 5; i++) {
        Element *mi = Text(doc, left, "menu-item", menuItems[i]);
        if (i == 0) AddClasses(mi, "hot");
    }


    Element *options = Div(doc, doc->root, "panel");
    options->id = "options-panel";
    Element *optBar = Div(doc, options, "panel-titlebar");
    Text(doc, optBar, "panel-title", "OPTIONS");
    Text(doc, optBar, "panel-close", "X");

    Element *tabs = TabsCreate(doc);
    ElementAppendChild(options, tabs);
    const char *tabNames[] = { "Gameplay", "Keyboard", "Mouse", "Gamepad", "Audio", "Video" };
    Element *gameplayPanel = NULL;
    for (int i = 0; i < 6; i++) {
        Element *panel = TabsAddTab(doc, tabs, tabNames[i]);
        AddClasses(panel, "acss-tab-panel-content");
        if (i == 0) gameplayPanel = panel;
    }

    Text(doc, gameplayPanel, "diff-label", "Combat difficulty:");
    struct { const char *title; const char *desc; } diffs[3] = {
        { "Easy", "Enemies are easy to defeat, and the computer helps you aim." },
        { "Normal", "Challenging enemies; your weapons do normal damage." },
        { "Hard", "Enemies are very tough; your weapons are less effective." },
    };
    for (int i = 0; i < 3; i++) {
        Element *row = Div(doc, gameplayPanel, "radio-row");
        Element *radio = ElementCreate(doc, ELEMENT_RADIO, "");
        if (i == 1) radio->checked = true;
        ElementAppendChild(row, radio);
        Element *rt = Div(doc, row, "radio-text");
        Text(doc, rt, "radio-title", diffs[i].title);
        Text(doc, rt, "radio-desc", diffs[i].desc);
    }
    Element *optActions = Div(doc, gameplayPanel, "options-actions");
    Btn(doc, optActions, "primary", "OK");
    Btn(doc, optActions, "", "Cancel");
    Btn(doc, optActions, "", "Apply");


    Element *ach = Div(doc, doc->root, "panel");
    ach->id = "ach-panel";
    Element *achBar = Div(doc, ach, "panel-titlebar");
    Text(doc, achBar, "panel-title", "My Achievements");
    Text(doc, achBar, "panel-close", "X");
    Element *achBody = Div(doc, ach, "panel-body");
    Element *progRow = Div(doc, achBody, "ach-progress-row");
    Text(doc, progRow, "ach-progress-label", "Total Achievements Earned");
    Text(doc, progRow, "ach-progress-label", "2 / 17 (11%)");
    Div(doc, achBody, "ach-bar-track");
    Element *achList = Div(doc, achBody, "ach-list");
    struct { const char *title; const char *desc; bool gold; } achData[5] = {
        { "Web Weaver", "Find and break every web cache in this chapter.", false },
        { "Clean Sweep", "Defeat the gunship without taking a hit.", false },
        { "Gnome Voyager", "Launch the garden gnome into orbit.", true },
        { "Cache Raider", "Steal a strider's power cell.", false },
        { "Vort Ally", "Complete the escort mission unscathed.", false },
    };
    for (int i = 0; i < 5; i++) {
        Element *row = Div(doc, achList, "ach-row");
        Element *icon = Div(doc, row, "ach-icon");
        if (achData[i].gold) AddClasses(icon, "gold");
        Element *txt = Div(doc, row, "ach-text");
        Text(doc, txt, "ach-title", achData[i].title);
        Text(doc, txt, "ach-desc", achData[i].desc);
    }
    Element *achFooter = Div(doc, achBody, "ach-footer");
    Element *hideRow = Div(doc, achFooter, "hide-row");
    Element *hideCb = ElementCreate(doc, ELEMENT_CHECKBOX, "");
    ElementAppendChild(hideRow, hideCb);
    Text(doc, hideRow, "hide-label", "Hide Achieved");
    Btn(doc, achFooter, "", "Back");

    Element *newgame = Div(doc, doc->root, "panel");
    newgame->id = "newgame-panel";
    Element *ngBar = Div(doc, newgame, "panel-titlebar");
    Text(doc, ngBar, "panel-title", "NEW GAME");
    Text(doc, ngBar, "panel-close", "X");
    Element *ngBody = Div(doc, newgame, "panel-body");
    Element *chRow = Div(doc, ngBody, "chapter-row");
    const char *chNums[] = { "CHAPTER 1", "CHAPTER 2", "CHAPTER 3" };
    const char *chNames[] = { "TO THE WHITE FOREST", "THIS VORTAL COIL", "FREEMAN PONTIFEX" };
    for (int i = 0; i < 3; i++) {
        Element *col = Div(doc, chRow, "chapter-col");
        Element *lbl = Text(doc, col, "chapter-label", chNums[i]);
        Element *nm = Text(doc, col, "chapter-title", chNames[i]);
        Element *thumb = Div(doc, col, "chapter-thumb");
        if (i == 0) { AddClasses(lbl, "active"); AddClasses(thumb, "active"); }
        (void)nm;
    }
    Element *moreRow = Div(doc, ngBody, "more-row");
    Btn(doc, moreRow, "", "More >");
    Div(doc, ngBody, "hairline");
    Element *commRow = Div(doc, ngBody, "commentary-row");
    Element *commCb = ElementCreate(doc, ELEMENT_CHECKBOX, "");
    ElementAppendChild(commRow, commCb);
    Text(doc, commRow, "commentary-label", "Enable commentary track");
    Element *ngActions = Div(doc, ngBody, "newgame-actions");
    Btn(doc, ngActions, "primary", "Start new game");
    Btn(doc, ngActions, "", "Cancel");

    bool loaded = DocumentLoadStyleFromString(doc, CSS);
    if (!loaded) printf("acss: warning -- CSS failed to parse\n");

    while (!WindowShouldClose()) {
        float w = (float)GetScreenWidth();
        float h = (float)GetScreenHeight();

        LayoutDocument(doc, w, h);
        UpdateDocument(doc);

        BeginDrawing();
        ClearBackground(RAYWHITE);
        RenderDocument(doc);
        EndDrawing();
    }

    DocumentDestroy(doc);
    CloseWindow();
    return 0;
}
