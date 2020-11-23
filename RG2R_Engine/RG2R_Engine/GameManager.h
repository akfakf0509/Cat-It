#pragma once
#include "Object.h"

#include <map>
#include <string>
#include <fstream>

class DataManager
{
private:
	std::map<std::string, std::string> datas;

	bool loaded;
public:
	DataManager();
	~DataManager();

	DataManager* Insert(const std::string&, const std::string&);
	DataManager* Save(const std::string&);
	DataManager* Load(const std::string&);

	bool GetIsLoad();
	std::string GetData(const std::string&);
};

#include <dshow.h>
#pragma comment(lib, "strmiids.lib")

struct Music
{
	IGraphBuilder* pGraph = nullptr;
	IMediaControl* pControl = nullptr;
	IMediaPosition* pPosition = nullptr;
	IMediaEventEx* pEventEx = nullptr;
	IBasicAudio* pBasicAudio = nullptr;
};

class MusicPlayer
{
private:
	HRESULT hr = CoInitialize(NULL);

private:
	std::map<const std::wstring, Music*> musics;
	Music* currentMusic = nullptr;

	bool isPlaying;

	long volume;

public:
	MusicPlayer();
	~MusicPlayer();

	void Update();

	MusicPlayer* Load(const std::wstring&);
	MusicPlayer* Play(const std::wstring&);
	MusicPlayer* Pause();
	MusicPlayer* Stop();
	MusicPlayer* SetVolume(long);
	MusicPlayer* SetPosition(REFTIME);

	long GetVolume();
	REFTIME GetPosition();
};

#define DataM GetDataM()
#define MusicM GetMusicM()
#define PauseM GetPauseM()
#define SettingM GetSettingM()

class GameManager
{
private:
	DataManager* dataManager;
	MusicPlayer* musicManager;
public:
	GameManager();
	~GameManager();

	void Update();

	DataManager* GetDataM() { return dataManager; }
	MusicPlayer* GetMusicM() { return musicManager; }
};

