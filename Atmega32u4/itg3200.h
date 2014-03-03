/*
 * itg3200.h
 *
 * Created: 01.03.2014 14:27:45
 *  Author: Matthias Riegler
 */ 


#ifndef ITG3200_H_
#define ITG3200_H_

/* === ITG3200 Register Defines === */
#define ITG3200_ADDR	0x68
#define ITG3200_WHO		0x00
#define	ITG3200_SMPL	0x15
#define ITG3200_DLPF	0x16
#define ITG3200_INT_C	0x17
#define ITG3200_INT_S	0x1A
#define	ITG3200_TMP_H	0x1B
#define	ITG3200_TMP_L	0x1C
#define	ITG3200_GX_H	0x1D
#define	ITG3200_GX_L	0x1E
#define	ITG3200_GY_H	0x1F
#define	ITG3200_GY_L	0x20
#define ITG3200_GZ_H	0x21
#define ITG3200_GZ_L	0x22
#define ITG3200_PWR_M	0x3E

/* === General ITG3200 Defines === */
#define ITG3200_SENSITIVITY 14.375
#define ITG3200_TEMP_SENSITIVITY 280.0
#define ITG3200_TEMP_OFFSET 13200
#define ITG3200_TEMP_OFFSET_CELSIUS 35.0



#endif /* ITG3200_H_ */