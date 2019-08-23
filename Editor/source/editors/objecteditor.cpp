#include "objecteditor.h"
#include "ui_objecteditor.h"
#include <projectmanager.h>

ObjectEditor::ObjectEditor(AssetEntry* asset, QWidget *parent) :
  QWidget(parent), ui(new Ui::ObjectEditor), held_asset(asset) {
  ui->setupUi(this);

  // assign slots
  connect(ui->objectSave, SIGNAL(pressed()), this, SLOT(save_asset()));

  // parse asset into respective places
  ui->objectNameEdit->setText(asset->node.attribute("name").as_string());
  ui->objectPersistent->setCheckState((asset->node.attribute("persistent").as_int() == 1) ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
  ui->objectCodeEditor->document()->setPlainText(asset->node.text().as_string());
}

void ObjectEditor::save_asset() {
  printf("saving asset %s\n", held_asset->name.c_str());

  // if name has been changed
  std::string requested_name = ui->objectNameEdit->text().toUtf8().data();
  if(requested_name.compare(held_asset->name) != 0) {
    // make sure name isn't taken
    if(ProjectData::fetch().asset_name_exists(requested_name)) {
      ProjectManager::fetch().show_error_message("Asset with name " + QString(requested_name.c_str()) + " already exists.");
      return;
    }

    // rename
    ProjectData::fetch().rename_asset(held_asset->name, requested_name);

    held_asset->name = requested_name;
    held_asset->node.attribute("name").set_value(requested_name.c_str());
    // change tab and tree name
    ProjectManager::fetch().get_ui()->editorTabs->rename_tab(held_asset->id, held_asset->name);
    ProjectManager::fetch().get_ui()->assetTree->rename_tree_item(held_asset->id, held_asset->name);
  }

  // change held node data
  held_asset->node.attribute("persistent").set_value((ui->objectPersistent->checkState() == Qt::CheckState::Checked) ? "1" : "0");
  held_asset->node.text().set(ui->objectCodeEditor->document()->toPlainText().toUtf8().data());
}

ObjectEditor::~ObjectEditor() {
  delete ui;
}

