#pragma once

#ifndef LIBREALSENSE_F200_CALIB_PARAMS_H
#define LIBREALSENSE_F200_CALIB_PARAMS_H

#include <librealsense/CameraContext.h>

namespace f200
{

struct OACOffsetData
{
    int OACOffset1;
    int OACOffset2;
    int OACOffset3;
    int OACOffset4;
};

struct IVCAMTemperatureData
{
    float LiguriaTemp;
    float IRTemp;
    float AmbientTemp;
};

struct IVCAMThermalLoopParams
{
    float IRThermalLoopEnable = 1;      // enable the mechanism
    float TimeOutA = 10000;             // default time out
    float TimeOutB = 0;                 // reserved
    float TimeOutC = 0;                 // reserved
    float TransitionTemp = 3;           // celcius degrees, the transition temperatures to ignore and use offset;
    float TempThreshold = 2;            // celcius degrees, the temperatures delta that above should be fixed;
    float HFOVsensitivity = 0.025f;
    float FcxSlopeA = -0.003696988f;    // the temperature model fc slope a from slope_hfcx = ref_fcx*a + b
    float FcxSlopeB = 0.005809239f;     // the temperature model fc slope b from slope_hfcx = ref_fcx*a + b
    float FcxSlopeC = 0;                // reserved
    float FcxOffset = 0;                // the temperature model fc offset
    float UxSlopeA = -0.000210918f;     // the temperature model ux slope a from slope_ux = ref_ux*a + ref_fcx*b
    float UxSlopeB = 0.000034253955f;   // the temperature model ux slope b from slope_ux = ref_ux*a + ref_fcx*b
    float UxSlopeC = 0;                 // reserved
    float UxOffset = 0;                 // the temperature model ux offset
    float LiguriaTempWeight = 1;        // the liguria temperature weight in the temperature delta calculations
    float IrTempWeight = 0;             // the Ir temperature weight in the temperature delta calculations
    float AmbientTempWeight = 0;        // reserved
    float Param1 = 0;                   // reserved
    float Param2 = 0;                   // reserved
    float Param3 = 0;                   // reserved
    float Param4 = 0;                   // reserved
    float Param5 = 0;                   // reserved
};

struct IVCAMTesterData
{
    int16_t TableValidation;
    int16_t TableVarsion;
    OACOffsetData OACOffsetData;
    IVCAMThermalLoopParams ThermalLoopParams;
    IVCAMTemperatureData TemperatureData;
};
    
struct CameraCalibrationParameters 
{
    float Rmax;
    float Kc[3][3];		// [3x3]: intrinsic calibration matrix of the IR camera
    float Distc[5];		// [1x5]: forward distortion parameters of the IR camera
    float Invdistc[5];	// [1x5]: the inverse distortion parameters of the IR camera
    float Pp[3][4];		// [3x4]: projection matrix
    float Kp[3][3];		// [3x3]: intrinsic calibration matrix of the projector
    float Rp[3][3];		// [3x3]: extrinsic calibration matrix of the projector
    float Tp[3];			// [1x3]: translation vector of the projector
    float Distp[5];		// [1x5]: forward distortion parameters of the projector
    float Invdistp[5];	// [1x5]: inverse distortion parameters of the projector
    float Pt[3][4];		// [3x4]: IR to RGB (texture mapping) image transformation matrix
    float Kt[3][3];
    float Rt[3][3];
    float Tt[3];
    float Distt[5];		// [1x5]: The inverse distortion parameters of the RGB camera
    float Invdistt[5];
    float QV[6];
};

struct CameraCalibrationParametersVersion
{
    int uniqueNumber; //Should be 0xCAFECAFE in Calibration version 1 or later. In calibration version 0 this is zero.
    int16_t TableValidation;
    int16_t TableVarsion;
    CameraCalibrationParameters CalibrationParameters;
};

class IVCAMHardwareIOInternal;
    
class IVCAMHardwareIO
{
    std::unique_ptr<IVCAMHardwareIOInternal> internal;
    
public:
    
    IVCAMHardwareIO();
    ~IVCAMHardwareIO();
    
    bool StartTempCompensationLoop();
    void StopTempCompensationLoop();
    
    // SetDepthResolution(int width, int height)
    
    CameraCalibrationParameters & GetParameters();
};
    
} // end namespace f200

#endif