#include "acss/acss.h"
#include <cstdio>
#include <cstring>
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
    "Root { background-color: #16171a; font-family: sans-serif; }"
    ""
    "#backdrop { position: absolute; left: 0px; top: 0px; width: 1024px; height: 780px;"
    "            background-image: linear-gradient(200deg, #2a2c2e, #101113 65%); }"
    "#portrait { position: absolute; left: 610px; top: 40px; width: 380px; height: 500px;"
    "            background-image: linear-gradient(160deg, #3a4550, #1a2027); display: flex;"
    "            align-items: center; justify-content: center; }"
    "#portrait-caption { color: #5b6672; font-size: 13px; letter-spacing: 1px; }"
    "#wordmark { position: absolute; left: 30px; top: 725px; color: #d99a2b; font-size: 26px;"
    "            font-weight: bold; letter-spacing: 6px; white-space: nowrap; }"
    "#footer-right { position: absolute; left: 900px; top: 690px; display: flex; flex-direction: column; align-items: flex-end; gap: 4px; }"
    ".footer-label { color: #cfd2d6; font-size: 13px; }"
    ""
    "#console { position: absolute; left: 40px; top: 40px; width: 560px; background-color: #3b3f31; border: 1px solid #14150f; }"
    "#console-bar { display: flex; flex-direction: row; justify-content: space-between; align-items: center;"
    "               background-color: #4c5140; padding: 6px 10px; }"
    "#console-title { color: #e2e4d6; font-size: 12px; }"
    "#console-close { color: #c3c6b8; font-size: 14px; }"
    "#console-log { background-color: #2a2d22; height: 260px; }"
    "#console-input-row { display: flex; flex-direction: row; gap: 6px; padding: 8px; }"
    "#console-input { width: 470px; height: 22px; background-color: #2a2d22; border: 1px solid #14150f; color: #e2e4d6; }"
    ""
    "#menu-list { position: absolute; left: 40px; top: 480px; }"
    ".menu-item { color: #eceade; font-size: 15px; padding: 5px 0; }"
    ".menu-gap { height: 14px; }"
    ""
    "#options-panel { position: absolute; left: 262px; top: 178px; width: 500px; background-color: #3b3f31; border: 1px solid #14150f; }"
    "#options-bar { display: flex; flex-direction: row; justify-content: space-between; align-items: center;"
    "               background-color: #4c5140; padding: 6px 10px; }"
    "#options-title { color: #e2e4d6; font-size: 12px; }"
    "#options-close { color: #c3c6b8; font-size: 14px; }"
    ".acss-tab-bar { display: flex; flex-direction: row; background-color: #4c5140; padding-left: 4px; }"
    ".acss-tab { color: #c3c6b8; font-size: 11px; padding: 6px 10px; background-color: transparent; }"
    ".acss-tab.active { color: #d99a2b; background-color: #3b3f31; }"
    ".acss-tab-panels { padding: 12px; }"
    ""
    ".kb-header-row { display: flex; flex-direction: row; padding: 4px 6px; }"
    ".kb-col1 { width: 210px; color: #d99a2b; font-size: 10px; letter-spacing: 1px; }"
    ".kb-col2 { width: 140px; color: #d99a2b; font-size: 10px; letter-spacing: 1px; }"
    ".kb-col3 { width: 100px; color: #d99a2b; font-size: 10px; letter-spacing: 1px; }"
    ".kb-row { display: flex; flex-direction: row; padding: 5px 6px; }"
    ".kb-row.hot { background-color: #a3831f; }"
    ".kb-cell1 { width: 210px; color: #e2e4d6; font-size: 12px; }"
    ".kb-cell2 { width: 140px; color: #e2e4d6; font-size: 12px; }"
    ".kb-cell3 { width: 100px; color: #e2e4d6; font-size: 12px; }"
    "#kb-list { height: 190px; overflow: scroll; }"
    ""
    "#kb-footer { display: flex; flex-direction: row; justify-content: space-between; align-items: center; padding: 10px 12px; }"
    ".edit-group { display: flex; flex-direction: row; gap: 8px; }"
    "Button { background-color: #5c6049; color: #eceade; font-size: 12px; padding: 6px 14px; border: 1px solid #14150f; }"
    ".options-actions { display: flex; flex-direction: row; justify-content: flex-end; gap: 8px; padding: 0px 12px 12px 12px; }";

int main(int argc, char **argv) {
    bool showOptions = (argc > 1 && strcmp(argv[1], "options") == 0);

    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(1024, 780, "acss game-ui demo 6 -- HL1 portrait menu layout recreation");
    SetTargetFPS(60);

    Document *doc = DocumentCreate();

    Div(doc, doc->root, "")->id = "backdrop";
    Element *portrait = Div(doc, doc->root, "");
    portrait->id = "portrait";
    Text(doc, portrait, "", "[ character portrait placeholder ]")->id = "portrait-caption";
    Text(doc, doc->root, "", "H A L F - L I F E")->id = "wordmark";
    Element *footerRight = Div(doc, doc->root, "");
    footerRight->id = "footer-right";
    Text(doc, footerRight, "footer-label", "Servers");
    Text(doc, footerRight, "footer-label", "STEAM");

    Element *console = Div(doc, doc->root, "");
    console->id = "console";
    Element *conBar = Div(doc, console, "");
    conBar->id = "console-bar";
    Text(doc, conBar, "", "Console")->id = "console-title";
    Text(doc, conBar, "", "X")->id = "console-close";
    Div(doc, console, "")->id = "console-log"; /* empty -- matches the freshly-opened reference */
    Element *conInputRow = Div(doc, console, "");
    conInputRow->id = "console-input-row";
    Element *conInput = ElementCreate(doc, ELEMENT_INPUT, "");
    conInput->id = "console-input";
    ElementAppendChild(conInputRow, conInput);
    Btn(doc, conInputRow, "", "Submit");

    Element *menuList = Div(doc, doc->root, "");
    menuList->id = "menu-list";
    Text(doc, menuList, "menu-item", "New Game");
    Text(doc, menuList, "menu-item", "Load Game");
    Div(doc, menuList, "menu-gap");
    Text(doc, menuList, "menu-item", "Find Servers");
    Text(doc, menuList, "menu-item", "Create Server");
    Div(doc, menuList, "menu-gap");
    Text(doc, menuList, "menu-item", "Options");
    Text(doc, menuList, "menu-item", "Quit");

    if (showOptions) {
        Element *options = Div(doc, doc->root, "");
        options->id = "options-panel";
        Element *optBar = Div(doc, options, "");
        optBar->id = "options-bar";
        Text(doc, optBar, "", "Options")->id = "options-title";
        Text(doc, optBar, "", "X")->id = "options-close";

        Element *tabs = TabsCreate(doc);
        ElementAppendChild(options, tabs);
        const char *tabNames[] = { "Keyboard", "Mouse", "Audio", "Video", "Voice", "Lock", "Multiplayer" };
        Element *kbPanel = NULL;
        for (int i = 0; i < 7; i++) {
            Element *p = TabsAddTab(doc, tabs, tabNames[i]);
            if (i == 0) kbPanel = p;
        }

        Element *hdrRow = Div(doc, kbPanel, "kb-header-row");
        Text(doc, hdrRow, "kb-col1", "MOVEMENT");
        Text(doc, hdrRow, "kb-col2", "KEY/BUTTON");
        Text(doc, hdrRow, "kb-col3", "ALTERNATE");
        Element *kbList = Div(doc, kbPanel, "");
        kbList->id = "kb-list";
        struct { const char *action, *key, *alt; } binds[] = {
            { "Move forward", "Up", "W" },
            { "Move back", "Down", "S" },
            { "Turn left", "Left", "" },
            { "Turn right", "Right", "" },
            { "Move left (strafe)", "A", "," },
            { "Move right (strafe)", "D", "." },
            { "Jump", "Space", "" },
            { "Duck", "Left Ctrl", "" },
            { "Swim up", "V", "" },
            { "Swim down", "C", "/" },
        };
        for (size_t i = 0; i < sizeof(binds) / sizeof(binds[0]); i++) {
            Element *row = Div(doc, kbList, "kb-row");
            if (i == 0) AddClasses(row, "hot");
            Text(doc, row, "kb-cell1", binds[i].action);
            Text(doc, row, "kb-cell2", binds[i].key);
            Text(doc, row, "kb-cell3", binds[i].alt);
        }

        Element *footer = Div(doc, options, "");
        footer->id = "kb-footer";
        Btn(doc, footer, "", "Use Defaults");
        Element *editGroup = Div(doc, footer, "edit-group");
        Btn(doc, editGroup, "", "Edit key");
        Btn(doc, editGroup, "", "Clear Key");

        Element *actions = Div(doc, options, "options-actions");
        Btn(doc, actions, "", "OK");
        Btn(doc, actions, "", "Cancel");
        Btn(doc, actions, "", "Apply");
    }

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
