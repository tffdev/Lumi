/**

 * Lumi Game Creator - version 0.0.1
 * --------------------------------------------------------
 * Report bugs and download new versions at https://github.com/tfcat/lumigamecreator
 * Copyright (C) 2019-2019, by Daniel Brier (danbrierly@gmail.com)
 *
 *
 * This library is distributed under the MIT License.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */
#include <windows.h>
#include <iostream>
#include <vector>
#include <QFile>
#include <QStandardPaths>
#include <QFileInfo>
#include <QDir>
#include <engine.h>
#undef main

void engine_main() {
  try {
    LumiEngine game;
    game.run();
  } catch (const std::exception& e) {
    printf("Error in run_game: %s\n", e.what());
  }
}

int main(int argc, char* argv[]) {
  printf("argc %i, argv %s", argc, argv[1]);
  if(argc > 1) {
    // custom filesystem path
    FileSystem::set_data_path(argv[1]);
  } else {
    // Standard path (in release, will replace this with current_directory/data)
    FileSystem::set_data_path("../data/");
  }

  // Load DLLs
  QString destination = QString(
        QStandardPaths::writableLocation(QStandardPaths::AppDataLocation))
      + "/LumiGameEngine";

  if(!QDir(destination).exists())
    QDir().mkdir(destination);

  std::vector<QString> files = {
    ":/r/dlls/lua53.dll",
    ":/r/dlls/libgcc_s_seh-1.dll",
    ":/r/dlls/libjpeg-9.dll",
    ":/r/dlls/libogg-0.dll",
    ":/r/dlls/libpng16-16.dll",
    ":/r/dlls/libvorbis-0.dll",
    ":/r/dlls/libvorbisfile-3.dll",
    ":/r/dlls/libwinpthread-1.dll",
    ":/r/dlls/zlib1.dll",
  };

  for(QString dll_resource_path : files) {
    QFile file(dll_resource_path);
    QFileInfo fileInfo(file.fileName());
    QString truncated_filename(fileInfo.fileName());

    if(!QFile::exists(destination + "/" + truncated_filename)) {
      if(!file.copy(destination + "/" + truncated_filename)) {
        printf("Can't copy dll [%s] to temporary directory: %s\n",
               (destination + "/" + truncated_filename).toUtf8().data(),
               file.errorString().toUtf8().data());
        throw;
      } else {
        printf("Copied dll file [%s] to temp directory.\n",
              (destination + "/" + truncated_filename).toUtf8().data());
      }
    }
  }

  SetDllDirectoryA(destination.toUtf8().constData());
  engine_main();
}
