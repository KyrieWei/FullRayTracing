#pragma once

float FrDielectric(float cosThetaI, float etaI, float etaT);


class BxDF
{
public:
	virtual ~BxDF() {}
	
};

class LambertianReflection : public BxDF
{

};