#ifndef CAMERA_DEBUG_H
#define CAMERA_DEBUG_H

#define DBG_CAMERA_HARDWARE		0
#define DBG_V4L2_CAMERA			0
#define DBG_PREVIEW				0
#define DBG_CALLBACK			0
#define DBG_CAMERA_FACTORY		0
#define DBG_CAMERA_CONFIG		0

// enable all print information
// #define LOG_NDEBUG 0

#define F_LOG ALOGV("%s, line: %d", __FUNCTION__, __LINE__);

#define LOGV	ALOGV
#define LOGD	ALOGD
#define LOGW	ALOGW
#define LOGE	ALOGE

#define LOGE_IF	ALOGE_IF
#define LOGW_IF	ALOGW_IF

#define TO_UPDATA	0			// to do

// performance debug
#define DBG_TIME_ENABLE		0
#if DBG_TIME_ENABLE
#define LOG_TIME			ALOGD
#define DBG_TIME_BEGIN(inf, en)											\
	int64_t llt_ms = systemTime() / 1000000;							\
	int64_t lt_ms = llt_ms;												\
	int64_t nt_ms = 0;													\
	if (en)	LOG_TIME("\t[T_DBG_bgn] %s timestamp: %lld", inf, lt_ms);

#define DBG_TIME_DIFF(inf)												\
	nt_ms = systemTime() / 1000000;										\
	LOG_TIME("\t[T_DBG_dff] %s use: %lld(ms)", inf, (nt_ms - lt_ms));	\
	nt_ms = lt_ms;

#define DBG_TIME_END(inf, en)											\
	nt_ms = systemTime() / 1000000;										\
	LOG_TIME("\t[T_DBG_end] %s use: %lld(ms)", inf, (nt_ms - llt_ms));	\
	if (en) LOG_TIME("\t[T_DBG_end] %s timestamp: %lld", inf, nt_ms);
#else
#define DBG_TIME_BEGIN(inf, en)
#define DBG_TIME_DIFF(inf)
#define DBG_TIME_END(inf, en)
#endif



#define DBG_TIME_AVG_ENABLE		0
#if DBG_TIME_AVG_ENABLE
#define LOG_TIME_AVG			ALOGD
#define DBG_TIME_AVG_BEGIN(tag)											\
	static int64_t tag##_time = 0;										\
	static int tag##_cnt = 0;

#define DBG_TIME_AVG_INIT(tag)											\
	tag##_time = 0;	tag##_cnt = 0;

#define DBG_TIME_AVG_AREA_IN(tag)										\
	int64_t tag##_diff = systemTime();
	
#define DBG_TIME_AVG_AREA_OUT(tag)										\
	tag##_diff = systemTime() - tag##_diff;								\
	tag##_time += tag##_diff;											\
	tag##_cnt++;
	
#define DBG_TIME_AVG_END(tag, inf)										\
	if (tag##_cnt > 0) LOG_TIME_AVG("\t[T_DBG_avg] %s cnt: %d, average use: %lld(us)", inf, tag##_cnt, tag##_time/tag##_cnt/1000);
#else
#define DBG_TIME_AVG_BEGIN(tag)
#define DBG_TIME_AVG_INIT(tag)
#define DBG_TIME_AVG_AREA_IN(tag)
#define DBG_TIME_AVG_AREA_OUT(tag)
#define DBG_TIME_AVG_END(tag, inf)
#endif


#ifdef __SUN4I__
#define USE_MP_CONVERT 1		// A10 can define 1, or must 0
#else
#define USE_MP_CONVERT 0		// A10 can define 1, or must 0
#endif

#endif // CAMERA_DEBUG_H

