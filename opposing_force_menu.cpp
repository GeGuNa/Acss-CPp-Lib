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
    "Root { background-color: #232017; font-family: sans-serif; }"
    ""
    "#backdrop { position: absolute; left: 0px; top: 0px; width: 1280px; height: 720px;"
    "            background-image: linear-gradient(120deg, #4a4632, #232017 55%, #362f22); }"
    "#logo-ring { position: absolute; left: 980px; top: 380px; width: 260px; height: 260px;"
    "             border: 10px solid #6b6455; border-radius: 130px; display: flex; align-items: center; justify-content: center; }"
    "#logo-glyph { color: #6b6455; font-size: 90px; font-weight: bold; }"
    ""
    "#title-block { position: absolute; left: 40px; top: 30px; }"
    "#title-1 { color: #c0392b; font-size: 44px; font-weight: bold; letter-spacing: 6px; }"
    "#title-2 { color: #d9a548; font-size: 46px; font-weight: bold; letter-spacing: 3px; margin-top: 6px; }"
    ""
    "#menu-rows { position: absolute; left: 40px; top: 190px; display: flex; flex-direction: column; gap: 12px; }"
    ".menu-row { display: flex; flex-direction: row; align-items: baseline; gap: 30px; }"
    ".menu-item { width: 260px; color: #d9a548; font-size: 22px; font-weight: bold; letter-spacing: 1px; }"
    ".menu-desc { width: 460px; color: #b9b6a8; font-size: 14px; }"
    ""
    "#changegame-panel { position: absolute; left: 470px; top: 270px; width: 560px; background-color: #1c1d1a; border: 1px solid #050505; }"
    "#cg-bar { display: flex; flex-direction: row; justify-content: space-between; align-items: center;"
    "          background-color: #26251f; padding: 8px 12px; }"
    "#cg-title { color: #d9a548; font-size: 14px; font-weight: bold; }"
    "#cg-close { color: #cfd2d6; font-size: 15px; }"
    "#cg-body { padding: 14px; }"
    "#cg-label { color: #cfd2d6; font-size: 12px; margin-bottom: 6px; }"
    "#cg-list { height: 220px; overflow: scroll; background-color: #101010; border: 1px solid #050505; }"
    ".cg-row { color: #d7d9dc; font-size: 13px; padding: 6px 10px; }"
    ".cg-row.hot { background-color: #b9821f; color: #17170f; font-weight: bold; }"
    "#cg-warning { color: #9a9d92; font-size: 12px; margin-top: 10px; }"
    "#cg-actions { display: flex; flex-direction: row; justify-content: flex-end; gap: 8px; margin-top: 12px; }"
    "Button { background-color: #3a3a30; color: #eceade; font-size: 12px; padding: 8px 16px; border: 1px solid #050505; }"
    "Button.primary { background-color: #b9821f; color: #17170f; font-weight: bold; }";

int main(void) {
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(1280, 720, "acss game-ui demo 7 -- Opposing Force style menu layout recreation");
    SetTargetFPS(60);

    Document *doc = DocumentCreate();

    Div(doc, doc->root, "")->id = "backdrop";
    Element *logoRing = Div(doc, doc->root, "");
    logoRing->id = "logo-ring";
    Text(doc, logoRing, "", "L")->id = "logo-glyph"; 

    Element *titleBlock = Div(doc, doc->root, "");
    titleBlock->id = "title-block";
    Text(doc, titleBlock, "", "HALF-LIFE")->id = "title-1";
    Text(doc, titleBlock, "", "OPPOSING FORCE")->id = "title-2";

    Element *menuRows = Div(doc, doc->root, "");
    menuRows->id = "menu-rows";
    struct { const char *item, *desc; } items[] = {
        { "NEW GAME", "Begin a new game." },
        { "BOOT CAMP", "Off for little training before the real fight." },
        { "CONFIGURATION", "Your are looking at it." },
        { "LOAD GAME", "Load a saved game." },
        { "MULTIPLAYER", "Prepare for combat. This means teamwork." },
        { "CREATE SERVER", "Set up an Opposing Force game on a local area network." },
        { "CUSTOM GAME", "Select a custom game, maggot." },
        { "QUIT", "A good soldier never leaves his squad behind." },
    };
    for (size_t i = 0; i < sizeof(items) / sizeof(items[0]); i++) {
        Element *row = Div(doc, menuRows, "menu-row");
        Text(doc, row, "menu-item", items[i].item);
        Text(doc, row, "menu-desc", items[i].desc);
    }

    Element *cg = Div(doc, doc->root, "");
    cg->id = "changegame-panel";
    Element *cgBar = Div(doc, cg, "");
    cgBar->id = "cg-bar";
    Text(doc, cgBar, "", "Change game")->id = "cg-title";
    Text(doc, cgBar, "", "X")->id = "cg-close";
    Element *cgBody = Div(doc, cg, "");
    cgBody->id = "cg-body";
    Text(doc, cgBody, "", "Game")->id = "cg-label";
    Element *cgList = Div(doc, cgBody, "");
    cgList->id = "cg-list";
    const char *games[] = {
        "Blue Shift", "Blue Shift", "Blue Shift", "Blue Shift",
        "Counter-Strike", "Half-Life: Decay", "Deathmatch Classic",
        "Deathmatch Classic", "INVASION", "Ricochet",
    };
    for (size_t i = 0; i < sizeof(games) / sizeof(games[0]); i++) {
        Element *row = Text(doc, cgList, "cg-row", games[i]);
        if (i == 0) AddClasses(row, "hot");
    }
    Text(doc, cgBody, "", "Changing games will cause the engine to restart.")->id = "cg-warning";
    Element *cgActions = Div(doc, cgBody, "");
    cgActions->id = "cg-actions";
    Btn(doc, cgActions, "primary", "Change game");
    Btn(doc, cgActions, "", "Cancel");

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
