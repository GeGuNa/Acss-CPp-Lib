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
    "Root { background-color: #0a0a09; font-family: sans-serif; }"
    ""
    "#backdrop { position: absolute; left: 0px; top: 0px; width: 1280px; height: 720px;"
    "            background-image: linear-gradient(135deg, #1c1a16, #0a0a09 65%); }"
    ""
    "#cs-title { position: absolute; left: 40px; top: 40px; color: #d7d2c4; font-size: 30px;"
    "            font-weight: bold; letter-spacing: 3px; }"
    "#menu-list { position: absolute; left: 40px; top: 100px; }"
    ".menu-item { color: #c9c4b6; font-size: 15px; letter-spacing: 1px; padding: 9px 0; }"
    ".menu-item.hot { color: #d99a2b; }"
    ""
    "#console { position: absolute; left: 760px; top: 20px; width: 500px; background-color: #26251f; border: 1px solid #0a0a09; }"
    "#console-bar { display: flex; flex-direction: row; justify-content: space-between; align-items: center;"
    "               background-color: #38362d; padding: 6px 10px; }"
    "#console-title { color: #d8d9c8; font-size: 12px; }"
    "#console-log { background-color: #101010; padding: 10px; height: 90px; color: #6fae2e; font-size: 11px; }"
    ".log-line { margin-bottom: 2px; }"
    ""
    "#options-panel { position: absolute; left: 380px; top: 180px; width: 560px; background-color: #3a382f; border: 1px solid #0a0a09; }"
    "#options-bar { display: flex; flex-direction: row; justify-content: space-between; align-items: center;"
    "               background-color: #2c2b24; padding: 8px 12px; }"
    "#options-title { color: #d8d9c8; font-size: 13px; font-weight: bold; letter-spacing: 1px; }"
    "#options-close { color: #b8bba8; font-size: 15px; }"
    ".acss-tab-bar { display: flex; flex-direction: row; background-color: #2c2b24; padding-left: 4px; }"
    ".acss-tab { color: #a9a595; font-size: 11px; padding: 7px 12px; background-color: transparent; }"
    ".acss-tab.active { color: #e8c15a; background-color: #3a382f; }"
    ".acss-tab-panels { padding: 18px; }"
    ""
    ".video-grid { display: flex; flex-direction: row; gap: 24px; }"
    ".video-col { display: flex; flex-direction: column; gap: 12px; width: 240px; }"
    ".field-label { color: #d8d9c8; font-size: 12px; }"
    "Select { width: 240px; height: 26px; background-color: #26251f; border: 1px solid #0a0a09; color: #e8c15a; font-size: 12px; }"
    ""
    "Button { background-color: #4b4a3d; color: #d7d2c4; font-size: 12px; padding: 8px 12px; border: 1px solid #0a0a09; }"
    ".credits-link { color: #8fae5a; font-size: 11px; margin-top: 14px; }"
    ".options-actions { display: flex; flex-direction: row; justify-content: flex-end; gap: 8px; margin-top: 20px; }";

int main(void) {
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(1280, 720, "acss game-ui demo 4 -- Counter-Strike options menu layout recreation");
    SetTargetFPS(60);

    Document *doc = DocumentCreate();

    Div(doc, doc->root, "")->id = "backdrop";
    Text(doc, doc->root, "", "COUNTER-STRIKE")->id = "cs-title";

    Element *menuList = Div(doc, doc->root, "");
    menuList->id = "menu-list";
    const char *menuItems[] = { "FIND SERVERS", "CREATE SERVER", "ACHIEVEMENTS", "REPORT BUG", "VIDEO STRESS TEST", "OPTIONS", "QUIT" };
    for (int i = 0; i < 7; i++) {
        Element *mi = Text(doc, menuList, "menu-item", menuItems[i]);
        if (i == 5) AddClasses(mi, "hot");
    }

    Element *console = Div(doc, doc->root, "");
    console->id = "console";
    Element *conBar = Div(doc, console, "");
    conBar->id = "console-bar";
    Text(doc, conBar, "", "Console")->id = "console-title";
    Element *conLog = Div(doc, console, "");
    conLog->id = "console-log";
    Text(doc, conLog, "log-line", "] vgui_ui_scale_factor \"2\" (def. \"1\")");
    Text(doc, conLog, "log-line", "] version");
    Text(doc, conLog, "log-line", "Build Label: 9540945");

    Element *options = Div(doc, doc->root, "");
    options->id = "options-panel";
    Element *optBar = Div(doc, options, "");
    optBar->id = "options-bar";
    Text(doc, optBar, "", "OPTIONS")->id = "options-title";
    Text(doc, optBar, "", "X")->id = "options-close";

    Element *tabs = TabsCreate(doc);
    ElementAppendChild(options, tabs);
    const char *tabNames[] = { "Keyboard", "Mouse", "Audio", "Video", "Voice", "Multiplayer" };
    Element *videoPanel = NULL;
    for (int i = 0; i < 6; i++) {
        Element *p = TabsAddTab(doc, tabs, tabNames[i]);
        if (i == 3) videoPanel = p;
    }
    TabsSetActive(doc, tabs, 3); 

    Element *grid = Div(doc, videoPanel, "video-grid");
    Element *col1 = Div(doc, grid, "video-col");
    Text(doc, col1, "field-label", "Resolution");
    Element *resSelect = ElementCreate(doc, ELEMENT_SELECT, "");
    ElementAppendChild(col1, resSelect);
    ElementAddOption(resSelect, "1920 x 1080 (native)");
    ElementAddOption(resSelect, "1600 x 900");
    ElementAddOption(resSelect, "1280 x 720");
    resSelect->selectedIndex = 0;

    Text(doc, col1, "field-label", "Aspect Ratio");
    Element *aspSelect = ElementCreate(doc, ELEMENT_SELECT, "");
    ElementAppendChild(col1, aspSelect);
    ElementAddOption(aspSelect, "Widescreen 16:9");
    ElementAddOption(aspSelect, "Standard 4:3");
    aspSelect->selectedIndex = 0;

    Btn(doc, col1, "", "Adjust brightness levels...");

    Element *col2 = Div(doc, grid, "video-col");
    Text(doc, col2, "field-label", "Display Mode");
    Element *modeSelect = ElementCreate(doc, ELEMENT_SELECT, "");
    ElementAppendChild(col2, modeSelect);
    ElementAddOption(modeSelect, "Full screen");
    ElementAddOption(modeSelect, "Windowed");
    ElementAddOption(modeSelect, "Borderless");
    modeSelect->selectedIndex = 0;

    Btn(doc, col2, "", "Advanced...");
    Text(doc, col2, "credits-link", "3rd party technology credits");

    Element *optActions = Div(doc, videoPanel, "options-actions");
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
