/*
 * Copyright 2012 AS3NUI
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */
#ifndef KinectExtension_MSKinectDevice_h
#define KinectExtension_MSKinectDevice_h

#include "ExtensionConfig.h"

#ifdef AIRKINECT_TARGET_MSSDK

#include "PointCloudRegion.h"
#include "KinectCapabilities.h"
#include "KinectDevice.h"
#include "AKMSSDKRGBParser.h"
#include "AKMSSDKDepthParser.h"
#include "AKMSSDKInfraredParser.h"

class MSKinectDevice : public KinectDevice
{
public:

	MSKinectDevice(int nr);
    
    void			start();
    void			stop();
    
    void			dispose();

	//Overridden FRE functions
	FREObject			freSetDepthMode(FREObject argv[]);
	FREObject			freSetInfraredMode(FREObject argv[]);

	FREObject           freSetSkeletonMode(FREObject argv[]);
	FREObject			freChooseSkeletons(FREObject argv[]);
	FREObject			freSetNearModeEnabled(FREObject argv[]);
	FREObject           freCameraElevationGetAngle(FREObject argv[]);
	FREObject           freCameraElevationSetAngle(FREObject argv[]);

protected:

	void				setUserColor(int userID, int color, bool useIntensity);
	void				setRGBMode(int rgbWidth, int rgbHeight, int asRGBWidth, int asRGBHeight, bool asRGBMirrored);

	void				setDefaults();
	void				cleanupByteArrays();

	void				createPointCloudGenerator();
	void				createUserMasksGenerator();
	void				createUserFrameGenerator();

private:

	NUI_TRANSFORM_SMOOTH_PARAMETERS		transformSmoothingParameters;
	void					addKinectDeviceStatusListener();
	void CALLBACK			statusProc( HRESULT hrStatus, const OLECHAR* instanceName, const OLECHAR* uniqueDeviceName );
	static void CALLBACK	statusProcThunk( HRESULT hrStatus, const OLECHAR* instanceName, const OLECHAR* uniqueDeviceName, void * pUserData);
	void					dispatchError(HRESULT hr);

	HRESULT					setSkeletonTrackingFlags();

	int						imageFrameTimeout;
	INuiSensor*             nuiSensor;

	static void             *deviceThread(void *ptr);
	void                    run();

    HANDLE					depthFrameEvent;
	HANDLE					infraredFrameEvent;
    HANDLE					rgbFrameEvent;
    HANDLE					userEvent;

	HANDLE					userFrameHandle;
    HANDLE					depthFrameHandle;
	HANDLE					infraredFrameHandle;
    HANDLE					rgbFrameHandle;

	BYTE					*userIndexColors;

	NUI_IMAGE_RESOLUTION	depthResolution;
	bool					depthPlayerIndexEnabled;

	NUI_IMAGE_RESOLUTION	infraredResolution;
    
	NUI_IMAGE_RESOLUTION	rgbResolution;

	//Handlers
	void					readRGBFrame();
	AKMSSDKRGBParser*		rgbParser;

	void					readDepthFrame();
	AKMSSDKDepthParser*		depthParser;

	void					readInfraredFrame();
	AKMSSDKInfraredParser*	infraredParser;

	void					dispatchUserFrameIfNeeded();
	void					dispatchRGBIfNeeded();
	void					dispatchDepthIfNeeded();
	void					dispatchInfraredIfNeeded();
	void					dispatchPointCloudIfNeeded();
	void					dispatchUserMaskIfNeeded();
};

#endif
#endif