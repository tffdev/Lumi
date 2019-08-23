#include "objecteditor.h"
#include "ui_objecteditor.h"

ObjectEditor::ObjectEditor(AssetEntry* asset, QWidget *parent) :
  QWidget(parent), ui(new Ui::ObjectEditor), held_asset(asset) {
  ui->setupUi(this);

  // parse asset into respective places
  ui->objectNameEdit->setText(asset->node.attribute("name").as_string());
  ui->objectCodeEditor->document()->setPlainText(asset->node.text().as_string());
  ui->objectPersistent->setCheckState((asset->node.attribute("persistent").as_int() == 1) ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);

}

ObjectEditor::~ObjectEditor() {
  delete ui;
}

