#include "include/filesystem.h"
#include <QFile>
#include <QDir>

FileSystem::FileSystem() {}

bool FileSystem::write_to_file(QString data, QString path) {
  QFile file(path);
  file.open(QIODevice::ReadWrite);
  file.resize(0);
  if(file.write(data.toUtf8().data()) == -1) return false;
  file.close();
  return true;
}

void FileSystem::copy_directory_recursively(QString src, QString dst) {
    QDir dir(src);
    if (! dir.exists())
        return;

    foreach (QString d, dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot)) {
        QString dst_path = dst + QDir::separator() + d;
        dir.mkpath(dst_path);
        copy_directory_recursively(src+ QDir::separator() + d, dst_path);
    }

    foreach (QString f, dir.entryList(QDir::Files)) {
        QFile::copy(src + QDir::separator() + f, dst + QDir::separator() + f);
    }
}
