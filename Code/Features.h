namespace Features {
	void UpdatePerTick();



	extern int StealthTimer;
	extern bool AimbotAutoShoot;
	extern bool TPToMeBool;
	void TPToMe();
	void UpdatePlayerList();
	extern const char* Name;
	extern const char* RID;
	extern const char* GodeModeInfo;
	extern int Wanted;
	extern const char* Street;
	extern const char* Zone;
	extern const char* Veh;
	extern float armorper;
	extern int TotalEvents;
	extern bool EnableControlBypass;
	void ClearPropProtection();
	extern bool ClearPropProtectionBool;
	extern int ConnectedPlayer;
	extern bool HashGunBool;
	void HashGun();
	extern bool IsOnline;
	extern bool AddWeaponsBool;
	void AddWeapons();

	extern bool UpdateInfo;
	extern const char* Speeed;
	extern bool AimbotESPTarget;
	extern bool BlindEyeAll;
	extern bool FixLoop;
	extern bool FreezeAll;
	extern bool WaterAll;
	extern bool FireAll;
	bool ImGUIMode;
	extern bool SoundSpamAll;
	extern bool RockstarCheck;
	extern bool ExplodeAll;
	extern bool NeverWantedAll;
	extern bool RemoteOTRAll;
	extern bool CameraSpamAll;
	extern int hornboostspeed;
	extern int TotalDropedMoney;
	extern int MoneyNotifyAmount;
	extern int TotalMoneyBags;
	extern bool CLOWNGUN;
	void KickPlayer();
	void clowngun(bool toggle);
	extern int ShootCash;
	extern bool MOLOTOV;
	void molotov(bool toggle);
	extern bool KickPlayerBool;
	extern bool FlyingCarBool;
	void FlyingCar(bool toggle);

	extern bool BlamePlayerBool;

	void SendToJob();
	extern bool SendToJobBool;


	extern bool BlackScreenBool;
	void BlackScreen();


	extern bool bomber;
	void bomber_mode(bool toggle);


	extern bool KickDropBool;
	void KickDrop();


	extern int Explosionfickk;
	extern int Explosionfickkkk;
	extern int ficksizee;
	extern int Explosionfick;
	extern int ficksize;
	extern int rt;
	extern int rrt;
	extern int rrrt;

	extern bool fuckedhandling;
	void fuckhandling(bool toggle);



	extern bool VehSpamCrashBool;
	void VehSpamCrash(bool toggle);


	void SaveRID(std::string name, char* rockstarid);

	extern Vector3 oregano;

	extern bool Carelectric;

	extern bool CarClownLoop;
	extern bool Carfireworkloop;
	extern bool Caralien1;
	extern bool Caralien2;
	extern bool Carelectric;
	extern bool CarLightning;
	extern bool moneyeffect15;
	extern bool ghooosoot;
	extern int BlockedEvents;
	extern bool ForceShowMoneyStat;
	extern bool MenuHelpBool;
	void MenuHelp(bool toggle);

	extern bool BetterFlyingCarBool;
	void BetterFlyingCar(bool toggle);

	extern bool hornboostbool;
	void hornboost(bool toggle);


	extern bool DisablePhoneBool;
	void DisablePhone(bool toggle);
	extern bool BlackHoleBool;
	void BlackHole(bool toggle);

	void HeartBeat();

	extern bool ShowAllPlayerRadarBool;
	void ShowAllPlayerRadar(bool toggle);

	extern bool CrashLobbyBool;
	void CrashLobby(bool toggle);

	extern char* selectShootVeh;

	extern char keyyy[50];

	extern bool Raser;
	void raser(bool toggle);

	extern bool leagun;
	void leaWgun(bool toggle);

	extern bool SmokeAmmoBool;
	void SmokeAmmo(bool toggle);

	extern bool Grenade;
	void grenade(bool toggle);


	extern bool LobbySaveBool;
	void LobbySave(bool toggle);

	extern bool Flare;
	void flare(bool toggle);

	extern bool RPG;
	void rpg(bool toggle);

	extern Hash DROPHASH;
	extern bool DeleteVehicleBool;
	void DeleteVehicle(bool toggle);

	extern bool ExplodeVehicleBool;
	void ExplodeVehicle(bool toggle);

	void CustomVehicleColor();
	void SendTextMessage(char* msg);
	void RockstarAdminCheck();
	void HalloweenEnable();
	void SetWeathers(int weather);
	void Hulk(bool toggle);
	void SendTextMessage(int player);
	void MagicCarpet(bool toggle);
	void LoadPlugins(fs::path asi_path);
	void GodMode(bool toggle);
	void UltraJump(bool toggle);
	void FireBreath(bool toggle);
	void PTFXLightning(bool toggle);
	void PedSize(bool toggle);
	extern bool GodModeBool;
	void neverwant(bool toggle);

	extern bool neverwantbool;

	void randomoutfit();

	extern std::string ConsoleLogger;

	extern bool espbool;
	void esp();
	namespace ESP {
		extern int red;
		extern int green;
		extern int blue;
	}
	extern bool HeaderImage;
	extern bool dowbool;
	extern int DropAmount;
	extern bool CustomVehicleColorBool;
	extern bool PedSizeBool;
	extern bool MagicCarpetBool;
	extern bool UltraJumpBool;
	extern bool Forcefield;
	extern bool FireBreathBool;
	extern bool RemoteNeverWanted[32];
	void ShootVehicle(bool toggle);
	extern bool ShootVehicleBool;


	extern bool AimbotAutoShoot;
	extern bool AimbotESPTarget;


	extern bool PTFXLightningBool;
	extern float pedsizee;
	extern bool HulkBool;
	extern int RPDROPDELAY;
	extern float pedwithh;
	extern bool DisplayFPS;
	extern bool CashDropAll;
	//void RequestControlOfEnt(Entity entity);
	extern float RunSpeed;
	void featureDisplayFPS(bool toggle);
	extern bool CashDropLocationBool;
	extern bool BlockAllProtex;
	extern bool ChatCommands, SlashVehicle, SlashCash, SlashOtr, SlashDay, SlashNight, SlashSnow, SlashClear, SlashWeapons, SlashNeverWanted, SlashClone;

	void OfficeMoney();
	void OfficeStatue();
	void CashDropLocation();
	void DriveOnWater();
	void SaveOutfit(std::string name);
	extern bool ObjectGunBool;
	extern bool VALKYIREROCKET;
	void valkyirerocket();
	extern bool GravityGun;
	void gravitygun();
	void objectgunpl();
	extern bool AntiMoneyDrop;
	void Enemy(char* model);
	void Bodyguard(char* model);
	extern bool ToBank;
	extern bool SlowMoBool;
	void SlowMo();


	extern int alpha;
	void DeleteVeh();

	extern bool SpawnMaxed;
	extern bool SpawnInCar;
	extern bool SpawnEffect;
	extern bool freecambool;
	void freecam();

	void PlaceObjectByHash (Hash hash, float x, float y, float z, float pitch, float roll, float yaw, float heading, int id);

	extern bool noclipallbool;
	void noclipall();

	extern bool ShootAsteroidBool;
	void ShootAsteroid();

	extern bool ExplodeAmmoBool;
	void ExplodeAmmo();


	extern bool CloneProtectionBool;
	void CloneProtection(bool toggle);


	void previewCar(const char* carname);

	extern bool ExplosiveAmmoBool;
	void ExplosiveAmmoo();

	extern bool particel8bool;
	void particel8(bool toggle);

	extern bool particel9bool;
	void particel9(bool toggle);

	extern bool BunkerBool;
	void Bunker(bool toggle);


	extern bool particel10bool;
	void particel10(bool toggle);

	extern bool particel11bool;
	void particel11(bool toggle);

	extern bool particel12bool;
	void particel12(bool toggle);

	extern bool particel13bool;
	void particel13(bool toggle);

	extern bool particel14bool;
	void particel14(bool toggle);

	extern bool particel15bool;
	void particel15(bool toggle);

	extern bool particel16bool;
	void particel16(bool toggle);

	extern int KohleMoney;

	extern bool StealthBool;
	void Stealth(bool toggle);

	extern bool VehStealthBool;
	void VehStealth(bool toggle);



	extern bool WaterSplashBool;
	void WaterSplash(bool toggle);

	extern bool ElectricBool;
	void Electric(bool toggle);


	extern bool DisableHUDBool;
	void DisableHUD(bool toggle);

	extern bool MaxHeistPayoutBool;
	void MaxHeistPayout(bool toggle);

	extern bool ElectricBooshBool;
	void ElectricBoosh(bool toggle);

	extern bool SmokeBool;
	void Smoke(bool toggle);

	extern bool SlideRunBool;
	void SlideRun(bool toggle);

	extern bool MoneyGunBool;
	void MoneyGun(bool toggle);


	extern bool NetworKIDCrashBool;
	void NetworkIDCrash(bool toggle);


	extern bool DriveItBool;
	void DriveIt(bool toggle);


	extern bool ModelCrashBool;
	void ModelCrash(bool toggle);

	extern bool isolatemebool;
	void isolateme();

	extern bool AirWalkBool;
	void AirWalk();

	extern bool AFKNo;
	void AntiAFK();

	extern bool MenuNotifyBool;
	void MenuNotify();

	extern bool RunningBool;
	void RunningFast(bool toggle);

	extern bool BackstrokePro;
	void BackstrokeSpeed();


	extern bool ShowCurrentCoordBool;
	void ShowCurrentCoord(bool toggle);

	extern bool SentDetectionEventBool;
	void SentDetectionEvent();





	extern bool InvisibilityBool;
	void Invisibility();

	extern bool mobileRadio;
	void mobiletunes();

	extern bool RPGunBool;
	void RPGun(bool toggle);

	extern bool AlienOneBool;
	void Alien(bool toggle);

	extern bool AlienTwoBool;
	void AlienTwo(bool toggle);

	extern bool DriftModeBool;
	void DriftMode(bool toggle);



	extern bool ClownEffectBool;
	void ClownEffect(bool toggle);

	extern bool GhostRiderBool;
	void GhostRider(bool toggle);

	extern bool RagdollBool;
	void NoRagdoll();

	extern bool OffRadarBool;
	void OffRadar(bool toggle);

	extern bool ShootR;
	void ShootRocket(bool toggle);


	extern bool AttachmentBool;
	void Attachment(bool toggle);

	extern bool ShootT;
	void ShootTanks(bool toggle);


	extern bool ShootTankR;
	void ShootTankRounds(bool toggle);

	extern bool ShootBall;
	void ShootBalls(bool toggle);

	extern bool ShootMini;
	void ShootMiniGun(bool toggle);

	extern bool carRPG;
	void shootRPGCar(bool toggle);

	extern bool llcar;
	void LLCar(bool toggle);

	extern bool ggcar;
	void GGCar(bool toggle);

	extern bool wwcar;
	void WWCar(bool toggle);
	extern bool ExplodePedBool;
	void ExplodePed(bool toggle);


	void WriteVehicle(std::string name, Vehicle veh);

	extern bool cccar;
	void CCCar(bool toggle);

	extern bool ttcar;
	void TTCar(bool toggle);

	extern bool ttcarflare;
	void TTCarflare(bool toggle);


	extern bool qqcar;
	void QQCar(bool toggle);

	extern bool qqcarxdsa;
	void QQCarsd(bool toggle);


	extern bool TinyPlayerBool;
	void TinyPlayer();

	extern int WantedLevel;
	void ChangeWanted(int level);

	extern std::string String;
	void SetName(const std::string& name);

	void HealPlayer();

	extern bool SpectateList;
	void Spectate();

	extern bool FuckCamBool;
	void FuckTheirCam();


	extern bool RPLooperBool;
	void RPLooper(bool toggle);


	extern bool ExplodeList[32];
	void ExplodeLoopPlayer(int target);

	extern bool CashDropRemote[32];
	void CashDropV2(int target);

	Vehicle LoadVehicle(std::string name);


	extern bool WaterList[32];
	void WaterLoop(int target);


	extern bool FireWorkBool;
	void FireWork(bool toggle);

	extern bool FireList[32];
	void FireLoop(int target);

	extern bool FreezeList[32];
	void Freeze(int target);

	void TeleportToPlayer(int player);

	void TrapPlayer(int ped);

	void BlamePlayer();

	void AirStrikeKill();

	void RemoteLevels(int selectedPlayer);



	void CloneVehicle(int ped);

	void TeleportInVehicle(int player);

	void KickFromVehicle(int player);

	void RamPlayer();

	void AttachObjects(char* object);

	void Teleport1(bool all = false);
	void Teleport2(bool all = false);
	void Teleport3(bool all = false);
	void Teleport4(bool all = false);
	void Teleport5(bool all = false);
	void Teleport6(bool all = false);
	void Teleport7(bool all = false);
	void Teleport8(bool all = false);
	void Teleport9(bool all = false);
	void Teleport10(bool all = false);
	void Teleport11(bool all = false);
	void Teleport12(bool all = false);
	void Teleport13(bool all = false);
	void Teleport14(bool all = false);
	void Teleport15(bool all = false);
	void Teleport16(bool all = false);
	void Teleport17(bool all = false);
	void Teleport18(bool all = false);
	void Teleport19(bool all = false);
	void Teleport20(bool all = false);
	void TeleportCustom(int place);

	extern bool Spam[32];
	void DoSoundSpam(int player, bool all = false);

	extern bool RemoteOTRBool[32];
	void RemoteOTR(int target);

	void ForceDisappear();

	void RemoveWanted(int player);



	extern bool CEOKickBool;
	void CEOKick();


	void CEOBan(bool all = false);

	void InfiniteLoading();

	void TrollMessage();


	extern bool SpoofLevelBool;

	void SpoofLevel(bool toggle);




	void Invite2Place(int player, int place);

	void MessageSpam(int player, std::int64_t message);

	extern bool InfiniteAmmoBool;
	void InfiniteAmmo();

	extern bool ExplosiveAmmoFlag;

	extern bool ClownWeaponEffectBool;
	void ClownWeaponEffect(bool toggle);

	extern bool BankNoteEffectBool;
	void BankNoteEffect(bool toggle);

	extern bool TruckCrashEffectBool;
	void TruckCrashEffect(bool toggle);

	extern bool ElectricWeaponEffectBool;
	void ElectricWeaponEffect(bool toggle);

	extern bool AlienWeaponEffectBool;
	void AlienWeaponEffect(bool toggle);

	extern bool FireWorkWeaponTwoBool;
	void FireWorkWeaponTwo(bool toggle);

	extern bool FireWorkWeaponBool;
	void FireWorkWeapon(bool toggle);

	void ExplosiveAmmo();

	extern bool FireShoot;
	void ShootFire();

	extern bool WaterShoot;
	void ShootWater();

	extern bool FireworkBool;
	void FireWork();

	extern bool FireworkBool;
	void FireWork();

	extern bool AirStrike;
	void PreditorGun();

	extern bool fakezerohealthbool;
	void fakezerohealth();





	extern bool seatbeltbool;
	void seatbelt();
	
	extern bool vehiclestealthbool;
	void vehiclestealth();

	extern bool RainbowWeaponsBool;
	void RainbowWeapons();

	extern bool AimbotBool;
	void Aimbot();

	extern bool DamageBool;
	void DamageMod();

	extern bool Recoil;
	void NoRecoil();

	extern bool RapidFireBool;
	void RapidFire();

	extern bool OrbitalCooldownBool;
	void OrbitalCooldown();

	extern int boostlevel;
	void carboost();

	void PlateEdit(char* plate);
	extern std::vector<std::string> list;
	extern std::vector<std::string> ListOutfit;
	extern bool cargodmodebool;
	void cargodmode();

	extern bool flymodebool;
	void flymode(bool toggle);

	extern bool superjumpbool;
	void superjump(bool toggle);

	extern bool ultimatejumpbool;
	void ultimatejump(bool toggle);


	extern bool selfclonebool;
	
	void selfclone(bool toggle);


	extern bool ForceFieldBool;
	void ForceFieeld(bool toggle);

	extern bool ultrarunbool;
	void ultrarun(bool toggle);

	extern bool pilotmanbool;
	void pilotman(bool toggle);

	extern bool dummyflybool;
	void dummyfly(bool toggle);

	extern bool testbool;
	void test(bool toggle);


	extern bool Boost;
	void RocketBoost();

	extern bool zerospeedbool;
	void zerospeed();

	extern bool AsteroidShowerBool;
	void AsteroidShower(bool toggle);


	extern bool FakeLoopBool;
	void FakeLoop(bool toggle);

	extern bool AsteroidBool;
	void Asteroid(bool toggle);

	extern bool ChaosModeBool;
	void ChaosMode(bool toggle);


	extern bool TransActionSpamBool;
	void TransActionSpam();


	extern bool remoteContainerFlybool;
	void remoteContainerFly();

	extern bool containerflybool;
	void containerfly();

	extern bool containerstairsbool;
	void containerstairs();

	extern bool sonicvehicle;
	void carboostt();

	extern bool InvisibleCarBool;
	void InvisibleCar();

	extern bool vehiclegravitybool;
	void vehiclegravity();

	extern bool WeaponRockets;
	void VehicleRockets();

	extern bool piggybackbool;
	void piggyback();

	extern bool SpeedoBool;
	extern bool MPH;
	extern bool PlateMPH;
	void Speedometer();

	extern bool MatrixPlates;
	void MatrixPlate();

	extern bool StickyBool;
	void Sticky();

	void FixCar();

	void maxvehicle();

	void OpenDoors();

	void flip();

	extern int primarycolorintr;
	extern int primarycolorintg;
	extern int primarycolorintb;
	void PrimaryColor();

	extern int secondarycolorintr;
	extern int secondarycolorintg;
	extern int secondarycolorintb;
	void SecondaryColor1();

	extern bool rainbowbool;
	void rainbow();

	extern bool NeonBool;
	void Neon();

	extern bool RainbowPaintLoop;
	void HasPaintLoop();

	void LoadPreset(std::string name);
	extern std::vector<std::string> listPresets();
	extern std::vector<std::string> listoutfit();
	void LoadOutfit(std::string name);

	void AltStealth(int amount);
	extern bool moneyrain2k;
	void RainMoney();
	extern bool superman;
	extern bool EXPLOSION_EVENT;
	extern bool GAME_CLOCK_EVENT;
	extern bool GAME_WEATHER_EVENT;
	extern bool NETWORK_CLEAR_PED_TASKS_EVENT;
	extern bool GIVE_WEAPON_EVENT;
	extern bool REMOVE_WEAPON_EVENT;
	extern bool REMOVE_ALL_WEAPONS_EVENT;
	extern bool FIRE_EVENT;
	extern bool ALTER_WANTED_LEVEL_EVENT;
	void TimeSpam();
	extern bool TimeSpamBool;
	void SuperMan();
	extern int TimePD1;
	extern int BagDelay;
	extern bool AimBool;
	void AimToDelete();
	extern int TimeHour;
	extern int TimeMinute;
	void UpdatePresence();

	extern int TimeSecond;
	void settime(int Hours, int Minutes, int Seconds);

	void Yankton();
	void Yacht();
	void Carrier();
	void SunkenShip();
	void PrimaryColor();
	void Hospital();
	void Farm();
	void Morgue();
	void FixCar();
	void Invader();
	void Jewelry();

	void IrlTime();

	extern int WaveIntensityValue;
	void SetWaveIntensity();

	void SetWeather(int weather);

	extern bool GravityBool;
	void Gravity();

	extern bool explodenearbyvehiclesbool;
	void explodenearbyvehicles();

	extern int Levels[8000];
	extern int levelrp;
	void SetRank(int rpvalue);

	extern bool shootcashbool;
	void shootcash();

	extern bool teleportbool;
	void teleportgun();

	extern bool savenewdrop;
	void cashdropself();
	extern bool MoneyDropBool;
	void MoneyDrop();

	extern bool ALLMoneyDropBool;
	void ALLMoneyDrop();

	extern bool RPDropBool;
	void RPDrop();

	void doStealth(int amount);
	void RemoveStealth(int amount);
	extern bool StealthLoop;

	void UnlockAll();
	void UnlockSnacks();
	void UnlockArmor();
	void UnlockFireworks();
	void UnlockStats();
	void UnlockTattoos();
	void UnlockParachutes();
	void UnlockRims();
	void UnlockVehicles();
	void UnlockAchievements();
	void UnlockHairstyles();
	void UnlockWeapons();
	void UnlockClothes();

	extern bool  SnowBool;
	extern bool  XmasShitBool;
	extern bool  HalloweenShit;

	extern bool  ValentineClothingBool;
	extern bool  ValentineVehicleBool;
	extern bool  ValentineGunBool;
	extern bool  ValentineMaskBool;
	extern bool  ValentineHairBool;
	extern bool  HaloweenWeaponsBool;
	extern bool  HeistBoxvilleBool;
	extern bool  HeistEnduroBool;
	extern bool  HeistHydraBool;
	extern bool  HeistInsurgentBool;
	extern bool  HeistInsurgent2Bool;
	extern bool  HeistLectroBool;
	extern bool  HeistMuleBool;
	extern bool  HeistSavageBool;
	extern bool  HeistTechnicalBool;
	extern bool  HeistValkyrieBool;
	extern bool  HeistPrisonBool;
	extern bool  SnowballBool;
	extern bool  ChristmasContentBool;
	extern bool  ChristmasClothingBool;
	extern bool  ChristmasMaskBool;
	extern bool  ChristmasVehicleBool;
	extern bool  IndpendenceDayBool;
	extern bool  WesternSoverignBool;
	extern bool  MonsterTruckBool;
	extern bool  BeerHat1Bool;
	extern bool  BeerHat2Bool;
	extern bool  BeerHat3Bool;
	extern bool  BeerHat4Bool;
	extern bool  BeerHat5Bool;
	extern bool  BeerHat6Bool;
	void BeerHats();
	void LoadPlayerInfo(int player);
	extern std::string Token;

	extern bool Nametag;
	void NameTagESP();

	extern int StealthAmount;

	extern bool LogEvent;
	extern bool DisableCell;
	void DisablePhone();
	extern bool ChatSensor;
	extern bool LogMetric;
	extern bool EventNotif;

	void ClearProps();

	extern bool Hidden;

	void BruteForceWeaponAddons(Ped ped, Hash weaponHash);

	void TransactionError(int player);

	extern bool MentalStateBool;
	void MentalState();

	void GentleKick(bool all = false);


	extern bool BlindEyeBool[32];
	void BlindEye(int player);

	void BannerMessage();

	extern bool ToggledOn;
	extern bool ToggledOff;
	void SetLobbyTime(int hr, int min, int sec);
	void SetWanted(int level);
	void BankedMoney();
	extern bool AddSpam;
	extern bool BannerSpam;
	extern bool RemoveSpam;

	extern bool CameraSpam[32];
	void sendFaceCameraForward(int player);

	void StolenMoney();

	extern bool DevMode;

	extern bool AmmoEditorBool;
	void AmmoEditor(std::string weaponType);
}