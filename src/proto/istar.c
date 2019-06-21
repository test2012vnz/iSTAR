/* Automatically generated nanopb constant definitions */
/* Generated by nanopb-0.3.9.2 at Mon May 13 08:48:24 2019. */

#include "istar.h"

/* @@protoc_insertion_point(includes) */
#if PB_PROTO_HEADER_VERSION != 30
#error Regenerate this file with the current version of nanopb generator.
#endif



const pb_field_t Comunication_fields[4] = {
    PB_FIELD(  1, INT32   , SINGULAR, STATIC  , FIRST, Comunication, WIFI, WIFI, 0),
    PB_FIELD(  2, INT32   , SINGULAR, STATIC  , OTHER, Comunication, Ethernet, WIFI, 0),
    PB_FIELD(  3, INT32   , SINGULAR, STATIC  , OTHER, Comunication, GSM, Ethernet, 0),
    PB_LAST_FIELD
};

const pb_field_t Header_fields[8] = {
    PB_FIELD(  1, STRING  , SINGULAR, STATIC  , FIRST, Header, Serial, Serial, 0),
    PB_FIELD(  2, UINT32  , SINGULAR, STATIC  , OTHER, Header, Reset_Count, Serial, 0),
    PB_FIELD(  3, UINT32  , SINGULAR, STATIC  , OTHER, Header, Free_Ram, Reset_Count, 0),
    PB_FIELD(  4, MESSAGE , SINGULAR, STATIC  , OTHER, Header, Com, Free_Ram, &Comunication_fields),
    PB_FIELD(  5, STRING  , SINGULAR, STATIC  , OTHER, Header, Version, Com, 0),
    PB_FIELD(  6, FLOAT   , SINGULAR, STATIC  , OTHER, Header, INTemp, Version, 0),
    PB_FIELD(  7, STRING  , SINGULAR, STATIC  , OTHER, Header, Debug, INTemp, 0),
    PB_LAST_FIELD
};

const pb_field_t iSTAR_fields[39] = {
    PB_FIELD(  1, INT32   , SINGULAR, STATIC  , FIRST, iSTAR, A1, A1, 0),
    PB_FIELD(  2, BOOL    , SINGULAR, STATIC  , OTHER, iSTAR, A2, A1, 0),
    PB_FIELD(  3, UINT32  , SINGULAR, STATIC  , OTHER, iSTAR, A3, A2, 0),
    PB_FIELD(  4, UINT32  , SINGULAR, STATIC  , OTHER, iSTAR, A4, A3, 0),
    PB_FIELD(  5, BOOL    , SINGULAR, STATIC  , OTHER, iSTAR, A5, A4, 0),
    PB_FIELD(  6, BOOL    , SINGULAR, STATIC  , OTHER, iSTAR, A6, A5, 0),
    PB_FIELD(  7, BOOL    , SINGULAR, STATIC  , OTHER, iSTAR, A7, A6, 0),
    PB_FIELD(  8, UINT32  , SINGULAR, STATIC  , OTHER, iSTAR, A8, A7, 0),
    PB_FIELD(  9, UINT32  , SINGULAR, STATIC  , OTHER, iSTAR, A9, A8, 0),
    PB_FIELD( 10, UINT32  , SINGULAR, STATIC  , OTHER, iSTAR, A10, A9, 0),
    PB_FIELD( 11, UINT32  , SINGULAR, STATIC  , OTHER, iSTAR, A11, A10, 0),
    PB_FIELD( 12, UINT32  , SINGULAR, STATIC  , OTHER, iSTAR, A12, A11, 0),
    PB_FIELD( 13, UINT32  , SINGULAR, STATIC  , OTHER, iSTAR, A13, A12, 0),
    PB_FIELD( 14, UINT32  , SINGULAR, STATIC  , OTHER, iSTAR, A14, A13, 0),
    PB_FIELD( 15, UINT32  , SINGULAR, STATIC  , OTHER, iSTAR, A15, A14, 0),
    PB_FIELD( 16, STRING  , SINGULAR, STATIC  , OTHER, iSTAR, A16, A15, 0),
    PB_FIELD( 17, UINT32  , SINGULAR, STATIC  , OTHER, iSTAR, A17, A16, 0),
    PB_FIELD( 18, UINT32  , SINGULAR, STATIC  , OTHER, iSTAR, A18, A17, 0),
    PB_FIELD( 19, UINT32  , SINGULAR, STATIC  , OTHER, iSTAR, A19, A18, 0),
    PB_FIELD( 20, UINT32  , SINGULAR, STATIC  , OTHER, iSTAR, A20, A19, 0),
    PB_FIELD( 21, UINT32  , SINGULAR, STATIC  , OTHER, iSTAR, A21, A20, 0),
    PB_FIELD( 22, UINT32  , SINGULAR, STATIC  , OTHER, iSTAR, A22, A21, 0),
    PB_FIELD( 23, STRING  , SINGULAR, STATIC  , OTHER, iSTAR, A23, A22, 0),
    PB_FIELD( 24, STRING  , SINGULAR, STATIC  , OTHER, iSTAR, A24, A23, 0),
    PB_FIELD( 25, STRING  , SINGULAR, STATIC  , OTHER, iSTAR, A25, A24, 0),
    PB_FIELD( 26, STRING  , SINGULAR, STATIC  , OTHER, iSTAR, A26, A25, 0),
    PB_FIELD( 27, STRING  , SINGULAR, STATIC  , OTHER, iSTAR, A27, A26, 0),
    PB_FIELD( 28, STRING  , SINGULAR, STATIC  , OTHER, iSTAR, A28, A27, 0),
    PB_FIELD( 29, UINT32  , SINGULAR, STATIC  , OTHER, iSTAR, A29, A28, 0),
    PB_FIELD( 30, UINT32  , SINGULAR, STATIC  , OTHER, iSTAR, A30, A29, 0),
    PB_FIELD( 31, UINT32  , SINGULAR, STATIC  , OTHER, iSTAR, A31, A30, 0),
    PB_FIELD( 32, UINT32  , SINGULAR, STATIC  , OTHER, iSTAR, A32, A31, 0),
    PB_FIELD( 33, UINT32  , SINGULAR, STATIC  , OTHER, iSTAR, A33, A32, 0),
    PB_FIELD( 34, UINT32  , SINGULAR, STATIC  , OTHER, iSTAR, A34, A33, 0),
    PB_FIELD( 35, UINT32  , SINGULAR, STATIC  , OTHER, iSTAR, A35, A34, 0),
    PB_FIELD( 36, UINT32  , SINGULAR, STATIC  , OTHER, iSTAR, A36, A35, 0),
    PB_FIELD( 37, STRING  , SINGULAR, STATIC  , OTHER, iSTAR, A37, A36, 0),
    PB_FIELD( 38, UINT32  , SINGULAR, STATIC  , OTHER, iSTAR, status, A37, 0),
    PB_LAST_FIELD
};

const pb_field_t DPM_fields[40] = {
    PB_FIELD(  1, FLOAT   , SINGULAR, STATIC  , FIRST, DPM, A1, A1, 0),
    PB_FIELD(  2, FLOAT   , SINGULAR, STATIC  , OTHER, DPM, A2, A1, 0),
    PB_FIELD(  3, FLOAT   , SINGULAR, STATIC  , OTHER, DPM, A3, A2, 0),
    PB_FIELD(  4, FLOAT   , SINGULAR, STATIC  , OTHER, DPM, A4, A3, 0),
    PB_FIELD(  5, FLOAT   , SINGULAR, STATIC  , OTHER, DPM, A5, A4, 0),
    PB_FIELD(  6, FLOAT   , SINGULAR, STATIC  , OTHER, DPM, A6, A5, 0),
    PB_FIELD(  7, FLOAT   , SINGULAR, STATIC  , OTHER, DPM, A7, A6, 0),
    PB_FIELD(  8, FLOAT   , SINGULAR, STATIC  , OTHER, DPM, A8, A7, 0),
    PB_FIELD(  9, FLOAT   , SINGULAR, STATIC  , OTHER, DPM, A9, A8, 0),
    PB_FIELD( 10, FLOAT   , SINGULAR, STATIC  , OTHER, DPM, A10, A9, 0),
    PB_FIELD( 11, FLOAT   , SINGULAR, STATIC  , OTHER, DPM, A11, A10, 0),
    PB_FIELD( 12, FLOAT   , SINGULAR, STATIC  , OTHER, DPM, A12, A11, 0),
    PB_FIELD( 13, FLOAT   , SINGULAR, STATIC  , OTHER, DPM, A13, A12, 0),
    PB_FIELD( 14, FLOAT   , SINGULAR, STATIC  , OTHER, DPM, A14, A13, 0),
    PB_FIELD( 15, FLOAT   , SINGULAR, STATIC  , OTHER, DPM, A15, A14, 0),
    PB_FIELD( 16, FLOAT   , SINGULAR, STATIC  , OTHER, DPM, A16, A15, 0),
    PB_FIELD( 17, FLOAT   , SINGULAR, STATIC  , OTHER, DPM, A17, A16, 0),
    PB_FIELD( 18, FLOAT   , SINGULAR, STATIC  , OTHER, DPM, A18, A17, 0),
    PB_FIELD( 19, FLOAT   , SINGULAR, STATIC  , OTHER, DPM, A19, A18, 0),
    PB_FIELD( 20, FLOAT   , SINGULAR, STATIC  , OTHER, DPM, A20, A19, 0),
    PB_FIELD( 21, FLOAT   , SINGULAR, STATIC  , OTHER, DPM, A21, A20, 0),
    PB_FIELD( 22, FLOAT   , SINGULAR, STATIC  , OTHER, DPM, A22, A21, 0),
    PB_FIELD( 23, FLOAT   , SINGULAR, STATIC  , OTHER, DPM, A23, A22, 0),
    PB_FIELD( 24, FLOAT   , SINGULAR, STATIC  , OTHER, DPM, A24, A23, 0),
    PB_FIELD( 25, FLOAT   , SINGULAR, STATIC  , OTHER, DPM, A25, A24, 0),
    PB_FIELD( 26, FLOAT   , SINGULAR, STATIC  , OTHER, DPM, A26, A25, 0),
    PB_FIELD( 27, FLOAT   , SINGULAR, STATIC  , OTHER, DPM, A27, A26, 0),
    PB_FIELD( 28, FLOAT   , SINGULAR, STATIC  , OTHER, DPM, A28, A27, 0),
    PB_FIELD( 29, FLOAT   , SINGULAR, STATIC  , OTHER, DPM, A29, A28, 0),
    PB_FIELD( 30, FLOAT   , SINGULAR, STATIC  , OTHER, DPM, A30, A29, 0),
    PB_FIELD( 31, FLOAT   , SINGULAR, STATIC  , OTHER, DPM, A31, A30, 0),
    PB_FIELD( 32, UINT32  , SINGULAR, STATIC  , OTHER, DPM, A32, A31, 0),
    PB_FIELD( 33, UINT32  , SINGULAR, STATIC  , OTHER, DPM, A33, A32, 0),
    PB_FIELD( 34, UINT32  , SINGULAR, STATIC  , OTHER, DPM, A34, A33, 0),
    PB_FIELD( 35, UINT32  , SINGULAR, STATIC  , OTHER, DPM, A35, A34, 0),
    PB_FIELD( 36, UINT32  , SINGULAR, STATIC  , OTHER, DPM, A36, A35, 0),
    PB_FIELD( 37, UINT32  , SINGULAR, STATIC  , OTHER, DPM, A37, A36, 0),
    PB_FIELD( 38, UINT32  , SINGULAR, STATIC  , OTHER, DPM, A38, A37, 0),
    PB_FIELD( 39, UINT32  , SINGULAR, STATIC  , OTHER, DPM, status, A38, 0),
    PB_LAST_FIELD
};

const pb_field_t SOFAR_fields[40] = {
    PB_FIELD(  1, UINT32  , SINGULAR, STATIC  , FIRST, SOFAR, A1, A1, 0),
    PB_FIELD(  2, UINT32  , SINGULAR, STATIC  , OTHER, SOFAR, A2, A1, 0),
    PB_FIELD(  3, UINT32  , SINGULAR, STATIC  , OTHER, SOFAR, A3, A2, 0),
    PB_FIELD(  4, UINT32  , SINGULAR, STATIC  , OTHER, SOFAR, A4, A3, 0),
    PB_FIELD(  5, UINT32  , SINGULAR, STATIC  , OTHER, SOFAR, A5, A4, 0),
    PB_FIELD(  6, UINT32  , SINGULAR, STATIC  , OTHER, SOFAR, A6, A5, 0),
    PB_FIELD(  7, FLOAT   , SINGULAR, STATIC  , OTHER, SOFAR, A7, A6, 0),
    PB_FIELD(  8, FLOAT   , SINGULAR, STATIC  , OTHER, SOFAR, A8, A7, 0),
    PB_FIELD(  9, FLOAT   , SINGULAR, STATIC  , OTHER, SOFAR, A9, A8, 0),
    PB_FIELD( 10, FLOAT   , SINGULAR, STATIC  , OTHER, SOFAR, A10, A9, 0),
    PB_FIELD( 11, FLOAT   , SINGULAR, STATIC  , OTHER, SOFAR, A11, A10, 0),
    PB_FIELD( 12, FLOAT   , SINGULAR, STATIC  , OTHER, SOFAR, A12, A11, 0),
    PB_FIELD( 13, FLOAT   , SINGULAR, STATIC  , OTHER, SOFAR, A13, A12, 0),
    PB_FIELD( 14, FLOAT   , SINGULAR, STATIC  , OTHER, SOFAR, A14, A13, 0),
    PB_FIELD( 15, FLOAT   , SINGULAR, STATIC  , OTHER, SOFAR, A15, A14, 0),
    PB_FIELD( 16, FLOAT   , SINGULAR, STATIC  , OTHER, SOFAR, A16, A15, 0),
    PB_FIELD( 17, FLOAT   , SINGULAR, STATIC  , OTHER, SOFAR, A17, A16, 0),
    PB_FIELD( 18, FLOAT   , SINGULAR, STATIC  , OTHER, SOFAR, A18, A17, 0),
    PB_FIELD( 19, FLOAT   , SINGULAR, STATIC  , OTHER, SOFAR, A19, A18, 0),
    PB_FIELD( 20, FLOAT   , SINGULAR, STATIC  , OTHER, SOFAR, A20, A19, 0),
    PB_FIELD( 21, FLOAT   , SINGULAR, STATIC  , OTHER, SOFAR, A21, A20, 0),
    PB_FIELD( 22, FLOAT   , SINGULAR, STATIC  , OTHER, SOFAR, A22, A21, 0),
    PB_FIELD( 23, FLOAT   , SINGULAR, STATIC  , OTHER, SOFAR, A23, A22, 0),
    PB_FIELD( 24, FLOAT   , SINGULAR, STATIC  , OTHER, SOFAR, A24, A23, 0),
    PB_FIELD( 25, UINT32  , SINGULAR, STATIC  , OTHER, SOFAR, A25, A24, 0),
    PB_FIELD( 26, INT32   , SINGULAR, STATIC  , OTHER, SOFAR, A26, A25, 0),
    PB_FIELD( 27, INT32   , SINGULAR, STATIC  , OTHER, SOFAR, A27, A26, 0),
    PB_FIELD( 28, UINT32  , SINGULAR, STATIC  , OTHER, SOFAR, A28, A27, 0),
    PB_FIELD( 29, UINT32  , SINGULAR, STATIC  , OTHER, SOFAR, A29, A28, 0),
    PB_FIELD( 30, UINT32  , SINGULAR, STATIC  , OTHER, SOFAR, A30, A29, 0),
    PB_FIELD( 31, UINT32  , SINGULAR, STATIC  , OTHER, SOFAR, A31, A30, 0),
    PB_FIELD( 32, UINT32  , SINGULAR, STATIC  , OTHER, SOFAR, A32, A31, 0),
    PB_FIELD( 33, UINT32  , SINGULAR, STATIC  , OTHER, SOFAR, A33, A32, 0),
    PB_FIELD( 34, UINT32  , SINGULAR, STATIC  , OTHER, SOFAR, A34, A33, 0),
    PB_FIELD( 35, UINT32  , SINGULAR, STATIC  , OTHER, SOFAR, A35, A34, 0),
    PB_FIELD( 36, UINT32  , SINGULAR, STATIC  , OTHER, SOFAR, A36, A35, 0),
    PB_FIELD( 37, UINT32  , SINGULAR, STATIC  , OTHER, SOFAR, A37, A36, 0),
    PB_FIELD( 38, UINT32  , SINGULAR, STATIC  , OTHER, SOFAR, A38, A37, 0),
    PB_FIELD( 39, UINT32  , SINGULAR, STATIC  , OTHER, SOFAR, status, A38, 0),
    PB_LAST_FIELD
};

const pb_field_t MFM_fields[34] = {
    PB_FIELD(  1, FLOAT   , SINGULAR, STATIC  , FIRST, MFM, A1, A1, 0),
    PB_FIELD(  2, FLOAT   , SINGULAR, STATIC  , OTHER, MFM, A2, A1, 0),
    PB_FIELD(  3, FLOAT   , SINGULAR, STATIC  , OTHER, MFM, A3, A2, 0),
    PB_FIELD(  4, FLOAT   , SINGULAR, STATIC  , OTHER, MFM, A4, A3, 0),
    PB_FIELD(  5, FLOAT   , SINGULAR, STATIC  , OTHER, MFM, A5, A4, 0),
    PB_FIELD(  6, FLOAT   , SINGULAR, STATIC  , OTHER, MFM, A6, A5, 0),
    PB_FIELD(  7, FLOAT   , SINGULAR, STATIC  , OTHER, MFM, A7, A6, 0),
    PB_FIELD(  8, FLOAT   , SINGULAR, STATIC  , OTHER, MFM, A8, A7, 0),
    PB_FIELD(  9, FLOAT   , SINGULAR, STATIC  , OTHER, MFM, A9, A8, 0),
    PB_FIELD( 10, FLOAT   , SINGULAR, STATIC  , OTHER, MFM, A10, A9, 0),
    PB_FIELD( 11, FLOAT   , SINGULAR, STATIC  , OTHER, MFM, A11, A10, 0),
    PB_FIELD( 12, FLOAT   , SINGULAR, STATIC  , OTHER, MFM, A12, A11, 0),
    PB_FIELD( 13, FLOAT   , SINGULAR, STATIC  , OTHER, MFM, A13, A12, 0),
    PB_FIELD( 14, FLOAT   , SINGULAR, STATIC  , OTHER, MFM, A14, A13, 0),
    PB_FIELD( 15, FLOAT   , SINGULAR, STATIC  , OTHER, MFM, A15, A14, 0),
    PB_FIELD( 16, FLOAT   , SINGULAR, STATIC  , OTHER, MFM, A16, A15, 0),
    PB_FIELD( 17, FLOAT   , SINGULAR, STATIC  , OTHER, MFM, A17, A16, 0),
    PB_FIELD( 18, FLOAT   , SINGULAR, STATIC  , OTHER, MFM, A18, A17, 0),
    PB_FIELD( 19, FLOAT   , SINGULAR, STATIC  , OTHER, MFM, A19, A18, 0),
    PB_FIELD( 20, FLOAT   , SINGULAR, STATIC  , OTHER, MFM, A20, A19, 0),
    PB_FIELD( 21, FLOAT   , SINGULAR, STATIC  , OTHER, MFM, A21, A20, 0),
    PB_FIELD( 22, FLOAT   , SINGULAR, STATIC  , OTHER, MFM, A22, A21, 0),
    PB_FIELD( 23, FLOAT   , SINGULAR, STATIC  , OTHER, MFM, A23, A22, 0),
    PB_FIELD( 24, FLOAT   , SINGULAR, STATIC  , OTHER, MFM, A24, A23, 0),
    PB_FIELD( 25, FLOAT   , SINGULAR, STATIC  , OTHER, MFM, A25, A24, 0),
    PB_FIELD( 26, FLOAT   , SINGULAR, STATIC  , OTHER, MFM, A26, A25, 0),
    PB_FIELD( 27, FLOAT   , SINGULAR, STATIC  , OTHER, MFM, A27, A26, 0),
    PB_FIELD( 28, FLOAT   , SINGULAR, STATIC  , OTHER, MFM, A28, A27, 0),
    PB_FIELD( 29, FLOAT   , SINGULAR, STATIC  , OTHER, MFM, A29, A28, 0),
    PB_FIELD( 30, FLOAT   , SINGULAR, STATIC  , OTHER, MFM, A30, A29, 0),
    PB_FIELD( 31, FLOAT   , SINGULAR, STATIC  , OTHER, MFM, A31, A30, 0),
    PB_FIELD( 32, FLOAT   , SINGULAR, STATIC  , OTHER, MFM, A32, A31, 0),
    PB_FIELD( 33, UINT32  , SINGULAR, STATIC  , OTHER, MFM, status, A32, 0),
    PB_LAST_FIELD
};

const pb_field_t Frame_fields[6] = {
    PB_FIELD(  1, MESSAGE , SINGULAR, POINTER , FIRST, Frame, header, header, &Header_fields),
    PB_FIELD(  2, MESSAGE , SINGULAR, POINTER , OTHER, Frame, istar, header, &iSTAR_fields),
    PB_FIELD(  3, MESSAGE , SINGULAR, POINTER , OTHER, Frame, dpm, istar, &DPM_fields),
    PB_FIELD(  4, MESSAGE , SINGULAR, POINTER , OTHER, Frame, sofar, dpm, &SOFAR_fields),
    PB_FIELD(  5, MESSAGE , SINGULAR, POINTER , OTHER, Frame, mfm, sofar, &MFM_fields),
    PB_LAST_FIELD
};


/* Check that field information fits in pb_field_t */
#if !defined(PB_FIELD_32BIT)
/* If you get an error here, it means that you need to define PB_FIELD_32BIT
 * compile-time option. You can do that in pb.h or on compiler command line.
 * 
 * The reason you need to do this is that some of your messages contain tag
 * numbers or field sizes that are larger than what can fit in 8 or 16 bit
 * field descriptors.
 */
PB_STATIC_ASSERT((pb_membersize(Header, Com) < 65536), YOU_MUST_DEFINE_PB_FIELD_32BIT_FOR_MESSAGES_Comunication_Header_iSTAR_DPM_SOFAR_MFM_Frame)
#endif

#if !defined(PB_FIELD_16BIT) && !defined(PB_FIELD_32BIT)
/* If you get an error here, it means that you need to define PB_FIELD_16BIT
 * compile-time option. You can do that in pb.h or on compiler command line.
 * 
 * The reason you need to do this is that some of your messages contain tag
 * numbers or field sizes that are larger than what can fit in the default
 * 8 bit descriptors.
 */
PB_STATIC_ASSERT((pb_membersize(Header, Com) < 256), YOU_MUST_DEFINE_PB_FIELD_16BIT_FOR_MESSAGES_Comunication_Header_iSTAR_DPM_SOFAR_MFM_Frame)
#endif


/* @@protoc_insertion_point(eof) */