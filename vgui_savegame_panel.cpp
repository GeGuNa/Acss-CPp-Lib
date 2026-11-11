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
static Element *Btn(Document *doc, Element *parent, const char *cls, const char *text) {
    Element *e = ElementCreate(doc, ELEMENT_BUTTON, "");
    if (cls[0]) AddClasses(e, cls);
    ElementSetText(e, text);
    ElementAppendChild(parent, e);
    return e;
}

static const char *CSS =
    "Root { background-color: #3a3d33; padding: 20px; }"
    "#savegame-panel { width: 420px; background-color: #3a3d33; }"
    "Select { width: 420px; height: 28px; background-color: #2c2e26; border: 1px solid #16170f;"
    "         color: #d99a2b; font-size: 13px; text-align: center; }"
    ".btn-row { display: flex; flex-direction: row; gap: 8px; margin-top: 8px; }"
    "Button { flex-grow: 1; background-color: #4b4f3e; color: #b9bcae; font-size: 12px; padding: 8px 0; "
    "         border: 1px solid #16170f; text-align: center; }"
    "Button.enabled { color: #eceade; background-color: #5c6049; }";

int main(void) {
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(460, 140, "acss game-ui demo 3 -- VGUI save-game panel layout recreation");
    SetTargetFPS(60);

    Document *doc = DocumentCreate();

    Element *panel = Div(doc, doc->root, "");
    panel->id = "savegame-panel";

    Element *saveSelect = ElementCreate(doc, ELEMENT_SELECT, "");
    ElementAppendChild(panel, saveSelect);
    ElementAddOption(saveSelect, "QUICK SAVE");
    ElementAddOption(saveSelect, "autosave01");
    ElementAddOption(saveSelect, "chapter3_save");
    saveSelect->selectedIndex = 0;

    Element *row = Div(doc, panel, "btn-row");
    Btn(doc, row, "", "Delete");
    Btn(doc, row, "enabled", "Load");
    Btn(doc, row, "enabled", "Cancel");

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
