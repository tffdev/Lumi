#pragma once
#include <QWidget>

namespace Ui {
  class ObjectEditor;
}

class ObjectEditor : public QWidget
{
  Q_OBJECT

public:
  explicit ObjectEditor(QWidget *parent = nullptr);
  ~ObjectEditor();

private:
  Ui::ObjectEditor *ui;
};
