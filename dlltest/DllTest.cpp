#include <iostream>
#include <cassert>
#include <string>
#include <fstream>
#include <cmath>
#include <sstream>std::stringstream ss
#include "GeoSOT3D.h"

#include "Utils.hpp"


inline
void test(bool quality) {
	if (!quality) {
		std::cout << "���벻һ��" << std::endl;
		//exit(-1);
	}
}

int main() {
	std::ifstream ifs;
	std::ofstream ofs;
	//ifs.open(".\\xibu\\xibu128_centerpoint.txt"); // ������ļ�
	ifs.open("D:\\test_tif\\lonlat\\input.txt");
    ofs.open("D:\\test_tif\\lonlat\\out.txt"); // ������ļ�
	if (!ifs.is_open() || !ofs.is_open()) {
		std::cerr << "�ļ���ʧ��" << std::endl;
		//exit(-1);
	}
	std::string line;
	std::stringstream ss;

	unsigned char level = 18   ;//256 x 256������
	double height = 0;
	double dbB = 0;
	double dbL = 0;
	int id = 0;
	std::string strB;
	std::string strL;
	std::string strHeight;
	while (std::getline(ifs, line)) {
		ss << line;
		ss >> strB >> strL >> strHeight;
		// std::cout << strB << " " << strL << " " << strHeight << std::endl;
		dbB = std::stod(strB);
		dbL = std::stod(strL);
		height = std::stod(strHeight);

		unsigned char geoSotCode[256]{ 0x00 };
		int ret = PointGridIdentify3D(dbB, dbL, height, level, geoSotCode);
		if (ret != 0) {
			std::cerr << "����" << std::endl;
			return -1;
		}
		ChangeCode changeCode(geoSotCode, level);

		std::string hexOneDCode = "";
		changeCode.getHexOneDimensionalCode(hexOneDCode);

		//double dlon;
  //      double dlat;
	 //   double dheight;
	 //   double dlonmax;
	 //   double dlatmax;
	 //   double dheightm;
	 //   GetRangeFromCellCode3D(geoSotCode, level,dlon, dlat, dheight,dlonmax, dlatmax,dheightm);

		//ofs << line << "\t" << hexOneDCode << std::endl;
		id++;
		//ofs <<id<<" "<<hexOneDCode<<" 1"<<" "<<"19" << std::endl;
		ofs << id << " " << hexOneDCode << " " << 1 << " " << 18 << std::endl;

		line.clear();
		ss.clear();
	}
	std::cout << "����" << std::endl;
	ifs.close();
	ofs.close();
}


//int main()
//{
//	/*std::string Ndms = "12^12'37.0098\"N";
//	std::string Edms = "123^32'54.8198\"E";
//	double nddd = dms2ddd(Ndms);
//	double eddd = dms2ddd(Edms);*/
//
//
//	double height = 21.028828;
//	double dbB = 28.27137104081308;
//	double dbL = 113.0292103333053;
//	unsigned char level = 20;
//
//	double dLon = 0.0;
//	double dLat = 0.0;
//	double dHeight = 0.0;
//	double dLonMax = 0.00;
//	double dLatMax = 0.0;
//	double dHeightM = 0.0;
//
//	double maxB = 0.0;
//	double maxL = 0.0;
//	double minB = 0.0;
//	double minL = 0.0;
//
//	std::fstream fs;
//	fs.open("GeoSOT_code.txt", std::ios::out);
//	if (!fs.is_open()) {
//		std::cerr << " ���ļ�ʧ��" << std::endl;
//		// exit(-1);
//	}
//	fs << "��ӡ��ʽ����ͼ�������ң��������ϵ��������" << std::endl;
//
//	for (int j = 0; j < 18; ++j) {
//		fs << "�� " << j + 1 << std::endl;
//		dbB = 28.267777777777777;
//		for (int i = 0; i < 8; ++i) {
//			unsigned char geoSotCode[256]{ 0x00 };
//			int ret = PointGridIdentify3D(dbB, dbL, height, level, geoSotCode);
//			if (ret != 0) {
//				std::cerr << "����" << std::endl;
//				return -1;
//			}
//			ChangeCode changeCode(geoSotCode, level);
//
//			std::string hexOneDCode = "";
//			changeCode.getHexOneDimensionalCode(hexOneDCode);
//			fs << i + 1 << " : " << hexOneDCode << std::endl;
//
//			GetRangeFromCellCode3D(geoSotCode, level, dLon, dLat, dHeight, dLonMax, dLatMax, dHeightM);
//			
//
//			dbB = dLatMax;
//		}
//		maxB = dLatMax;
//		dbL = dLonMax;
//	}
//	maxL = dbL;
//	
//	fs << std::setprecision(17);
//	fs << "γ�ȷ�Χ��" << minB << " ~ " << maxB << std::endl;
//	fs << "���ȷ�Χ��" << minL << " ~ " << maxL << std::endl;
//	fs << "��С�߶� ��" << dHeight << std::endl;
//	fs << "���߶ȣ�" << dHeightM << std::endl;
//
//	unsigned char geoSotCode[256]{ 0x00 };
//	int ret = PointGridIdentify3D(dbB, dbL, height, level, geoSotCode);
//	if (ret != 0) {
//		std::cerr << "����" << std::endl;
//		return -1;
//	}
//	ChangeCode changeCode(geoSotCode, level);
//	std::string octalOneDCode = "";
//	changeCode.getOctalOneDimensionalCode(octalOneDCode);
//	std::cout << " : " << octalOneDCode << std::endl;
//	std::string hexOneDCode = "";
//	changeCode.getHexOneDimensionalCode(hexOneDCode);
//	std::cout << " : " << hexOneDCode << std::endl;
//
//	
//
//	GetRangeFromCellCode3D(geoSotCode, level, dLon, dLat, dHeight, dLonMax, dLatMax, dHeightM);
//	std::cout << std::setprecision(17);
//	std::cout << "��Сγ�ȣ�" << dLat << std::endl;
//	std::cout << "��С���ȶȣ�" << dLon << std::endl;
//	std::cout << "��С�߶ȣ�" << dHeight << std::endl;
//	std::cout << "���γ�ȣ�" << dLatMax << std::endl;
//	std::cout << "��󾭶ȣ�" << dLonMax << std::endl;
//	std::cout << "���߶ȣ�" << dHeightM << std::endl;
//}
//#include <iostream>
//#include "geosot3d.h"
//int main()
//{
// /*   ����Ժ���½� 113.0288125436,28.2676253053,3.1638
//	             113.0288125436,28.2714994323,3.1638
//	             113.0399756323,28.2714994323,3.1638
//	             113.0399756323,28.2676253053,3.1638
//	����Ժ���Ͻ� 113.0399756323,28.2714994323,90.8258
//	             113.0288125436,28.2714994323,90.8258
//	             113.0399756323,28.2714994323,90.8258
//	             113.0399756323,28.2676253053,90.8258
//	�����������½� 86.583080��41.595060 1124
//	        ���Ͻ� 86.635230��41.570990 1308  */
//
//	double mydbb = 41.595060;//γ��
//    double mydbl = 86.583080;//����
//	double myheight = 0;
//	int mylevel = 19;
//	unsigned char code[256];
//	int grid3d= PointGridIdentify3D(mydbb, mydbl, myheight, mylevel, code);
//
//	double dlon;
//	double dlat;
//	double dheight;
//	double dlonmax;
//	double dlatmax;
//	double dheightm;
//	GetRangeFromCellCode3D(code, mylevel,dlon, dlat, dheight,dlonmax, dlatmax,dheightm);
//	std::cout <<dlon <<'\n' << dlat << '\n'<< dlonmax<< '\n' << dlatmax<< '\n' ;
//	return 0;
//}//		dLon	113.02888888888889	double
 // dLat	28.267777777777777	double




//#include <windows.h>
//#include <iostream>
//int main()
//{
//	//loadlibrary
//	double mydbb = 100;
//	double mydbl =100;
//	double myheight = 100;
//	unsigned char mylevel = 23;
//	unsigned char code[256];
//	hinstance hdll = loadlibrary("libgeosot3d.dll");
//	typedef int(*mygeosot3d)(double dbb, double dbl, double height, unsigned char level, unsigned char geoid[]);
//	mygeosot3d addfunction = (mygeosot3d)getprocaddress(hdll,"geosot3d");
//	addfunction(mydbb, mydbl, myheight, mylevel, code);
//	return 0;
//}