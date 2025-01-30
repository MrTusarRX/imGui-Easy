#define DRAWMENU



void DrawMenu(){

    const ImVec2 window_size = ImVec2(510, 530);
    const char* window_title = "Modded by MrxH - [x32]";
    const char* name = "Cover Fire";
    const char* version = "1.24.17";
    
    // Begin the main menu window
   ImGui::SetNextWindowSize(window_size);
   if (ImGui::Begin(window_title, nullptr))
    {
        ImGui::TextColored(ImVec4(1, 1, 1, 1), "Name : %s",name);
        ImGui::TextColored(ImVec4(1, 1, 1, 1), "Version : %s",version);
        ImGui::Text("FPS : %.3f ms (%.1f)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    
        
        
        ImVec2 cursor_pos = ImGui::GetCursorScreenPos();
        ImGui::GetWindowDrawList()->AddLine(cursor_pos,
        ImVec2(cursor_pos.x + ImGui::GetContentRegionAvail().x, cursor_pos.y),
        ImGui::GetColorU32(ImGuiCol_Text));
        ImGui::Spacing();
   
        if (ImGui::CollapsingHeader("ESP VISUALS")) {
        ImGui::TextColored(ImVec4(1, 1, 1, 1), "ESP DRAW");
        ImGui::Checkbox("ENABLE ESP",&Esp);
        ImGui::Checkbox("ENABLE Test Example",&Test);
        ImGui::Checkbox("ESP LINE",&ESPLine);
        ImGui::SameLine();
        ImGui::ColorEdit3("ESP LINE COLOUR", (float*)&ESPLineColor,ImGuiColorEditFlags_NoLabel|ImGuiColorEditFlags_NoInputs);
        ImGui::Checkbox("ESP BOX",&ESPBox);
        ImGui::SameLine();
        ImGui::ColorEdit3("ESP BOX COLOUR", (float*)&ESPBoxColor,ImGuiColorEditFlags_NoLabel|ImGuiColorEditFlags_NoInputs);
        ImGui::Checkbox("ESP HEALTH",&Esphealth);
        ImGui::Checkbox("ESP HEALTH (CIRCLE)",&EspPoint);
        ImGui::Checkbox("ESP OBJECT",&EspObject);
        ImGui::Text("ESP LINE SIZE");
        ImGui::SliderFloat("##ESPLINE",&ESPLineSize,0.f,10.10f);
        ImGui::Text("ESP BOX SIZE");
        ImGui::SliderFloat("##ESPBOX",&ESPBoxSize,0.f,10.10f);
        ImGui::Separator();
        }
        
        if (ImGui::CollapsingHeader("MENU")) {
        if (ImGui::Button("Dark"))
           ImGui::StyleColorsDark();
           ImGui::SameLine();
        if (ImGui::Button("Light"))
           ImGui::StyleColorsLight();
           ImGui::SameLine();
        if (ImGui::Button("Classic"))
            ImGui::StyleColorsClassic();  
         ImGui::Separator();
        }
     
     ImGui::End();
    }
}



    
   
void DrawESP() {
    /*
 std::string Name = "Kentik v1.0 IS RUNNING";

 ESP::DrawText(20.0f, {((float) glWidth / 2), glHeight / 1.5 }, ImVec4(255, 255, 255, 30),Name.c_str());
 */
if(Esp){
    
if (espManager->enemies->empty()) {
   return;
  }
  
for (int i = 0; i < espManager->enemies->size(); i++) { 
   void *Player = (*espManager->enemies)[i]->object;
     if(get_camera != nullptr) {
        if (Player != nullptr) {
          if (PlayerAlive(Player)) {

Vector3 PlayerPos = GetPlayerPosition(Player);
void *Camera = get_camera();
Vector3 PlayerPosNew = WorldToScreenPoint(Camera, PlayerPos);
if (PlayerPosNew.z < 1.f) continue;

Vector3 Origin = PlayerPos;
Origin.y += 0.7f;
float posnum = 1.0; //Height slider
float posnum2 = 1.0; //Width slider
float posnum3 = 5.0;
Origin.y += posnum;


Vector3 BoxPosNew = WorldToScreenPoint(Camera, Origin);
float Hight =
abs(BoxPosNew.y - PlayerPosNew.y) * (posnum2 / posnum), Width = Hight * 0.6f;
Rect rect = Rect(BoxPosNew.x - Width / 2.f,
glHeight - BoxPosNew.y,
Width, Hight
);


 if(ESPLine){
      ESP::DrawLine(ImVec2(glWidth/2.0, glHeight/15.0f), ImVec2(rect.x + rect.width/2, rect.y + rect.height/20), ESPLineColor, ESPLineSize);
       }


 if(ESPBox){
      ESP::DrawBox(rect, ESPBoxColor, ESPBoxSize);
       }
       
 if(Esphealth){
     int CurrentHP = GetHealth(Player);
     std::string health;
     health = float_to_string_health(CurrentHP);
     ESP::DrawText(17.0f, ImVec2(BoxPosNew.x,glHeight - BoxPosNew.y), ImVec4(255, 255, 255, 30), health.c_str());

       }
       
 if(EspPoint){
     int CurrentHP = GetHealth(Player);
     int MaxHP = GetHealthMax(Player);
     ESP::DrawCircleHealth(ImVec2(BoxPosNew.x,glHeight - BoxPosNew.y), CurrentHP, MaxHP, 15.0f);

       } 
      
 if(EspObject){  
     ESP::DrawCircleFilled(ImVec2(glWidth / 2.0, glHeight / 15.0f), 31.0f,ImVec4(255, 255, 255, 255));
     std::string Allplayers;
     Allplayers +=  "";
     Allplayers += std::to_string((int32_t) espManager->enemies->size());
     ESP::DrawText(30.0f, ImVec2(glWidth / 2.02, glHeight / 20.07f), ImVec4(0, 0, 0, 255), Allplayers.c_str());

       }      
      }
     }
    }
   }
  }
}
