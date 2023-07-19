This is just a sandbox plugin for me to learn how to do things the [CommonLibSSE NG](https://github.com/CharmedBaryon/CommonLibSSE-NG) way. It's based on [this excellent template by mrowrpurr](https://github.com/SkyrimScripting/SKSE_Template_MultipleSourceAndHeaderFiles) and can be built in the same way: 
1. install [vcpkg](https://github.com/microsoft/vcpkg)
2. add vcpkg path to environment variables as VCPKG_ROOT and run /vcpkg/bootstrap-vcpkg.bat
3. install Visual Studio 2022 with "C++ Desktop Development" module
4. install VSCode
5. open this repository's root folder in VSCode and it will automatically configure itself.
6. if you add/remove any source files, open CMakeLists.txt in VSCode and then save it to refresh the build configuration.

I don't know if this plugin will run on non-VR versions due to the HIGGS and OpenVR dependencies.

---
- [Call Native Papyrus functions](#call-native-papyrus-functions)
- [Interface with HIGGSVR](#interface-with-higgsvr)
- [Animation Event Listener](#Animation-Event-Listener)
- (Todo) Read VR controller position and button inputs
- Launch projectile from arbitrary location
- (Todo) Hook into projectile update function
- (Todo) Register custom Papyrus functions to set SKSE variables from an MCM

 ## Call Native Papyrus Functions
 I tried to do this the "right" way with REL::Relocation<func_t>, but I couldn't get it to work so I fell back to the SKSE method. Including Relocation.[h|cpp] from SKSE works fine, with one edit:
 ```
 s_baseAddr = reinterpret_cast<uintptr_t>(GetModuleHandle((char*)NULL));
```
This example will add a cabbage to the Player's inventory every time a save is loaded.

See: `nativePapyrus.cpp, nativePapyrus.h, Relocation.cpp, Relocation.h, VRExample::GameLoad()`

## Interface with HIGGSVR
The HIGGS header just needs some namespace qualifiers. The interface is retrieved in plugin.cpp and the onWeaponGrab() callback is registered in VRExample.cpp.

This example will log the left hand's finger curl values when the player grabs a weapon with two hands.

## Event Listeners
custemEventSink.h provides a template for an event listener that can have callbacks added or removed at runtime. The best explanation is an example:

```void onButtonPress(RE::InputEvent *const *eventPtr){
    // do stuff
}

auto inputSink = EventSink<RE::InputEvent *>::GetSingleton();
inputSink->AddCallback(onButtonPress);
RE::BSInputDeviceManager::GetSingleton()->AddEventSink(inputSink);```

BSInputDeviceManager is an example of a BSTEventSource. There's over 100 BSTEventSources in CommonLibSSE and they should all work with this template.

This example implements isGameStopped() from [Disable Input VR](https://www.nexusmods.com/skyrimspecialedition/mods/27800) to check if the game is paused due to a menu being open.
---
## Original project template description and instructions at https://github.com/SkyrimScripting/SKSE_Template_MultipleSourceAndHeaderFiles
