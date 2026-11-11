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
    "Root { background-color: #0c0d0b; font-family: sans-serif; }"
    ""
    "#backdrop { position: absolute; left: 0px; top: 0px; width: 1280px; height: 720px;"
    "            background-image: radial-gradient(circle, #26241f, #0c0d0b 70%); }"
    "#life-wordmark { position: absolute; left: 760px; top: 60px; color: #ffffff; font-size: 90px;"
    "                 font-weight: bold; letter-spacing: 22px; opacity: 0.14; }"
    ""
    "#console { position: absolute; left: 40px; top: 40px; width: 540px; background-color: #2a2c26; border: 1px solid #0c0d0b; }"
    "#console-bar { display: flex; flex-direction: row; justify-content: space-between; align-items: center;"
    "               background-color: #3d4033; padding: 6px 10px; }"
    "#console-title { color: #d8d9c8; font-size: 12px; }"
    "#console-close { color: #b8bba8; font-size: 14px; }"
    "#console-log { background-color: #14150f; padding: 10px; height: 190px; color: #6fae2e; font-size: 12px; }"
    ".log-line { margin-bottom: 2px; }"
    "#console-input { width: 518px; height: 22px; margin: 8px; background-color: #14150f; border: 1px solid #4a4d3f; color: #d8d9c8; }"
    ""
    "#menu-list { position: absolute; left: 40px; top: 470px; }"
    ".menu-item { color: #d99a2b; font-size: 22px; letter-spacing: 1px; padding: 6px 0; }"
    ""
    "#options-panel { position: absolute; left: 380px; top: 140px; width: 520px; background-color: #4b4f3e; border: 1px solid #14150f; }"
    "#options-bar { display: flex; flex-direction: row; justify-content: space-between; align-items: center;"
    "               background-color: #3d4033; padding: 6px 10px; }"
    "#options-title { color: #d8d9c8; font-size: 12px; }"
    "#options-close { color: #b8bba8; font-size: 14px; }"
    ".acss-tab-bar { display: flex; flex-direction: row; background-color: #3d4033; padding-left: 4px; }"
    ".acss-tab { color: #a9ad98; font-size: 11px; padding: 6px 10px; background-color: transparent; }"
    ".acss-tab.active { color: #e8c15a; background-color: #4b4f3e; }"
    ".acss-tab-panels { padding: 16px; }"
    ""
    ".mp-row { display: flex; flex-direction: row; gap: 20px; }"
    ".mp-preview { display: flex; flex-direction: column; align-items: center; gap: 10px; }"
    ".model-box { width: 160px; height: 190px; background-color: #33362b; }"
    ".spray-box { width: 62px; height: 62px; background-color: #d97a2b; display: flex; align-items: center; justify-content: center;"
    "             color: #ffffff; font-size: 22px; font-weight: bold; }"
    ".mp-fields { display: flex; flex-direction: column; gap: 10px; width: 300px; }"
    ".field-label { color: #d8d9c8; font-size: 12px; }"
    "Input { width: 280px; height: 24px; background-color: #33362b; border: 1px solid #14150f; color: #ffffff; padding: 0 6px; }"
    "Select { width: 280px; height: 26px; background-color: #33362b; border: 1px solid #14150f; color: #ffffff; }"
    "Range { width: 280px; }"
    ".advanced-row { display: flex; flex-direction: row; justify-content: flex-end; }"
    ""
    "Button { background-color: #5c6049; color: #eceade; font-size: 12px; padding: 6px 16px; border: 1px solid #14150f; }"
    ".options-actions { display: flex; flex-direction: row; justify-content: flex-end; gap: 8px; margin-top: 16px; }";

int main(void) {
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(1280, 720, "acss game-ui demo 2 -- Half-Life 1 VGUI menu layout recreation");
    SetTargetFPS(60);

    Document *doc = DocumentCreate();

    Div(doc, doc->root, "")->id = "backdrop";
    Element *wordmark = Text(doc, doc->root, "", "LIFE");
    wordmark->id = "life-wordmark";


    Element *console = Div(doc, doc->root, "");
    console->id = "console";
    Element *conBar = Div(doc, console, "");
    conBar->id = "console-bar";
    Text(doc, conBar, "", "Console")->id = "console-title";
    Text(doc, conBar, "", "X")->id = "console-close";
    Element *conLog = Div(doc, console, "");
    conLog->id = "console-log";
    const char *logLines[] = {
        "OnNewUrlLaunchParameters",
        "Playing startup video...",
        "] version",
        "Protocol version 48",
        "Exe version 1.1.2.2 (valve)",
        "Exe build: 10:06:31 Oct 7 2024 (10210)",
    };
    for (int i = 0; i < 6; i++) Text(doc, conLog, "log-line", logLines[i]);
    Element *conInput = ElementCreate(doc, ELEMENT_INPUT, "");
    conInput->id = "console-input";
    ElementAppendChild(console, conInput);


    Element *menuList = Div(doc, doc->root, "");
    menuList->id = "menu-list";
    const char *menuItems[] = { "Load game", "Find servers", "Create server", "Options", "Quit" };
    for (int i = 0; i < 5; i++) Text(doc, menuList, "menu-item", menuItems[i]);


    Element *options = Div(doc, doc->root, "");
    options->id = "options-panel";
    Element *optBar = Div(doc, options, "");
    optBar->id = "options-bar";
    Text(doc, optBar, "", "Options")->id = "options-title";
    Text(doc, optBar, "", "X")->id = "options-close";

    Element *tabs = TabsCreate(doc);
    ElementAppendChild(options, tabs);
    const char *tabNames[] = { "Audio", "Video", "Aim", "Keyboard", "Voice", "Content", "Multiplayer" };
    Element *mpPanel = NULL;
    for (int i = 0; i < 7; i++) {
        Element *p = TabsAddTab(doc, tabs, tabNames[i]);
        if (i == 6) mpPanel = p;
    }
    TabsSetActive(doc, tabs, 6); 

    Element *mpRow = Div(doc, mpPanel, "mp-row");
    Element *preview = Div(doc, mpRow, "mp-preview");
    Div(doc, preview, "model-box");
    Text(doc, Div(doc, preview, "spray-box"), "", "L"); 

    Element *fields = Div(doc, mpRow, "mp-fields");
    Text(doc, fields, "field-label", "Player name");
    Element *nameInput = ElementCreate(doc, ELEMENT_INPUT, "");
    ElementSetText(nameInput, "Gabe Newell");
    nameInput->text = "Gabe Newell";
    ElementAppendChild(fields, nameInput);

    Text(doc, fields, "field-label", "Player model");
    Element *modelSelect = ElementCreate(doc, ELEMENT_SELECT, "");
    ElementAppendChild(fields, modelSelect);
    ElementAddOption(modelSelect, "gordon");
    ElementAddOption(modelSelect, "barney");
    ElementAddOption(modelSelect, "gina");
    modelSelect->selectedIndex = 0;

    Text(doc, fields, "field-label", "Primary color");
    Element *primary = ElementCreate(doc, ELEMENT_RANGE, "");
    primary->value = 30.0f;
    ElementAppendChild(fields, primary);
    Text(doc, fields, "field-label", "Secondary color");
    Element *secondary = ElementCreate(doc, ELEMENT_RANGE, "");
    secondary->value = 10.0f;
    ElementAppendChild(fields, secondary);

    Text(doc, fields, "field-label", "Spraypaint image");
    Element *sprayLogo = ElementCreate(doc, ELEMENT_SELECT, "");
    ElementAppendChild(fields, sprayLogo);
    ElementAddOption(sprayLogo, "lambda");
    ElementAddOption(sprayLogo, "gordon");
    sprayLogo->selectedIndex = 0;
    Element *sprayColor = ElementCreate(doc, ELEMENT_SELECT, "");
    ElementAppendChild(fields, sprayColor);
    ElementAddOption(sprayColor, "Orange");
    ElementAddOption(sprayColor, "Red");
    ElementAddOption(sprayColor, "Blue");
    sprayColor->selectedIndex = 0;

    Element *advRow = Div(doc, mpPanel, "advanced-row");
    Btn(doc, advRow, "", "Advanced...");

    Element *optActions = Div(doc, mpPanel, "options-actions");
    Btn(doc, optActions, "", "OK");
    Btn(doc, optActions, "", "Cancel");
    Btn(doc, optActions, "", "Apply");

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
