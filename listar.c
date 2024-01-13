#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#include <windows.h>
#endif

typedef struct extension_type
{
    char extension[7];
    char name_type[0xf];
} extension_type;

extension_type extensiones[] = {
    {.extension = "txt", .name_type = "TEXT"},
    {.extension = "exe", .name_type = "EXE"},
    {.extension = "pdf", .name_type = "PDF"},
    {.extension = "dll", .name_type = "DLL"},
    {.extension = "c", .name_type = "C"},
    {.extension = "py", .name_type = "PY"},
    {.extension = "h", .name_type = "H"},
    {.extension = "rar", .name_type = "RAR"}};

void lista_directorio(const char *nombre, unsigned short tab_level);

int main(int argc, char const *argv[])
{
#ifdef _WIN32
    char str[100];
#else
    char str[MAX_PATH];
#endif

    printf("RUTA A LISTAR: ");
    scanf("%99s", str);

    printf("RUTA SERA LISTADA: %s\n", str);
    lista_directorio(str, 0);

#ifdef _WIN32
    system("pause");
#endif

    return 0;
}

#ifdef _WIN32
void lista_directorio(const char *nombre, unsigned short tab_level)
{
    char search_path[MAX_PATH];
    snprintf(search_path, sizeof(search_path), "%s\\*", nombre);

    WIN32_FIND_DATA findFileData;
    HANDLE hFind = FindFirstFile(search_path, &findFileData);

    if (hFind == INVALID_HANDLE_VALUE)
    {
        fprintf(stderr, "No se puede abrir el directorio %s.\n", nombre);
        return;
    }

    do
    {
        if (strcmp(findFileData.cFileName, ".") == 0 || strcmp(findFileData.cFileName, "..") == 0)
            continue;

        size_t size_path = snprintf(NULL, 0, "%s\\%s", nombre, findFileData.cFileName) + 1;
        char *path = (char *)calloc(size_path + 1, sizeof(char));
        snprintf(path, size_path, "%s\\%s", nombre, findFileData.cFileName);

        char *tabs = (char *)calloc(tab_level + 1, sizeof(char));
        memset(tabs, '\t', tab_level);

        if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            printf("%s|-%s- %s\n", tabs, "DIR", findFileData.cFileName);
            lista_directorio(path, tab_level + 1);
        }
        else
        {
            char *ptr = strchr(findFileData.cFileName, '.');
            if (ptr != NULL)
            {
                ptr += 1;

                int extension_found = 0;
                for (size_t i = 0; i < sizeof(extensiones) / sizeof(extension_type); i++)
                {
                    if (strcmp(extensiones[i].extension, ptr) == 0)
                    {
                        printf("%s|-%s-- %s\n", tabs, extensiones[i].name_type, findFileData.cFileName);
                        extension_found = 1;
                        break;
                    }
                }

                if (!extension_found)
                {
                    printf("%s|-%s- %s\n", tabs, "EXTENSION NF", findFileData.cFileName);
                }
            }
        }

        free(path);
        free(tabs);

    } while (FindNextFile(hFind, &findFileData) != 0);

    FindClose(hFind);
}
#else

void lista_directorio(const char *nombre, unsigned short tab_level)
{
    DIR *folder = opendir(nombre);

    if (folder == NULL)
    {
        fprintf(stderr, "No se puede abrir el directorio %s.\n", nombre);
        return;
    }

    struct dirent *directorio = readdir(folder);

    while (directorio != NULL)
    {
        if (strcmp(directorio->d_name, ".") != 0 && strcmp(directorio->d_name, "..") != 0)
        {
            size_t size_path = snprintf(NULL, 0, "%s/%s", nombre, directorio->d_name) + 1;
            char *path = (char *)malloc(size_path);
            snprintf(path, size_path, "%s/%s", nombre, directorio->d_name);

            char *tabs = (char *)calloc(tab_level + 1, sizeof(char));
            memset(tabs, '\t', tab_level);

            if (directorio->d_type == DT_DIR)
            {
                printf("%s|-%s- %s\n", tabs, "DIR", directorio->d_name);
                lista_directorio(path, tab_level + 1);
            }
            else
            {
                char *ptr = strchr(directorio->d_name, '.');
                if (ptr != NULL)
                {
                    ptr += 1;

                    int extension_found = 0;
                    for (size_t i = 0; i < sizeof(extensiones) / sizeof(extension_type); i++)
                    {
                        if (strcmp(extensiones[i].extension, ptr) == 0)
                        {
                            printf("%s|-%s- %s\n", tabs, extensiones[i].name_type, directorio->d_name);
                            extension_found = 1;
                            break;
                        }
                    }

                    if (!extension_found)
                    {
                        printf("%s|-%s- %s\n", tabs, "EXTENSION NOT FOUND", directorio->d_name);
                    }
                }
            }

            free(path);
            free(tabs);
        }

        directorio = readdir(folder);
    }

    closedir(folder);
}
#endif