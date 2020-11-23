#include "stdafx.h"
#include "GameManager.h"

DataManager::DataManager() {
	Load("Resources/Data");
}

DataManager::~DataManager() {}

DataManager* DataManager::Insert(const std::string& key, const std::string& value) {
	datas[key] = value;

	return this;
}

DataManager* DataManager::Save(const std::string& path) {
	std::ofstream writeFile;
	writeFile.open(path);

	for (auto iter : datas) {
		std::string data = iter.first + ":" + iter.second + "\n";

		writeFile.write(data.c_str(), data.size());
	}

	return this;
}

DataManager* DataManager::Load(const std::string& path) {
	std::ifstream readFile;
	readFile.open(path);

	if (readFile.is_open()) {
		while (!readFile.eof()) {
			std::string data;

			std::getline(readFile, data);

			if (data == "") {
				break;
			}

			std::string key = data.substr(0, data.find(':'));
			std::string value = data.substr(data.find(':') + 1);

			Insert(key, value);
		}
	}
	else {
		std::cout << "Error Can't load file" << std::endl;
		std::cout << "Path : " << path << std::endl;
		std::cout << "Create File.. " <<

		Save(path);
	}

	return this;
}

bool DataManager::GetIsLoad() {
	return loaded;
}

std::string DataManager::GetData(const std::string& key) {
	if (datas.find(key) == datas.end()) {
		return "-1";
	}

	return datas[key];
}


MusicPlayer::MusicPlayer() {
}

MusicPlayer::~MusicPlayer() {
	for (auto iter : musics) {
		iter.second->pGraph->Release();
		iter.second->pControl->Release();
		iter.second->pPosition->Release();
		iter.second->pEventEx->Release();
		iter.second->pBasicAudio->Release();
	}
	CoUninitialize();
}

void MusicPlayer::Update() {
	long eventCode, param1, param2;

	for (auto iter : musics) {
		iter.second->pEventEx->GetEvent(&eventCode, &param1, &param2, 0);

		if (eventCode == EC_COMPLETE) {
			iter.second->pPosition->put_CurrentPosition(0);
		}

		iter.second->pEventEx->FreeEventParams(eventCode, param1, param2);
	}
}

MusicPlayer* MusicPlayer::Load(const std::wstring& path) {
	auto isExist = musics.find(path);

	if (isExist == musics.end()) {
		Music* iter = new Music();

		musics.insert(std::pair<const std::wstring, Music*>(path, iter));

		currentMusic = iter;

		hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void**)&iter->pGraph);
		hr = iter->pGraph->QueryInterface(IID_IMediaControl, (void**)&iter->pControl);
		hr = iter->pGraph->QueryInterface(IID_IMediaPosition, (void**)&iter->pPosition);
		hr = iter->pGraph->QueryInterface(IID_IMediaEventEx, (void**)&iter->pEventEx);
		hr = iter->pGraph->QueryInterface(IID_IBasicAudio, (void**)&iter->pBasicAudio);

		hr = currentMusic->pGraph->RenderFile(path.c_str(), NULL);
	}
	else {
		currentMusic = (*isExist).second;
	}

	return this;
}

MusicPlayer* MusicPlayer::Play(const std::wstring& path) {
	if (currentMusic != nullptr) {
		Stop();
	}

	Load(path);

	hr = currentMusic->pBasicAudio->put_Volume(volume);
	hr = currentMusic->pControl->Run();

	return this;
}

MusicPlayer* MusicPlayer::Pause() {
	hr = currentMusic->pControl->Pause();

	return this;
}

MusicPlayer* MusicPlayer::Stop() {
	hr = currentMusic->pControl->Stop();
	hr = currentMusic->pPosition->put_CurrentPosition(0);

	return this;
}

MusicPlayer* MusicPlayer::SetVolume(long volume) {
	this->volume = volume;

	for (auto iter : musics) {
		hr = iter.second->pBasicAudio->put_Volume(volume);
	}

	return this;
}

MusicPlayer* MusicPlayer::SetPosition(REFTIME position) {
	hr = currentMusic->pPosition->put_CurrentPosition(position);

	return this;
}

long MusicPlayer::GetVolume() {
	return volume;
}

REFTIME MusicPlayer::GetPosition() {
	REFTIME position;

	currentMusic->pPosition->get_CurrentPosition(&position);

	return position;
}

GameManager::GameManager() {
	dataManager = new DataManager();
	musicManager = new MusicPlayer();
}

GameManager::~GameManager() {
	SafeDelete(dataManager);
	SafeDelete(musicManager);
}

void GameManager::Update() {
	musicManager->Update();
}