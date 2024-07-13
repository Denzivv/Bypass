#include "fontch.h"
#include "Includes.h"
#include "Tools.h"
#include "fake_dlfcn.h"
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_android.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include "StrEnc.h"
#include "plthook.h"
#include "Items.h"
#include "json.hpp"
#include "Icon.h"
#include "Iconcpp.h"
#include "Vector2.hpp"
#include "Vector3.hpp"
#include "ImguiPP.cpp"
#include "Menu.h"
#include "NIKE.h"
#include "Rect.h"
using json = nlohmann::json;
#define SLEEP_TIME 1000LL / 60LL
#include "SDK.hpp"
using namespace SDK;
#include <curl/curl.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include "base64/base64.h"
#include <stdio.h>
#include "Rect.h"
#include "KittyMemory/MemoryPatch.h"
#include "MemoryTools.h"
//#include "FTools/ImguiPP.h"
//#include "FTools/Iconcpp.h"
#include "FTools/CN.h"
#include "FTools/Font.h"
#include "FTools/Icon.h"
#include "Helper/obfuscate.h"
#include "Helper/fake_dlfcn.h"
#include "Helper/Includes.h"
#include "Helper/plthook.h"
#include "Helper/json.hpp"
#include "FONTS/F48.h"
#include "FONTS/F19.h"
#include "FONTS/F50.h"
#include "FONTS/F68.h"
#include "FONTS/F86.h"
#include "FONTS/Social.h"
#include "And64InlineHook/And64InlineHook.hpp"
#include <imgui/stb_image.h>


#include <imgui/stb_image.h>
char extra[32];
std::string g_Token, g_Auth;
std::string KeySlot = "";
std::string FlotingText = "";
std::string expiredDate = "";
bool bValid = true;
bool show_live_pron = false;
bool show_zm = false;
bool show_zz = false;
bool show_jz = false;
bool show_nc = false;
bool show_bypass = false;
bool show_another_info = true;
bool Bypass = true; 
bool show_gy = false;
bool show_xhmaster_pron = false;
bool WideView = false;
bool FlashSdk = false;
float FOVSize = 250;
bool HIDEESP = true;
float FOVSizea = 250;
#define GNames_Offset 0x6F0BCB4
#define GEngine_Offset 0xCB15820 //UEngine
#define GEngine_Offset 0xCB34E08 //UlocalPlayer
#define GUObject_Offset 0xC8E1270
#define GetActorArray 0x8B367FC
#define Canvas_Map_Offset 0xC503A40
#define Process_Event_Offset 0x7144F50
#define GNativeAndroidApp_Offset 0xC443A08
#define Actors_Offset 0xA0



using json = nlohmann::json;
char extras[64];

#define CREATE_COLOR(r, g, b, a) new float[4] {(float)r, (float)g, (float)b, (float)a};
#define IM_PI                   3.14159265358979323846f
#define RAD2DEG(x) ((float)(x) * (float)(180.f / IM_PI))
#define DEG2RAD(x) ((float)(x) * (float)(IM_PI / 180.f))
#define W2S(w, s) UGameplayStatics::ProjectWorldToScreen(localController, w, true, s)

void RotateTriangle(std::array<Vector3, 3> & points, float rotation) {
    const auto points_center = (points.at(0) + points.at(1) +  points.at(2)) / 3;
    for (auto & point : points) {
        point = point - points_center;
        const auto temp_x = point.X;
        const auto temp_y = point.Y;
        const auto theta = DEG2RAD(rotation);
        const auto c = cosf(theta);
        const auto s = sinf(theta);
        point.X = temp_x * c - temp_y * s;
        point.Y = temp_x * s + temp_y * c;
        point = point + points_center;
    }
}
bool WriteAddr(void *addr, void *buffer, size_t length) {
    unsigned long page_size = sysconf(_SC_PAGESIZE);
    unsigned long size = page_size * sizeof(uintptr_t);
    return mprotect((void *) ((uintptr_t) addr - ((uintptr_t) addr % page_size) - page_size), (size_t) size, PROT_EXEC | PROT_READ | PROT_WRITE) == 0 && memcpy(addr, buffer, length) != 0;
}

#define DefineHook(RET, NAME, ARGS) \
	RET(*Orig_##NAME)               \
	ARGS;                           \
	RET Hook_##NAME ARGS

template<typename T>
void Write(uintptr_t addr, T value) {
    WriteAddr((void *) addr, &value, sizeof(T));
}

#define MEMORY(lib, offset, hex) patchOffset(OBFUSCATE(lib), string2Offset(OBFUSCATE(offset)), OBFUSCATE(hex), true)
#if defined(__aarch64__)
#else

#endif


#define targetLibName OBFUSCATE("libUE4.so")  /// here you can ad your lib name
#define targetLibName OBFUSCATE("libanort.so")
#define targetLibName OBFUSCATE("libanogs.so")
#define targetLibName OBFUSCATE("libgcloud.so")

json items_data;

uintptr_t ANOGS;
uintptr_t anogs;
uintptr_t UE4;
uintptr_t g_Anogs;
uintptr_t g_TDataMaster;
uintptr_t CrashSight;
uintptr_t Anogs;
uintptr_t TDataMaster;
uintptr_t g_Gcloud;

android_app *g_App = 0;
ASTExtraPlayerCharacter *g_LocalPlayer = 0;
ASTExtraPlayerController *g_LocalController = 0;

bool initImGui = false;
int screenWidth = -1, glWidth, screenHeight = -1, glHeight;
float density = -1;

static UEngine *GEngine = 0;
UWorld *GetWorld() {
    while (!GEngine) {
 GEngine = UObject::FindObject<UEngine>("UAEGameEngine Transient.UAEGameEngine_1");
        sleep(1);
          }
    if (GEngine) {
    auto ViewPort = GEngine->GameViewport;
     if (ViewPort) {
   return ViewPort->World;
     }   }
    return 0;
       }

TNameEntryArray *GetGNames() {
return ((TNameEntryArray *(*)()) (UE4 + GNames_Offset))();
}

std::vector<AActor *> getActors() {
auto World = GetWorld();
if (!World)
return std::vector<AActor *>();

auto PersistentLevel = World->PersistentLevel;
if (!PersistentLevel)
return std::vector<AActor *>();

auto Actors = *(TArray<AActor *> *)((uintptr_t) PersistentLevel + Actors_Offset);

std::vector<AActor *> actors;
for (int i = 0; i < Actors.Num(); i++) {
auto Actor = Actors[i];
if (Actor) {
actors.push_back(Actor);
}
}
return actors;
}

enum EAimTarget {
    Head = 0,
    Chest = 1
};

enum EAimTrigger {
    Shooting = 0,
    None = 1,
    Scoping = 2,
    Both = 3,
    Any = 4
};

enum BBox {
  Neno = 0,
  Box = 1,
  Box3D = 2,
  
};

enum EAimBy {
    FOV = 0,
    Distance = 1
};

enum EEsp {
    LineNone = 0,
    LineTop = 1,
    LineMid = 2,
    LineBelow = 3,
};

enum EAimMode {
    AimBullet = 0,
    Pbullet = 1,
    AimBot = 2
};

std::map<int, bool> Items;

struct sConfig {
	bool Bypass;
	bool spawn;
	bool LOBBY;
    bool Island;
	bool Fov;
	bool EnimiesAlert;
    struct sPlayerESP {
        bool Line;
        bool Box;
        bool Health;
        bool Skeleton;
        bool Name;
        bool Distance;
        bool TeamID;
        bool Vehicle;
        bool NoBot;
        bool Grenade;
        bool LootBox;
		bool wideview;
		bool Island;
		bool LOBBY;
		EEsp By;
		bool Aimbotchest;
    };

    sPlayerESP PlayerESP{0};

    struct sVehicleESP {
        bool ShowVehicle;
        bool ShowDistance;
    };
    sVehicleESP VehicleESP{0};

    struct sAimMenu {
        bool Enable;
        bool AimBot;
		bool MagicBullet;
		EAimMode Mode;
		bool AimBy;
        bool FOV;
        EAimTarget Target;
        EAimTrigger Trigger;
        bool IgnoreKnocked;
        bool IgnoreBot;
        bool VisCheck;
		bool RecoilComparison;
		float Cross;
		float Crosss;
		float Recc;
		float Meter;
    };
    sAimMenu SilentAim{0};
    sAimMenu AimBot{0};
	
	struct sFAK
	{
    bool Box3D;
    bool Box;
	BBox By;
	};
	sFAK FAK{0};
	
    struct sHighRisk {
        bool Cross;
        bool HitEffect;
        bool Recoil;
		bool Unlock;
        bool NoSmoke;
    };
    sHighRisk HighRisk{0};
	
	struct sOTHER {
        bool EXP;
        bool BLOCK_SPECTATE;
        bool FPS;
        bool HIDEESP;
        bool Bypass; 
        bool HiTLERYT;
        bool spawn;
    };
    sOTHER OTHER{0};

    struct sColorsESP {
        float *Line;
        float *Box;
        float *Name;
        float *Distance;
        float *Skeleton;
        float *SkeletonVisible;
        float *BotNn;
	    float *Skeletonbot;
	     float *nonbot;
         float *Skeletonnon;
         float *BotNv;
         float *PotNn;
         float *PotNv;
        float *Vehicle;
    };
    sColorsESP ColorsESP{0};
};

sConfig Config{0};
#define CREATE_COLOR(r, g, b, a) new float[4] {(float)r, (float)g, (float)b, (float)a};

 
struct sRegion {
    uintptr_t start, end;
};

std::vector<sRegion> trapRegions;

bool isObjectInvalid(UObject *obj) {
    if (!Tools::IsPtrValid(obj)) {
        return true;
    }

    if (!Tools::IsPtrValid(obj->ClassPrivate)) {
        return true;
    }

    if (obj->InternalIndex <= 0) {
        return true;
    }

    if (obj->NamePrivate.ComparisonIndex <= 0) {
        return true;
    }

    if ((uintptr_t)(obj) % sizeof(uintptr_t) != 0x0 && (uintptr_t)(obj) % sizeof(uintptr_t) != 0x4) {
        return true;
    }

    if (std::any_of(trapRegions.begin(), trapRegions.end(), [obj](sRegion region) { return ((uintptr_t) obj) >= region.start && ((uintptr_t) obj) <= region.end; }) ||
        std::any_of(trapRegions.begin(), trapRegions.end(), [obj](sRegion region) { return ((uintptr_t) obj->ClassPrivate) >= region.start && ((uintptr_t) obj->ClassPrivate) <= region.end; })) {
        return true;
    }

    return false;
}

typedef void (*ImGuiDemoMarkerCallback)(const char* file, int line, const char* section, void* user_data);
extern ImGuiDemoMarkerCallback  GImGuiDemoMarkerCallback;
extern void* GImGuiDemoMarkerCallbackUserData;
ImGuiDemoMarkerCallback         GImGuiDemoMarkerCallback = NULL;
void* GImGuiDemoMarkerCallbackUserData = NULL;
#define IMGUI_DEMO_MARKER(section)  do { if (GImGuiDemoMarkerCallback != NULL) GImGuiDemoMarkerCallback(__FILE__, __LINE__, section, GImGuiDemoMarkerCallbackUserData); } while (0)
ImGuiStyle& style = ImGui::GetStyle();
static ImGuiStyle ref_saved_style;
 
std::string getObjectPath(UObject *Object) {
    std::string s;
    for (auto super = Object->ClassPrivate; super; super = (UClass *) super->SuperStruct) {
        if (!s.empty())
            s += ".";
        s += super->NamePrivate.GetName();
    }
    return s;
}
 
int32_t ToColor(float *col) {
    return ImGui::ColorConvertFloat4ToU32(*(ImVec4 *) (col));
}

FRotator ToRotator(FVector local, FVector target) {
    FVector rotation = UKismetMathLibrary::Subtract_VectorVector(local, target);

    float hyp = sqrt(rotation.X * rotation.X + rotation.Y * rotation.Y);

    FRotator newViewAngle = {0};
    newViewAngle.Pitch = -atan(rotation.Z / hyp) * (180.f / (float) 3.14159265358979323846);
    newViewAngle.Yaw = atan(rotation.Y / rotation.X) * (180.f / (float) 3.14159265358979323846);
    newViewAngle.Roll = (float) 0.f;

    if (rotation.X >= 0.f)
        newViewAngle.Yaw += 180.0f;

    return newViewAngle;
}

#define W2S(w, s) UGameplayStatics::ProjectWorldToScreen(localController, w, true, s)

auto GetTargetForAimBot() {
    ASTExtraPlayerCharacter *result = 0;
    float max = std::numeric_limits<float>::infinity();

    auto Actors = getActors();
    auto localPlayer = g_LocalPlayer;
    auto localController = g_LocalController;

    if (localPlayer) {
        for (auto Actor : Actors) {
            if (isObjectInvalid(Actor))
                continue;

            if (Actor->IsA(ASTExtraPlayerCharacter::StaticClass())) {
                auto Player = (ASTExtraPlayerCharacter *) Actor;

                if (Player->PlayerKey == localPlayer->PlayerKey)
                    continue;

                if (Player->TeamID == localPlayer->TeamID)
                    continue;

                if (Player->bDead)
                    continue;

                if (Config.AimBot.IgnoreKnocked) {
                    if (Player->Health == 0.0f)
                        continue;
                }

                if (Config.AimBot.VisCheck) {
                    if (!localController->LineOfSightTo(Player, {0, 0, 0}, true))
                        continue;
                }

                if (Config.AimBot.IgnoreBot) {
                    if (Player->bEnsure)
                        continue;
                }

                auto Root = Player->GetBonePos("Root", {});
                auto Head = Player->GetBonePos("Head", {});

                FVector2D RootSc, HeadSc;
                if (W2S(Root, &RootSc) && W2S(Head, &HeadSc)) {
                    float height = abs(HeadSc.Y - RootSc.Y);
                    float width = height * 0.65f;

                    FVector middlePoint = {HeadSc.X + (width / 2), HeadSc.Y + (height / 2), 0};
                    if ((middlePoint.X >= 0 && middlePoint.X <= glWidth) && (middlePoint.Y >= 0 && middlePoint.Y <= glHeight)) {
                        FVector2D v2Middle = FVector2D((float) (glWidth / 2), (float) (glHeight / 2));
                        FVector2D v2Loc = FVector2D(middlePoint.X, middlePoint.Y);

                        float dist = FVector2D::Distance(v2Middle, v2Loc);

                        if (dist < max) {
                            max = dist;
                            result = Player;
                        }
                    }
                }
            }
        }
    }

    return result;
}

auto GetTargetByCrossDist() {
    ASTExtraPlayerCharacter *result = 0;
    float max = std::numeric_limits<float>::infinity();

    auto Actors = getActors();

    auto localPlayer = g_LocalPlayer;
    auto localController = g_LocalController;

    if (localPlayer) {
        for (int i = 0; i < Actors.size(); i++) {
            auto Actor = Actors[i];
            if (isObjectInvalid(Actor))
                continue;

            if (Actor->IsA(ASTExtraPlayerCharacter::StaticClass())) {
                auto Player = (ASTExtraPlayerCharacter *) Actor;
				auto Target = (ASTExtraPlayerCharacter *) Actor;
				
			    float dist = localPlayer->GetDistanceTo(Target) / 100.0f;    
                if (dist > Config.SilentAim.Meter)
                    continue;
				
                if (Player->PlayerKey == localPlayer->PlayerKey)
                    continue;

                if (Player->TeamID == localPlayer->TeamID)
                    continue;

                if (Player->bDead)
                    continue;

                if (Config.SilentAim.IgnoreKnocked) {
                    if (Player->Health == 0.0f)
                        continue;
                }

                if (Config.SilentAim.VisCheck) {
                    if (!localController->LineOfSightTo(Player, {0, 0, 0}, true))
                        continue;
                }
                if (Config.SilentAim.IgnoreBot) {
                    if (Player->bIsAI)
                        continue;
                }

                auto Root = Player->GetBonePos("Root", {});
                auto Head = Player->GetBonePos("Head", {});

                FVector2D RootSc, HeadSc;
                if (W2S(Root, &RootSc) && W2S(Head, &HeadSc)) {
                    float height = abs(HeadSc.Y - RootSc.Y);
                    float width = height * 0.65f;

                    FVector middlePoint = {HeadSc.X + (width / 2), HeadSc.Y + (height / 2), 0};
                    if ((middlePoint.X >= 0 && middlePoint.X <= glWidth) && (middlePoint.Y >= 0 && middlePoint.Y <= glHeight)) {
                        FVector2D v2Middle = FVector2D((float) (glWidth / 2), (float) (glHeight / 2));
                        FVector2D v2Loc = FVector2D(middlePoint.X, middlePoint.Y);

                        float dist = FVector2D::Distance(v2Middle, v2Loc);

                        if (dist < max) {
                            max = dist;
                            result = Player;
                        }
                    }
                }
            }
        }
    }

    return result;
}


ASTExtraPlayerCharacter *GetTargetForAim() {
    /*if (Config.AimBot.AimBy == EAimBy::FOV) {
        return GetTargetByCrossDist();
    }
  /*  if (Config.AimBot.AimBy == EAimBy::Distance) {
        return GetTargetByDistance();
    }*/
    return 0;
}


const char *GetVehicleName(ASTExtraVehicleBase *Vehicle) {
    switch (Vehicle->VehicleShapeType) {
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Motorbike:
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Motorbike_SideCart:
            return "Motorbike";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Dacia:
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_HeavyDacia:
            return "Dacia";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_MiniBus:
            return "Mini Bus";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_PickUp:
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_PickUp01:
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_HeavyPickup:
            return "Pick Up";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Buggy:
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_HeavyBuggy:
            return "Buggy";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_UAZ:
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_UAZ01:
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_UAZ02:
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_UAZ03:
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_HeavyUAZ:
            return "UAZ";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_PG117:
            return "PG117";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Aquarail:
            return "Aquarail";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Mirado:
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Mirado01:
            return "Mirado";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Rony:
            return "Rony";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Scooter:
            return "Scooter";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_SnowMobile:
            return "Snow Mobile";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_TukTukTuk:
            return "Tuk Tuk";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_SnowBike:
            return "Snow Bike";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Surfboard:
            return "Surf Board";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Snowboard:
            return "Snow Board";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Amphibious:
            return "Amphibious";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_LadaNiva:
            return "Lada Niva";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_UAV:
            return "UAV";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_MegaDrop:
            return "Mega Drop";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Lamborghini:
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Lamborghini01:
            return "Lamborghini";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_GoldMirado:
            return "Gold Mirado";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_BigFoot:
            return "Big Foot";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_HeavyUH60:
            return "UH60";
            break;
        default:
            return "Vehicle";
            break;
    }
    return "Vehicle";
}
void (*orig_shoot_event)(USTExtraShootWeaponComponent *thiz, FVector start, FRotator rot, void *unk1, int unk2) = 0;

void shoot_event(USTExtraShootWeaponComponent *thiz, FVector start, FRotator rot, ASTExtraShootWeapon *weapon, int unk1) {
    if (Config.SilentAim.Enable) {
        ASTExtraPlayerCharacter *Target = GetTargetByCrossDist();
        if (Target) {
            bool triggerOk = false;
            if (Config.SilentAim.Trigger != EAimTrigger::None) {
                if (Config.SilentAim.Trigger == EAimTrigger::Shooting) {
                    triggerOk = g_LocalPlayer->bIsWeaponFiring;
                } else if (Config.SilentAim.Trigger == EAimTrigger::Scoping) {
                    triggerOk = g_LocalPlayer->bIsGunADS;
                } else if (Config.SilentAim.Trigger == EAimTrigger::Both) {
                    triggerOk = g_LocalPlayer->bIsWeaponFiring && g_LocalPlayer->bIsGunADS;
                } else if (Config.SilentAim.Trigger == EAimTrigger::Any) {
                    triggerOk = g_LocalPlayer->bIsWeaponFiring || g_LocalPlayer->bIsGunADS;
                }
            } else triggerOk = true;
            if (triggerOk) {
                FVector targetAimPos = Target->GetBonePos("Head", {});
                if (Config.SilentAim.Target == EAimTarget::Chest) {
                    targetAimPos.Z -= 25.0f;
                }
                UShootWeaponEntity *ShootWeaponEntityComponent = thiz->ShootWeaponEntityComponent;
                if (ShootWeaponEntityComponent) {
                    ASTExtraVehicleBase *CurrentVehicle = Target->CurrentVehicle;
                    if (CurrentVehicle) {
                        FVector LinearVelocity = CurrentVehicle->ReplicatedMovement.LinearVelocity;

                        float dist = g_LocalPlayer->GetDistanceTo(Target);
                        auto timeToTravel = dist / ShootWeaponEntityComponent->BulletFireSpeed;

                        targetAimPos = UKismetMathLibrary::Add_VectorVector(targetAimPos, UKismetMathLibrary::Multiply_VectorFloat(LinearVelocity, timeToTravel));
                    } else {
                        FVector Velocity = Target->GetVelocity();

                        float dist = g_LocalPlayer->GetDistanceTo(Target);
                        auto timeToTravel = dist / ShootWeaponEntityComponent->BulletFireSpeed;

                        targetAimPos = UKismetMathLibrary::Add_VectorVector(targetAimPos, UKismetMathLibrary::Multiply_VectorFloat(Velocity, timeToTravel));
                    }
                    FVector fDir = UKismetMathLibrary::Subtract_VectorVector(targetAimPos, g_LocalController->PlayerCameraManager->CameraCache.POV.Location);
                    rot = UKismetMathLibrary::Conv_VectorToRotator(fDir);
                }
            }
        }
    }
    return orig_shoot_event(thiz, start, rot, weapon, unk1);
}

class FPSCounter {
protected:
    unsigned int m_fps;
    unsigned int m_fpscount;
    long m_fpsinterval;

public:
    FPSCounter() : m_fps(0), m_fpscount(0), m_fpsinterval(0) {
    }

    void update() {
        m_fpscount++;

        if (m_fpsinterval < time(0)) {
            m_fps = m_fpscount;

            m_fpscount = 0;
            m_fpsinterval = time(0) + 1;
        }
    }

    unsigned int get() const {
        return m_fps;
    }
};

FPSCounter fps;

// ======================================================================== //
void DrawBoxEnemy(ImDrawList *draw, ImVec2 X, ImVec2 Y, float thicc, float rounding, int color) {
    draw->AddLine({X.x, X.y}, {Y.x, Y.y}, color, thicc);
}
void Box4Line(ImDrawList *draw, float thicc, int x, int y, int w, int h, int color) {
    int iw = w / 4;
    int ih = h / 4;
    // top
    draw->AddRect(ImVec2(x, y),ImVec2(x + iw, y), color, thicc);
    draw->AddRect(ImVec2(x + w - iw, y),ImVec2(x + w, y), color, thicc);
    draw->AddRect(ImVec2(x, y),ImVec2(x, y + ih), color, thicc);
    draw->AddRect(ImVec2(x + w - 1, y),ImVec2(x + w - 1, y + ih), color, thicc);;
    // bottom
    draw->AddRect(ImVec2(x, y + h),ImVec2(x + iw, y + h), color, thicc);
    draw->AddRect(ImVec2(x + w - iw, y + h),ImVec2(x + w, y + h), color, thicc);
    draw->AddRect(ImVec2(x, y + h - ih), ImVec2(x, y + h), color, thicc);
    draw->AddRect(ImVec2(x + w - 1, y + h - ih), ImVec2(x + w - 1, y + h), color, thicc);
}
void DrawBoxEnemy(ImDrawList *draw, ImVec2 X, ImVec2 Y, float thicc, int color) {
    draw->AddLine({X.x, X.y}, {Y.x, Y.y}, color, thicc);
}

void DrawFilledRectangle(int x, int y, int w, int h, ImU32 col, float rounding) {
    ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), col, rounding);
}

void DrawRectangle(int x, int y, int w, int h, ImU32 col, float rounding) {
    ImGui::GetBackgroundDrawList()->AddRect(ImVec2(x, y), ImVec2(x + w, y + h), col, rounding);
}
bool W2S2(FVector worldPos, FVector2D *screenPos) {
    return g_LocalController->ProjectWorldLocationToScreen(worldPos, true, screenPos);
}

void Line(ImDrawList *draw,FVector2D origin, FVector2D dest, ImColor color)
{
   draw->AddLine({origin.X, origin.Y},{dest.X, dest.Y},color, 2.0f);
}




//𝐉𝐎𝐈𝐍 𝐅𝐎𝐑 𝐁𝐆𝐌𝐢 𝟐. 𝟗 𝐒𝐑𝐂 - @Src_Leeakers
//𝐓𝐆 - @Src_Leeakers


//𝐉𝐎𝐈𝐍 𝐅𝐎𝐑 𝐁𝐆𝐌𝐢 𝟐. 𝟗 𝐒𝐑𝐂 - @Src_Leeakers
//𝐓𝐆 - @Src_Leeakers


//𝐉𝐎𝐈𝐍 𝐅𝐎𝐑 𝐁𝐆𝐌𝐢 𝟐. 𝟗 𝐒𝐑𝐂 - @Src_Leeakers
//𝐓𝐆 - @Src_Leeakers



void Box3D1(ImDrawList *draw, FVector origin, FVector extends, ImColor col) {
    origin.X -= extends.X / 2.f;
    origin.Y -= extends.Y / 2.f;
    origin.Z -= extends.Z / 2.f;   
    
 FVector one = origin;
 FVector two = origin; two.X += extends.X;
 FVector tree = origin; tree.X += extends.X; tree.Y += extends.Y;
 FVector four = origin; four.Y += extends.Y;

 FVector five = one; five.Z += extends.Z;
 FVector six = two; six.Z += extends.Z;
 FVector seven = tree; seven.Z += extends.Z;
 FVector eight = four; eight.Z += extends.Z;

    FVector2D s1, s2, s3, s4, s5, s6, s7, s8;
    if (W2S2(one, &s1) && W2S2(two, &s2) && W2S2(tree, &s3) && W2S2(four, &s4) &&
    W2S2(five, &s5) && W2S2(six, &s6) && W2S2(seven, &s7) && W2S2(eight, &s8))
    {        
    Line(draw,s1, s2, col);
    Line(draw,s2, s3, col);
    Line(draw,s3, s4, col);
    Line(draw,s4, s1, col);

    Line(draw,s5, s6, col);
    Line(draw,s6, s7, col);
    Line(draw,s7, s8, col);
    Line(draw,s8, s5, col);
 
    Line(draw,s1, s5, col);
    Line(draw,s2, s6, col);
    Line(draw,s3, s7, col);
    Line(draw,s4, s8, col);
     }}

// ======================================================================== //


static float isRed = 0.0f, isGreen = 0.01f, isBlue = 0.0f;

void DrawESP(ImDrawList *draw) {


MemoryPatch::createWithHex("libanogs.so", 0x1749A8,"00 00 80 D2 C0 03 5F D6").Modify();//CASE 16
MemoryPatch::createWithHex("libanogs.so", 0x1672E8,"00 00 80 D2 C0 03 5F D6").Modify();//CASE 35
MemoryPatch::createWithHex("libanogs.so", 0x1676F8,"00 00 80 D2 C0 03 5F D6").Modify();//CASE 37
MemoryPatch::createWithHex("libanogs.so", 0xDFA50,"00 00 80 D2 C0 03 5F D6").Modify();//MEMCPY
MemoryPatch::createWithHex("libanogs.so", 0xE6D3C,"00 00 80 D2 C0 03 5F D6").Modify();//10 YEAR FIXER










	
draw->AddText({((float) density / 19.0f), 50}, IM_COL32(255, 0, 0, 200),
"FPS :");

draw->AddText({((float) density / 19.0f), 80}, IM_COL32(255, 0, 0, 200),
"Playsafe ");


	
	
	
	auto isFrames = ImGui::GetFrameCount();

    if(isFrames % 1 == 0) {

        if(isGreen == 0.01f && isBlue == 0.0f){
            isRed += 0.01f;
             }

        if(isRed > 0.99f && isBlue == 0.0f){
            isRed = 1.0f;
            isGreen += 0.01f;
            }

        if(isGreen > 0.99f && isBlue == 0.0f){
            isGreen = 1.0f;
            isRed -= 0.01f;
        }

       if(isRed < 0.01f && isGreen == 1.0f){
            isRed = 0.0f;
            isBlue += 0.01f;
            }

        if(isBlue > 0.99f && isRed == 0.0f){
            isBlue = 1.0f;
            isGreen -= 0.01f;
            }
        if(isGreen < 0.01f && isBlue == 1.0f){
            isGreen = 0.0f;
            isRed += 0.01f;
            }
        if(isRed > 0.99f && isGreen == 0.0f){
            isRed = 1.0f;
            isBlue -= 0.01f;
            }
        if(isBlue < 0.01f && isGreen == 0.0f){
            isBlue = 0.0f;
            isRed -= 0.01f;
            if(isRed < 0.01f)
            isGreen = 0.01f;
        }
		
        if(isGreen == 0.01f && isBlue == 0.0f){
            isRed += 0.01f;
             }

        if(isRed > 0.99f && isBlue == 0.0f){
            isRed = 1.0f;
            isGreen += 0.01f;
            }

        if(isGreen > 0.99f && isBlue == 0.0f){
            isGreen = 1.0f;
            isRed -= 0.01f;
        }

       if(isRed < 0.01f && isGreen == 1.0f){
            isRed = 0.0f;
            isBlue += 0.01f;
            }

        if(isBlue > 0.99f && isRed == 0.0f){
            isBlue = 1.0f;
            isGreen -= 0.01f;
            }
        if(isGreen < 0.01f && isBlue == 1.0f){
            isGreen = 0.0f;
            isRed += 0.01f;
            }
        if(isRed > 0.99f && isGreen == 0.0f){
            isRed = 1.0f;
            isBlue -= 0.01f;
            }
        if(isBlue < 0.01f && isGreen == 0.0f){
            isBlue = 0.0f;
            isRed -= 0.01f;
            if(isRed < 0.01f)
            isGreen = 0.01f;
        }
		
		
        if(isGreen == 0.01f && isBlue == 0.0f){
            isRed += 0.01f;
             }

        if(isRed > 0.99f && isBlue == 0.0f){
            isRed = 1.0f;
            isGreen += 0.01f;
            }

        if(isGreen > 0.99f && isBlue == 0.0f){
            isGreen = 1.0f;
            isRed -= 0.01f;
        }

       if(isRed < 0.01f && isGreen == 1.0f){
            isRed = 0.0f;
            isBlue += 0.01f;
            }

        if(isBlue > 0.99f && isRed == 0.0f){
            isBlue = 1.0f;
            isGreen -= 0.01f;
            }
        if(isGreen < 0.01f && isBlue == 1.0f){
            isGreen = 0.0f;
            isRed += 0.01f;
            }
        if(isRed > 0.99f && isGreen == 0.0f){
            isRed = 1.0f;
            isBlue -= 0.01f;
            }
        if(isBlue < 0.01f && isGreen == 0.0f){
            isBlue = 0.0f;
            isRed -= 0.01f;
            if(isRed < 0.01f)
            isGreen = 0.01f;
        }
		
		
        if(isGreen == 0.01f && isBlue == 0.0f){
            isRed += 0.01f;
             }

        if(isRed > 0.99f && isBlue == 0.0f){
            isRed = 1.0f;
            isGreen += 0.01f;
            }

        if(isGreen > 0.99f && isBlue == 0.0f){
            isGreen = 1.0f;
            isRed -= 0.01f;
        }

       if(isRed < 0.01f && isGreen == 1.0f){
            isRed = 0.0f;
            isBlue += 0.01f;
            }

        if(isBlue > 0.99f && isRed == 0.0f){
            isBlue = 1.0f;
            isGreen -= 0.01f;
            }
        if(isGreen < 0.01f && isBlue == 1.0f){
            isGreen = 0.0f;
            isRed += 0.01f;
            }
        if(isRed > 0.99f && isGreen == 0.0f){
            isRed = 1.0f;
            isBlue -= 0.01f;
            }
        if(isBlue < 0.01f && isGreen == 0.0f){
            isBlue = 0.0f;
            isRed -= 0.01f;
            if(isRed < 0.01f)
            isGreen = 0.01f;
        }
		
		
        if(isGreen == 0.01f && isBlue == 0.0f){
            isRed += 0.01f;
             }

        if(isRed > 0.99f && isBlue == 0.0f){
            isRed = 1.0f;
            isGreen += 0.01f;
            }

        if(isGreen > 0.99f && isBlue == 0.0f){
            isGreen = 1.0f;
            isRed -= 0.01f;
        }

       if(isRed < 0.01f && isGreen == 1.0f){
            isRed = 0.0f;
            isBlue += 0.01f;
            }

        if(isBlue > 0.99f && isRed == 0.0f){
            isBlue = 1.0f;
            isGreen -= 0.01f;
            }
        if(isGreen < 0.01f && isBlue == 1.0f){
            isGreen = 0.0f;
            isRed += 0.01f;
            }
        if(isRed > 0.99f && isGreen == 0.0f){
            isRed = 1.0f;
            isBlue -= 0.01f;
            }
        if(isBlue < 0.01f && isGreen == 0.0f){
            isBlue = 0.0f;
            isRed -= 0.01f;
            if(isRed < 0.01f)
            isGreen = 0.01f;
        }
		
		
		
        if(isGreen == 0.01f && isBlue == 0.0f){
            isRed += 0.01f;
             }

        if(isRed > 0.99f && isBlue == 0.0f){
            isRed = 1.0f;
            isGreen += 0.01f;
            }

        if(isGreen > 0.99f && isBlue == 0.0f){
            isGreen = 1.0f;
            isRed -= 0.01f;
        }

       if(isRed < 0.01f && isGreen == 1.0f){
            isRed = 0.0f;
            isBlue += 0.01f;
            }

        if(isBlue > 0.99f && isRed == 0.0f){
            isBlue = 1.0f;
            isGreen -= 0.01f;
            }
        if(isGreen < 0.01f && isBlue == 1.0f){
            isGreen = 0.0f;
            isRed += 0.01f;
            }
        if(isRed > 0.99f && isGreen == 0.0f){
            isRed = 1.0f;
            isBlue -= 0.01f;
            }
        if(isBlue < 0.01f && isGreen == 0.0f){
            isBlue = 0.0f;
            isRed -= 0.01f;
            if(isRed < 0.01f)
            isGreen = 0.01f;
        }
		
		
		
        if(isGreen == 0.01f && isBlue == 0.0f){
            isRed += 0.01f;
             }

        if(isRed > 0.99f && isBlue == 0.0f){
            isRed = 1.0f;
            isGreen += 0.01f;
            }

        if(isGreen > 0.99f && isBlue == 0.0f){
            isGreen = 1.0f;
            isRed -= 0.01f;
        }

       if(isRed < 0.01f && isGreen == 1.0f){
            isRed = 0.0f;
            isBlue += 0.01f;
            }

        if(isBlue > 0.99f && isRed == 0.0f){
            isBlue = 1.0f;
            isGreen -= 0.01f;
            }
        if(isGreen < 0.01f && isBlue == 1.0f){
            isGreen = 0.0f;
            isRed += 0.01f;
            }
        if(isRed > 0.99f && isGreen == 0.0f){
            isRed = 1.0f;
            isBlue -= 0.01f;
            }
        if(isBlue < 0.01f && isGreen == 0.0f){
            isBlue = 0.0f;
            isRed -= 0.01f;
            if(isRed < 0.01f)
            isGreen = 0.01f;
        }
		
		if(isGreen == 0.01f && isBlue == 0.0f){
            isRed += 0.01f;
             }

        if(isRed > 0.99f && isBlue == 0.0f){
            isRed = 1.0f;
            isGreen += 0.01f;
            }

        if(isGreen > 0.99f && isBlue == 0.0f){
            isGreen = 1.0f;
            isRed -= 0.01f;
        }

       if(isRed < 0.01f && isGreen == 1.0f){
            isRed = 0.0f;
            isBlue += 0.01f;
            }

        if(isBlue > 0.99f && isRed == 0.0f){
            isBlue = 1.0f;
            isGreen -= 0.01f;
            }
        if(isGreen < 0.01f && isBlue == 1.0f){
            isGreen = 0.0f;
            isRed += 0.01f;
            }
        if(isRed > 0.99f && isGreen == 0.0f){
            isRed = 1.0f;
            isBlue -= 0.01f;
            }
        if(isBlue < 0.01f && isGreen == 0.0f){
            isBlue = 0.0f;
            isRed -= 0.01f;
            if(isRed < 0.01f)
            isGreen = 0.01f;
        }
		
        if(isGreen == 0.01f && isBlue == 0.0f){
            isRed += 0.01f;
             }

        if(isRed > 0.99f && isBlue == 0.0f){
            isRed = 1.0f;
            isGreen += 0.01f;
            }

        if(isGreen > 0.99f && isBlue == 0.0f){
            isGreen = 1.0f;
            isRed -= 0.01f;
        }

       if(isRed < 0.01f && isGreen == 1.0f){
            isRed = 0.0f;
            isBlue += 0.01f;
            }

        if(isBlue > 0.99f && isRed == 0.0f){
            isBlue = 1.0f;
            isGreen -= 0.01f;
            }
        if(isGreen < 0.01f && isBlue == 1.0f){
            isGreen = 0.0f;
            isRed += 0.01f;
            }
        if(isRed > 0.99f && isGreen == 0.0f){
            isRed = 1.0f;
            isBlue -= 0.01f;
            }
        if(isBlue < 0.01f && isGreen == 0.0f){
            isBlue = 0.0f;
            isRed -= 0.01f;
            if(isRed < 0.01f)
            isGreen = 0.01f;
        }
		
		
        if(isGreen == 0.01f && isBlue == 0.0f){
            isRed += 0.01f;
             }

        if(isRed > 0.99f && isBlue == 0.0f){
            isRed = 1.0f;
            isGreen += 0.01f;
            }

        if(isGreen > 0.99f && isBlue == 0.0f){
            isGreen = 1.0f;
            isRed -= 0.01f;
        }

       if(isRed < 0.01f && isGreen == 1.0f){
            isRed = 0.0f;
            isBlue += 0.01f;
            }

        if(isBlue > 0.99f && isRed == 0.0f){
            isBlue = 1.0f;
            isGreen -= 0.01f;
            }
        if(isGreen < 0.01f && isBlue == 1.0f){
            isGreen = 0.0f;
            isRed += 0.01f;
            }
        if(isRed > 0.99f && isGreen == 0.0f){
            isRed = 1.0f;
            isBlue -= 0.01f;
            }
        if(isBlue < 0.01f && isGreen == 0.0f){
            isBlue = 0.0f;
            isRed -= 0.01f;
            if(isRed < 0.01f)
            isGreen = 0.01f;
        }
		
		
        if(isGreen == 0.01f && isBlue == 0.0f){
            isRed += 0.01f;
             }

        if(isRed > 0.99f && isBlue == 0.0f){
            isRed = 1.0f;
            isGreen += 0.01f;
            }

        if(isGreen > 0.99f && isBlue == 0.0f){
            isGreen = 1.0f;
            isRed -= 0.01f;
        }

       if(isRed < 0.01f && isGreen == 1.0f){
            isRed = 0.0f;
            isBlue += 0.01f;
            }

        if(isBlue > 0.99f && isRed == 0.0f){
            isBlue = 1.0f;
            isGreen -= 0.01f;
            }
        if(isGreen < 0.01f && isBlue == 1.0f){
            isGreen = 0.0f;
            isRed += 0.01f;
            }
        if(isRed > 0.99f && isGreen == 0.0f){
            isRed = 1.0f;
            isBlue -= 0.01f;
            }
        if(isBlue < 0.01f && isGreen == 0.0f){
            isBlue = 0.0f;
            isRed -= 0.01f;
            if(isRed < 0.01f)
            isGreen = 0.01f;
        }
		
		
        if(isGreen == 0.01f && isBlue == 0.0f){
            isRed += 0.01f;
             }

        if(isRed > 0.99f && isBlue == 0.0f){
            isRed = 1.0f;
            isGreen += 0.01f;
            }

        if(isGreen > 0.99f && isBlue == 0.0f){
            isGreen = 1.0f;
            isRed -= 0.01f;
        }

       if(isRed < 0.01f && isGreen == 1.0f){
            isRed = 0.0f;
            isBlue += 0.01f;
            }

        if(isBlue > 0.99f && isRed == 0.0f){
            isBlue = 1.0f;
            isGreen -= 0.01f;
            }
        if(isGreen < 0.01f && isBlue == 1.0f){
            isGreen = 0.0f;
            isRed += 0.01f;
            }
        if(isRed > 0.99f && isGreen == 0.0f){
            isRed = 1.0f;
            isBlue -= 0.01f;
            }
        if(isBlue < 0.01f && isGreen == 0.0f){
            isBlue = 0.0f;
            isRed -= 0.01f;
            if(isRed < 0.01f)
            isGreen = 0.01f;
        }
		
		
		
        if(isGreen == 0.01f && isBlue == 0.0f){
            isRed += 0.01f;
             }

        if(isRed > 0.99f && isBlue == 0.0f){
            isRed = 1.0f;
            isGreen += 0.01f;
            }

        if(isGreen > 0.99f && isBlue == 0.0f){
            isGreen = 1.0f;
            isRed -= 0.01f;
        }

       if(isRed < 0.01f && isGreen == 1.0f){
            isRed = 0.0f;
            isBlue += 0.01f;
            }

        if(isBlue > 0.99f && isRed == 0.0f){
            isBlue = 1.0f;
            isGreen -= 0.01f;
            }
        if(isGreen < 0.01f && isBlue == 1.0f){
            isGreen = 0.0f;
            isRed += 0.01f;
            }
        if(isRed > 0.99f && isGreen == 0.0f){
            isRed = 1.0f;
            isBlue -= 0.01f;
            }
        if(isBlue < 0.01f && isGreen == 0.0f){
            isBlue = 0.0f;
            isRed -= 0.01f;
            if(isRed < 0.01f)
            isGreen = 0.01f;
        }
		
		
		
        if(isGreen == 0.01f && isBlue == 0.0f){
            isRed += 0.01f;
             }

        if(isRed > 0.99f && isBlue == 0.0f){
            isRed = 1.0f;
            isGreen += 0.01f;
            }

        if(isGreen > 0.99f && isBlue == 0.0f){
            isGreen = 1.0f;
            isRed -= 0.01f;
        }

       if(isRed < 0.01f && isGreen == 1.0f){
            isRed = 0.0f;
            isBlue += 0.01f;
            }

        if(isBlue > 0.99f && isRed == 0.0f){
            isBlue = 1.0f;
            isGreen -= 0.01f;
            }
        if(isGreen < 0.01f && isBlue == 1.0f){
            isGreen = 0.0f;
            isRed += 0.01f;
            }
        if(isRed > 0.99f && isGreen == 0.0f){
            isRed = 1.0f;
            isBlue -= 0.01f;
            }
        if(isBlue < 0.01f && isGreen == 0.0f){
            isBlue = 0.0f;
            isRed -= 0.01f;
            if(isRed < 0.01f)
            isGreen = 0.01f;
        }
		
		
        if(isGreen == 0.01f && isBlue == 0.0f){
            isRed += 0.01f;
             }

        if(isRed > 0.99f && isBlue == 0.0f){
            isRed = 1.0f;
            isGreen += 0.01f;
            }

        if(isGreen > 0.99f && isBlue == 0.0f){
            isGreen = 1.0f;
            isRed -= 0.01f;
        }

       if(isRed < 0.01f && isGreen == 1.0f){
            isRed = 0.0f;
            isBlue += 0.01f;
            }

        if(isBlue > 0.99f && isRed == 0.0f){
            isBlue = 1.0f;
            isGreen -= 0.01f;
            }
        if(isGreen < 0.01f && isBlue == 1.0f){
            isGreen = 0.0f;
            isRed += 0.01f;
            }
        if(isRed > 0.99f && isGreen == 0.0f){
            isRed = 1.0f;
            isBlue -= 0.01f;
            }
        if(isBlue < 0.01f && isGreen == 0.0f){
            isBlue = 0.0f;
            isRed -= 0.01f;
            if(isRed < 0.01f)
            isGreen = 0.01f;
        }
		
        if(isGreen == 0.01f && isBlue == 0.0f){
            isRed += 0.01f;
             }

        if(isRed > 0.99f && isBlue == 0.0f){
            isRed = 1.0f;
            isGreen += 0.01f;
            }

        if(isGreen > 0.99f && isBlue == 0.0f){
            isGreen = 1.0f;
            isRed -= 0.01f;
        }

       if(isRed < 0.01f && isGreen == 1.0f){
            isRed = 0.0f;
            isBlue += 0.01f;
            }

        if(isBlue > 0.99f && isRed == 0.0f){
            isBlue = 1.0f;
            isGreen -= 0.01f;
            }
        if(isGreen < 0.01f && isBlue == 1.0f){
            isGreen = 0.0f;
            isRed += 0.01f;
            }
        if(isRed > 0.99f && isGreen == 0.0f){
            isRed = 1.0f;
            isBlue -= 0.01f;
            }
        if(isBlue < 0.01f && isGreen == 0.0f){
            isBlue = 0.0f;
            isRed -= 0.01f;
            if(isRed < 0.01f)
            isGreen = 0.01f;
        }
		
		
        if(isGreen == 0.01f && isBlue == 0.0f){
            isRed += 0.01f;
             }

        if(isRed > 0.99f && isBlue == 0.0f){
            isRed = 1.0f;
            isGreen += 0.01f;
            }

        if(isGreen > 0.99f && isBlue == 0.0f){
            isGreen = 1.0f;
            isRed -= 0.01f;
        }

       if(isRed < 0.01f && isGreen == 1.0f){
            isRed = 0.0f;
            isBlue += 0.01f;
            }

        if(isBlue > 0.99f && isRed == 0.0f){
            isBlue = 1.0f;
            isGreen -= 0.01f;
            }
        if(isGreen < 0.01f && isBlue == 1.0f){
            isGreen = 0.0f;
            isRed += 0.01f;
            }
        if(isRed > 0.99f && isGreen == 0.0f){
            isRed = 1.0f;
            isBlue -= 0.01f;
            }
        if(isBlue < 0.01f && isGreen == 0.0f){
            isBlue = 0.0f;
            isRed -= 0.01f;
            if(isRed < 0.01f)
            isGreen = 0.01f;
        }
		
		
        if(isGreen == 0.01f && isBlue == 0.0f){
            isRed += 0.01f;
             }

        if(isRed > 0.99f && isBlue == 0.0f){
            isRed = 1.0f;
            isGreen += 0.01f;
            }

        if(isGreen > 0.99f && isBlue == 0.0f){
            isGreen = 1.0f;
            isRed -= 0.01f;
        }

       if(isRed < 0.01f && isGreen == 1.0f){
            isRed = 0.0f;
            isBlue += 0.01f;
            }

        if(isBlue > 0.99f && isRed == 0.0f){
            isBlue = 1.0f;
            isGreen -= 0.01f;
            }
        if(isGreen < 0.01f && isBlue == 1.0f){
            isGreen = 0.0f;
            isRed += 0.01f;
            }
        if(isRed > 0.99f && isGreen == 0.0f){
            isRed = 1.0f;
            isBlue -= 0.01f;
            }
        if(isBlue < 0.01f && isGreen == 0.0f){
            isBlue = 0.0f;
            isRed -= 0.01f;
            if(isRed < 0.01f)
            isGreen = 0.01f;
        }
		
		
        if(isGreen == 0.01f && isBlue == 0.0f){
            isRed += 0.01f;
             }

        if(isRed > 0.99f && isBlue == 0.0f){
            isRed = 1.0f;
            isGreen += 0.01f;
            }

        if(isGreen > 0.99f && isBlue == 0.0f){
            isGreen = 1.0f;
            isRed -= 0.01f;
        }

       if(isRed < 0.01f && isGreen == 1.0f){
            isRed = 0.0f;
            isBlue += 0.01f;
            }

        if(isBlue > 0.99f && isRed == 0.0f){
            isBlue = 1.0f;
            isGreen -= 0.01f;
            }
        if(isGreen < 0.01f && isBlue == 1.0f){
            isGreen = 0.0f;
            isRed += 0.01f;
            }
        if(isRed > 0.99f && isGreen == 0.0f){
            isRed = 1.0f;
            isBlue -= 0.01f;
            }
        if(isBlue < 0.01f && isGreen == 0.0f){
            isBlue = 0.0f;
            isRed -= 0.01f;
            if(isRed < 0.01f)
            isGreen = 0.01f;
        }
		
		
		
        if(isGreen == 0.01f && isBlue == 0.0f){
            isRed += 0.01f;
             }

        if(isRed > 0.99f && isBlue == 0.0f){
            isRed = 1.0f;
            isGreen += 0.01f;
            }

        if(isGreen > 0.99f && isBlue == 0.0f){
            isGreen = 1.0f;
            isRed -= 0.01f;
        }

       if(isRed < 0.01f && isGreen == 1.0f){
            isRed = 0.0f;
            isBlue += 0.01f;
            }

        if(isBlue > 0.99f && isRed == 0.0f){
            isBlue = 1.0f;
            isGreen -= 0.01f;
            }
        if(isGreen < 0.01f && isBlue == 1.0f){
            isGreen = 0.0f;
            isRed += 0.01f;
            }
        if(isRed > 0.99f && isGreen == 0.0f){
            isRed = 1.0f;
            isBlue -= 0.01f;
            }
        if(isBlue < 0.01f && isGreen == 0.0f){
            isBlue = 0.0f;
            isRed -= 0.01f;
            if(isRed < 0.01f)
            isGreen = 0.01f;
        }
		
		
		
        if(isGreen == 0.01f && isBlue == 0.0f){
            isRed += 0.01f;
             }

        if(isRed > 0.99f && isBlue == 0.0f){
            isRed = 1.0f;
            isGreen += 0.01f;
            }

        if(isGreen > 0.99f && isBlue == 0.0f){
            isGreen = 1.0f;
            isRed -= 0.01f;
        }

       if(isRed < 0.01f && isGreen == 1.0f){
            isRed = 0.0f;
            isBlue += 0.01f;
            }

        if(isBlue > 0.99f && isRed == 0.0f){
            isBlue = 1.0f;
            isGreen -= 0.01f;
            }
        if(isGreen < 0.01f && isBlue == 1.0f){
            isGreen = 0.0f;
            isRed += 0.01f;
            }
        if(isRed > 0.99f && isGreen == 0.0f){
            isRed = 1.0f;
            isBlue -= 0.01f;
            }
        if(isBlue < 0.01f && isGreen == 0.0f){
            isBlue = 0.0f;
            isRed -= 0.01f;
            if(isRed < 0.01f)
            isGreen = 0.01f;
        }
		
		if(isGreen == 0.01f && isBlue == 0.0f){
            isRed += 0.01f;
             }

        if(isRed > 0.99f && isBlue == 0.0f){
            isRed = 1.0f;
            isGreen += 0.01f;
            }

        if(isGreen > 0.99f && isBlue == 0.0f){
            isGreen = 1.0f;
            isRed -= 0.01f;
        }

       if(isRed < 0.01f && isGreen == 1.0f){
            isRed = 0.0f;
            isBlue += 0.01f;
            }

        if(isBlue > 0.99f && isRed == 0.0f){
            isBlue = 1.0f;
            isGreen -= 0.01f;
            }
        if(isGreen < 0.01f && isBlue == 1.0f){
            isGreen = 0.0f;
            isRed += 0.01f;
            }
        if(isRed > 0.99f && isGreen == 0.0f){
            isRed = 1.0f;
            isBlue -= 0.01f;
            }
        if(isBlue < 0.01f && isGreen == 0.0f){
            isBlue = 0.0f;
            isRed -= 0.01f;
            if(isRed < 0.01f)
            isGreen = 0.01f;
        }
		
        if(isGreen == 0.01f && isBlue == 0.0f){
            isRed += 0.01f;
             }

        if(isRed > 0.99f && isBlue == 0.0f){
            isRed = 1.0f;
            isGreen += 0.01f;
            }

        if(isGreen > 0.99f && isBlue == 0.0f){
            isGreen = 1.0f;
            isRed -= 0.01f;
        }

       if(isRed < 0.01f && isGreen == 1.0f){
            isRed = 0.0f;
            isBlue += 0.01f;
            }

        if(isBlue > 0.99f && isRed == 0.0f){
            isBlue = 1.0f;
            isGreen -= 0.01f;
            }
        if(isGreen < 0.01f && isBlue == 1.0f){
            isGreen = 0.0f;
            isRed += 0.01f;
            }
        if(isRed > 0.99f && isGreen == 0.0f){
            isRed = 1.0f;
            isBlue -= 0.01f;
            }
        if(isBlue < 0.01f && isGreen == 0.0f){
            isBlue = 0.0f;
            isRed -= 0.01f;
            if(isRed < 0.01f)
            isGreen = 0.01f;
        }
		
		
        if(isGreen == 0.01f && isBlue == 0.0f){
            isRed += 0.01f;
             }

        if(isRed > 0.99f && isBlue == 0.0f){
            isRed = 1.0f;
            isGreen += 0.01f;
            }

        if(isGreen > 0.99f && isBlue == 0.0f){
            isGreen = 1.0f;
            isRed -= 0.01f;
        }

       if(isRed < 0.01f && isGreen == 1.0f){
            isRed = 0.0f;
            isBlue += 0.01f;
            }

        if(isBlue > 0.99f && isRed == 0.0f){
            isBlue = 1.0f;
            isGreen -= 0.01f;
            }
        if(isGreen < 0.01f && isBlue == 1.0f){
            isGreen = 0.0f;
            isRed += 0.01f;
            }
        if(isRed > 0.99f && isGreen == 0.0f){
            isRed = 1.0f;
            isBlue -= 0.01f;
            }
        if(isBlue < 0.01f && isGreen == 0.0f){
            isBlue = 0.0f;
            isRed -= 0.01f;
            if(isRed < 0.01f)
            isGreen = 0.01f;
        }
		
		
        if(isGreen == 0.01f && isBlue == 0.0f){
            isRed += 0.01f;
             }

        if(isRed > 0.99f && isBlue == 0.0f){
            isRed = 1.0f;
            isGreen += 0.01f;
            }

        if(isGreen > 0.99f && isBlue == 0.0f){
            isGreen = 1.0f;
            isRed -= 0.01f;
        }

       if(isRed < 0.01f && isGreen == 1.0f){
            isRed = 0.0f;
            isBlue += 0.01f;
            }

        if(isBlue > 0.99f && isRed == 0.0f){
            isBlue = 1.0f;
            isGreen -= 0.01f;
            }
        if(isGreen < 0.01f && isBlue == 1.0f){
            isGreen = 0.0f;
            isRed += 0.01f;
            }
        if(isRed > 0.99f && isGreen == 0.0f){
            isRed = 1.0f;
            isBlue -= 0.01f;
            }
        if(isBlue < 0.01f && isGreen == 0.0f){
            isBlue = 0.0f;
            isRed -= 0.01f;
            if(isRed < 0.01f)
            isGreen = 0.01f;
        }
		
		
        if(isGreen == 0.01f && isBlue == 0.0f){
            isRed += 0.01f;
             }

        if(isRed > 0.99f && isBlue == 0.0f){
            isRed = 1.0f;
            isGreen += 0.01f;
            }

        if(isGreen > 0.99f && isBlue == 0.0f){
            isGreen = 1.0f;
            isRed -= 0.01f;
        }

       if(isRed < 0.01f && isGreen == 1.0f){
            isRed = 0.0f;
            isBlue += 0.01f;
            }

        if(isBlue > 0.99f && isRed == 0.0f){
            isBlue = 1.0f;
            isGreen -= 0.01f;
            }
        if(isGreen < 0.01f && isBlue == 1.0f){
            isGreen = 0.0f;
            isRed += 0.01f;
            }
        if(isRed > 0.99f && isGreen == 0.0f){
            isRed = 1.0f;
            isBlue -= 0.01f;
            }
        if(isBlue < 0.01f && isGreen == 0.0f){
            isBlue = 0.0f;
            isRed -= 0.01f;
            if(isRed < 0.01f)
            isGreen = 0.01f;
        }
		
		
        if(isGreen == 0.01f && isBlue == 0.0f){
            isRed += 0.01f;
             }

        if(isRed > 0.99f && isBlue == 0.0f){
            isRed = 1.0f;
            isGreen += 0.01f;
            }

        if(isGreen > 0.99f && isBlue == 0.0f){
            isGreen = 1.0f;
            isRed -= 0.01f;
        }

       if(isRed < 0.01f && isGreen == 1.0f){
            isRed = 0.0f;
            isBlue += 0.01f;
            }

        if(isBlue > 0.99f && isRed == 0.0f){
            isBlue = 1.0f;
            isGreen -= 0.01f;
            }
        if(isGreen < 0.01f && isBlue == 1.0f){
            isGreen = 0.0f;
            isRed += 0.01f;
            }
        if(isRed > 0.99f && isGreen == 0.0f){
            isRed = 1.0f;
            isBlue -= 0.01f;
            }
        if(isBlue < 0.01f && isGreen == 0.0f){
            isBlue = 0.0f;
            isRed -= 0.01f;
            if(isRed < 0.01f)
            isGreen = 0.01f;
        }
		
		
        if(isGreen == 0.01f && isBlue == 0.0f){
            isRed += 0.01f;
             }

        if(isRed > 0.99f && isBlue == 0.0f){
            isRed = 1.0f;
            isGreen += 0.01f;
            }

        if(isGreen > 0.99f && isBlue == 0.0f){
            isGreen = 1.0f;
            isRed -= 0.01f;
        }

       if(isRed < 0.01f && isGreen == 1.0f){
            isRed = 0.0f;
            isBlue += 0.01f;
            }

        if(isBlue > 0.99f && isRed == 0.0f){
            isBlue = 1.0f;
            isGreen -= 0.01f;
            }
        if(isGreen < 0.01f && isBlue == 1.0f){
            isGreen = 0.0f;
            isRed += 0.01f;
            }
        if(isRed > 0.99f && isGreen == 0.0f){
            isRed = 1.0f;
            isBlue -= 0.01f;
            }
        if(isBlue < 0.01f && isGreen == 0.0f){
            isBlue = 0.0f;
            isRed -= 0.01f;
            if(isRed < 0.01f)
            isGreen = 0.01f;
        }
		
 
    }
	
/*draw->AddText(NULL, ((float) density / 17.0f),{(float) glWidth / 150 + glWidth / 40,556},IM_COL32(9, 237, 230, 255), "               JAAT X REVOLUTION KIRAAK");
draw->AddText(NULL, ((float) density / 19.0f),{(float) glWidth / 150 + glWidth / 15,600},IM_COL32(9, 237, 17, 255), "Play safe | Send feedbacks @OPxJAAT");
*/
    if (Config.OTHER.HIDEESP) {
        HIDEESP = false;
    } else {
        HIDEESP = true;
    }
    if (HIDEESP) {

		//auto GetTargetByPussy() {
       ASTExtraPlayerCharacter *result = 0;
       float max = std::numeric_limits<float>::infinity();
		
        auto Actors = getActors();

        int totalEnemies = 0, totalBots = 0;

        ASTExtraPlayerCharacter *localPlayer = 0;
        ASTExtraPlayerController *localController = 0;


        std::string sFPS = "FPS: ";
        sFPS += std::to_string(fps.get());

             if (Config.OTHER.FPS) {
			
            draw->AddText({ ((float) density / 10.0f), 160}, IM_COL32(0,255,0, 255),
			              sFPS.c_str());
        }
		
		if (Config.OTHER.EXP) {
		
		
        }


        for (int i = 0; i < Actors.size(); i++) {
            auto Actor = Actors[i];
            if (isObjectInvalid(Actor))
                continue;

            if (Actor->IsA(ASTExtraPlayerController::StaticClass())) {
                localController = (ASTExtraPlayerController *) Actor;
                break;
            }
        }
		
		//Floating2
		
		if (localController ==0){
			std::string sFPS = "";
			draw->AddText({((float) density / 10.0f), 40},IM_COL32(255, 0, 0, 0),sFPS.c_str());
			}else{
            std::string sFPS = "Frem Rate : ";
            sFPS += std::to_string(fps.get());
            draw->AddText({((float) density / 10.0f), 40},IM_COL32(255, 155, 0, 0),sFPS.c_str());
        }

        if (localController) {
            for (int i = 0; i < Actors.size(); i++) {
                auto Actor = Actors[i];
                if (isObjectInvalid(Actor))
                    continue;

                if (Actor->IsA(ASTExtraPlayerCharacter::StaticClass())) {
                    if (((ASTExtraPlayerCharacter *) Actor)->PlayerKey ==
                        localController->PlayerKey) {
                        localPlayer = (ASTExtraPlayerCharacter *) Actor;
                        break;
                    }
                }
            }


            if (localPlayer) {
        if (localPlayer->PartHitComponent) {
            auto ConfigCollisionDistSqAngles = localPlayer->PartHitComponent->ConfigCollisionDistSqAngles;
            auto numAngles = ConfigCollisionDistSqAngles.Num();
            for (int j = numAngles - 1; j >= 0; j--) {
            int numAnglesIndex = numAngles - j -1;
            float offset = sin(j* 0.2f + 0.3f)* 2.0f;
            float baseAngle = numAnglesIndex % 2 == 0 ? 170.0f : -190.0f;
            ConfigCollisionDistSqAngles[j].Angle = baseAngle + offset;
            localPlayer->PartHitComponent->ConfigCollisionDistSqAngles = ConfigCollisionDistSqAngles;
            }}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\\




//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\\
				
                static bool bShooting = false;
                  if (Config.SilentAim.Enable) {
    auto WeaponManagerComponent = localPlayer->WeaponManagerComponent;
    if (WeaponManagerComponent) {
        auto propSlot = WeaponManagerComponent->GetCurrentUsingPropSlot();
        if ((int)propSlot.GetValue() >= 1 && (int)propSlot.GetValue() <= 3) {
            auto CurrentWeaponReplicated = (ASTExtraShootWeapon*)WeaponManagerComponent->CurrentWeaponReplicated;
            if (CurrentWeaponReplicated) {
                auto ShootWeaponComponent = CurrentWeaponReplicated->ShootWeaponComponent;
                if (ShootWeaponComponent) {
                    int shoot_event_idx = 168;
                    auto VTable = *(void ***) (ShootWeaponComponent);
                    auto f_mprotect = [](uintptr_t addr, size_t len, int32_t prot) -> int32_t {
                      static_assert(PAGE_SIZE == 4096);
                     constexpr size_t page_size = static_cast<size_t>(PAGE_SIZE);
                      void* start = reinterpret_cast<void*>(addr & -page_size);
                      uintptr_t end = (addr + len + page_size - 1) & -page_size;
                      return mprotect(start, end - reinterpret_cast<uintptr_t>(start), prot);
                   };
                   if(VTable){
                    uintptr_t table_entry = reinterpret_cast<uintptr_t>(&VTable[shoot_event_idx]); 
                    if (VTable && (VTable[shoot_event_idx] != shoot_event)) {                      
                        orig_shoot_event = decltype(orig_shoot_event)(VTable[shoot_event_idx]);
                        f_mprotect((uintptr_t)(&VTable[shoot_event_idx]), sizeof(uintptr_t), PROT_READ | PROT_WRITE);                                                          
                        uintptr_t new_func_ptr = reinterpret_cast<uintptr_t>(&shoot_event);
                        VTable[shoot_event_idx] = reinterpret_cast<void*>(new_func_ptr);
                        f_mprotect(table_entry, sizeof(uintptr_t), PROT_READ | PROT_EXEC);
                        }
                    }
                }
            }
        }
    }
}
                //Aimbot//
                if (Config.AimBot.Enable) {
                    ASTExtraPlayerCharacter *Target = GetTargetForAimBot();
                    if (Target) {
                        bool triggerOk = false;
                        if (Config.AimBot.Trigger != EAimTrigger::None) {
                            if (Config.AimBot.Trigger == EAimTrigger::Shooting) {
                                triggerOk = localPlayer->bIsWeaponFiring;
                            } else if (Config.AimBot.Trigger == EAimTrigger::Scoping) {
                                triggerOk = localPlayer->bIsGunADS;
                            } else if (Config.AimBot.Trigger == EAimTrigger::Both) {
                                triggerOk = localPlayer->bIsWeaponFiring && localPlayer->bIsGunADS;
                            } else if (Config.AimBot.Trigger == EAimTrigger::Any) {
                                triggerOk = localPlayer->bIsWeaponFiring || localPlayer->bIsGunADS;
                            }
                        } else triggerOk = true;
                        if (triggerOk) {
                            FVector targetAimPos = Target->GetBonePos("Head", {});
                            if (Config.AimBot.Target == EAimTarget::Chest) {
                                targetAimPos.Z -= 25.0f;
                            }

                            auto WeaponManagerComponent = localPlayer->WeaponManagerComponent;
                            if (WeaponManagerComponent) {
                                auto propSlot = WeaponManagerComponent->GetCurrentUsingPropSlot();
                                if ((int) propSlot.GetValue() >= 1 &&
                                    (int) propSlot.GetValue() <= 3) {
                                    auto CurrentWeaponReplicated = (ASTExtraShootWeapon *) WeaponManagerComponent->CurrentWeaponReplicated;
                                    if (CurrentWeaponReplicated) {
                                        auto ShootWeaponComponent = CurrentWeaponReplicated->ShootWeaponComponent;
                                        if (ShootWeaponComponent) {
                                            UShootWeaponEntity *ShootWeaponEntityComponent = ShootWeaponComponent->ShootWeaponEntityComponent;
                                            if (ShootWeaponEntityComponent) {
                                                ASTExtraVehicleBase *CurrentVehicle = Target->CurrentVehicle;
                                                if (CurrentVehicle) {
                                                    FVector LinearVelocity = CurrentVehicle->ReplicatedMovement.LinearVelocity;

                                                    float dist = localPlayer->GetDistanceTo(Target);
                                                    auto timeToTravel = dist /
                                                                        ShootWeaponEntityComponent->BulletFireSpeed;

                                                    targetAimPos = UKismetMathLibrary::Add_VectorVector(
                                                            targetAimPos,
                                                            UKismetMathLibrary::Multiply_VectorFloat(
                                                                    LinearVelocity, timeToTravel));
                                                } else {
                                                    FVector Velocity = Target->GetVelocity();

                                                    float dist = localPlayer->GetDistanceTo(Target);
                                                    auto timeToTravel = dist /
                                                                        ShootWeaponEntityComponent->BulletFireSpeed;

                                                    targetAimPos = UKismetMathLibrary::Add_VectorVector(
                                                            targetAimPos,
                                                            UKismetMathLibrary::Multiply_VectorFloat(
                                                                    Velocity, timeToTravel));
                                                }
                                                localController->SetControlRotation(ToRotator(
                                                        localController->PlayerCameraManager->CameraCache.POV.Location,
                                                        targetAimPos), "");
														
                                            if (Config.AimBot.RecoilComparison) {
                                                    if (g_LocalPlayer->bIsGunADS) {
                                                        if (g_LocalPlayer->bIsWeaponFiring) {
                                                            float dist = g_LocalPlayer->GetDistanceTo(Target) / 100.f;                                                                                 
                                                            targetAimPos.Z -= dist * Config.AimBot.Recc;
                                                        }  
                                                    }
                                                }
                                                localController->SetControlRotation(ToRotator(localController->PlayerCameraManager->CameraCache.POV.Location, targetAimPos), "");
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                  }
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\\


                for (auto &i : Actors) {
                auto Actor = i;
                if (isObjectInvalid(Actor))
                    continue;

                if (Actor->IsA(ASTExtraPlayerCharacter::StaticClass())) {
                    auto Player = (ASTExtraPlayerCharacter *) Actor;

                    float Distance = localPlayer->GetDistanceTo(Player) / 100.0f;
                    if (Distance > 500)
                        continue;

                    if (Player->PlayerKey == localController->PlayerKey)
                        continue;

                    if (Player->TeamID == localController->TeamID)
                        continue;

                    if (Player->bDead)
                        continue;
				
					int healthOutline;
                    if (!Player->Mesh)
                        continue;

                    if (Player->bEnsure)
                        totalBots++;
                    else totalEnemies++;

                    if (Config.PlayerESP.NoBot)
                        if (Player->bEnsure)
                            continue;

                    float magic_number = (Distance);
                    float mx = (glWidth / 4) / magic_number;

                    float healthLength = glWidth / 19;
                    if (healthLength < mx)
                        healthLength = mx;

                    auto HeadPos = Player->GetBonePos("Head", {});
                    ImVec2 HeadPosSC;

                    auto RootPos = Player->GetBonePos("Root", {});
                    ImVec2 RootPosSC;
                    auto upper_r = Player->GetBonePos("upperarm_r", {});
                    ImVec2 upper_rPoSC;
                    auto lowerarm_r = Player->GetBonePos("lowerarm_r", {});
                    ImVec2 lowerarm_rPoSC;
                    auto hand_r = Player->GetBonePos("hand_r", {});
                    ImVec2 hand_rPoSC;
                    auto upper_l = Player->GetBonePos("upperarm_l", {});
                    ImVec2 upper_lPoSC;
                    auto lowerarm_l = Player->GetBonePos("lowerarm_l", {});
                    ImVec2 lowerarm_lSC;
                    auto hand_l = Player->GetBonePos("hand_l", {});
                    ImVec2 hand_lPoSC;
                    auto thigh_l = Player->GetBonePos("thigh_l", {});
                    ImVec2 thigh_lPoSC;
                    auto calf_l = Player->GetBonePos("calf_l", {});
                    ImVec2 calf_lPoSC;
                    auto foot_l = Player->GetBonePos("foot_l", {});
                    ImVec2 foot_lPoSC;
                    auto thigh_r = Player->GetBonePos("thigh_r", {});
                    ImVec2 thigh_rPoSC;
                    auto calf_r = Player->GetBonePos("calf_r", {});
                    ImVec2 calf_rPoSC;
                    auto foot_r = Player->GetBonePos("foot_r", {});
                    ImVec2 foot_rPoSC;
                    auto neck_01 = Player->GetBonePos("neck_01", {});
                    ImVec2 neck_01PoSC;
                    auto Pelvis = Player->GetBonePos("Pelvis", {});
                    ImVec2 PelvisPoSC;

                    bool IsVisible = localController->LineOfSightTo(Player, {0, 0, 0}, true);

                    int SCOLOR, SCOLOR2;

                    if (IsVisible)
                    {
                        SCOLOR = ToColor(Config.ColorsESP.SkeletonVisible);
                        SCOLOR2 = IM_COL32(0, 255, 0, 255);
                    }else{
                        SCOLOR = ToColor(Config.ColorsESP.Skeleton);
                        SCOLOR2 = IM_COL32(255, 255, 255, 255);
                    }

                    if (W2S(HeadPos, (FVector2D *) &HeadPosSC) &&
                        W2S(upper_r, (FVector2D *) &upper_rPoSC) &&
                        W2S(upper_l, (FVector2D *) &upper_lPoSC) &&
                        W2S(lowerarm_r, (FVector2D *) &lowerarm_rPoSC ) &&
                        W2S(hand_r, (FVector2D *) &hand_rPoSC ) &&
                        W2S(lowerarm_l, (FVector2D *) &lowerarm_lSC ) &&
                        W2S(hand_l, (FVector2D *) &hand_lPoSC ) &&
                        W2S(thigh_l, (FVector2D *) &thigh_lPoSC ) &&
                        W2S(calf_l, (FVector2D *) &calf_lPoSC ) &&
                        W2S(foot_l, (FVector2D *) &foot_lPoSC ) &&
                        W2S(thigh_r, (FVector2D *) &thigh_rPoSC ) &&
                        W2S(calf_r, (FVector2D *) &calf_rPoSC ) &&
                        W2S(foot_r, (FVector2D *) &foot_rPoSC ) &&
                        W2S(neck_01, (FVector2D *) &neck_01PoSC ) &&
                        W2S(Pelvis, (FVector2D *) &PelvisPoSC ) &&
                        W2S(RootPos, (FVector2D *) &RootPosSC)){

                        if (Distance < 350.0f && totalEnemies > 0 || totalBots > 0) {

                            if (Config.PlayerESP.Line) {
                                draw->AddLine({(float) glWidth / 2, 0}, ImVec2(HeadPosSC.x, HeadPosSC.y - 55.0f), SCOLOR2, 1.5f);
                            }
                            if (Config.PlayerESP.Box) {
                                float boxHeight = abs(HeadPosSC.y - RootPosSC.y);
                                float boxWidth = boxHeight * 0.65f;
                             //   Box4Line(draw, 0.2f, HeadPosSC.x - (boxWidth / 2), HeadPosSC.y, boxWidth, boxHeight,  GetRandomColorByIndexAlpa(Player->TeamID));
                            }
                            if (Config.PlayerESP.Skeleton) {
                                draw->AddLine({upper_rPoSC.x, upper_rPoSC.y}, neck_01PoSC, SCOLOR, 1.5f);
                                draw->AddLine({upper_lPoSC.x, upper_lPoSC.y}, neck_01PoSC, SCOLOR, 1.5f);

                                draw->AddLine({upper_rPoSC.x, upper_rPoSC.y}, lowerarm_rPoSC, SCOLOR, 1.5f);
                                draw->AddLine({lowerarm_rPoSC.x, lowerarm_rPoSC.y}, hand_rPoSC, SCOLOR , 1.5f);

                                draw->AddLine({upper_lPoSC.x, upper_lPoSC.y}, lowerarm_lSC, SCOLOR, 1.5f);
                                draw->AddLine({lowerarm_lSC.x, lowerarm_lSC.y}, hand_lPoSC, SCOLOR, 1.5f);

                                draw->AddLine({thigh_rPoSC.x, thigh_rPoSC.y}, thigh_lPoSC, SCOLOR, 1.5f);

                                draw->AddLine({thigh_lPoSC.x, thigh_lPoSC.y}, calf_lPoSC, SCOLOR, 1.5f);
                                draw->AddLine({calf_lPoSC.x, calf_lPoSC.y}, foot_lPoSC, SCOLOR, 1.5f);

                                draw->AddLine({thigh_rPoSC.x, thigh_rPoSC.y}, calf_rPoSC, SCOLOR, 1.5f);
                                draw->AddLine({calf_rPoSC.x, calf_rPoSC.y}, foot_rPoSC, SCOLOR, 1.5f);

                                draw->AddLine({neck_01PoSC.x, neck_01PoSC.y}, PelvisPoSC, SCOLOR, 1.5f);
                                draw->AddLine({neck_01PoSC.x, neck_01PoSC.y}, HeadPosSC, SCOLOR, 1.5f);

								
                            }

							}
							if (Config.PlayerESP.Grenade) {
                if (Actor->IsA(ASTExtraGrenadeBase::StaticClass())) {
                                auto Grenade = (ASTExtraGrenadeBase *) Actor;
                                auto RootComponent = Actor->RootComponent;
                                if (!RootComponent)
                                    continue;
                                float Distance = Grenade->GetDistanceTo(localPlayer) / 100.f;

                                FVector2D grenadePos;
                                if (Config.PlayerESP.Grenade) {
                                    FVector Cross;
                            Cross.X = 1000.0f; 
                            Cross.Y = 1000.0f; // Front
                            Cross.Z = 1.0f; // Height
                            
                            
                                Box3D1(draw, Grenade->K2_GetActorLocation(), Cross, IM_COL32(255, 255, 255, 255));							
                                }
                                
                                
                                if (Config.PlayerESP.Grenade) {
                                    FVector Cross;
                            Cross.X = 700.0f; 
                            Cross.Y = 700.0f; // Front
                            Cross.Z = 3.0f; // Height
                                Box3D1(draw, Grenade->K2_GetActorLocation(), Cross, IM_COL32(255, 200, 0, 255));							
                                                                }
                                                                
                         if (Config.PlayerESP.Grenade) {
                                    FVector Cross;
                            Cross.X = 400.0f; 
                            Cross.Y = 400.0f; // Front
                            Cross.Z = 3.0f; // Height
                                Box3D1(draw, Grenade->K2_GetActorLocation(), Cross, IM_COL32(255, 0, 84, 255));							
                                                                }
                                                                
                        if (Config.PlayerESP.Grenade) {
                                    FVector Cross;
                            Cross.X = 250.0f; 
                            Cross.Y = 250.0f; // Front
                            Cross.Z = 3.0f; // Height
                                Box3D1(draw, Grenade->K2_GetActorLocation(), Cross, IM_COL32(255, 0, 0, 255));							
                                                                }
                                                                
                              if (Config.PlayerESP.Grenade) {
                                    FVector Cross;
                            Cross.X = 100.0f; 
                            Cross.Y = 100.0f; // Front
                            Cross.Z = 3.0f; // Height
                                Box3D1(draw, Grenade->K2_GetActorLocation(), Cross, IM_COL32(255, 200, 0, 255));							
                                                                }                                  
                                

                                if (W2S(Grenade->K2_GetActorLocation(), &grenadePos)) {
                                    std::string s = "Grenade";
                                    s += "[";
                                    s += std::to_string((int) Distance);
                                    s += "M]";

                                    draw->AddText(NULL, ((float) density / 10.0f),
                                                  {grenadePos.X, grenadePos.Y},
                                                  IM_COL32(255, 255, 255, 255), s.c_str());
                                }
                            }
                        }
				
							
                                            
                              if (Config.PlayerESP.Health) {
                                   int CurHP = (int) std::max(0, std::min((int) Player->Health,
                                                                           (int) Player->HealthMax));
                                    int MaxHP = (int) Player->HealthMax;

                                    long HPColor = IM_COL32(255, 0, 0, 60);
                                    long HPRectColor = IM_COL32(255, 255, 255, 200);

                                    if (Player->Health == 0.0f && !Player->bDead) {
                                        HPColor = IM_COL32(255, 0, 0, 60);

                                        CurHP = Player->NearDeathBreath;
                                        if (Player->NearDeatchComponent) {
                                            MaxHP = Player->NearDeatchComponent->BreathMax;
                                        }
                                    }

                                  
                                                float boxWidth = density / 1.6f;
                                                boxWidth -= std::min(
                                                ((boxWidth / 2) / 0.001f) * Distance,
                                                boxWidth / 2);
                                                float boxHeight = boxWidth * 0.15f;
                                                ImVec2 vStart = {HeadPosSC.x - (boxWidth / 2),
                                                HeadPosSC.y -
                                                (boxHeight * 2.001f)};
                                                ImVec2 vEndFilled = {
                                                vStart.x + (CurHP * boxWidth / MaxHP),
                                                vStart.y + boxHeight};
                                                ImVec2 vEndRect = {vStart.x + boxWidth,
                                                vStart.y + boxHeight};
                                                draw->AddRectFilled(vStart, vEndFilled, HPColor,
                                                11.0f);
                                                draw->AddRect(vStart, vEndRect,
                                                healthOutline, 11.0f);
                        }                        
								

                                    if (Config.PlayerESP.TeamID) {
                         float boxWidth = density / 2.0f;
                                               boxWidth -= std::min(
                                               ((boxWidth / 2) / 00.0f) * Distance,
                                               boxWidth / 2);
                                               float boxHeight = boxWidth * 0.19f;
                                               std::string s;
                                               s += std::to_string(Player->TeamID);
                                               draw->AddText(NULL, ((float) density / 30.0f),
                                               {HeadPosSC.x - (boxWidth / 1.7),
                                               HeadPosSC.y - (boxHeight * 1.83f)},
                                               IM_COL32(255, 255, 255, 255),
                                               s.c_str());
                        }


                        if (Config.PlayerESP.Name) {
                            float boxWidth = density / 2.0f;
                                               boxWidth -= std::min(
                                               ((boxWidth / 2) / 00.0f) * Distance,
                                               boxWidth / 2);
                                               float boxHeight = boxWidth * 0.19f;
                                               std::string s;
                                               if (Player->bIsAI) {
                                               s += "    Ai ";
                                               } else {
                                               s += Player->PlayerName.ToString();
                                               }
                                               draw->AddText(NULL, ((float) density / 30.0f),
                                               {HeadPosSC.x - (boxWidth / 3.3),
                                               HeadPosSC.y - (boxHeight * 1.83f)},
                                               IM_COL32(255, 255, 255, 255),
                                               s.c_str());
                        }
							if (Config.PlayerESP.Distance) {
                        float boxWidth = density / 1.8f;
                                               boxWidth -= std::min(
                                               ((boxWidth / 2) / 00.0f) * Distance,
                                               boxWidth / 2);
                                               float boxHeight = boxWidth * 0.20f;
                            std::string s;
							        s += "";
                                    s += std::to_string((int) Distance);
                                    s += "m";
         draw->AddText(NULL, ((float) density / 30.0f), {HeadPosSC.x - 20, HeadPosSC.y - 58}, IM_COL32(255, 255, 255, 255), s.c_str());
                    }
                    }
                }

                if (Config.PlayerESP.Vehicle) {
					Config.PlayerESP.Line = true;
                    if (i->IsA(ASTExtraVehicleBase::StaticClass())) {
                        auto Vehicle = (ASTExtraVehicleBase *) i;

                        if (!Vehicle->Mesh)
                            continue;

                        float Distance = Vehicle->GetDistanceTo(localPlayer) / 100.f;

                        FVector2D vehiclePos;
                        if (W2S(Vehicle->K2_GetActorLocation(), &vehiclePos)) {
                            std::string s = "[";
                                s += GetVehicleName(Vehicle);
                            s += "-";
                                s += std::to_string((int) Distance);
                                s += "M]";

                            draw->AddText(NULL, ((float) density / 20.0f), {vehiclePos.X, vehiclePos.Y}, ToColor(Config.ColorsESP.Vehicle), s.c_str());
                        }
                    }
                }

                if (i->IsA(APickUpWrapperActor::StaticClass())) {
                    auto PickUp = (APickUpWrapperActor *) i;
                    if (Items[PickUp->DefineID.TypeSpecificID]) {
                        auto RootComponent = PickUp->RootComponent;
                        if (!RootComponent)
                            continue;

                        float Distance = PickUp->GetDistanceTo(localPlayer) / 100.f;

                        FVector2D itemPos;
                            if (W2S(PickUp->K2_GetActorLocation(), &itemPos)) {
                                std::string s;
                                uint32_t tc = 0xFF000000;

                                for (auto &category: items_data) {
                                    for (auto &item: category["Items"]) {
                                        if (item["itemId"] == PickUp->DefineID.TypeSpecificID) {
                                            s = item["itemName"].get<std::string>();
                                            tc = strtoul(
                                                    item["itemTextColor"].get<std::string>().c_str(),
                                                    0, 16);
                                            break;
                                    }
                                }
                            }

                            s += " - ";
                            s += std::to_string((int) Distance);
                            s += "M]";
							
							draw->AddText(NULL, ((float) density / 20.0f),
                                              {itemPos.X, itemPos.Y}, tc, s.c_str());
                        }
                    }
                }
            }
        }
    }
     g_LocalController = localController;
           g_LocalPlayer = localPlayer;
    
	
	 
        std::string s;
        if (totalEnemies + totalBots > 0) {
            std::string s;
            if (totalEnemies + totalBots < 10)
                s += "     ";
            else s += "    ";
            s += std::to_string((int) totalEnemies + totalBots);
            draw->AddRectFilled(ImVec2(glWidth / 2 - 68, 61.5), ImVec2(glWidth / 2 + 68, 85.5), IM_COL32(255, 0, 0, 15));
            draw->AddRectFilled(ImVec2(glWidth / 2 - 60, 61.5), ImVec2(glWidth / 2 + 60, 85.5), IM_COL32(255, 0, 0, 15));
            draw->AddRectFilled(ImVec2(glWidth / 2 - 56, 61.5), ImVec2(glWidth / 2 + 56, 85.5), IM_COL32(255, 0, 0, 15));
            draw->AddRectFilled(ImVec2(glWidth / 2 - 52, 61.5), ImVec2(glWidth / 2 + 52, 85.5), IM_COL32(255, 0, 0, 15));
            draw->AddRectFilled(ImVec2(glWidth / 2 - 48, 61.5), ImVec2(glWidth / 2 + 48, 85.5), IM_COL32(255, 0, 0, 15));
            draw->AddRectFilled(ImVec2(glWidth / 2 - 44, 61.5), ImVec2(glWidth / 2 + 44, 85.5), IM_COL32(255, 0, 0, 15));
            draw->AddRectFilled(ImVec2(glWidth / 2 - 40, 61.5), ImVec2(glWidth / 2 + 40, 85.5), IM_COL32(255, 0, 0, 15));
            draw->AddRectFilled(ImVec2(glWidth / 2 - 36, 61.5), ImVec2(glWidth / 2 + 36, 85.5), IM_COL32(255, 0, 0, 15));
            draw->AddText(nullptr, ((float) density / 21.0f), ImVec2(glWidth / 2 - 32.f, 61), IM_COL32(255, 255, 255, 255), s.c_str());
        } else{
            std::string s;
            s += "CLEAR";
            draw->AddRectFilled(ImVec2(glWidth / 2 - 68, 61.5), ImVec2(glWidth / 2 + 68, 85.5), IM_COL32(87, 143, 255, 15));
            draw->AddRectFilled(ImVec2(glWidth / 2 - 60, 61.5), ImVec2(glWidth / 2 + 60, 85.5), IM_COL32(87, 143, 255, 15));
            draw->AddRectFilled(ImVec2(glWidth / 2 - 56, 61.5), ImVec2(glWidth / 2 + 56, 85.5), IM_COL32(87, 143, 255, 15));
            draw->AddRectFilled(ImVec2(glWidth / 2 - 52, 61.5), ImVec2(glWidth / 2 + 52, 85.5), IM_COL32(87, 143, 255, 15));
            draw->AddRectFilled(ImVec2(glWidth / 2 - 48, 61.5), ImVec2(glWidth / 2 + 48, 85.5), IM_COL32(87, 143, 255, 15));
            draw->AddRectFilled(ImVec2(glWidth / 2 - 44, 61.5), ImVec2(glWidth / 2 + 44, 85.5), IM_COL32(87, 143, 255, 15));
            draw->AddRectFilled(ImVec2(glWidth / 2 - 40, 61.5), ImVec2(glWidth / 2 + 40, 85.5), IM_COL32(87, 143, 255, 15));
            draw->AddRectFilled(ImVec2(glWidth / 2 - 36, 61.5), ImVec2(glWidth / 2 + 36, 85.5), IM_COL32(87, 143, 255, 15));
            draw->AddText(nullptr, ((float) density / 21.0f), ImVec2(glWidth / 2 - 32.f, 61), IM_COL32(255, 255, 255, 255), s.c_str());
            }
			}
			if (Config.AimBot.Mode == EAimMode::AimBot || Config.AimBot.Mode == EAimMode::AimBullet || Config.AimBot.Mode == EAimMode::Pbullet) {
            if (Config.AimBot.AimBy == EAimBy::FOV) {
                draw->AddCircle(ImVec2(glWidth / 2, glHeight / 2), FOVSizea, IM_COL32(255, 255, 255, 240), 0, 1.0f);;
            }					  
			
		if (Config.EnimiesAlert) {
draw->AddText(NULL, ((float) density / 10.0f), {((float)glWidth / 2) - (glWidth / 8), 100}, ImColor(isRed, isBlue, isGreen), "Warning! Enimes Alert");
draw->AddText(NULL, ((float) density / 10.0f), {((float)glWidth / 2) - (glWidth / 8), 100}, ImColor(isRed, isBlue, isGreen), "Warning! Enimes Alert");
draw->AddText(NULL, ((float) density / 10.0f), {((float)glWidth / 2) - (glWidth / 8), 100}, ImColor(isRed, isBlue, isGreen), "Warning! Enimes Alert");
draw->AddText(NULL, ((float) density / 10.0f), {((float)glWidth / 2) - (glWidth / 8), 100}, ImColor(isRed, isBlue, isGreen), "Warning! Enimes Alert");
       }
		}
		}
		
      
        
			
			

	
	
	  
		

 
std::string getClipboardText() {
    if (!g_App)
        return "";

    auto activity = g_App->activity;
    if (!activity)
        return "";

    auto vm = activity->vm;
    if (!vm)
        return "";

    auto object = activity->clazz;
    if (!object)
        return "";

    std::string result;

    JNIEnv *env;
    vm->AttachCurrentThread(&env, 0);
    {
        auto ContextClass = env->FindClass("android/content/Context");
        auto getSystemServiceMethod = env->GetMethodID(ContextClass, "getSystemService", "(Ljava/lang/String;)Ljava/lang/Object;");

        auto str = env->NewStringUTF("clipboard");
        auto clipboardManager = env->CallObjectMethod(object, getSystemServiceMethod, str);
        env->DeleteLocalRef(str);

        auto ClipboardManagerClass = env->FindClass("android/content/ClipboardManager");
        auto getText = env->GetMethodID(ClipboardManagerClass, "getText", "()Ljava/lang/CharSequence;");

        auto CharSequenceClass = env->FindClass("java/lang/CharSequence");
        auto toStringMethod = env->GetMethodID(CharSequenceClass, "toString", "()Ljava/lang/String;");

        auto text = env->CallObjectMethod(clipboardManager, getText);
        if (text) {
            str = (jstring) env->CallObjectMethod(text, toStringMethod);
            result = env->GetStringUTFChars(str, 0);
            env->DeleteLocalRef(str);
            env->DeleteLocalRef(text);
        }

        env->DeleteLocalRef(CharSequenceClass);
        env->DeleteLocalRef(ClipboardManagerClass);
        env->DeleteLocalRef(clipboardManager);
        env->DeleteLocalRef(ContextClass);
    }
    vm->DetachCurrentThread();

    return result;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

// ======================================================================== //
	//=============== 𝗠𝗔𝗗𝗘 𝗕𝗬 @SANSERO_MOD_1 =============== //
	//=============== 𝗠𝗔𝗗𝗘 𝗕𝗬 @SANSERO_MOD_1 =============== //
	//=============== 𝗠𝗔𝗗𝗘 𝗕𝗬 @SANSERO_MOD_1 =============== //
	//=============== 𝗠𝗔𝗗𝗘 𝗕𝗬 @SANSERO_MOD_1 =============== //
const char *GetAndroidID(JNIEnv *env, jobject context) {
    jclass contextClass = env->FindClass(/*android/content/Context*/ StrEnc("`L+&0^[S+-:J^$,r9q92(as", "\x01\x22\x4F\x54\x5F\x37\x3F\x7C\x48\x42\x54\x3E\x3B\x4A\x58\x5D\x7A\x1E\x57\x46\x4D\x19\x07", 23).c_str());
    jmethodID getContentResolverMethod = env->GetMethodID(contextClass, /*getContentResolver*/ StrEnc("E8X\\7r7ys_Q%JS+L+~", "\x22\x5D\x2C\x1F\x58\x1C\x43\x1C\x1D\x2B\x03\x40\x39\x3C\x47\x3A\x4E\x0C", 18).c_str(), /*()Landroid/content/ContentResolver;*/ StrEnc("8^QKmj< }5D:9q7f.BXkef]A*GYLNg}B!/L", "\x10\x77\x1D\x2A\x03\x0E\x4E\x4F\x14\x51\x6B\x59\x56\x1F\x43\x03\x40\x36\x77\x28\x0A\x08\x29\x24\x44\x33\x0B\x29\x3D\x08\x11\x34\x44\x5D\x77", 35).c_str());
    jclass settingSecureClass = env->FindClass(/*android/provider/Settings$Secure*/ StrEnc("T1yw^BCF^af&dB_@Raf}\\FS,zT~L(3Z\"", "\x35\x5F\x1D\x05\x31\x2B\x27\x69\x2E\x13\x09\x50\x0D\x26\x3A\x32\x7D\x32\x03\x09\x28\x2F\x3D\x4B\x09\x70\x2D\x29\x4B\x46\x28\x47", 32).c_str());
    jmethodID getStringMethod = env->GetStaticMethodID(settingSecureClass, /*getString*/ StrEnc("e<F*J5c0Y", "\x02\x59\x32\x79\x3E\x47\x0A\x5E\x3E", 9).c_str(), /*(Landroid/content/ContentResolver;Ljava/lang/String;)Ljava/lang/String;*/ StrEnc("$6*%R*!XO\"m18o,0S!*`uI$IW)l_/_knSdlRiO1T`2sH|Ouy__^}%Y)JsQ:-\"(2_^-$i{?H", "\x0C\x7A\x4B\x4B\x36\x58\x4E\x31\x2B\x0D\x0E\x5E\x56\x1B\x49\x5E\x27\x0E\x69\x0F\x1B\x3D\x41\x27\x23\x7B\x09\x2C\x40\x33\x1D\x0B\x21\x5F\x20\x38\x08\x39\x50\x7B\x0C\x53\x1D\x2F\x53\x1C\x01\x0B\x36\x31\x39\x46\x0C\x15\x43\x2B\x05\x30\x15\x41\x43\x46\x55\x70\x0D\x59\x56\x00\x15\x58\x73", 71).c_str());

    auto obj = env->CallObjectMethod(context, getContentResolverMethod);
    auto str = (jstring) env->CallStaticObjectMethod(settingSecureClass, getStringMethod, obj, env->NewStringUTF(/*android_id*/ StrEnc("ujHO)8OfOE", "\x14\x04\x2C\x3D\x46\x51\x2B\x39\x26\x21", 10).c_str()));
    return env->GetStringUTFChars(str, 0);
}

const char *GetDeviceModel(JNIEnv *env) {
    jclass buildClass = env->FindClass(/*android/os/Build*/ StrEnc("m5I{GKGWBP-VOxkA", "\x0C\x5B\x2D\x09\x28\x22\x23\x78\x2D\x23\x02\x14\x3A\x11\x07\x25", 16).c_str());
    jfieldID modelId = env->GetStaticFieldID(buildClass, /*MODEL*/ StrEnc("|}[q:", "\x31\x32\x1F\x34\x76", 5).c_str(), /*Ljava/lang/String;*/ StrEnc(".D:C:ETZ1O-Ib&^h.Y", "\x62\x2E\x5B\x35\x5B\x6A\x38\x3B\x5F\x28\x02\x1A\x16\x54\x37\x06\x49\x62", 18).c_str());

    auto str = (jstring) env->GetStaticObjectField(buildClass, modelId);
    return env->GetStringUTFChars(str, 0);
}

const char *GetDeviceBrand(JNIEnv *env) {
    jclass buildClass = env->FindClass(/*android/os/Build*/ StrEnc("0iW=2^>0zTRB!B90", "\x51\x07\x33\x4F\x5D\x37\x5A\x1F\x15\x27\x7D\x00\x54\x2B\x55\x54", 16).c_str());
    jfieldID modelId = env->GetStaticFieldID(buildClass, /*BRAND*/ StrEnc("@{[FP", "\x02\x29\x1A\x08\x14", 5).c_str(), /*Ljava/lang/String;*/ StrEnc(".D:C:ETZ1O-Ib&^h.Y", "\x62\x2E\x5B\x35\x5B\x6A\x38\x3B\x5F\x28\x02\x1A\x16\x54\x37\x06\x49\x62", 18).c_str());

    auto str = (jstring) env->GetStaticObjectField(buildClass, modelId);
    return env->GetStringUTFChars(str, 0);
}

const char *GetPackageName(JNIEnv *env, jobject context) {
    jclass contextClass = env->FindClass(/*android/content/Context*/ StrEnc("`L+&0^[S+-:J^$,r9q92(as", "\x01\x22\x4F\x54\x5F\x37\x3F\x7C\x48\x42\x54\x3E\x3B\x4A\x58\x5D\x7A\x1E\x57\x46\x4D\x19\x07", 23).c_str());
    jmethodID getPackageNameId = env->GetMethodID(contextClass, /*getPackageName*/ StrEnc("YN4DaP)!{wRGN}", "\x3E\x2B\x40\x14\x00\x33\x42\x40\x1C\x12\x1C\x26\x23\x18", 14).c_str(), /*()Ljava/lang/String;*/ StrEnc("VnpibEspM(b]<s#[9cQD", "\x7E\x47\x3C\x03\x03\x33\x12\x5F\x21\x49\x0C\x3A\x13\x20\x57\x29\x50\x0D\x36\x7F", 20).c_str());

    auto str = (jstring) env->CallObjectMethod(context, getPackageNameId);
    return env->GetStringUTFChars(str, 0);
}

const char *GetDeviceUniqueIdentifier(JNIEnv *env, const char *uuid) {
    jclass uuidClass = env->FindClass(/*java/util/UUID*/ StrEnc("B/TxJ=3BZ_]SFx", "\x28\x4E\x22\x19\x65\x48\x47\x2B\x36\x70\x08\x06\x0F\x3C", 14).c_str());

    auto len = strlen(uuid);

    jbyteArray myJByteArray = env->NewByteArray(len);
    env->SetByteArrayRegion(myJByteArray, 0, len, (jbyte *) uuid);

    jmethodID nameUUIDFromBytesMethod = env->GetStaticMethodID(uuidClass, /*nameUUIDFromBytes*/ StrEnc("P6LV|'0#A+zQmoat,", "\x3E\x57\x21\x33\x29\x72\x79\x67\x07\x59\x15\x3C\x2F\x16\x15\x11\x5F", 17).c_str(), /*([B)Ljava/util/UUID;*/ StrEnc("sW[\"Q[W3,7@H.vT0) xB", "\x5B\x0C\x19\x0B\x1D\x31\x36\x45\x4D\x18\x35\x3C\x47\x1A\x7B\x65\x7C\x69\x3C\x79", 20).c_str());
    jmethodID toStringMethod = env->GetMethodID(uuidClass, /*toString*/ StrEnc("2~5292eW", "\x46\x11\x66\x46\x4B\x5B\x0B\x30", 8).c_str(), /*()Ljava/lang/String;*/ StrEnc("P$BMc' #j?<:myTh_*h0", "\x78\x0D\x0E\x27\x02\x51\x41\x0C\x06\x5E\x52\x5D\x42\x2A\x20\x1A\x36\x44\x0F\x0B", 20).c_str());

    auto obj = env->CallStaticObjectMethod(uuidClass, nameUUIDFromBytesMethod, myJByteArray);
    auto str = (jstring) env->CallObjectMethod(obj, toStringMethod);
    return env->GetStringUTFChars(str, 0);
}

struct MemoryStruct {
    char *memory;
    size_t size;
};
// ============== //
 //====MAIN LOGIN====?======//
static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *) userp;

    mem->memory = (char *) realloc(mem->memory, mem->size + realsize + 1);
    if (mem->memory == NULL) {
        return 0;
    }

    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}

// ================ //
	//=============== 𝗠𝗔𝗗𝗘 𝗕𝗬 @SANSERO_MOD_1 =============== //
	//=============== 𝗠𝗔𝗗𝗘 𝗕𝗬 @SANSERO_MOD_1 =============== //
	//=============== 𝗠𝗔𝗗𝗘 𝗕𝗬 @SANSERO_MOD_1 =============== //
	//=============== 𝗠𝗔𝗗𝗘 𝗕𝗬 @SANSERO_MOD_1 =============== //
 //====MAIN LOGIN====?======//
std::string Login(const char *user_key) {
    if (!g_App)
        return "Internal Error";

    auto activity = g_App->activity;
    if (!activity)
        return "Internal Error";

    auto vm = activity->vm;
    if (!vm)
        return "Internal Error";

    auto object = activity->clazz;
    if (!object)
        return "Internal Error";

    JNIEnv *env;
    vm->AttachCurrentThread(&env, 0);

    std::string hwid = user_key;
    hwid += GetAndroidID(env, object);
    hwid += GetDeviceModel(env);
    hwid += GetDeviceBrand(env);

    std::string UUID = GetDeviceUniqueIdentifier(env, hwid.c_str());

    vm->DetachCurrentThread();

    std::string errMsg;

    struct MemoryStruct chunk{};
    chunk.memory = (char *) malloc(1);
    chunk.size = 0;

    CURL *curl;
    CURLcode res;
    curl = curl_easy_init();
//http://MODxmods.com
      if (curl) {
        std::string BHATIA = OBFUSCATE ("https://indkey.xyz/public/connect");
        curl_easy_setopt(curl, CURLOPT_URL ,BHATIA.c_str());

        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, /*https*/ StrEnc("!mLBO", "\x49\x19\x38\x32\x3C", 5).c_str());
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, /*Content-Type: application/x-www-form-urlencoded*/ StrEnc("@;Ls\\(KP4Qrop`b#d3094/r1cf<c<=H)AiiBG6i|Ta66s2[", "\x03\x54\x22\x07\x39\x46\x3F\x7D\x60\x28\x02\x0A\x4A\x40\x03\x53\x14\x5F\x59\x5A\x55\x5B\x1B\x5E\x0D\x49\x44\x4E\x4B\x4A\x3F\x04\x27\x06\x1B\x2F\x6A\x43\x1B\x10\x31\x0F\x55\x59\x17\x57\x3F", 47).c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    
        char data[4096];
            sprintf(data, /*game=PUBG&user_key=%s&serial=%s*/ StrEnc("qu2yXK,YkJyGD@ut0.u~Nb'5(:.:chK", "\x16\x14\x5F\x1C\x65\x1B\x79\x1B\x2C\x6C\x0C\x34\x21\x32\x2A\x1F\x55\x57\x48\x5B\x3D\x44\x54\x50\x5A\x53\x4F\x56\x5E\x4D\x38", 31).c_str(), user_key, UUID.c_str());
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);

            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *) &chunk);

            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

            res = curl_easy_perform(curl);
            if (res == CURLE_OK) {
                try {
                    json result = json::parse(chunk.memory);
                    if (result[StrEnc("(>_LBm", "\x5B\x4A\x3E\x38\x37\x1E", 6).c_str()] == true) {
                        std::string token = result[StrEnc("fAVA", "\x02\x20\x22\x20", 4).c_str()][StrEnc("{>3Lr", "\x0F\x51\x58\x29\x1C", 5).c_str()].get<std::string>();
                        time_t rng = result[StrEnc("fAVA", "\x02\x20\x22\x20", 4).c_str()][StrEnc("+n,", "\x59\x00\x4B", 3).c_str()].get<time_t>();
						//ModName = result["data"]["ModName"].get<std::string>();
   					  //  EXP = result["data"]["EXP"].get<std::string>();
                      //  BHATIA_SLOT = result["data"]["BHATIA_SLOT"].get<std::string>();
                       // ModName64 = result["data"]["ModName64"].get<std::string>();
                      //  MOD_STATUS64 = result["data"]["MOD_STATUS64"].get<std::string>();
                      //  FLOTING_TEST64 = result["data"]["FLOTING_TEST64"].get<std::string>();
                    
                    if (rng + 30 > time(0)) {
                            std::string auth = /*PUBG*/ StrEnc("Q*) ", "\x01\x7F\x6B\x67", 4).c_str();;
                            auth += "-";
                            auth += user_key;
                            auth += "-";
                            auth += UUID;
                            auth += "-";
                            std::string BHATIAENC = OBFUSCATE("Vm8Lk7Uj2JmsjCPVPVjrLa7zgfx3uz9E");
                            auth += BHATIAENC.c_str();
                            std::string outputAuth = Tools::CalcMD5(auth);

                        g_Token = token;
                        g_Auth = outputAuth;

                        bValid = g_Token == g_Auth;
                    }
                } else {
                    errMsg = result[/*reason*/ StrEnc("LW(3(c", "\x3E\x32\x49\x40\x47\x0D", 6).c_str()].get<std::string>();
                }
            } catch (json::exception &e) {
                errMsg = "{";
                errMsg += e.what();
                errMsg += "}\n{";
                errMsg += chunk.memory;
                errMsg += "}";
            }
        } else {
            errMsg = curl_easy_strerror(res);
        }
    }
    curl_easy_cleanup(curl);

    return bValid ? "OK" : errMsg;
}

#define IM_CLAMP(V, MN, MX)     ((V) < (MN) ? (MN) : (V) > (MX) ? (MX) : (V))
namespace Settings
{
    static int Tab = 1;
}

	EGLBoolean (*orig_eglSwapBuffers)(EGLDisplay dpy, EGLSurface surface);

    EGLBoolean _eglSwapBuffers(EGLDisplay dpy, EGLSurface surface) {
        eglQuerySurface(dpy, surface, EGL_WIDTH, &glWidth);
        eglQuerySurface(dpy, surface, EGL_HEIGHT, &glHeight);
        if (glWidth <= 0 || glHeight <= 0)
            return orig_eglSwapBuffers(dpy, surface);

        if (!g_App)
            return orig_eglSwapBuffers(dpy, surface);

        screenWidth = ANativeWindow_getWidth(g_App->window);
        screenHeight = ANativeWindow_getHeight(g_App->window);
        density = AConfiguration_getDensity(g_App->config);

            if (!initImGui) {
      ImGui::CreateContext();
  
                  ImGuiStyle& style = ImGui::GetStyle();
				 
			//ImportFonts();
		style.WindowRounding = 0.0f;
        style.FrameRounding = 10.0f;
		//style.ChildRounding = 5.0f;
        style.ScrollbarRounding = 0.0f;
		style.ScrollbarSize = 8.0f;
		style.GrabMinSize = 5.0f;
		style.FrameBorderSize = 0.0f;
		style.WindowBorderSize = 0.0f;
		
		style.ItemSpacing = ImVec2(6,4);
		style.ItemInnerSpacing = ImVec2(12,3);
		
        style.WindowTitleAlign = ImVec2(0.5, 0.5);
		style.ButtonTextAlign = ImVec2(0.5,0.5);
		
	//	style.WindowSize = ImVec2(300,180);
        style.FramePadding = ImVec2(3,3);
		style.WindowPadding = ImVec2(3,3);//12 12 for center
		
        style.Colors[ImGuiCol_Text]                  = ImColor(255, 255, 255,255);
        style.Colors[ImGuiCol_TextDisabled]          = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
        style.Colors[ImGuiCol_WindowBg]              = ImColor(0, 0, 0,185);
        //style.Colors[ImGuiCol_ChildBg]               = ImColor(32, 32, 32,255);
        style.Colors[ImGuiCol_PopupBg]               = ImColor(42, 74, 123,90);
       // style.Colors[ImGuiCol_Border]                = ImColor(255, 87, 34,255);   //ImVec4(0.518f, 0.557f, 0.592f, 1.00f);
       // style.Colors[ImGuiCol_BorderShadow]          = ImColor(255, 87, 34,255);;

        style.Colors[ImGuiCol_FrameBg]               = ImColor(42, 74, 123,90);
        style.Colors[ImGuiCol_FrameBgActive]         = ImColor(42, 74, 123,90);
        style.Colors[ImGuiCol_FrameBgHovered]        = ImColor(42, 74, 123,90);
		
        style.Colors[ImGuiCol_TitleBg]               = ImColor(42, 74, 123,255);
        style.Colors[ImGuiCol_TitleBgActive]         = ImColor(42, 74, 123,255);
        style.Colors[ImGuiCol_TitleBgCollapsed]      = ImColor(42, 74, 123,100);
		
        style.Colors[ImGuiCol_MenuBarBg]             = ImColor(24, 24, 24,255);
        style.Colors[ImGuiCol_ScrollbarBg]           = ImColor(24, 24, 24,255);
        style.Colors[ImGuiCol_ScrollbarGrab]         = ImColor(32, 32, 32,255);
        style.Colors[ImGuiCol_ScrollbarGrabHovered]  = ImColor(32, 32, 32,255);
        style.Colors[ImGuiCol_ScrollbarGrabActive]   = ImColor(32, 32, 32,255);
        style.Colors[ImGuiCol_CheckMark]             = ImColor(65, 132, 223, 255);
        style.Colors[ImGuiCol_SliderGrab]            = ImColor(32, 32, 32,255);
        style.Colors[ImGuiCol_SliderGrabActive]      = ImColor(32, 32, 32,255);

        style.Colors[ImGuiCol_Separator]             = ImVec4(0.00f, 0.89f, 1.00f, 0.00f);
        style.Colors[ImGuiCol_SeparatorActive]       = ImVec4(0.00f, 0.89f, 1.00f, 0.00f);
        style.Colors[ImGuiCol_SeparatorHovered]      = ImVec4(0.00f, 0.89f, 1.00f, 0.00f);

        style.Colors[ImGuiCol_Button]                = ImColor(42, 74, 123,255);
        style.Colors[ImGuiCol_ButtonActive]          = ImColor(48, 107, 177,255);
        style.Colors[ImGuiCol_ButtonHovered]         = ImColor(42, 74, 123,255);

        style.Colors[ImGuiCol_Header]                = ImColor(32, 32, 32,255);
        style.Colors[ImGuiCol_HeaderActive]          = ImColor(255, 87, 34,255);
        style.Colors[ImGuiCol_HeaderHovered]         = ImColor(255, 87, 34,255);

        style.Colors[ImGuiCol_ResizeGrip]            = ImVec4(1.00f, 1.00f, 1.00f, 0.85f);
        style.Colors[ImGuiCol_ResizeGripHovered]     = ImVec4(1.00f, 1.00f, 1.00f, 0.60f);
        style.Colors[ImGuiCol_ResizeGripActive]      = ImVec4(1.00f, 1.00f, 1.00f, 0.90f);
        style.Colors[ImGuiCol_PlotLines]             = ImColor(255, 87, 34,255);
        style.Colors[ImGuiCol_PlotLinesHovered]      = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
        style.Colors[ImGuiCol_PlotHistogram]         = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
        style.Colors[ImGuiCol_PlotHistogramHovered]  = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
        style.Colors[ImGuiCol_TextSelectedBg]        = ImVec4(0.00f, 0.00f, 1.00f, 0.35f);

                      style.ScaleAllSizes(std::max(2.5f, density / 200.0f));
					   style.ScrollbarSize /= 1;
        ImGui_ImplAndroid_Init();
        ImGui_ImplOpenGL3_Init("#version 300 es");

            ImGuiIO &io = ImGui::GetIO();

            io.ConfigWindowsMoveFromTitleBarOnly = true;
            io.IniFilename = NULL;


            
            static const ImWchar icons_ranges[] = { 0xf000, 0xf3ff, 0 };
        ImFontConfig icons_config;
		
		ImFontConfig CustomFont;
        CustomFont.FontDataOwnedByAtlas = false;

		
               ImFontConfig cfg;
        cfg.SizePixels = ((float) density / 18.0f);
        io.Fonts->AddFontFromMemoryTTF((void *)PIRO_data, PIRO_size, 23.0f, NULL, io.Fonts->GetGlyphRangesChineseFull());    
        io.Fonts->AddFontFromMemoryCompressedTTF(font_awesome_data, font_awesome_size, 23.0f, &icons_config, icons_ranges);        
		
        memset(&Config, 0, sizeof(sConfig));
		
// ===============================ESPCOLOR ================================== // 

           Config.ColorsESP.Line = CREATE_COLOR(0, 0, 139, 255);
           Config.ColorsESP.Box = CREATE_COLOR(0, 0, 139, 255);
           Config.ColorsESP.Name = CREATE_COLOR(255, 0, 0, 255);
           Config.ColorsESP.Vehicle = CREATE_COLOR(255, 0, 0, 255);
           Config.ColorsESP.Skeletonbot = CREATE_COLOR(255, 255, 255, 255);
           Config.ColorsESP.BotNv = CREATE_COLOR(255, 255, 0, 255);
           Config.ColorsESP.BotNn = CREATE_COLOR(255, 0, 0, 255);
           Config.ColorsESP.Skeletonnon = CREATE_COLOR(255, 0, 0, 255);
           Config.ColorsESP.PotNv = CREATE_COLOR(0, 255, 0, 255);
           Config.ColorsESP.PotNn = CREATE_COLOR(255, 0, 0, 255);
           Config.ColorsESP.nonbot = CREATE_COLOR(150, 150, 150, 255);
           Config.ColorsESP.SkeletonVisible = CREATE_COLOR(0, 255, 0, 255);
           Config.ColorsESP.Skeleton = CREATE_COLOR(255, 0, 0, 255);
           Config.SilentAim.Meter = 110.0f;
            initImGui = true;
    }

    ImGuiIO &io = ImGui::GetIO();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplAndroid_NewFrame(glWidth, glHeight);
        ImGui::NewFrame();

        DrawESP(ImGui::GetBackgroundDrawList());

      ImGui::SetNextWindowSize(ImVec2((float) glWidth * 0.45f, (float) glHeight * 0.70f),ImGuiCond_Once); // 45% width 70% height
        if (show_another_info) {
    if (ImGui::Begin(OBFUSCATE("DENZIVVV VIP LOGIN"), &show_another_info, ImGuiWindowFlags_NoBringToFrontOnFocus)) {
        static bool isLogin = true;
	 
            static std::string err;
            if (!isLogin) {
            ImGui::Text("Please Do Key Verification Vip");
            ImGui::PushItemWidth(-1);
            static char s[64];
            ImGui::InputText("##key", s, sizeof s);
            ImGui::PopItemWidth();

            if (ImGui::Button(" Paste Key ", ImVec2(ImGui::GetContentRegionAvailWidth(), 0))) {
                auto key = getClipboardText();
                strncpy(s, key.c_str(), sizeof s);
            }

            static std::string err;
            if (ImGui::Button(" Login ", ImVec2(ImGui::GetContentRegionAvailWidth(), 0))) {
                err = Login(s);
                if (err == "OK") {
                    isLogin = bValid && g_Auth == g_Token;
                }
            }

            if (!err.empty() && err != "OK") {
                ImGui::Text("Error: %s", err.c_str());
            }


            } else{

                {

	
					
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~| 𝐌𝐚𝐝𝐞𝐁𝐲𝐃𝐞𝐦𝐨𝐧 |~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\\
                
				            if (ImGui::BeginTabBar("Tab", ImGuiTabBarFlags_FittingPolicyScroll)) {
		 			        if (ImGui::BeginTabItem("Basic")) {
							ImGui::TextColored(ImColor(255,255,255,255), ("I don't have a screenshot to make"));
							ImGui::TableNextColumn();
							ImGui::TextColored(ImColor(255,255,255,255), ("add your future you want"));
							ImGui::TableNextColumn();
								
								
    						ImGui::EndTabItem();        
				        	 }
							 
							 
							 
							 
			   				 if (ImGui::BeginTabItem("X-Ray Vision")) {
				ImGui::TableNextColumn();    
				ImGui::TextColored(ImColor(202,206,51,255), ("EXPIRY:"));
				ImGui::SameLine();
				ImGui::TextColored(ImColor(0,255,0,255), ("2200-07-02 19:08:13"));
				ImGui::SameLine();
				ImGui::TextColored(ImColor(255,255,255,255), (" (9.09 FPS)"));
				ImGui::TableNextColumn();   
				ImGui::Checkbox("Island Antiban", &Config.PlayerESP.NoBot);	
				ImGui::SameLine();
				ImGui::Button("Delete Reports");
				ImGui::TableNextColumn();     
				ImGui::TableNextColumn();      
                             if (ImGui::BeginTable("split", 3));
							 {
				ImGui::TableNextColumn();     
				ImGui::TextColored(ImVec4(255,255,255,255), "Enemy Count Ui");
                static const char *koktanyasaya[] = {" ui 1", "ui 2"," ui 3"," ui 4"};
                ImGui::Combo("##Koktanyasaya OP", (int *) &Config.PlayerESP.By, koktanyasaya, 4, -1);
				ImGui::TableNextColumn();
				ImGui::TextColored(ImVec4(255,255,255,255), "Player Line");
                static const char *opxjaat[] = {"None", "ui 2"," ui 3"," ui 4"};
                ImGui::Combo("##opxjaat OP", (int *) &Config.PlayerESP.By, opxjaat, 4, -1);
				ImGui::TableNextColumn();
			    ImGui::TextColored(ImVec4(255,255,255,255), "Box Style");
                static const char *targ[] = {" None"," 2D"," 3D"};
                ImGui::Combo("##Target By", (int *) &Config.FAK.By, targ, 3, -1);
			    ImGui::TableNextColumn();
	            ImGui::Checkbox("Enemy Skeleton", &Config.PlayerESP.Skeleton);
              	ImGui::TableNextColumn();
				ImGui::Checkbox("Enemy Health", &Config.PlayerESP.Health);
                ImGui::TableNextColumn();
				ImGui::Checkbox("Enemy Health PC", &Config.PlayerESP.Health);
                ImGui::TableNextColumn();
				ImGui::Checkbox("Enemy Name", &Config.PlayerESP.Name);
                ImGui::TableNextColumn();
				ImGui::Checkbox("Enemy Distance", &Config.PlayerESP.Distance);
                ImGui::TableNextColumn();
				ImGui::Checkbox("Enemy TeamID", &Config.PlayerESP.TeamID);
                ImGui::TableNextColumn();
				ImGui::Checkbox("Enemy weapon", &Config.PlayerESP.Name);
                ImGui::TableNextColumn();
				ImGui::Checkbox("Enemy Status", &Config.PlayerESP.TeamID);
                ImGui::TableNextColumn();
				ImGui::Checkbox("Enemy SeeYou", &Config.PlayerESP.NoBot);
				ImGui::TableNextColumn();
				ImGui::Checkbox("Pleane Location", &Config.PlayerESP.NoBot);
				ImGui::TableNextColumn();
				ImGui::Checkbox("AirDrop Box", &Config.PlayerESP.NoBot);
				ImGui::TableNextColumn();
				ImGui::Checkbox("Dead Box", &Config.PlayerESP.LootBox);
				ImGui::TableNextColumn();
				ImGui::Checkbox("Vehicle", &Config.PlayerESP.Vehicle);
				ImGui::TableNextColumn();
				ImGui::Checkbox("Grenade Alert", &Config.PlayerESP.Name);
                ImGui::TableNextColumn();
				ImGui::Checkbox("Radar map", &Config.PlayerESP.Vehicle);
				ImGui::TableNextColumn();
 				ImGui::Checkbox("360 Alert", &Config.EnimiesAlert);				 
				ImGui::TableNextColumn();
				ImGui::Checkbox("Screen Alert", &Config.PlayerESP.Vehicle);				 
				ImGui::TableNextColumn();
 				ImGui::Checkbox("Game info", &Config.EnimiesAlert);				 
				ImGui::TableNextColumn();
						 	}
                ImGui::EndTable();	
			    ImGui::EndTabItem();        
				        	 }
							 
				if (ImGui::BeginTabItem("X-Ray Items")) {
				for (auto &i : items_data) {
                           // IMGUI_DEMO_MARKER("");
		    if (ImGui::CollapsingHeader(i["Category"].get<std::string>().c_str())) {
                                ImGui::Spacing();
                                for (auto &item : i["Items"]) {
                                    ImGui::Checkbox(item["itemName"].get<std::string>().c_str(),
                                                    (bool *) &Items[item["itemId"].get<int>()]);
                             
									 }
       
                            }
                        }
				   
				ImGui::EndTabItem();        
				        	 }
							 
							 
				if (ImGui::BeginTabItem("AimTouch")) {
				ImGui::TableNextColumn();
				ImGui::Checkbox(" AimTouch 2.0", &Config.AimBot.Enable);	
				ImGui::SameLine();
			    ImGui::Checkbox("Small Crosshai", &Config.HighRisk.Cross);	
				ImGui::SameLine();
				ImGui::Checkbox("No Recoil", &Config.HighRisk.Recoil);	
				ImGui::Separator();
				ImGui::TextColored(ImColor(255,255,255,255), ("Recoil Compensation"));
				ImGui::TableNextColumn();
				ImGui::Checkbox("", &Config.AimBot.RecoilComparison);
				ImGui::SameLine();
				ImGui::SliderFloat("", &Config.AimBot.Recc, 0.0f, 1.080f);
				ImGui::SliderFloat("Fov Width", &FOVSizea, 0,400, "%.3f Size", 0);
				ImGui::SliderFloat("Aim Speed", &Config.AimBot.Recc, 0.0f, 1.080f);
				ImGui::TextColored(ImColor(255,255,255,255), ("The Target One 1.100 Ues between"));
				ImGui::TableNextColumn();
			    ImGui::TextColored(ImColor(255,255,255,255), ("Trigger"));
				static const char *triggers[] = {"None", "Shooting", "Scoping", "Both (Shooting & Scoping)", "Any (Shooting / Scoping)"};
			    ImGui::Combo("##Trigger", (int *)&Config.AimBot.Trigger, triggers, 5, -1);
				ImGui::Separator();
				ImGui::Checkbox("Visibilty-Check", &Config.AimBot.VisCheck);
				ImGui::SameLine();
			    ImGui::Checkbox("Ignore-Knock", &Config.AimBot.IgnoreKnocked);
			    ImGui::SameLine();
			    ImGui::Checkbox("Ignore-Bot", &Config.AimBot.IgnoreBot);
				ImGui::Separator();
				ImGui::EndTabItem();        
				        	 }
							 
				if (ImGui::BeginTabItem("Settings")) {
					ImGui::Text("Mod Status - ");
              ImGui::SameLine();
              ImGui::TextColored(ImColor(0,255,0,255), ("SAFE"));
       	    //  ImGui::RadioButton("FOV", &Config.Fov);		 
					
					
					
				ImGui::EndTabItem();        
				        	 }
							 
			 }
		   }
        }
	}
}
	
		
		
    ImGui::End();
    ImGui::Render();
	
	
	

ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

return orig_eglSwapBuffers(dpy, surface);
}

int32_t (*orig_onInputEvent)(struct android_app *app, AInputEvent *inputEvent);

int32_t onInputEvent(struct android_app *app, AInputEvent *inputEvent) {
if (initImGui) {
ImGui_ImplAndroid_HandleInputEvent(inputEvent, {(float) screenWidth / (float) glWidth, (float) screenHeight / (float) glHeight});
}
return orig_onInputEvent(app, inputEvent);
}
[[noreturn]] void *bypass_thread(void *) {
while (true) {
auto t1 = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();



auto localPlayer = g_LocalPlayer;
auto localController = g_LocalController;
if (localPlayer && localController) {



if (Config.HighRisk.Recoil || Config.HighRisk.HitEffect || Config.HighRisk.Cross) {
auto WeaponManagerComponent = g_LocalPlayer->WeaponManagerComponent;
if (WeaponManagerComponent) {
auto CurrentWeaponReplicated = (ASTExtraShootWeapon *) WeaponManagerComponent->CurrentWeaponReplicated;
if (CurrentWeaponReplicated) {
auto ShootWeaponEntityComp = CurrentWeaponReplicated->ShootWeaponEntityComp;
auto ShootWeaponEffectComp = CurrentWeaponReplicated->ShootWeaponEffectComp;
if (ShootWeaponEntityComp && ShootWeaponEffectComp) {
if (Config.HighRisk.Recoil) {
ShootWeaponEntityComp->AccessoriesVRecoilFactor = 0.3f;
ShootWeaponEntityComp->AccessoriesHRecoilFactor = 0.3f;
ShootWeaponEntityComp->AccessoriesRecoveryFactor = 0.3f;

ShootWeaponEntityComp->RecoilKickADS = 0.3f;
}
if (Config.HighRisk.Cross) {
ShootWeaponEntityComp->GameDeviationFactor = 0.0f;
}
if (Config.HighRisk.HitEffect) {
ShootWeaponEntityComp->ExtraHitPerformScale = 30.0f;
}

}
}
}
}


}








auto td = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() - t1;
std::this_thread::sleep_for(std::chrono::milliseconds(std::max(std::min(0LL, SLEEP_TIME - td), SLEEP_TIME)));
}
return 0;
}






#define SLEEP_TIME 1000LL / 60LL
[[noreturn]] void *maps_thread(void *) {
while (true) {
auto t1 = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();



std::vector<sRegion> tmp;
char line[512];
FILE *f = fopen("/proc/self/maps", "r");;
if (f) {
while (fgets(line, sizeof line, f)) {
uintptr_t start, end;
char tmpProt[16];
if (sscanf(line, "%" PRIXPTR "-%" PRIXPTR " %16s %*s %*s %*s %*s", &start, &end, tmpProt) > 0) {
if (tmpProt[0] != 'r') {
tmp.push_back({start, end});
}
}
}
fclose(f);
}
trapRegions = tmp;
auto objs = UObject::GetGlobalObjects();
for (int i = 0; i < objs.Num(); i++) {
auto Object = objs.GetByIndex(i);
if (isObjectInvalid(Object))
continue;
if (WideView) {
if (Object->IsA(ULocalPlayer::StaticClass())) {
auto playerChar = (ULocalPlayer *) Object;
playerChar->AspectRatioAxisConstraint = EAspectRatioAxisConstraint::AspectRatio_MaintainYFOV;
}}else
if (Object->IsA(ULocalPlayer::StaticClass())) {
auto playerChar = (ULocalPlayer *) Object;
playerChar->AspectRatioAxisConstraint = EAspectRatioAxisConstraint::AspectRatio_MaintainXFOV;
}

if (Config.HighRisk.NoSmoke) {

auto objs = UObject::GetGlobalObjects();
for (int i = 0; i < objs.Num(); i++) {
auto Object = objs.GetByIndex(i);
if (isObjectInvalid(Object))
continue;

if (Object->IsA(UParticleEmitter::StaticClass())) {
auto playerChar = (UParticleEmitter *) Object;      
playerChar->EmitterRenderMode = EEmitterRenderMode::ERM_None;
playerChar->DetailMode = EDetailMode::DM_MAX;

}     
}
}




if (Config.HighRisk.Unlock) {
if (Object->IsA(USTExtraGameInstance::StaticClass())) {
auto playerChar = (USTExtraGameInstance *) Object;      
playerChar->UserDetailSetting.PUBGDeviceFPSDef = 90.0f;   
playerChar->UserDetailSetting.PUBGDeviceFPSLow = 90.0f;
playerChar->UserDetailSetting.PUBGDeviceFPSMid = 90.0f;
playerChar->UserDetailSetting.PUBGDeviceFPSHigh = 90.0f;
playerChar->UserDetailSetting.PUBGDeviceFPSHDR = 90.0f;
playerChar->UserDetailSetting.PUBGDeviceFPSUltralHigh = 90.0f;
}}
}

auto td = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() - t1;
std::this_thread::sleep_for(std::chrono::milliseconds(std::max(std::min(0LL, SLEEP_TIME - td),SLEEP_TIME)));
}
}

/*void * op_thread(void *) {
do {
sleep(1);
} while (!isLibraryLoaded(targetLibName));

//HOOK_LIB("libanort.so", "0x1B99A4", hsub_E2172, osub_E2172);
//HOOK_LIB("libanogs.so", "0x30ECC", hsub_E2172, osub_E2172);

return NULL;
}*/

void *main_thread(void *) {
system("adb shell am compat disable BLOCK_UNTRUSTED_TOUCHES com.tencent.ig");
UE4 = Tools::GetBaseAddress("libUE4.so");
while (!UE4) {
UE4 = Tools::GetBaseAddress("libUE4.so");
sleep(1);
}
Anogs = Tools::GetBaseAddress("libanogs.so");
while (!Anogs) {
Anogs = Tools::GetBaseAddress("libanogs.so");
sleep(1);
}
g_Gcloud = Tools::GetBaseAddress("libgcloud.so");
while (!g_Gcloud) {
g_Gcloud = Tools::GetBaseAddress("libgcloud.so");
sleep(1);
}
TDataMaster = Tools::GetBaseAddress("libTDataMaster.so");
while (!TDataMaster) {
TDataMaster = Tools::GetBaseAddress("libTDataMaster.so");
sleep(1);
}
while (!g_App) {
g_App = *(android_app **) (UE4 + GNativeAndroidApp_Offset);
sleep(1);
}

while (!g_App->onInputEvent)
sleep(1);

orig_onInputEvent = decltype(orig_onInputEvent)(g_App->onInputEvent);
g_App->onInputEvent = onInputEvent;

FName::GNames = GetGNames();
while (!FName::GNames) {
FName::GNames = GetGNames();
sleep(1);
}
UObject::GUObjectArray = (FUObjectArray *) (UE4 + GUObject_Offset);

A64HookFunction((void *) (Tools::GetBaseAddress(OBFUSCATE("libUE4.so")) + 0xADD4A40), (void *) _eglSwapBuffers, (void **) &orig_eglSwapBuffers);

pthread_t t;
pthread_create(&t, 0, maps_thread, 0);

items_data = json::parse(JSON_ITEMS);

return 0;
}
__attribute__((constructor)) void _init() {
pthread_t t;
pthread_create(&t, 0, main_thread, 0);
pthread_create(&t, 0, bypass_thread, 0);
//pthread_create(&t, 0, bypass_thread, 0);
}
__attribute__((constructor))
void lib_main() {
pthread_t ptid;
//pthread_create(&ptid, NULL, op_thread, NULL);
}



