#include <jni.h>
#include <string>


extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_nativepoc_NativeLibrary_stringFromJNI(JNIEnv *env,
                                                       jobject instance) {
    std::string hello = "Mirafra";
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_example_nativepoc_NativeLibrary_passingDataToJni(JNIEnv *env,
                                                          jobject instance,
                                                          jdoubleArray tmpArray_,
                                                          jint tmpInt,
                                                          jfloat tmpFloat) {
    jdouble *tmpArray = env->GetDoubleArrayElements(tmpArray_, NULL);
    int ret = 0;

    if (tmpArray[0] == 1 && tmpArray[1] == 2 && tmpArray[2] == 3 && tmpInt == 1) {
        // Correct Data got from JAVA
        ret = 0;
    } else {
        // Wrong Data got from JAVA
        ret = -1;
    }

    env->ReleaseDoubleArrayElements(tmpArray_, tmpArray, 0);
    return ret;
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_example_nativepoc_NativeLibrary_passObjectToJNI(JNIEnv *env,
                                                         jobject instance,
                                                         jobject sampleDataObj) {

    // Get jclass of the object
    jclass sampleDataOBJClass = env->GetObjectClass(sampleDataObj);

    // Get data field IDs of the object
    jfieldID sampIntField = env->GetFieldID(sampleDataOBJClass, "sampleInt", "I");
    jfieldID sampBoolField = env->GetFieldID(sampleDataOBJClass, "sampleBoolean", "Z");
    jfieldID sampStringField = env->GetFieldID(sampleDataOBJClass, "sampleString",
                                               "Ljava/lang/String;");

    // Get individual Data
    jint sampleInt = env->GetIntField(sampleDataObj, sampIntField);
    jboolean sampleBoolean = env->GetBooleanField(sampleDataObj, sampBoolField);

    // Update data
    const char *successString = "SUCCESS";
    env->SetObjectField(sampleDataObj, sampStringField, env->NewStringUTF(successString));

    // return error code (in this case, return the int value form the object)
    return sampleInt;
}

extern "C"
JNIEXPORT jobject JNICALL
Java_com_example_nativepoc_NativeLibrary_getObjectFromJNI(JNIEnv *env,
                                                          jobject instance) {

    // Create a jclass from actual Java object class path
    jclass sampleObjClass = env->FindClass(
            "com/example/nativepoc/EmployeeDataObj");
    jmethodID methodId = env->GetMethodID(sampleObjClass, "<init>", "()V");
    jobject sampleObj = env->NewObject(sampleObjClass, methodId);

    //Update fields of object
    const char *successString = "SUCCESS";
    jfieldID sampStringField = env->GetFieldID(sampleObjClass, "sampleString",
                                               "Ljava/lang/String;");
    env->SetObjectField(sampleObj, sampStringField, env->NewStringUTF(successString));

    //Update int data field
    int data = 10;
    jfieldID sampIntField = env->GetFieldID(sampleObjClass, "sampleInt", "I");
    env->SetIntField(sampleObj, sampIntField, data);

    return sampleObj;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_nativepoc_NativeLibrary_callTheCallBackMethod(JNIEnv *env,
                                                               jobject instance) {

    // Get jclass of the instance
    jclass jClassInstance = env->GetObjectClass(instance);

    // Get java callback method
    jmethodID callBackJava = env->GetMethodID(jClassInstance, "callBack", "(ILjava/lang/String;)V");

    // If method not found
    if (NULL == callBackJava) return;

    // create string data to pass
    const char *successString = "SUCCESS";

    // integer value to pass
    int data = 10;

    // Call back Java method with parameters
    env->CallVoidMethod(instance, callBackJava, data, env->NewStringUTF(successString));
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_nativepoc_NativeLibrary_stringNameFromJNI(JNIEnv *env, jobject thiz) {
    std::string hello = "Nitin Kumar";
    return env->NewStringUTF(hello.c_str());
}