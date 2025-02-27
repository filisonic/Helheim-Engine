#pragma once
#include "Globals.h"
#include "Module.h"

class ModuleOpenGL;
class ModuleWindow;
class ModuleInput;
class ModuleScene;
class ModuleFileSystem;
class ModuleCamera;
class ModuleResource;
class ModuleUI;
class ModuleDetourNavigation;
class ModuleAudio;
class ModuleEvent;
class ModuleScriptManager;
class ModulePhysics;

class Timer;

class ENGINE_API Application
{
public:
    Application();
    ~Application();


    ModuleOpenGL* GetOpenGL() { return render; }
    ModuleWindow* GetWindow() { return window; }
    ModuleInput*  GetInput() { return input; }
    ModuleCamera* GetCamera() { return camera;  }
    ModuleFileSystem* GetFileSystem() { return fileSystem; }
    ModuleScene* GetScene() { return scene; }
    ModuleUI* GetUI() { return ui; }
    ModuleResource* GetResource() { return resource; }
    ModuleDetourNavigation* GetNavigation() { return navigation; }
    ModuleAudio* GetAudio() { return audio; }
    ModuleEvent* GetEvent() { return event; }
    ModuleScriptManager* GetScriptManager() { return scriptManager; }
    ModulePhysics* GetPhysics() { return physics; }

    Timer* GetCurrentClock() const { return mCurrentTimer; }
    float GetDt() const;

    bool IsPlayMode() { return mIsPlayMode; }
    void Exit() { mExit = true; }

protected:
    ModuleOpenGL* render = nullptr;
    ModuleWindow* window = nullptr;
    ModuleInput* input = nullptr;
    ModuleFileSystem* fileSystem = nullptr;
    ModuleCamera* camera = nullptr;
    ModuleScene* scene = nullptr;
    ModuleResource* resource = nullptr;
    ModuleAudio* audio = nullptr;
    ModuleUI* ui = nullptr;
    ModuleDetourNavigation* navigation = nullptr;
    ModuleEvent* event = nullptr;
    ModuleScriptManager* scriptManager = nullptr;
    ModulePhysics* physics = nullptr;

    Timer* mCurrentTimer = nullptr;
    bool mEnableVsync = true;
    bool mIsPlayMode = false;
    bool mExit = false;
};

extern ENGINE_API Application* App;