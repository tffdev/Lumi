#include "configurationeditor.h"
#include "ui_configurationeditor.h"

ConfigurationEditor::ConfigurationEditor(TopLevelManager* tlm, pugi::xml_node* conf_node, QWidget *parent) :
  QWidget(parent),
  ui(new Ui::ConfigurationEditor),
  held_node(conf_node),
  tlm(tlm) {
  ui->setupUi(this);

  // assign slots
  connect(ui->buttonSave, &QPushButton::pressed, this, &ConfigurationEditor::save_configuration);

  if(!held_node->empty()) {
    ui->entryColor->setText(held_node->attribute("drawcolor").as_string());
    ui->entryScale->setValue(held_node->attribute("scale").as_double());
    ui->entryWidth->setValue(held_node->attribute("width").as_int());
    ui->entryHeight->setValue(held_node->attribute("height").as_int());
    ui->entryDefaultTitle->setText(held_node->attribute("title").as_string());
  }
}

ConfigurationEditor::~ConfigurationEditor() {
  delete ui;
}

void ConfigurationEditor::save_configuration() {
  held_node->attribute("drawcolor").set_value(ui->entryColor->text().toUtf8().data());
  held_node->attribute("scale").set_value(ui->entryScale->value());
  held_node->attribute("width").set_value(ui->entryWidth->value());
  held_node->attribute("height").set_value(ui->entryHeight->value());
  held_node->attribute("title").set_value(ui->entryDefaultTitle->text().toUtf8().data());
  tlm->set_statusbar_message("Saved project configuration!");
}
