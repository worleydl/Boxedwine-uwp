#ifndef __BOXED_TRANSLATION_H__
#define __BOXED_TRANSLATION_H__

enum {
INSTALLDLG_CONTAINER_HELP=1,
INSTALLDLG_CONTAINER_NAME_HELP,
INSTALLDLG_TYPE_SETUP_HELP,
INSTALLDLG_TYPE_DIR_HELP,
INSTALLDLG_TYPE_MOUNT_HELP,
INSTALLDLG_WINE_VERSION_HELP,
INSTALLDLG_RUN_WINE_CONFIG_HELP,
INSTALLDLG_INSTALL_TYPE_HELP,
INSTALLDLG_INSTALL_TYPE_LABEL,
INSTALLDLG_CONTAINER_LABEL,
INSTALLDLG_CONTAINER_NAME_LABEL,
INSTALLDLG_CONTAINER_WINE_VERSION_LABEL,
INSTALLDLG_CONTAINER_RUN_WINE_CONFIG_LABEL,
INSTALLDLG_SETUP_FILE_LOCATION_LABEL,
INSTALLDLG_DIRECTORY_LABEL,
INSTALLDLG_TITLE,
INSTALLDLG_OPEN_SETUP_FILE_TITLE,
INSTALLDLG_OPEN_FOLDER_TITLE,
INSTALLDLG_ERROR_SETUP_FILE_MISSING,
INSTALLDLG_ERROR_SETUP_FILE_NOT_FOUND,
INSTALLDLG_ERROR_DIR_MISSING,
INSTALLDLG_ERROR_DIR_NOT_FOUND,
INSTALLDLG_ERROR_CONTAINER_NAME_MISSING,
INSTALLDLG_ERROR_FAILED_TO_CREATE_CONTAINER_DIR,
INSTALLDLG_ERROR_CONTAINER_ALREADY_EXISTS,
GENERIC_BROWSE_BUTTON,
GENERIC_DLG_OK,
GENERIC_DLG_CANCEL,
GENERIC_DLG_ERROR_TITLE,
MAIN_BUTTON_INSTALL,
MAIN_BUTTON_CONTAINERS,
MAIN_BUTTON_SETTINGS,
MAIN_BUTTON_HELP,
MAIN_BUTTON_APPS,
};

const char* getTranslation(int msg, bool useDefaultIfMissing=true);
std::string getTranslationWithFormat(int msg, bool useDefaultIfMissing, const std::vector<std::string>& replacements);
std::string getTranslationWithFormat(int msg, bool useDefaultIfMissing, const std::string& string1);

#endif