#include "MainMenu.h"
#include "GameObject.h"
#include "Application.h"
#include "ModuleScene.h"
#include "ModuleInput.h"
#include "Keys.h"
#include "ModuleAudio.h"
#include "ScriptComponent.h"
#include "Transform2DComponent.h"
#include "ButtonComponent.h"
#include "ImageComponent.h"
#include "SliderComponent.h"
#include "Resource.h"
#include "ModuleResource.h"
#include "TextComponent.h"
#include "Timer.h"
#include "ModuleWindow.h"
#include "AudioManager.h"

CREATE(MainMenu)
{
    CLASS(owner);

    SEPARATOR("MENUS");
    MEMBER(MemberType::GAMEOBJECT, mSplashScreen);
    MEMBER(MemberType::GAMEOBJECT, mStudioScreen);
    MEMBER(MemberType::GAMEOBJECT, mEngineScreen);
    MEMBER(MemberType::GAMEOBJECT, mLoadingScreen);
    MEMBER(MemberType::GAMEOBJECT, mLoadingSliderGO);

    MEMBER(MemberType::GAMEOBJECT, mMainMenu);
    MEMBER(MemberType::GAMEOBJECT, mOptionsMenu);
    MEMBER(MemberType::GAMEOBJECT, mCreditsMenu);
    MEMBER(MemberType::GAMEOBJECT, mCreditsListText);
    MEMBER(MemberType::GAMEOBJECT, mOptionsContainerGO);

    SEPARATOR("SETTINGS");
	MEMBER(MemberType::GAMEOBJECT, mGeneralVolumeSliderGO);
    MEMBER(MemberType::GAMEOBJECT, mGeneralVolumeFillGO);
    MEMBER(MemberType::GAMEOBJECT, mMusicVolumeSliderGO);
    MEMBER(MemberType::GAMEOBJECT, mMusicVolumeFillGO);
    MEMBER(MemberType::GAMEOBJECT, mEffectsVolumeSliderGO);
    MEMBER(MemberType::GAMEOBJECT, mEffectsVolumeFillGO);
    MEMBER(MemberType::GAMEOBJECT, mVSyncButtonOffGO);
    MEMBER(MemberType::GAMEOBJECT, mVSyncButtonOnGO);
    MEMBER(MemberType::GAMEOBJECT, mVSyncImageOn_On);
    MEMBER(MemberType::GAMEOBJECT, mVSyncImageOff_On);
    MEMBER(MemberType::GAMEOBJECT, mFullscreenButtonOnGO);
    MEMBER(MemberType::GAMEOBJECT, mFullscreenButtonOffGO);
    MEMBER(MemberType::GAMEOBJECT, mFullscreenImageOn_On);
    MEMBER(MemberType::GAMEOBJECT, mFullscreenImageOff_On);

    SEPARATOR("Play Btn");
    MEMBER(MemberType::GAMEOBJECT, mPlayGO);
    MEMBER(MemberType::GAMEOBJECT, mPlayText);
    MEMBER(MemberType::GAMEOBJECT, mPlayHover);
    MEMBER(MemberType::GAMEOBJECT, mPlayClicked);

    SEPARATOR("Options Btn");
    MEMBER(MemberType::GAMEOBJECT, mOptionsGO);
    MEMBER(MemberType::GAMEOBJECT, mOptionsText);
    MEMBER(MemberType::GAMEOBJECT, mOptionsHover);
    MEMBER(MemberType::GAMEOBJECT, mOptionsClicked);

    SEPARATOR("Credits Btn");
    MEMBER(MemberType::GAMEOBJECT, mCreditsGO);
    MEMBER(MemberType::GAMEOBJECT, mCreditsText);
    MEMBER(MemberType::GAMEOBJECT, mCreditsHover);
    MEMBER(MemberType::GAMEOBJECT, mCreditsClicked);

    SEPARATOR("Quit Btn");
    MEMBER(MemberType::GAMEOBJECT, mQuitGO);
    MEMBER(MemberType::GAMEOBJECT, mQuitText);
    MEMBER(MemberType::GAMEOBJECT, mQuitHover);
    MEMBER(MemberType::GAMEOBJECT, mQuitClicked);

    SEPARATOR("Keyboard Btn");
    MEMBER(MemberType::GAMEOBJECT, mKeyboardGO);
    MEMBER(MemberType::GAMEOBJECT, mKeyboardText);
    MEMBER(MemberType::GAMEOBJECT, mKeyboardHover);
    MEMBER(MemberType::GAMEOBJECT, mKeyboardClicked);

    SEPARATOR("Controller Btn");
    MEMBER(MemberType::GAMEOBJECT, mControllerGO);
    MEMBER(MemberType::GAMEOBJECT, mControllerText);
    MEMBER(MemberType::GAMEOBJECT, mControllerHover);
    MEMBER(MemberType::GAMEOBJECT, mControllerClicked);

    SEPARATOR("Audio Btn");
    MEMBER(MemberType::GAMEOBJECT, mAudioGO);
    MEMBER(MemberType::GAMEOBJECT, mAudioText);
    MEMBER(MemberType::GAMEOBJECT, mAudioHover);
    MEMBER(MemberType::GAMEOBJECT, mAudioClicked);

    SEPARATOR("Settings Btn");
    MEMBER(MemberType::GAMEOBJECT, mSettingsGO);
    MEMBER(MemberType::GAMEOBJECT, mSettingsText);
    MEMBER(MemberType::GAMEOBJECT, mSettingsHover);
    MEMBER(MemberType::GAMEOBJECT, mSettingsClicked);

    SEPARATOR("Options Screens");
    MEMBER(MemberType::GAMEOBJECT, mControlsScreenGO);
    MEMBER(MemberType::GAMEOBJECT, mSettingsScreenGO);
    MEMBER(MemberType::GAMEOBJECT, mAudioScreenGO);
    MEMBER(MemberType::GAMEOBJECT, mKeyboardScreenGO);

    SEPARATOR("Audio buttons");
    MEMBER(MemberType::GAMEOBJECT, mGeneralVolumeUp);
    MEMBER(MemberType::GAMEOBJECT, mGeneralVolumeDown);
    MEMBER(MemberType::GAMEOBJECT, mMusicVolumeUp);
    MEMBER(MemberType::GAMEOBJECT, mMusicVolumeDown);
    MEMBER(MemberType::GAMEOBJECT, mEffectsVolumeUp);
    MEMBER(MemberType::GAMEOBJECT, mEffectsVolumeDown);

    SEPARATOR("OTHERS");
    MEMBER(MemberType::GAMEOBJECT, mAudioManagerGO);

    END_CREATE;
}

MainMenu::MainMenu(GameObject* owner) : Script(owner) {}

void MainMenu::Start() 
{
    mSplashButton = static_cast<ButtonComponent*>(mSplashScreen->GetComponent(ComponentType::BUTTON));
    mSplashButton->AddEventHandler(EventType::CLICK, new std::function<void()>(std::bind(&MainMenu::OnSplashButtonClick, this)));

    // Main buttons

    mPlayButton = static_cast<ButtonComponent*>(mPlayGO->GetComponent(ComponentType::BUTTON));
    mPlayButton->AddEventHandler(EventType::CLICK, new std::function<void()>(std::bind(&MainMenu::OnPlayButtonClick, this)));
    mPlayButton->AddEventHandler(EventType::HOVER, new std::function<void()>(std::bind(&MainMenu::OnPlayButtonHover, this)));
    mPlayButton->AddEventHandler(EventType::HOVEROFF, new std::function<void()>(std::bind(&MainMenu::OnPlayButtonHoverOff, this)));

    mOptionsButton = static_cast<ButtonComponent*>(mOptionsGO->GetComponent(ComponentType::BUTTON));
    mOptionsButton->AddEventHandler(EventType::CLICK, new std::function<void()>(std::bind(&MainMenu::OnOptionsButtonClick, this)));
    mOptionsButton->AddEventHandler(EventType::HOVER, new std::function<void()>(std::bind(&MainMenu::OnOptionsButtonHover, this)));
    mOptionsButton->AddEventHandler(EventType::HOVEROFF, new std::function<void()>(std::bind(&MainMenu::OnOptionsButtonHoverOff, this)));

    mCreditsButton = static_cast<ButtonComponent*>(mCreditsGO->GetComponent(ComponentType::BUTTON));
    mCreditsButton->AddEventHandler(EventType::CLICK, new std::function<void()>(std::bind(&MainMenu::OnCreditsButtonClick, this)));
    mCreditsButton->AddEventHandler(EventType::HOVER, new std::function<void()>(std::bind(&MainMenu::OnCreditsButtonHover, this)));
    mCreditsButton->AddEventHandler(EventType::HOVEROFF, new std::function<void()>(std::bind(&MainMenu::OnCreditsButtonHoverOff, this)));

    mQuitButton = static_cast<ButtonComponent*>(mQuitGO->GetComponent(ComponentType::BUTTON));
    mQuitButton->AddEventHandler(EventType::CLICK, new std::function<void()>(std::bind(&MainMenu::OnQuitButtonClick, this)));
    mQuitButton->AddEventHandler(EventType::HOVER, new std::function<void()>(std::bind(&MainMenu::OnQuitButtonHover, this)));
    mQuitButton->AddEventHandler(EventType::HOVEROFF, new std::function<void()>(std::bind(&MainMenu::OnQuitButtonHoverOff, this)));

    // Options buttons

    mSettingsButton = static_cast<ButtonComponent*>(mSettingsGO->GetComponent(ComponentType::BUTTON));
    mSettingsButton->AddEventHandler(EventType::CLICK, new std::function<void()>(std::bind(&MainMenu::OnSettingsButtonClick, this)));
    mSettingsButton->AddEventHandler(EventType::HOVER, new std::function<void()>(std::bind(&MainMenu::OnSettingsButtonHover, this)));
    mSettingsButton->AddEventHandler(EventType::HOVEROFF, new std::function<void()>(std::bind(&MainMenu::OnSettingsButtonHoverOff, this)));

    mControllerButton = static_cast<ButtonComponent*>(mControllerGO->GetComponent(ComponentType::BUTTON));
    mControllerButton->AddEventHandler(EventType::CLICK, new std::function<void()>(std::bind(&MainMenu::OnControllerButtonClick, this)));
    mControllerButton->AddEventHandler(EventType::HOVER, new std::function<void()>(std::bind(&MainMenu::OnControllerButtonHover, this)));
    mControllerButton->AddEventHandler(EventType::HOVEROFF, new std::function<void()>(std::bind(&MainMenu::OnControllerButtonHoverOff, this)));

    mAudioButton = static_cast<ButtonComponent*>(mAudioGO->GetComponent(ComponentType::BUTTON));
    mAudioButton->AddEventHandler(EventType::CLICK, new std::function<void()>(std::bind(&MainMenu::OnAudioButtonClick, this)));
    mAudioButton->AddEventHandler(EventType::HOVER, new std::function<void()>(std::bind(&MainMenu::OnAudioButtonHover, this)));
    mAudioButton->AddEventHandler(EventType::HOVEROFF, new std::function<void()>(std::bind(&MainMenu::OnAudioButtonHoverOff, this)));

    mKeyboardButton = static_cast<ButtonComponent*>(mKeyboardGO->GetComponent(ComponentType::BUTTON));
    mKeyboardButton->AddEventHandler(EventType::CLICK, new std::function<void()>(std::bind(&MainMenu::OnKeyboardButtonClick, this)));
    mKeyboardButton->AddEventHandler(EventType::HOVER, new std::function<void()>(std::bind(&MainMenu::OnKeyboardButtonHover, this)));
    mKeyboardButton->AddEventHandler(EventType::HOVEROFF, new std::function<void()>(std::bind(&MainMenu::OnKeyboardButtonHoverOff, this)));

    // Others

    mTextTransform = static_cast<Transform2DComponent*>(mCreditsListText->GetComponent(ComponentType::TRANSFORM2D));

    static_cast<ButtonComponent*>(mGeneralVolumeUp->GetComponent(ComponentType::BUTTON))
        ->AddEventHandler(EventType::CLICK, new std::function<void()>(std::bind(&MainMenu::OnGeneralUp, this)));
    static_cast<ButtonComponent*>(mGeneralVolumeDown->GetComponent(ComponentType::BUTTON))
        ->AddEventHandler(EventType::CLICK, new std::function<void()>(std::bind(&MainMenu::OnGeneralDown, this)));
    static_cast<ButtonComponent*>(mMusicVolumeUp->GetComponent(ComponentType::BUTTON))
        ->AddEventHandler(EventType::CLICK, new std::function<void()>(std::bind(&MainMenu::OnMusicUp, this)));
    static_cast<ButtonComponent*>(mMusicVolumeDown->GetComponent(ComponentType::BUTTON))
        ->AddEventHandler(EventType::CLICK, new std::function<void()>(std::bind(&MainMenu::OnMusicDown, this)));
    static_cast<ButtonComponent*>(mEffectsVolumeUp->GetComponent(ComponentType::BUTTON))
        ->AddEventHandler(EventType::CLICK, new std::function<void()>(std::bind(&MainMenu::OnEffectsUp, this)));
    static_cast<ButtonComponent*>(mEffectsVolumeDown->GetComponent(ComponentType::BUTTON))
        ->AddEventHandler(EventType::CLICK, new std::function<void()>(std::bind(&MainMenu::OnEffectsDown, this)));

    mGeneralVolumeSlider = static_cast<SliderComponent*>(mGeneralVolumeSliderGO->GetComponent(ComponentType::SLIDER));
    mGeneralVolumeFill = static_cast<ImageComponent*>(mGeneralVolumeFillGO->GetComponent(ComponentType::IMAGE));
    mMusicVolumeSlider = static_cast<SliderComponent*>(mMusicVolumeSliderGO->GetComponent(ComponentType::SLIDER));
    mMusicVolumeFill = static_cast<ImageComponent*>(mMusicVolumeFillGO->GetComponent(ComponentType::IMAGE));
    mEffectsVolumeSlider = static_cast<SliderComponent*>(mEffectsVolumeSliderGO->GetComponent(ComponentType::SLIDER));
    mEffectsVolumeFill = static_cast<ImageComponent*>(mEffectsVolumeFillGO->GetComponent(ComponentType::IMAGE));

    mVSyncOnButton = static_cast<ButtonComponent*>(mVSyncButtonOnGO->GetComponent(ComponentType::BUTTON));
    mVSyncOffButton = static_cast<ButtonComponent*>(mVSyncButtonOffGO->GetComponent(ComponentType::BUTTON));
    mFullscreenOnButton = static_cast<ButtonComponent*>(mFullscreenButtonOnGO->GetComponent(ComponentType::BUTTON));
    mFullscreenOffButton = static_cast<ButtonComponent*>(mFullscreenButtonOffGO->GetComponent(ComponentType::BUTTON));

    mVSyncOnButton->AddEventHandler(EventType::CLICK, new std::function<void()>(std::bind(&MainMenu::OnVSyncButtonOnClick, this)));
    mVSyncOffButton->AddEventHandler(EventType::CLICK, new std::function<void()>(std::bind(&MainMenu::OnVSyncButtonOffClick, this)));
    mFullscreenOnButton->AddEventHandler(EventType::CLICK, new std::function<void()>(std::bind(&MainMenu::OnFullscreenButtonOnClick, this)));
    mFullscreenOffButton->AddEventHandler(EventType::CLICK, new std::function<void()>(std::bind(&MainMenu::OnFullscreenButtonOffClick, this)));

    if (mAudioManagerGO)
    {
        ScriptComponent* script = static_cast<ScriptComponent*>(mAudioManagerGO->GetComponent(ComponentType::SCRIPT));
        mAudioManager = static_cast<AudioManager*>(script->GetScriptInstance());
        mBGMID = mAudioManager->Play(BGM::MAINMENU);
    }

    mLoadingSlider = static_cast<SliderComponent*>(mLoadingSliderGO->GetComponent(ComponentType::SLIDER));
    mLoadingSlider->SetValue(0.01f);

    // Init the volume setting sliders
    App->GetAudio()->SetVolume("bus:/", mGeneralVolumeValue);
    mGeneralVolumeSlider->SetValue(mGeneralVolumeValue);
    App->GetAudio()->SetVolume("bus:/music", mMusicVolumeValue);
    mMusicVolumeSlider->SetValue(mMusicVolumeValue);
    App->GetAudio()->SetVolume("bus:/sfx", mEffectsVolumeValue);
    mEffectsVolumeSlider->SetValue(mEffectsVolumeValue);


    OpenMenu(MENU_TYPE::STUDIO);
}

void MainMenu::Update()
{
    if (mStudioBool) 
    {
        if (mStudioTimer.DelayWithoutReset(1.5f))
        {
            OpenMenu(MENU_TYPE::ENGINE);
            mStudioBool = false;
            return;
        }
        else return;
    }
        
    if (mEngineBool) 
    {
        if (mEngineTimer.DelayWithoutReset(1.5f))
        {
            OpenMenu(MENU_TYPE::SPLASH);
            mEngineBool = false;
            return;
        }
        else return;
    }
        
    if (mIsInitial) 
    {
        if (App->GetInput()->GetKeyboardReciveInputs() ||
            App->GetInput()->GetGameControllerReceivedInputs() ||
            App->GetInput()->GetMouseRecieveInputs()) 
        {
            mIsInitial = false;
            OpenMenu(MENU_TYPE::MAIN);
            OnPlayButtonHover(); // Hover first option when the menu is first laoded    
            OnKeyboardButtonHover(); // Pre-hover the first option
            return;
        }
        else return;
    }

    Controls();
        
    /*if (mIsScrolling)
    {
        float3 currentPosition = mTextTransform->GetPosition();
        if (currentPosition.y > 3400.0f) mTextTransform->SetPosition(float3(currentPosition.x, -500.0f, currentPosition.z));
        else mTextTransform->SetPosition(float3(currentPosition.x, currentPosition.y + 200 * App->GetDt(), currentPosition.z));
    }*/

    if (mLoadlevel == true && mTimer.Delay(1.25f))
    {
        mAudioManager->Release(BGM::MAINMENU, mBGMID);
        App->GetScene()->Load("Assets/Scenes/Level1Scene");
    }
    else if (mLoadlevel == true)
    {
        if (mLoadingSlider->GetValue() < 1)
        mLoadingSlider->SetValue(mLoadingSlider->GetValue() + 0.01);
    }

}

void MainMenu::Controls()
{
    if (App->GetInput()->GetKey(Keys::Keys_UP) == KeyState::KEY_DOWN ||
        App->GetInput()->GetGameControllerButton(ControllerButton::SDL_CONTROLLER_BUTTON_DPAD_UP) == ButtonState::BUTTON_DOWN) 
    {
        mAudioManager->PlayOneShot(SFX::MAINMENU_SELECT);
        if (mCurrentMenu == MENU_TYPE::MAIN) // MENU MAIN BUTTONS
        { 
            if (mOption > 0)
            {
                mOption--;
            }
            else
            {
                mOption = 3;
            }
            HoverMenu(static_cast<MENU_TYPE>(mOption));
        }
        else if (mCurrentMenu == MENU_TYPE::OPTIONS)
        {
            if (mSettingOption > 7)
            {
                mSettingOption--;
            }
            else
            {
                mSettingOption = 10;
            }
            HoverSubMenu(static_cast<MENU_TYPE>(mSettingOption));
        }
        else if (mCurrentMenu == MENU_TYPE::SETTINGS)
        {
            if (mSubsettingOption > 0)
            {
                mSubsettingOption--;
            }
            else
            {
                mSubsettingOption = 4;
            }
            HoverSubSubMenu(static_cast<SETTING_TYPE>(mSubsettingOption));
        }
    }

    if (App->GetInput()->GetKey(Keys::Keys_DOWN) == KeyState::KEY_DOWN ||
        App->GetInput()->GetGameControllerButton(ControllerButton::SDL_CONTROLLER_BUTTON_DPAD_DOWN) == ButtonState::BUTTON_DOWN)
    {
        mAudioManager->PlayOneShot(SFX::MAINMENU_SELECT);
        if (mCurrentMenu == MENU_TYPE::MAIN) // MENU MAIN BUTTONS
        {
            if (mOption < 3)
            {
                mOption++;
            }
            else
            {
                mOption = 0;
            }
            HoverMenu(static_cast<MENU_TYPE>(mOption));
        }
        else if (mCurrentMenu == MENU_TYPE::OPTIONS)
        {
            if (mSettingOption < 10)

            {
                mSettingOption++;
            }
            else
            {
                mSettingOption = 7;
            }
            HoverSubMenu(static_cast<MENU_TYPE>(mSettingOption));
        }
        else if (mCurrentMenu == MENU_TYPE::SETTINGS) 
        {
            if (mSubsettingOption < 4)
            {
                mSubsettingOption++;
            }
            else
            {
                mSubsettingOption = 0;
            }
                HoverSubSubMenu(static_cast<SETTING_TYPE>(mSubsettingOption));
        }
    }

    if (App->GetInput()->GetKey(Keys::Keys_RETURN) == KeyState::KEY_DOWN || 
        App->GetInput()->GetKey(Keys::Keys_KP_ENTER) == KeyState::KEY_DOWN ||
        App->GetInput()->GetGameControllerButton(ControllerButton::SDL_CONTROLLER_BUTTON_A) == ButtonState::BUTTON_DOWN)
    {

        if (mCurrentMenu == MENU_TYPE::MAIN)
        {
            mAudioManager->PlayOneShot(SFX::MAINMENU_OK);

            ClickMenu(static_cast<MENU_TYPE>(mOption));
        } 
        else if (mCurrentMenu == MENU_TYPE::OPTIONS)
        {
            mAudioManager->PlayOneShot(SFX::MAINMENU_OK);

            OpenMenu(static_cast<MENU_TYPE>(mSettingOption));
        }
        else if (mCurrentMenu == MENU_TYPE::SETTINGS)
        {
            if (mCurrentSetting == SETTING_TYPE::VSYNC)
            {
                OnVSyncButtonOnClick();
            }
            else if (mCurrentSetting == SETTING_TYPE::FULL_SCREEN)
            {
				OnFullscreenButtonOnClick();
            }
            
        }
    }

    if (App->GetInput()->GetKey(Keys::Keys_LEFT) == KeyState::KEY_DOWN ||
        App->GetInput()->GetGameControllerButton(ControllerButton::SDL_CONTROLLER_BUTTON_DPAD_LEFT) == ButtonState::BUTTON_DOWN)
    {
        if (mCurrentMenu == MENU_TYPE::SETTINGS)
        {
            OnSlide(static_cast<SETTING_TYPE>(mSubsettingOption), DIRECTION::LEFT, 0.01f);
        }
    }

    if (App->GetInput()->GetKey(Keys::Keys_RIGHT) == KeyState::KEY_DOWN ||
        App->GetInput()->GetGameControllerButton(ControllerButton::SDL_CONTROLLER_BUTTON_DPAD_RIGHT) == ButtonState::BUTTON_DOWN)
    {
        if (mCurrentMenu == MENU_TYPE::SETTINGS)
        {
            OnSlide(static_cast<SETTING_TYPE>(mSubsettingOption), DIRECTION::RIGHT, 0.01f);
        }
        
    }

    //TODO: Implement a way to increase/decrease x10 using the keyboard also
    if (App->GetInput()->GetGameControllerButton(ControllerButton::SDL_CONTROLLER_BUTTON_RIGHTSHOULDER) == ButtonState::BUTTON_DOWN)
    {
        if (mCurrentMenu == MENU_TYPE::SETTINGS)
        {
            OnSlide(static_cast<SETTING_TYPE>(mSubsettingOption), DIRECTION::RIGHT, 0.1f);
        }

    }

    if (App->GetInput()->GetGameControllerButton(ControllerButton::SDL_CONTROLLER_BUTTON_LEFTSHOULDER) == ButtonState::BUTTON_DOWN)
    {
        if (mCurrentMenu == MENU_TYPE::SETTINGS)
        {
            OnSlide(static_cast<SETTING_TYPE>(mSubsettingOption), DIRECTION::LEFT, 0.1f);
        }

    }



    if (App->GetInput()->GetKey(Keys::Keys_ESCAPE) == KeyState::KEY_DOWN ||
        App->GetInput()->GetGameControllerButton(ControllerButton::SDL_CONTROLLER_BUTTON_B) == ButtonState::BUTTON_DOWN)
    {
        mAudioManager->PlayOneShot(SFX::MAINMENU_CANCEL);
        if (mCurrentMenu == MENU_TYPE::SETTINGS || mCurrentMenu == MENU_TYPE::CONTROLS || mCurrentMenu == MENU_TYPE::AUDIO || mCurrentMenu == MENU_TYPE::KEYBOARD )
        {
			if (mCurrentMenu == MENU_TYPE::SETTINGS)
            {
                mSubsettingOption = 3;
                mSettingsClicked->SetEnabled(false);
                OnSettingsButtonHover();
            }
            else if (mCurrentMenu == MENU_TYPE::CONTROLS) 
            {
                mSubsettingOption = 1;
                mControllerClicked->SetEnabled(false);
                OnControllerButtonHover();
            }
            else if (mCurrentMenu == MENU_TYPE::AUDIO)
            {
                mSubsettingOption = 2;
                mAudioClicked->SetEnabled(false);
                OnAudioButtonHover();
            }
            else if (mCurrentMenu == MENU_TYPE::KEYBOARD)
            {
                mSubsettingOption = 0;
                mKeyboardClicked->SetEnabled(false);
                OnKeyboardButtonHover();
            }
            OpenMenu(MENU_TYPE::OPTIONS);
        }
		else
        {
            mOptionsClicked->SetEnabled(false);
            mCreditsClicked->SetEnabled(false);
			OpenMenu(MENU_TYPE::MAIN);
		}
    }
}

// MENUS

void MainMenu::OpenMenu(MENU_TYPE type) 
{
    mCurrentMenu = type;

    mEngineScreen->SetEnabled(false);
    mStudioScreen->SetEnabled(false);
    mSplashScreen->SetEnabled(false);
    mLoadingScreen->SetEnabled(false);

    mOptionsMenu->SetEnabled(false);
    mCreditsMenu->SetEnabled(false);

    mSettingsScreenGO->SetEnabled(false);
    mControlsScreenGO->SetEnabled(false);
    mOptionsContainerGO->SetEnabled(false);
    mAudioScreenGO->SetEnabled(false);
    mKeyboardScreenGO->SetEnabled(false);

    mIsScrolling = false;


    switch (type) 
    {
        case MENU_TYPE::MAIN:
            mMainMenu->SetEnabled(true);
            break;
        case MENU_TYPE::OPTIONS:
            mOptionsMenu->SetEnabled(true);
            mOptionsContainerGO->SetEnabled(true);
            mOptionsClicked->SetEnabled(true);
            mCreditsClicked->SetEnabled(false);
            break;
        case MENU_TYPE::CREDITS:
            mCreditsMenu->SetEnabled(true);
            mIsScrolling = true;
            //mTextTransform->SetPosition(float3(mTextTransform->GetPosition().x, 0, mTextTransform->GetPosition().z));
            mOptionsClicked->SetEnabled(false);
            mCreditsClicked->SetEnabled(true);
            break;
        case MENU_TYPE::LOADING:
            mLoadingScreen->SetEnabled(true);
            break;
        case MENU_TYPE::SPLASH:
            mSplashScreen->SetEnabled(true);
            break;
        case MENU_TYPE::ENGINE:
            mEngineScreen->SetEnabled(true);
            break;
        case MENU_TYPE::STUDIO:
            mStudioScreen->SetEnabled(true);
            break;
        case MENU_TYPE::CONTROLS:
            mOptionsMenu->SetEnabled(true);
            mOptionsContainerGO->SetEnabled(true);
            mControlsScreenGO->SetEnabled(true);
            mControllerClicked->SetEnabled(true);
            mAudioClicked->SetEnabled(false);
            mKeyboardClicked->SetEnabled(false);
            mSettingsClicked->SetEnabled(false);
            break;
        case MENU_TYPE::AUDIO:
            mOptionsMenu->SetEnabled(true);
            mOptionsContainerGO->SetEnabled(true);
            mAudioScreenGO->SetEnabled(true);
            mControllerClicked->SetEnabled(false);
            mAudioClicked->SetEnabled(true);
            mKeyboardClicked->SetEnabled(false);
            mSettingsClicked->SetEnabled(false);
            break;
        case MENU_TYPE::KEYBOARD:
            mOptionsMenu->SetEnabled(true);
            mOptionsContainerGO->SetEnabled(true);
            mKeyboardScreenGO->SetEnabled(true);
            mControllerClicked->SetEnabled(false);
            mAudioClicked->SetEnabled(false);
            mKeyboardClicked->SetEnabled(true);
            mSettingsClicked->SetEnabled(false);
            break;
        case MENU_TYPE::SETTINGS:
            mOptionsMenu->SetEnabled(true);
            mOptionsContainerGO->SetEnabled(true);
            mSettingsScreenGO->SetEnabled(true);
            mControllerClicked->SetEnabled(false);
            mAudioClicked->SetEnabled(false);
            mKeyboardClicked->SetEnabled(false);
            mSettingsClicked->SetEnabled(true);
            OnGeneralVolumeHover(); // Hover the first button
            break;
    }
}

// CLICKS

void MainMenu::ClickMenu(MENU_TYPE type)
{
    if (mSplashScreen->IsActive())
    {
        OnSplashButtonClick();
        return;
    }

    switch (type) {
    case MENU_TYPE::MAIN:
        OnPlayButtonClick();
        break;
    case MENU_TYPE::OPTIONS:
        OnOptionsButtonClick();
        break;
    case MENU_TYPE::CREDITS:
        OnCreditsButtonClick();
        break;
    case MENU_TYPE::LOADING:
        OnQuitButtonClick();
        break;
    }
}

void MainMenu::OnMainButtonClick() 
{
    OpenMenu(MENU_TYPE::MAIN);
}

void MainMenu::OnQuitButtonClick() {
    App->Exit();
    exit(0);
}

void MainMenu::OnOptionsButtonClick() 
{
    OpenMenu(MENU_TYPE::OPTIONS);
}

void MainMenu::OnCreditsButtonClick() 
{
    OpenMenu(MENU_TYPE::CREDITS);
}

void MainMenu::OnPlayButtonClick() 
{
    mAudioManager->PlayOneShot(SFX::MAINMENU_START);
    OpenMenu(MENU_TYPE::LOADING);
    mLoadlevel = true;
}

void MainMenu::OnSplashButtonClick() 
{
    OnPlayButtonHover();
    OpenMenu(MENU_TYPE::MAIN);
}

void MainMenu::OnControllerButtonClick()
{
    OpenMenu(MENU_TYPE::CONTROLS);
}

void MainMenu::OnAudioButtonClick()
{
    OpenMenu(MENU_TYPE::AUDIO);
}

void MainMenu::OnKeyboardButtonClick()
{
    OpenMenu(MENU_TYPE::KEYBOARD);
}

void MainMenu::OnSettingsButtonClick()
{
    OpenMenu(MENU_TYPE::SETTINGS);
    if (App->GetWindow()->IsWindowFullscreen())
    {
        mFullscreenImageOff_On->SetEnabled(false);
        mFullscreenImageOn_On->SetEnabled(true);
    }
    else
    {
        mFullscreenImageOff_On->SetEnabled(true);
        mFullscreenImageOn_On->SetEnabled(false);
    }
}

void MainMenu::OnVSyncButtonOnClick()
{
    mVSyncImageOff_On->SetEnabled(false);
    mVSyncImageOn_On->SetEnabled(true);

    App->GetCurrentClock()->SetVsyncStatus(true);
}

void MainMenu::OnVSyncButtonOffClick()
{
    mVSyncImageOff_On->SetEnabled(true);
    mVSyncImageOn_On->SetEnabled(false);

    App->GetCurrentClock()->SetVsyncStatus(false);
}

void MainMenu::OnFullscreenButtonOnClick()
{
    mFullscreenImageOff_On->SetEnabled(false);
    mFullscreenImageOn_On->SetEnabled(true);

    App->GetWindow()->WindowFullscreen(true);
}

void MainMenu::OnFullscreenButtonOffClick()
{
    mFullscreenImageOff_On->SetEnabled(true);
    mFullscreenImageOn_On->SetEnabled(false);

    App->GetWindow()->WindowFullscreen(false);
}

void MainMenu::OnSlide(SETTING_TYPE type, DIRECTION direction, float step)
{
	// Early return. Just double checking we're not calling it on elements that are not sliders within the settings menu.
    if (type != SETTING_TYPE::GENERAL_VOLUME && type != SETTING_TYPE::MUSIC_VOLUME && type != SETTING_TYPE::EFFECTS_VOLUME) return;

    switch (type)
    {
    case SETTING_TYPE::GENERAL_VOLUME:
		if (direction == DIRECTION::LEFT)
        {
            mGeneralVolumeValue = App->GetAudio()->GetVolume("bus:/");
            if (mGeneralVolumeValue - step <= 0.0f)
            {
                App->GetAudio()->SetVolume("bus:/", 0.f);
				mGeneralVolumeSlider->SetValue(0.001f);
            }
            else
			{
				App->GetAudio()->SetVolume("bus:/", mGeneralVolumeValue - step);
                mGeneralVolumeSlider->SetValue(mGeneralVolumeValue - step);
            }
		}
		else // DIRECTION::RIGHT
        {
            mGeneralVolumeValue = App->GetAudio()->GetVolume("bus:/");
            if (mGeneralVolumeValue + step > 1.f)
            {
                App->GetAudio()->SetVolume("bus:/", 1.f);
                mGeneralVolumeSlider->SetValue(1.f);
            }
            else
            {
                App->GetAudio()->SetVolume("bus:/", mGeneralVolumeValue + step);
                mGeneralVolumeSlider->SetValue(mGeneralVolumeValue + step);
            }
        }
        break;
    case SETTING_TYPE::MUSIC_VOLUME:
        if (direction == DIRECTION::LEFT)
        {
            mMusicVolumeValue = App->GetAudio()->GetVolume("bus:/music");
            if (mMusicVolumeValue - step <= 0.0f)
            {
                App->GetAudio()->SetVolume("bus:/music", 0.f);
                mMusicVolumeSlider->SetValue(0.001f);
            }
            else
            {
                App->GetAudio()->SetVolume("bus:/music", mMusicVolumeValue - step);
                mMusicVolumeSlider->SetValue(mMusicVolumeValue - step);
            }
        }
        else // DIRECTION::RIGHT
        {
            mMusicVolumeValue = App->GetAudio()->GetVolume("bus:/music");
            if (mMusicVolumeValue + step > 1.f)
            {
                App->GetAudio()->SetVolume("bus:/music", 1.f);
                mMusicVolumeSlider->SetValue(1.f);
            }
            else
            {
                App->GetAudio()->SetVolume("bus:/music", mMusicVolumeValue + step);
                mMusicVolumeSlider->SetValue(mMusicVolumeValue + step);
            }
        }
        break;
    case SETTING_TYPE::EFFECTS_VOLUME:
        if (direction == DIRECTION::LEFT)
        {
            mEffectsVolumeValue = App->GetAudio()->GetVolume("bus:/sfx");
            if (mEffectsVolumeValue - step <= 0.0f)
            {
                App->GetAudio()->SetVolume("bus:/sfx", 0.f);
                mEffectsVolumeSlider->SetValue(0.001f);
            }
            else
            {
                App->GetAudio()->SetVolume("bus:/sfx", mEffectsVolumeValue - step);
                mEffectsVolumeSlider->SetValue(mEffectsVolumeValue - step);
            }
        }
        else // DIRECTION::RIGHT
        {
            mEffectsVolumeValue = App->GetAudio()->GetVolume("bus:/sfx");
            if (mEffectsVolumeValue + step > 1.f)
            {
                App->GetAudio()->SetVolume("bus:/sfx", 1.f);
                mEffectsVolumeSlider->SetValue(1.f);
            }
            else
            {
                App->GetAudio()->SetVolume("bus:/sfx", mEffectsVolumeValue + step);
                mEffectsVolumeSlider->SetValue(mEffectsVolumeValue + step);
            }
        }
        break;
    }
}

// SELECTED
void MainMenu::HoverMenu(MENU_TYPE type) 
{
    switch (type) 
    {
        case MENU_TYPE::MAIN:
            OnPlayButtonHover();
            break;
        case MENU_TYPE::OPTIONS:
            OnOptionsButtonHover();
            break;
        case MENU_TYPE::CREDITS:
            OnCreditsButtonHover();
            break;
        case MENU_TYPE::LOADING:
            OnQuitButtonHover();
            break;
    }
}

void MainMenu::HoverSubMenu(MENU_TYPE type)
{
    switch (type) 
    {
        case MENU_TYPE::CONTROLS:
            OnControllerButtonHover();
            break;
        case MENU_TYPE::SETTINGS:
            OnSettingsButtonHover();
            break;
        case MENU_TYPE::AUDIO:
            OnAudioButtonHover();
            break;
        case MENU_TYPE::KEYBOARD:
            OnKeyboardButtonHover();
            break;
    }
}

void MainMenu::HoverSubSubMenu(SETTING_TYPE type)
{
    switch (type)
    {
    case SETTING_TYPE::GENERAL_VOLUME:
        OnGeneralVolumeHover();
        break;
    case SETTING_TYPE::MUSIC_VOLUME:
        OnMusicVolumeHover();
        break;
    case SETTING_TYPE::EFFECTS_VOLUME:
        OnEffectsVolumeHover();
        break;
    /*case SETTING_TYPE::VSYNC:
        OnVSyncButtonHover();
		break;
    case SETTING_TYPE::FULL_SCREEN:
        OnFullscreenButtonHover();
		break;*/
    }
}

void MainMenu::OnGeneralVolumeHover()
{
    //ImageComponent* image = static_cast<ImageComponent*>(mGeneralVolumeButtonGO->GetComponent(ComponentType::IMAGE));
    mGeneralVolumeFill->SetAlpha(1.f);
	mCurrentSetting = SETTING_TYPE::GENERAL_VOLUME;

	//TODO: Abstract this abomination (in all of the hover functions)
    OnMusicVolumeHoverOff();
    OnEffectsVolumeHoverOff();
}

void MainMenu::OnMusicVolumeHover()
{
    mMusicVolumeFill->SetAlpha(1.f);
    mCurrentSetting = SETTING_TYPE::MUSIC_VOLUME;

    OnGeneralVolumeHoverOff();
    OnEffectsVolumeHoverOff();
}

void MainMenu::OnEffectsVolumeHover()
{
	mEffectsVolumeFill->SetAlpha(1.f);
    mCurrentSetting = SETTING_TYPE::EFFECTS_VOLUME;

    OnGeneralVolumeHoverOff();
    OnMusicVolumeHoverOff();
}

/*void MainMenu::OnVSyncButtonHover()
{
    ImageComponent* image = static_cast<ImageComponent*>(mVSyncButtonGO->GetComponent(ComponentType::IMAGE));
    image->SetAlpha(1.f);
    mCurrentSetting = SETTING_TYPE::VSYNC;

    OnGeneralVolumeHoverOff();
    OnMusicVolumeHoverOff();
    OnEffectsVolumeHoverOff();
    OnFullscreenButtonHoverOff();
}*/

/*void MainMenu::OnFullscreenButtonHover()
{
    ImageComponent* image = static_cast<ImageComponent*>(mFullscreenButtonGO->GetComponent(ComponentType::IMAGE));
    image->SetAlpha(1.f);
    mCurrentSetting = SETTING_TYPE::FULL_SCREEN;

    OnGeneralVolumeHoverOff();
    OnMusicVolumeHoverOff();
    OnEffectsVolumeHoverOff();
    OnVSyncButtonHoverOff();
}*/

void MainMenu::OnQuitButtonHover() 
{
    if (mOption != 3) 
    {
        mAudioManager->PlayOneShot(SFX::MAINMENU_SELECT);
    }

    mQuitHover->SetEnabled(true);
    mQuitText->SetEnabled(false);

    mOption = 3;

    // Set the other hovers off (integration mouse/click)
    OnCreditsButtonHoverOff();
    OnPlayButtonHoverOff();
    OnOptionsButtonHoverOff();
}

void MainMenu::OnQuitButtonHoverOff() 
{
    mQuitHover->SetEnabled(false);
    mQuitText->SetEnabled(true);
}

void MainMenu::OnOptionsButtonHover() 
{
    if (mOption != 1)
    {
        mAudioManager->PlayOneShot(SFX::MAINMENU_SELECT);
    }

    mOptionsHover->SetEnabled(true);
    mOptionsText->SetEnabled(false);

    mOption = 1;

    // Set the other hovers off (integration mouse/click)
    OnCreditsButtonHoverOff();
    OnPlayButtonHoverOff();
    OnQuitButtonHoverOff();
}

void MainMenu::OnOptionsButtonHoverOff() 
{
    mOptionsHover->SetEnabled(false);
    mOptionsText->SetEnabled(true);
}

void MainMenu::OnCreditsButtonHover() 
{
    if (mOption != 2)
    {
        mAudioManager->PlayOneShot(SFX::MAINMENU_SELECT);
    }

    mCreditsHover->SetEnabled(true);
    mCreditsText->SetEnabled(false);

    mOption = 2;

    // Set the other hovers off (integration mouse/click)
    OnPlayButtonHoverOff();
    OnOptionsButtonHoverOff();
    OnQuitButtonHoverOff();
}

void MainMenu::OnCreditsButtonHoverOff() 
{
    mCreditsHover->SetEnabled(false);
    mCreditsText->SetEnabled(true);
}

void MainMenu::OnPlayButtonHover()
{
    if (mOption != 0)
    {
        mAudioManager->PlayOneShot(SFX::MAINMENU_SELECT);
    }

    mPlayHover->SetEnabled(true);
    mPlayText->SetEnabled(false);

    mOption = 0;

    // Set the other hovers off (integration mouse/click)
    OnCreditsButtonHoverOff();
    OnOptionsButtonHoverOff();
    OnQuitButtonHoverOff();
}

void MainMenu::OnPlayButtonHoverOff()
{
    mPlayHover->SetEnabled(false);
    mPlayText->SetEnabled(true);
}

void MainMenu::OnControllerButtonHover()
{
    //ImageComponent* image = static_cast<ImageComponent*>(mControllerGO->GetComponent(ComponentType::IMAGE));
    //image->SetAlpha(0.8f);

    mControllerHover->SetEnabled(true);
    mControllerText->SetEnabled(false);

    // Set the other hovers off (integration mouse/click)
    OnSettingsButtonHoverOff();
    OnAudioButtonHoverOff();
    OnKeyboardButtonHoverOff();
}

void MainMenu::OnControllerButtonHoverOff()
{
    //ImageComponent* image = static_cast<ImageComponent*>(mControllerGO->GetComponent(ComponentType::IMAGE));
    //image->SetAlpha(0.2f);
    mControllerHover->SetEnabled(false);
    mControllerText->SetEnabled(true);
}

void MainMenu::OnAudioButtonHover()
{
    //ImageComponent* image = static_cast<ImageComponent*>(mAudioGO->GetComponent(ComponentType::IMAGE));
    //image->SetAlpha(0.8f);

    mAudioHover->SetEnabled(true);
    mAudioText->SetEnabled(false);

    // Set the other hovers off (integration mouse/click)
    OnSettingsButtonHoverOff();
    OnControllerButtonHoverOff();
    OnKeyboardButtonHoverOff();
}

void MainMenu::OnAudioButtonHoverOff()
{
    mAudioHover->SetEnabled(false);
    mAudioText->SetEnabled(true);

    //ImageComponent* image = static_cast<ImageComponent*>(mAudioGO->GetComponent(ComponentType::IMAGE));
    //image->SetAlpha(0.2f);
}

void MainMenu::OnKeyboardButtonHover()
{
    //ImageComponent* image = static_cast<ImageComponent*>(mKeyboardGO->GetComponent(ComponentType::IMAGE));
    //image->SetAlpha(0.8f);

    mKeyboardHover->SetEnabled(true);
    mKeyboardText->SetEnabled(false);

    // Set the other hovers off (integration mouse/click)
    OnSettingsButtonHoverOff();
    OnControllerButtonHoverOff();
    OnAudioButtonHoverOff();
}

void MainMenu::OnKeyboardButtonHoverOff()
{
    //ImageComponent* image = static_cast<ImageComponent*>(mKeyboardGO->GetComponent(ComponentType::IMAGE));
    //image->SetAlpha(0.2f);

    mKeyboardHover->SetEnabled(false);
    mKeyboardText->SetEnabled(true);
}

void MainMenu::OnSettingsButtonHover()
{
    //ImageComponent* image = static_cast<ImageComponent*>(mSettingsButtonGO->GetComponent(ComponentType::IMAGE));
    //image->SetAlpha(0.8f);

    mSettingsHover->SetEnabled(true);
    mSettingsText->SetEnabled(false);

    // Set the other hovers off (integration mouse/click)
    OnKeyboardButtonHoverOff();
    OnControllerButtonHoverOff();
    OnAudioButtonHoverOff();
}

void MainMenu::OnSettingsButtonHoverOff()
{
    //ImageComponent* image = static_cast<ImageComponent*>(mSettingsButtonGO->GetComponent(ComponentType::IMAGE));
    //image->SetAlpha(0.2f);

    mSettingsHover->SetEnabled(false);
    mSettingsText->SetEnabled(true);
}

void MainMenu::OnGeneralVolumeHoverOff()
{
    mGeneralVolumeFill->SetAlpha(0.8f);
}

void MainMenu::OnMusicVolumeHoverOff()
{
    mMusicVolumeFill->SetAlpha(0.8f);
}

void MainMenu::OnEffectsVolumeHoverOff()
{
    mEffectsVolumeFill->SetAlpha(0.8f);
}

/*void MainMenu::OnVSyncButtonHoverOff()
{
    ImageComponent* image = static_cast<ImageComponent*>(mVSyncButtonGO->GetComponent(ComponentType::IMAGE));
    image->SetAlpha(0.8f);
}*/

/*void MainMenu::OnFullscreenButtonHoverOff()
{
    ImageComponent* image = static_cast<ImageComponent*>(mFullscreenButtonGO->GetComponent(ComponentType::IMAGE));
    image->SetAlpha(0.8f);
}*/

void MainMenu::OnGeneralUp()
{
    OnSlide(static_cast<SETTING_TYPE>(0), DIRECTION::RIGHT, 0.1f);
}

void MainMenu::OnGeneralDown()
{
    OnSlide(static_cast<SETTING_TYPE>(0), DIRECTION::LEFT, 0.1f);
}

void MainMenu::OnMusicUp()
{
    OnSlide(static_cast<SETTING_TYPE>(1), DIRECTION::RIGHT, 0.1f);
}

void MainMenu::OnMusicDown()
{
    OnSlide(static_cast<SETTING_TYPE>(1), DIRECTION::LEFT, 0.1f);
}

void MainMenu::OnEffectsUp()
{
    OnSlide(static_cast<SETTING_TYPE>(2), DIRECTION::RIGHT, 0.1f);
}

void MainMenu::OnEffectsDown()
{
    OnSlide(static_cast<SETTING_TYPE>(2), DIRECTION::LEFT, 0.1f);
}
