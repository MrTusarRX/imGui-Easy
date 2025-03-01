### ImGui Menu Image
![LGLGUI](https://github.com/MrTusarRX/imGui-Easy/blob/main/IMG_20240507_114319_278.jpg)
***
# ImGui Android Mod Menu

Welcome to the **ImGui Android Mod Menu** project! This is an educational project that demonstrates how to create an in-game overlay menu using **ImGui** for Android applications. It does **not promote any illegal activity** and is intended for **debugging, UI enhancements, and learning purposes**.

## 🔹 About

This project integrates **ImGui (Dear ImGui)** with Android applications using JNI and OpenGL. The menu provides a simple interface with buttons, checkboxes, and sliders that can be used to modify in-game UI elements or experiment with game logic.

### 📌 **Features**
✅ **Customizable UI overlay** with ImGui  
✅ **Toggle buttons, sliders, and text fields**  
✅ **Designed for debugging & testing**  
✅ **Lightweight & OpenGL-powered**  
✅ **Safe & educational—no illegal modifications**  

## 🚀 Installation & Usage

### 1️⃣ **Requirements**
- Android device or emulator  
- A game or application with OpenGL support  
- Android NDK & CMake  
- Root access (optional for deeper memory access)  

### 2️⃣ **How to Build**
1. Clone this repository:
   ```bash
   git clone https://github.com/MrTusarRX/imGui-Easy.git
  bash```
**




-----------------------------------------------------------------------------------------------------------
   1. Set up your Android project in Android Studio.
   2. Include ImGui and OpenGL dependencies.
   3. Compile and run the app on an Android device or emulator.

3️⃣ How to Use

    Open the app, and the ImGui menu overlay will appear.
    Toggle features using checkboxes or sliders.
    Customize the UI elements as needed for debugging.

🔧 Code Example

Here’s a basic example of an ImGui menu in C++ for Android:
```#include "imgui.h"
#include "imgui_impl_android.h"
#include "imgui_impl_opengl3.h"
#include <jni.h>

bool feature1 = false;
float customValue = 1.0f;

void RenderMenu() {
    ImGui::Begin("ImGui Mod Menu");

    ImGui::Text("Game Debug Menu");
    ImGui::Separator();

    if (ImGui::Checkbox("Enable Debug Mode", &feature1)) {
        // Feature activation logic here
    }

    ImGui::SliderFloat("Adjust Value", &customValue, 0.1f, 10.0f);

    ImGui::End();
}

extern "C" void Java_com_example_modmenu_MainActivity_DrawMenu(JNIEnv *env, jobject thiz) {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplAndroid_NewFrame();
    ImGui::NewFrame();

    RenderMenu(); 

    ImGui::Render();
}```


📜 Disclaimer

🔹 This project is for educational and debugging purposes only.
🔹 We do not promote cheating, piracy, or illegal activities.
🔹 Users are responsible for how they use this code.
📬 Contact

Developer: MrTusarRX
GitHub: MrTusarRX







