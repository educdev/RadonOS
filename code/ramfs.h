#include <murmur/murmur.h>
#include <stdint.h>
#include <sys/types.h>
#define FNV_OFFSET_BASIS 2166136261U
#define FNV_PRIME 16777619U

typedef struct file {
  uint32_t valid;
  uint8_t *dados;
  char namebuffer[100];
  uint32_t size;
} file;
typedef struct folder {
  uint32_t valid;
  char *files[100];
  int p;

} folder;

typedef struct filee {
  char namebuffer[100];

} filee;
typedef struct folderr {
  char namebuffer[100];

} folderr;
folderr folders[100];
filee files[100];
int pato = 0;
int pato2 = 0;
size_t lenstr(const char *text) {
  size_t a = 0;
  while (text[a] != '\0') {
    a++;
  }
  return a;
}
static void cpstr(char *destino, const char *origem) {
  int i = 0;
  while (origem[i] != '\0') {
    destino[i] = origem[i];
    i++;
  }
  destino[i] = '\0';
}
int CreateFile(uint8_t *file, const char *name) {
  uint32_t hash = FNV_OFFSET_BASIS;
  for (int i = 0; name[i] != '\0'; i++) {
    hash ^= name[i];
    hash *= FNV_PRIME;
    hash &= 0xFFFFFFFFU;
  }
  hash %= 8388608U;
  hash += 0x10000;
  struct file *filee = (struct file *)(uintptr_t)hash;
  if (filee->valid == 0xBA5EBA11) {
    return 0;
  }
  filee->valid = 0xBA5EBA11;
  filee->dados = file;
  filee->size = lenstr((char *)file);
  cpstr(filee->namebuffer, name);
  struct filee filo;
  cpstr(filo.namebuffer, name);
  cpstr(files[pato++].namebuffer, filo.namebuffer);

  return 1;
}
int MKDIR(const char *name) {
  uint32_t hash = FNV_OFFSET_BASIS;
  for (int i = 0; name[i] != '\0'; i++) {
    hash ^= name[i];
    hash *= FNV_PRIME;
    hash &= 0xFFFFFFFFU;
  }
  hash %= 8388608U;
  hash += 0x10000;
  struct folder *folderr = (struct folder *)(uintptr_t)hash;
  if (folderr->valid == 0x6A2746A2) {
    return 0;
  }
  for (int i = 0; i < 100; i++) {
    folderr->files[i] = NULL;
  }
  folderr->p = 0;
  folderr->valid = 0x6A2746A2;
  return 1;
}
struct file *ReadFile(const char *name) {
  uint32_t hash = FNV_OFFSET_BASIS;
  for (int i = 0; name[i] != '\0'; i++) {
    hash ^= name[i];
    hash *= FNV_PRIME;
    hash &= 0xFFFFFFFFU;
  }
  hash %= 8388608U;
  hash += 0x10000;
  struct file *filee = (struct file *)(uintptr_t)hash;
  if (filee->valid != 0xBA5EBA11) {
    return NULL;
  } else {
    return filee;
  }
}
char **LISTFolderFILES(const char *name) {
  uint32_t hash = FNV_OFFSET_BASIS;
  for (int i = 0; name[i] != '\0'; i++) {
    hash ^= name[i];
    hash *= FNV_PRIME;
    hash &= 0xFFFFFFFFU;
  }
  hash %= 8388608U;
  hash += 0x10000;
  struct folder *folderr = (struct folder *)(uintptr_t)hash;
  if (folderr->valid != 0x6A2746A2) {
    return NULL;
  }
  return folderr->files;
}
int mkfileinfolder(const char *name, const char *fname, const char *dados) {
  uint32_t hash = FNV_OFFSET_BASIS;
  for (int i = 0; fname[i] != '\0'; i++) {
    hash ^= fname[i];
    hash *= FNV_PRIME;
    hash &= 0xFFFFFFFFU;
  }
  hash %= 8388608U;
  hash += 0x10000;
  struct folder *folderr = (struct folder *)(uintptr_t)hash;
  if (folderr->valid != 0x6A2746A2) {
    return 0;
  }
  char filename[1000];
  cpstr(filename, fname);
  cpstr(filename + lenstr(fname), name);
  uint32_t hashh = FNV_OFFSET_BASIS;
  for (int i = 0; filename[i] != '\0'; i++) {
    hashh ^= filename[i];
    hashh *= FNV_PRIME;
    hashh &= 0xFFFFFFFFU;
  }
  hashh %= 8388608U;
  hashh += 0x10000;
  struct file *filee = (struct file *)(uintptr_t)hashh;
  if (filee->valid != 0xBA5EBA11) {
    filee->valid = 0xBA5EBA11;
    filee->dados = (uint8_t *)dados;
    filee->size = lenstr((char *)dados);
    cpstr(filee->namebuffer, name);
  }

  folderr->files[folderr->p++] = filee->namebuffer;
  return 1;
}
struct file *ReadFolderFile(const char *name, const char *fname) {
  char filename[1000];
  cpstr(filename, fname);
  cpstr(filename + lenstr(fname), name);
  uint32_t hash = FNV_OFFSET_BASIS;
  for (int i = 0; filename[i] != '\0'; i++) {
    hash ^= filename[i];
    hash *= FNV_PRIME;
    hash &= 0xFFFFFFFFU;
  }
  hash %= 8388608U;
  hash += 0x10000;
  struct file *filee = (struct file *)(uintptr_t)hash;
  if (filee->valid != 0xBA5EBA11) {
    return NULL;
  } else {
    return filee;
  }
}
int EditFile(uint8_t *file, const char *name) {
  uint32_t hash = FNV_OFFSET_BASIS;
  for (int i = 0; name[i] != '\0'; i++) {
    hash ^= name[i];
    hash *= FNV_PRIME;
    hash &= 0xFFFFFFFFU;
  }
  hash %= 8388608U;
  hash += 0x10000;
  struct file *filee = (struct file *)(uintptr_t)hash;
  if (filee->valid != 0xBA5EBA11) {
    return 0;
  }
  filee->dados = file;
  filee->size = lenstr((char *)file);

  return 1;
}
