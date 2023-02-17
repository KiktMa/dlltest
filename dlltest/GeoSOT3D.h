#pragma once
#if defined(_MSC_VER) || defined(__CYGWIN__) || defined(__MINGW32__) || defined( __BCPLUSPLUS__) || defined( __MWERKS__)
#   if defined( GEOSOT3D_EXPORTS_STATIC )
#       define GEOSOT3D_EXPORTS
#       define GEOSOT3D_EXPORT_C
#   elif defined( GEOSOT3D_EXPORTS )
#       define GEOSOT3D_EXPORT __declspec(dllexport)
#       define GEOSOT3D_EXPORT_C extern "C" __declspec(dllexport)
#   else
#       define GEOSOT3D_EXPORT __declspec(dllimport)
#       define GEOSOT3D_EXPORT_C extern "C" __declspec(dllimport)
#endif
#else
#define GEOSOT3D_EXPORT
#define GEOSOT3D_EXPORT_C extern "C"
#endif

#ifdef GEOSOT_WASM_EXPORT
#undef GEOSOT2D_EXPORT_C
#include <emscripten\emscripten.h>
//#include <emscripten\val.h>
#define GEOSOT2D_EXPORT_C extern "C" EMSCRIPTEN_KEEPALIVE
#endif


/**
 * 输入3D剖分编码处理 给定经纬高度，指定层级，给出该层级下的编码
 * @param dbB 维度
 * @param dbL 经度
 * @param height 高度 单位米
 * @param level 层级
 * @param[out] geoID 三维编码
 * @returns 返回值为 -1时，层级越界，编码失败 ，返回值为0时，编码正常
 * @author ljf
 * @exception
 * @sa PointGridIdentify3D
 * @Date 2020/02/28 16:06
 * @note
 * 网格编码(点)
 **/
GEOSOT3D_EXPORT_C int PointGridIdentify3D(double dbB, double dbL, double height, unsigned char level, unsigned char geoID[]);

/**
 * 网格编码转换为网格的经纬高范围
 * @param[in] geoID 空间网格编码
 * @param[in] layer 层级
 * @param[out] dLon 绝对值最小的经度值
 * @param[out] dLat 绝对值最小的纬度值
 * @param[out] dHeight 绝对值最小的高度值
 * @param[out] dLonMax 绝对值最大的经度值
 * @param[out] dLatMax 绝对值最大的纬度值
 * @param[out] dHeightM 绝对值最大的高度值
 * @author ljf
 * @exception
 * @sa GetRangeFromCellCode3D
 * @Date 2020/03/18 9:31
 * @note
 **/
GEOSOT3D_EXPORT_C void GetRangeFromCellCode3D(unsigned char geoID[], unsigned char layer, double &dLon, double &dLat, double &dHeight, double &dLonMax, double &dLatMax, double &dHeightM);


//////////////////////////////////////////////////////////////////////////
//几何体
//////////////////////////////////////////////////////////////////////////
/**
 * 三维多边形剖分编码 给定经纬高度，指定层级，给出该层级下的编码
 * @param[in] chLayer 剖分层级
 * @param[in] dbLon 多边形点的经度集合
 * @param[in] dbLat 多边形点的纬度集合
 * @param[in] pointNum 多边形点的数量
 * @param[in] dbStartHeight 多边形起点高度
 * @param[in] dbEndHeight 多边形终点高度
 * @param[out] geoID 剖分编码结果集合
 * @param[out] num 剖分网格数量
 * @returns 返回值为-1时，传入geoID_array数组长度不够，返回值为-2时，编码失败，返回值1时，编码成功
 * @author wgf
 * @exception
 * @Date 2020/02/23 12:25
 * @note
 * 网格编码(多边形体)
 **/
GEOSOT3D_EXPORT_C int PolygonGridIndentify3D(int chLayer, double dbLon[], double dbLat[], int pointNum, double dbStartHeight, double dbEndHeight, unsigned char geoID[], int &num);



/**
 * 三维折线剖分编码--Bresenham方法 给定经纬高度，指定层级，给出该层级下的编码
 * @param[in] dbLon 点经度集合
 * @param[in] dbLat 点纬度集合
 * @param[in] dbHeight 点高度集合
 * @param[in] pointNum 点的个数
 * @param[in] layer 剖分层级
 * @param[out] geoID 剖分编码结果集合
 * @param[out] num 剖分网格数量
 * @returns 返回值为-1时，传入geoID_array数组长度不够，返回值为-2时，编码失败，返回值1时，编码成功
 * @author wgf
 * @exception
 * @sa ReturnAllCell3D_Line
 * @Date 2020/02/23 12:40
 * @note 网格编码(折线体)
 **/
GEOSOT3D_EXPORT_C int ReturnAllCell3D_Line(double dbLon[], double dbLat[], double dbHeight[], int pointNum, int layer, unsigned char geoID[], int &num);
