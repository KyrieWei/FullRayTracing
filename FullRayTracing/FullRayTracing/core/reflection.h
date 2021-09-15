#pragma once
#include "../maths/Vector3D.h"
#include "../maths/Defines.h"

float FrDielectric(float cosThetaI, float etaI, float etaT);
float FrConductor(float cosThetaI, const float& etaI, const float& etaT, const float& k);

class BxDF
{
public:
	virtual ~BxDF() {}
	
};

class Fresnel
{
public:
	virtual ~Fresnel();
	virtual float Evaluate(float cosI) const = 0;
	virtual std::string ToString() const = 0;
};

class FresnelConductor : public Fresnel
{
public:
	float Evaluate(float cosI) const;
	FresnelConductor(const float& etaI, const float& etaT, const float& k) : etaI(etaI), etaT(etaT), k(k) { }
	std::string ToString() const;
private:
	float etaI, etaT, k;
};

class FresnelDielectric : public Fresnel
{
public:
	float Evaluate(float cosI) const;
	FresnelDielectric(float etaI, float etaT) : etaI(etaI), etaT(etaT) { }
private:
	float etaI, etaT;
};

class LambertianReflection : public BxDF
{
public:
	LambertianReflection(const Vector3D& R) : R(R) { }
	Vector3D f(const Vector3D& wo, const Vector3D& wi) const;
private:
	const Vector3D R;
};