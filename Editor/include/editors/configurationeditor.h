#pragma once
#include <QWidget>
#include <external/pugixml.hpp>
#include <toplevelmanager.h>

namespace Ui {
  class ConfigurationEditor;
}

class ConfigurationEditor : public QWidget
{
  Q_OBJECT

public:
  explicit ConfigurationEditor(TopLevelManager* tlm, pugi::xml_node* conf_node, QWidget *parent = nullptr);
  ~ConfigurationEditor();

public slots:
  void save_configuration();

private:
  Ui::ConfigurationEditor *ui;
  pugi::xml_node* held_node;
  TopLevelManager* tlm;
};

