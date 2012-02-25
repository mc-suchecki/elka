#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "tifftags.h"
#include "codes.h"

typedef struct {
  int width, height;
  unsigned char* pImg;
  int imgSize;
  int comp;
} imgInfo;

typedef struct {
  unsigned short bfType; 
  unsigned long  bfSize; 
  unsigned short bfReserved1; 
  unsigned short bfReserved2; 
  unsigned long  bfOffBits; 
  unsigned long  biSize; 
  long  biWidth; 
  long  biHeight; 
  short biPlanes; 
  short biBitCount; 
  unsigned long  biCompression; 
  unsigned long  biSizeImage; 
  long biXPelsPerMeter; 
  long biYPelsPerMeter; 
  unsigned long  biClrUsed; 
  unsigned long  biClrImportant;
  unsigned long  RGBQuad_0;
  unsigned long  RGBQuad_1;
} bmpHdr;

//funkcje napisane w asemblerze
extern void WriteBits(unsigned short rleCount, unsigned short *rleLine, unsigned char *pels);
unsigned short ReadCode(g3code *codetable, unsigned char** srcptr, unsigned char *mask);

void* freeResources(FILE* pFile, void* pFirst, void* pSnd) {
  if(pFile) fclose(pFile);
  if(pFirst) free(pFirst);
  if(pSnd) free(pSnd);
  return 0;
}

imgInfo* InitImage(int w, int h) {
  imgInfo *pImg;
  if ( (pImg = (imgInfo *) malloc(sizeof(imgInfo))) == 0)
    return 0;
  pImg->height = h;
  pImg->width = w;
  pImg->pImg = (unsigned char*) malloc((((w + 31) >> 5) << 2) * h);
  if (pImg->pImg == 0) {
    free(pImg);
    return 0;
  }
  memset(pImg->pImg, 0xFF, (((w + 31) >> 5) << 2) * h);
  return pImg;
}

void FreeImage(imgInfo* pInfo) {
  if(pInfo && pInfo->pImg) free(pInfo->pImg);
  if(pInfo) free(pInfo);
}

int saveBMP(const imgInfo* pInfo, const char* fname) {
  int lineBytes = ((pInfo->width + 31) >> 5)<<2;
  bmpHdr bmpHead = {
    0x4D42,				// unsigned short bfType; 
    sizeof(bmpHdr),		// unsigned long  bfSize; 
    0, 0,				// unsigned short bfReserved1, bfReserved2; 
    sizeof(bmpHdr),		// unsigned long  bfOffBits; 
    40,					// unsigned long  biSize; 
    pInfo->width,		// long  biWidth; 
    pInfo->height,		// long  biHeight; 
    1,					// short biPlanes; 
    1,					// short biBitCount; 
    0,					// unsigned long  biCompression; 
    lineBytes * pInfo->height,	// unsigned long  biSizeImage; 
    11811,				// long biXPelsPerMeter; = 300 dpi
    11811,				// long biYPelsPerMeter; 
    2,					// unsigned long  biClrUsed; 
    0,					// unsigned long  biClrImportant;
    0x00000000,			// unsigned long  RGBQuad_0;
    0x00FFFFFF			// unsigned long  RGBQuad_1;
  };

  FILE * fbmp;
  unsigned char *ptr;
  int y;

  if ((fbmp = fopen(fname, "wb")) == 0) return -1;

  if (fwrite(&bmpHead, sizeof(bmpHdr), 1, fbmp) != 1) {
    fclose(fbmp);
    return -2;
  }

  ptr = pInfo->pImg + lineBytes * (pInfo->height - 1);
  for (y=pInfo->height; y > 0; --y, ptr -= lineBytes)
    if (fwrite(ptr, sizeof(unsigned char), lineBytes, fbmp) != lineBytes) {
      fclose(fbmp);
      return -3;
    }

  fclose(fbmp);
  return 0;
}

imgInfo* readTIFF(const char* fname) {
  imgInfo* pInfo = 0;
  FILE* ftif = 0;
  TIFF_T_Header tifHead;
  unsigned short dirSize = 0, i;
  TIFF_T_DirEntry *pDir = 0;
  int width = 0, height = 0;
  int imgOffset = 0;
  int imgLength = 0;
  unsigned char *pCImg = 0, *pImg = 0;

  pInfo = 0;
  if ((ftif = fopen(fname, "rb")) == 0) return 0;

  if (fread((void *) &tifHead, sizeof(tifHead), 1, ftif) != 1)
    return (imgInfo *) freeResources(ftif, 0, 0);

  if (tifHead.byteorder != 0x4949 && tifHead.version != 42)
    return (imgInfo *) freeResources(ftif, 0, 0);

  if (fseek(ftif, tifHead.diroffset, SEEK_SET) == -1 ||
      fread((void *) &dirSize, sizeof(unsigned short), 1, ftif) != 1 ||
      (pDir = (TIFF_T_DirEntry *) malloc(sizeof(TIFF_T_DirEntry)*dirSize)) == 0)
    return (imgInfo *) freeResources(ftif, 0, 0);

  if (fread((void *) pDir, sizeof(TIFF_T_DirEntry), dirSize, ftif) != dirSize)
    return (imgInfo *) freeResources(ftif, pDir, 0);

  for (i = 0; i < dirSize; ++i) {
    switch (pDir[i].tag) {
      case TIFF_C_ImageWidth:
        if (pDir[i].type != TIFF_C_LONG || pDir[i].count != 1)
          return (imgInfo *) freeResources(ftif, pDir, 0);
        width = (int) pDir[i].value;
        break;
      case TIFF_C_ImageLength:
        if (pDir[i].type != TIFF_C_LONG || pDir[i].count != 1)
          return (imgInfo *) freeResources(ftif, pDir, 0);
        height = (int) pDir[i].value;
        break;
      case TIFF_C_BitsPerSample:
      case TIFF_C_Tresholding:
      case TIFF_C_FillOrder:
      case TIFF_C_SamplesPerPixel:
        if (pDir[i].type != TIFF_C_SHORT || pDir[i].count != 1 || (pDir[i].value & 0xFFFF) != 1)
          return (imgInfo *) freeResources(ftif, pDir, 0);
        break;
      case TIFF_C_Compression:
        if (pDir[i].type != TIFF_C_SHORT || pDir[i].count != 1 || pDir[i].value != TIFF_C_CCITT1D)
          return (imgInfo *) freeResources(ftif, pDir, 0);
        break;
      case TIFF_C_PhotometricInterpretation:
        if (pDir[i].type != TIFF_C_SHORT || pDir[i].count != 1 || pDir[i].value != TIFF_C_WhiteIsZero)
          return (imgInfo *) freeResources(ftif, pDir, 0);
        break;
      case TIFF_C_StripOffsets:
        if (pDir[i].type != TIFF_C_LONG || pDir[i].count != 1)
          return (imgInfo *) freeResources(ftif, pDir, 0);
        imgOffset = (int) pDir[i].value;
        break;
      case TIFF_C_RowsPerStrip:
        if (pDir[i].type != TIFF_C_LONG || pDir[i].count != 1 || pDir[i].value != height)
          return (imgInfo *) freeResources(ftif, pDir, 0);
        break;
      case TIFF_C_StripByteCounts:
        if (pDir[i].type != TIFF_C_LONG || pDir[i].count != 1)
          return (imgInfo *) freeResources(ftif, pDir, 0);
        imgLength = (int) pDir[i].value;
        break;
    }
  }

  if (width == 0 || height == 0 || imgOffset == 0 || imgLength == 0)
    return (imgInfo *) freeResources(ftif, pDir, 0);
  free(pDir);

  if ((pCImg = malloc(imgLength + 4)) == 0 ||
      fseek(ftif, imgOffset, SEEK_SET) == -1 ||
      fread(pCImg, sizeof(unsigned char), imgLength, ftif) != imgLength)
    return (imgInfo *) freeResources(ftif, pCImg, 0);
  fclose(ftif);

  pInfo = malloc(sizeof(imgInfo));
  pInfo->width = width;
  pInfo->height = height;
  pInfo->pImg = pCImg;
  pInfo->imgSize = imgLength;
  pInfo->comp = 1;
  /* nadmiarowe bajty w buforze obrazu wype³niam zerami - dziêki temu
     nie bêdê musia³ ca³y czas sprawdzaæ, czy nie "wybiegam" poza bufor
     skompresowanego obrazu - dostanê infromacjê o b³êdnym kodzie */
  *(unsigned long *)(pInfo->pImg + pInfo->imgSize) = 0l;

  return pInfo;
}

//i - dl
//clen - dh
//rlen - ax
//code - edi
//codetable - stos
//srcptr - stos
//mask - stos
//maska - cl
//bajt - ch
/* Funkcja odczytuje ze strumienia kody T4 sk³adaj¹c w razie potrzeby kody z³o¿one.
IN: white - oznaczenie, czy czytany bêdzie odcinek bia³y czy czarny
srcptr - wskazanie na bie¿¹cy bajt strumienia wejœciowego (mo¿e byæ modyfikowany)
mask - maska odczytu strumienia wejœciowego w bie¿¹cym bajcie (mo¿e byæ modyfikowany)
RET: d³ugoœæ odcinka lub 0xFFFF w przypadku b³êdu */
unsigned short ReadCodeC(g3code *codetable, unsigned char** srcptr, unsigned char *mask) {
  unsigned char i = 0, clen = 1;
  unsigned short rlen = 0;
  unsigned short code = (**srcptr) & (*mask) ? 1 : 0;
  *mask >>= 1;
  if(*mask == 0) {
    ++*srcptr;
    *mask = 0x80;
  }

  while (1) {
    code = (code << 1) | ((**srcptr) & (*mask) ? 1 : 0);
    *mask >>= 1;
    if(*mask == 0) {
      ++*srcptr;
      *mask = 0x80;
    }

    ++clen;
    if(clen > 13) return 0xFFFF;

    for (; codetable[i].length == clen; ++i) {
      if (codetable[i].code == code) {
        rlen += (unsigned short) codetable[i].value;
        if (codetable[i].value < 64) {  //koniec szukania
          return rlen;
        } else {                        //szukamy od poczatku
          code = (**srcptr) & (*mask) ? 1 : 0;
          *mask >>= 1;
          if(*mask == 0) {
            ++*srcptr;
            *mask = 0x80;
          }
          clen = 1;
          i = 0;
          break;
        }
      }
    }

  }
  return rlen;
}

imgInfo* G32RAS(imgInfo* pImg) {
  imgInfo* pInfo = InitImage(pImg->width, pImg->height);
  unsigned short *refline = (unsigned short*) malloc((pImg->width + 1)*sizeof(unsigned short));
  unsigned short linewidth = ((pImg->width + 31) >> 5 ) << 2;
  unsigned short i = pInfo->height;
  unsigned char *dstptr = pInfo->pImg;
  unsigned char *srcptr = pImg->pImg; 
  unsigned char mask = 0x80;
  int length, linelen;
  g3code *codetable;
  short rleCnt;

  for (; i > 0; --i) {
    rleCnt = 0;
    codetable = whitecodes;
    linelen = 0;

    do {
      length = ReadCode(codetable, &srcptr, &mask);
      refline[rleCnt++] = length;
      linelen += length;
      if (codetable == blackcodes) codetable = whitecodes;
      else codetable = blackcodes;
    } while (linelen < pImg->width);

    if (linelen != pImg->width) break;

    if(mask != 0x80) {
      ++srcptr;
      mask = 0x80;
    }

    WriteBits(rleCnt, refline, dstptr);
    dstptr += linewidth ;
  }
  free(refline);
  return pInfo;
}

int main(int argc, char* argv[]) {
  imgInfo *pInfo, *pCmp;

  if(sizeof(bmpHdr) != 62) {
    printf("Trzeba zmieniæ opcje kompilacji, tak by rozmiar struktury bmpHdr wynosi³ 62 bajty.\n");
    return 1;
  }

  if((pCmp = readTIFF("spim.tif")) == 0) return 2;
  pInfo = G32RAS(pCmp);
  if(saveBMP(pInfo, "spim.bmp") != 0) return 3;

  return 0;
}
