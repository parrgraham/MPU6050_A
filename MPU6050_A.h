//i2c_default gets defined in the i2c.h file ,need to put more hours into that part

#ifdef i2c_default
//as per the datasheet and register map
//https://invensense.tdk.com/wp-content/uploads/2015/02/MPU-6000-Datasheet1.pdf
//https://invensense.tdk.com/wp-content/uploads/2015/02/MPU-6000-Register-Map1.pdf
static int addr = 0x68;
static void mpu6050_reset() {
    uint8_t buf[] = {0x6B, 0x00};
    i2c_write_blocking(i2c_default, addr, buf, 2, false);
}
//def need to anki up some of the basic commands
//also data types and binary table and pointers
//also binary math tricks
//critical that I figure out Github
static void mpu6050_read_raw(int16_t accel[3], int16_t gyro[3], int16_t *temp) {

    uint8_t buffer[6];
    uint8_t val = 0x3B;
    
    i2c_write_blocking(i2c_default, addr, &val, 1, true); 
    i2c_read_blocking(i2c_default, addr, buffer, 6, false);

    for (int i = 0; i < 3; i++) {
        accel[i] = (buffer[i * 2] << 8 | buffer[(i * 2) + 1]);
    }
//I am looking to intern at your company ,I am looking to learn from established embedded developers
    //
    val = 0x43;
    i2c_write_blocking(i2c_default, addr, &val, 1, true);
    i2c_read_blocking(i2c_default, addr, buffer, 6, false);  // False - finished with bus

    for (int i = 0; i < 3; i++) {
        gyro[i] = (buffer[i * 2] << 8 | buffer[(i * 2) + 1]);;
    }

    val = 0x41;
    i2c_write_blocking(i2c_default, addr, &val, 1, true);
    i2c_read_blocking(i2c_default, addr, buffer, 2, false);  // False - finished with bus

    *temp = buffer[0] << 8 | buffer[1];
}
#endif
