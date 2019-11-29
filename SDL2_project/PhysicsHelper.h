#pragma once
#include "BoxCollider.h"
#include "MathHelper.h"

inline bool BoxBoxCollision(BoxCollider* b1, BoxCollider* b2)
{
	Vector2D projAxis[4];

	projAxis[0] = (b1->GetVertexPos(0) - b1->GetVertexPos(1)).Normalized();
	projAxis[1] = (b1->GetVertexPos(0) - b1->GetVertexPos(2)).Normalized();
	projAxis[2] = (b2->GetVertexPos(0) - b2->GetVertexPos(1)).Normalized();
	projAxis[3] = (b2->GetVertexPos(0) - b2->GetVertexPos(2)).Normalized();

	float b1Min = 0.0f, b1Max = 0.0f;
	float b2Min = 0.0f, b2Max = 0.0f;
	float proj1 = 0.0f, proj2 = 0.0f;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			proj1 = Dot(b1->GetVertexPos(j), projAxis[i]);
			proj2 = Dot(b2->GetVertexPos(j), projAxis[i]);

			if (j == 0)
			{
				b1Min = b1Max = proj1;
				b2Min = b2Max = proj2;
			}
			else
			{
				if (proj1 < b1Min)
					b1Min = proj1;
				if (proj1 > b1Max)
					b1Max = proj1;

				if (proj2 < b2Min)
					b2Min = proj2;
				if (proj2 > b2Max)
					b2Max = proj2;
			}
		}

		float halfDis1 = (b1Max - b1Min) * 0.5f;
		float midPoint1 = b1Min + halfDis1;

		float halfDis2 = (b2Max - b2Min) * 0.5f;
		float midPoint2 = b2Min + halfDis2;

		if (abs(midPoint1 - midPoint2) > (halfDis1 + halfDis2))
		{
			return false;
		}
	}
	return true;
}

inline bool ColliderColliderCheck(Collider* c1, Collider* c2)
{
	return BoxBoxCollision(static_cast<BoxCollider*>(c1), static_cast<BoxCollider*>(c2));
}
