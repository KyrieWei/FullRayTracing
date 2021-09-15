#include "reflection.h"
#include "../tools/Utility.h"

float FrDielectric(float cosThetaI, float etaI, float etaT)
{
	cosThetaI = m_clamp(cosThetaI, -1, 1);

	//potentially swap indices of refraction
	if (cosThetaI < 0.f)
	{
		std::swap(etaI, etaT);
		cosThetaI = std::abs(cosThetaI);
	}

	//compute cosThetaT using Snell's law
	float sinThetaI = std::sqrt(std::max((float)0, 1 - cosThetaI * cosThetaI));
	float sinThetaT = etaI / etaT * sinThetaI;

	//handle total internal reflection
	if (sinThetaT >= 1) return 1;

	float cosThetaT = std::sqrt(std::max((float)0, 1 - sinThetaT * sinThetaT));

	float rparl = (etaT * cosThetaI - etaI * cosThetaT) / (etaT * cosThetaI + etaI * cosThetaT);
	float rparp = (etaI * cosThetaI - etaT * cosThetaT) / (etaI * cosThetaI + etaT * cosThetaT);

	return 0.5 * (rparl * rparl + rparp * rparp);
}

float FrConductor(float cosThetaI, const float& etaI, const float& etaT, const float& k)
{
	cosThetaI = m_clamp(cosThetaI, -1, 1);
	float eta = etaT / etaI;
	float etak = k / etaI;

	float cosThetaI2 = cosThetaI * cosThetaI;
	float sinThetaI2 = 1.0 - cosThetaI2;
	float eta2 = eta * eta;
	float etak2 = etak * etak;

	float t0 = eta2 - etak2 - sinThetaI2;
	float a2plusb2 = sqrt(t0 * t0 + 4 * eta2 * etak2);
	float t1 = a2plusb2 + cosThetaI2;
	float a = sqrt(0.5f * (a2plusb2 + t0));
	float t2 = 2.0f * cosThetaI * a;
	float Rs = (t1 - t2) / (t1 + t2);

	float t3 = cosThetaI2 * a2plusb2 + sinThetaI2 * sinThetaI2;
	float t4 = t2 * sinThetaI2;
	float Rp = Rs * (t3 - t4) / (t3 + t4);

	return 0.5 * (Rp + Rs);
}

Fresnel::~Fresnel() { }

float FresnelConductor::Evaluate(float cosThetaI) const
{
	return FrConductor(std::abs(cosThetaI), etaI, etaT, k);
}

float FresnelDielectric::Evaluate(float cosThetaI) const
{
	return FrDielectric(cosThetaI, etaI, etaT);
}

Vector3D LambertianReflection::f(const Vector3D& wo, const Vector3D& wi) const
{
	return R * InvPI;
}