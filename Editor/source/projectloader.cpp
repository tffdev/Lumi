#include "include/projectloader.h"
#include <editortabs.h>
#include <assettree.h>
#include <QFileDialog>


void ProjectLoader::open_load_dialog(TopLevelManager* toplevelmanager) {
  // Ask the user to load a .lumi file
  QString q_filename = QFileDialog::getOpenFileName(nullptr, "Load Lumi Project", QString(), "Lumi File (*.lumi)");

  if(q_filename.compare("") == 0)
    return toplevelmanager->show_statusbar_message("Project load cancelled.");

  // push filename to projectdata utility function
  if(!toplevelmanager->get_database()->load_project_file_into_database(q_filename))
    toplevelmanager->show_error_message("Error loading project " + q_filename);

  toplevelmanager->get_tab_widget()->close_all_tabs();

  toplevelmanager->get_tree_widget()->load_database_into_tree(toplevelmanager->get_database());
}
