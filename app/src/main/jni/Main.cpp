#include <list>
#include <vector>
#include <string.h>
#include <pthread.h>
#include <thread>
#include <cstring>
#include <jni.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <dlfcn.h>
#include "Includes/Logger.h"
#include "Includes/obfuscate.h"
#include "Includes/Utils.h"
#include "KittyMemory/MemoryPatch.h"
#include "Menu/Setup.h"
#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include "imgui.h"
#include "imgui_internal.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_android.h"
#include "ByNameModding/BNM.hpp"
#include "Unity/Vector2.h"
#include "Unity/Vector3.h"
#include "Unity/Rect.h"
#include "Unity/Quaternion.h"
#include "offsets.h"
#include "Drawing.h"
#include "bools.h"
#include "hooks.h"
int  glWidth, glHeight;
#include "EspManager.h"
ESPManager *espManager;
#include "DrawMenu.h"





#define Hook(offset,newptr,oldptr) MSHookFunction((void*)getAbsoluteAddress("libil2cpp.so",offset),(void*)newptr,(void**)&oldptr)
using namespace BNM;

auto getClass(const char *C) {
   auto clasz = LoadClass("", C);
   return clasz;
}
auto getClass(const char *N, const char *C) {
   auto clasz = LoadClass(N, C);
   return clasz;
}

uintptr_t getOffset(LoadClass clasz, const char *M, int param = 0) {
    uintptr_t offset = clasz.GetMethodOffsetByName(M, param);
    return offset;
}

uintptr_t getOffset(LoadClass clasz, const char *M, std::vector<string>params_names) {
    uintptr_t offset = clasz.GetMethodOffsetByName(M, params_names);
    return offset;
}
uintptr_t address = 0;
//Target lib here
#define targetLibName OBFUSCATE("libil2cpp.so")
#include "Includes/Macros.h"


#define HOOK(ret, func, ...) \
    ret (*orig##func)(__VA_ARGS__); \
    ret my##func(__VA_ARGS__)

HOOK(void, Input, void *thiz, void *ex_ab, void *ex_ac){
    origInput(thiz, ex_ab, ex_ac);
    ImGui_ImplAndroid_HandleInputEvent((AInputEvent *)thiz);
    return;
}



///PATCHIMG///
struct Patches{
MemoryPatch x;
}hexPatches;





void *enemyPlayer = NULL;
void (*old_PlayerUpdate)(void *player);
void _PlayerUpdate(void *player)
         {
   if (player != NULL) 
      {
 if (Esp)
     {
      espManager->tryAddEnemy(player);
      }
   }
old_PlayerUpdate(player);
}
 

//Add Bool Name In bool.h Such Test

int(*old_example)(void *player);
int Example(void *player) {
    if(player != NULL) {
        if(Test) {
            return 696969696969; // your hooking Value
        }
    }
    return old_example(player);  
}
















void SetupImgui() {
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();    
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
	io.DisplaySize = ImVec2((float)glWidth, (float)glHeight);
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    // Setup Platform/Renderer backends
    ImGui_ImplOpenGL3_Init("#version 100");
    // We load the default font with increased size to improve readability on many devices with "high" DPI.
    ImFontConfig font_cfg;
    font_cfg.SizePixels = 22.0f;
    io.Fonts->AddFontDefault(&font_cfg);
    // Arbitrary scale-up
    ImGui::GetStyle().ScaleAllSizes(3.0f);
}

bool clearMousePos = true, setup = false;




EGLBoolean (*old_eglSwapBuffers)(EGLDisplay dpy, EGLSurface surface);
EGLBoolean hook_eglSwapBuffers(EGLDisplay dpy, EGLSurface surface) {
 eglQuerySurface(dpy, surface, EGL_WIDTH, &glWidth);
    eglQuerySurface(dpy, surface, EGL_HEIGHT, &glHeight);

	if (!setup) {
        SetupImgui();
        setup = true;
    }

    ImGuiIO &io = ImGui::GetIO();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();
    DrawMenu();
    DrawESP();
    //Rendering
    ImGui::EndFrame();
    ImGui::Render();
    glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (clearMousePos) {
        io.MousePos = ImVec2(-1, -1);
        clearMousePos = false;
    }

    return old_eglSwapBuffers(dpy, surface);
}





void *imgui_go(void *) {
    sleep(2);
    espManager = new ESPManager();
    address = findLibrary(targetLibName);
    auto addr = (uintptr_t)dlsym(RTLD_NEXT, "eglSwapBuffers"); 
   //Lets hook to the egl
    DobbyHook((void *)addr, (void *)hook_eglSwapBuffers, (void **)&old_eglSwapBuffers);

    
    MSHookFunction((void *)getAbsoluteAddress("libil2cpp.so", 0x45FDE8), (void *) _PlayerUpdate, (void **) &old_PlayerUpdate); 




DobbyHook((void *)getAbsoluteAddress("libil2cpp.so", 0x45FDE8), (void *) Example, (void **) &old_example); 

//And If You Want Add Toggle Then Go To The DrawMenu.h
//Use Dobbyhook For Hooking 
   
    pthread_exit(nullptr);
    return nullptr;


}


__attribute__((constructor))
void lib_main() {
    
    // Create a new thread so it does not block the main thread, means the game would not freeze
    pthread_t ptid;
    pthread_create(&ptid, NULL, imgui_go, NULL);
    
}

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void * reserved)
{
    JNIEnv *env;
    vm->GetEnv((void **) &env, JNI_VERSION_1_6);

    void *sym_input = DobbySymbolResolver(("/system/lib/libinput.so"), ("_ZN7android13InputConsumer21initializeMotionEventEPNS_11MotionEventEPKNS_12InputMessageE"));
    if (NULL != sym_input){
        DobbyHook((void *)sym_input, (void *) myInput, (void **)&origInput);
    }
    return JNI_VERSION_1_6;
}
