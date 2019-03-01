/*
	by unitx 12.22.2018 (3.1.2019 - lastUpdate)
*/

#pragma once

#include <windows.h>
#include <winternl.h>
#include <tlhelp32.h>
#include <shlwapi.h>
#include <dwmapi.h> 

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <atlstr.h> 
#include <vector>
#include <assert.h>
#include <sstream>
#include <iostream>
#include <fstream>
#include <tchar.h>

#include <d3d11.h>

#include <string>
#include <thread>
#include <chrono>
#include <mutex>

#include <winioctl.h>
#include <sys/types.h>
#include <algorithm>

#include <iomanip>  
#include <dxgiformat.h>
#include <stdarg.h> 
#include <memory>  
#include <psapi.h>

#include <vector>
#include "Vector3.h"

#pragma warning (disable: 4996)

using namespace std;

// new offsets -> https://www.unknowncheats.me/forum/dayz-sa/104269-dayz-structs-offsets.html

//this offset for last build 03/01/2019 (march)

#define off_world 0xe339c8
#define off_networkmanager 0xddff80

#define off_networkmanager_networkclient 0x50

#define off_networkclient_scoreboard 0x10
#define off_networkclient_playeridentity_size 0x168
#define off_networkclient_servername 0x330

#define off_playeridentity_networkid 0x30
#define off_playeridentity_playername 0x100

#define off_world_camera 0x1b8

#define off_camera_viewright 0x8
#define off_camera_viewup 0x14
#define off_camera_viewforward 0x20
#define off_camera_viewtranslation 0x2C
#define off_camera_viewportsize 0x58
#define off_camera_projection_d1 0xD0
#define off_camera_projection_d2 0xDC

#define off_world_nearanimaltable 0xe48
#define off_world_faranimaltable 0xf90
#define off_world_slowanimaltable 0x10a8
#define off_world_itemtable 0x1f48
#define off_world_bullettable 0xD00 

#define off_world_cameraon 0x2840
#define off_world_playeron 0x2848

#define off_world_terraingrid 0xb40

#define off_sortedobject_entity 0x8

#define off_entity_cameraentry 0x2168
#define off_entity_futurevisualstate 0x88 
#define off_entity_renderervisualstate 0x130
#define off_entity_futureentitytype 0x38
#define off_entity_rendererentitytype 0xe0
#define off_entity_sortobject 0x138
#define off_entity_baseentity 0xa8
#define off_entity_networkid 0x564
#define off_entity_inventory 0x438

#define off_cameraentry_movupdown 0xa4
#define off_cameraentry_movforwardbackward 0xc4
#define off_cameraentry_movleftright 0xc8
#define off_cameraentry_movrotate 0xd8

#define off_inventory_iteminhands 0x200

#define off_entitytype_basetype 0x88
#define off_entitytype_typename 0x68
#define off_entitytype_modelname 0x78
#define off_entitytype_configname 0x98
#define off_entitytype_cleanname 0x540

#define off_visualstate_position 0x2c
#define off_visualstate_headposition 0xf8

#define off_x 0x2c
#define off_y 0x30
#define off_z 0x34

#define off_text 0x10
#define off_length 0x8
