#include "include/instanceasset.h"

InstanceAsset::InstanceAsset(int reg_id) : registry_id(reg_id){}

int InstanceAsset::get_id() {
  return registry_id;
}
