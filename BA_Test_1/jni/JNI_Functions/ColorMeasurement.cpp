#include "Functions/ProcessingFunctions.hpp"
#include "JNI_FUNCTIONS/JNI_Functions.hpp"

using namespace std;

#ifdef __cplusplus
extern "C" {
#endif

	/**
		\brief UNUSED Java Native Interface function called from Java which delegates the retrieval of color values and correlated color temperature

		@param env a JNIEnv pointer variable pointing to the Java Native Interface Environment variable
		@param jo a jobject variable containing an object of the Java Class calling this function
		@param frameAddress a jlong variable containing the memory address of a cv::Mat object containing frame data which is generated by Java via the camera
		@param values a jdoubleArray data structure containing the x and y coordinates of the scan rectangle as well as the width and height

		Delegates the retrieval of the color values and correlated color temperature value to the function proc::gnrc::measuredImageValues()

		@see proc::gnrc::measuredImageValues()

		@see Java/Android Component Documentation
		@see de.ur.juergenhahn.ba.Handler.NativeHandler.measureImageValues()

		@return a jdoubleArray containing the color values and the correlated color temperature
	*/
	JNIEXPORT jdoubleArray JNICALL Java_de_ur_juergenhahn_ba_Handler_NativeHandler_measureImageValuesNative(JNIEnv *env, jobject jo, jlong frameAddress, jdoubleArray values)
	{
		jsize length = env->GetArrayLength(values);
		jdouble *valuesBody = env->GetDoubleArrayElements(values, 0);

		jdoubleArray ret = env->NewDoubleArray(5);
		double temp[5];

		cv::Mat &frame = *(cv::Mat *) frameAddress;
		cv::Rect rect(valuesBody[0], valuesBody[1], valuesBody[2], valuesBody[3]);

		proc::gnrc::measuredImageValues(temp, frame, rect);

		env->SetDoubleArrayRegion(ret, 0, 5, temp);
		env->ReleaseDoubleArrayElements(values, valuesBody, 0);
		env->DeleteLocalRef(values);

		return ret;
	}

#ifdef __cplusplus
}
#endif
