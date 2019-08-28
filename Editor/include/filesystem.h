#pragma once
#include <QString>

class FileSystem
{
public:
  FileSystem();
  static bool write_to_file(QString data, QString path);
  static void copy_directory_recursively(QString src, QString dst);
};

