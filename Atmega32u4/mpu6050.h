/*
 * mpu6050.h
 *
 * Created: 29.03.2014 11:52:57
 *  Author: Matthias
 */ 


#ifndef MPU6050_H_
#define MPU6050_H_

#define MPU6050_ADDR 0x68

/* Accelerometer */
#define MPU6050_ACCEL_XOUT_H 0x3B
#define MPU6050_ACCEL_XOUT_L 0x3C
#define MPU6050_ACCEL_YOUT_H 0x3D
#define MPU6050_ACCEL_YOUT_L 0x3E
#define MPU6050_ACCEL_ZOUT_H 0x3F
#define MPU6050_ACCEL_ZOUT_L 0x40

/* Gyro */
#define MPU6050_GYRO_XOUT_H 0x43
#define MPU6050_GYRO_XOUT_L 0x44
#define MPU6050_GYRO_YOUT_H 0x45
#define MPU6050_GYRO_YOUT_L 0x46
#define MPU6050_GYRO_ZOUT_H 0x47
#define MPU6050_GYRO_ZOUT_L 0x48

/* Temperature */
#define MPU6050_TEMP_OUT_H 0x41
#define MPU6050_TEMP_OUT_L 0x42

/* Power Management */
#define MPU6050_POWER_MGR1 0x6B
#define MPU6050_POWER_MGR2 0x6C


/* DLP */
#define MPU6050_DLPF 0x1A

/* Gyro Range */
#define MPU6050_GYRO_RANGE 0x1B

/* ACC Range */
#define MPU6050_ACC_RANGE 0x1C

#endif /* MPU6050_H_ */