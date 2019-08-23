#pragma once
#include <QWidget>

namespace Ui {
  class ConfigurationEditor;
}

class ConfigurationEditor : public QWidget
{
  Q_OBJECT

public:
  explicit ConfigurationEditor(QWidget *parent = nullptr);
  ~ConfigurationEditor();

private:
  Ui::ConfigurationEditor *ui;
};

