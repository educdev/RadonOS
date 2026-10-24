#include "fonte.h"
#include "ramfs.h"
#include <murmur/murmur.h>

#include <sys/types.h>

unsigned char tempo = 0;
int color = 0;
char textbuffer[10000];
char temp[1000];
char tempp[1000];

static char *splitvalue[10];

void drawtext(unsigned char *framebuffer, char r, char g, char b, char *texto,
              int cursor, unsigned short pitch, unsigned char bpp) {
  for (int i = 0; i < lenstr(texto); i++) {
    for (int yy = 0; yy < 16; yy++) {
      for (int xx = 0; xx < 16; xx++) {

        if (font16x16_pixel(texto[i], (int)xx, (int)yy) == 1) {
          unsigned int posicao_pixel =
              (((int)yy + (cursor * 16)) * (int)pitch) +
              (((int)xx + (i * 16)) * bpp);
          framebuffer[posicao_pixel] = b;
          framebuffer[posicao_pixel + 1] = g;
          framebuffer[posicao_pixel + 2] = r;
        }
      }
    }
  }
}
static int startswith(char *text, char *text2, int cn) {
  for (int i = 0; i < cn; i++) {
    if (text[i] != text2[i]) {
      return 0;
    }
  }
  return 1;
}

static char *slice(char *text, int cn) {
  cpstr(tempp, text);
  tempp[cn - 1] = '\0';
  return (tempp + cn);
}

static char **split(char *texto, char s) {
  char **resultado = splitvalue;
  char *temp;
  cpstr(temp, texto);
  char *start;
  char j = 0;
  resultado[j++] = temp;
  for (int i = 0; temp[i] != '\0'; i++) {
    if (temp[i] == s) {
      temp[i] = '\0';
      resultado[j++] = &temp[i + 1];
    }
  }
  return resultado;
}
void frect(unsigned char *framebuffer, unsigned short pitch, int sx, int sy,
           int ex, int ey, char r, char g, char b, unsigned char bpp) {
  for (int y = sy; y < ey; y++) {
    for (int x = sx; x < ex; x++) {
      unsigned int pospixel = ((int)y * (int)pitch) + ((int)x * (int)bpp);
      framebuffer[pospixel] = (int)b;
      framebuffer[pospixel + 1] = (int)g;
      framebuffer[pospixel + 2] = (int)r;
    }
  }
}

int porta(unsigned short port) {
  register char abu asm("al");
  asm volatile("inb %1, %0" : "=a"(abu) : "Nd"(port));

  return abu;
}
void writesize(char *str, int width, int height) {

  cpstr(str, "*       * ");
  int i = lenstr(str);
  if (width > 1000 && height > 1000) {
    str[i++] = (width / 1000) + '0';
    str[i++] = ((width / 100) % 10) + '0';
    str[i++] = ((width / 10) % 10) + '0';
    str[i++] = (width % 10) + '0';
    // ---------
    str[i++] = 'x';
    // ---------
    str[i++] = (height / 1000) + '0';
    str[i++] = ((height / 100) % 10) + '0';
    str[i++] = ((height / 10) % 10) + '0';
    str[i++] = (height % 10) + '0';
  }
  if (width > 1000 && height < 1000) {
    str[i++] = (width / 1000) + '0';
    str[i++] = ((width / 100) % 10) + '0';
    str[i++] = ((width / 10) % 10) + '0';
    str[i++] = (width % 10) + '0';
    // ---------
    str[i++] = 'x';
    // ---------
    str[i++] = (height / 100) + '0';
    str[i++] = ((height / 10) % 10) + '0';
    str[i++] = (height % 10) + '0';
  }
  if (width < 1000 && height < 1000) {
    str[i++] = (width / 100) + '0';
    str[i++] = ((width / 10) % 10) + '0';
    str[i++] = (width % 10) + '0';
    // ---------
    str[i++] = 'x';
    // ---------
    str[i++] = (height / 100) + '0';
    str[i++] = ((height / 10) % 10) + '0';
    str[i++] = (height % 10) + '0';
  }
}
char teclas(int scancode) {
  static unsigned int shift = 0;
  if (scancode == 0x2A) {
    shift = 1;
    return 0;
  }
  if (scancode == 0xAA) {
    shift = 0;
    return 0;
  }
  if (shift == 1) {
    switch (scancode) {
    case 0x1E:
      return 'A';
    case 0x30:
      return 'B';
    case 0x2E:
      return 'C';
    case 0x20:
      return 'D';
    case 0x12:
      return 'E';
    case 0x21:
      return 'F';
    case 0x22:
      return 'G';
    case 0x23:
      return 'H';
    case 0x17:
      return 'I';
    case 0x24:
      return 'J';
    case 0x25:
      return 'K';
    case 0x26:
      return 'L';
    case 0x32:
      return 'M';
    case 0x31:
      return 'N';
    case 0x18:
      return 'O';
    case 0x19:
      return 'P';
    case 0x10:
      return 'Q';
    case 0x13:
      return 'R';
    case 0x1F:
      return 'S';
    case 0x14:
      return 'T';
    case 0x16:
      return 'U';
    case 0x2F:
      return 'V';
    case 0x11:
      return 'W';
    case 0x2D:
      return 'X';
    case 0x15:
      return 'Y';
    case 0x2C:
      return 'Z';

    case 0x02:
      return '!';
    case 0x03:
      return '@';
    case 0x04:
      return '#';
    case 0x05:
      return '$';
    case 0x06:
      return '%';
    case 0x07:
      return '^';
    case 0x08:
      return '&';
    case 0x09:
      return '*';
    case 0x0A:
      return '(';
    case 0x0B:
      return ')';

    case 0x0C:
      return '_';
    case 0x27:
      return ':';
    case 0x28:
      return '"';
    case 0x33:
      return '<';
    case 0x35:
      return '?';

    case 0x0E:
      return '\b';
    case 0x1C:
      return 0x1C;
    case 0x39:
      return ' ';
    case 0x4A:
      return '-';

    default:
      return 0;
    }
  } else if (shift == 0) {

    switch (scancode) {

    case 0x0E:
      return '\b';

    case 0x1C:
      return 0x1C;

    case 0x39:
      return ' ';
    case 0x3A:
      return 0x3A;

    case 0x1E:
      return 'a';
    case 0x30:
      return 'b';
    case 0x2E:
      return 'c';
    case 0x20:
      return 'd';
    case 0x12:
      return 'e';
    case 0x21:
      return 'f';
    case 0x22:
      return 'g';
    case 0x23:
      return 'h';
    case 0x17:
      return 'i';
    case 0x24:
      return 'j';
    case 0x25:
      return 'k';
    case 0x26:
      return 'l';
    case 0x32:
      return 'm';
    case 0x31:
      return 'n';
    case 0x18:
      return 'o';
    case 0x19:
      return 'p';
    case 0x10:
      return 'q';
    case 0x13:
      return 'r';
    case 0x1F:
      return 's';
    case 0x14:
      return 't';
    case 0x16:
      return 'u';
    case 0x2F:
      return 'v';
    case 0x11:
      return 'w';
    case 0x2D:
      return 'x';
    case 0x15:
      return 'y';
    case 0x2C:
      return 'z';
    case 0x02:
      return '1';
    case 0x03:
      return '2';
    case 0x04:
      return '3';
    case 0x05:
      return '4';
    case 0x06:
      return '5';
    case 0x07:
      return '6';
    case 0x08:
      return '7';
    case 0x09:
      return '8';
    case 0x0A:
      return '9';
    case 0x0B:
      return '0';

    case 0x0C:
      return '-';
    case 0x27:
      return ';';
    case 0x28:
      return '\'';
    case 0x33:
      return ',';
    case 0x35:
      return '/';
    case 0x4A:
      return '-';
    case 0x34:
      return '.';

    default:
      return 0;
    }
  }
}
void reset() {
  __asm__ __volatile__("mov $0x0CF9, %%dx \n\t"
                       "mov $0x0E, %%al \n\t"
                       "outb %%al, (%%dx)"
                       :
                       :
                       : "ax", "dx");
}
int CMPSTR(const char *string, const char *string1) {
  int i = 0;
  while (string[i] == string1[i]) {
    if (string[i] == '\0') {
      return 1;
    }
    i++;
  }
  return 0;
}

void main(void) {

  struct murmur_registry_entry *vbe = murmur_get_registry_key("VBE_INFO");
  int i = 3;
  if (vbe == NULL || vbe->size < 256) {
    while (1)
      ;
  }

  unsigned char *info = vbe->value;

  unsigned short width = info[0x12] | (info[0x13] << 8);
  unsigned short height = info[0x14] | (info[0x15] << 8);

  unsigned int address =
      info[0x28] | (info[0x29] << 8) | (info[0x2A] << 16) | (info[0x2B] << 24);

  unsigned char *framebuffer = (unsigned char *)(uintptr_t)address;
  unsigned char bpp = info[0x19];
  unsigned char bytes_per_pixel = bpp / 8;
  unsigned short pitch = width * bytes_per_pixel;

  drawtext(framebuffer, (int)44, (int)158, (int)93, "RadonOS 0.6", 0, pitch,
           bytes_per_pixel);
  drawtext(framebuffer, (int)0, (int)255, (int)255, "VESA GRAPHICS", 1, pitch,
           bytes_per_pixel);
  drawtext(framebuffer, (int)255, (int)255, (int)0, "Protected Mode", 2, pitch,
           bytes_per_pixel);

  int idx = 0;
  char capslock = 0;
  char promptbuffer[10000];
  cpstr(promptbuffer, "radonos> ");

  drawtext(framebuffer, 255, 255, 255, promptbuffer, i, pitch, bytes_per_pixel);

  while (1) { // terminal loop(bcvy have terminal cancer)

    while ((porta(0x64) & 0x01) == 0) {
    }
    unsigned char scancode = porta(0x60);
    if ((scancode & 0x80) && scancode != 0xAA) {
      continue;
    }
    char tec = teclas(scancode);

    if (tec != 0) {
      if (tec == 0x3A) {
        if (capslock == 1) {
          capslock = 0;
        } else {
          capslock = 1;
        }
        continue;
      }
      if (tec == 0x1C) {
        if (i >= height / 16) {
          i = -1;
          frect(framebuffer, pitch, 0, 0, width, height, 0, 0, 0,
                bytes_per_pixel);
        }

        char **splited = split(textbuffer, ' ');
        textbuffer[idx] = '\0';
        if (CMPSTR(textbuffer, "reboot") == 1) {
          reset();
        } else if (startswith(textbuffer, "echo", 4) == 1) {
          i++;
          drawtext(framebuffer, 255, 255, 255, slice(textbuffer, 5), i++, pitch,
                   bytes_per_pixel);

        } else if (CMPSTR(textbuffer, "clear") == 1) {
          frect(framebuffer, pitch, 0, 0, width, height, 0, 0, 0,
                bytes_per_pixel);

          cpstr(promptbuffer, "radonos> ");
          i = 0;
          drawtext(framebuffer, 255, 255, 0, promptbuffer, i, pitch,
                   bytes_per_pixel);

        } else if (CMPSTR(textbuffer, "fetch") == 1) {
          i++;
          char string[100];
          writesize(string, width, height);
          drawtext(framebuffer, 100, 255, 255, "   ***    RadonOS 0.6", i++,
                   pitch, bytes_per_pixel);

          drawtext(framebuffer, 100, 255, 200, " *     *  VESA GRAPHICS", i++,
                   pitch, bytes_per_pixel);
          drawtext(framebuffer, 50, 255, 150, "*       * PROTECTED MODE", i++,
                   pitch, bytes_per_pixel);
          drawtext(framebuffer, 0, 220, 100, string, i++, pitch,
                   bytes_per_pixel);
          drawtext(framebuffer, 0, 180, 80, " *     * ", i++, pitch,
                   bytes_per_pixel);
          drawtext(framebuffer, 50, 150, 60, "   ***   ", i++, pitch,
                   bytes_per_pixel);

        } else if (CMPSTR(textbuffer, "help") == 1) {
          i++;
          drawtext(framebuffer, 255, 100, 50, "Commands:", i++, pitch,
                   bytes_per_pixel);
          drawtext(framebuffer, 255, 255, 150, "help: Mostra todos os comandos",
                   i++, pitch, bytes_per_pixel);
          drawtext(framebuffer, 255, 255, 100, "clear: Limpa a tela", i++,
                   pitch, bytes_per_pixel);
          drawtext(framebuffer, 255, 255, 0,
                   "fetch: Mostra informacoes do computador e a logo", i++,
                   pitch, bytes_per_pixel);
          drawtext(framebuffer, 255, 200, 0, "echo: Mostra um texto na tela",
                   i++, pitch, bytes_per_pixel);
          drawtext(framebuffer, 255, 100, 0, "reboot: Reinicia o computador",
                   i++, pitch, bytes_per_pixel);
          drawtext(framebuffer, 200, 0, 0, "mkfile: Cria um arquivo no ramfs",
                   i++, pitch, bytes_per_pixel);
          drawtext(framebuffer, 255, 0, 0, "readfile:  Le um arquivo no ramfs",
                   i++, pitch, bytes_per_pixel);
          drawtext(framebuffer, 255, 100, 0, "ls: Lista os arquivos", i++,
                   pitch, bytes_per_pixel);
          drawtext(framebuffer, 255, 150, 0, "mkdir: Cria uma pasta", i++,
                   pitch, bytes_per_pixel);
          drawtext(framebuffer, 255, 200, 0,
                   "readfolderfile: Le um arquivo de uma pasta", i++, pitch,
                   bytes_per_pixel);
          drawtext(framebuffer, 255, 255, 0,
                   "mkfindir: Cria um arquivo dentro de uma pasta", i++, pitch,
                   bytes_per_pixel);
          drawtext(framebuffer, 255, 200, 0,
                   "dir: Lista os arquivos de uma pasta(recebe nome da pasta)",
                   i++, pitch, bytes_per_pixel);

        } else if (startswith(textbuffer, "mkfile", 6)) {
          i++;
          if (CreateFile(slice(textbuffer,
                               2 + (lenstr("mkfile") + lenstr(splited[1]))),
                         splited[1]) == 0) {
            drawtext(framebuffer, 255, 0, 0, "Erro: Arquivo ja existe", i++,
                     pitch, bytes_per_pixel);
          } else {
            drawtext(framebuffer, 255, 255, 255, ReadFile(splited[1])->dados,
                     i++, pitch, bytes_per_pixel);
          }
        } else if (CMPSTR(textbuffer, "ls") == 1) {
          i++;
          int sixseven = 0;
          while (1) {
            if (files[sixseven].namebuffer[0] == '\0') {
              break;
            }
            drawtext(framebuffer, 255, 255, 255, files[sixseven].namebuffer,
                     i++, pitch, bytes_per_pixel);
            sixseven++;
          }
        } else if (CMPSTR(splited[0], "readfile") == 1) {
          i++;
          if (ReadFile(splited[1]) != NULL) {
            drawtext(framebuffer, 255, 255, 255, ReadFile(splited[1])->dados,
                     i++, pitch, bytes_per_pixel);
          } else {
            drawtext(framebuffer, 255, 0, 0, "Erro: Arquivo nao encontrado",
                     i++, pitch, bytes_per_pixel);
          }
        } else if (CMPSTR(splited[0], "readfolderfile")) {
          i++;
          if (ReadFolderFile(splited[1], splited[2]) != NULL) {
            drawtext(framebuffer, 255, 255, 255,
                     ReadFolderFile(splited[1], splited[2])->dados, i++, pitch,
                     bytes_per_pixel);
          } else {
            i++;
            drawtext(framebuffer, 255, 0, 0,
                     "Erro: Arquivo nao encontrado na pasta", i++, pitch,
                     bytes_per_pixel);
          }

        } else if (startswith(textbuffer, "mkfindir", 8)) {
          i++;
          if (mkfileinfolder(splited[1], splited[2],
                             slice(textbuffer, (lenstr(splited[1]) +
                                                lenstr(splited[2]) + 8) +
                                                   3)) == 1) {
            drawtext(framebuffer, 0, 255, 0, "Arquivo criado com sucesso", i++,
                     pitch, bytes_per_pixel);
          } else {
            drawtext(framebuffer, 255, 0, 0,
                     "Erro: Pasta nao existe,Arquivo ja existe ou ouve colisao",
                     i++, pitch, bytes_per_pixel);
          }
        } else if (startswith(textbuffer, "mkdir", 5)) {
          i++;
          if (MKDIR(splited[1]) == 1) {
            drawtext(framebuffer, 0, 255, 0, "Pasta criada com sucesso", i++,
                     pitch, bytes_per_pixel);
          } else {
            drawtext(framebuffer, 255, 0, 0,
                     "Erro: Pasta ja existe ou ouve colisao", i++, pitch,
                     bytes_per_pixel);
          }

        } else if (startswith(textbuffer, "dir", 3)) {
          i++;
          char **listed = LISTFolderFILES(splited[1]);
          if (listed != NULL) {
            for (int h = 0; h < 100; h++) {
              if (listed[h] == NULL) {
                break;
              }
              drawtext(framebuffer, 255, 255, 255, listed[h], i, pitch,
                       bytes_per_pixel);
              i++;
            }
          }

        } else {
          i++;
          drawtext(framebuffer, 255, 0, 0, "Erro: Comando nao encontrado", i++,
                   pitch, bytes_per_pixel);
        }

        for (int a = 0; a < idx; a++) {
          textbuffer[a] = 0;
        }
        idx = 0;
        cpstr(promptbuffer, "radonos> ");
        drawtext(framebuffer, 255, 255, 255, promptbuffer, i, pitch,
                 bytes_per_pixel);

        continue;
      }
      if (tec == '\b') {
        if (idx > 0) {
          idx--;
          textbuffer[idx] = '\0';
        } else {
          continue;
        }

      } else {
        if (idx >= sizeof(textbuffer) - 1) {
          continue;
        }

        if (capslock == 1 && tec >= 'a' && tec <= 'z') {
          textbuffer[idx] = tec - 32;
        } else {
          textbuffer[idx] = tec;
        }
        idx++;
        textbuffer[idx] = '\0';
      }
      if (i >= height / 16) {
        i = 0;
        frect(framebuffer, pitch, 0, 0, width, height, 0, 0, 0,
              bytes_per_pixel);
      }
      cpstr(promptbuffer, "radonos> ");
      cpstr(&promptbuffer[9], textbuffer);

      frect(framebuffer, pitch, 0, i * 16, width, (i * 16) + 16, 0, 0, 0,
            bytes_per_pixel);
      drawtext(framebuffer, 255, 255, 255, promptbuffer, i, pitch,
               bytes_per_pixel);
    }
  }
  while (1)
    ;
}
