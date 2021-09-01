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

