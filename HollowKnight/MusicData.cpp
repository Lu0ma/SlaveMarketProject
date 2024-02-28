#include "MusicData.h"
#include"MusicManager.h"
MusicData::MusicData(const string& _path):IManagable(_path)
{
}

void MusicData::Register()
{
	MusicManager::GetInstance().Add(id, this);
}
