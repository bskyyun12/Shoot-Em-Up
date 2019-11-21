#pragma once
#include "MathHelper.h"
#include <vector>

class BezierPath
{
private:

	std::vector<BezierCurve> mCurves;
	std::vector<int> mSamples;

public:

	BezierPath();
	~BezierPath();

	void Clear();

	void AddCurve(BezierCurve curve, int samples);

	void Sample(std::vector<Vector2D>* sampledPath);
};