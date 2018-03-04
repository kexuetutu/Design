#pragma once

#include <vector>
#include <map>
#include "section.h"
#include "material.h"

class Beam
{
	//static double gama0;
public:
	Beam();
	~Beam();

	void setSection(Section* section, double c);//设置几何参数
	void setMaterial(Concrete* concrete, Rebar* rebarL, Rebar* rebarS);//设置材料
	void setCalculateParameter(double γ0, int Nfb, int Nfb_gz);//设置计算参数
	void setForce(double N, double V2, double V3, double T, double M2, double M3);//设置内力
	void design();//配筋设计
	void check();//验算配筋结果

private:
	struct Data
	{//基本参数
		//[?]怎么给struct赋初值？
		//几何参数
		Section* section;//截面参数
		double c;//保护层厚度
		//材料参数
		Concrete* concrete;//砼材料
		Rebar* longitudinal;//纵筋材料
		Rebar* stirrup;//箍筋材料
//		Steel* skeleton;//钢骨材料
		//计算参数
		double γ0;//γ0
		int Nfb;//抗震等级
		int Nfb_gz;//抗震构造等级
	} data;
	struct Force
	{//内力
		double N;
		double V2;
		double V3;
		double T;
		double M2;
		double M3;
	};
	std::map<std::string, Force> m_caseMap;//单工况内力
	std::vector<Force> m_FundamentalCombination;//基本组合
	std::vector<Force> m_NominalCombination;//标准组合
	std::vector<Force> m_QuasiPermanentCombination;//准永久组合
	struct Result
	{//设计结果
		double x;//受压区高度mm
		double As;//受拉钢筋面积mm²
		double As_c;//受压钢筋面积mm²
		double rho;//受拉钢筋配筋率ρ
		double rho_c;//受压钢筋配筋率ρ'
		double Asv;//箍筋面积mm²
		double rho_sv;//箍筋面积率ρsv
	};
	std::vector<Result> m_result;//各断面设计结果
	
	void setCheck();

	friend class DesignBeam;
};