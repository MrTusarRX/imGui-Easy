Vector3 get_position(void *transform) {
    if (!transform)
    return Vector3();
    Vector3 position;
    static const auto get_position_injected = reinterpret_cast<uint64_t(__fastcall *)(void *, Vector3 &)>(getAbsoluteAddress("libil2cpp.so", Offset::getposition));
    get_position_injected(transform, position);
    return position;
}


void *get_camera() {
    static const auto get_camera_injected = reinterpret_cast<uint64_t(__fastcall *)()>(getAbsoluteAddress("libil2cpp.so", Offset::Camera));
    return (void *) 
    get_camera_injected();
}



void *get_transform(void *player)
{
    if(!player)
     return NULL;
    static const auto get_transform_injected = reinterpret_cast<uint64_t(__fastcall *)(void *)>(getAbsoluteAddress("libil2cpp.so",Offset::gettransform));
     return (void *)
     get_transform_injected(player);
    
}



Vector3 WorldToScreenPoint(void *transform ,Vector3 test)
{
    if(!transform)
     return Vector3();
     Vector3 position;
     static const auto WorldToScreenPoint_injected = reinterpret_cast<uint64_t(__fastcall *)(void *, Vector3,int,Vector3 &)>(getAbsoluteAddress("libil2cpp.so",Offset::WorldToScreenPoint));
     WorldToScreenPoint_injected(transform ,test,2,position);    
     return position;   
}


Vector3 GetPlayerPosition(void *player) {
    return get_position(get_transform(player));
}





float GetHealth(void *player) {
    if (!player) return NULL;
    static const auto get_Health = reinterpret_cast<uint64_t(__fastcall *)(void *)>(getAbsoluteAddress("libil2cpp.so", 0x4538B0));
    return (float) get_Health(player);
}
float GetHealthMax(void *player) {
    if (!player) return NULL;
    static const auto get_Health = reinterpret_cast<uint64_t(__fastcall *)(void *)>(getAbsoluteAddress("libil2cpp.so", 0x4538A8));
    return (float) get_Health(player);
}
/* добовлять если есть get_dead
bool GetPlayerDead(void *player) {
    if (!player) return NULL;
    static const auto get_dead = reinterpret_cast<uint64_t(__fastcall *)(void *)>(getAbsoluteAddress("libil2cpp.so", 0xD01B6C));
    return (bool) get_dead(player);
}
*/
bool isDead(void *player) {
    return *(bool *) ((uint64_t) player + 0x102);
}
bool PlayerAlive(void *player) {
    return player != NULL && isDead(player) != true;
}

bool IsPlayerDead(void *player) {
    return player == NULL && isDead(player);
}
