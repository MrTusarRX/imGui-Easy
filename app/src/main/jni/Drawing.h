
#ifndef ImGuiAndroid_Drawing
#define ImGuiAndroid_Drawing

#include "ImGui/imgui_internal.h"


namespace ESP
   {
       
void DrawLine(ImVec2 start, ImVec2 end,ImVec4 color,float size)
   {
   auto background = ImGui::GetBackgroundDrawList();
   if(background)
   {
    background->AddLine(start, end, ImColor(color.x, color.y, color.z, color.w),size);
   }
}

 void DrawText(float fontSize, ImVec2 position, ImVec4 color, const char *text)
    {
        auto background = ImGui::GetBackgroundDrawList();

        if(background)
        {
            background->AddText(NULL, fontSize, position, ImColor(color.x, color.y, color.z, color.w), text);
        }
    }

     
void DrawBox(Rect rect, ImVec4 color,float size)
    {
        ImVec2 v1(rect.x, rect.y);
        ImVec2 v2(rect.x + rect.width, rect.y);
        ImVec2 v3(rect.x + rect.width, rect.y + rect.height);
        ImVec2 v4(rect.x, rect.y + rect.height);

        DrawLine(v1, v2, color,size);
        DrawLine(v2, v3, color,size);
        DrawLine(v3, v4, color,size);
        DrawLine(v4, v1, color,size);
    }
    

    
Vector3 add(Vector3 a, Vector3 b) {
    Vector3 c;
    c.x= a.x + b.x;
    c.y = a.y + b.y;
    c.z = a.z + b.z;
    return c;
}
    


void DrawCircleHealth(ImVec2 position, int health, int max_health, float raddi) {
    float a_max = ((3.14159265359f * 2.0f));
    ImU32 healthColor = IM_COL32(0, 160, 0, 230); // GREEN
    if (health <= (max_health * 0.6)) {
        healthColor = IM_COL32(255, 255, 0, 110); // YELLOW
    }
    if (health < (max_health * 0.3)) {
        healthColor = IM_COL32(255, 0, 0, 255); // RED
    }
    ImGui::GetBackgroundDrawList()->PathArcTo(position, raddi, (-(a_max / 4.0f)) + (a_max / max_health) * (max_health - health), a_max - (a_max / 4.0f));
    ImGui::GetBackgroundDrawList()->PathStroke(healthColor, ImDrawFlags_None, 4);
}

 
void DrawCircleFilled(ImVec2 end, float radius, ImVec4 color)
    {
        auto background = ImGui::GetBackgroundDrawList();

        if(background)
        {
         

                background->AddCircleFilled(end, radius, ImColor(color.x, color.y, color.z, color.w));
            

            
        }
    }
}




//copy pested hehehe
string float_to_string_health (int value) 
{
    string str; 
    str = "HEALTH : ";
    str += std::to_string(value);
    return str;
}


template <typename T>
struct monoArray
{
    void* klass;
    void* monitor;
    void* bounds;
    int   max_length;
    void* vector [1];
    int getLength()
    {
        return max_length;
    }
    T getPointer()
    {
        return (T)vector;
    }
};

template <typename T>
struct monoList {
	void *unk0;
	void *unk1;
	monoArray<T> *items;
	int size;
	int version;
	
	T getItems(){
		return items->getPointer();
	}
	
	int getSize(){
		return size;
	}
	
	int getVersion(){
		return version;
	}
};

template <typename K, typename V>
struct monoDictionary {
	void *unk0;
	void *unk1;
	monoArray<int **> *table;
	monoArray<void **> *linkSlots;
	monoArray<K> *keys;
	monoArray<V> *values;
	int touchedSlots;
	int emptySlot;
	int size;
	
	K getKeys(){
		return keys->getPointer();
	}
	
	V getValues(){
		return values->getPointer();
	}
	
	int getNumKeys(){
		return keys->getLength();
	}
	
	int getNumValues(){
		return values->getLength();
	}
	
	int getSize(){
		return size;
	}
};

#endif
