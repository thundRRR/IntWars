#include "RAFManager.h"
#include "tinydir.h"

using namespace std;

RAFManager* RAFManager::instance = 0;

bool RAFManager::init(const string& rootDirectory) {
   tinydir_dir dir;

   if(tinydir_open_sorted(&dir, rootDirectory.c_str()) == -1) {
      return false;
   }

   for (int i = 0; i < dir.n_files; i++)
   {
      tinydir_file file;
      tinydir_readfile_n(&dir, &file, i);

      if (!file.is_dir || strcmp(file.name, ".") == 0 || strcmp(file.name, "..") == 0) {
         continue;
      }
      
      printf("%s\n", file.name);
      
      string rafPath = rootDirectory + '/' + file.name + "/Archive_2.raf";
      RAFFile* raf = new RAFFile(rafPath);
      
      files.push_back(raf);
   }
   
   printf("Loaded %d RAF files\n", files.size());

   tinydir_close(&dir);
   
   return true;
}

bool RAFManager::readFile(const std::string& path, vector<unsigned char>& toFill) {
   for(vector<RAFFile*>::iterator it = files.begin(); it != files.end(); ++it) {
      RAFFile* f = *it;
      if(f->readFile(path, toFill)) {
         return true;
      }
   }
   
   return false;
}