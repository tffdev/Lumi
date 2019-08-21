#pragma once
#include <unordered_map>
#include <type_traits>
#include <vector>

template <typename T>
class Database
{
public:
  Database() {}
  ~Database() {}

  void insert_asset(std::string name, T asset) {
    asset_map.insert(std::pair<std::string, T>(name, asset));
  }

  bool asset_exists(std::string name) {
    return asset_map.count(name) > 0;
  }

  T get_asset(std::string name) {
    return asset_map.at(name);
  }

  std::vector<T> get_all_assets() {
    std::vector<T> vector;
    for(std::pair<std::string, T> kv : asset_map) {
      vector.push_back(kv.second);
    }
    return vector;
  }

  void clear() {
    asset_map.clear();
  }

private:
  std::unordered_map<std::string, T> asset_map;
};
