#pragma once
#include "Function.h"
#include <json.hpp>
#include <map>
#include <string>
#include <variant>

class GlobalVariables {
private:
	//using
	using json = nlohmann::json;

public:
	static GlobalVariables* GetInstance();

private:
	GlobalVariables() = default;
	~GlobalVariables() = default;
	GlobalVariables(const GlobalVariables&) = delete;
	const GlobalVariables& operator=(const GlobalVariables&) = delete;

public:
	void Update();

public:
	void CreateGroup(const std::string& groupName);
	void SaveFile(const std::string& groupName);
	void LoadFiles();
	void LoadFile(const std::string& groupName);

	void SetValue(const std::string& groupName, const std::string& key, int32_t value);
	void SetValue(const std::string& groupName, const std::string& key, float value);
	void SetValue(const std::string& groupName, const std::string& key, const Vector3& value);

private:
	// 項目
	struct Item {
		// 項目の値
		std::variant<int32_t, float, Vector3> value;
	};
	// グループ
	struct Group {
		std::map<std::string, Item> items;
	};

	// 全データ
	std::map<std::string, Group> datas_;
	//グローバル変数の保存先ファイルパス
	const std::string kDirectryPath = "Resources/GlobalVariables/";

};