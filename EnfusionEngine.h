/**
 * Copyright (c) 2019 exsightcore (by emey)
 * last up - 04.19.2019
 */


#include "Engine.h"
#include "EnfusionProcess.h"

struct Types
{
	static const uint64_t dayzplayer = 0x7265;
	static const uint64_t Car = 0x2C948FCF;
	static const uint64_t Thing = 0xD7DD68DB;
};

class EnfusionEngine
{
public:
	static uint64_t GetWorld();
	static uint64_t GetNetworkManager();
	static uint64_t GetNetworkClient();
	static uint64_t GetNetworkClientScoreBoard();
	static string GetNetworkClientServerName();
	static uint64_t GetCountOfPlayers();
	static string GetPlayerName(uint64_t Entity);
	static string GetItemName(uint64_t Entity); // my own
	static uint64_t GetPlayerIdentityNetworkId(uint64_t Identity);
	static string GetPlayerIdentityPlayerName(uint64_t Identity);
	static uint64_t GetIdentity(uint64_t networkId);
	static uint64_t GetCamera();
	static uint64_t GetCameraEntry();
	static uint64_t GetCameraOn();
	static uint64_t GetLocalPlayer();
	static uint64_t GetLocalPlayerVisualState();
	static uint64_t GetInventory(uint64_t Entity);
	static string GetItemInHands(uint64_t Entity);
	static uint64_t GetEntity(uint64_t PlayerList, uint64_t SelectedPlayer);
	static uint64_t GetNetworkId(uint64_t Entity);
	static string GetEntityTypeName(uint64_t Entity);
	static uint64_t GetType(uint64_t Entity);
	static string GetTypeName(uint64_t Entity);
	static string GetModelName(uint64_t Entity);
	static Vector3 GetCoordinate(uint64_t Entity);
	static float GetDistanceToMe(Vector3 Entity);
	static float GetDistanceFromTo(Vector3 From, Vector3 To);
	static uint64_t GetItemTable();
	static uint64_t GetItemTableSize();
	static uint64_t NearEntityTable();
	static uint64_t NearEntityTableSize();
	static uint64_t FarEntityTable();
	static uint64_t FarEntityTableSize();
	static uint64_t BulletTable();
	static uint64_t BulletTableSize();
	static vector<uint64_t> GetAllItems();
	static vector<uint64_t> GetNearEntityes();
	static vector<uint64_t> GetFarEntityes();
	static vector<uint64_t> GetAllEntityes();
	static vector<uint64_t> GetAllBullets();
	static Vector3 WorldToScreen(Vector3 Position);
	static void MovCameraUp();
	static void MovCameraDown();
	static void MovCameraRight();
	static void MovCameraLeft();
	static void MovCameraForward();
	static void MovCameraBackward();
	static void SetTerrainGrid(float value);
	static float CameraSpeed;
	static bool SetPosition(uint64_t Entity, Vector3 to);
	static bool KillBySilentAim(uint64_t Entity);
	static bool SetCameraMovSpeed(float Speed);
	static Vector3 GetInvertedViewRight();
	static Vector3 GetInvertedViewUp();
	static Vector3 GetInvertedViewForward();
	static Vector3 GetViewportSize();
	static Vector3 GetInvertedViewTranslation();
	static Vector3 GetProjectionD1();
	static Vector3 GetProjectionD2();
	static string GetDirection();
	static float RadiansToDegrees(float value);
private:
	static string ReadArmaString(uint64_t address);
};

uint64_t EnfusionEngine::GetWorld() {
	return EnfusionProcess::ReadData<uint64_t>(
		EnfusionProcess::ModuleBase + off_world);
}

uint64_t EnfusionEngine::GetNetworkManager() {
	return EnfusionProcess::ReadData<uint64_t>(
		EnfusionProcess::ModuleBase + off_networkmanager);
}

uint64_t EnfusionEngine::GetNetworkClient() {
	return EnfusionProcess::ReadData<uint64_t>(
		EnfusionEngine::GetNetworkManager() + off_networkmanager_networkclient);
}

uint64_t  EnfusionEngine::GetNetworkClientScoreBoard() {
	return EnfusionProcess::ReadData<uint64_t>(
		EnfusionEngine::GetNetworkClient() + off_networkclient_scoreboard);
}

string EnfusionEngine::GetNetworkClientServerName() {
	return EnfusionEngine::ReadArmaString(EnfusionProcess::ReadData<uint64_t>(
		EnfusionEngine::GetNetworkClient() + off_networkclient_servername)).c_str();
}

uint64_t EnfusionEngine::GetCountOfPlayers() {
	return EnfusionProcess::ReadData<uint64_t>(
		EnfusionEngine::GetNetworkClientScoreBoard() + off_sortedobject_entity);
}

string EnfusionEngine::GetPlayerName(uint64_t Entity) {

	return GetPlayerIdentityPlayerName(
		EnfusionEngine::GetNetworkId(Entity)).c_str();
}

string EnfusionEngine::GetItemName(uint64_t Entity) {

	return GetItemName(
		EnfusionEngine::GetNetworkId(Entity)).c_str();
}

uint64_t EnfusionEngine::GetPlayerIdentityNetworkId(uint64_t Identity) {
	return EnfusionProcess::ReadData<uint64_t>(Identity + off_playeridentity_networkid);
}

string EnfusionEngine::GetPlayerIdentityPlayerName(uint64_t Identity) {
	return EnfusionEngine::ReadArmaString(EnfusionProcess::ReadData<uint64_t>(Identity + off_playeridentity_playername));
}

uint64_t EnfusionEngine::GetIdentity(uint64_t networkId) {
	for (uint64_t i = 0; i < EnfusionEngine::GetCountOfPlayers(); i++) {
		uint64_t tempIdentity = EnfusionEngine::GetPlayerIdentityNetworkId(
			EnfusionProcess::ReadData<uint64_t>(
				EnfusionEngine::GetNetworkClientScoreBoard() + i * off_networkclient_playeridentity_size));

		if (tempIdentity == networkId)
			return  tempIdentity;
	}
}

uint64_t EnfusionEngine::GetCameraOn() {
	return EnfusionProcess::ReadData<uint64_t>(
		EnfusionEngine::GetWorld() + off_world_cameraon);
}

uint64_t EnfusionEngine::GetCamera() {
	return EnfusionProcess::ReadData<uint64_t>(
		EnfusionEngine::GetWorld() + off_world_camera);
}

uint64_t EnfusionEngine::GetCameraEntry() {
	return EnfusionProcess::ReadData<uint64_t>(
		EnfusionEngine::GetLocalPlayer() + off_entity_cameraentry);
}

bool EnfusionEngine::SetCameraMovSpeed(float Speed) {
	EnfusionEngine::CameraSpeed = Speed;
	return true;
}

float EnfusionEngine::CameraSpeed = 1.0f;

void EnfusionEngine::MovCameraUp() {
	if (EnfusionEngine::CameraSpeed <= 0) { EnfusionEngine::CameraSpeed = 1.0f; }

	float updown = EnfusionProcess::ReadData<float>(
		EnfusionEngine::GetCameraEntry() + off_cameraentry_movupdown);

	EnfusionProcess::WriteData<float>(
		EnfusionEngine::GetCameraEntry() + off_cameraentry_movupdown, updown + EnfusionEngine::CameraSpeed);
}

void EnfusionEngine::MovCameraDown() {
	if (EnfusionEngine::CameraSpeed <= 0) { EnfusionEngine::CameraSpeed = 1.0f; }

	float updown = EnfusionProcess::ReadData<float>(
		EnfusionEngine::GetCameraEntry() + off_cameraentry_movupdown);

	EnfusionProcess::WriteData<float>(
		EnfusionEngine::GetCameraEntry() + off_cameraentry_movupdown, updown - EnfusionEngine::CameraSpeed);
}

void EnfusionEngine::MovCameraRight() {
	if (EnfusionEngine::CameraSpeed <= 0) { EnfusionEngine::CameraSpeed = 1.0f; }

	float updown = EnfusionProcess::ReadData<float>(
		EnfusionEngine::GetCameraEntry() + off_cameraentry_movleftright);

	EnfusionProcess::WriteData<float>(
		EnfusionEngine::GetCameraEntry() + off_cameraentry_movleftright, updown + EnfusionEngine::CameraSpeed);
}

void EnfusionEngine::MovCameraLeft() {
	if (EnfusionEngine::CameraSpeed <= 0) { EnfusionEngine::CameraSpeed = 1.0f; }

	float updown = EnfusionProcess::ReadData<float>(
		EnfusionEngine::GetCameraEntry() + off_cameraentry_movleftright);

	EnfusionProcess::WriteData<float>(
		EnfusionEngine::GetCameraEntry() + off_cameraentry_movleftright, updown - EnfusionEngine::CameraSpeed);
}

void EnfusionEngine::MovCameraForward() {
	if (EnfusionEngine::CameraSpeed <= 0) { EnfusionEngine::CameraSpeed = 1.0f; }

	float updown = EnfusionProcess::ReadData<float>(
		EnfusionEngine::GetCameraEntry() + off_cameraentry_movforwardbackward);

	EnfusionProcess::WriteData<float>(
		EnfusionEngine::GetCameraEntry() + off_cameraentry_movforwardbackward, updown - EnfusionEngine::CameraSpeed);
}

void EnfusionEngine::MovCameraBackward() {
	if (EnfusionEngine::CameraSpeed <= 0) { EnfusionEngine::CameraSpeed = 1.0f; }

	float updown = EnfusionProcess::ReadData<float>(
		EnfusionEngine::GetCameraEntry() + off_cameraentry_movforwardbackward);

	EnfusionProcess::WriteData<float>(
		EnfusionEngine::GetCameraEntry() + off_cameraentry_movforwardbackward, updown + EnfusionEngine::CameraSpeed);
}

void EnfusionEngine::SetTerrainGrid(float value) {
	EnfusionProcess::WriteData<float>(EnfusionEngine::GetWorld() + off_world_terraingrid, value); //0 - remove 12 - set
}

uint64_t EnfusionEngine::GetLocalPlayer() {
	return EnfusionProcess::ReadData<uint64_t>(
		EnfusionEngine::GetCameraOn() + off_sortedobject_entity);
}

uint64_t EnfusionEngine::GetLocalPlayerVisualState() {
	return EnfusionProcess::ReadData<uint64_t>(
		EnfusionEngine::GetLocalPlayer() + off_entity_futurevisualstate);
}

uint64_t EnfusionEngine::GetEntity(uint64_t PlayerList, uint64_t SelectedPlayer) {
	return EnfusionProcess::ReadData<uint64_t>(PlayerList + SelectedPlayer * off_sortedobject_entity);
}

uint64_t EnfusionEngine::GetNetworkId(uint64_t Entity) {
	return EnfusionProcess::ReadData<uint64_t>(Entity + off_entity_networkid);
}

uint64_t EnfusionEngine::GetInventory(uint64_t Entity) {
	return EnfusionProcess::ReadData<uint64_t>(Entity + off_entity_inventory);
}

string EnfusionEngine::GetItemInHands(uint64_t Entity) {
	return EnfusionEngine::ReadArmaString(EnfusionProcess::ReadData<uint64_t>(
		EnfusionProcess::ReadData<uint64_t>(EnfusionProcess::ReadData<uint64_t>(
			EnfusionEngine::GetInventory(Entity) + off_inventory_iteminhands)
			+ off_entity_rendererentitytype) + off_entitytype_cleanname)).c_str();
}

string EnfusionEngine::GetEntityTypeName(uint64_t Entity) {
	return EnfusionEngine::ReadArmaString(EnfusionProcess::ReadData<uint64_t>(
		EnfusionProcess::ReadData<uint64_t>(
			Entity + off_entity_rendererentitytype)
		+ off_entitytype_configname)).c_str();
}

uint64_t EnfusionEngine::GetType(uint64_t Entity) {
	return EnfusionProcess::ReadData<uint64_t>(
		EnfusionProcess::ReadData<uint64_t>(
			EnfusionProcess::ReadData<uint64_t>(
				Entity + off_entity_rendererentitytype)
			+ off_entitytype_configname) + 0x18);
}

Vector3 EnfusionEngine::GetInvertedViewRight() {
	return Vector3(EnfusionProcess::ReadData<Vector3>(
		EnfusionEngine::GetCamera() + off_camera_viewright));
}

Vector3 EnfusionEngine::GetInvertedViewUp() {
	return Vector3(EnfusionProcess::ReadData<Vector3>(
		EnfusionEngine::GetCamera() + off_camera_viewup));
}

Vector3 EnfusionEngine::GetInvertedViewForward() {
	return Vector3(EnfusionProcess::ReadData<Vector3>(
		EnfusionEngine::GetCamera() + off_camera_viewforward));
}

Vector3 EnfusionEngine::GetViewportSize() {
	return Vector3(EnfusionProcess::ReadData<Vector3>(
		EnfusionEngine::GetCamera() + off_camera_viewportsize));
}

Vector3 EnfusionEngine::GetInvertedViewTranslation() {
	return Vector3(EnfusionProcess::ReadData<Vector3>(
		EnfusionEngine::GetCamera() + off_camera_viewtranslation));
}

Vector3 EnfusionEngine::GetProjectionD1() {
	return Vector3(EnfusionProcess::ReadData<Vector3>(
		EnfusionEngine::GetCamera() + off_camera_projection_d1));
}

Vector3 EnfusionEngine::GetProjectionD2() {
	return Vector3(EnfusionProcess::ReadData<Vector3>(
		EnfusionEngine::GetCamera() + off_camera_projection_d2));
}

Vector3 EnfusionEngine::WorldToScreen(Vector3 Position)
{
	//convert world cords to screen cords :)

	if (!EnfusionEngine::GetCamera())
		return Vector3();

	Vector3 temp = Position - EnfusionEngine::GetInvertedViewTranslation();

	float x = temp.Dot(EnfusionEngine::GetInvertedViewRight());
	float y = temp.Dot(EnfusionEngine::GetInvertedViewUp());
	float z = temp.Dot(EnfusionEngine::GetInvertedViewForward());

	return Vector3(
		EnfusionEngine::GetViewportSize().x * (1 + (x / EnfusionEngine::GetProjectionD1().x / z)),
		EnfusionEngine::GetViewportSize().y * (1 - (y / EnfusionEngine::GetProjectionD2().y / z)),
		z);
}

float EnfusionEngine::RadiansToDegrees(float radians) {
	float degrees;
	degrees = ((radians * 180) / 3.14159265358979323846);
	return degrees;
}

string EnfusionEngine::GetDirection()
{
	//get ur direction view

	Vector3 viewAnglesRadians, viewAngle;
	viewAnglesRadians.x = atan2(
		EnfusionEngine::GetInvertedViewRight().z, EnfusionEngine::GetInvertedViewRight().x);
	viewAngle.x = EnfusionEngine::RadiansToDegrees(viewAnglesRadians.x);
	viewAnglesRadians.y = atan2(
		EnfusionEngine::GetInvertedViewForward().y, EnfusionEngine::GetInvertedViewUp().y);
	viewAngle.y = EnfusionEngine::RadiansToDegrees(viewAnglesRadians.y);

	if (viewAngle.x >= 0 && viewAngle.x <= 90) {
		return "NW";
	}
	else if (viewAngle.x <= 0 && viewAngle.x >= -90) {
		return "NE";
	}
	else if (viewAngle.x >= 90 && viewAngle.x <= 180) {
		return "SW";
	}
	else if (viewAngle.x <= -90 && viewAngle.x >= -180) {
		return "SE";
	}
}

Vector3 EnfusionEngine::GetCoordinate(uint64_t Entity)
{
	if (Entity == EnfusionEngine::GetLocalPlayer()) {
		return Vector3(EnfusionProcess::ReadData<Vector3>(
			EnfusionEngine::GetLocalPlayerVisualState() + off_visualstate_position));
	}
	else {
		return  Vector3(EnfusionProcess::ReadData<Vector3>(
			EnfusionProcess::ReadData<uint64_t>(
				Entity + off_entity_renderervisualstate) + off_visualstate_position));
	}
}

float EnfusionEngine::GetDistanceToMe(Vector3 Entity)
{
	return Entity.Distance(
		EnfusionEngine::GetCoordinate(EnfusionEngine::GetLocalPlayer()));
}

float EnfusionEngine::GetDistanceFromTo(Vector3 From, Vector3 To)
{
	return From.Distance(To);
}

string EnfusionEngine::GetTypeName(uint64_t Entity) {

	return EnfusionEngine::ReadArmaString(EnfusionProcess::ReadData<uint64_t>(
		EnfusionProcess::ReadData<uint64_t>(Entity + off_entity_rendererentitytype) + off_entitytype_typename)).c_str();
}

string EnfusionEngine::GetModelName(uint64_t Entity) {

	return EnfusionEngine::ReadArmaString(EnfusionProcess::ReadData<uint64_t>(
		EnfusionProcess::ReadData<uint64_t>(Entity + off_entity_rendererentitytype) + off_entitytype_modelname)).c_str();
}

uint64_t EnfusionEngine::BulletTable() {
	return EnfusionProcess::ReadData<uint64_t>(
		EnfusionEngine::GetWorld() + off_world_bullettable);
}

uint64_t EnfusionEngine::BulletTableSize() {
	return sizeof(EnfusionEngine::BulletTable());
}

uint64_t EnfusionEngine::GetItemTable()
{
	return EnfusionProcess::ReadData<uint64_t>(
		EnfusionEngine::GetWorld() + off_world_itemtable);
}

uint64_t EnfusionEngine::GetItemTableSize() {
	return sizeof(EnfusionEngine::GetItemTable()) * 3;
}


uint64_t EnfusionEngine::NearEntityTable() {
	return EnfusionProcess::ReadData<uint64_t>(
		EnfusionEngine::GetWorld() + off_world_nearanimaltable);
}

uint64_t EnfusionEngine::NearEntityTableSize() {
	return sizeof(EnfusionEngine::NearEntityTable());
}

uint64_t EnfusionEngine::FarEntityTable() {
	return EnfusionProcess::ReadData<uint64_t>(
		EnfusionEngine::GetWorld() + off_world_faranimaltable);
}

uint64_t EnfusionEngine::FarEntityTableSize() {
	return sizeof(EnfusionEngine::FarEntityTable());
}

vector<uint64_t> EnfusionEngine::GetAllItems()
{
	vector<uint64_t> arrayList;

	for (uint64_t ItemId = NULL; ItemId < EnfusionEngine::GetItemTableSize(); ++ItemId) {
		arrayList.push_back(EnfusionEngine::GetEntity(EnfusionEngine::GetItemTable(), ItemId));
	}

	return arrayList;
}

vector<uint64_t> EnfusionEngine::GetNearEntityes() // get entityes from 0 - 100m
{
	vector<uint64_t> arrayList;

	for (uint64_t playerId = NULL; playerId < EnfusionEngine::NearEntityTableSize(); ++playerId) {
		arrayList.push_back(EnfusionEngine::GetEntity(EnfusionEngine::NearEntityTable(), playerId));
	}
	return arrayList;
}

vector<uint64_t> EnfusionEngine::GetFarEntityes() // get entityes from 100 - 1000 & 1635m
{
	vector<uint64_t> arrayList;

	for (uint64_t playerId = NULL; playerId < EnfusionEngine::FarEntityTableSize(); ++playerId) {
		arrayList.push_back(EnfusionEngine::GetEntity(EnfusionEngine::FarEntityTable(), playerId));
	}
	return arrayList;
}

bool EnfusionEngine::SetPosition(uint64_t Entity, Vector3 TargetPosition)
{
	if (Entity == EnfusionEngine::GetLocalPlayer()) {
		EnfusionProcess::WriteData<Vector3>(
			EnfusionProcess::ReadData<uint64_t>(
				Entity + off_entity_futurevisualstate) + off_visualstate_position, TargetPosition);
	}
	else {
		EnfusionProcess::WriteData<Vector3>(
			EnfusionProcess::ReadData<uint64_t>(
				Entity + off_entity_renderervisualstate) + off_visualstate_position, TargetPosition);
	}
	return true;
}

bool EnfusionEngine::KillBySilentAim(uint64_t Entity)
{
	for (uint64_t playerId = NULL; playerId < EnfusionEngine::BulletTableSize(); ++playerId) {
		Vector3 WorldPosition = EnfusionEngine::GetCoordinate(Entity);
		EnfusionEngine::SetPosition(EnfusionEngine::GetEntity(EnfusionEngine::BulletTable(), playerId), // tp ur bullet to entity head
			Vector3(WorldPosition.x, WorldPosition.y + 1.0f, WorldPosition.z)); // body pos [+/-] :)
	}
	return true;
}

vector<uint64_t> EnfusionEngine::GetAllBullets()
{
	vector<uint64_t> arrayList;

	for (uint64_t playerId = NULL; playerId < EnfusionEngine::BulletTableSize(); ++playerId) {
		arrayList.push_back(EnfusionEngine::GetEntity(EnfusionEngine::BulletTable(), playerId));
	}

	return arrayList; 
}

vector<uint64_t> EnfusionEngine::GetAllEntityes()
{
	vector<uint64_t> arrayList;

	for (uint64_t playerId = NULL; playerId < EnfusionEngine::NearEntityTableSize() + 512; ++playerId) {
		if (playerId != 0) { // check if entity != localplayer
			uint64_t targetentity = EnfusionEngine::GetEntity(EnfusionEngine::NearEntityTable(), playerId);

			if (EnfusionEngine::GetEntityTypeName(targetentity) == "dayzplayer") {
				arrayList.push_back(targetentity);
			}
		}
	}

	for (uint64_t playerId = NULL; playerId < EnfusionEngine::FarEntityTableSize() + 512; ++playerId) {
		uint64_t targetentity = EnfusionEngine::GetEntity(EnfusionEngine::FarEntityTable(), playerId);

		if (EnfusionEngine::GetEntityTypeName(targetentity) == "dayzplayer") {
			arrayList.push_back(targetentity);
		}
	}

	return arrayList;
}

std::string EnfusionEngine::ReadArmaString(uint64_t address)
{
	int length = EnfusionProcess::ReadData<uint64_t>(address + off_length);
	std::string text = EnfusionProcess::ReadString(address + off_text, length);

	return text.c_str();
}




















