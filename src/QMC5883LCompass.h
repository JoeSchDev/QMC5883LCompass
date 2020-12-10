#ifndef QMC5883L_Compass
#define QMC5883L_Compass

#include "Arduino.h"
#include "Wire.h"

#define MODE_CONTROL_STANDBY 0x00
#define MODE_CONTROL_CONTINUES 0x01

#define DATA_RATE_10HZ  (0x00 << 2)
#define DATA_RATE_50HZ  (0x01 << 2)
#define DATA_RATE_100HZ (0x02 << 2)
#define DATA_RATE_200HZ (0x03 << 2)

#define FULL_SCALE_2G  (0x00 << 4)
#define FULL_SCALE_8G  (0x01 << 4)

#define OVER_SAMPLE_RATIO_64  (0x03 << 6)
#define OVER_SAMPLE_RATIO_128 (0x02 << 6)
#define OVER_SAMPLE_RATIO_256 (0x01 << 6)
#define OVER_SAMPLE_RATIO_512 (0x00 << 6)

#define STATUS_DRDY  0x01
#define STATUS_OVL   0x02
#define STATUS_DOR   0x04

class QMC5883LCompass{
	
  public:
    QMC5883LCompass();
	void init();
    void setADDR(byte b);
    void setMode(byte mode, byte odr, byte rng, byte osr);
	void setSmoothing(byte steps, bool adv);
	void setCalibration(int x_min, int x_max, int y_min, int y_max, int z_min, int z_max);
    void setReset();
    byte read();
	int getX();
	int getY();
	int getZ();
	int getAzimuth();
	byte getBearing(int azimuth);
	void getDirection(char* myArray, int azimuth);
	
  private:
    void _writeReg(byte reg,byte val);
	int _get(int index);
	bool _smoothUse = false;
	byte _smoothSteps = 5;
	bool _smoothAdvanced = false;
    byte _ADDR = 0x0D;
	int _vRaw[3] = {0,0,0};
	int _vHistory[10][3];
	int _vScan = 0;
	long _vTotals[3] = {0,0,0};
	int _vSmooth[3] = {0,0,0};
	void _smoothing();
	bool _calibrationUse = false;
	int _vCalibration[3][2];
	int _vCalibrated[3];
	void _applyCalibration();
	const char _bearings[16][3] =  {
		{' ', ' ', 'N'},
		{'N', 'N', 'E'},
		{' ', 'N', 'E'},
		{'E', 'N', 'E'},
		{' ', ' ', 'E'},
		{'E', 'S', 'E'},
		{' ', 'S', 'E'},
		{'S', 'S', 'E'},
		{' ', ' ', 'S'},
		{'S', 'S', 'W'},
		{' ', 'S', 'W'},
		{'W', 'S', 'W'},
		{' ', ' ', 'W'},
		{'W', 'N', 'W'},
		{' ', 'N', 'W'},
		{'N', 'N', 'W'},
	};
	
	
	
};

#endif
