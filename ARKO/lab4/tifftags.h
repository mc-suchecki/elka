#ifndef __TIFFTAGS_H
#define __TIFFTAGS_H

#include "codes.h"

/* TIFF types definitions */

#define   TIFF_C_BYTE                          1         /*  8-bit unsigned integer */
#define   TIFF_C_ASCII                         2         /* byte containing 7-bit ASCII code */
#define   TIFF_C_SHORT                         3         /* 16-bit unsigned integer */
#define   TIFF_C_LONG                          4         /* 32-bit unsigned integer */
#define   TIFF_C_RATIONAL                      5         /* two LONG's: numerator & denominator */
#define   TIFF_C_SBYTE                         6         /*  8-bit U2 integer */
#define   TIFF_C_UNDEFINED                     7         /*  8-bit byte that may contain anything */
#define   TIFF_C_SSHORT                        8         /* 16-bit U2 integer */
#define   TIFF_C_SLONG                         9         /* 32-bit U2 integer */
#define   TIFF_C_SRATIONAL                    10         /* two SLONG's */
#define   TIFF_C_FLOAT                        11         /* single precision IEEE format */
#define   TIFF_C_DOUBLE                       12         /* double precision IEEE format */


/* TIFF tags definitions  */

#define   TIFF_C_NewSubfileType              254         /*  0xFE   */
#define   TIFF_C_SubfileType                 255         /*  0xFF   */
#define   TIFF_C_ImageWidth                  256         /*  0x100  */
#define   TIFF_C_ImageLength                 257         /*  0x101  */
#define   TIFF_C_BitsPerSample               258         /*  0x102  */
#define   TIFF_C_Compression                 259         /*  0x103  */
  #define   TIFF_C_Uncompressed                1
  #define   TIFF_C_CCITT1D                     2
  #define   TIFF_C_Group3Fax                   3
  #define   TIFF_C_Group4Fax                   4
  #define   TIFF_C_LZW                         5
  #define   TIFF_C_JPEG                        6
  #define   TIFF_C_PackBits                    32773
  #define   TIFF_C_ArpaService                 32774
#define   TIFF_C_PhotometricInterpretation   262         /*  0x106  */
  #define   TIFF_C_WhiteIsZero                 0
  #define   TIFF_C_BlackIsZero                 1
  #define   TIFF_C_RGB                         2
  #define   TIFF_C_RGBPalette                  3
  #define   TIFF_C_TransparencyMask            4
  #define   TIFF_C_CMYK                        5
  #define   TIFF_C_YCbCr                       6
  #define   TIFF_C_CIELab                      8
#define   TIFF_C_Tresholding                 263         /*  0x107  */
#define   TIFF_C_CellWidth                   264         /*  0x108  */
#define   TIFF_C_CellLength                  265         /*  0x109  */
#define   TIFF_C_FillOrder                   266         /*  0x10A  */
#define   TIFF_C_DocumentName                269         /*  0x10D  */
#define   TIFF_C_ImageDescription            270         /*  0x10E  */
#define   TIFF_C_Make                        271         /*  0x10F  */
#define   TIFF_C_Model                       272         /*  0x110  */
#define   TIFF_C_StripOffsets                273         /*  0x111  */
#define   TIFF_C_Orientation                 274         /*  0x112  */
#define   TIFF_C_SamplesPerPixel             277         /*  0x115  */
#define   TIFF_C_RowsPerStrip                278         /*  0x116  */
#define   TIFF_C_StripByteCounts             279         /*  0x117  */
#define   TIFF_C_MinSampleValue              280         /*  0x118  */
#define   TIFF_C_MaxSampleValue              281         /*  0x119  */
#define   TIFF_C_XResolution                 282         /*  0x11A  */
#define   TIFF_C_YResolution                 283         /*  0x11B  */
#define   TIFF_C_PlanarConfiguration         284         /*  0x11C  */
#define   TIFF_C_PageName                    285         /*  0x11D  */
#define   TIFF_C_XPosition                   286         /*  0x11E  */
#define   TIFF_C_YPosition                   287         /*  0x11F  */
#define   TIFF_C_FreeOffsets                 288         /*  0x120  */
#define   TIFF_C_FreeByteCounts              289         /*  0x121  */
#define   TIFF_C_GrayResponseUnit            290         /*  0x122  */
#define   TIFF_C_GrayResponseCurve           291         /*  0x123  */
#define   TIFF_C_T4Options                   292         /*  0x124  */
#define   TIFF_C_T6Options                   293         /*  0x125  */
#define   TIFF_C_ResolutionUnit              296         /*  0x128  */
#define   TIFF_C_PageNumber                  297         /*  0x129  */
#define   TIFF_C_TransferFunction            301         /*  0x12D  */
#define   TIFF_C_Software                    305         /*  0x131  */
#define   TIFF_C_DateTime                    306         /*  0x132  */
#define   TIFF_C_Artist                      315         /*  0x13B  */
#define   TIFF_C_HostComputer                316         /*  0x13C  */
#define   TIFF_C_Predictor                   317         /*  0x13D  */
#define   TIFF_C_WhitePoint                  318         /*  0x13E  */
#define   TIFF_C_PrimaryChromacities         319         /*  0x13F  */
#define   TIFF_C_ColorMap                    320         /*  0x140  */
#define   TIFF_C_HaltoneHints                321         /*  0x141  */
#define   TIFF_C_TileWidth                   322         /*  0x142  */
#define   TIFF_C_TileLength                  323         /*  0x143  */
#define   TIFF_C_TileOffsets                 324         /*  0x144  */
#define   TIFF_C_TileByteCounts              325         /*  0x145  */
#define   TIFF_C_InkSet                      332         /*  0x14C  */
#define   TIFF_C_InkNames                    333         /*  0x14D  */
#define   TIFF_C_NumberOfInks                334         /*  0x14E  */
#define   TIFF_C_DotRange                    336         /*  0x150  */
#define   TIFF_C_TargetPrinter               337         /*  0x151  */
#define   TIFF_C_ExtraSamples                338         /*  0x152  */
#define   TIFF_C_SampleFormat                339         /*  0x153  */
#define   TIFF_C_SMinSampleValue             340         /*  0x154  */
#define   TIFF_C_SMaxSampleValue             341         /*  0x155  */
#define   TIFF_C_TransferRange               342         /*  0x156  */
#define   TIFF_C_JPEGProc                    512         /*  0x200  */
#define   TIFF_C_JPEGInterchangeFormat       513         /*  0x201  */
#define   TIFF_C_JPEGInterchangeFormatLngth  514         /*  0x202  */
#define   TIFF_C_JPEGRestartInterval         515         /*  0x203  */
#define   TIFF_C_JPEGLoslessPredictors       517         /*  0x205  */
#define   TIFF_C_JPEGPointTransforms         518         /*  0x206  */
#define   TIFF_C_JPEGQTables                 519         /*  0x207  */
#define   TIFF_C_JPEGDCTables                520         /*  0x208  */
#define   TIFF_C_JPEGACTables                521         /*  0x209  */
#define   TIFF_C_YCbCrCoefficients           529         /*  0x211  */
#define   TIFF_C_YCbCrSubSampling            530         /*  0x212  */
#define   TIFF_C_YCbCrPositioning            531         /*  0x213  */
#define   TIFF_C_ReferenceBlackWhite         532         /*  0x214  */
#define   TIFF_C_Copyright                   33432       /*  0x8298 */


typedef   struct {
          unsigned short  byteorder ;
          unsigned short  version ;
          unsigned long   diroffset ;
          } TIFF_T_Header ;

typedef   struct {
          unsigned short  tag ;
          unsigned short  type ;
          unsigned long   count ;
          unsigned long   value ;
          } TIFF_T_DirEntry ;


/* internal constants definitions */

#define   TIFF_C_NONE                       0xFF         /* */
#define   TIFF_C_EXIST                      0xFE
#define   TIFF_C_PROCESS                    0xFD
#define   TIFF_C_IGNORE                     0xFC
#define   TIFF_C_BASIC                      0xFB

#define   TIFF_C_Undef                      0xFA
#define   TIFF_C_SampPPel                   0xF9
#define   TIFF_C_StripsPImg                 0xF8
#define   TIFF_C_BitsPSmpl                  0xF7
#define   TIFF_C_TilesPImg                  0xF6

#define   TIFF_C_HostOrder                  0x4949

typedef   struct {
            unsigned short  tag ;
            char *          name ;
            unsigned char   p_type,
                            s_type ;
            unsigned short  number ;
            unsigned short  status ;
            unsigned char   def_ind ;
            unsigned long   value ;
          } TIFF_T_TagDescr ;

unsigned short ReadCode(g3code *codetable, unsigned char** srcptr, unsigned char *mask) {
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

#endif /* __TIFFTAGS_H */
